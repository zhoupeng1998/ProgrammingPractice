#ifndef COMPARE_SORT_H_
#define COMPARE_SORT_H_

namespace DSZP {

void swap (int& a, int& b);

int* mergeSortedArray (int* arr1, int sz1, int* arr2, int sz2);
void heapify (int* arr, int pos, int len);
void buildHeap (int* arr, int len);

int* insertionSort (int* arr, int len);
int* bubbleSort (int arr[], int len);
int* selectionSort (int* arr, int len);
int* mergeSort (int* arr, int size);
int* heapSort (int* arr, int len);
int* quickSort (int* arr, int len);

}

#endif
