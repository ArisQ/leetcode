#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        vector<vector<int>> fourSum(vector<int> &nums,int target) {
            vector<vector<int>> result;
            if (nums.size()<4)
                return result;
            sort(nums.begin(),nums.end());
            for(auto a=nums.begin();a!=nums.end();++a){
                for(auto b=next(a);b!=nums.end();++b) {
                    auto c=next(b);
                    auto d=prev(nums.end());
                    while(c<d) {
                        int v=*a+*b+*c+*d;
                        cout<<*a<<" "<<*b<<" "<<*c<<" "<<*d<<" "<<v<<" "<<target<<endl;
                        if(v<target) 
                            ++c;
                        else if(v>target)
                            --d;
                        else {//== 
                            result.push_back({*a,*b,*c,*d});
                            while(c<d && *c==*(c+1)) ++c;
                            while(c<d && *d==*(d-1)) --d;
                            ++c;
                            --d;
                        }
                    }
                    while(b+1<nums.end() && *b==*(b+1)) ++b;
                }
                while(a+1<nums.end() && *a==*(a+1)) ++a;
            }
            return result;
        }
};

TEST_CASE("Longest common prefix") {
    vector<vector<int>> inputs = {
        {1, 0, -1, 0, -2, 2},
        {-3,-2,-1,0,0,1,2,3},
        {0},
        {5,5,3,5,1,-5,1,-2}
    };
    vector<int> targets={0,0,0,4};
    vector<vector<vector<int>>> expect_outputs = {
        {
            {-1, 0,0, 1},
            {-2,-1, -1, 2},
            {-2,0, 0, 2},
        },
        {
            {-3,-2,2,3},
            {-3,-1,1,3},
            {-3,0,0,3},
            {-3,0,1,2},
            {-2,-1,0,3},
            {-2,-1,1,2},
            {-2,0,0,2},
            {-1,0,0,1}
        },
        {},
        {
            {-5,1,3,5}
        }
    };
    for(size_t i=1;i<inputs.size();++i)
        REQUIRE(Solution().fourSum(inputs[i],targets[i])==expect_outputs[i]);
    }
