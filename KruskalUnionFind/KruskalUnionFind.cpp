#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h> 
#include "List.h"


template<class T>
class Node {
public:
    T x, y;
    Node(T x, T y) {
        this->x = x;
        this->y = y;
    }
};

template<class T, class K>
class Edge {
public:
    Node<T>* pair;
    int x;
    int y;
    K weight;
    Edge(Node<T>* pair, K weight) {
        this->pair = pair;
        this->weight = weight;
        x = pair->x;
        y = pair->y;
    }
};

int edge_cmp(Edge<int, int> e1, Edge<int, int> e2) {
    if (e1.weight == e2.weight) return 0;
    else if (e1.weight < e2.weight) return -1;
    else return 1;
}
int edge_cmp(Edge<int, int>* e1, Edge<int, int>* e2) {
    if (e1->weight == e2->weight) return 0;
    else if (e1->weight < e2->weight) return -1;
    else return 1;
}

template<class T, class K>
class Graph {
private:
    List<Edge<T, K>*>* edges = new List<Edge<T, K>*>();
    int size;

public:
    Graph() {
        size = 0;
    }
    List<Edge<T, K>*>* getEdges() {
        return edges;
    }
    int getSize() {
        return size;
    }

    void add(T x, T y, K weight) {
        Node<T>* newPair = new Node<T>(x, y);
        Edge<T, K>* newEdge = new Edge<T, K>(newPair, weight);
        edges->add(newEdge);
        //edges->add_order(newEdge, edge_cmp);
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

    void common_union(int index1, int index2) {
        parent[index1] = index2;
    }
    void union_by_rank(int index1, int index2) {
        if (rank[index1] < rank[index2]) {
            parent[index1] = index2;
        }
        else if (rank[index1] > rank[index2]) {
            parent[index2] = index1;
        }
        else {
            parent[index2] = index1;
            rank[index1]++;
        }
    }

    int find(int i) {
        if (i == parent[i])
            return i;
        return find(parent[i]);
    }
    int compression_find(int i) {
        if (i == parent[i])
            return i;

        int root = find(parent[i]);
        if (root != parent[i])
            parent[i] = root;
        return root;
    }

    void show() {
        for (int i = 0; i < size; i++) {
            std::cout << i << " " << find(i) << " " << rank[i] << std::endl;
        }
    }
};

void Kruskal(Graph<int, int>* graph){
    //int gSize = graph->getSize();
    int gSize = 7;
    UnionFind* uf = new UnionFind(gSize);

    ListNode<Edge<int, int>*>* temp = graph->getEdges()->getHead();
    //Sortowanko here

    for (int i = 0; i < gSize; i++) {
        if (uf->find(temp->value->x) != uf->find(temp->value->y)) {
            uf->union_by_rank(temp->value->x, temp->value->y);
            std::cout << i <<" if" << std::endl;
        }

        temp = temp->next;
    }
    uf->show();
}


    
int main()
{
    Graph<int, int>* graph = new Graph<int, int>();
    graph->add(1, 5, 1);
    graph->add(3, 4, 1);
    graph->add(2, 5, 2);
    graph->add(3, 5, 3);
    graph->add(0, 5, 4);
    graph->add(2, 3, 4);
    graph->add(0, 6, 5);
    graph->add(1, 2, 6);
    graph->add(3, 6, 8);

    Kruskal(graph);

    return 0;
}