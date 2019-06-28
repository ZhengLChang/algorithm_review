#include <iostream>
#include <vector>
#include <cstdio>
/**
  时间复杂度: logn
  */
int binarySearch(int arr[], int length, int target){
	int low = 0, high = length - 1, mid;
	while(low <= high){
		mid = low + ((high - low) >> 2);
		if(arr[mid] == target){
			return mid;
		}else if(arr[mid] > target){
			high = mid - 1;
		}else{
			low = mid + 1;
		}
	}
	return -1;
}

int main(){
	int arr[] = {1, 2, 3, 4, 5, 6, 14};
	fprintf(stderr, "%d\n", binarySearch(arr, sizeof(arr)/ sizeof(arr[0]), 14));
	return 0;
}
