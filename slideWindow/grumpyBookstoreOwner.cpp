/**
 * https://leetcode-cn.com/problems/grumpy-bookstore-owner/
 */
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int res = 0;
        int cur_res = 0;
        int32_t left = 0, right = 0;
        int base = 0;//不使用抑制情绪时，客户满意数目
        for(int i = 0; i < customers.size(); ++i){
            if(grumpy[i] == 1){
                continue;//生气，客户不满意，跳过
            }
            cur_res += customers[i];
        }
        if(minutes <= 0){
            return cur_res;
        }
        for(left = 0, right = 0; right < customers.size(); ++right){
            if(right - left >= minutes){
                //生气？
                if(grumpy[left] == 1){
                    cur_res -= customers[left];
                }
                ++left;
            }
            if(grumpy[right] == 1){
                cur_res += customers[right];
            }
            res = max(res, cur_res);
        }
        return res;
    }
};

int main(void){
    Solution sol;
    vector<int> customers = {1};//{1,0,1,2,1,1,7,5};
    vector<int> grumpy = {0};//{0,1,0,1,0,1,0,1};
    int minutes = 1;//3;
    int res = 0;

    res = sol.maxSatisfied(customers, grumpy, minutes);
    cout << res << endl;
    return 0;
}


