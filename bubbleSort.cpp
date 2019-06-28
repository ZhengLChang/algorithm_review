#include <iostream>
#include <vector>
using namespace std;
/**
  时间复杂度 n^2
  */

void bubbleSort(vector<int> &arr, int len){
	int temp = 0;
	int i = 0, j = 0;
	for(i = 0; i < len; i++){
		for(j = 0; j < len - i - 1; j++){
			if(arr[j] > arr[j + 1]){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main(void){
	vector<int> arr = {11, 2, 3, 8, 7, 10};
	int i = 0;
	bubbleSort(arr, arr.size());
	for(i = 0; i < arr.size(); i++){
		cout << arr[i] << "\t";
	}
	cout << endl;
	return 0;
}

/*
#include <stdio.h>

void bubbleSort(int arr[], int len){
	int temp = 0;
	int i = 0, j = 0;
	for(i = 0; i < len; i++){
		for(j = 0; j < len - i; j++){
			if(arr[j] > arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main(void){
	int arr[] = {11, 2, 3, 8, 7, 10};
	int i = 0;
	bubbleSort(arr, sizeof(arr) / sizeof(arr[0]) - 1);
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); i++){
		fprintf(stderr, "%d\t", arr[i]);
	}
	fprintf(stderr, "\n");

	return 0;
}
*/
