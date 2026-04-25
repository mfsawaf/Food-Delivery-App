#ifndef BINARY_H
#define BINARY_H

#include <string>
using namespace std;

const int MAX_ITEMS = 20;

class Order;

struct OrderRecord {
    char orderId[50];
    char customerName[100];
    char driverName[100];
    int itemsCount;
    char itemNames[MAX_ITEMS][100];
    double itemPrices[MAX_ITEMS];
    int itemQuantities[MAX_ITEMS];
    double totalPrice;
    int status;
};

OrderRecord toRecord(const Order& o);
void saveBinary(const string& file, const OrderRecord& r);
bool loadBinary(const string& file, int index, OrderRecord& out);

#endif
