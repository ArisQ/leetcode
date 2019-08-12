#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <set>

using namespace std;


ostream &operator<<(ostream &os, const vector<int> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
    vector<string> result;
    vector<int> dot;
    int n;
public:
    vector<string> restoreIpAddresses(string s) {
        //0-255
        n = s.size();
        dot.resize(3);
        restoreIpAddresses(s, 0, 0);
        return result;
    }

    void restoreIpAddresses(string &s, int start, int part) {
        if (part == 3) {
            if (isValid(s, start, n - 1)) {
                string ip;
                ip.reserve(n + 3);
                int iter = 0;
                for (auto dotPos:dot) {
                    for (; iter <= dotPos; ++iter)
                        ip.push_back(s[iter]);
                    ip.push_back('.');
                }
                for (; iter < n; ++iter)
                    ip.push_back(s[iter]);
                cout << iter << endl;
                result.push_back(ip);
                cout << ip << endl;
                cout << dot << endl;
            }
            return;
        }
        for (int i = 0; i < 3 && start + i < n; ++i) {
            if (isValid(s, start, start + i)) {
                dot[part] = start + i;
                restoreIpAddresses(s, start + i + 1, part + 1);
            }
        }
    }

    bool isValid(const string &s, int start, int end) { //[start,end]
        //0  0-1  0-1-2
        if (end - start == 0)
            return true;
        if (end - start == 1 && s[start] != '0')
            return true;
        if (end - start == 2) {
            if (s[start] == '1')
                return true;
            if (s[start] == '2' && s[start + 1] < '5')
                return true;
            if (s[start] == '2' && s[start + 1] == '5' && s[start + 2] < '6')
                return true;
        }
        return false;
    }
};

TEST_CASE("Restore IP Addresses") {
    string input = "25525511135";
    vector<string> output{"255.255.11.135", "255.255.111.35"};
    auto answer = Solution().restoreIpAddresses(input);
    REQUIRE(multiset<string>(answer.begin(), answer.end()) == multiset<string>(output.begin(), output.end()));
}

TEST_CASE("Restore IP Addresses - 0000") {
    string input = "0000";
    vector<string> output{"0.0.0.0"};
    auto answer = Solution().restoreIpAddresses(input);
    REQUIRE(multiset<string>(answer.begin(), answer.end()) == multiset<string>(output.begin(), output.end()));
}
