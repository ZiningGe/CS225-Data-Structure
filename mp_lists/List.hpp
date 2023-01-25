/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List():length_(0){ 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curNode = head_;
  ListNode* temp = NULL;
  while (curNode != NULL){
    temp = curNode -> next;
    delete curNode;
    curNode = temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  head_ = newNode;
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;
  
  if (tail_ != NULL){
    tail_ -> next = newNode;
  }
  tail_ = newNode;
  if (head_ == NULL){
    head_ = newNode;
  }
  
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    if (curr->prev != NULL){
      curr->prev->next = NULL;
      curr->prev = NULL;
    }
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
    ListNode* curr = head_;
    ListNode* prev = NULL;
    ListNode* first = NULL;
    ListNode* second = NULL;
    ListNode* third = NULL;
    while (curr != NULL&& curr->next != NULL && curr->next->next != NULL){
      //initialize
      first = curr;
      second = curr->next;
      third = curr->next->next;
      //last loop
      second->prev = prev;
      
      //switch
      first->next = third->next;
      third->next = first;

      //second->prev = first->prev;
      first->prev = third;
      
      if(first == head_){
        head_ = second;
      }
      else{
        prev->next = second;
      }
      
      //update  
      curr = first->next;
      prev = first;
      tail_ = prev;
    }
    if(curr != NULL){
      curr->prev =first;
      while(curr!= head_ && curr != NULL){
        tail_ = curr;
        curr = curr->next;
      } 
    }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
  ListNode* temp = head_;
  head_ = tail_;
  tail_ = temp;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
    if (head_ != NULL){
      ListNode* curNode = startPoint;
      ListNode* finalNode = endPoint->next;
      ListNode* nextNode = NULL;
      ListNode* temp = NULL;
      while (curNode != finalNode){
        nextNode = curNode->next;
        temp = curNode->next;
        curNode->next = curNode->prev;
        curNode->prev = temp;
        curNode = nextNode;
      }
      if(startPoint->next != NULL){
        startPoint->next->next = endPoint;
      }
      temp = endPoint->prev;
      endPoint->prev = startPoint->next;
      startPoint->next = temp;
      if(temp != NULL){
        temp->prev = startPoint;
      }
    }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(head_ != NULL){
    ListNode* curr = head_;
    ListNode* prev = NULL;
    while(curr != NULL){
      int count = 0;
      ListNode * start = curr;
      while(curr != NULL && count < n){
        prev = curr;
        curr = curr->next;
        count++;
      }
      std::cout<<"start is "<< start->data<<std::endl;
      std::cout<<"end is "<< prev->data<<std::endl;
      reverse(start,prev);
      if (start == head_){
        head_ = prev;
      }
      if (prev->next == NULL){
        tail_ = start;
      }
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  // /// @todo Graded in MP3.2
  // ListNode* secondcurr = second;
  // while (secondcurr != NULL){
  //   //std::cout<<"curr is "<< secondcurr->data<<std::endl;
  //   ListNode* firstcurr = first;
  //   ListNode* firstprev = NULL;
  //   ListNode* temp = NULL;
  //   ListNode* secondcurrnext = secondcurr->next;

  //   //std::cout<<"curr is "<<__LINE__<<std::endl;

  //   while(firstcurr != NULL &&  firstcurr->data < secondcurr->data){
  //     firstprev = firstcurr;
  //     firstcurr = firstcurr->next;
  //   }
  //   if(firstcurr == first){
  //     temp = first;
  //     first = secondcurr;
  //     secondcurr->next = temp;
  //     secondcurr->prev = NULL;
  //     if (temp != NULL){
  //       temp->prev = secondcurr;
  //     }

  //   }
  //   else{
  //     firstprev->next = secondcurr;
  //     secondcurr->prev = firstprev;
  //     secondcurr->next = firstcurr;
  //     if(firstcurr != NULL){
  //       firstcurr->prev = secondcurr;
  //     }

  //   }
  //   secondcurr = secondcurrnext;
  // }
  // return first;
  ListNode* newhead = NULL;
  ListNode* curr = newhead;
  ListNode* firstcurr = first;
  ListNode* secondcurr = second;
  ListNode* temp = NULL;

  while(firstcurr != NULL && secondcurr != NULL){
    //std::cout<<"cur is "<<__LINE__<<std::endl;

    if (firstcurr->data < secondcurr->data){

      temp = firstcurr->next;
      if(curr == NULL){
        newhead = firstcurr;
        curr = firstcurr;
        curr->next= NULL;

      }
      else{
        curr->next = firstcurr;
        firstcurr->prev = curr;
        curr = curr->next;
      }
      firstcurr = temp;
    }
    else{

      temp = secondcurr->next;
      if(curr == NULL){

        newhead = secondcurr;
        curr = secondcurr;
        curr->next= NULL;
      }
      else{
        curr->next = secondcurr;
        secondcurr->prev = curr;
        curr = curr->next;

      }
      secondcurr = temp;
    }
    //std::cout<<"curr_data is "<<curr->data<<std::endl;
    //std::cout<<"newhead is "<<newhead->data<<std::endl;

  }
  if(firstcurr == NULL && secondcurr != NULL){
    if(curr == NULL){
      newhead = secondcurr;
    }
    else{
      curr->next = secondcurr;
      secondcurr->prev = curr;
    }
    
  }
  else if(firstcurr != NULL && secondcurr == NULL){
    if(curr == NULL){
      newhead = firstcurr;
    }
    else{
      curr->next = firstcurr;
      firstcurr->prev = curr;
    }
  }
  first = newhead;
  return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1){
    return start;
  }
  ListNode* curr = start;
  ListNode* start2 = NULL;

  for(int i = 0; i < chainLength/2; i++){
    curr = curr->next;
  }
  start2 = curr;
  start2->prev->next = NULL;
  start2->prev = NULL;
  

  return merge(mergesort(start,chainLength/2), mergesort(start2,chainLength-chainLength/2));

}
