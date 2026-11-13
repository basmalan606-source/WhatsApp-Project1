#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User() {
        username = "";
        password = "";
        phoneNumber = "";
        status = "";
        updateLastSeen();
    }

    User(string uname, string pwd, string phone) {
        username = uname;
        password = pwd;
        phoneNumber = phone;
        updateLastSeen();
    }

    string getUsername() const {
        return username;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getStatus() const {
        return status;
    }

    string getLastSeen() const {
        return lastSeen;
    }

    void setStatus(string newStatus) {
        status = newStatus;
    }

    void setPhoneNumber(string phone) {
        phoneNumber = phone;
    }

    void updateLastSeen() {
        time_t currentTime = time(0);
        tm* timeInfo = localtime(&currentTime);
        char timeArr[20];
        strftime(timeArr, 20, "%d/%m/%Y %H:%M:%S", timeInfo );
        lastSeen = timeArr;
    }

    bool checkPassword(string pwd) const {

        return password == pwd;
    }

    void changePassword(string newPwd) {
        password = newPwd;
    }
};


