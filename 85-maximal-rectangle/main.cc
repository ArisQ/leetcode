#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
    int m, n;
    int maxRectangle;
    vector<vector<int>> countV;
    vector<vector<int>> countH;
public:
    int maximalRectangle(vector<vector<char>> &matrix) {
        if (matrix.empty() || matrix[0].empty())
            return 0;
        m = matrix.size();
        n = matrix[0].size();
        countV = vector<vector<int>>(m, vector<int>(n, 0));
        countH = vector<vector<int>>(m, vector<int>(n, 0));
        cout << matrix;
        for (int j = 0; j < n; ++j)
            if (matrix[0][j] == '1')
                countV[0][j] = 1;
        for (int i = 1; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == '1')
                    countV[i][j] = countV[i - 1][j] + 1;
        cout << countV;
        for (int i = 0; i < m; ++i)
            if (matrix[i][0] == '1')
                countH[i][0] = 1;
        for (int j = 1; j < n; ++j)
            for (int i = 0; i < m; ++i)
                if (matrix[i][j] == '1')
                    countH[i][j] = countH[i][j - 1] + 1;
        cout << countH;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == '1')
                    findRectangle(i, j, 1, 1);
        return maxRectangle;
    }

    void findRectangle(int i, int j, int v, int h) {
        cout << i << " " << j << " " << v << " " << h << " " << maxRectangle << endl;
        maxRectangle = max(maxRectangle, v * h);
        if (i < m - 1 && j < n - 1 && countH[i + 1][j + 1] > h && countV[i + 1][j + 1] > v)
            findRectangle(i + 1, j + 1, v + 1, h + 1);
        int extend = 1;
        while (i + extend < m && countH[i + extend][j] >= v)
            ++extend;
        if (extend > 1)
            maxRectangle = max(maxRectangle, (v + extend - 1) * h);
        extend = 1;
        while (j + extend < n && countV[i][j + extend] >= h)
            ++extend;
        if (extend > 1)
            maxRectangle = max(maxRectangle, v * (h + extend - 1));
    }
};

TEST_CASE("Maximal Rectangle") {
    vector<vector<char>> matrix{
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    REQUIRE(Solution().maximalRectangle(matrix) == 6);
}
