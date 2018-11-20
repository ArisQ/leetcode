#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <vector>

using namespace std;

  //Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            vector<ListNode*> stack;
            auto p=head;
            while(p!=NULL) {
                stack.push_back(p);
                p=p->next;
            }
            while(n>1) {
                stack.pop_back();
                --n;
            }
            auto nth=stack.back();
            stack.pop_back();
            if(stack.empty())
                return nth->next;
            auto n_1th=stack.back();
            n_1th->next=nth->next;
            delete nth;
            return head;
        }
};

ListNode *makeListNode(const vector<int> values) {
    ListNode *head=NULL;
    for(auto iter=values.crbegin();iter!=values.crend();++iter) {
        auto p=new ListNode(*iter);
        p->next=head;
        head=p;
    }
    return head;
}

void freeListNode(ListNode *head) {
    while(head!=NULL){
        auto p=head;
        head=head->next;
        delete p;
    }
}

bool equalListNode(const ListNode *l,const ListNode *r) {
    while(l!=NULL && r!=NULL) {
       if(l->val!=r->val) 
           return false;
       l=l->next;
       r=r->next;
    }
    if(l!=NULL || r!=NULL)
        return false;
    return true;
}

void printListNode(const ListNode *head) {
    while(head!=NULL) {
        cout<<head->val<<" ";
        head=head->next;
    }
    cout<<endl;
}

TEST_CASE("Remove Nth Node From End of List") {
    auto input=makeListNode({1,2,3,4,5});
    auto output=makeListNode({1,2,3,5});
    printListNode(input);
    printListNode(output);
    auto answer=Solution().removeNthFromEnd(input,2);
    printListNode(answer);
    REQUIRE(equalListNode(answer,output)==true);
    freeListNode(input);
    freeListNode(output);
}
