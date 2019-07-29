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
    int trap(vector<int> &height) {
        int result = 0; //trapped water
        stack<int> indexes;
        for (int i = 0; i < height.size(); ++i) {
            int bottom_height = 0;
            while (!indexes.empty() && height[indexes.top()] <= height[i]) { //每个元素最多被push一次，pop一次，因此是O(n)
                //height[indexes.top()] <= height[i]
                result += (i - indexes.top() - 1) * (height[indexes.top()] - bottom_height);
                bottom_height = height[indexes.top()];
                indexes.pop();
            }
            if (!indexes.empty()) { //height[indexes.top()] > height[i]
                result += (i - indexes.top() - 1) * (height[i] - bottom_height);
            }
            indexes.push(i);
        }
        return result;
    }
};

TEST_CASE("Trapping Rain Water") {
    vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    REQUIRE(Solution().trap(height) == 6);
}

TEST_CASE("Trapping Rain Water - Empty") {
    vector<int> height;
    REQUIRE(Solution().trap(height) == 0);
}

TEST_CASE("Trapping Rain Water - Single") {
    vector<int> height{1};
    REQUIRE(Solution().trap(height) == 0);
}

TEST_CASE("Trapping Rain Water - Double") {
    vector<int> height{1, 2};
    REQUIRE(Solution().trap(height) == 0);
}

TEST_CASE("Trapping Rain Water - Triple Convex") {
    vector<int> height{1, 2, 1};
    REQUIRE(Solution().trap(height) == 0);
}

TEST_CASE("Trapping Rain Water - Triple Concave") {
    vector<int> height{2, 1, 2};
    REQUIRE(Solution().trap(height) == 1);
}

TEST_CASE("Trapping Rain Water - Wrong Answer 4,2,3") {
    vector<int> height{4, 2, 3};
    REQUIRE(Solution().trap(height) == 1);
}
