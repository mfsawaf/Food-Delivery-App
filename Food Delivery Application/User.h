#ifndef USER_H
#define USER_H

#include <string>
#include "Enum.h"
using namespace std;

class User {
protected:
    string userId;
    string name;
    string phoneNumber;
    static int totalUsers;

public:
    User();
    User(string id, string n, string phone);
    virtual ~User();

    virtual void displayInfo() const = 0;
    virtual double calculateEarnings() const = 0;

    static int getTotalUsers();
    string getUserId() const;
    string getName() const;
    string getPhoneNumber() const;
};

#endif
