#include <iostream>
#include <vector>
/**
www.cnblogs.com/wanglei5205/p/8733524.html
定理: 计算机软件技术基础 119
  **/
using namespace std;
void adjust(vector<int> &arr, int len, int index){
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int maxIdx = index;
	if(left < len && arr[left] > arr[maxIdx]){
		maxIdx = left;
	}
	if(right < len && arr[right] > arr[maxIdx]){
		maxIdx = right;
	}
	if(maxIdx != index){
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);
	}
}
void heapSort(vector<int> &arr, int size){
	for(int i = size / 2 - 1; i >= 0; i--){
		adjust(arr, size, i);
	}
	for(int i = size - 1; i >= 1; i--){
		swap(arr[0], arr[i]);
		adjust(arr, i, 0);
	}
}
int main(){
	vector<int> arr = {8, 1, 14, 3, 21, 5};
	heapSort(arr, arr.size());
	for(int i = 0; i < arr.size(); i++){
		cout << arr[i] << endl;
	}
	return 0;
}







