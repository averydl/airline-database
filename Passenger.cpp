#include "LinkedList.h"
#include "Passenger.h"
#include <iostream> 
#include <algorithm>
/*
 * Default constructor
 */
Passenger::Passenger() {}

/* 
 * Primary constructor; initializes all fields of the Passenger class
 * to the argument values provided to the constructor
 */	
Passenger::Passenger(std::string _name, std::string _surname, 	
			std::string _address, std::string _number) {
	name = _name;
	surname = _surname;
	address = _address;
	number = _number;
}

/*
 * Overridden equal-to operator; returns true IFF both the name and surname
 * string fields of the Passenger parameter are equal to those in the calling instance
 */
bool Passenger::operator==(const Passenger& p) {
    //convert parameter 'p' name and surname fields to upper case
    std::string p_surname = p.surname;
    std::transform(p_surname.begin(), p_surname.end(), p_surname.begin(), ::toupper);
    
    std::string p_name = p.name;
    std::transform(p_name.begin(), p_name.end(), p_name.begin(), ::toupper);
    
    //convert instance name and surname fields to upper case
    std::string _surname = this->surname;
    std::transform(_surname.begin(), _surname.end(), _surname.begin(), ::toupper);
    
    std::string _name = this->name;
    std::transform(_name.begin(), _name.end(), _name.begin(), ::toupper);
    
    //return true if upper-case first/last name of the calling instance
    //are equal to the upper-case first/last name of p
    return (_surname == p_surname && _name == p_name);
}

/*
 * Overridden less-than operator; returns true if the
 * instance Passenger has a 'surname' field which
 * evaluates to less-than the surname field of p
 * after converting both to upper-case
 *
 * -OR-
 *
 * In the case that the surname fields are 'equal', returns true
 * if the calling instance's 'name' field evaluates to less-than
 * the argument Passenger's name field after converting both
 * to upper-case
 */
bool Passenger::operator<(const Passenger& p) {
    //convert parameter 'p' name and surname fields to upper case
    std::string p_surname = p.surname;
    std::transform(p_surname.begin(), p_surname.end(), p_surname.begin(), ::toupper);
    
    std::string p_name = p.name;
    std::transform(p_name.begin(), p_name.end(), p_name.begin(), ::toupper);
    
    //convert instance name and surname fields to upper case
    std::string _surname = this->surname;
    std::transform(_surname.begin(), _surname.end(), _surname.begin(), ::toupper);
    
    std::string _name = this->name;
    std::transform(_name.begin(), _name.end(), _name.begin(), ::toupper);
    
    //compare name/surname of this instance and the parameter p and return
    //true/false given the criteria listed above in the function description
    if(_surname == p_surname)
        return (_name < p_name);
    else
        return (_surname < p_surname);
}

/*
 * 'Getter' method which returns the 'name'
 * field of an instance of Passenger
 */
std::string Passenger::getName() const {
	return name;
}

/*
 * 'Getter' method which returns the 'surname'
 * field of an instance of Passenger
 */
std::string Passenger::getSurname() const {
	return surname;
}

/*
 * 'Getter' method which returns the 'address'
 * field of an instance of Passenger
 */
std::string Passenger::getAddress() const  {
	return address;
}
/*
 * 'Getter' method which returns the 'number'
 * field of an instance of Passenger
 */
std::string Passenger::getNumber() const {
	return number;
}

/*
 * 'Setter' method which changes the 'name'
 * field of an instance of Passenger to _name
 */
void Passenger::setName(std::string _name) {
	name = _name;
}

/*
 * 'Setter' method which changes the 'surname'
 * field of an instance of Passenger to _surname
 */
void Passenger::setSurname(std::string _surname) {
	name = _surname;
}

/*
 * 'Setter' method which changes the 'address'
 * field of an instance of Passenger to _address
 */
void Passenger::setAddress(std::string _address) {
	address = _address;
}

/*
 * 'Setter' method which changes the 'number'
 * field of an instance of Passenger to _number
 */
void Passenger::setNumber(std::string _number) {
	number = _number;
}
