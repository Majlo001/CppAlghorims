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
	double w = m / (double) n;
	//const int w = std::max(m / n, 1);
	List<int>* newArray = new List<int>[n];


	for (int i = 0; i < n; i++) {
		const int index = array[i] / w;
		newArray[index].add_order(array[i]);
	}

	int index = 0;
	for (int i = 0; i < n; i++) {
		const int tempSize = newArray[i].getSize();
		if (tempSize == 0)
			continue;
		ListNode<int>* temp = newArray[i].getHead();
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


template<typename T>
void bucketSort(T* array, int n, double m, int(*key)(T), int(*data_cmp)(T, T)) {
	double w = m / (double) n;
	List<T>* newArray = new List<T>[n];

	for (int i = 0; i < n; i++) {
		//const int index = floor(key(array[i]) / w);
		//const int index = key(array[i]) / w;
		const int index = array[i]->pesel / w;
		newArray[index].add_order(array[i], data_cmp);
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

template<typename T>
std::string array_to_string(T* array, int n, int max, std::string(*data_to_str)(T)) {
	std::ostringstream temp;
	if (n < max) {
		max = n;
	}

	for (int i=0; i < max; i++) {
		temp << data_to_str(array[i]) + "\n";
	}

	return temp.str();
}



void main_ints()
{
	srand(0);
	const int MAX_ORDER = 7;
	const int m = (int)pow(10, 7);
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = (int)pow(10, o);
		int* array1 = new int[n];
		for (int i = 0; i < n; i++)
		{
			int rand_val = ((rand() << 15) + rand()) % m;
			array1[i] = rand_val;
		}
		std::cout << "Sortowanie 10^" << o << " liczb" << std::endl;
		//std::cout << array_to_string(array1, n, 10, not_str) << std::endl;


		int* array2 = new int[n];
		int* array3 = new int[n];
		memcpy(array2, array1, n * sizeof(int));
		memcpy(array3, array1, n * sizeof(int));

		//sortowanie przez zliczanie ( do wykonania w miejscu )
		clock_t t1 = clock();
		countingSort(array1, n, m);
		clock_t t2 = clock();

		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Counting Sort: " << time << "s" << std::endl;
		std::cout << "Czas na jeden element: " << (time / n) * 1000 * 1000 * 1000 << " ns" << std::endl;
		std::cout << array_to_string(array1, n, 10, not_str) << std::endl;
		
		t1 = clock();	// sortowanie przez kopcowanie ( do wykonania w miejscu )
		BinaryHeap<int>* bh = new BinaryHeap<int>(array2, n, normal_cmp, true);
		bh->sort(normal_cmp);
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Heapsort: " << time << "s" << std::endl;
		std::cout << "Czas na jeden element: " << (time / n) * 1000 * 1000 * 1000 << " ns" << std::endl;
		std::cout << array_to_string(array2, n, 10, not_str) << std::endl;


		// sortowanie kubelkowe ( do wykonania w miejscu )
		t1 = clock();
		bucketSort(array3, n, m);
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Bucket Sort: " << time << "s" << std::endl;
		std::cout << "Czas na jeden element: " << (time / n) * 1000 * 1000 * 1000 << " ns" << std::endl;
		std::cout << array_to_string(array3, n, 10, not_str) << std::endl;


		bool s1 = arraysEqual(array1, array2, n, normal_cmp);
		bool s2 = arraysEqual(array2, array3, n, normal_cmp);
		std::cout << "Porownanie: " << s1 << " " << s2 << std::endl;


		std::cout << std::endl;

		delete[] array1;
		delete[] array2;
		delete[] array3;
	}
}

void main_some_objects() {
	const int MAX_ORDER = 7;
	const double m_double = (double)pow(2, 30);

	for (int o = 1; o <= MAX_ORDER; o++) {
		const int n = (int)pow(10, o);
		Person** array1 = new Person * [n];
		for (int i = 0; i < n; i++)
		{
			double pesel = ((rand() << 15) + rand()) / m_double;
			Person* so = new Person(pesel, "Adam", "Adamiak", i);
			array1[i] = so;
		}
		std::cout << "Sortowanie 10^" << o << " liczb" << std::endl;
		//std::cout << array_to_string(array1, n, 10, person_to_str) << std::endl;


		Person** array2 = new Person * [n];
		memcpy(array2, array1, n * sizeof(Person*));

		// sortowanie przez kopcowanie
		clock_t t1 = clock();
		BinaryHeap<Person*>* bh = new BinaryHeap<Person*>(array1, n, person_cmp, true);
		bh->sort(person_cmp);
		clock_t t2 = clock();
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Heapsort: " << time << "s" << std::endl;
		std::cout << "Czas na jeden element: " << (time / n) * 1000 * 1000 * 1000 << " ns" << std::endl;
		std::cout << array_to_string(array1, n, 10, person_to_str) << std::endl;
		//std::cout << bh->to_string(person_to_str, 15) << std::endl;


		// sortowanie kubelkowe ( do wykonania w miejscu )
		t1 = clock();
		bucketSort<Person*>(array2, n, 1.0, person_key_double, person_cmp);
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Bucket Sort: " << time << "s" << std::endl;
		std::cout << "Czas na jeden element: " << (time / n) * 1000 * 1000 * 1000 << " ns" << std::endl;
		std::cout << array_to_string(array2, n, 10, person_to_str) << std::endl;


		bool s1 = arraysEqual(array1, array2, n, person_cmp);
		std::cout << "Porownanie: " << s1 << std::endl;
		std::cout << std::endl;
		delete[] array1;
		delete[] array2;
	}
}

int main()
{
	//main_ints();
	main_some_objects();
	return 0;
}
