#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h>
#include <fstream>
#include "List.h"
#include "DynamicArray.h"


class Node {
public:
    double x, y;
    Node(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

class Edge {
public:
    int x;
    int y;
    double weight;
    Edge(int x, int y, double weight) {
        this->x = x;
        this->y = y;
        this->weight = weight;
    }
};

int edge_cmp(Edge e1, Edge e2) {
    if (e1.weight == e2.weight) return 0;
    else if (e1.weight < e2.weight) return -1;
    else return 1;
}
int edge_cmp(Edge* e1, Edge* e2) {
    if (e1->weight == e2->weight) return 0;
    else if (e1->weight < e2->weight) return -1;
    else return 1;
}
double edge_key(Edge e) {
    return e.weight;
}
double edge_key(Edge* e) {
    return e->weight;
}
std::string edge_to_str(Edge e) {
    return std::to_string(e.x) + " " + std::to_string(e.y) + " " + std::to_string(e.weight);
}
std::string edge_to_str(Edge* e) {
    return std::to_string(e->x) + " " + std::to_string(e->y) + " " + std::to_string(e->weight);
}


class Graph {
private:
    dynamicArray<Node*>* nodes = new dynamicArray<Node*>();
    dynamicArray<Edge*>* edges = new dynamicArray<Edge*>();
    int size;

public:
    Graph() {
        size = 0;
    }
    Edge** getArray() {
        return edges->getArray();
    }
    int getSize() {
        return size;
    }
    void addNewNode(double x, double y) {
        Node* newPair = new Node(x, y);
        nodes->add(newPair);
    }

    void addNewEdge(int x, int y, double weight) {
        Edge* newEdge = new Edge(x, y, weight);
        edges->add(newEdge);
        size++;
    }
};

class UnionFind {
    int size;
    int* parent;
    int* rank;
public:
    UnionFind(int n) {
        size = n;
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }
    int find(int i) {
        if (i == parent[i])
            return i;
        return find(parent[i]);
    }
    /*int compression_find(int i) {
        if (i == parent[i])
            return i;

        int root = find(parent[i]);
        if (root != parent[i])
            parent[i] = root;
        return root;
    }*/
    int compression_find(int i) {
        if (i == parent[i])
            return i;

        int root = find(parent[i]);
        if (root != parent[i])
            parent[i] = root;
        return root;
    } // Do przerowbienia jak na kurewskiej wikipedii

    void common_union(int index1, int index2) {
        int xRoot = compression_find(index1);
        int yRoot = compression_find(index2);

        if (xRoot != yRoot) {
            parent[xRoot] = yRoot;
        }
    }
    /*void union_by_rank(int index1, int index2) {
        if (index1 == index2) {
            return;
        }

        if (rank[index1] < rank[index2]) {
            parent[index1] = index2;
        }
        else if (rank[index1] > rank[index2]) {
            parent[index2] = index1;
        }
        else if (rank[index1] == rank[index2]) {
            parent[index2] = index1;
            rank[index1]++;
        }
    }*/
    void union_by_rank(int index1, int index2) {
        int xRoot = compression_find(index1);
        int yRoot = compression_find(index2);

        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        }
        else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        }
        else if (xRoot != yRoot) {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }


    void show() {
        for (int i = 0; i < size; i++) {
            std::cout << i << " " << find(i) << " " << rank[i] << std::endl;
        }
    }
};

template<typename T>
void bucketSort(T* array, int n, double m, double(*key)(T), int(*data_cmp)(T, T)) {
    //double w = m / (double)n;
    List<T>* newArray = new List<T>[n];


    for (int i = 0; i < n; i++) {
        //std::cout << key(array[i]) << std::endl;
        int bi = n * key(array[i]);
        newArray[bi].add_order(array[i], data_cmp);
    }

    //for (int i = 0; i < n; i++) {
    //    //const int index = floor(key(array[i]) / w);
    //    const int index = key(array[i]) / w;
    //    newArray[index].add_order(array[i], data_cmp);
    //}

    int index = 0;
    for (int i = 0; i < n; i++) {
        const int tempSize = newArray[i].getSize();
        if (tempSize == 0)
            continue;
        ListNode<T>* temp = newArray[i].getHead();
        if (tempSize == 1)
            array[index++] = temp->value;
        else
            for (int j = 0; j < tempSize; j++) {
                array[index++] = temp->value;
                temp = temp->next;
            }
    }

    delete[] newArray;
}

void Kruskal(Graph* graph){
    int gSize = graph->getSize();
    UnionFind* uf = new UnionFind(gSize);
    dynamicArray<Edge*>* mst = new dynamicArray<Edge*>();

    Edge** tempEdge = graph->getArray();
    bucketSort<Edge*>(tempEdge, gSize, 1.0, edge_key, edge_cmp);

    /*for (int i = 0; i < gSize; i++) {
        if (uf->find(tempEdge[i]->x) != uf->find(tempEdge[i]->y)) {
            uf->common_union(tempEdge[i]->x, tempEdge[i]->y);
            mst->add(tempEdge[i]);
        }
    }*/
    for (int i = 0; i < gSize; i++) {
        if (uf->find(tempEdge[i]->x) != uf->find(tempEdge[i]->y)) {
            uf->union_by_rank(tempEdge[i]->x, tempEdge[i]->y);
            mst->add(tempEdge[i]);
        }
    }
    std::cout << mst->getSize() << std::endl;
    std::cout << mst->to_string(edge_to_str) << std::endl;
}


void readFromFile(Graph* graph, std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::in);

    
    if (file.is_open())
    {
        std::string temp;
        getline(file, temp);
        int n = std::stoi(temp);

        double x, y;
        char c;
        for(int i = 0; i < n; i++) {
            getline(file, temp);
            std::istringstream output(temp);
            output >> x;
            output >> c;
            output >> y;
            //std::cout << x << " " << y << std::endl;
            graph->addNewNode(x, y);
        }

        getline(file, temp);
        n = std::stoi(temp);

        int i1, i2;
        double weight;
        char c1, c2;


        int pos = 0;
        for (int i = 0; i < n; i++) {
            getline(file, temp);

            pos = temp.find(" ");
            i1 = std::stoi(temp.substr(0, pos));
            temp.erase(0, pos + 1);
            pos = temp.find(" ");
            i2 = std::stoi(temp.substr(0, pos));
            temp.erase(0, pos + 1);
            pos = temp.find(" ");
            weight = std::stod(temp.substr(0, pos));
            temp.erase(0, pos + 1);

            //::cout << i1 << " " << i2 << " " << weight << std::endl;
            graph->addNewEdge(i1, i2, weight);
            pos = 0;
        }

        file.close();
    }
}

    
int main()
{
    Graph* graph1 = new Graph();
    readFromFile(graph1, "g1.txt");
    Kruskal(graph1);


    /*graph->add(1, 5, 1);
    graph->add(3, 4, 1);
    graph->add(2, 5, 2);
    graph->add(3, 5, 3);
    graph->add(0, 5, 4);
    graph->add(2, 3, 4);
    graph->add(0, 6, 5);
    graph->add(1, 2, 6);
    graph->add(3, 6, 8);*/



    return 0;
}