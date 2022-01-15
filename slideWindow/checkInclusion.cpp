/*
   https://leetcode-cn.com/problems/permutation-in-string/
   */
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<char, int32_t> target_table;
    unordered_map<char, int32_t> win_table;
    bool check(){
        for(const auto& obj:target_table){
            //cout << obj.first << ", " << obj.second << endl;
            if(! win_table.count(obj.first) ||
                    win_table[obj.first] != obj.second){
                return false; 
            }
        }
        return true;
    }
    bool checkInclusion(string s1, string s2) {
        for(const auto& c:s1){
            ++target_table[c];
        }
        for(int i = 0; i + s1.size() <= s2.size(); ++i){
            win_table.clear();
            for(int j = i; j < s2.size() && j - i < s1.size(); ++j){
                //cout << "i: " << i << ",j: " << j << endl;
                if(target_table.count(s2[j]) <= 0){
                    break;
                }
                ++win_table[s2[j]];
            }
            if(check()){
                return true;
            }
        }
        return false;
    }
};


int main(void){
    Solution sol;
    //string s1 = "ab", s2 = "eidbaooo";
    string s1 = "ab", s2 = "eidboaoo";
    bool res = sol.checkInclusion(s1, s2);
    cout << res << endl;
    return 0;
}

