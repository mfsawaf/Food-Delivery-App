#include "User.h"

int User::totalUsers = 0;

User::User() : userId(""), name(""), phoneNumber("") {
    totalUsers++;
}

User::User(string id, string n, string phone)
    : userId(id), name(n), phoneNumber(phone) {
    totalUsers++;
}

User::~User() {
    totalUsers--;
}

int User::getTotalUsers() {
    return totalUsers;
}

string User::getUserId() const {
    return userId;
}

string User::getName() const {
    return name;
}

string User::getPhoneNumber() const {
    return phoneNumber;
}
