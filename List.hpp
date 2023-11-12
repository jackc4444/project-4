#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>

class List {
  
  private:



					//a private type
				  struct Node {
					Node *next;
					Node *prev;
					T datum;
				  };







  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
	  assert(empty());
	  for (Iterator i = other.begin(); i != other.end(); ++i){
		  push_back(*i);
	  }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

	int listsize;
  
  
  
						public:
						
	List() : first(nullptr), last(nullptr), listsize(0){
	}
	
	List(const List<T> &other) : first(nullptr), last(nullptr), listsize(0){
		copy_all(other);
	}

	~List(){
		clear();
	}




		  class Iterator {
			friend class List;
			
			
			private:
			Node *node_ptr;

			Iterator(Node *p) : node_ptr(p){
			}
		
			

			public:
			// * ,++, default constructor, == and !=.
			Iterator() : node_ptr(nullptr){
			}
			
			Iterator& operator--() {
			  assert(node_ptr);
			  node_ptr = node_ptr->prev;
			  return *this;
			}
			
			T& operator*() const{
				assert(node_ptr != nullptr);
				return node_ptr -> datum;
			}
			
			Iterator& operator++(){
				//make sure iterator node isn't currently already null
				assert(node_ptr != nullptr);
				node_ptr = node_ptr -> next;
				return *this;
			}
			
			bool operator==(Iterator right) const{
				return node_ptr == right.node_ptr;
			}
			
			bool operator!=(Iterator right) const{
				return node_ptr != right.node_ptr;
			}
			

		  };




  //EFFECTS:  returns true if the list is empty
  bool empty() const{
	  if (first){
		  return false;
	  }
	  return true;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const{
	  return listsize;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T& front(){
	  assert(!empty());
	  return first -> datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
	  assert(!empty());
	  return last -> datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
	  if (empty()){
		  Node *temp = new Node{nullptr, nullptr, datum};
		  first = temp;
		  last = temp;
		  listsize++;
	  }
	  else{
	  Node *temp = new Node;
	  temp -> datum = datum;
	  temp -> next = first;
	  temp -> prev = nullptr;
	  
	  first -> prev = temp;
	  first = temp;
	  listsize++;
	  }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
	  if (empty()){
		  push_front(datum);
	  }
	  else{
		  Node *temp = new Node;
		  temp -> datum = datum;
		  temp -> next = nullptr;
		  temp -> prev = last;
		  
		  last -> next = temp;
		  last = temp;
		  listsize++;
	  }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
	  if (empty()){ return; }
	  
	  Node *newfirst = first -> next;
	  if (newfirst){ // list size at least 2
		  newfirst -> prev = nullptr;
		  delete first;
		  first = newfirst;
		  listsize = listsize - 1;
	  }
	  else{ //nullptr, list is only size 1
		  delete first;
		  first = nullptr;
		  last = nullptr;
		  listsize = 0;
	  }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
	  if (empty()){ return; }
	  
	  Node *newlast = last -> prev;
	  if (newlast){ // has previous element or size of at least 2
			newlast -> next = nullptr;
			delete last;
			last = newlast;
			listsize = listsize - 1;
	  }
	  else{ //single node list makes newlast nullptr
		  delete last;
		  last = nullptr;
		  first = nullptr;
		  listsize = 0;
	  }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
	  while (!empty()){
		  pop_front();
	  }
  }

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
	  return Iterator();
  }

  //REQUIRES: i is valid
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
	  assert(i.node_ptr != nullptr);
	  Node *nextnode = i.node_ptr -> next;
	  Node *prevnode = i.node_ptr -> prev;
	  
	  //4 possible cases: nextnode and prevnode are valid
	  // nextnode is null (end of list)
	  // prevnode is null (beginning of list)
	  // both are null (single item list)
	  if (prevnode != nullptr && nextnode != nullptr){
		  prevnode -> next = nextnode;
		  nextnode -> prev = prevnode;
		  delete i.node_ptr;
		  listsize = listsize - 1;
	  }
	  else if (prevnode != nullptr && nextnode == nullptr){
		  pop_back();
	  }
	  else if (prevnode == nullptr && nextnode != nullptr){
		  pop_front();
	  }
	  else{
		  pop_front();
	  }
	  
  }

  //REQUIRES: i is a valid iterator
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
	  assert(i.node_ptr != nullptr);
	  
	  //check if added node is going to be new first element
	  if (i.node_ptr == first){
		  push_front(datum);
	  }
	  else{
		  Node *temp = new Node;
		  temp -> next = i.node_ptr;
		  temp -> prev = i.node_ptr -> prev;
		  temp -> datum = datum;
		  
		  (i.node_ptr -> prev) -> next = temp;
		  i.node_ptr -> prev = temp;
		  listsize++;
		  
	  }
	  
  }
	
	//assignment operator
	List<T>& operator=(const List<T> &right){
		if (right.begin() == begin()){ //self assignment check
			return *this;
		}
		clear();
		copy_all(right);
		return *this;
	}






};//List










#endif // Do not remove this. Write all your code above this line.
