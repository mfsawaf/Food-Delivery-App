#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Enum.h"
#include "User.h"
#include "Customer.h"
#include "Delivery.h"
#include "Food Item.h"
#include "Order.h"
#include "FileOp.h"
#include "Binary.h"
using namespace std;

int main() {
    Customer** customers = nullptr;
    DeliveryDriver** drivers = nullptr;
    Order** orders = nullptr;

    int custCount = 0, drvCount = 0, ordCount = 0;
    int custCap = 0, drvCap = 0, ordCap = 0;

    int custId = 1, drvId = 1, ordId = 1000;

    while (true) {
        cout << endl;
        cout << "=== ELMENUS SYSTEM ===" << endl;
        cout << "1. Register New Customer" << endl;
        cout << "2. Register New Driver" << endl;
        cout << endl;
        cout << "3. Create New Order" << endl;
        cout << "4. Add Item to Order" << endl;
        cout << "5. Assign Driver to Order" << endl;
        cout << "6. Update Order Status" << endl;
        cout << "7. Display Order Details" << endl;
        cout << endl;
        cout << "8. Display Customers Information " << endl;
        cout << "9. Display Drivers Information " << endl;
        cout << "10. Compare two Orders by Total " << endl;
        cout << "11. Display System Stats" << endl;
        cout << endl;
        cout << "12. Save Completed Orders to File" << endl;
        cout << "13. Save Driver Statistics to File" << endl;
        cout << endl;
        cout << "14. Save Order to Binary File" << endl;
        cout << "15. Load Order by Position" << endl;
        cout << "16. Binary File to Statistics" << endl;
        cout << endl;
        cout << "0. Exit" << endl;
        cout << "=====================" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        if (ch == 0) break;

        if (ch == 1) {
            if (custCount >= custCap) {
                custCap = (custCap == 0) ? 2 : custCap * 2;
                Customer** tmp = new Customer*[custCap];
                for (int i = 0; i < custCount; i++) tmp[i] = customers[i];
                delete[] customers;
                customers = tmp;
            }

            string n, p, a;
            cout << "Name: ";
            cin >> n;
            cout << "Phone: ";
            cin >> p;
            cout << "Address: ";
            cin >> a;

            customers[custCount] = new Customer("C" + to_string(custId++), n, p, a);
            custCount++;
            cout << "Customer added" << endl;
        }
        else if (ch == 2) {
            if (drvCount >= drvCap) {
                drvCap = (drvCap == 0) ? 2 : drvCap * 2;
                DeliveryDriver** tmp = new DeliveryDriver*[drvCap];
                for (int i = 0; i < drvCount; i++) tmp[i] = drivers[i];
                delete[] drivers;
                drivers = tmp;
            }

            string n, p, v;
            cout << "Name: ";
            cin >> n;
            cout << "Phone: ";
            cin >> p;
            cout << "Vehicle: ";
            cin >> v;

            drivers[drvCount] = new DeliveryDriver("D" + to_string(drvId++), n, p, v);
            drvCount++;
            cout << "Driver added" << endl;
        }
        else if (ch == 3) {
            if (custCount == 0) {
                cout << "No customers" << endl;
                continue;
            }

            if (ordCount >= ordCap) {
                ordCap = (ordCap == 0) ? 2 : ordCap * 2;
                Order** tmp = new Order*[ordCap];
                for (int i = 0; i < ordCount; i++) tmp[i] = orders[i];
                delete[] orders;
                orders = tmp;
            }

            int idx;
            cout << "Customer index: ";
            cin >> idx;

            if (idx < 0 || idx >= custCount) {
                cout << "Invalid" << endl;
                continue;
            }

            orders[ordCount] = new Order("O" + to_string(ordId++), customers[idx]);
            ordCount++;
            cout << "Order created" << endl;
        }
        else if (ch == 4) {
            if (ordCount == 0) {
                cout << "No orders" << endl;
                continue;
            }

            int idx;
            cout << "Order index: ";
            cin >> idx;

            if (idx < 0 || idx >= ordCount) {
                cout << "Invalid" << endl;
                continue;
            }

            string n;
            double p;
            int q;
            cout << "Item name: ";
            cin >> n;
            cout << "Price: ";
            cin >> p;
            cout << "Quantity: ";
            cin >> q;

            orders[idx]->operator+=(FoodItem(n, p, q));
            cout << "Item added" << endl;
        }
        else if (ch == 5) {
            if (ordCount == 0 || drvCount == 0) {
                cout << "Need orders and drivers" << endl;
                continue;
            }

            int oi, di;
            cout << "Order index: ";
            cin >> oi;
            cout << "Driver index: ";
            cin >> di;

            if (oi < 0 || oi >= ordCount || di < 0 || di >= drvCount) {
                cout << "Invalid" << endl;
                continue;
            }

            orders[oi]->assignDriver(drivers[di]);
            cout << "Driver assigned" << endl;
        }
        else if (ch == 6) {
            if (ordCount == 0) {
                cout << "No orders" << endl;
                continue;
            }

            int idx;
            cout << "Order index: ";
            cin >> idx;

            if (idx < 0 || idx >= ordCount) {
                cout << "Invalid" << endl;
                continue;
            }

            int s;
            cout << "Status (0-4): ";
            cin >> s;

            orders[idx]->updateStatus(static_cast<OrderStatus>(s));
            cout << "Status updated" << endl;
        }
        else if (ch == 7) {
            if (ordCount == 0) {
                cout << "No orders" << endl;
                continue;
            }

            int idx;
            cout << "Order index: ";
            cin >> idx;

            if (idx < 0 || idx >= ordCount) {
                cout << "Invalid" << endl;
                continue;
            }

            orders[idx]->displayOrder();
        }
        else if (ch == 8) {
            if (custCount == 0) {
                cout << "No customers" << endl;
                continue;
            }

            for (int i = 0; i < custCount; i++) {
                customers[i]->displayInfo();
                cout << endl;
            }
        }
        else if (ch == 9) {
            if (drvCount == 0) {
                cout << "No drivers" << endl;
                continue;
            }

            for (int i = 0; i < drvCount; i++) {
                drivers[i]->displayInfo();
                cout << endl;
            }
        }
        else if (ch == 10) {
            if (ordCount < 2) {
                cout << "Need 2 orders" << endl;
                continue;
            }

            int a, b;
            cout << "First order: ";
            cin >> a;
            cout << "Second order: ";
            cin >> b;

            if (a < 0 || a >= ordCount || b < 0 || b >= ordCount) {
                cout << "Invalid" << endl;
                continue;
            }

            if (*orders[a] > *orders[b]) {
                cout << "Order " << a << " has higher total" << endl;
            } else if (*orders[b] > *orders[a]) {
                cout << "Order " << b << " has higher total" << endl;
            } else {
                cout << "Same total" << endl;
            }
        }
        else if (ch == 11) {
            cout << "Total users: " << User::getTotalUsers() << endl;
            cout << "Total orders: " << Order::getTotalOrders() << endl;
            cout << "Customers: " << custCount << endl;
            cout << "Drivers: " << drvCount << endl;
            cout << "Active orders: " << ordCount << endl;
        }
        else if (ch == 12) {
            saveCompletedOrders(orders, ordCount);
        }
        else if (ch == 13) {
            saveDriverStats(drivers, drvCount);
        }
        else if (ch == 14) {
            for (int i = 0; i < ordCount; i++) {
                OrderRecord r = toRecord(*orders[i]);
                saveBinary("orders.dat", r);
            }
            cout << "Saved to binary" << endl;
        }
        else if (ch == 15) {
            int pos;
            cout << "Position: ";
            cin >> pos;

            OrderRecord r;
            if (loadBinary("orders.dat", pos, r)) {
                cout << "Order ID: " << r.orderId << endl;
                cout << "Customer: " << r.customerName << endl;
                cout << "Total: " << fixed << setprecision(2) << r.totalPrice << " EGP" << endl;
            } else {
                cout << "Not found" << endl;
            }
        }
        else if (ch == 16) {
            ifstream file("orders.dat", ios::binary | ios::ate);
            if (!file) {
                cout << "No binary file" << endl;
                continue;
            }

            streampos size = file.tellg();
            int recs = size / sizeof(OrderRecord);

            cout << "File size: " << size << " bytes" << endl;
            cout << "Record size: " << sizeof(OrderRecord) << " bytes" << endl;
            cout << "Records: " << recs << endl;

            file.close();
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }

    for (int i = 0; i < custCount; i++) delete customers[i];
    for (int i = 0; i < drvCount; i++) delete drivers[i];
    for (int i = 0; i < ordCount; i++) delete orders[i];

    delete[] customers;
    delete[] drivers;
    delete[] orders;

    cout << "Exit" << endl;

    return 0;
}
