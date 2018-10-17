#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
/*
 * Class header file written by Derek Avery
 * for Assignment 2 - CS 300 @ Bellevue College
 * Due Friday, October 19th, 2018
 */

/* 
 * This class represents a plane passenger, including relevant
 * fields such as name and address, as well as methods to 
 * retrieve and modify this information. This class will
 * work in conjunction with client code to aid in the creation
 * of a passenger 'database' for Assignment 2 as described above
 */
class Passenger {
	
	public:
    
        // Constructors //
        
        Passenger();                                                //default constructor
        Passenger(std::string name, std::string surname,            //main constructor; initializes name,
                  std::string address, std::string number);         //surname, address, and phone #
    
		// Functions //
    
        bool operator==(const Passenger& p);        //equal-to operator
        bool operator<(const Passenger& p);         //less-than operator
    
		std::string getName() const;		//getter; return passenger name
		std::string getSurname() const;		//getter; return passenger surname
		std::string getAddress() const;		//getter; return passenger address
		std::string getNumber() const;		//getter; return passenger phone #
	
		void setName(std::string _name);	    //setter; set passenger name
		void setSurname(std::string _surname);	//setter; set passenger surname
		void setAddress(std::string _address);	//setter; set passenger address
		void setNumber(std::string _number);	//setter; set passenger phone #
    
        friend std::ostream& operator<<(std::ostream &os, Passenger &p);   //return ostream w/ passenger information

	private:
		
		// Fields //

		std::string name;		    //passenger name
		std::string surname;		//passenger surname
		std::string address;		//passenger address
		std::string number;		    //passenger phone number
	
	
};

#endif /* PASSENGER_H */

