#include "Order.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Order::totalOrders = 0;

Order::Order()
    : orderId(""), customer(nullptr), driver(nullptr), items(nullptr),
      itemCount(0), capacity(0), status(OrderStatus::PENDING) {
    totalOrders++;
}

Order::Order(string id, Customer* cust)
    : orderId(id), customer(cust), driver(nullptr), items(nullptr),
      itemCount(0), capacity(0), status(OrderStatus::PENDING) {
    totalOrders++;
}

Order::Order(const Order& other)
    : orderId(other.orderId), customer(other.customer), driver(other.driver),
      itemCount(other.itemCount), capacity(other.capacity), status(other.status) {
    if (capacity > 0) {
        items = new FoodItem[capacity];
        for (int i = 0; i < itemCount; i++) {
            items[i] = other.items[i];
        }
    } else {
        items = nullptr;
    }
    totalOrders++;
}

Order::~Order() {
    delete[] items;
    totalOrders--;
}

void Order::grow() {
    int newCap = (capacity == 0) ? 5 : capacity * 2;
    FoodItem* newItems = new FoodItem[newCap];
    for (int i = 0; i < itemCount; i++) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
    capacity = newCap;
}

void Order::addItem(const FoodItem& item) {
    if (itemCount >= capacity) grow();
    items[itemCount] = item;
    itemCount++;
}

void Order::assignDriver(DeliveryDriver* drv) {
    driver = drv;
}

void Order::updateStatus(OrderStatus newStatus) {
    status = newStatus;
    if (status == OrderStatus::DELIVERED) {
        if (driver) {
            driver->completeDelivery(calculateTotal());
            ++(*driver);
        }
        if (customer) {
            customer->addLoyaltyPoints(static_cast<int>(calculateTotal() * 2));
        }
    }
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (int i = 0; i < itemCount; i++) {
        total += items[i].calculateItemTotal();
    }
    return total;
}

void Order::displayOrder() const {
    cout << "Order ID: " << orderId << endl;
    if (customer) {
        cout << "Customer: " << customer->getName() << endl;
    }
    if (driver) {
        cout << "Driver: " << driver->getName() << endl;
    }
    cout << "Status: ";
    switch(status) {
        case OrderStatus::PENDING: cout << "PENDING"; break;
        case OrderStatus::PREPARING: cout << "PREPARING"; break;
        case OrderStatus::OUT_FOR_DELIVERY: cout << "OUT_FOR_DELIVERY"; break;
        case OrderStatus::DELIVERED: cout << "DELIVERED"; break;
        case OrderStatus::CANCELLED: cout << "CANCELLED"; break;
    }
    cout << endl;
    cout << "Items:" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << "  ";
        items[i].displayItem();
    }
    cout << "Total: " << fixed << setprecision(2) << calculateTotal() << " EGP" << endl;
}

int Order::getTotalOrders() {
    return totalOrders;
}

string Order::getOrderId() const {
    return orderId;
}

Customer* Order::getCustomer() const {
    return customer;
}

DeliveryDriver* Order::getDriver() const {
    return driver;
}

OrderStatus Order::getStatus() const {
    return status;
}

int Order::getItemCount() const {
    return itemCount;
}

Order& Order::operator+=(const FoodItem& item) {
    addItem(item);
    return *this;
}

Order Order::operator+(const Order& other) const {
    Order result(orderId + "_" + other.orderId, customer);
    for (int i = 0; i < itemCount; i++) {
        result.addItem(items[i]);
    }
    for (int i = 0; i < other.itemCount; i++) {
        result.addItem(other.items[i]);
    }
    return result;
}

FoodItem& Order::operator[](int index) {
    return items[index];
}

const FoodItem& Order::operator[](int index) const {
    return items[index];
}

ostream& operator<<(ostream& os, const Order& order) {
    os << "Order " << order.orderId << " - Total: "
       << fixed << setprecision(2) << order.calculateTotal() << " EGP";
    return os;
}

bool operator>(const Order& left, const Order& right) {
    return left.calculateTotal() > right.calculateTotal();
}
