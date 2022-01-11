/*
   https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/solution/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/
解题思路
i为左窗口， j为右窗口；
因为每次我要让右窗口移动， 所以用for循环， 当右窗口移动到len时停止；

再用一个S【】数组去标记每个字符在 窗口 出现的次数，当S[a] == 2;
代表a字符出现了2次， 这时候我们就移动左窗口， 并将出窗口的每个字符次数减1，即S[s[i]]--;

然后每次更新窗口的最大长度， j - i + 1 为当前窗口的长度；
如果比更新前大， 则更新窗口的最大长度为j - i + 1;
否则不更新

int lengthOfLongestSubstring(char * s){
    int len = strlen(s);
    if(len == 0)
        return 0;
    int S[256] = {0};
    int i, j, m = 0;
    for(i = 0, j = 0; j < len; j++){
        S[s[j]]++;
        while(S[s[j]] > 1){
            S[s[i]]--;
            i++;
        }
        m = fmax(m, j - i + 1);
    }
    return m;
}

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int i, j,maxi = 0;
        vector<int> S(128, 0);
        int len = s.size();
        for(i = 0, j = 0; j < len; j++){
            S[s[j]]++;
            while(S[s[j]] > 1){
                S[s[i]]--;
                i++;
            }
            maxi = max(maxi, j - i + 1);
        }
        return maxi;
    }
    
};


   */
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include "../util.h"


using namespace std;
class Solution{
public:
    int lengthOfLongestSubstring(std::string s){
        std::unordered_set<char> occ;
        int n = s.size();

        int rk = -1, ans = 0;

        for(int i = 0; i < n; ++i){
            if(i != 0){
                occ.erase(s[i - 1]);
            }
            while(rk + 1 < n && !occ.count(s[rk + 1]))
            {
                occ.insert(s[rk + 1]);
                ++rk;
            }
            ans = std::max(ans, rk - i + 1);
        }
        return ans;
    }
};

namespace BI
{
class Solution{
public:
    int lengthOfLongestSubstring(std::string s){
        int32_t l = 1, r = s.size(), mid = l + (r - l + 1) / 2;
        int32_t i = 0, ans = 0;
        unordered_map<char, int32_t> occ_map;
        char head_char = 0;
        bool is_repeated = false;

        while(l <= r){
            mid = l + (r - l + 1) / 2;
            head_char = s.at(0);
            
            occ_map.clear(); 
            for(i = 0; i + mid < s.size(); ++i){
                if(occ_map.in)
            }

        }
    }
};
}


int main(void)
{
    Solution s;
    uint64_t t1 = GetNowUsecs();
    string str = "uirqkccmgnpbqwfkmplmfovxkjtgxbhwzqdlydunpuzxgvodnaanxpdiuhbitfllitaufvcmtneqmvibimvxmzvysignmsfykppdktpfhhcayfcwcrtjsgnyvzytevlqfabpjwxvjtfksztmdtrzgagdjtpeozzxppnkdbjayfbxqrqaefkcdbuvteobztucgdbcmlgnxldcwtzkvhwqxbsqlbsrbvesemhnbswssqvbiketdewfauvtzmyzrrqslzagjcyuznkpkgpkkinldxcjtuoumcbcttabfuzjbtoqjqbpnsemojbtctvdmobnuutcsfmhkrbwkmpdcdncqizgtlqekvqophqxewkpxpkrgjivrtarxtwbbfhfikbrdwohppyiyyztopksdmxvqiaafswyjfnlwntldwniypzaxrscyqfrlqehqgzaxxazfwtwjajsrmwuerdqklhwoqxptcvqoqbjwfqrewirtcbskmkaqgtcnxnsqmwgwjxruhyyjtbuivvepnxiwjmtlrvexjzevctflajibxkvmbzdfwoqobmhstgpshtxitwttpkdvfmfwtwsazfgzwbtmqrowrcesyyeuwunodesrzbmjbxnchaqptfgqlknuarhgnsbwnucdhckpbwhtwhejivrmuccbwnyenyvonquscneswngwbkjysxvdwbzymwxcrnexrxhmuwvycmsiazmqavgmyurbcmvdjplloidbzacunerwobvaxsromiiwzqxnrsjpyoacfxcmmogmokhpmhxzkdzmpjcrgaeihdhczrmxmfurjatuwxriiwtfojwvkkybcdmwayhnzrnqrynwtrvmtgtrxndlbtlhyzfjtbtvqujjuwpibuonuwjdfvnhdqqzlmwwheztjkrrzrroogovapywxkjsccjnseanhxijybintgbjwlkmdzuoeclfqatffgjvcbujovunnauprhoocxzghzvsmuyhsl";
    std::cout << s.lengthOfLongestSubstring(str) << std::endl;
    uint64_t t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    return 0;
}
