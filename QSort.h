#ifndef QSORT_H
#define QSORT_H
// ============================================================================
// Nicholas Smith
// Quicksort
// qsort.cpp
// 14 February 2013
//
// Description: This program provides a classic quicksort implementation
// ============================================================================
#include <cstdlib>

// ====QuickSort============================================================
// Desc:	a standard implementation of the classic mergesort algorithm.
// Param 1:	a pointer to the array of integers to be sorted.
// Param 2: the first index of the array
// Param 3: the last index of the array
// Output:	parameter 1 now points to an array with the same values in non-decreasing
//			order.
// ============================================================================
template <typename T>
void MergeSort(T* arr, int s, int e)
{
	if(s >= e)
		return;
	int m = s + (e - s) / 2;
	MergeSort(arr, s, m);
	MergeSort(arr, m + 1, e);
	//Merge arrays
	int i = s, j = m + 1, n = e - s + 1;
	T* tmp = new T[n];
	for(int c = 0; c < n; ++c)
	{
		if(i <= m && (j > e || arr[i] <= arr[j]))
			tmp[c] = arr[i++];
		else
			tmp[c] = arr[j++];
	}
	for(int c = 0; c < n; ++c)
		arr[s + c] = tmp[c];
	delete [] tmp;
	return;
}

// ====Partition==============================================================
// Desc:	Hoare's Partition
// Param 1:	a pointer to the array of integers to be sorted.
// Param 2: the first index of the array
// Param 3: the last index of the array
// Output:	parameter 1 now points to an array with the same values in non-decreasing
//			order.
// ============================================================================
template <typename T>
int Partition(T* a, int l, int r)
{
	int i = l, j = r + 1, x;
	T p = a[(x = (rand() % (j - l)) + l)];		//Generate random number between l and r
	Swap(a[l], a[x]);
	do
	{
		do i++; while(a[i] < p && i <= r);
		do j--; while(a[j] > p);
		if(i < j)
			Swap(a[i], a[j]);
	} while(i < j);
	Swap(a[l], a[j]);
	return j;
}

// ====QuickSort============================================================
// Desc:	a standard implementation of the classic quick sort algorithm.
// Param 1:	a pointer to the array of integers to be sorted.
// Param 2: the first index of the array
// Param 3: the last index of the array
// Output:	parameter 1 now points to an array with the same values in non-decreasing
//			order.
// ============================================================================
template <typename T>
void QuickSort(T* a, int l, int r)
{
	if(l < r)
	{
		int s = Partition(a, l, r);
		QuickSort(a, l, s - 1);
		QuickSort(a, s + 1, r);
	}
}

// ====Swap====================================================================
// Desc:	swaps x and y
// Param 1:	x
// Param 2: y
// Output:	x and y are swapped
// ============================================================================
template <typename T>
void Swap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}
#endif
