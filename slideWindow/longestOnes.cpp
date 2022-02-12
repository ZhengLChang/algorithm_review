
/*
 * https://leetcode-cn.com/problems/max-consecutive-ones-iii/
 */
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
      int longestOnes(vector<int>& nums, int k) {
          int32_t res = 0;
          if(nums.size() <= 0){
              return res;
          }
          int left = 0, right = 0;
          int zero_num = 0;
          for(left = 0; right < nums.size(); ++right){
            if(nums[right] == 0){
                ++zero_num;
            }
            while(zero_num > k){
                if(nums[left] == 0){
                    --zero_num;
                }
                ++left;
            }
            res = res > (right - left + 1) ? res:(right - left + 1);
          }
          return res;
      }
};

int main(void){
    Solution sol;
    //vector<int> nums = {1,1,1,0,0,0,1,1,1,1,0};
    //int k = 2;
    vector<int> nums = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    int k = 3;
    int ans = sol.longestOnes(nums, k);
    cout << ans << endl;
    return 0;
}

