#include <windows.h>
#include <iostream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

//volatile double n;
//int save_index_big = 0;
//int save_index_small = 0;
double save_average = 0;

struct array {
	array(double* arr, double size) : arr(arr), size(size) {};
	double* arr;
	int min = 0;
	int max = 0;
	double average = 0;
	double count = 0;
	double size;
};

void min_max(array* ar) {
	const int min_max_sleep = 7;
	int max_ind = 0, min_ind = 0;
	for (int i = 0; i < ar->size; i++)
	{
		if (ar->arr[i] > ar->max)
		{
			ar->max = ar->arr[i];
			max_ind = i;
		}
		if (ar->arr[i] < ar->min)
		{
			ar->min = ar->arr[i];
			min_ind = i;
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(min_max_sleep));
	}
	ar->max = max_ind;
	ar->min = min_ind;
	std::cout << "the smallest element of the array = " << ar->min << std::endl;
	std::cout << "the biggest element of the array = " << ar->max << std::endl;
}

void average(array* ar) {
	const int average_sleep = 12;
	for (int i = 0; i < ar->size; i++)
	{
		ar->average = 0;
		ar->average += ar->arr[i];
		ar->count++;
		boost::this_thread::sleep_for(boost::chrono::milliseconds(average_sleep));
	}
	ar->average = ar->average / ar->count;
	save_average = ar->average;
	std::cout << "average = " << ar->average << std::endl;
}

int main()
{
	int size_array;
	std::cout << "size of array ";
	std::cin >> size_array;
	double* array1 = new double[size_array];
	std::cout << "enter the array elements " << std::endl;
	for (int i = 0; i < size_array; i++)
	{
		std::cin >> array1[i];
	}

	array* args = new array(array1, size_array);
	args->arr = array1;
	args->size = size_array;

	boost::thread min_maxT(min_max, args);
	boost::thread averageT(average, args);

	min_maxT.join();
	averageT.join();

	array1[args->min] = array1[args->max] = args->average;

	for (int i = 0; i < size_array; i++)
	{
		std::cout << array1[i] << " ";
	}
	return 0;
}