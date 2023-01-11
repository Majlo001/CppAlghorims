#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h>
#include <fstream>
#include "List.h"
#include "DynamicArray.h"

int findCounter = 0;
void resetFindCounter() {
    findCounter = 0;
}

class Node {
public:
    double x, y;
    Node(double x, double y) {
        this->x = x;
        this->y = y;
    }
    ~Node() {
        x = 0.0;
        y = 0.0;
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
    Edge() {
        x = 0;
        y = 0;
        weight = 0.0;
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
    ~Graph() {
        size = 0;
        nodes->clear();
        edges->clear();
        delete nodes;
        delete edges;
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
    ~UnionFind() {
        size = 0;
        delete parent;
        delete rank;
    }
    int find(int i) {
        findCounter++;
        if (i == parent[i])
            return i;
        return find(parent[i]);
    }
    int compression_find(int i) {
        findCounter++;
        if (i == parent[i])
            return i;

        int root = find(parent[i]);
        if (root != parent[i])
            parent[i] = root;
        return root;
    }
    void common_union(int index1, int index2) {

        if (index1 != index2) {
            parent[index1] = index2;
        }
    }
    void union_by_rank(int index1, int index2) {

        if (rank[index1] < rank[index2]) {
            parent[index1] = index2;
        }
        else if (rank[index1] > rank[index2]) {
            parent[index2] = index1;
        }
        else if (index1 != index2) {
            parent[index2] = index1;
            rank[index1]++;
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
    List<T>* newArray = new List<T>[n];


    for (int i = 0; i < n; i++) {
        int bi = n * key(array[i]);
        newArray[bi].add_order(array[i], data_cmp);
    }

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

dynamicArray<Edge*>* Kruskal(Graph* graph){
    int gSize = graph->getSize();
    UnionFind* uf = new UnionFind(gSize);
    dynamicArray<Edge*>* mst = new dynamicArray<Edge*>();

    Edge** tempEdge = graph->getArray();
    double max_time_per_element = 0.0;

    std::cout << "Zwykly Kruskall: " << std::endl;
    clock_t t1 = clock();
    bucketSort<Edge*>(tempEdge, gSize, 1.0, edge_key, edge_cmp);
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "Czas sortowania: " << time * 1000 << " ms" << std::endl;

    t1 = clock();
    for (int i = 0; i < gSize; i++) {
        if (uf->find(tempEdge[i]->x) != uf->find(tempEdge[i]->y)) {
            uf->common_union(tempEdge[i]->x, tempEdge[i]->y);
            mst->add(tempEdge[i]);
        }
    }
    t2 = clock();
    time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "Czas obliczen glownej petli: " << time * 1000 << " ms" << std::endl;

    //std::cout << mst->to_string(edge_to_str) << std::endl;

    delete uf;
    return mst;
}

dynamicArray<Edge*>* BetterKruskal(Graph* graph) {
    int gSize = graph->getSize();
    UnionFind* uf = new UnionFind(gSize);
    dynamicArray<Edge*>* mst = new dynamicArray<Edge*>();

    Edge** tempEdge = graph->getArray();
    double max_time_per_element = 0.0;
    double weightCount = 0.0;

    std::cout << "Lepszy Kruskall: " << std::endl;
    /*clock_t t1 = clock();
    bucketSort<Edge*>(tempEdge, gSize, 1.0, edge_key, edge_cmp);
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "Czas sortowania: " << time * 1000 << " ms" << std::endl;*/

    clock_t t1 = clock();
    for (int i = 0; i < gSize; i++) {
        if (uf->compression_find(tempEdge[i]->x) != uf->compression_find(tempEdge[i]->y)) {
            uf->union_by_rank(tempEdge[i]->x, tempEdge[i]->y);
            mst->add(tempEdge[i]);
        }
    }
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "Czas obliczen glownej petli: " << time * 1000 << " ms" << std::endl;

    for (int i = 0; i < mst->getSize(); i++) {
        weightCount += mst->get_index(i)->weight;
    }
    std::cout << "Krawedzie: " << mst->getSize() + 1 << " suma wag: " << weightCount << std::endl;

    //std::cout << mst->to_string(edge_to_str) << std::endl;

    delete uf;
    return mst;
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

            graph->addNewEdge(i1, i2, weight);
            pos = 0;
        }

        file.close();
    }
}

    
int main()
{
    dynamicArray<Edge*>* mst;

    std::cout << "g1.txt" << std::endl;
    Graph* graph1 = new Graph();
    readFromFile(graph1, "g1.txt");
    mst = Kruskal(graph1);
    std::cout << "Liczba wykonan findow: " << findCounter << std::endl << std::endl;
    resetFindCounter();
    mst = BetterKruskal(graph1);
    std::cout << "Liczba wykonan findow: " << findCounter << std::endl << std::endl;
    resetFindCounter();
    //std::cout << mst->to_string(edge_to_str) << std::endl;


    std::cout << "g2.txt" << std::endl;
    Graph* graph2 = new Graph();
    readFromFile(graph2, "g2.txt");
    mst = Kruskal(graph2);
    std::cout << "Liczba wykonan findow: " << findCounter << std::endl << std::endl;
    resetFindCounter();
    mst = BetterKruskal(graph2);
    std::cout << "Liczba wykonan findow: " << findCounter << std::endl << std::endl;
    resetFindCounter();
    //std::cout << mst->to_string(edge_to_str) << std::endl;


    std::cout << "g3.txt" << std::endl;
    Graph* graph3 = new Graph();
    readFromFile(graph3, "g3.txt");
    mst = Kruskal(graph3);
    std::cout << "Liczba wykonan findow: " << findCounter << std::endl << std::endl;
    resetFindCounter();
    mst = BetterKruskal(graph3);
    std::cout << "Liczba wykonan findow: " << findCounter << std::endl << std::endl;
    resetFindCounter();
    //std::cout << mst->to_string(edge_to_str) << std::endl;

    delete graph1;
    delete graph2;
    delete graph3;
    delete mst;
    return 0;
}
