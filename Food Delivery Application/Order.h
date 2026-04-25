#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "Enum.h"
#include "Customer.h"
#include "Delivery.h"
#include "Food Item.h"
using namespace std;

class Order {
    string orderId;
    Customer* customer;
    DeliveryDriver* driver;
    FoodItem* items;
    int itemCount;
    int capacity;
    OrderStatus status;
    static int totalOrders;

    void grow();

public:
    Order();
    Order(string id, Customer* cust);
    Order(const Order& other);
    ~Order();

    void addItem(const FoodItem& item);
    void assignDriver(DeliveryDriver* drv);
    void updateStatus(OrderStatus newStatus);
    double calculateTotal() const;
    void displayOrder() const;

    static int getTotalOrders();

    string getOrderId() const;
    Customer* getCustomer() const;
    DeliveryDriver* getDriver() const;
    OrderStatus getStatus() const;
    int getItemCount() const;

    Order& operator+=(const FoodItem& item);
    Order operator+(const Order& other) const;
    FoodItem& operator[](int index);
    const FoodItem& operator[](int index) const;

    friend ostream& operator<<(ostream& os, const Order& order);
    friend bool operator>(const Order& left, const Order& right);
};

#endif
