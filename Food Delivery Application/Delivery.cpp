#include "Delivery.h"
#include <iostream>
#include <iomanip>
using namespace std;

DeliveryDriver::DeliveryDriver()
    : User(), vehicleType(""), completedDeliveries(0), totalEarnings(0.0) {}

DeliveryDriver::DeliveryDriver(string id, string n, string phone, string vehicle)
    : User(id, n, phone), vehicleType(vehicle), completedDeliveries(0), totalEarnings(0.0) {}

void DeliveryDriver::displayInfo() const {
    cout << "Driver ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Vehicle: " << vehicleType << endl;
    cout << "Completed Deliveries: " << completedDeliveries << endl;
    cout << "Total Earnings: " << fixed << setprecision(2) << totalEarnings << " EGP" << endl;
    if (completedDeliveries > 0) {
        cout << "Average: " << totalEarnings / completedDeliveries << " EGP per delivery" << endl;
    }
}

double DeliveryDriver::calculateEarnings() const {
    return totalEarnings;
}

void DeliveryDriver::completeDelivery(double orderValue) {
    totalEarnings += orderValue * 0.15;
    completedDeliveries++;
}

DeliveryDriver& DeliveryDriver::operator++() {
    completedDeliveries++;
    return *this;
}

DeliveryDriver DeliveryDriver::operator++(int) {
    DeliveryDriver temp = *this;
    completedDeliveries++;
    return temp;
}

string DeliveryDriver::getVehicleType() const {
    return vehicleType;
}

int DeliveryDriver::getCompletedDeliveries() const {
    return completedDeliveries;
}

double DeliveryDriver::getTotalEarnings() const {
    return totalEarnings;
}
