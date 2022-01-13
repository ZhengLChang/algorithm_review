/*
   https://leetcode-cn.com/problems/sliding-window-maximum/
   */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int32_t max_num = INT_MIN;
        vector<int> ans;
        for(int l = 0; l + k <= nums.size(); ++l){
            max_num = INT_MIN;
            for(int r = l; r < l + k; ++r){
                if(nums[r] > max_num){
                    max_num = nums[r];
                }
            }
            ans.push_back(max_num);
        }
        return ans;
    }
};

int main(void){
    Solution sol;
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    //int k = 3;
    int k = 1;
    vector<int> ans = sol.maxSlidingWindow(nums, k);
    for(const auto &obj:ans){
        cout << obj << ", ";
    }
    cout << endl;
    return 0;
}


