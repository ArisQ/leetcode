#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
    public:
        int threeSumClosest(vector<int> &nums,int target) {
            if(nums.size()<3)
                return accumulate(nums.begin(),nums.end(),0);
            sort(nums.begin(),nums.end());
            int result=accumulate(nums.begin(),next(nums.begin(),3),0);
            for(auto a=nums.cbegin();a<prev(nums.cend(),2);++a)
                for(auto b=next(a),c=prev(nums.cend());b<c;) {
                    int current;
                    current=*a+*b+*c;
                    if(abs(current-target)<abs(result-target)) {
                        result=current;
                    }
                    if(current<target)
                        ++b;
                    else if(current>target)
                        --c;
                    else
                        return current;
                }
            return result;
        }
};

TEST_CASE("3Sum Closest") {
    vector<int> input={-1,2,1,-4};
    REQUIRE(Solution().threeSumClosest(input,1) == 2);
}
