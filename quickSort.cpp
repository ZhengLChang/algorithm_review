#include <iostream>
#include <vector>
using namespace std;
/**
	时间复杂度: nlogn
  */
void quickSort(vector<int> &arr, int left, int right){
	int key = arr[left];
	int l = left;
	int r = right;
	if(left >= right)
		return;
	while(left < right){
		while(left < right && arr[right] >= key){
			right--;
		}
		if(left < right){
			arr[left] = arr[right];
		}
		while(left < right && arr[left] < key){
			left++;
		}
		if(left < right){
			arr[right] = arr[left];
		}
	}
	arr[left] = key;
	quickSort(arr, l, left - 1);
	quickSort(arr, left + 1, r);
	return ;
}
int main(void){
	vector<int> arr = {46, 79, 56, 38, 40, 84};
	int i = 0;
	quickSort(arr, 0, arr.size() - 1);
	for(i = 0; i < arr.size(); i++){
		cout << arr[i] << "\t";
	}
	cout << endl;

	return 0;
}
