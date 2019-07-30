#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        cout.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution0 {
public:
    int jump(vector<int> &nums) {
        int nums_size = nums.size();
        if (nums_size <= 1)
            return 0;
        vector<int> steps(nums_size);
        steps[nums_size - 1] = 0;
        for (int i = nums_size - 2; i >= 0; --i) {
            steps[i] = nums_size;
            for (int j = 1; i + j < nums_size && j <= nums[i]; ++j) {
                if (steps[i + j] < steps[i])
                    steps[i] = steps[i + j];
            }
            ++steps[i];
        }
        cout << steps;
        return steps[0];
    }
};

class Solution {
public:
    int jump(vector<int> &nums) {
        int nums_size = nums.size();
        if (nums_size <= 1)
            return 0;
        vector<int> steps(nums_size);
        steps[nums_size - 1] = 0;
        for (int i = nums_size - 2; i >= 0; --i) {
            if (nums[i] == 0) {
                steps[i] = nums_size;
                continue;
            }
            if (i + nums[i] >= nums_size)
                steps[i] = 1;
            else
                steps[i] = steps[i + nums[i]] + 1;
            for (int j = 1; i + j < nums_size && steps[i + j] > steps[i]; ++j)
                steps[i + j] = steps[i];
        }
        return steps[0];
    }
};

TEST_CASE("Jump Game II") {
    vector<int> input{2, 3, 1, 1, 4};
    REQUIRE(Solution().jump(input) == 2);
}

TEST_CASE("Jump Game II - Wrong Answer 1") {
    vector<int> input{1};
    REQUIRE(Solution().jump(input) == 0);
}

TEST_CASE("Jump Game II - Wrong Answer 2") {
    vector<int> input{0};
    REQUIRE(Solution().jump(input) == 0);
}

TEST_CASE("Jump Game II - Wrong Answer 3") {
    vector<int> input{2, 1};
    REQUIRE(Solution().jump(input) == 1);
}

TEST_CASE("Jump Game II - Wrong Answer 4") {
    vector<int> input;
    for (int i = 25000; i >= 1; --i)
        input.push_back(i);
    input.push_back(1);
    input.push_back(0);
    REQUIRE(Solution().jump(input) == 2);
}

TEST_CASE("Jump Game II - Wrong Answer 5") {
    vector<int> input{2, 0, 2, 4, 6, 0, 0, 3};
    REQUIRE(Solution().jump(input) == 3);
}
TEST_CASE("Jump Game II - Wrong Answer 6") {
    vector<int> input{2, 3, 0, 1, 4};
    REQUIRE(Solution().jump(input) == 2);
}