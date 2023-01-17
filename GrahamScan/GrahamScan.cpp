#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h>
#include <fstream>
#include "List.h"
#include "HeapSort.h"


class Point {
public:
    double x, y;
    int id = 0;
    Point() {
        x = 0.0;
        y = 0.0;
        id = 0;
    }
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Point(double x, double y, int id) {
        this->x = x;
        this->y = y;
        this->id = id;
    }
    Point(const Point& point){
        x = point.x;
        y = point.y;
    }
    ~Point() {
        x = 0.0;
        y = 0.0;
        id = 0;
    }
    Point operator- (Point p2) {
        Point temp;
        temp.x = x - p2.x;
        temp.y = y - p2.y;
        return temp;
    };
    bool operator< (Point* p2) {
        return x < p2->x;
    }
};

double cmp(Point p1, Point p2) {
    return p2.x * p1.y - p1.x * p2.y;
}
double cmp(Point* p1, Point* p2) {
    return p2->x * p1->y - p1->x * p2->y;
}

int point_cmp(Point p1, Point p2) {
    double temp = p2.x * p1.y - p1.x * p2.y;
    if (temp == 0) return 0;
    else if (temp < 0) return -1;
    else return 1;
}
int point_cmp(Point* p1, Point* p2) {
    double temp = p2->x * p1->y - p1->x * p2->y;
    if (p1->x + p1->y == 0) return -1;
    if (p2->x + p2->y == 0) return 1;
    if (temp == 0) {
        if (p1 > p2) return 1;
        else if (p1 < p2) return -1;
        else return 0;
        return 0;
    }
    else if (temp < 0) return -1;
    else return 1;
}
std::string point_to_str(Point* p) {
    return std::to_string(p->x) + " " + std::to_string(p->y);
}
std::string point_to_str(Point p) {
    return std::to_string(p.x) + " " + std::to_string(p.y);
}


int findMin(Point** points, int n) {
    int minPoint = 0;

    for (int i = 1; i < n-1; i++) {
        if (points[minPoint]->y > points[i]->y) {
            minPoint = i;
        }
        else if (points[minPoint]->y == points[i]->y) {
            if (points[minPoint]->x > points[i]->x) {
                minPoint = i;
            }
        }
    }

    return minPoint;
}


List<int>* grahamScan(Point** points, int n) {
    List<int>* CH = new List<int>();
    int minPoint = findMin(points, n);

    Point** points_copy = new Point*[n];
    for (int i = 0; i < n; i++) {
        Point* pcp = new Point(points[i]->x, points[i]->y, i);
        pcp->x = pcp->x - points[minPoint]->x;
        pcp->y = pcp->y - points[minPoint]->y;
        points_copy[i] = pcp;
    }


    //Sortowanko here
    BinaryHeap<Point*>* bh = new BinaryHeap<Point*>(points_copy, n, point_cmp, true);
    bh->sort(point_cmp);
    //std::cout << std::endl << std::endl << "BH:" << std::endl;
    //std::cout << bh->to_string(point_to_str) << std::endl;

    /*for (int i = 0; i < n; i++) {
        points_copy[i]->x = points_copy[i]->x + points[minPoint]->x;
        points_copy[i]->y = points_copy[i]->y + points[minPoint]->y;
    }*/


    CH->add(points_copy[0]->id);
    CH->add(points_copy[1]->id);

    for (int i = 2; i < n; i++) {
            CH->add(points_copy[i]->id);

            while (cmp((*points[CH->getTail()->prev->value] - *points[CH->getTail()->prev->prev->value]), (*points[CH->getTail()->value] - *points[CH->getTail()->prev->value])) > 0) {
                CH->del_2tolast();

                if (CH->getSize() < 3)
                    break;
            }
    }


    ListNode<int>* temp = CH->getHead();
    for (int i = 0; i < CH->getSize(); i++) {
        //std::cout << points_copy[temp->value]->x << " " << points_copy[temp->value]->y << std::endl;
        temp = temp->next;
    }

    delete[] points_copy;
    return CH;
}



Point** readFromFile(Point** points, std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::in);


    if (file.is_open())
    {
        std::string temp;
        getline(file, temp);
        int n = std::stoi(temp);
        points = new Point*[n];

        double x, y;
        char c;
        for (int i = 0; i < n; i++) {
            getline(file, temp);
            std::istringstream output(temp);
            output >> x;
            output >> c;
            output >> y;

            Point* newPoint = new Point(x, y);
            points[i] = newPoint;
            //std::cout << points[i]->x << " " << points[i]->y << std::endl;
        }

        file.close();
        return points;
    }
}
int getN(std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::in);

    if (file.is_open())
    {
        std::string temp;
        getline(file, temp);
        int n = std::stoi(temp);

        file.close();
        return n;
    }
}

int main()
{
    Point** points = nullptr;
    int n = getN("points2.txt");
    //int n = getN("test2.txt");
    List<int>* CH;

    points = readFromFile(points, "points2.txt");
    //points = readFromFile(points, "test2.txt");
    CH = grahamScan(points, n);
    std::cout << CH->to_string() << std::endl;
    
    return 0;
}