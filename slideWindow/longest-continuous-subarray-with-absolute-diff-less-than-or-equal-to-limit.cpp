/*
 * https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 */
#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;
class Solution {
public:
    bool check(const map<int, int>& s, int limit){
        if(s.size() == 0){
            return true;
        }
        if(s.rbegin()->first - s.begin()->first  > limit){
            //cout << *s.rbegin() << ", " << *s.begin() << endl;
            return false;
        }
        return true;
    }
    int longestSubarray(vector<int>& nums, int limit) {
        int ans = 0;
        map<int, int> s;
/*
        for(auto num:nums){
            s.insert(num);
        }
        */
        for(int32_t left =0, right = 0; right < nums.size(); ++right){
            ++s[nums[right]];
            while(!check(s, limit)){
                //cout << "erase: " << nums[left] << endl;
                --s[nums[left]];
                if(s[nums[left]] <= 0)
                    s.erase(nums[left]);
                ++left; 
            }
            ans = ans > (right - left + 1) ? ans : (right - left + 1);
            //cout << "ans: " << ans << endl;
        }

        return ans;
    }
};

int main(){
    Solution sol;
    //vector<int> nums = {10, 1, 2, 4, 7, 2};
    vector<int> nums = {4,2,2,2,4,4,2,2};
    
    int32_t limit = 0;
    int32_t ans = 2;

    ans = sol.longestSubarray(nums, limit); 

    cout << ans << endl;
    return 0;
}

