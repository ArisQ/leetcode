#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include <queue>
#include <deque>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty())
            return nullptr;
        if (lists.size() == 1) {
            return lists[0];
        }
        deque<ListNode *> list_node_queue(lists.begin(), lists.end());
        while (list_node_queue.size() >= 2) {
            auto p = list_node_queue.front();
            list_node_queue.pop_front();
            auto q = list_node_queue.front();
            list_node_queue.pop_front();
            list_node_queue.push_back(mergeTwoLists(p, q));
        }
        return list_node_queue[0]; //size()==1
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};


TEST_CASE("Merge k Sorted Lists") {
    auto input = vector<ListNode *>{
        makeList({1, 4, 5}),
        makeList({1, 3, 4}),
        makeList({2, 6})
    };
    auto output = makeList({1, 1, 2, 3, 4, 4, 5, 6});
    cout << output << endl;
    cout << input << endl;
    auto answer = Solution().mergeKLists(input);
    cout << answer << endl;
    REQUIRE(equalList(answer, output));
//    freeListArray(input);
    freeList(output);
    freeList(answer);
}

