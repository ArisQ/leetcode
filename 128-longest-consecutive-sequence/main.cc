#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <list>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const pair<T, T> &p) {
    os << p.first << " " << p.second;
    return os;
}

class Solution {
public:
    virtual int longestConsecutive(const vector<int> &nums) = 0;
};

class Solution1: public Solution {
public:
    int longestConsecutive(const vector<int> &nums) override {
        int n = nums.size();
        list<pair<int, int>> sequences;
        for (int i = 0; i < n; ++i)
            sequences.emplace_back(nums[i], nums[i]);
        for (auto p = sequences.begin(); p != sequences.end();) {
            bool merged = false;
            auto q = sequences.begin();
            while (q != sequences.end()) {
                cout << *p << " " << *q << " ";
                if (q == p) {
                    cout << "equal " << endl;
                    ++q;
                    continue;
                }
                if (p->first <= q->second + 1 && q->first <= p->second + 1) {
                    cout << "iter ";
                    p->first = min(p->first, q->first);
                    p->second = max(p->second, q->second);
                    merged = true;
                    auto r = q;
                    ++q;
                    sequences.erase(r);
                } else {
                    cout << "not iter ";
                    ++q;
                }
                cout << endl;
            }
            if (!merged)
                ++p;
        }
        for (auto &seq:sequences)
            cout << seq.first << " " << seq.second << endl;
        int result = 0;
        for (auto &seq:sequences)
            result = max(result, seq.second - seq.first + 1);
        return result;
    }
};

class SolutionHash: public Solution {
public:
    int longestConsecutive(const vector<int> &nums) override {
        set<int> numSet; // unordered_set
        for (int num:nums)
            numSet.insert(num);
        int result = 0;
        for (int num:numSet) {
            if (numSet.find(num - 1) == numSet.end()) {
                int next = num + 1, count = 1;
                while (numSet.find(next) != numSet.end()) {
                    ++next;
                    ++count;
                }
                result = max(result, count);
            }
        }
        return result;
    }
};
TEST_CASE("Longest Consecutive Sequence") {
    vector<shared_ptr<Solution>> solutions{
        make_shared<Solution1>(),
        make_shared<SolutionHash>()
    };
    for (auto &solution:solutions) {
        REQUIRE(solution->longestConsecutive({100, 4, 200, 1, 3, 2}) == 4);
        REQUIRE(solution->longestConsecutive({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}) == 9);
    }
}
