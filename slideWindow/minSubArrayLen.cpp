//https://leetcode-cn.com/problems/minimum-size-subarray-sum/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int32_t l = 1, r = nums.size(), mid = 0;
        int32_t matched_len = 0;
        bool is_match = false;
        int32_t begin_num_sum = 0;
        int32_t last_head_num = 0;
        int32_t i = 0;
        while(l <= r){
            is_match = false;
            begin_num_sum = 0;
            mid = l + (r - l + 1) / 2;
           //             cout << "mid: " << mid << endl;

            last_head_num = nums[0];
            for(i = 0; i < mid; ++i){
                begin_num_sum = begin_num_sum + nums[i];
                if(begin_num_sum >= target){
                    matched_len = i + 1;
                    is_match = true;
                    break;
                }
            }
            if(! is_match)
            {
                for(i = 1; i + mid <= nums.size(); ++i){
                    begin_num_sum -= last_head_num;
                    //cout << "last_head_num" << endl;
                    last_head_num = nums[i];
                    begin_num_sum += nums[i + mid - 1];
                    if(begin_num_sum >= target){
                        matched_len = mid;
                        //cout << "matched_len: " << matched_len << endl;
                        is_match = true;
                        break;
                    }
                }
            }

            if(is_match)
            {
                r = matched_len - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        return matched_len;
    }
};

int main()
{
    Solution sol;
#if 0
    vector<int32_t> arr = {2,3,1,2,4,3};
    int32_t target = 7;
#elif 0
    vector<int32_t> arr = {1,4,4};
    int32_t target = 4;
#elif 0
    vector<int32_t> arr = {1,1,1,1,1,1,1,1};
    int32_t target = 5;
#elif 1
    vector<int32_t> arr = {1,4,4};
    int32_t target = 4;
#elif 0
    vector<int32_t> arr = {1,2,3,4,5};
    int32_t target = 15;
#endif
    int32_t n = sol.minSubArrayLen(target, arr);
    cout << n << endl;
    return 0;
}


