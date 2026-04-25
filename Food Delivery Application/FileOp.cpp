#include "FileOp.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

void saveCompletedOrders(Order** orders, int orderCount) {
    ofstream file("completed_orders.txt");

    cout << endl << "Saving completed orders..." << endl;
    file << "COMPLETED ORDERS" << endl;
    file << "================" << endl << endl;

    for (int i = 0; i < orderCount; i++) {
        if (orders[i]->getStatus() == OrderStatus::DELIVERED) {
            Order* o = orders[i];
            cout << o->getOrderId() << " - "
                 << fixed << setprecision(2) << o->calculateTotal() << " EGP" << endl;

            file << "Order: " << o->getOrderId() << endl;
            file << "Customer: " << o->getCustomer()->getName() << endl;
            file << "Total: " << fixed << setprecision(2) << o->calculateTotal() << " EGP" << endl;
            file << "------------------------" << endl;
        }
    }

    file.close();
    cout << "Saved to completed_orders.txt" << endl;
}

void saveDriverStats(DeliveryDriver** drivers, int driverCount) {
    ofstream file("driver_stats.txt");

    cout << endl << "Saving driver statistics..." << endl;
    file << "DRIVER STATISTICS" << endl;
    file << "=================" << endl << endl;

    for (int i = 0; i < driverCount; i++) {
        DeliveryDriver* d = drivers[i];
        cout << d->getName() << " - " << d->getCompletedDeliveries()
             << " deliveries - " << fixed << setprecision(2)
             << d->getTotalEarnings() << " EGP" << endl;

        file << d->getName() << endl;
        file << "Deliveries: " << d->getCompletedDeliveries() << endl;
        file << "Earnings: " << fixed << setprecision(2)
             << d->getTotalEarnings() << " EGP" << endl;
        file << "------------------------" << endl;
    }

    file.close();
    cout << "Saved to driver_stats.txt" << endl;
}
