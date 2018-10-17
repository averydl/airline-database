#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H

#include "LinkedList.h"
#include "Passenger.h"
#include "ElementNotFoundException.h"
#define TRACE {printf("Executing %s line %d\n", __FILE__, __LINE__);}

template <class T>
class OrderedLinkedList : public LinkedList<T> {
	public:
        void deleteNode(T&);    //delete an element from the OrderedLinkedList which contains target T
        void insert(T&);        //insert an element in the OrderedLinkedList containing T equal-to the function argument
        T& search(T&);             //return element from the list which evaluates equal-to the function argument
    private:
        void insertFirst(T&);    //change insertFirst to private to avoid accidental mis-ordering of elements
        void insertLast(T&);     //change insertLast to private to avoid accidental mis-ordering of elements

};

/*
 * New inheriting class-specific function 'insert' is a generic
 * function which will insert an element into the list such that
 * ordering is maintained; this will be the only active 'insert'
 * method, and the other overridden 'insert' methods will simply
 * call this revised method, as inserting at the beginning/end of
 * the list is now only acceptable in the rare case that the element
 * being inserted at the beginning/end would maintain ordering
 *
 * This class throws an ElementNotFoundException in the case that
 * a function is called which relies on or would modify/remove (e.g.
 * search, insert) nodes containing a T which evaluates equal-to the
 * function argument IFF the element does not exist in the list.
 * The exception will contain an identifier code of -1, which is an
 * arbitrary error code
 */
template <class T>
void OrderedLinkedList<T>::insert(T& item) {
    //create new node temp to insert into the list
    node<T>* temp = new node<T>;
    temp -> data = item;
    
    //edge case: empty list
    if(this -> count == 0) {
        //place the new node @ the front of the list @ increment count
        this -> head = temp;
        this -> last = temp;
        temp -> next = NULL;
    }
    //edge case: single-element list
    else if(this -> count == 1) {
        //check if the data in temp is < the first element; if
        //so, place it at the front
        if(temp -> data < this -> head -> data) {
            this -> head = temp;
            temp -> next = this -> last;
        } else {//if temp->data > the first element, place it at the end of the list
            this -> last = temp;
            this -> head -> next = temp;
            temp -> next = NULL;
        }
    }
    
    //general case: two+ elements in list -> insert the new node to maintain ordering
    else {
        //edge case: maintain ordering by inserting temp @ front of the list
        if(temp -> data < this -> head -> data) {
            temp -> next = this -> head -> next;
            this -> head = temp;
        }
        
        else {
            //create temporary node pointers to keep track of position while traversing list
            node<T> *leading = this -> head -> next;
            node<T> *trailing = this -> head;
            
            //traverse list until the correct insertion point in the list is reached
            while(leading != NULL && (leading -> data < temp -> data)){
                trailing = leading;
                leading = leading -> next;
            }
            //insert the element once the proper position is located
            temp -> next = leading;
            trailing -> next = temp;
            //if element is at the end of the list, make 'last' point to it
            if(temp -> next == NULL)
                this -> last = temp;
        }
    }
    this->count++;  //increment count after new node is inserted successfully
}

/*
 * This method will delete a node from the LinkedList which
 * contains a T object which evaluates equal-to the argument
 * 'item' if such a node exists; if such a node does not
 * exist in this LinkedList, this function will throw
 * an ElementNotFoundException
 */
template <class T>
void OrderedLinkedList<T>::deleteNode(T& item) {
    
    if(this->count == 0) {//edge case: if the list is empty, throw exception as item does not exist
        throw ElementNotFoundException("The list is empty!");
        
    } else if(this->count == 1) {//edge case: handle list with a single element
        
        if(this->head->data == item) {//if the only element equals item, delete it
            delete this->head;
            this->head = this->last = NULL;
        } else {//if the single element is not equal to item, throw an exception
            throw ElementNotFoundException("Element does not exist!");
        }
        
    } else if(this->head->data == item) {//edge case: delete the front element
        
        node<T>* temp_head = this->head;
        this->head = this->head->next;
        delete temp_head;
        
    } else {//general case: search list of two or more elements for the target item

        //temporary pointers to iterate through nodes in list
        node<T>* lag = this->head;
        node<T>* lead = lag->next;
        
        //compare each element to item until target is found or end of list is reached
        while(lead != NULL && !(lead->data == item)) {
            lag = lead;
            lead = lead->next;
        }
        //delete the element if it is found, throw exception if it is not
        if(lead != NULL) {
            lag->next = lead->next;
            delete lead;
        } else {
            throw ElementNotFoundException("Element does not exist!");
        }
        //if item deleted was at the end of the list,
        //reassign 'last' to point to the new end element
        if(lag->next == NULL) {
            this->last = lag;
        }
    }
    this->count--; //decrement count after successfully deleting the target node
}

/*
 * This search function returns a T contained in one of this OrderedLinkedList
 * nodes, provided that such a T exists which evaluates equal-to the passed
 * T parameter 'item'. If no such element exists, this function will
 * throw an exception
 */
template <class T>
T& OrderedLinkedList<T>::search(T& item) {
    if(this->count == 0) {//edge case: empty list can not contain T == item
        throw ElementNotFoundException("List is empty!");
    } else if(this->count == 1) {//edge case: single-element list
        if(this->head->data == item) {//if first node's T equals item, return it
            return this->head->data;
        } else {//if the first and only node does not contain T == item, throw exception
            throw ElementNotFoundException("Element does not exist!");
        }
    } else {//general case: 2 or more elements contained in list
        node<T>* temp = this->head; //temporary node pointer, used to iterate through list
        
        //iterate through each item in list until target node or end of list is reached
        while( (temp != NULL) && !(temp->data == item)) {
            temp = temp->next;
        }
        if(temp == NULL) {//if target node is not found, throw exception
            throw ElementNotFoundException("Element does not exist!");
        } else {//if target node is found, return it
            return temp->data;
        }
        
    }
}

/*
 * Override insertFirst; this function now simply makes a
 * call to the new 'insert' function to ensure ordering
 * is maintained in the OrderedLinkedList
 */
template <class T>
void OrderedLinkedList<T>::insertFirst(T& item) {
    insert(item);
}

/*
 * Override insertFirst; this function now simply makes a
 * call to the new 'insert' function to ensure ordering
 * is maintained in the OrderedLinkedList
 */
template <class T>
void OrderedLinkedList<T>::insertLast(T& item) {
    insert(item);
}

#endif /* ORDEREDLINKEDLIST_H_ */
