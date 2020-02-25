#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution1 {
public:
    int candy(const vector<int> &ratings) {
        int n = ratings.size();
        if (n == 0) return 0;
        vector<int> candies(n);
        candies[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            } else {
                candies[i] = 1;
                // fix second requirement
                for (int j = i; j > 0 && ratings[j] < ratings[j - 1]; j--) {
                    if (candies[j - 1] <= candies[j]) {
                        candies[j - 1] = candies[j] + 1;
                    } else {
                        break;
                    }
                }
            }

        }

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            // cout<< candies[i]<< " ";
            sum += candies[i];
        }
        return sum;
    }
};


class Solution2 {
public:
    int candy(const vector<int> &ratings) {
        int n=ratings.size();
        if(n==0) return 0;
        int sum=1;
        int peak_index=0; // peak index
        int peak_value=1;
        int pre=1; // pre value
        for(int i=1;i<n;++i) {
            if(ratings[i]==ratings[i-1]) {
                sum+=1;
                peak_index=i;
                peak_value=1;
                pre=1;
            }else if(ratings[i]<ratings[i-1]){
                sum+=i-peak_index;
                if(peak_value<i-peak_index+1) {
                    assert(peak_value==i-peak_index);
                    sum+=1;
                    peak_value=i-peak_index+1;
                }
                pre=1;
            }else{ //ratings[i]>ratings[i-1]
                ++pre;
                sum+=pre;
                peak_index=i;
                peak_value=pre;
            }
        }
        return sum;
    }
};


TEST_CASE("Candy") {
    REQUIRE(Solution1().candy({1, 0, 2}) == 5);
    REQUIRE(Solution1().candy({1, 2, 2}) == 4);
    REQUIRE(Solution2().candy({1, 0, 2}) == 5);
    REQUIRE(Solution2().candy({1, 2, 2}) == 4);
}
