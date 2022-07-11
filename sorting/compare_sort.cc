#include "compare_sort.h"

namespace ZP {

void swap (int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

int* insertionSort (int *arr, int len) {
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0 && arr[j] < arr[j-1]; --j) {
            swap(arr[j], arr[j-1]);
        }
    }
    return arr;
}

int* bubbleSort (int *arr, int len) {
    for (int i = 0; i < len-1; ++i) {
        for (int j = 0; j < len-1-i; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    return arr;
}

int* selectionSort (int *arr, int len) {
    int selectedIndex;
    for (int i = 0; i < len-1; ++i) {
        selectedIndex = i;
        for (int j = i+1; j < len; ++j) {
            if (arr[j] < arr[selectedIndex]) {
                selectedIndex = j;
            }
        }
        if (selectedIndex != i) {
            swap(arr[i], arr[selectedIndex]);
        }
    }
    return arr;
}

int* mergeSortedArray (int *arr1, int sz1, int *arr2, int sz2) {
    int* mergedArray = new int[sz1+sz2];
    int count1 = 0, count2 = 0, i = 0;
    while (count1 < sz1 && count2 < sz2) {
        if (arr1[count1] <= arr2[count2]) {
            mergedArray[i++] = arr1[count1++];
        } else {
            mergedArray[i++] = arr2[count2++];
        }
    }
    for (; count1 < sz1; count1++) {
        mergedArray[i++] = arr1[count1];
    }
    for (; count2 < sz2; count2++) {
        mergedArray[i++] = arr2[count2];
    }
    return mergedArray;
}

int* mergeSort (int *arr, int size) {
    if (size < 2) {
        return arr;
    }
    int* left = mergeSort(arr, size/2);
    int* right = mergeSort(arr+size/2, size-size/2);
    int* combined = mergeSortedArray(left, size/2, right, size-size/2);
    for (int i = 0; i < size; ++i) {
        arr[i] = combined[i];
    }
    delete [] combined;
    return arr;
}

void heapify (int* arr, int pos, int len) {
    if (pos < len) {
        int left = pos * 2 + 1, right = pos * 2 + 2, max = pos;
        if (left < len && arr[left] > arr[max]) {
            max = left;
        }
        if (right < len && arr[right] > arr[max]) {
            max = right;
        }
        if (max != pos) {
            swap(arr[max], arr[pos]);
            heapify(arr, max, len);
        }
    }
}

void buildHeap (int* arr, int len) {
    for (int i = len / 2; i >= 0; --i) {
        heapify(arr, i, len);
    }
}

int* heapSort (int* arr, int len) {
    for (int i = 0; i < len; ++i) {
        buildHeap(arr, len - i);
        int temp = arr[0];
        arr[0] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
    return arr;
}

int* quickSort (int *arr, int len) {
    if (len >= 2) {
        int piv = len - 1, i = 0, j = piv - 1;
        while (i < j) {
            for (; i <= j && arr[i] < arr[piv]; ++i) ;
            for (; j >= i && arr[j] >= arr[piv]; --j) ;
            if (i < j) {
                swap(arr[i], arr[j]);
                ++i; --j;
            }
        }
        if (arr[i] >= arr[piv]) {
            swap(arr[i], arr[piv]);
            piv = i;
        }
        quickSort(arr, piv);
        quickSort(arr+piv+1, len-piv-1);
    }
    return arr;
}

}
