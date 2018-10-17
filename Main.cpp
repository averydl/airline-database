#include "OrderedLinkedList.h"
#include "Passenger.h"
#include <iostream>
#include <algorithm>

// Global Variables //

//strings to hold user input during each loop of main program execution
std::string flight_no, name, surname, address, number;

//string showing user input options
std::string const MENU = "A(Add) | S (Search) | D (Delete) | L (List) | Q (Quit): ";

//array to hold LinkedLists of Passengers -- one for each flight
OrderedLinkedList<Passenger>** flights = new OrderedLinkedList<Passenger>*[4];

// Functions //

std::ostream &operator<<(std::ostream &os, Passenger &p);   //returns outputstream object with strings from Passenger fields
bool hasNumber(const std::string& s);                       //returns true if the argument string contains any numeric digits
bool validFlight(const std::string& s);                     //returns true if the string argument is a valid flight number
bool promptForInput();                                      //sets global constants to user-specified values; returns true if user input is valid
int getFlightIndex(const std::string& s);                   //returns the index in flights which holds the list for argument flight number

/*
 * This Main class is used to manage a simple database consisting
 * of four passenger manifests for a theoretical airline, which offers
 * four flights per day: flight 100, 200, 300 and 400. Users will
 * be able to interact with this database indirectly to perform operations
 * including adding/removing passengers from a flight, and listing
 * passengers currently 'booked' on a given flight.
 *
 * During program execution, users will be able to utilize program
 * functionality via a simple command-line interface, with will prompt
 * them to execute different commands and display the results of each
 * command via the active console window.
 *
 * This code has been written
 * to conform to specifications of:
 *
 * CS300Fall18_Assignment2.pdf - due Oct. 19, 2018
 *
 * This document was provided in CS 300
 * at Bellevue College, by Prof. Fatma Cemile Serce
 *
 */

int main() {
    std::string input;  //string to hold user input while program runs
    std::cout << "***DELTA AIRLINES***\nPlease choose an operation:\n"; //prompt for user input
    
    //initialize Passenger linked lists for each of the four flights
    for(int i = 0; i < 4; i++) {
        flights[i] = new OrderedLinkedList<Passenger>();
    }
    while(true) {
        std::cout << "\n";
        std::cout << MENU;  //display menu of input options
        std::getline(std::cin, input);  //store user input
        
        if(input == "A" || input == "a") {  //execute "Add" operation if user enters "A" or "a"
            
            //prompt for user input of flight number and first/last name
            bool valid_input = promptForInput();
            
            //if user input was valid, continue
            if(valid_input) {
            
                //prompt for and store address
                std::cout << "Enter address: ";
                std::getline(std::cin, address);
                
                //prompt for and store phone number
                std::cout << "Enter phone: ";
                std::getline(std::cin, number);
                
                int index = getFlightIndex(flight_no); //index of LinkedList corresponding to flight_no
                
                //insert this new passenger into the LinkedList corresponding to their flight number
                Passenger* p = new Passenger(name, surname, address, number);
                flights[index]->insert(*p);
            }

        } else if(input == "S" || input == "s") { //execute search operation if user enters "S" or "s"

            //prompt for and store name
            std::cout << "Enter last name: ";
            std::getline(std::cin, surname);
            
            //prompt for and store last name
            std::cout << "Enter first name: ";
            std::getline(std::cin, name);
            
            //do not continue if first/last name are not properly formatted;
            //if this is the case, print an error message
            if(hasNumber(name) || hasNumber(surname)) {
                std::cout << "Error: First/last name(s) contain numeric character(s)";
            } else {
                
                int index = 0;
                Passenger* p = new Passenger(name, surname, "", ""); //passenger passed as parameter in search() function
                char* f_no[] = {"100", "200", "300", "400"};    //valid flight numbers with same indexing as 'flights' array
                bool pass_found = false; //boolean value representing whether or not the passenger was found
                
                while(index < 4) {//search each list for the user-entered passenger
                    try {
                        //print passenger information if a passenger with matching first/last name
                        //exists in ANY of the four LinkedLists
                        Passenger &pass = flights[index]->search(*p);
                        std::cout << "Flight number: " << f_no[index] << "\n";
                        std::cout << "First name: " << pass.getName() << "\n";
                        std::cout << "Last name: " << pass.getSurname() << "\n";
                        std::cout << "Address: " << pass.getAddress() << "\n";
                        std::cout << "Phone: " << pass.getNumber() << "\n";
                        index++;
                        pass_found = true;
                    } catch(ElementNotFoundException) {//handle exception if passenger is not found in current list
                        index++;
                    }
                }
                //print error message if passenger is not found
                if(!pass_found)
                    std::cout << "Passenger not found\n";
            }
  
        } else if(input == "D" || input == "d") { //execute delete function if user enters "D" or "d"
            
            //prompt for user input of flight number and first/last name
            bool valid_input = promptForInput();
            
            //if user input was valid, continue
            if(valid_input) {
                int index = getFlightIndex(flight_no);  //index of LinkedList corresponding to flight_no
                Passenger* p = new Passenger(name, surname, "", ""); //passenger passed as parameter in deleteNode() function
                
                //attempt to delete the target passenger from the
                //LinkedList corresponding to their flight_no
                try {
                    flights[index]->deleteNode(*p);
                    std::cout << "The passenger is deleted\n";
                } catch(ElementNotFoundException) {
                    std::cout << "Passenger not found\n";
                }
            }
            
        } else if(input == "L" || input == "l") {//execute list function if user enters "L" or "l"
            
            //prompt for flight number
            std::cout << "Enter flight number: ";
            std::getline(std::cin, flight_no);
            
            //if the flight number is not valid, print error message and return false
            if(!validFlight(flight_no)) {
                std::cout << "Error: Invalid flight number\n";
            } else {//if flight number is valid, print all passengers in the corresponding LinkedList
                int index = getFlightIndex(flight_no); //index of LinkedList corresponding to flight_no
                std::cout << *flights[index];
            }
            
        } else if(input == "Q" || input == "q") {//terminate loop to cause function to end if user enters "Q" or "q"
            break;
            
        } else {
            std::cout << "Invalid input: please try again\n";
        }
    }
}

/*
 * Inserts string fields from Passenger 'p' into
 * the target outputstream
 */
std::ostream& operator<<(std::ostream &os, Passenger &p) {
    os << p.name << " " << p.surname << " [" << p.address
    << "] [" << p.number << "]";
    return os;
}

/*
 * This function will return true if the argument string s
 * contains any digits (0-9) at any position, or false otherwise;
 * code for this function was developed in part by referencing
 * information available at the following URL on Oct. 16, 2018
 *
 * https://stackoverflow.com/questions/9642292/function-to-check-if-string-contains-a-number
 */
bool hasNumber(const std::string& s) {
    return std::any_of(s.begin(), s.end(), ::isdigit);
}

/*
 * This function will return true if the argument string s
 * represents a valid flight number; there are only four valid
 * flight numbers: "100", "200", "300", or "400", per the assignment
 * specifications noted in the main funciton description. If s is not
 * equal to one of those strings, this function will return false
 */
bool validFlight(const std::string& s) {
    return (s == "100" || s == "200" ||
            s == "300" || s == "400");
}

/*
 * This function returns an numerical (0-3) index of the
 * LinkedList in the 'flights array which corresponds to
 * flight number f_no. In the case that f_no is not a valid
 * string as stated in the specification of main(), this method
 * returns -1 to prevent this program from behaving unexpectedly
 * in the event that flight numbers are not verified prior to
 * calling this method and/or utilizing the index it returns.
 */
int getFlightIndex(const std::string& f_no) {
    int index = -1;//index of flight number to be returned
    
    //assign index of the correct LinkedList for the flight_no entered by the user
    if(f_no == "100")
        index = 0;
    if(f_no == "200")
        index = 1;
    if(f_no == "300")
        index = 2;
    if(f_no == "400")
        index = 3;
    
    return index;
}

/*
 * Each time a user performs any of the add, search,
 * or delete operations in this program, this function
 * will prompt for user input and change the corresponding
 * global variables flight_no, first/last name, address
 * and phone number to match user-input, all while verifying
 * that user-entered information is consistent with
 * assignment specifications
 */
bool promptForInput() {
    //prompt for flight number
    std::cout << "Enter flight number: ";
    std::getline(std::cin, flight_no);
    
    //if the flight number is not valid, print error message and return false
    if(!validFlight(flight_no)) {
        std::cout << "Error: Invalid flight number\n";
        return false;
    } else {
        //prompt for and store name
        std::cout << "Enter last name: ";
        std::getline(std::cin, surname);
        
        //prompt for and store last name
        std::cout << "Enter first name: ";
        std::getline(std::cin, name);
        
        //print error message if either first or
        //last name contain any numeric values & return false
        if(hasNumber(name) || hasNumber(surname)) {
            std::cout << "Error: First/last name(s) contain numeric character(s)";
            return false;
        }
    }
    return true;
}

