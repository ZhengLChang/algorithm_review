/*
 * https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/
 * */
#include <iostream>
#include <unordered_map>
#include <unordered_set>


using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int32_t ans = -1;
        return ans;
    }
};


int main(void){
    Solution sol;
    vector<int32_t> nums = {1};
    int32_t k = 1;

    int32_t ans = sol.shortestSubarray(nums, k); 

    cout << "ans: " << ans << endl;
    return 0;
}

