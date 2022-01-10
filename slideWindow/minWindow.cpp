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
        for(i = 0; i < t_size; ++i){
            auto iter = target_map.find(t.at(i));
            if(iter != target_map.end()){
                target_map.insert(make_pair(t.at(i), 1));
            }else{
                ++target_map[t.at(i)];
            }
        }
        int32_t need_match = s_size;
        for(i = 0; i + t_size < s_size; ++i){
            if(i > 0){
                auto s_iter = current_map.find(s.at(i - 1));
                auto t_iter = target_map.find(s.at(i - 1));

                if(s_iter != current_map.end() && s_iter->second > 0){
                    if(t_iter != target_map.end() &&
                            s_iter->second <= t_iter->second){
                        ++need_match;
                    }
                    --s_iter->second;
                }
            }
            for(j = i; j < s_size; ++j){
                auto t_iter = target_map.find(s.at(j));
                if(t_iter == target_map.end()){
                    continue;
                }
                auto s_iter = current_map.find(s.at(j));
                if(s_iter == current_map.end()){
                    current_map.insert(make_pair(s.at(j), 1));
                    --need_match;
                }else if(s_iter->second < t_iter->second){
                    ++s_iter->second;
                    //++current_map[t.at(i)];
                    --need_match;
                }
                else if(s_iter->second >= t_iter->second){
                    ++s_iter->second;
                    //++current_map[t.at(i)];
                }
                if(need_match == 0){
                    break;
                }
            }
            if(need_match != 0){
                continue;
            }
            //匹配
            for(int32_t m = i + 1; m <= j; ++m){
                auto s_iter = current_map.find(s.at(m - 1));
                auto t_iter = target_map.find(s.at(m - 1));

                if(s_iter != current_map.end() && s_iter->second > 0){
                    --t_iter->second;
                    if(t_iter != target_map.end() &&
                            s_iter->second <= t_iter->second){
                        ++need_match;
                        if(res_str.size() == 0 ||
                                res_str.size() < j - m + 1){
                            res_str = s.substr(m - 1, j - m + 1);
                        }
                        i = m - 1;
                        break; //最短的
                    }
                }
            }
        }
        return res_str;
    }
};

int main()
{
    string s = "ADOBECODEBANC", t = "ABC";
    Solution sol;    
    //string s = "a", t = "a";
    //string s = "a", t = "aa";

    string res = sol.minWindow(s, t);
    cout << res << endl;
    return 0;
}
