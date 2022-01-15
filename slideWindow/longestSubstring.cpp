/*
   https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/
   */
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<char, int32_t> record;
    bool check(int k){
        for(const auto &iter:record){
            if(iter.second < k){
                return false;
            }
        }
        return true;
    }
    int longestSubstring(string s, int k) {
        int32_t ans_left = 0, ans_len = 0;
        int32_t left = 0, right = 0;

        for(left = 0; left + k <= s.size(); ++left){
            record.clear();
            for(right = left; right < s.size(); ++right){
                ++record[s[right]];
                if(check(k) && ans_len < right - left + 1){
                    ans_left = left;
                    ans_len = right - left + 1;
                }
            }
        }
        //cout << "longestSubstring: " << s.substr(ans_left, ans_len) << endl;;
        return ans_len;
    }
};

namespace Optimize{
class Solution {
public:
    int longestSubstring(string s, int k) {
        int32_t ans_left = 0, ans_len = 0;
        int32_t left = 0, right = 0;

        for(left = 0; left < s.size(); ++left){
                ++record[s[right]];
        }

        for()

        for(left = 0; left + k <= s.size(); ++left){
            record.clear();
            for(right = left; right < s.size(); ++right){
                ++record[s[right]];
                if(check(k) && ans_len < right - left + 1){
                    ans_left = left;
                    ans_len = right - left + 1;
                }
            }
        }
        //cout << "longestSubstring: " << s.substr(ans_left, ans_len) << endl;;
        return ans_len;
    }
};
}

int main(void){
    Solution sol;
    //string s = "aaabb";
    //int32_t k = 3;
    //string s= "ababbc";
    //int32_t k = 2;
    string s= "a";
    int32_t k = 1;

    if(s.size() < 100){
        cout << "s: " << s << endl;
        cout << "k: " << k << endl;
    }
    int32_t ans = sol.longestSubstring(s, k);

    cout << ans << endl;
    return 0;
}

