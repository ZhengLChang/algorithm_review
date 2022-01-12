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
    int32_t s_size = 0;
    int32_t need_match = 0;

    string minWindow(string s, string t) {
        s_size = s.size();
        need_match = t.size();
        if(s_size < need_match){
            return "";
        }
        unordered_map<char, int32_t> target_map(need_match);
        unordered_map<char, int32_t> current_map(need_match);
        string res_str;
        int32_t l = 0, r = 0;

        //init target map
        for(const auto &c:t){
            ++target_map[c];
        }

        for(l = 0, r = 0; l <= r && l < s_size; ){
            if(need_match == 0){
                auto s_iter = current_map.find(s.at(l));
                auto t_iter = target_map.find(s.at(l));

                if(s_iter != current_map.end() && s_iter->second > 0){
                    if(t_iter != target_map.end() &&
                            s_iter->second <= t_iter->second){
                        if(res_str.size() == 0 ||
                             res_str.size() > r - l + 1){
                            res_str = s.substr(l, r - l + 1);
                        }
                        ++r;
                        ++need_match;
                        ++l;
                        --s_iter->second;
                        continue;
                    }
                    --s_iter->second;
                }
                ++l;
                continue;
            }

            for(; r < s_size; ++r){
                auto t_iter = target_map.find(s.at(r));
                if(t_iter == target_map.end()){
                    continue;
                }
                ++current_map[s.at(r)];

                auto s_iter = current_map.find(s.at(r));
                if(s_iter != current_map.end() && s_iter->second <= t_iter->second){
                    --need_match;
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

namespace Official{
class Solution {
public:
    unordered_map <char, int> ori, cnt;

    bool check() {
        for (const auto &p: ori) {
            if (cnt[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        for (const auto &c: t) {
            ++ori[c];
        }

        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;

        while (r < int(s.size())) {
            if (ori.find(s[++r]) != ori.end()) {
                ++cnt[s[r]];
            }
            while (check() && l <= r) {
                if (r - l + 1 < len) {
                    len = r - l + 1;
                    ansL = l;
                }
                if (ori.find(s[l]) != ori.end()) {
                    --cnt[s[l]];
                }
                ++l;
            }
        }

        return ansL == -1 ? string() : s.substr(ansL, len);
    }
};
}


int main()
{
    Solution sol;    
    //string s = "ab", t = "b";
    //string s = "AADOBECODEBANC", t = "ABC";
    //string s = "a", t = "a";
    //string s = "a", t = "aa";
    string s = "aa", t = "aa";

    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    string res = sol.minWindow(s, t);
    cout << res << endl;
    return 0;
}
