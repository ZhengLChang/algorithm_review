/*
 * https://leetcode-cn.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/
 */
#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int32_t res = 0;
        int32_t sum = 0;
        for(int32_t left = 0; left < k; ++left){
            sum += arr[left];
        }
        if(sum / k >= threshold){
            ++res;
        }
        
        for(int32_t left = 1; left + k <= arr.size(); ++left){
            sum -= arr[left - 1];
            sum += arr[left + k - 1];
            if(sum / k >= threshold){
                ++res;
            }
        }
        return res;
    }
};


int main(void){
    Solution sol;
    vector<int32_t> arr = {7,7,7,7,7,7,7};//{1,1,1,1,1};//{2,2,2,2,5,5,5,8};
    int32_t k = 7, threshold = 7;

    int32_t ans = 3;
    ans = sol.numOfSubarrays(arr, k, threshold);
    cout << ans << endl;
    return 0;
}
