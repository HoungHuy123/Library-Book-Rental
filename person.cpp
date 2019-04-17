#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName) {
    // complete constructor
    cardID = cardNo;
    active = act;
    firstName = fName;
    lastName = lName;
}

string Person::getFirstName() {
    return firstName; // complete
}

string Person::getLastName() {
    return lastName; // complete
}

int Person::getId() {
    return cardID; // complete
}

void Person::setActive(bool act) {
    active = act;
} // complete

bool Person::isActive() {
    if (active == true) 
        return true;
    else 
        return false; // complete
}

string Person::fullName() {
    return firstName + " " + lastName; // complete
}