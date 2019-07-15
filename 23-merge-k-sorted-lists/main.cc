#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
#include "list_node.h"

using namespace std;


class Solution {
public:
    ListNode *mergeKLists(vector<ListNode*>& lists) {
        return nullptr;
    }
};


TEST_CASE("Merge Two Sorted Lists - Solution") {
    auto input = vector<ListNode*> {
        makeList({1, 4, 5}),
        makeList({1, 3, 4}),
        makeList({2, 5})
    };
    auto output = makeList({1, 1, 2, 3, 4, 4, 5, 6});
    printListArray(input);
    printListNode(output);
    auto answer = Solution().mergeKLists(&input);
    printListNode(answer);
    REQUIRE(equalListNode(answer, output) == true);
    freeListArray(input);
    freeList(output);
    freeList(answer);
}