/**
 * https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
 */ 
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int32_t> target;
        unordered_map<char, int32_t> win;
        
        for(const auto& c:p){
            ++target[c];
        }

        int32_t left = 0, right = 0;
        for(left = 0; left + p.size() < s.size(); ++left){}

    }
};


int main(void){
    Solution sol;
    string s = "cbaebabacd", p = "abc";

    vector<int> ans = sol.findAnagrams(s, p);
    for(const auto& m:ans){
        cout << m << ",";
    }
    cout << endl;
    return 0;
}
