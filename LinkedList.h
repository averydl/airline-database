#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
using namespace std;

/*
 * Node struct; data type for use
 * constructing a LinkedList of objects,
 * of arbitrary class type <T>
 */
template <class T>
struct node{
    T data;
    node<T>* next;
};

/* Linked List class provided
 * by Professor Fatma Cemile Serce
 * at Bellevue College, for CS 300;
 *
 * Modified by Derek Avery for the
 * October 19, 2018 submission of
 * Assignment 2 for CS 300 @
 * Bellevue College
 */
template <class T>
class LinkedList{
	private:
		LinkedList(const LinkedList&)=delete; //copy constructor
        void copylist(LinkedList<T>& list);   //helper function for assignment operator

	protected:
		int count;
		node<T> *head, *last;
    
	public:
		LinkedList();   //default constructor
		bool isEmpty(); //returns true if the list contains 0 elements
		int length();   //returns the number of T nodes in the list
		T front();      //returns T contained in the first node of the list
		T back();       //returns T contained in the last node of the list
		void insertFirst(T&);   //insert new node<T> at front of list
		void insertLast(T&);    //insert new node<T> at end of list
		void deleteNode(T&);    //remove a node<T> from the list, where the node contains T 'equal to' the argument T
        void destroylist();     //remove all nodes and free the memory they occupied
		LinkedList<T>& operator=(LinkedList<T>&);   //assignment operator
		template <class U>
		friend ostream& operator<<(ostream& os, LinkedList<U>& list);
		~LinkedList();
};

/*
 * Default constructor; 'head' and 'last'
 * nodes are NULL pointers, and count is
 * initialized to a starting value of 0, as the
 * list is effectively empty upon instantiation
 * via the default constructor
 */
template <class T>
LinkedList<T>::LinkedList(){
     head = last = NULL;
     count = 0;
}

/*
 * Returns true if the LinkedList
 * contains any <T> nodes
 */
template <class T>
bool LinkedList<T>::isEmpty(){
	return head==NULL;
}

/*
 * Returns the number of elements
 * contained in the linked list
 */
template <class T>
int LinkedList<T>::length(){
	return count;
}

/*
 * Return the object contained in
 * the front node of the linked list
 */
template <class T>
T LinkedList<T>::front(){
	return head->data;
}

/*
 * Return the object contained in
 * the last node in the linked list
 */
template <class T>
T LinkedList<T>::back(){
	return last->data;
}

/*
 * Insert a new node at the front of
 * the linked list
 */
template <class T>
void LinkedList<T>::insertFirst(T& item){
    node<T> *temp = new node<T>;
    temp->data = item;
    temp->next = head;
    head = temp;
    count++;
    if(last==NULL)
        last = temp;
}

/*
 * Insert a node at the end of
 * the linked list
 */
template <class T>
void LinkedList<T>::insertLast(T& item){
	node<T> *newnode = new node<T>;
	newnode->data = item;
	newnode->next = NULL;
	if(head==NULL){
		head = last = newnode;
	}else{
		last->next = newnode;
		last = newnode;
	}
	count++;
}

/*
 * Deletes a node from the
 * Linked List which contains an object
 * which is equal to 'item'.
 *
 * Precondition: <T> class must have
 * valid equal-to and less-than operators
 * in order for this function to work correctly
 */
template <class T>
void LinkedList<T>::deleteNode(T& item){
    //print error message if list is empty
	if(head == NULL)
		cerr<<"empty list";
	else{
		if(head->data == item){
            // edge case; delete the target node when
            // it is the first element in the list
			node<T>* p = head;
			head = head->next;
			delete p;
			count--;
			if(head==NULL) last = NULL;
		}else{
            // all other cases; delete a node
            // element in the list if it exists
			node<T>* p = head;
			node<T>* q = p->next;
            
            // iterate through list until the end is reached,
            // or an element equal to 'item' is found
			while(q!=NULL && q->data != item){
				p = q;
				q = q->next;
			}
            
            // if the target element exists, delete it
			if(q!=NULL){
				p->next = q->next;
				count--;
                
                // point 'last' at penultimate element if the
                // deleted element was at the end of the list
				if(last == q) last = p;
				delete q;
			}
		}
	}
}

/*
 * Effectively destroys an instance of a LinkedList;
 * used in conjunction with the destructor to free
 * all memory associated with an instance of LinkedList
 */
template <class T>
void LinkedList<T>::destroylist(){
	node<T> *p;
	while(head != NULL){
		p = head;
		head = head->next;
		delete p;
	}
	last = NULL;
	count = 0;
}

/*
 * Assignment operator; if the passed instance of LinkedList
 * is not the current instance, this function will remove
 * all elements from the list and duplicate the argument 'list'
 * by inserting each of its nodes' values into the current
 * LinkedList instance
 */
template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& list){
	if(this != &list){
        copylist(list);
	}
    return *this;
}

/*
 * Deep-copy the elements of LinkedList parameter 'list'
 * to the current instance of LinkedList to make it a
 * value-wise duplicate of 'list'
 */
template <class T>
void LinkedList<T>::copylist(LinkedList<T>& list) {
    //remove all elements from the current list
    destroylist();
    
    if(list.count != 0) {//if the 'list' parameter is not empty
        
        //create temporary node pointer to keep track
        //of the current element of 'list' being copied
        node<T>* temp = list.head;
        
        //insert all elements from 'list' into this
        //current LinkedList instance
        while(temp != NULL) {
            insertFirst(temp->data);
            temp = temp->next;
        }
    }
}

/*
 * Write data from all elements contained
 * in the linked list to an output stream
 * buffer; provides improved method of
 * printing visual representation of the
 * LinkedList
 */
template <class T>
ostream& operator<<(ostream& os, LinkedList<T>& list){
	node<T> *p = list.head;
	while(p != NULL){
		os << p -> data << " " << endl;
		p = p->next;
	}
    return os;
}

/*
 * LinkedList destructor; frees all memory
 * associated with the Linked List via the
 * destroyList() function
 */
template <class T>
LinkedList<T>::~LinkedList(){
	destroylist();
}


#endif /* LINKEDLIST_H_ */
