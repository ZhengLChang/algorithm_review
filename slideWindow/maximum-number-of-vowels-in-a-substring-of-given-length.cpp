/*
 * https://leetcode-cn.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
 * 给你字符串 s 和整数 k 。

请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。

英文中的 元音字母 为（a, e, i, o, u）



输入：s = "abciiidef", k = 3
输出：3
解释：子字符串 "iii" 包含 3 个元音字母。

 */

#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;
class Solution {
public:
    int maxVowels(string s, int k) {
        int32_t ans = 0;
        int32_t vowel_num = 0;

        for(int32_t left = 0, right = 0; right < s.size(); ++right){
            if(s.at(right) == 'a' ||
                    s.at(right) == 'e' ||
                    s.at(right) == 'i' ||
                    s.at(right) == 'o' ||
                    s.at(right) == 'u'){
                ++vowel_num;
            } 
            while(right - left + 1 > k){
                if(s.at(left) == 'a' ||
                        s.at(left) == 'e' ||
                        s.at(left) == 'i' ||
                        s.at(left) == 'o' ||
                        s.at(left) == 'u'){
                    --vowel_num;
                }
                ++left;
            }
            if(right - left + 1 == k){
                ans = ans > vowel_num ? ans : vowel_num;
            }

        }

        return ans;
    }
};

int main(void){
    Solution sol;
    string s = "abciiidef";
    int k = 3;

    int ans = sol.maxVowels(s, k);


    cout << ans << endl;
    return 0;
}


