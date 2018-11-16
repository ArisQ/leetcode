#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include <string>

using namespace std;

class Solution {
    public:
        vector<string> letterCombinations(string digits) {
            const vector<vector<char>> letters={
                {'a','b','c'},//2
                {'d','e','f'},
                {'g','h','i'},
                {'j','k','l'},
                {'m','n','o'},
                {'p','q','r','s'},
                {'t','u','v'},
                {'w','x','y','z'},
            };
            vector<string> result1;
            vector<string> result2;
            vector<string> &result=result1;
            vector<string> &next_result=result2;
            if(digits.size()==0)
                return result1;
            for(auto i=letters[digits[0]-'2'].begin();i!=letters[digits[0]-'2'].end();++i)
                result1.push_back(string(1,*i));
            for(auto d=next(digits.begin());d!=digits.end();++d) {
                for(auto p=result.begin();p!=result.end();++p){
                    for(auto i=letters[*d-'2'].begin();i!=letters[*d-'2'].end();++i)
                        next_result.push_back(*p+*i);
                } 
                auto &temp=result;
                result=next_result;
                next_result=temp;
                next_result.clear();
            }
            return result;
        }
};

TEST_CASE("3Sum Closest") {
    vector<string> inputs={"23","7"};
    vector<vector<string>> outputs={
        {"ad","ae","af","bd","be","bf","cd","ce","cf"},
        {"p","q","r","s"} 
    };
    for(size_t i=0;i<inputs.size();++i)
        REQUIRE(Solution().letterCombinations(inputs[i]) == outputs[i]);
}

