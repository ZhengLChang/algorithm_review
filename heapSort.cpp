#include <iostream>
#include <vector>
/**
www.cnblogs.com/wanglei5205/p/8733524.html
完全二叉树性质: 计算机软件技术基础 119
定义：如果一棵二叉树中，只有最下面的两层结点度数小于2，其余各层结点度数都等于2，并且最下面一层的结点，都集中在该层最左边的若干位置上，则此二叉树称为完全二叉树。
性质1、具有n个结点的完全二叉树的高度k为[log^2n]。
性质2、对于具有n个结点的完全二叉树，如果按照从上（根结点）到下(叶结点)和从左到右的顺序对二叉树中的所有结点从1开始到n进行编号，则对于任意的下标为i的结点，有：
（1）如果i=0，则它是根结点，它没有父结点；如果i>0,则它的父结点的下标为i/2。
（2）如果2i<=n，则下标为i的结点的左子结点的下标为2i；否则，下标为i的结点没有左子结点。
（3）如果2i+1<=n，则下标为i的结点的右子结点的下标为2i+1；否则，下标为i的结点没有右子结点。 
时间复杂度: nlogn
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
	/*从最后一个非叶子结(size/2 - 1)点向上*/
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







