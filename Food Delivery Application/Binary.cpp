#include "Binary.h"
#include "Order.h"
#include <fstream>
#include <chrono>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

OrderRecord toRecord(const Order& o) {
    OrderRecord r;
    memset(&r, 0, sizeof(r));

    strcpy(r.orderId, o.getOrderId().c_str());
    strcpy(r.customerName, o.getCustomer()->getName().c_str());

    if (o.getDriver()) {
        strcpy(r.driverName, o.getDriver()->getName().c_str());
    }

    r.itemsCount = o.getItemCount();
    if (r.itemsCount > MAX_ITEMS) r.itemsCount = MAX_ITEMS;

    for (int i = 0; i < r.itemsCount; i++) {
        strcpy(r.itemNames[i], o[i].getItemName().c_str());
        r.itemPrices[i] = o[i].getPrice();
        r.itemQuantities[i] = o[i].getQuantity();
    }

    r.totalPrice = o.calculateTotal();
    r.status = static_cast<int>(o.getStatus());

    return r;
}

void saveBinary(const string& file, const OrderRecord& r) {
    ofstream f(file, ios::binary | ios::app);
    if (!f) return;

    f.write(reinterpret_cast<const char*>(&r), sizeof(r));
    f.close();
}

bool loadBinary(const string& file, int index, OrderRecord& out) {
    auto start = chrono::high_resolution_clock::now();

    ifstream f(file, ios::binary);
    if (!f) return false;

    f.seekg(index * sizeof(OrderRecord));
    f.read(reinterpret_cast<char*>(&out), sizeof(out));

    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Time: " << time.count() << " microseconds" << endl;

    return f.gcount() == sizeof(out);
}
