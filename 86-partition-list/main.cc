#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode* partition(ListNode* head,int x){
        ListNode dummy(0);
        ListNode *lessEnd=&dummy,*currentLead=&dummy,*current=nullpt;
        dummy.next=head;
        while(currentLead->next!=nullptr){
//            if(currentLead->next->val<x){
//                current=currentLead->next;
//                currentLead->next=current->next;
//                current->next=lessEnd->next;
//                lessEnd->next=current;
//                lessEnd=current;
//            }
            currentLead=currentLead->next;
        }
        cout<<dummy.next;
        return dummy.next;
    }
};

TEST_CASE("Partition List") {
    ListNode *input=makeList({1,4,3,2,5,2});
    ListNode *output=makeList({1,2,2,4,3,5});
    cout<<input;
    cout<<output;
    REQUIRE(equalList(Solution().partition(input,3),output));
}
