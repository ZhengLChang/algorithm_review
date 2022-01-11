/*
   https://leetcode-cn.com/problems/minimum-window-substring/
   */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int32_t s_size = s.size();
        int32_t t_size = t.size();
        string res_str;
        if(s_size < t_size){
            return "";
        }
        unordered_map<char, int32_t> target_map(t_size);
        unordered_map<char, int32_t> current_map(t_size);
        int32_t i = 0, j = 0;
        int32_t l = 0, r = 0;
        for(i = 0; i < t_size; ++i){
            auto iter = target_map.find(t.at(i));
            if(iter != target_map.end()){
                target_map.insert(make_pair(t.at(i), 1));
            }else{
                ++target_map[t.at(i)];
            }
        }

        int32_t need_match = t_size;

        for(l = 0, r = 0; l <= r && l < s_size; ++l){
            //if(l > 0){
            if(need_match == 0)
            {
                auto s_iter = current_map.find(s.at(l));
                auto t_iter = target_map.find(s.at(l));

                if(s_iter != current_map.end() && s_iter->second > 0){
                    if(t_iter != target_map.end() &&
                            s_iter->second <= t_iter->second){

                        if(res_str.size() == 0 ||
                             res_str.size() > r - l + 1){
                            res_str = s.substr(l, r - l + 1);
                            cout << "res_str: " << res_str << endl;
                        }
                        ++r;
                        ++need_match;
                        --s_iter->second;
                        continue;
                    }
                    --s_iter->second;
                }
            }

            if(need_match == 0){
                continue;
            }

            for(; r < s_size; ++r){
                auto t_iter = target_map.find(s.at(r));
                if(t_iter == target_map.end()){
                    continue;
                }
                auto s_iter = current_map.find(s.at(r));
                if(s_iter == current_map.end()){
                    current_map.insert(make_pair(s.at(r), 1));
                    --need_match;
                }else if(s_iter->second < t_iter->second){
                    ++s_iter->second;
                    --need_match;
                }
                else if(s_iter->second >= t_iter->second){
                    ++s_iter->second;
                }
                if(need_match == 0){
                    break;
                }
            }
            if(need_match != 0){
                return res_str;
            }else{
                if(res_str.size() == 0 ||
                        res_str.size() > r - l + 1){
                    res_str = s.substr(l, r - l + 1);
                }
            }
        }

        return res_str;
    }
};

int main()
{
    Solution sol;    
    //string s = "ab", t = "b";
    string s = "AADOBECODEBANC", t = "ABC";
    //string s = "a", t = "a";
    //string s = "a", t = "aa";

    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    string res = sol.minWindow(s, t);
    cout << res << endl;
    return 0;
}
