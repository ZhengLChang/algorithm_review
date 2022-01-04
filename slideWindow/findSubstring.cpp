/*
https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../util.h"

using namespace std;
class Solution{
public:
    vector<int> findSubstring(string s, vector<string>& words)
    {
        vector<int> v;
        int words_size = words.size();
        if(! words_size )
        {
            return v;
        }
        int single_word_size = words[0].size();
        int min_length = single_word_size * words_size;
        //cout << "single_word_size: " << single_word_size << endl;
        for(int i = 0; i + single_word_size <= s.size() && i + min_length <= s.size(); ++i)
        {
            vector<int> flags(words_size);
            /*
            for(auto iter = flags.begin(); iter != flags.end(); ++iter)
            {
                cout << *iter << " ";
            }
            cout << endl;
            */
            int need_match_num = words_size;
            for(int m = i; m + single_word_size <= s.size(); m += single_word_size)
            {
                bool is_match = false;
                
                for(int j = 0; j < words_size; j = j + 1)
                {
                    if(flags[j])
                    {
                        continue;
                    }
                    if(strncmp(s.c_str() + m, words[j].c_str(), single_word_size) == 0)
                    {
                        is_match = true;
                        --need_match_num;
                        flags[j] = 1;
                        break;
                    }
                }
                if(! is_match)
                {
                    break;
                }
            }
            if(need_match_num == 0)
            {
                v.push_back(i);
            //    break;
            }
            /*
            cout << (s.c_str() + i) << endl;
    for(auto iter = flags.begin(); iter != flags.end(); ++iter)
            {
                cout << *iter << " ";
            }
            cout << endl;
            */

        }
        return v;
    }
};

namespace with_hash{
class Solution{
public:
    vector<int> findSubstring(string s, vector<string>& words)
    {
        vector<int> v;
        unordered_map<string, int> words_table;
        int words_size = words.size();
        if(! words_size )
        {
            return v;
        }

        for(auto iter = words.begin(); iter != words.end(); ++iter)
        {
            if(words_table.find(*iter) == words_table.end())
            {
                words_table[*iter] = 1;
            }
            else
            {
                ++words_table[*iter];
            }
        }
        int single_word_size = words[0].size();
        int min_length = single_word_size * words_size;
        //cout << "single_word_size: " << single_word_size << endl;
        for(int i = 0; i + single_word_size <= s.size() && i + min_length <= s.size(); ++i)
        {
            auto words_table_tmp = words_table;
            int need_match_num = words_size;
            for(int m = i; m + single_word_size <= s.size(); m += single_word_size)
            {
                bool is_match = false;
                string substring = string(s, m, single_word_size);
                if(words_table_tmp[substring] > 0)
                {
                    is_match = true;
                    --need_match_num;
                    --words_table_tmp[substring];
                }
                else
                {
                    break;
                }
                if(need_match_num <= 0)
                {
                    v.push_back(i);
                    break;
                }
            }
            /*
            cout << (s.c_str() + i) << endl;
    for(auto iter = flags.begin(); iter != flags.end(); ++iter)
            {
                cout << *iter << " ";
            }
            cout << endl;
            */

        }
        return v;
    }
};
}

int main(void)
{
#if 1
    with_hash::Solution s;
#else
    Solution s;
#endif
    /*
"wordgoodgoodgoodbestword"
["word","good","best","good"]

       */
    vector<string> words = {"word","good","best","good"};
    vector<int> v;
    uint64_t t1 = GetNowUsecs();
    for(int i = 0; i < 10000; ++i)
    {
        v = s.findSubstring("wordgoodgoodgoodbestword", words);
    }
    uint64_t t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    for(int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
    return 0;
}


