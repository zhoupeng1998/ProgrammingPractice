#include "linear_sort.h"

namespace ZP {

int* countingSort (int* arr, int len) {
    if (len == 0) {
        return arr;
    }
    int small = *arr, large = *arr;
    for (int i = 1; i < len; ++i) {
        if (arr[i] < small) {
            small = arr[i];
        } else if (arr[i] > large) {
            large = arr[i];
        }
    }
    int countSize = large - small + 1, pos = 0;
    int* count = new int[countSize];
    for (int i = 0; i < countSize; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < len; ++i) {
        count[arr[i] - small]++;
    }
    for (int i = 0; i < countSize; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            arr[pos++] = small + i;
        }
    }
    return arr;
}

int* radixSort (int* arr, int len, int digit) {
    if (len == 0 || digit == 0) {
        return arr;
    }
    int d = 1, radix = 1, *bucket[20];
    for (int i = 0; i < 20; ++i) {
        bucket[i] = new int[len + 1];
        bucket[i][0] = 0;
    }
    for (; d <= digit; ++d, radix *= 10) {
        for (int i = 0; i < len; ++i) {
            int digit = ((arr[i] - arr[i] % radix) / radix) % 10;
            if (digit <= 0) {
                digit = -digit + 10;
            }
            ++bucket[digit][0];
            bucket[digit][bucket[digit][0]] = arr[i];
        }
        int p = 0;
        for (int i = 19; i >= 10; --i) {
            for (int j = 1; j <= bucket[i][0]; ++j) {
                arr[p++] = bucket[i][j];
            }
            bucket[i][0] = 0;
        }
        for (int i = 0; i < 10; ++i) {
            for (int j = 1; j <= bucket[i][0]; ++j) {
                arr[p++] = bucket[i][j];
            }
            bucket[i][0] = 0;
        }
    }
    return arr;
}

}
