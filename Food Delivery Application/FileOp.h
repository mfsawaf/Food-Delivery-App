#ifndef FILEOP_H
#define FILEOP_H

#include <string>
#include "Order.h"
#include "Delivery.h"
using namespace std;

void saveCompletedOrders(Order** orders, int orderCount);
void saveDriverStats(DeliveryDriver** drivers, int driverCount);

#endif
