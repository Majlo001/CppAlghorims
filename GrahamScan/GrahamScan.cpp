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
    Point() {
        x = 0.0;
        y = 0.0;
    }
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Point(const Point& point){
        x = point.x;
        y = point.y;
    }
    ~Point() {
        x = 0.0;
        y = 0.0;
    }
    Point operator- (Point p2) {
        Point temp;
        temp.x = x - p2.x;
        temp.y = y - p2.y;
        return temp;
    };
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
    if (temp == 0) return 0;
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
        Point* pcp = new Point(points[i]->x, points[i]->y);
        pcp->x = pcp->x - points[minPoint]->x;
        pcp->y = pcp->y - points[minPoint]->y;
        points_copy[i] = pcp;
    }

    /*Point* tmpPoint = points[0];
    points[0] = points[minPoint];
    points[minPoint] = tmpPoint;*/
    std::cout << points[0]->x << " " << points[0]->y << std::endl;
    std::cout << points_copy[0]->x << " " << points_copy[0]->y << std::endl;


    //Sortowanko here
    BinaryHeap<Point*>* bh = new BinaryHeap<Point*>(points_copy, n, point_cmp, true);
    bh->sort(point_cmp);
    std::cout << std::endl << std::endl << "BH:" << std::endl;
    std::cout << bh->to_string(point_to_str) << std::endl;


    CH->add(0);
    CH->add(1);

    for (int i = 2; i < n; i++) {
        if (minPoint != i) {
            CH->add(i);

            while (cmp((*points_copy[CH->getTail()->prev->value] - *points_copy[CH->getTail()->prev->prev->value]), (*points_copy[CH->getTail()->value] - *points_copy[CH->getTail()->prev->value])) > 0) {
                CH->del_2tolast();

                if (CH->getSize() < 3)
                    break;
            }
        }
    }
    CH->add_order(minPoint-1);


    for (int i = 0; i < n; i++) {
        points_copy[i]->x = points_copy[i]->x + points[minPoint]->x;
        points_copy[i]->y = points_copy[i]->y + points[minPoint]->y;
    }
    ListNode<int>* temp = CH->getHead();
    for (int i = 0; i < CH->getSize(); i++) {
        std::cout << points_copy[temp->value]->x << " " << points_copy[temp->value]->y << std::endl;
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
            //points->add(newPoint);
            points[i] = newPoint;
            std::cout << points[i]->x << " " << points[i]->y << std::endl;
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
    //int n = getN("points1.txt");
    int n = getN("test2.txt");
    List<int>* CH;

    //points = readFromFile(points, "points1.txt");
    points = readFromFile(points, "test2.txt");
    CH = grahamScan(points, n);
    std::cout << CH->to_string() << std::endl;
    
    return 0;
}