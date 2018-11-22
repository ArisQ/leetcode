#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> u;
        vector<vector<string>> p;
        u.push_back(vector<string>()); //u0=[]
        p.push_back(vector<string>()); //p0=[]
        u.push_back({"()"}); //u1=["()"]
        p.push_back(vector<string>()); //p1=[]
        std::function<vector<string>(int)> part_plan;
        part_plan = [&u, &part_plan](int x) {
            if (x == 1)
                return u[1];
            vector<string> result;
            for (int i = 1; i < x; ++i) {
                for (auto &sl:u[i]) {
                    if (x - i > 1)
                        for (auto &sr:u[x - i]) {
                            result.push_back(sl + sr);
                        }
                    auto pp_x_i = part_plan(x - i); //此处也可以使用子问题的解而不是递归
                    for (auto &sr:pp_x_i) {
                        result.push_back(sl + sr);
                    }
                }
            }
            return result;
        };
        for (int i = 2; i <= n; ++i) {
            vector<string> un;
            for (auto &s:u[i - 1])
                un.push_back('(' + s + ')');
            for (auto &s:p[i - 1])
                un.push_back('(' + s + ')');
            u.push_back(un);
            p.push_back(part_plan(i));
        }
        vector<string> result(u[n]);
        result.insert(result.end(), p[n].begin(), p[n].end());
        return result;
    }
};

ostream &operator<<(ostream &out, vector<string> vs) {
    for (auto &s :vs)
        cout << s << " ";
    return out;
}

TEST_CASE("Generate Parentheses") {
    vector<string> p3 = {
        "((()))",
        "(()())",
        "(())()",
        "()(())",
        "()()()"
    };
    auto output = Solution().generateParenthesis(3);
    cout << p3 << endl;
    cout << output << endl;
    REQUIRE(set<string>(p3.begin(), p3.end()) == set<string>(output.begin(), output.end()));
}

