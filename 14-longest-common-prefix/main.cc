#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(const vector<string>& strs) {
        if(strs.size()==0)
            return string();
        size_t min_str_size=strs.begin()->size();
        for(auto str_iter=strs.cbegin()+1;str_iter!=strs.cend();++str_iter)
            if(str_iter->size()<min_str_size)
                min_str_size=str_iter->size();
        string result;
        bool different=false;
        auto c_iter=strs.cbegin()->cbegin();
        for(size_t i=0;i<min_str_size;++i,++c_iter) {
            for(auto j=strs.cbegin()+1;j!=strs.cend();++j)
                if(*c_iter!=(*j)[i]) {
                    different=true;
                    break;
                }
            if(different)
                break;
        }
        return string(strs.begin()->cbegin(),c_iter);
    }
};

TEST_CASE("Longest common prefix") {
    REQUIRE(Solution().longestCommonPrefix(vector<string>{"flower","flow","flight"}) ==string("fl"));
    REQUIRE(Solution().longestCommonPrefix(vector<string>{"dog","racecar","car"}) == string());
}
