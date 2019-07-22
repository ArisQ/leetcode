#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os << element << " ";
    }
    os << endl;
    return os;
}

class Solution {
public:
    void nextPermutation(vector<int> &nums) {
        if (nums.empty())
            return;
        // 找到从末尾开始的第一个峰值
        // 即 *nums.rend()  ...   *(peak_iter-1) < *peak_iter >= *(peak_iter+1) >= ...  >= *(numbs.rbegin())
        auto peak_iter = nums.rbegin();
        for (; peak_iter + 1 != nums.rend() && *(peak_iter + 1) >= *peak_iter; ++peak_iter);
        if (peak_iter + 1 != nums.rend()) {
            //峰值不是最左端，交换peak_iter左侧与peak_iter右侧中比左侧大的最小的数
            auto left_iter = peak_iter + 1;
            auto down_iter = peak_iter;//比*left_iter大的最小数
            for (; down_iter != nums.rbegin() && *(down_iter - 1) > *left_iter; --down_iter);
            //swap left_iter  down_iter
            int temp;
            temp = *left_iter;
            *left_iter = *down_iter;
            *down_iter = temp;
        }
        //peak_iter--cbegin已按从大到小排序，将之从小到大排序
        for (auto p = peak_iter, q = nums.rbegin(); p > q; --p, ++q) {
            int temp;
            temp = *p;
            *p = *q;
            *q = temp;
        }
    }
};

TEST_CASE("Next Permutation - Example 1") {
    vector<int> input{1, 2, 3};
    vector<int> output{1, 3, 2};
    Solution().nextPermutation(input);
    REQUIRE(input == output);
}

TEST_CASE("Next Permutation - Example 2") {
    vector<int> input{3, 2, 1};
    vector<int> output{1, 2, 3};
    Solution().nextPermutation(input);
    REQUIRE(input == output);
}

TEST_CASE("Next Permutation - Example 3") {
    vector<int> input{1, 1, 5};
    vector<int> output{1, 5, 1};
    Solution().nextPermutation(input);
    REQUIRE(input == output);
}

TEST_CASE("Next Permutation - Cutsom 1") {
    vector<int> input{1, 1, 5, 5};
    vector<int> output{1, 5, 1, 5};
    Solution().nextPermutation(input);
    REQUIRE(input == output);
}

