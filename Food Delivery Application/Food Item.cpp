#include "Food Item.h"

#include <iostream>
#include <iomanip>
using namespace std;

FoodItem::FoodItem() : itemName(""), price(0.0), quantity(0) {}

FoodItem::FoodItem(string name, double p, int q)
    : itemName(name), price(p), quantity(q) {}

string FoodItem::getItemName() const {
    return itemName;
}

double FoodItem::getPrice() const {
    return price;
}

int FoodItem::getQuantity() const {
    return quantity;
}

void FoodItem::setItemName(string name) {
    itemName = name;
}

void FoodItem::setPrice(double p) {
    price = p;
}

void FoodItem::setQuantity(int q) {
    quantity = q;
}

double FoodItem::calculateItemTotal() const {
    return price * quantity;
}

void FoodItem::displayItem() const {
    cout << itemName << " x" << quantity << " @ "
         << fixed << setprecision(2) << price
         << " EGP = " << calculateItemTotal() << " EGP" << endl;
}
