#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <string>
using namespace std;

class Customer : public User {
    string deliveryAddress;
    int loyaltyPoints;

public:
    Customer();
    Customer(string id, string n, string phone, string address);

    void displayInfo() const override;
    double calculateEarnings() const override;

    string getDeliveryAddress() const;
    int getLoyaltyPoints() const;
    void setDeliveryAddress(string address);
    void addLoyaltyPoints(int points);

    Customer& operator+=(int points);
};

#endif
