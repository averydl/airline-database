#include <iostream>
#include <exception>

/*
 * This exception subclass represents an error which occurs
 * when a client attempts to delete an element from a LinkedList
 * which does not exist in the list. This exception header
 * is a modified version of code obtained from:
 *
 * Prof. Fatma Cemile Cerce
 * at Bellevue College
 * Original Code Downloaded: Oct. 15, 2018
 */
using namespace std;

class ElementNotFoundException: public exception{
    const char* description;
    
    /*
     * Primary constructor; when this type of exception
     * is generated, an error-specific message must be
     * included indicating verbally what exceptional
     * case lead to the error
     */
    public:
        ElementNotFoundException(const char*  _description):
                description(_description){}
    
        /*
         * Returns the error description provided during construction
         * of this instance of the ElementNotFoundException
         */
        const char* what() const throw(){
           return description;
        }


};
