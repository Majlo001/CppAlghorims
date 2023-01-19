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

    Point** points_copy = new Point*[n - 1];
    int k = 0;
    for (int i = 0; i < n; i++, k++) {
        Point* pcp = new Point(points[i]->x, points[i]->y, i);
        pcp->x = pcp->x - points[minPoint]->x;
        pcp->y = pcp->y - points[minPoint]->y;
        if (i == minPoint)
        {
            k--;
            continue;
        }
        points_copy[k] = pcp;
    }

    clock_t t1 = clock();
    BinaryHeap<Point*>* bh = new BinaryHeap<Point*>(points_copy, n-1, point_cmp, true);
    bh->sort(point_cmp);
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "Czas obliczen sortowania: " << time * 1000 << " ms" << std::endl;

    //std::cout << bh->to_string(point_to_str) << std::endl;
    /*for (int i = 0; i < n; i++) {
        points_copy[i]->x = points_copy[i]->x + points[minPoint]->x;
        points_copy[i]->y = points_copy[i]->y + points[minPoint]->y;
        std::cout << points_copy[i]->x << " " << points_copy[i]->y << std::endl;
    }*/



    t1 = clock();
    CH->add(minPoint);
    CH->add(points_copy[0]->id);

    for (int i = 1; i < n - 1; i++) {
        CH->add(points_copy[i]->id);

        while (cmp((*points[CH->getTail()->prev->value] - *points[CH->getTail()->prev->prev->value]), (*points[CH->getTail()->value] - *points[CH->getTail()->prev->value])) > 0) {
            CH->del_2tolast();
        }
    }
    t2 = clock();
    time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << "Czas obliczen glownej petli: " << time * 1000 << " ms" << std::endl;


    delete bh;
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
        points = new Point * [n];

        double x, y;
        std::string delimiter = " ";
        std::string token;
        
        for (int i = 0; i < n; i++) {
            getline(file, temp);

            int pos = 0;
            pos = temp.find(delimiter);
            token = temp.substr(0, pos);
            x = std::stod(token);
            temp.erase(0, pos + delimiter.length());

            pos = temp.find(delimiter);
            token = temp.substr(0, pos);
            y = std::stod(token);
            temp.erase(0, pos + delimiter.length());

            //std::cout << i << ": " << x << " " << y << std::endl;
            Point* newPoint = new Point(x, y);
            points[i] = newPoint;
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
    List<int>* CH;
    int n;


    std::cout << "Points 1" << std::endl;
    n = getN("points1.txt");
    std::cout << "Liczba punktow: "<< n << std::endl;
    points = readFromFile(points, "points1.txt");
    CH = grahamScan(points, n);
    std::cout << CH->getSize() << std::endl;
    std::cout << CH->to_string() << std::endl << std::endl << std::endl;
    CH->del_all();


    std::cout << "Points 2" << std::endl;
    n = getN("points2.txt");
    std::cout << "Liczba punktow: " << n << std::endl;
    points = readFromFile(points, "points2.txt");
    CH = grahamScan(points, n);
    std::cout << CH->getSize() << std::endl;
    std::cout << CH->to_string() << std::endl << std::endl << std::endl;
    CH->del_all();


    std::cout << "Points 3" << std::endl;
    n = getN("points3.txt");
    std::cout << "Liczba punktow: " << n << std::endl;
    points = readFromFile(points, "points3.txt");
    CH = grahamScan(points, n);
    std::cout << CH->getSize() << std::endl;
    std::cout << CH->to_string() << std::endl << std::endl << std::endl;
    CH->del_all();


    std::cout << "Points 4" << std::endl;
    n = getN("points4.txt");
    std::cout << "Liczba punktow: " << n << std::endl;
    points = readFromFile(points, "points4.txt");
    CH = grahamScan(points, n);
    std::cout << CH->getSize() << std::endl;
    std::cout << CH->to_string() << std::endl << std::endl << std::endl;
    CH->del_all();


    std::cout << "Points 5" << std::endl;
    n = getN("points5.txt");
    std::cout << "Liczba punktow: " << n << std::endl;
    points = readFromFile(points, "points5.txt");
    CH = grahamScan(points, n);
    std::cout << CH->getSize() << std::endl;
    std::cout << CH->to_string() << std::endl << std::endl << std::endl;
    CH->del_all();
    

    delete CH;
    delete[] points;
    return 0;
}
