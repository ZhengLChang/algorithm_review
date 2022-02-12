/*
 * https://leetcode-cn.com/problems/count-number-of-nice-subarrays/
 */
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int32_t res = 0;
        if(k <= 0){
            return 0;
        }
        int32_t left = 0;
        int32_t right = 0;

        int32_t cnt = 0;
        vector<int32_t> nice_nums;

        nice_nums.push_back(-1);
        for(int32_t i = 0; i < nums.size(); ++i){
            //奇数？
            if(nums[i] & 0x01){
                nice_nums.push_back(i);
            }
        }
        nice_nums.push_back(nums.size());
        /*
        for(auto nice:nice_nums){
            cout << nice << endl;
        }
        */
        for(int32_t i = 1; i + k < nice_nums.size(); ++i){
            left = nice_nums[i] - nice_nums[i - 1];
            right = nice_nums[i + k] - nice_nums[i + k - 1];
            res += left * right;
        }
#if 0
        for(int32_t i = 0; i + k - 1 < nice_nums.size(); ++i){
            if(i == 0){
                left = nice_nums[i] + 1;
            }else{
                left = nice_nums[i] - nice_nums[i - 1];
            }

            if(i + k == nice_nums.size()){
                right = nums.size() - nice_nums[i + k - 1];
            }else{
                right = nice_nums[i + k] - nice_nums[i + k - 1];
            }
            //cout << "left: " << left << endl;
            //cout << "right: " << right << endl;
            res += left * right;
        }
#endif

        return res;
    }
};

int main(void){
    Solution sol;
    vector<int> nums = {2,2,2,1,2,2,1,2,2,2};/*{1,1,2,1,1};*/
    int32_t k = 2;

    int ans = sol.numberOfSubarrays(nums, k);

    cout << ans << endl;
    return 0;
}

