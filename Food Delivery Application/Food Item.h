#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
using namespace std;

class FoodItem {
    string itemName;
    double price;
    int quantity;

public:
    FoodItem();
    FoodItem(string name, double p, int q);

    string getItemName() const;
    double getPrice() const;
    int getQuantity() const;

    void setItemName(string name);
    void setPrice(double p);
    void setQuantity(int q);

    double calculateItemTotal() const;
    void displayItem() const;
};

#endif
