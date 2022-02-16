/*
 * https://leetcode-cn.com/problems/swap-for-longest-repeated-character-substring/
 */
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxRepOpt1(string text) {
        if(text.size() == 0){
            return 0;
        }
        int res = 1;
        unordered_map<char, int> m;
        for(const auto& c:text){
            ++m[c];
        }

        for(const auto& o:m){
            cout << o.first << ", " << o.second << endl;
        }
           
        return res;
    }
};

int main(void){
    Solution sol;
    string text = "ababa";
    int32_t ans = 0;
    
    ans = sol.maxRepOpt1(text);

    cout << ans << endl;;
    return 0;
}

