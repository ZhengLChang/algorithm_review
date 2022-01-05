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
        unordered_set<string> sub_set(124000);
        for(int i = 0; i < s.size(); ++i)
        {
            if(longest_str.size() > (s.size() - i))
            {
                continue;
            }
            for(j = i; j < s.size(); ++j)
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
        cout << sub_set.size() << endl;
                        return longest_str;
                    }

                }
            }
        }
        cout << sub_set.size() << endl;
        return longest_str;
    }
};


int main()
{
    Solution s;
    //string str = "banana";
    //string str = "aa";
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    string str = "polxtvqlurgobbzbjcjsupskvzmtuveuavrzcxaifmdwqjbuejdasuxcvsupqnucorfawncjqkbakilhiekavhmsjbtlsfydijafxhgrgbsswtnvdquwokcliaxevairergwdtndsibiulqiutkcwsqpzuyypnhiowgvkkdbpkoyvgwyuqcokjnxluamwnuhqjtaossezwxvkpdkqcleqjkelcludtbigxkueupnxjncrbgvdrsdpppqqcopnwadqsxkvlkghfmtvdeygpyxamvxhmmaunxskgnenobvnzizbxwrjeedisrgzykoaidiffzqzsmirxkvfwmtifywamcpxziyjohcudzelgbmdgiaqwnzdbkwbhdioiokaivzlzscshrvbmggdztjuimribrgmdlcctvldbcxwpqnqbkzrcayqdqraobqcgoxxocclasphcjcydpkgkqhrmmxtklpxfxnrgnzczjxanaltnjhwfatgryqhcllemgqcchiagizpdgiqioqyhrpattutmuotrcwtxvdqzzsomofizebbqrgwruydyawsssjkakjpjlzmfhmjetymftxrhilpcgfqyoohyydnodfortlkeoncmfkdraiqydxcodyapjaxumjwczwmthrcecfgsswwtnyqurvggamjbsjdzmcuyefwnsrnhhpusfdsxbsrsrywbccullupdbovnmzluqsfdhqbef";
    uint64_t t1 = GetNowUsecs();
    string longeststr = s.longestDupSubstring(str);
    uint64_t t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr << endl;
    return 0;
}
