#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Solution {
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

int main()
{
    Solution slt;
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


