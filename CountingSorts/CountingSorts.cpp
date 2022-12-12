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
	List<int>* newArray = new List<int>[n];

	for (int i = 0; i < n; i++) {
		List<int>* list = new List<int>();
		newArray[i] = *list;
	}
	for (int i = 0; i < n; i++) {
		int index = 0;
		if (w > 1) index = floor(array[i] / w);
		//std::cout << "Index " << i << ": " << array[i] << " " << index << std::endl;
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
		}
	}

	newArray->del_all();
	delete[] newArray;
}


template<typename T>
void bucketSort(T* array, int n, double m, int(*key)(T),int(*data_cmp)(T, T)) {
	double w = m / n;
	//std::cout << w << " " << n << " " << m << std::endl;
	List<T>* newArray = new List<T>[n];

	for (int i = 0; i < n; i++) {
		List<T>* list = new List<T>();
		newArray[i] = *list;
	}
	for (int i = 0; i < n; i++) {
		int index = floor(key(array[i]) / w);
		//std::cout << "Index " << i << ": " << array[i]->pesel << " " << index << std::endl;
		newArray[index].add_order(array[i], data_cmp);
	}

	if (w > 1) {
		int index = 0;
		for (int i = n - 1; i >= 0; i--) {
			//for (int i = 0; i < n; i++) {
			int tempSize = newArray[i].getSize();
			for (int j = 0; j < tempSize; j++) {
				array[index] = newArray[i].get();
				index++;
			}
		}
	}
	else {
		//for (int i = 0; i < n; i++) {
		for (int i = n - 1; i >= 0; i--) {
			array[i] = newArray[0].get();
			//std::cout << array[i]->pesel << std::endl;
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
			int rand_val = rand() % m;
			array1[i] = rand_val;
		}
		//[...] skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )

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
		//[...] wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		
		t1 = clock();	// sortowanie przez kopcowanie ( do wykonania w miejscu )
		BinaryHeap<int>* bh = new BinaryHeap<int>(array2, n, normal_cmp, true);
		bh->sort(normal_cmp);
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Heapsort: " << time << "s" << std::endl;


		// wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		// sortowanie kubelkowe ( do wykonania w miejscu )
		t1 = clock();
		bucketSort(array3, n, m);
		t2 = clock();

		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Bucket Sort: " << time << "s" << std::endl;
		// wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
		// sprawdzenie zgodnosci tablic array1 , array2 , array3 i wypis informacji o zgodnosci na
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

	/*for (int o = 1; o <= MAX_ORDER; o++){*/

	const int n = (int)pow(10, 2); // rozmiar tablicy z danymi
	Person** array1 = new Person*[n];
	for (int i = 0; i < n; i++)
	{
		double pesel = ((rand() << 15) + rand()) / m_double;
		Person* so = new Person(pesel, ('a' + rand() % 26), "Adamiak", i);
		array1[i] = so;
	}
	//[...] skrotowy wypis tablicy do posortowania ( np . pewna liczba poczatkowych elementow )
	Person** array2 = new Person*[n];
	memcpy(array2, array1, n * sizeof(Person*));

	// sortowanie przez kopcowanie
	clock_t t1 = clock();
	BinaryHeap<Person*>* bh = new BinaryHeap<Person*>(array1, n, person_cmp, true);
	bh->sort(person_cmp);
	clock_t t2 = clock();
	double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "Heapsort: " << time << "s" << std::endl;
	std::cout << bh->to_string(person_to_str, 15) << std::endl;
	// wypis pomiaru czasu i skrotowej postaci wynikowej tablicy
	

	// sortowanie kubelkowe ( do wykonania w miejscu )
	t1 = clock();
	bucketSort<Person*>(array2, n, 1.0, person_key_double, person_cmp);
	t2 = clock();

	time = (t2 - t1) / (double)CLOCKS_PER_SEC;
	std::cout << "Bucket Sort: " << time << "s" << std::endl;


	bool s1 = arraysEqual(array1, array2, n, person_cmp);
	std::cout << "Porownanie: " << s1 << std::endl;

	std::cout << std::endl;
}

int main()
{
	main_some_objects();
	//main_ints();
	return 0;
}