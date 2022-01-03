/*
   https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/solution/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/
   */
#include <unordered_set>
#include <iostream>
#include <algorithm>


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


int main(void)
{
    Solution s;
    std::cout << s.lengthOfLongestSubstring("21233333333333333") << std::endl;
}
