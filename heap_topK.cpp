#include <iostream>
#include <vector>

using namespace std;

class heap_topK{
public:
    heap_topK(const int &K = 10);
    heap_topK(vector<int>& init_arr, const int& K = 10);
    void add(const int &new_num);
    void print_result();

private:
    void heap_sort(vector<int> &arr, int arr_len);
    void adjust(vector<int>&arr, int arr_len, int index);
    int m_K;
    vector<int> m_arr;
};

heap_topK::heap_topK(const int &K)
{
    m_K = K;
}

heap_topK::heap_topK(vector<int>& init_arr, const int& K)
{
    m_K = K;
    for(auto node:init_arr)
    {
        add(node);
    }
}
void heap_topK::add(const int &new_num)
{
    int arr_len = m_arr.size();
    if(arr_len <= 0)
    {
        m_arr.push_back(new_num);
        return;
    }
    else if(arr_len < m_K)
    {
        m_arr.push_back(new_num);
        heap_sort(m_arr, m_arr.size());
    }
    else if(m_arr[0] < new_num)
    {
        m_arr[0] = new_num;
        heap_sort(m_arr, m_arr.size());
    }
}

void heap_topK::print_result()
{
    vector<int> tmp_arr(m_arr);

    for(auto node : tmp_arr)
    {
        cout << node << " ";
    }
    cout << endl;

    int arr_len = tmp_arr.size();
    for(int i = arr_len - 1; i >= 0; --i)
    {
        int tmp = tmp_arr[i];
        tmp_arr[i] = tmp_arr[0];
        tmp_arr[0] = tmp;
        heap_sort(tmp_arr, i);
    }
    for(auto node : tmp_arr)
    {
        cout << node << " ";
    }
    cout << endl;
}
void heap_topK::heap_sort(vector<int> &arr, int arr_len)
{
    int last_non_leaf_node = arr_len / 2 - 1; 
    for(int i = last_non_leaf_node; i >= 0; --i)
    {
        adjust(arr, arr_len, i);
    }
}
void heap_topK::adjust(vector<int>&arr, int arr_len, int index)
{
    int left_node = index * 2 + 1;
    int right_node = index * 2 + 2;
    int max_node = index;
    if(left_node < arr_len && arr[left_node] < arr[max_node])
    {
        max_node = left_node; 
    }
    if(right_node < arr_len && arr[right_node] < arr[max_node])
    {
        max_node = right_node; 
    }
    if (max_node != index)
    {
        int tmp = arr[max_node];
        arr[max_node] = arr[index];
        arr[index] = tmp;
        adjust(arr, arr_len, max_node);
    }

}

int main(void)
{
    vector<int> arr = {8, 5, 2, 22, 1, 5, 19, 9, 4, 10, 11};
    heap_topK topK_obj = heap_topK(arr);
    topK_obj.print_result();
    return 0;
}



