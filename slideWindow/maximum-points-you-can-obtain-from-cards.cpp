/*
 * https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/
 */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int32_t ans = 0;
        vector<int32_t> ans_v;
        vector<int32_t> reverse_ans_v;

        ans_v.resize(cardPoints.size() + 1);
        reverse_ans_v.resize(cardPoints.size() + 1);
        int32_t i = 1;
        for(const auto c : cardPoints){
            if(i == 0)
                ans_v[i] = c;
            else
                ans_v[i] = ans_v[i - 1] + c;
            ++i;
        }
        int32_t j = 1;
        for(i = cardPoints.size() - 1; i >= 0; --i){
            if(i == cardPoints.size() - 1){
                reverse_ans_v[j] = cardPoints[cardPoints.size() - 1];
            }
            else
            {
                reverse_ans_v[j] = cardPoints[i] + reverse_ans_v[j - 1];
            }
            ++j;
        }
#if 0 
        for(const auto c:ans_v){
            cout << c << ", ";
        }
        cout << endl;
        for(const auto c:reverse_ans_v){
            cout << c << ", ";
        }
        cout << endl;
#endif
        for(i = 0; i <= k; ++i){
            int32_t new_ans = ans_v[k - i] + reverse_ans_v[i];
            ans = ans > new_ans ? ans:new_ans;
        }

        return ans;
    }
};


int main(void){
    Solution sol;
    vector<int> cardPoints = {2, 2, 2};
    int32_t k = 2;
    int32_t ans = 12;
    cout << "原始: " ;
        for(const auto c:cardPoints){
            cout << c << ", ";
        }
        cout << endl;

    ans = sol.maxScore(cardPoints, k);

    cout << ans << endl;
    return 0;
}







