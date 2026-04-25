#include "Customer.h"
#include <iostream>
using namespace std;

Customer::Customer() : User(), deliveryAddress(""), loyaltyPoints(0) {}

Customer::Customer(string id, string n, string phone, string address)
    : User(id, n, phone), deliveryAddress(address), loyaltyPoints(0) {}

void Customer::displayInfo() const {
    cout << "Customer ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Address: " << deliveryAddress << endl;
    cout << "Loyalty Points: " << loyaltyPoints << endl;
    cout << "Points value: " << calculateEarnings() << " EGP" << endl;
}

double Customer::calculateEarnings() const {
    return loyaltyPoints * 0.5;
}

string Customer::getDeliveryAddress() const {
    return deliveryAddress;
}

int Customer::getLoyaltyPoints() const {
    return loyaltyPoints;
}

void Customer::setDeliveryAddress(string address) {
    deliveryAddress = address;
}

void Customer::addLoyaltyPoints(int points) {
    loyaltyPoints += points;
}

Customer& Customer::operator+=(int points) {
    loyaltyPoints += points;
    return *this;
}
