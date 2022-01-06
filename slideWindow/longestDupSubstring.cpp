/*
   https://leetcode-cn.com/problems/longest-duplicate-substring/
   */
#include <iostream>
#include <unordered_set>
#include "../util.h"

using namespace std;

class Solution {
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string substring = "";
        int substr_len = 0;
        int j = 0;
        if(s.size() <= 1)
        {
            return "";
        }
        unordered_set<string> sub_set(1240);
        int win_len = s.size() - 1;
        for(; win_len >= 1; --win_len)
        {
            sub_set.clear();
            for(int i = 0; i + win_len <= s.size(); ++ i)
            {
                substring = s.substr(i, win_len);
                if(sub_set.find(substring) == sub_set.end())
                {
                    sub_set.insert(substring);
                }
                else
                {
                    //cout << "sub_set.size() : " << sub_set.size() << endl;
                    return substring;
                }
            }
        }
        return "";
#if 0
        for(int i = 0; i < s.size(); ++i)
        {
            if(longest_str.size() > (s.size() - i))
            {
                continue;
            }
            for(j = s.size(); j < s.size(); ++j)
            {
                substr_len = (j - i + 1);
                if(longest_str.size() > substr_len)
                {
                    continue;
                }
                //cout << "(" << longest_str.size() << ", " << (j - i + 1) << ")" << endl;
                substring = s.substr(i, substr_len);
                if(sub_set.find(substring) == sub_set.end())
                {
                    sub_set.insert(substring);
                }
                else if(substring.size() > longest_str.size())
                {
                    longest_str = substring;
                    if(longest_str.size() == s.size() - 1)
                    {
                        return longest_str;
                    }

                }
            }
        }
        return longest_str;
#endif
    }
};

namespace Bi
{
class Solution {
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string substring = "";
        bool is_match = false;
        int substr_len = 0;
        int j = 0;
        if(s.size() <= 1)
        {
            return "";
        }
        unordered_set<string> sub_set(1240);
        int min_win_len = 1;
        int max_win_len = s.size() - 1;
        int mid_win_len = (max_win_len - min_win_len)/ 2 + min_win_len;
        for(; ;)   
        {
            //if(mid_win_len == min_win_len && max_win_len > min_win_len)
            //{
            //    ++mid_win_len;
            //}
            is_match = false;
            sub_set.clear();
            //cout << "mid_win_len: " << mid_win_len << endl;
            for(int i = 0; i + mid_win_len <= s.size(); ++ i)
            {
                substring = s.substr(i, mid_win_len);
                if(sub_set.find(substring) == sub_set.end())
                {
                    sub_set.insert(substring);
                }
                else
                {
                    longest_str = substring;
                    is_match = true;
                    break;
                }

            }
            if(mid_win_len == min_win_len || 
                    mid_win_len == max_win_len)
            {
                break;
            }
            if(is_match)
            {
                min_win_len = mid_win_len + 1;
                mid_win_len = (max_win_len - min_win_len)/ 2 + min_win_len;
            }
            else
            {
                max_win_len = mid_win_len;
                mid_win_len = (max_win_len - min_win_len)/ 2 + min_win_len;
            }
        }

        return longest_str;
    }
};
}

int main()
{
    Solution s;
    Bi::Solution s_bi;
    //string str = "banana";
    //string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "abcd";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    //string str = "polxtvqlurgobbzbjcjsupskvzmtuveuavrzcxaifmdwqjbuejdasuxcvsupqnucorfawncjqkbakilhiekavhmsjbtlsfydijafxhgrgbsswtnvdquwokcliaxevairergwdtndsibiulqiutkcwsqpzuyypnhiowgvkkdbpkoyvgwyuqcokjnxluamwnuhqjtaossezwxvkpdkqcleqjkelcludtbigxkueupnxjncrbgvdrsdpppqqcopnwadqsxkvlkghfmtvdeygpyxamvxhmmaunxskgnenobvnzizbxwrjeedisrgzykoaidiffzqzsmirxkvfwmtifywamcpxziyjohcudzelgbmdgiaqwnzdbkwbhdioiokaivzlzscshrvbmggdztjuimribrgmdlcctvldbcxwpqnqbkzrcayqdqraobqcgoxxocclasphcjcydpkgkqhrmmxtklpxfxnrgnzczjxanaltnjhwfatgryqhcllemgqcchiagizpdgiqioqyhrpattutmuotrcwtxvdqzzsomofizebbqrgwruydyawsssjkakjpjlzmfhmjetymftxrhilpcgfqyoohyydnodfortlkeoncmfkdraiqydxcodyapjaxumjwczwmthrcecfgsswwtnyqurvggamjbsjdzmcuyefwnsrnhhpusfdsxbsrsrywbccullupdbovnmzluqsfdhqbef";
    //string str = "abcd";
    uint64_t t1 = GetNowUsecs();
    string longeststr = s.longestDupSubstring(str);
    uint64_t t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr << endl;

    cout << "===== Bi ======" << endl;
    t1 = GetNowUsecs();
    longeststr = s_bi.longestDupSubstring(str);
    t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr << endl;
    return 0;
}
