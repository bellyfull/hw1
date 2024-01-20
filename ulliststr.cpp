#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"


ULListStr::ULListStr()
{
  head_ = NULL; // head item of linked list
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

  /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::push_back(const std::string& val) { //assuming val is a single char
  //if empty use default list constructor
  //update tail_
  //tail_->next turns from NULL to new Item
  //and new Item's prev turns to tail_ and new Item's next turns to NULL
  //else -> Item() and first = 0, last = len(val)
  
  //Item* newItem = new Item(); //first = last = 0
  // last = len(val); //creation of new item word X putting single chars in 

  if (empty()) { //when the list is empty
    Item* newItem = new Item();
    newItem->val[newItem->last] = val; 
    newItem->last++;
    head_ = newItem;
    tail_ = newItem;
    size_++;
    //head_->first == 0
    //head_->val[last]
    //prev = NULL;
    //next = NULL;
  } 
  else if (tail_->last == ARRSIZE) { // if tail node is FULL
    Item* newItem = new Item();
    newItem->val[newItem->last] = val;
    newItem->last++;
    newItem->prev = tail_;
    //ItemName->next = NULL;
    tail_->next = newItem;
    tail_ = newItem;
    size_++;
  }
  else { // when list exists and last node still has space
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }

}

  void ULListStr::push_front(const std::string& val) {
    //head_->prev = newItem, 
    //newItem->next = head_;
    //head_ = newItem;
    //newItem->val[first] = val;

    if (empty()) { // when list is empty
      Item* newItem = new Item();
      head_ = newItem;
      tail_ = newItem;
      newItem->val[newItem->first] = val;
      newItem->last++;
      size_++;
    }
    else if (head_->first != 0) { // when tail_'s FULL X when head_'s first isn't full
      // head_->prev = newItem;
      // newItem->next = head_;  
      // head_ = newItem;
      head_->first--;
      head_->val[head_->first] = val;
      size_++;
    }
    else { // when head_->first is FULL
      Item* newItem = new Item();
      newItem->last++;
      head_->prev = newItem;
      newItem->next = head_;
      head_ = newItem;
      newItem->val[newItem->first] = val;
      size_++;
    }

  }

  void ULListStr::pop_back() {
    // if list is empty nothing happens
    // if tail_->last = 1 in the node, update tail_--;
    // if tail_->last != 1 then popback
    if (empty()) { 
      return;
    }
    // below all have existing node(s) in list
    else if (tail_->last == 1 && tail_->prev == NULL) { //single element in node and is the only node
      delete tail_;
      head_ = tail_ = NULL;
      size_--;
    }
    else if (tail_->last == 1 && tail_->prev != NULL) { //single element in node with many nodes
      Item* temp = tail_->prev; // assigning second to last node temp pointer
      delete tail_; //removing the last node
      tail_ = temp; // tail_ updated to temp
      tail_->next = NULL;
      size_--;
    }
    else if (tail_->last>1) { //has more than one element in node
      tail_->last--;
      size_--;
    }
  }
  
  void ULListStr::pop_front() {
    // case1: empty list
    // case2: single element a) only node b) many nodes
    // case3: has more than one element
    if (empty()) {
      return;
    }
    if (head_->first == 0 && head_->last == 1 && head_->next == NULL) {
      delete head_;
      tail_ = NULL;
      head_ = NULL;
      size_--;
    }
    else if (head_->first == 0 && head_->last == 1 && head_->next != NULL) {
      Item* temp = head_->next;
      delete head_;
      head_ = temp;
      head_->prev = NULL;
      size_--;
    }
    else if (head_->last != 1) {
      head_->first++;
      size_--;
    }
  } 

  std::string const & ULListStr::back() const {
    //must return reference to last element
    // back element would be value at tail_->last-1
    if (empty()) {
      return NULL; //nullptr
    }
    return tail_->val[tail_->last-1];
  }
  std::string const & ULListStr::front() const {
    // front element would be head_->first
    if (empty()) {
      return NULL;
    }
    return head_->val[head_->first];
  }

    /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
  std::string* ULListStr::getValAtLoc(size_t loc) const {
    //loc is the index 
    //return pointer of value
    //loc must be <= size_ and >=0
    // loc%ARRSIZE

    if (empty()) {
      return NULL;
    }
    if (loc>=size_) {
      return NULL; // out of bounds
    }
    Item *iterator = head_;
    size_t count = 0;

    for (; iterator != NULL; iterator = iterator->next) {
      size_t arraysize = iterator->last - iterator->first;
      for (size_t i=0; i<arraysize; ++i) {
        if (count == loc) {
          return &iterator->val[iterator->first+i];
        }
        count++;
      }
    }
  return NULL;

}




void ULListStr::set(size_t loc, const std::string& val) //overwrites value at that loc
{
  std::string* ptr = getValAtLoc(loc); //ptr will point to value at loc
  if(ptr == NULL){ 
    throw std::invalid_argument("Bad location");
  }
  *ptr = val; //setting value to new val
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
