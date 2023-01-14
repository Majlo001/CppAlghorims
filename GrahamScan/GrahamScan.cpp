#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h>
#include <fstream>
#include "List.h"
#include "HeapSort.h"
//#include "DynamicArray.h"


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

int point_cmp(Point* p1, Point* p2) {
    double temp = cmp(p1, p2);
    if (temp == 0) return 0;
    else if (temp < 0) return -1;
    else return 1;
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
    int minPoint;
    List<int>* CH = new List<int>();

    minPoint = findMin(points, n);
    Point* tmpPoint = points[0];
    points[0] = points[minPoint];
    points[minPoint] = tmpPoint;


    std::cout << points[0]->x << " " << points[0]->y << std::endl;

    //Sortowanko here
    //Jakoœ


    CH->add(0);
    CH->add(1);

    for (int i = 2; i < n; i++) {
        CH->add(i);


        while (cmp((*points[CH->getTail()->prev->value] - *points[CH->getTail()->prev->prev->value]) , (*points[CH->getTail()->value] - *points[CH->getTail()->prev->value])) > 0) {
            CH->del_2tolast();

            if (CH->getSize() < 3) 
                break;
        }
    }

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
    int n = getN("points1.txt");
    List<int>* CH;

    points = readFromFile(points, "points1.txt");
    CH = grahamScan(points, n);
    std::cout << CH->to_string() << std::endl;
    
    return 0;
}