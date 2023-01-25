#include "List.h"
#include "List.hpp"
#include "List-given.hpp"

int main() {
  List<int> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }
  ListNode* curr = head_;
    //std::cout<<"current is "<<tail_->next->data<<std::endl;
    while (curr != NULL) {
        std::cout<<curr->data<< " ";
        curr = curr->next;
    }
  return 0;
}
