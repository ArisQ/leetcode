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

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<bool> used(n, false);//i used
        vector<int> factorial(n, 0); // (n-1-i)!
        string result(n, '0');

        factorial[n - 1] = 1;//0!=1
        for (int i = 1; i < n; ++i)
            factorial[n - 1 - i] = factorial[n - i] * i;
        // cout << factorial;

        k = k - 1;
        int index;
        for (int i = 0; i < n; ++i) {
            index = k / factorial[i];
            // cout << "i:" << i << " k:" << k << " index:" << index << endl;
            // cout << used;
            k = k % factorial[i];
            for (int j = 0; j < n; ++j) {
                if (used[j])
                    continue;
                if (index == 0) {
                    result[i] = j + '1';
                    used[j] = true;
                    break;
                }
                --index;
            }
        }
        return result;
    }
};

TEST_CASE("Permutation Sequence - Example 1") {
    REQUIRE(Solution().getPermutation(3, 3) == "213");
    REQUIRE(Solution().getPermutation(4, 9) == "2314");
    REQUIRE(Solution().getPermutation(1, 1) == "1");
    REQUIRE(Solution().getPermutation(2, 1) == "12");
    REQUIRE(Solution().getPermutation(2, 2) == "21");
}
