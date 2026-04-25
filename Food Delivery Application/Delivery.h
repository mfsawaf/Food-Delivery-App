#ifndef DELIVERY_H
#define DELIVERY_H

#include "User.h"
#include <string>
using namespace std;

class DeliveryDriver : public User {
    string vehicleType;
    int completedDeliveries;
    double totalEarnings;

public:
    DeliveryDriver();
    DeliveryDriver(string id, string n, string phone, string vehicle);

    void displayInfo() const override;
    double calculateEarnings() const override;

    void completeDelivery(double orderValue);

    DeliveryDriver& operator++();
    DeliveryDriver operator++(int);

    string getVehicleType() const;
    int getCompletedDeliveries() const;
    double getTotalEarnings() const;
};

#endif
