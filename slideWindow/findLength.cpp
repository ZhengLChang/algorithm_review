/*
   https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/
   */
#include <iostream>

class Solution{
public:
    int findLength(vector<int>& nums1, vector<int>& nums2){
        int i = 0, j = 0, k = 0;
        int nums1_size = nums1.size();
        int nums2_size = nums2.size();
        int min_len = nums1_size < nums2_size ? nums1_size:nums2_size;
        int max_common_len = 0;
        for(i = 0; i < nums1.size(); ++i)
        {
            for(j = 0; j < min_len; ++j)
            {
                if()
            }
        }
    }
};

int main()
{
    vector<int> &num1 = {1,2,3,2,1};
    vector<int> &num2 = {3,2,1,4,7};

    return 0;
}
