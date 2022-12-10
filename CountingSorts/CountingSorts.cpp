#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h> 
#include "BinaryHeap.h"
#include "List.h"



void countingSort(int* array, int n, const int m) {
	int* countsArray = new int[m];
	for (int i = 0; i < m; i++) {
		countsArray[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		countsArray[array[i]]++; 
	}
	int temp = 0;
	for (int i = 0; i < m; i++) {
		if (countsArray[i] != 0) {
			for (int j = 0; j < countsArray[i]; j++) {
				array[temp] = i;
				temp++;
			}
		}
	}

	delete[] countsArray;
}

void bucketSort(int* array, int n, const int m) {
	int w = m / n;
	List<int>* newArray = new List<int>[w];

	for (int i = 0; i < w; i++) {
		List<int>* list = new List<int>();
		newArray[i] = *list;
	}

	for (int i = 0; i < n; i++) {
		int index = floor(array[i] / w);
		newArray[index].add_order(array[i]);
	}
}



int main()
{
	srand(0);
	const int MAX_ORDER = 7;
	const int m = (int)pow(10, 7);


	const int n = (int)pow(10, 3);
	int* array1 = new int[n];

	for (int i = 0; i < n; i++) {
		//int rand_val = (rand() << 15) + rand();
		int rand_val = rand();
		array1[i] = rand_val;
	}

	int* array2 = new int[n];
	int* array3 = new int[n];
	memcpy(array2, array1, n * sizeof(int));
	memcpy(array3, array1, n * sizeof(int));

	clock_t t1 = clock();
	countingSort(array1, n, m);
	clock_t t2 = clock();


	BinaryHeap<int>* bh = new BinaryHeap<int>(array2, n, normal_cmp, true);
	//bh->sort(normal_cmp);
	std::cout << bh->to_string(not_str, 15) << std::endl;

	t1 = clock();
	bucketSort(array3, n, m);
	t2 = clock();



	delete[] array1;
	delete[] array2;
	delete[] array3;
	return 0;
}