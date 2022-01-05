/*
   https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/
   */
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
class Solution{
public:
    int findLength(vector<int>& nums1, vector<int>& nums2){
        int nums1_size = nums1.size();
        int nums2_size = nums2.size();
        int nums1_begin = nums1_size - 1;
        int nums1_end = nums1_size;
        int nums2_begin = 0;
        int nums2_end = 1;
        int win_len = nums1_end - nums2_begin;
        int k = 0;
        int max_comon_str = 0;
        for(; ;)
        {
            win_len = nums1_end - nums1_begin; 
            k = 0;
            for(int i = 0; i < win_len; ++i)
            {
                if(nums1[nums1_begin + i] == nums2[nums2_begin + i])
                {
                    ++k;
                }
                else
                {
                    max_comon_str = max_comon_str > k ? max_comon_str:k;
                    k = 0;
                }
            }
            max_comon_str = max_comon_str > k ? max_comon_str:k;
            /*未全部进入
              A   ----------
              B           ----------
             */
            if(nums2_begin == 0 &&
                    nums1_begin != 0 &&
                    nums2_end < nums2_size)
            {
                --nums1_begin;
                ++nums2_end;
            }
            /*
               全部进入
               A   -------------
               B     ----------
             */
            else if(nums2_begin == 0 &&
                    (nums2_end == nums2_size || nums1_begin == 0)&&
                    nums1_end - nums1_begin > 1)
            {
                if(nums1_begin == 0)
                {
                    --nums1_end;
                    ++nums2_begin;
                }
                else
                {
                    --nums1_begin;
                    --nums1_end;
                }
            }
            /*
               将从左侧出来
               A      -------------
               B     ----------
             */
            else if(nums2_begin > 0 &&
                    nums1_end - nums1_begin > 1)
            {
                --nums1_end;
                ++nums2_begin;
            }
            else
            {
                break;
            }

        }
        return max_comon_str;
    }
};

int main()
{
    Solution s;
#if 0
    vector<int> num1{1,2,3,2,1};
    vector<int> num2{3,2,1,4,7};
#else
    vector<int> num1{1,0,0,0,1};
    vector<int> num2{1,0,0,1,1};
#endif

    cout << s.findLength(num1, num2) << endl;
    return 0;
}
