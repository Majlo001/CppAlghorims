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
	for (int i = m-1; i >= 0; i--) {
	//for (int i = 0; i < m; i++) {
		if (countsArray[i] != 0) {
			for (int j = 0; j < countsArray[i]; j++) {
				array[temp] = i;
				temp++;
			}
		}
	}
	//std::cout << std::endl << std::endl;
	/*for (int i = 0; i < n; i++) {
		std::cout << array[i] << std::endl;
	}*/

	delete[] countsArray;
}

void bucketSort(int* array, int n, const int m) {
	int w = m / n;
	//std::cout << w << " " << n << " " << m << std::endl;
	List<int>* newArray = new List<int>[w];

	for (int i = 0; i < w; i++) {
		List<int>* list = new List<int>();
		newArray[i] = *list;
	}
	for (int i = 0; i < n; i++) {
		int index = 0;
		if (w > 1) index = floor(array[i] / w);
		newArray[index].add_order(array[i]);
	}

	/*if (w > 1) {
		for (int i = 0; i < n; i++) {
			std::cout << newArray[i].to_string() << std::endl;
		}
	}
	else {
		std::cout << newArray[0].to_string() << std::endl;
	}*/
	if (w > 1) {
		int index = 0;
		for (int i = n-1; i >= 0; i--) {
		//for (int i = 0; i < n; i++) {
			int tempSize = newArray[i].getSize();
			for (int j = 0; j < tempSize; j++) {
				array[index] = newArray[i].get();
				index++;
			}
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			array[i] = newArray[0].get();
			//std::cout << array[i] << std::endl;
		}
	}


	newArray->del_all();
	delete[] newArray;
}

template<typename T>
bool arraysEqual(T* array1, T* array2, const int n, int(*data_cmp)(T, T)) {
	for (int i = 0; i < n; i++) {
		int cmp = data_cmp(array1[i], array2[i]);
		if (cmp != 0) {
			return false;
		}
	}
	return true;
}



int main()
{
	srand(0);
	const int MAX_ORDER = 7;
	const int m = (int)pow(10, 2);


	const int n = (int)pow(10, 1);
	int* array1 = new int[n];

	for (int i = 0; i < n; i++) {
		//int rand_val = (rand() << 15) + rand();
		int rand_val = rand() % 100;
		//std::cout << rand_val << std::endl;
		array1[i] = rand_val;
	}

	int* array2 = new int[n];
	int* array3 = new int[n];
	memcpy(array2, array1, n * sizeof(int));
	memcpy(array3, array1, n * sizeof(int));

	clock_t t1 = clock();
	countingSort(array1, n, m);
	clock_t t2 = clock();

	double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "Counting Sort: " << time << "s" << std::endl;


	t1 = clock();
	BinaryHeap<int>* bh = new BinaryHeap<int>(array2, n, normal_cmp, true);
	bh->sort(normal_cmp);
	t2 = clock();

	time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "Heapsort: " << time << "s" << std::endl;

	//std::cout << std::endl << "Heapsort:" << std::endl;
	//std::cout << bh->to_string(not_str, n) << std::endl;

	t1 = clock();
	bucketSort(array3, n, m);
	t2 = clock();

	time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "Bucket Sort: " << time << "s" << std::endl;

	/*std::cout << std::endl << "Bucket Sort:" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << array3[i] << std::endl;
	}*/

	bool s1 = arraysEqual<int>(array1, array2, n, normal_cmp);
	bool s2 = arraysEqual<int>(array2, array3, n, normal_cmp);
	std::cout << s1 << " " << s2 << std::endl;



	delete[] array1;
	delete[] array2;
	delete[] array3;
	return 0;
}