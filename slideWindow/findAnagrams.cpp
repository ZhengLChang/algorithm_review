/**
 * https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
 */ 
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    unordered_map<char, int32_t> target;
    unordered_map<char, int32_t> win;
    bool check(){
        for(const auto &o:target){
            if(win[o.first] != o.second){
                return false;
            }
        }
        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        for(const auto& c:p){
            ++target[c];
        }

        int32_t left = 0, right = 0;
        for(; right < s.size(); ){
            while(right - left < p.size()){
                ++win[s.at(right)];
                ++right;
            }
            if(check()){
                ans.push_back(left);
            }
            --win[s.at(left)];
            ++left;
        }

        return ans;
    }
};


int main(void){
    Solution sol;
    //string s = "cbaebabacd", p = "abc";
    string s = "abab", p = "ab";

    vector<int> ans = sol.findAnagrams(s, p);
    for(const auto& m:ans){
        cout << m << ",";
    }
    cout << endl;
    return 0;
}
