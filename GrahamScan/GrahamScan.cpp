#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h>
#include <fstream>
#include "List.h"
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
    Point* operator- (Point* p2) { 
        Point* temp;
        temp->x = x - p2->x;
        temp->y = y - p2->y;
        return temp;
    };
};

double cmp(Point* p1, Point* p2) {
    return p2->x * p1->y - p1->x * p2->y;
}

Point* findMin(List<Point*>* points) {
    Point* minPoint;

    ListNode<Point*>*temp_object = points->getHead();
    minPoint = temp_object->value;

    for (int i = 1; i < points->getSize(); i++) {
        if (minPoint->y < temp_object->value->y) {
            minPoint = temp_object->value;
        }
        else if (minPoint->y = temp_object->value->y) {
            if (minPoint->x < temp_object->value->x) {
                minPoint = temp_object->value;
            }
        }
        temp_object = temp_object->next;
    }

    return minPoint;
}

List<int> grahamScan(List<Point*>* points) {
    List<Point*>* pointscp = new List<Point*>();
    Point* minPoint;
    List<Point*>* CH = new List<Point*>();

    ListNode<Point*>* temp_object = points->getHead();
    for (int i = 0; i < points->getSize(); i++) {
        pointscp->add(temp_object->value);
        temp_object = temp_object->next;
    }

    minPoint = findMin(pointscp);
    CH->add(minPoint);

    return;
}


void readFromFile(List<Point*>* points, std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::in);


    if (file.is_open())
    {
        std::string temp;
        getline(file, temp);
        int n = std::stoi(temp);

        double x, y;
        char c;
        for (int i = 0; i < n; i++) {
            getline(file, temp);
            std::istringstream output(temp);
            output >> x;
            output >> c;
            output >> y;

            Point* newPoint = new Point(x, y);
            points->add(newPoint);
        }

        file.close();
    }
}

int main()
{
    List<Point*>* points = new List<Point*>();
    readFromFile(points, "points1.txt");
    
    return 0;
}