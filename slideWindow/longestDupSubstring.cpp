/*
   https://leetcode-cn.com/problems/longest-duplicate-substring/
   */
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <utility>
#include <cmath>
#include <climits>
#include <vector>
#include "../util.h"

using namespace std;

class Solution {
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string substring = "";
        int substr_len = 0;
        int j = 0;
        int s_size = s.size();
        if(s_size <= 1)
        {
            return "";
        }
        unordered_set<string> sub_set(1240);
        int win_len = s_size - 1;
        int i = 0;
        for(; win_len >= 1; --win_len)
        {
            sub_set.clear();
            for(i = 0; i + win_len <= s_size; ++ i)
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
        //unordered_set<string, StringHash, StringComparer> sub_set(4240);
        unordered_set<string> sub_set;
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
            //cout << min_win_len << ", " << max_win_len << ", mid_win_len: " << mid_win_len << endl;
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
            if(mid_win_len == min_win_len)
            {
                break;
            }
            if(is_match)
            {
                min_win_len = mid_win_len + 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
            else
            {
                max_win_len = mid_win_len - 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
        }

        return longest_str;
    }
};
}
namespace Bi2
{
struct PairHash
{
    const size_t operator()(const std::pair<int32_t, int32_t>& x)const
    {
#if 0
        return x.second;
        uint64_t v = (uint64_t)x.second;
        uint32_t hash = 0xabcdef;
        hash = hash ^ v;
        return (size_t)(hash % 10240);
#endif
        return x.first ^ x.second;
    }
};
struct PairComparer
{
    bool operator()(const std::pair<int32_t, int32_t> &x1, const std::pair<int32_t, int32_t> &x2) const
    {
        return x1.first == x2.first && x1.second == x2.second;
    }
};


class Solution {
public:
    const int64_t mod1_num  = 2222222223LL;
    const int64_t mod2_num  = 1111011111LL;

    unordered_map<pair<int32_t , int32_t >,  pair<int64_t, int64_t>, PairHash, PairComparer> pow_cache;
    //char buf[1024] = "";
    //char res_buf[1024] = "";
    uint64_t proc_time = 0;
    Solution()
    {
        int64_t num1 = mod1_num * mod1_num;
        int64_t num2 = mod2_num * mod2_num;
        cout << num1 << endl;
        cout << num2 << endl;
    }
public:
    pair<int64_t, int64_t> my_pow(int32_t x, int32_t y)
    {
        long long ans1 = 1, ans2 = 1;
        long long contribute1 = x, contribute2 = x;
        int32_t m1 = y, m2 = y;
        while (m1 > 0) {
            if (m1 % 2 == 1) {
                ans1 = ans1 * contribute1 % mod1_num;
                if (ans1 < 0) {
                    ans1 += mod1_num;
                }
            }
            contribute1 = contribute1 * contribute1 % mod1_num;
            if (contribute1 < 0) {
                contribute1 += mod1_num;
            }
            m1 /= 2;
        }
        while (m2 > 0) {
            if (m2 % 2 == 1) {
                ans2 = ans2 * contribute2 % mod2_num;
                if (ans2 < 0) {
                    ans2 += mod2_num;
                }
            }
            contribute2 = contribute2 * contribute2 % mod2_num;
            if (contribute2 < 0) {
                contribute2 += mod2_num;
            }
            m2 /= 2;
        }
#if 0
        cout << x << "ˆ" << y << " = "  << ans1 << "   ";
        cout << x << "ˆ" << y << " = "  << ans2 << endl;
#endif
        return make_pair(ans1, ans2);
#if 0
        //uint64_t t1 = GetNowUsecs();
        auto iter = pow_cache.find(make_pair(x, y));
         pair<int64_t, int64_t> tmp_pair;
        if(iter != pow_cache.end())
        {
            //cout << "(" << x << ", " << y << ")" << iter->second.first << ", " << iter->second.second << endl;
            tmp_pair =  iter->second;
        }
        else if(y == 1)
        {
            tmp_pair = make_pair(0LL, (int64_t)x);
            pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        }
        else if(y <= 0)
        {
            tmp_pair = make_pair(0LL, 1LL);
            pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        }
        else
        {
            tmp_pair = num_mul(my_pow(x, y - 1), x, 1); 
            pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        }
        //uint64_t t2 = GetNowUsecs();
        //cout << (t2 - t1) << endl;
        //proc_time += (t2 - t1);
        return tmp_pair;
#elif 0
        int low = 1;
        int high = 0;
        for(int i = 0; i < y; ++i)
        {
            low = low * x;
            if(low > mod_num)
            {
            high += (int64_t)(low / mod_num);
            low = low % mod_num;
            }
            //if(high < 0 || low < 0)
                //cout << "x,y: " << x << ", " << y << " => " << "(" << high << ", " << low <<  ")" << endl;
        }
        auto tmp_pair = make_pair(high, low);
        pow_cache.insert(make_pair(make_pair(x, y), tmp_pair));
        return tmp_pair;
#endif
    }
    void num_sub(pair<int64_t, int64_t> &pair_num, const pair<int64_t, int64_t>& mul_pair_num)
    {
        auto pair_tmp = pair_num;
        pair_num.second -= mul_pair_num.second;
        pair_num.first -= mul_pair_num.first;

        pair_num.first = pair_num.first % mod1_num;
        pair_num.second = pair_num.second % mod2_num;
        while(pair_num.first < 0)
        {
            pair_num.first += mod1_num;
        }
        while(pair_num.second < 0)
        {
            pair_num.second += mod2_num;
        }
        //pair_num.first = pair_num.first % mod1_num;
        //pair_num.second = pair_num.second % mod2_num;
#if 0
        cout << "(" << pair_tmp.first << ", " << pair_tmp.second << ") - " << "(" << mul_pair_num.first << ", " << mul_pair_num.second << ")" << "= "  << "(" << pair_num.first << ", " << pair_num.second << ") " << endl;
#endif
        return ;
#if 0
        //snprintf(buf, sizeof(buf), "(%lld, %lld) - (%lld, %lld) = ", pair_num.first, pair_num.second, mul_pair_num.first, mul_pair_num.second);
        if(pair_num.second < mul_pair_num.second) 
        {
            pair_num.second += mod2_num;
            pair_num.first -= 1;
        }
        pair_num.second -= mul_pair_num.second;
        pair_num.first -= mul_pair_num.first;
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
#endif
        return;
    }
    void num_add(pair<int64_t, int64_t> &pair_num, const pair<int64_t, int64_t>& add_pair_num)
    {
        auto pair_tmp = pair_num;
        pair_num.first += add_pair_num.first;
        pair_num.second += add_pair_num.second;

        pair_num.first = pair_num.first % mod1_num;
        pair_num.second = pair_num.second % mod2_num;
        while(pair_num.first < 0)
        {
            pair_num.first += mod1_num;
        }
        while(pair_num.second < 0)
        {
            pair_num.second += mod2_num;
        }
        //pair_num.first = pair_num.first % mod1_num;
        //pair_num.second = pair_num.second % mod2_num;
#if 0
        cout << "(" << pair_tmp.first << ", " << pair_tmp.second << ") + " << "(" << add_pair_num.first << ", " << add_pair_num.second << ")" << "= "  << "(" << pair_num.first << ", " << pair_num.second << ") " << endl;
#endif
#if 0
        //snprintf(buf, sizeof(buf), "(%lld, %lld) + (%lld, %lld) = ", pair_num.first, pair_num.second, add_pair_num.first, add_pair_num.second);
        pair_num.second += add_pair_num.second;
        pair_num.first += add_pair_num.first;

        /*
        if(pair_num.second > mod2_num || pair_num.first > mod1_num)
        {
        pair_num.first += (int64_t)(pair_num.second / mod1_num);
        pair_num.second = (int64_t)(pair_num.second % mod2_num);
        pair_num.first = (int64_t)(pair_num.first % mod1_num);
        }
        */
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
#endif
        return;
    }
    void num_mul(pair<int64_t, int64_t> &pair_num, int64_t num)
    {
        auto pair_tmp = pair_num;
        pair_num.first = pair_num.first * num;
        pair_num.second = pair_num.second * num;
        pair_num.first = pair_num.first % mod1_num;
        pair_num.second = pair_num.second % mod2_num;
#if 1
        if(pair_num.first < 0)
        {
            pair_num.first += mod1_num;
        }
        if(pair_num.second < 0)
        {
            pair_num.second += mod2_num;
        }

        //pair_num.first = pair_num.first % mod1_num;
        //pair_num.second = pair_num.second % mod2_num;
#endif
#if 0
        cout << "(" << pair_tmp.first << ", " << pair_tmp.second << ") * " << num << " = (" << pair_num.first << ", " << pair_num.second << ") " << endl;
#endif
#if 0
        //snprintf(buf, sizeof(buf), "(%lld, %lld) * %lld = ", pair_num.first, pair_num.second, num);
        pair_num.second = pair_num.second * num;
        while(pair_num.second < 0)
        {
            pair_num.second += mod1_num;
        }
        
        pair_num.first = pair_num.first * num;
        while(pair_num.first < 0)
        {
            pair_num.first += mod1_num;
        }

        /*
        if(pair_num.second > mod2_num || pair_num.first > mod1_num)
        {
        pair_num.first += (int64_t)(pair_num.second / mod1_num);
        pair_num.second = (int64_t)(pair_num.second % mod2_num);
        pair_num.first = (int64_t)(pair_num.first % mod1_num);
        }
        */
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
#endif
        return;
    }
#if 0
    pair<int64_t, int64_t> num_mul(pair<int64_t, int64_t> &&tmp_pair_num, int64_t num, int32_t m)
    {
        //snprintf(buf, sizeof(buf), "(%lld, %lld) * %lld = ", pair_num.first, pair_num.second, num);
        pair<int64_t, int64_t> pair_num = tmp_pair_num;
        pair_num.second = pair_num.second * num;
        while(pair_num.second < 0)
        {
            pair_num.second += mod1_num;
        }
        pair_num.first = pair_num.first * num;
        while(pair_num.first < 0)
        {
            pair_num.first += mod1_num;
        }

        /*
        if(pair_num.second > mod2_num || pair_num.first > mod1_num)
        {
        pair_num.first += (int64_t)(pair_num.second / mod1_num);
        pair_num.second = (int64_t)(pair_num.second % mod2_num);
        pair_num.first = (int64_t)(pair_num.first % mod1_num);
        }
        */
        //snprintf(res_buf, sizeof(res_buf), "(%lld, %lld)", pair_num.first, pair_num.second);
        //cout << buf << res_buf << endl;
        return pair_num;
    }
#endif
public:
    string longestDupSubstring(string s){
        string longest_str = "";
        string org_str = s;
        string substring = "";
        bool is_match = false;
        int substr_len = 0;
        int j = 0;
        if(s.size() <= 1)
        {
            return "";
        }
        set<pair<uint64_t, uint64_t>> sub_set;
        int min_win_len = 1;
        int max_win_len = s.size() - 1;
        int mid_win_len = (max_win_len - min_win_len)/ 2 + min_win_len;
            //        high     low
        std::pair<int64_t, int64_t> last_hash = std::make_pair(0LL, 0LL);
        std::pair<int64_t, int64_t> last_begin_char_hash = std::make_pair(0LL, 0LL);
        std::pair<int64_t, int64_t> last_begin_char_base_hash = std::make_pair(0LL, 0LL);
        std::pair<int64_t, int64_t> tmp_pair = std::make_pair(0LL, 0LL);

        char * p_str = new char[s.size() + 1];
        strncpy(p_str, s.c_str(), s.size() + 1); 
        for(int i = 0; i < s.size(); ++i)
        {
            p_str[i] = (p_str[i] - 'a');
        }
        //s = string(p_str, s.size());
        for(; ;)   
        {
            is_match = false;
            sub_set.clear();

            last_hash.first = 0LL;
            last_hash.second = 0LL;

            last_begin_char_hash.first = 0LL;
            last_begin_char_hash.second = 0LL;
            
            last_begin_char_base_hash = my_pow(26, (mid_win_len - 1));
            
        
            for(int i = 0; i + mid_win_len <= s.size(); ++ i)
            {
                substring = s.substr(i, mid_win_len);
                if(i == 0)
                {
                    last_begin_char_hash = last_begin_char_base_hash;
                    num_mul(last_begin_char_hash, (int64_t)(substring.at(0)));

                    for(int m = 0; m < mid_win_len; ++m)
                    {
                        num_mul(last_hash, 26);
                        tmp_pair.first = (int64_t)(substring.at(m));
                        tmp_pair.second = (int64_t)(substring.at(m));
                        num_add(last_hash, tmp_pair);
                    }
                    sub_set.insert(last_hash);
                }
                else
                {
                    num_sub(last_hash, last_begin_char_hash);
                    num_mul(last_hash, 26LL);

                    tmp_pair.first = (int64_t)(substring.at(substring.size() - 1));
                    tmp_pair.second = (int64_t)(substring.at(substring.size() - 1));
                    num_add(last_hash, tmp_pair);

                    last_begin_char_hash = last_begin_char_base_hash;
                    num_mul(last_begin_char_hash, (int64_t)(substring.at(0)));
                    if(sub_set.find(last_hash) == sub_set.end())
                    {
                        sub_set.insert(last_hash);
                    }
                    else
                    {
                        longest_str = org_str.substr(i, mid_win_len);
                        is_match = true;
                        break;
                    }
                }
            }
            if(mid_win_len <= min_win_len)
            {
                break;
            }
            if(is_match)
            {
                min_win_len = mid_win_len + 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
            else
            {
                max_win_len = mid_win_len - 1;
                mid_win_len = (max_win_len - min_win_len + 1)/ 2 + min_win_len;
            }
        }

        return longest_str;
    }
};
}

namespace Official
{
typedef pair<long long, long long> pll;
class Solution {
public:
    long long pow(int a, int m, int mod) {
        long long ans = 1;
        long long contribute = a;
        while (m > 0) {
            if (m % 2 == 1) {
                ans = ans * contribute % mod;
                if (ans < 0) {
                    ans += mod;
                }
            }
            contribute = contribute * contribute % mod;
            if (contribute < 0) {
                contribute += mod;
            }
            m /= 2;
        }
        return ans;
    }

    int check(const vector<int> & arr, int m, int a1, int a2, int mod1, int mod2) {
        int n = arr.size();
        long long aL1 = pow(a1, m, mod1);
        long long aL2 = pow(a2, m, mod2);
        long long h1 = 0, h2 = 0;
        for (int i = 0; i < m; ++i) {
            h1 = (h1 * a1 % mod1 + arr[i]) % mod1;
            h2 = (h2 * a2 % mod2 + arr[i]) % mod2;
            if (h1 < 0) {
                h1 += mod1;
            }
            if (h2 < 0) {
                h2 += mod2;
            }
        }
        // 存储一个编码组合是否出现过
        set<pll> seen;
        seen.emplace(h1, h2);
        for (int start = 1; start <= n - m; ++start) {
            h1 = (h1 * a1 % mod1 - arr[start - 1] * aL1 % mod1 + arr[start + m - 1]) % mod1;
            h2 = (h2 * a2 % mod2 - arr[start - 1] * aL2 % mod2 + arr[start + m - 1]) % mod2;
            if (h1 < 0) {
                h1 += mod1;
            }
            if (h2 < 0) {
                h2 += mod2;
            }

            // 如果重复，则返回重复串的起点
            if (seen.count(make_pair(h1, h2))) {
                return start;
            }
            seen.emplace(h1, h2);
        }
        // 没有重复，则返回-1
        return -1;
    }

    string longestDupSubstring(string s) {
        srand((unsigned)time(NULL));
        // 生成两个进制
        int a1 = random()%75 + 26;
        int a2 = random()%75 + 26;

        // 生成两个模
        int mod1 = random()%(INT_MAX - 1000000006) + 1000000006;
        int mod2 = random()%(INT_MAX - 1000000006) + 1000000006;
        int n = s.size();
        // 先对所有字符进行编码
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = s[i] - 'a';
        }
        // 二分查找的范围是[1, n-1]
        int l = 1, r = n - 1;
        int length = 0, start = -1;
        while (l <= r) {
            int m = l + (r - l + 1) / 2;
            int idx = check(arr, m, a1, a2, mod1, mod2);
            if (idx != -1) {
                // 有重复子串，移动左边界
                l = m + 1;
                length = m;
                start = idx;
            } else {
                // 无重复子串，移动右边界
                r = m - 1;
            }
        }
        return start != -1 ? s.substr(start, length) : "";
    }
};
}

int main()
{
    //Official::Solution s;
    Bi2::Solution s;
    Official::Solution s_bi;
    string str = "uirqkccmgnpbqwfkmplmfovxkjtgxbhwzqdlydunpuzxgvodnaanxpdiuhbitfllitaufvcmtneqmvibimvxmzvysignmsfykppdktpfhhcayfcwcrtjsgnyvzytevlqfabpjwxvjtfksztmdtrzgagdjtpeozzxppnkdbjayfbxqrqaefkcdbuvteobztucgdbcmlgnxldcwtzkvhwqxbsqlbsrbvesemhnbswssqvbiketdewfauvtzmyzrrqslzagjcyuznkpkgpkkinldxcjtuoumcbcttabfuzjbtoqjqbpnsemojbtctvdmobnuutcsfmhkrbwkmpdcdncqizgtlqekvqophqxewkpxpkrgjivrtarxtwbbfhfikbrdwohppyiyyztopksdmxvqiaafswyjfnlwntldwniypzaxrscyqfrlqehqgzaxxazfwtwjajsrmwuerdqklhwoqxptcvqoqbjwfqrewirtcbskmkaqgtcnxnsqmwgwjxruhyyjtbuivvepnxiwjmtlrvexjzevctflajibxkvmbzdfwoqobmhstgpshtxitwttpkdvfmfwtwsazfgzwbtmqrowrcesyyeuwunodesrzbmjbxnchaqptfgqlknuarhgnsbwnucdhckpbwhtwhejivrmuccbwnyenyvonquscneswngwbkjysxvdwbzymwxcrnexrxhmuwvycmsiazmqavgmyurbcmvdjplloidbzacunerwobvaxsromiiwzqxnrsjpyoacfxcmmogmokhpmhxzkdzmpjcrgaeihdhczrmxmfurjatuwxriiwtfojwvkkybcdmwayhnzrnqrynwtrvmtgtrxndlbtlhyzfjtbtvqujjuwpibuonuwjdfvnhdqqzlmwwheztjkrrzrroogovapywxkjsccjnseanhxijybintgbjwlkmdzuoeclfqatffgjvcbujovunnauprhoocxzghzvsmuyhsl";
    //string str = "vcjwaksfwsykahshcddgkopaeiwtuspqkyduwhugimsegplvtuvrttfpzoxmvexkbqamyomdfhqftpenrjivntrrzseejrofenvdxviduskmfcqclvcbidskfgyrvvcqbsirshjcluzkjhrjayogeaixmqvdfrujwymeynkdccenlnsyvqxkcqvypclchskxqpshwpmswmgafpbdtiggcjcsoebeluyhqsdccxmbxndxbujekwwmclpjpzqxuqwzrogmeqzxoosddqwsuyhbxhvelbbnuvtavsavimxuahktntzuqbxbkquozjsvdgbvuybxuidchmbhiucwaijnocewwdgrpsaclqmkihutrbugzjemkctyrlaghimhiifwoctnpgkyjcuzgsjfucmekogxnqbuoxbciplsefvbiqlrtvdaotxpwwxspllqdzjdwhxhasvhxhfgsnkyesngvwavuatzhvqmalqwugotifukyvqsrhubddjrvwegvjvgkhjlidvvwmzeqhqichzyogfzzpomakemujrterqlboqljewxnawwvgpzahwzvzbxcfkiaddddikbvtvlrhvtlzbtdkmcgjxulhsjmuwklhvcjrdxtuirwmxunupfibwdupkgltmpbyurcuviufgyfcctjhasdvthgpztjurydisxdiiwywrdjnmniqytleujxnumqvcohrgjssdcdhpszqojpuxkylczjyqrvetmsdplljfjzmycmgxlmpkorgpzgvrvklnuumflmtqbasqfuadqjsndookyzdappehwapwispgmiicxtiuuvyygzghxvkwavlukhbvjqrewvqcvlbsfgtygxfcwrhomjvwpdxvzbkpleoupekpxcvuvncececuaslnfsckzxotjzuakbyszvtoclggvxjhcyddycthewfxmnzlldxocnekdreivyxcyuivpsovdrrdvjddzacttireuyusphqxokmu";
    //string str = "banana";
    //string str = "okmzpmxzwjbfssktjtebhhxfphcxefhonkncnrumgduoaeltjvwqwydpdsrbxsgmcdxrthilniqxkqzuuqzqhlccmqcmccfqddncchadnthtxjruvwsmazlzhijygmtabbzelslebyrfpyyvcwnaiqkkzlyillxmkfggyfwgzhhvyzfvnltjfxskdarvugagmnrzomkhldgqtqnghsddgrjmuhpgkfcjkkkaywkzsikptkrvbnvuyamegwempuwfpaypmuhhpuqrufsgpiojhblbihbrpwxdxzolgqmzoyeblpvvrnbnsdnonhpmbrqissifpdavvscezqzclvukfgmrmbmmwvzfpxcgecyxneipexrzqgfwzdqeeqrugeiupukpveufmnceetilfsqjprcygitjefwgcvqlsxrasvxkifeasofcdvhvrpmxvjevupqtgqfgkqjmhtkyfsjkrdczmnettzdxcqexenpxbsharuapjmdvmfygeytyqfcqigrovhzbxqxidjzxfbrlpjxibtbndgubwgihdzwoywqxegvxvdgaoarlauurxpwmxqjkidwmfuuhcqtljsvruinflvkyiiuwiiveplnxlviszwkjrvyxijqrulchzkerbdyrdhecyhscuojbecgokythwwdulgnfwvdptzdvgamoublzxdxsogqpunbtoixfnkgbdrgknvcydmphuaxqpsofmylyijpzhbqsxryqusjnqfikvoikwthrmdwrwqzrdmlugfglmlngjhpspvnfddqsvrajvielokmzpmxzwjbfssktjtebhhxfphcxefhonkncnrumgduoaeltjvwqwydpdsrbxsgmcdxrthilniqxkqzuuqzqhlccmqcmccfqddncchadnthtxjruvwsmazlzhijygmtabbzelslebyrfpyyvcwnaiqkkzlyillxmkfggyfwgzhhvyzfvnltjfxskdarvugagmnrzomkhldgqtqnghsddgrjmuhpgkfcjkkkaywkzsikptkrvbnvuyamegwempuwfpaypmuhhpuqrufsgpiojhblbihbrpwxdxzolgqmzoyeblpvvrnbnsdnonhpmbrqissifpdavvscezqzclvukfgmrmbmmwvzfpxcgecyxneipexrzqgfwzdqeeqrugeiupukpveufmnceetilfsqjprcygitjefwgcvqlsxrasvxkifeasofcdvhvrpmxvjevupqtgqfgkqjmhtkyfsjkrdczmnettzdxcqexenpxbsharuapjmdvmfygeytyqfcqigrovhzbxqxidjzxfbrlpjxibtbndgubwgihdzwoywqxegvxvdgaoarlauurxpwmxqjkidwmfuuhcqtljsvruinflvkyiiuwiiveplnxlviszwkjrvyxijqrulchzkerbdyrdhecyhscuojbecgokythwwdulgnfwvdptzdvgamoublzxdxsogqpunbtoixfnkgbdrgknvcydmphuaxqpsofmylyijpzhbqsxryqusjnqfikvoikwthrmdwrwqzrdmlugfglmlngjhpspvnfddqsvrajviel";
    //string str = "uswlzarxlolqxrulrtsvroiyurnuyxnhayjogwrdyjwqndkbpdixvhneshkzcwhkpywlezetcijyuadbnjtccdowaanowbueroqdszwmpahxujfftjfjgobmktytaragofkxboannlnuohnbenvqhrrgivnhzpxdclltbtiknveitptiwiqhgjnsaxjgkkmsedwzftgyxdbkgwixgkskmdopdzkbrnzydeoapixrpbqlrnbdizjcylgcwgusvaogusefvigsovhrrlknacpdpeagkdjefrdpbfejulubxwlskrutbikwnvceulibpvlawcgtxuyfehkpygwjruadaahzjxggxtcyszyabxdypnogukfphmcclricytktofvfayeycrtvkvpqpedylhqfkkqlulqkuqxtvplctcxhyongrubkzeoopqxphqhjbmbpaawbzadurxeixzlbbwvhwusfwbaxxicapmxphiqewpwukfihacnyomethcjeiauvcqxyucdfzkxjehtdkinoklekpfliuyvjxhpcxvstqzwbpwdkakjnazbzpnhkmsrxvdmmrrjspzcbstwttgwybjpzknmzdpelpoeabfocymgqwsxzyswhdxqxgoyglgnqdvgmtgwfyyoeagpqtaimjfeeunptsrxwajksdbqposjpvgkatoojkxxyvpxhqxvhkqxaeojuqozaokynrljqpkatfthwxlrxyubeqkehsxvhrhwetkqhdvekxxwkprrydcqrbpgaspemjyrrtlvuvzxyioiyvzcsgljssqskgqwxhrdnblrrzfmbifmqjosxdkgvxgpzzhjatcgvmtkvrxswghbsawmqdddmgcwkgzqkmxuayaglnurwoaaifqoyytvyagvtcsbmdbbmnnndfkzdcahvqivdacvrntqikpdlwbvemqxxeyzohhxupexktowslnzolbayffdjkcsivykycoqbidipouxevjfvpyfhdudqtstjswzlwhmbccfjfuyagfyiimhejkbzjekpjaldujxqoungvxaegpumjkynxnfcemurxtaodpmlssdgovflprpkcbnebdkfozolhdqmmhdqlrgbysovzrglwfhvxiqhlpnbfdkwsyaouwtuwhgzfltbybnigunnaxeiwmqurqxlmickwiopejujcyyscdmcvlmmhdptninxdfqwppztivpnvjnaidcfudjfaagrgyuplqnjiicsiayrdbhsvsqoxyttovomvadkcddfiimpbyczccysfbgvefrouuhacijstanhtonrorhsxgfxjzcmhkqawucytsdebvtdbkufjakgacyyscuifqfdwckqxoddfbyvqxzjtgnlwuulhhqbltjehrcugaiifmuwpshwsndlpduhtaargbzamwfjxxfjbdaptkyxbwcisnnpbrqravxlgyxkaiohtxotfsrqiijccivuyjhuvzxdspdrqvjranshaksxprasngplvvmbzehudeersaoplloqghhygcshhjwibrjtxyvbwvbvviqquqgmytzywjnjhsdhudlqnycqrmqsxbtxxaekluncstselbalvvnghacilvzmardzvfqdxjhmmrslzzymwkvzixhvgulwimdfkaoslnyxfnanioafucprzkxpzzrdenbjhypalzgdhzkezejgpbevprsluquukymdbapevmuxbgcswjwwdrecmsuxccwonaeltscntzupapbaaywhfxkmquvtdbahewivliyqrohpervegyxlretyagmegtwdhvfsotnazgexgecnlaseijheotvozbngotvpwjgoehzmusviztwlgpvlfyusdlkoaqywhpimuvzkgkwwolfppxmmhwrokfnatztlzbzuedslubajohsbtudpjhuejdtcuujojhyeemtypcuuvumgkdudijwmygyiqpzpxayuxqdfanxhiookutfmtwpjahtirwgozfzwftbazrmiionqdpvsmjgwhvfjrbazsoqmfczueefzjhxseaszbolxkxieszftcvvmzicqbkpuvgpztfjtugarjdfewpiddlluhqbgityhjytbtuemfmssydpivbhvnlhhrcsumlrqeqgjhupkkrdtjhsgjqrpzbsbbkegvwxmbrtkeuejrlgwwbkirgrvqhddnazuocjpaajkbfcevwywkhqyypwcgosmvmpoysgatglbgbkbnscsemdcshxjyguxbnxfmslenyykiyskvknemlxzwdwrnwqbtruyqnuzqrwfrpdinooujtpefkxoeuykmrkexogocuvnokxasvhpbcavyeauraeqgdykyhtxgicxdemwszdzaeaesmdhnibxukmtmxgznfhwlojormocpxzykragnycqgcluccnabprjdgqodiisunbjbzwhvvcudoprgzagngfolnaybhtqrumaoxppiyesfzfysbgrnuprpimpkdtsscratomkqvpzlkdengrmttplielzyqrzpiaxscpqdnempzmkulenvbdcladybwmqkryryvemrvihvgwxkklwtzxsmiryebnkwszevuciehdxncxqgkhhhnnxtpcakghpyipjxuqbwqjznubyyjaowrctsvqzdcdopujgwyhtkadoiksxowebvopgopcsepgybxrilshqwwuzvkedfgcgjllrhichvuxyuxkeaqwqqmcjbragfrtipgualwddxfleddddmucsacnzmlzggdqpxqsdghtghnhvxrlvteqcjkluiggcbcmnatoweadbykzyepnhuewyxlbjpbxhmvefjzqglaotjvzxkdxozboldnjbwjirgavlxsudakqxyxfrzobehohdammwbzclnyxlhpmlpowvencvzzonnejvpvjtsljlgakohgfoswahjfaufpuphbtbgdbrefivaomlsqubvgmkdakrxaxteiwbggujydivouymdhsyccnvcbbflmoycuktzxcznxtawnhnnwomhyxdhduuppjffzuhbbvwkpjxfvnvobgtltqsggkjyiuciuxnokhrdcpsdezeqmemduqwgutasohydwcsosucvugemcgnyjiirbkxykzxbgbvxvsbcyfyraaspbyfhervypiywfmdbjewwnjhqyaihgrmmaucaxptyozifytdjdlwuackmuhhssnsppqjnlbjgajxtfyagliremtyxwvstzmzhdzfiikowtcohtasaifqwvuhibzjwjlcvgvvwcksiepfudxvummhevvvmfmvfxmpxjpedysczfbbckagpmvovmakeypzbhnnojdwsadsrvvjltlmokfdrduushtlxgqwnkacvuafjppxkboqtlysgcgnuiinuojfhbeqtfapkziovphakuprnummcsdkvhuizsyfqrycusamhsyiwrwbycnvaxmmvqmbjmfenlgtqpdzxjqgsonyuqeuxowyohybiohkudaguntdpuqbarbigriigzrpfvwoommqhnskcymvejyfsikugyqxdsknugpeckxqhktwrmflhpicubahcgspnkzuswvqrflsulqikjbjkmeoyqdkwxtnrqmutpnvkooglifsyjhevmavccesmihqyroluvyyxktzylwhnquxlgwglvlchedcasgrontsmkjurtshubefuwitpltihphrvvotyxgdgtsjysatkavvilykdgsytsifiliddvusfxdsiowhlxoxwbjhkemfneregnfcixywkkiytsuxnccybamneoaaasabzykyhxympthywwbqjgczykuyimagjxnczhdtxyiyymzjybcomwrzovsqhfdtoxpjpjmjvnyeeixtsrttxsvszssjpaqklaczvbjeyargimbympagsksrfhctrhyyomozolhrbvgzxtuvgbdabsyyfrkkdhrwscsitiksjuocmhvyuweoimuibgcuxgkpxjbfatqqczoqyumyrusqsxkwihwmhjedbpylikrkvikthctcgjgrjmppljvugmkwczgfstnqbylwimwqokgqhklcvyldqlzuspjxqjgqwzpqefzgcmoakicyheklekiqowlnupsknlykmnmheqzafqlkwuidhqarfmwfmncgoswvweutnjhdpjrdxzagdfqpjupbchaffboucrkwdtdmraclrgtyrfhszsfaaraaovkokhqwbwhgeyimifyebbupxujhhtmieiounacuxmxlmewyrmbcuxglzoxhnrvalgocgaqdpavikirbehgtlybziudmdlgsymegqktpergknqmpnwfzkbqacdvrujwhmdwfuczoobqtrwjyilypxrrenjchvirxwasuducuawymajnfnyxxtgpcgrdodqndamaaltcnmlfrwxsilhvgskjtfnmwnpodorjjpqpozrhyccksqnktchunbflujfldoqpftodvyaccbdwxhzzihzqrgigqloosobrpnjvruouqpmtmksmlupjihjpqrncvjuascdwazepynhfeehrwgyxjdgybegdajuwzjhgrzvkpshpsqeoxhdfnhnwbuhsaoyumeunyznabqtwqbkyqooyzajtemzhoertrzvkfjjxfhddaqyvqvrqltzwtgkdlvpowhnyfdtcfwazxuaamguczphwqwznjhvbgzzmpxybfwdezclmecbojukvrmaxruvxmshdtcsjohzgpoqohlcnpoxvklsmmoetyvfebenroejsdgbvrxnuswsnejgwuolsdqzpbogynqvodsnbccffpnnblycziedwloxidhjlbpvdxzpsgqxmvynrcjleyldvepwtpvmnroebilexnnfebqrctrbeggirnigxauyxmfdyumngsdcexzqwgyhneeyshjfpxyvelhmdgqvjnwsnuuorkwbvrnzfqxgaihsktkxregdiungexuoqaikcioohsricytddadbjkbpuvprbzmxbpxwzdgaotwpinrdfebymilllpttfebctlnrhpxdnyyczkqesdrgauysgutcmushvkdsncpwdovzyhmqxnyxzxgilzmprmltduvmbjizazgctilvpnosumbanzxqrewrhncoxvrwttdgpblnbxdwkgevhguuxmulxrqalfqcttfgjtmvtfckwkqzhidabfavaqphvlfwtytilvunzdnxisqarzbnrpuhlsjlqbcdtgioioopisesfrbslyqpwkftdbyrfgyigaappfghswzksifhrwbfixytdyuaqylsgmseptwjaqmpompzeqactkgsygalrwpdzankvcuxufrsmmnoinhdjwqcywtkgpuxzjanpiooorghszsptudnokiidqhgxmqekhuoupurwnorcnjrtsjiqyvrpjxitufmsilrwlkxnuagljvvflmudqkdqqlzvyklpizafwzjpmvburpjdvgcousfceynkzkeggpsswefwhmsttpjdlbqptmojyblxbmgzjqmotnhsmortjnhyeerrsiaosqnaxhovxxojuoctbvjvcnlfxyjvpfzddhcpkimtkhztfsagrleovjzwnfrnwzxtsrewjmrfvqenalooplzjicozoyyecvhzfrargwqljhjknvefhfnxmyssimyvcmguqdhmsxkshhvuobenlgmfpnaoskdzihlrhvfyoekdujmrkgeyrpgdkqbfulqggvzboxbpgnvxparetxgjgyiztpgbklsbclmhahtvnkqugqjuerliyuvvhbecrgktbznsnxmaebjkbwhbnqirvkzzdtdoynbrnxqbivafzszibpduxiebotuphnipiadqulgvowfpqhstysawzdftziymukygmrtdlftivuoburfyyexngsjjlcwnqdbjlpaaseixlwraarkenojbjhqxkwzyvetyeogdqjyifjlqczlajcrlcmoslaowfagpbnyckdlmwrfohsukaixmgrkqjebrkljwiwktslbdawgfjrqzzmnrwbuygeamkdxutaabkdvavbuwzebghzxlciislnwyowludkjtxikxdadkkixxbtabxnzlobnoyadbnjomksddvgjrcfudwazrzptkkryqgovlciweuprrohotowkdupbazyocsanlhprydovbqwweeseorekcxaxxmuqgemnctycjchiuwetbycqzwygmdewujaldjogtsdwugmszyysysuygvadwshotmwlytemrcvsazmamqzijupkldjknndjxnpirulgrzzexloiucxwfqbbsdmlhujkmnxzaqqrrmtjywkkuwsqokhzeznzybandlsbwcoaiibsfufnvjqbrzggqfrvzpiaewtpfiencojahcljdubuqmwzxvlnwcewzgtrbvxxilnyqdscrmvavdmxotnppwwzilanwuxyibsfrarmxjexouwfvidgdyzaletybcwhwqhvrzhggfhfyeekfthinqlnfkzlerwedbnbotwoxxtjwkvmfliubretmvjvnmxvcjjcdwmmecrixhivokbnouzsdtratejqmazncvodkooecbnxgiuvqamhidiytynowdoktjfuihyvkjnjngtelyaytuoolpevjknpejejoxzoersmzkfdxnfyduylzedmkozsylcxheohpwjcdvyrhejnawvauzwwufatqkmundusufxvudfottxyhokmpfkjqxwbivsyppmtlcbdpgqeaszzgclaerigzldbtprxjyeixgquashtpokiyblarydsplvadcagmfttwbuslstlryztyljvdpcmzdufddneklbzjdbxvcflhmihslhjxsnysmuzjnbiwccvikgbndpdcymrvdubpwvnxnfxyazdnvmlhaisrbkpvaqhtleiezbbzfbbtugkrgocqzqnaeogzqjrrukvtkkejsmmqticbueuxxgwfxrljwykqjjcbbdypeihcbhspguiluyunyhjdolxhpwcawxofreizvbqvlykkmsutyzerbandsijhcpzllphpldxsovybcezefgzyoxlnqzypavpdoehqatqtokstkkneqyqcpggysvidzujuqvmfdyfhdsvemqaozxifackqqfavizltygghapbqataolckbineefqrunvdqwigzvjiwbujknolhbcxfgfqbcjgddlsvnzbfflgbfhbennlonoosuleuolyhrsgryiefmvitbfcnqkvyckfcpwistwcflpsqqpfpedioinrlkxgsbfzhtxtjzfdjypjjfkuqfplsghtjcqwukfxdmbsaxoezwctuvjnvrldlzrngmgbhsuqldyxaoimomtpipnpekcpqmgslkhoddkwdqimfqkgazfrdwkcyvqnigdikqzsfgvmlyyjnpaavmmnjfxipfcwuipcxfpebourxbsovfvwdwtdxdispbzuzbzwyjpskaamanirxbqnntrjjnjnkdonxbjofwpruxfggxfocvjvdaapflptpwmuujlidipagdudwqoqorspwqoeupounquwingejjhbxwwqgcbzfmodlvpptsqjoqliopitivbrxfpqqzrjppftuvyxieymksrrebzalipyweobgmpzazrzigsmxmdsxbrwewungjuspckdtclcseeqfutzelhelyjnnitviwksblwgyjvyildeivmymlwqsvkueecfdffoavnspdgeuqivkizubcxfucbrgiymxyjrpdumfyvrvqakkzsknsfrnurdavxoquncgppcahxrwdsbvzhhsxtdwadrcjexcnamhesnskazwkzslujboubzueoqgxiawjquqsavycnyptutqfhdflpjvlkkaufypqbkfkqlkuakuvotpxdmrsrscatmxgkiwlkxqactfikzbqmeljhhlpycgikltdifkguvnklufmlmymwmgnivnzqolwcyyqgmufcdfxomwfhykyvjsjtrwbwfprcowifemayhclmhfhdmacjdjbjbmupqwmcnatovvfxodiqwzrkwfzabhfkcknncirmjcqudafaqizduwzbtblqzxxwzzsvcvatilvcbpljrwyfbexmvnejtycgjymajunvlgbizcxbgeigcvcprhmuhlejpzyyhvjcwiuqbdagbqbqzfhvgzeyivksbpxmhqvtncynsyzgeknjrrhgcfnhihumgxbzrefzgbvaxvxhedzvdzebmxdzgzifyfyyfcluccaxzmbylktrprawebqgmukxgtlouwcruomaogosltkvevyolusgitgqyqcbryhxwtonkyehpctiqwvdatpfzljwwtlnxrbqdssalqnhefzaoebzmrbardwbmsfoxcsgnajyruawypwqtqxwfrhqwsusyrckghuqjciofzfcfsddrvnkhjhmmtsqpiimkobwlhdmsinglfwuutcepcoianuudwrdeikmukrdajzsymarepqbvuqcjegwyharjqphmnibwzucoxsezkvgownrcgjsmttquiahqvywdftsmpvyofbwntkgkfplxnetgmdfawjkpaigitkfveurgwzjsgwuynilnmbmdzawsrbtetpmtipqpalvatzhaihvrjvmseyuvpowzvnsdekkgbdcngnjykryoiqyeecbooghnridvykantprptapkidkpgdqvoafthbupeglxlumyyxwykgvbjcamwqwbkjluqynygybwztbqraafrarrpfodreeeykixkgrolgqjdcqc";
    //string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    //string str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "abcda";
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    //string str = "nnpxouomcofdjuujloanjimymadkuepightrfodmauhrsy";
    //string str = "polxtvqlurgobbzbjcjsupskvzmtuveuavrzcxaifmdwqjbuejdasuxcvsupqnucorfawncjqkbakilhiekavhmsjbtlsfydijafxhgrgbsswtnvdquwokcliaxevairergwdtndsibiulqiutkcwsqpzuyypnhiowgvkkdbpkoyvgwyuqcokjnxluamwnuhqjtaossezwxvkpdkqcleqjkelcludtbigxkueupnxjncrbgvdrsdpppqqcopnwadqsxkvlkghfmtvdeygpyxamvxhmmaunxskgnenobvnzizbxwrjeedisrgzykoaidiffzqzsmirxkvfwmtifywamcpxziyjohcudzelgbmdgiaqwnzdbkwbhdioiokaivzlzscshrvbmggdztjuimribrgmdlcctvldbcxwpqnqbkzrcayqdqraobqcgoxxocclasphcjcydpkgkqhrmmxtklpxfxnrgnzczjxanaltnjhwfatgryqhcllemgqcchiagizpdgiqioqyhrpattutmuotrcwtxvdqzzsomofizebbqrgwruydyawsssjkakjpjlzmfhmjetymftxrhilpcgfqyoohyydnodfortlkeoncmfkdraiqydxcodyapjaxumjwczwmthrcecfgsswwtnyqurvggamjbsjdzmcuyefwnsrnhhpusfdsxbsrsrywbccullupdbovnmzluqsfdhqbef";
    //string str = "abcdab";
    //string str = "djpqwlrroqeuwwqgxnvdftzgsgnmpnhnhezixyhlydjjekpeczwtguowubfjsyohxaihmbjzfchmbnppouguvklmiaqkgomqzvvfubklwexbnzbdkvtxjnpzmfdgomvvsekluemjqaatkbhklusgxbezjghoddwcmirwrnnsgzjzwrnfyqgjylzgwhwipinohhzkywikevsqurnirnmmkgwpgvdswttwpingslbzxzsodqvlluqetfzfzbdhilaugrxewhomtwzjyldxzwtxmufbcrxtqfpcqscbbstplqczhumhedcmmgfkhdyetexcyrlvdrkgxzsncrpoomtqwnwozbteedjozikggwkbexbibruqdpekpjpzzymxpvtsderhjwxvyfahximykcndxskcjwewnfcbvymijwkrisjtzyiegysxpyfdrblxjquytzgvajmdvylemhqcctivjzmkdojbpvucgswycfnjkyoqvzlufphsrvhcbkxamqmaoveycykirpboguhrimemgkkbdmkyvalkpmktlkhwtaafuphdksucgianjkyztzyrndfjhkemdlgnmbucmqqyvjmzqlmgerhvzdtbjsagisjsqnrzqlmimtxumlngktcptgpcevpybghuycisxbemgpwptokdqvzp";
    uint64_t t1 = GetNowUsecs();
    string longeststr = s.longestDupSubstring(str);
    uint64_t t2 = GetNowUsecs();
    //cout << "Spend time: " << (t2 - t1)  << "=>" << s.proc_time << endl;
    cout << "Spend time: " << (t2 - t1)   << endl;
    cout << longeststr.size() << " => " << longeststr << endl;

    cout << "===== Bi ======" << endl;
    t1 = GetNowUsecs();
    string longeststr_bi = s_bi.longestDupSubstring(str);
    t2 = GetNowUsecs();
    cout << "Spend time: " << (t2 - t1) << endl;
    cout << longeststr_bi.size() << " => " << longeststr_bi << endl;
    cout << "Equal? " << (longeststr == longeststr_bi) << endl;


    //for(auto iter =  s.pow_cache.begin(); iter != s.pow_cache.end(); ++iter)
    {
        //cout << iter->first.first << "^" << iter->first.second << " = " << iter->second.first << ", " << iter->second.second << endl;
    }
    return 0;
}
