#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Solution_1
{
  public:
    int maxArea(vector<int> &height)
    {
        int result = 0;
        int cij = 0;
        for (size_t i = 0; i < height.size(); ++i)
            for (size_t j = i + 1; j < height.size(); ++j)
            {
                cij = (j - i) * (height[i] <= height[j] ? height[i] : height[j]);
                if (cij > result)
                    result = cij;
            }
        return result;
    }
};

class Solution_2
{
  public:
    int maxArea(vector<int> &height)
    {
        int result = 0;
        int cij = 0;
        size_t size = height.size();
        for (size_t i = 0; i < size; ++i)
            for (size_t j = size - 1; j > i; --j)
            {
                if (height[j] >= height[i])
                {
                    cij = (j - i) * height[i];
                    if (cij > result)
                        result = cij;
                    break;
                }
                else
                {
                    cij = (j - i) * height[j];
                    if (cij > result)
                        result = cij;
                }
            }
        return result;
    }
};

TEST_CASE("Integer to Roman") {
    vector<int> input = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    REQUIRE(Solution_1().maxArea(input)==49);
    REQUIRE(Solution_2().maxArea(input)==49);
}
