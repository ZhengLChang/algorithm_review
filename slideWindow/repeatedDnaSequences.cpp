//https://leetcode-cn.com/problems/repeated-dna-sequences/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    const int64_t mod1_num  = 2222222223LL;
    const int64_t mod2_num  = 1111011111LL;
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        const int win_len = 10;
        unordered_map<string, int> substri_set(1023);
        string substr;

        for(int i = 0; i + win_len <= s.size(); ++i)
        {
            substr = s.substr(i, win_len);
            auto iter = substri_set.find(substr);
            if(iter == substri_set.end())
            {
                substri_set.insert(make_pair(substr, 1));
            }
            else if(iter->second <= 1)
            {
                iter->second = 2;
                ans.push_back(substr);
            }
        }
        return ans;
    }
};
namespace Opt{
class Solution {
public:
    const int32_t win_len = 10;
    /*
    const int64_t mod1_num  = 2222222223LL;
    const int64_t mod2_num  = 1111011111LL;
    */
    unordered_map<int64_t, int32_t> dna2num_map;
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        unordered_map<int64_t, int32_t> substri_set(1023);
        string substr;
        vector<char> v_str(s.size());
        int64_t cur_dna_hash = 0;
        int64_t last_dna_head_hash = 0;
        int64_t head_base = 1;
        if(s.size() <= win_len)
        {
            return ans;
        }
        for(int i = 0; i < win_len - 1; ++i)
        {
            head_base = head_base * 4;
        }
        for(int32_t i = 0; i < s.size(); ++i)
        {
            if(s[i] == 'A')
            {
                v_str[i] = 0;
            }
            else if(s[i] == 'C')
            {
                v_str[i] = 1;
            }
            else if(s[i] == 'G')
            {
                v_str[i] = 2;
            }
            else if(s[i] == 'T')
            {
                v_str[i] = 3;
            }
        }
        

        last_dna_head_hash = v_str[0] * head_base;
        for(int32_t i = 0; i < win_len; ++i)
        {
           cur_dna_hash = cur_dna_hash * 4 + v_str[i];
        }
        substri_set.insert(make_pair(cur_dna_hash, 1));

        for(int32_t i = 1; i + win_len <= s.size(); ++i)
        {
            cur_dna_hash -= last_dna_head_hash;
            last_dna_head_hash = v_str[i] * head_base;
            cur_dna_hash = cur_dna_hash * 4 + v_str[i + win_len - 1];

            auto iter = substri_set.find(cur_dna_hash);
            if(iter == substri_set.end())
            {
                substri_set.insert(make_pair(cur_dna_hash, 1));
            }
            else if(iter->second <= 1)
            {
                iter->second = 2;
                ans.push_back(s.substr(i, win_len));
            }
        }
        return ans;
    }
};
}
int main()
{
    Opt::Solution slt;
    //Solution slt;
    vector<string> v_s;
    v_s.push_back("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    v_s.push_back("AAAAAAAAAAAAA");
    v_s.push_back("AAAAAAAAAAA");

    for(int m = 0; m < v_s.size(); ++m)
    {
        auto ans = slt.findRepeatedDnaSequences(v_s[m]);
        cout << v_s[m] << endl;
        cout << "ans: " << endl;
        for(int i = 0; i < ans.size(); ++i)
        {
            cout << ans[i] << endl;
        }
        cout << endl << endl;
    }
    return 0;
}


