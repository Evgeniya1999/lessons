#ifndef QUICKSORT_H
#define QUICKSORT_H
#include<vector>

using namespace std;

int partition(vector<int>& arr, int left, int right);
void QSort(vector<int>& arr, int left, int right);
void QSort(vector<int>& arr);

#endif // QUICKSORT_H
