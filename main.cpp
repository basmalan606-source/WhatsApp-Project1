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
        strftime(timeArr, 20, "%d/%m/%Y %H:%M:%S", timeInfo);
        lastSeen = timeArr;
    }

    bool checkPassword(string pwd) const {

        return password == pwd;
    }

    void changePassword(string newPwd) {
        password = newPwd;
    }
};

// ========================
//      MESSAGE CLASS
// ========================
 class Message {
private:
     string sender;
     string content;
     string timestamp;
     string status;
     Message* replyTo;
public:
     Message(){
    sender = " ";
    content = " ";
    timestamp = " ";
    status = " ";
    replyTo = nullptr;
     }
     Message(string sndr, string cntnt){
    sender = sndr;
    content = cntnt;
    status = "sent";
    replyTo = nullptr;
    updateTimestamp();
   }
     string getContent() const{
     return content;
     }
     string getSender() const{
     return sender;
     }
     string getTimestamp() const{
     return timestamp;
     }
     string getStatus() const{
         return status;
     }
     Message* getReplyTo() const{
    return replyTo;
     }
     void setStatus(string newStatus){
     if( newStatus == "sent" || newStatus == "delivered" || newStatus == "read")
         status = newStatus;
     }
     void setReplyTo (Message* msg){
      replyTo = msg;
     }
     void updateTimestamp(){
    time_t t = time(0);
    timestamp = ctime(&t);
    cout << timestamp;
     }
     void display() const{
    cout << "\n [" << timestamp << "]" << endl;
    cout << sender << ":" << content << endl;
    cout << "Status:" << status << endl;
       if(replyTo != nullptr){
        cout <<"Reply to:" << replyTo->content << "\"" << endl;
       }
    }
    void addEmoji(string emojicode){
        if(emojicode == ":)" ){
            content += "\xF0\x9F\x99\x82";
        }
        else if(emojicode == ":(" ){
            content += "\xF0\x9F\x99\x81";
        }
        else if(emojicode == ":D" ){
            content += "\xF0\x9F\x98\x83";
        }
        else if(emojicode == "<3" ){
            content += "\xE2\x9D\xA4";
        }
        else if(emojicode == ":thumbsup:" ){
            content += "\xF0\x9F\x91\x8D";
        }
     }   
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat() {
        // TODO: Implement default constructor
    }

    Chat(vector<string> users, string name) {
        // TODO: Implement parameterized constructor
    }

    void addMessage(const Message& msg) {
        // TODO: Implement message addition
    }

    bool deleteMessage(int index, const string& username) {
        // TODO: Implement message deletion
        return false;
    }

    virtual void displayChat() const {
        // TODO: Implement chat display
    }

    vector<Message> searchMessages(string keyword) const {
        // TODO: Implement message search
        return {};
    }

    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2) {
        // TODO: Implement constructor
    }

    void displayChat() const override {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator) {
        chatName = name;
        participants = users;
        bool creatorexists = false;
        for (int i = 0;i < users.size();i++) {
            if (users[i] == creator) {
                creatorexists = true;
                break;
            }
        }
        if (!creatorexists) {
            participants.push_back(creator);
        }
        admins.push_back(creator);
        description = "No description provided.";

    }

    void addAdmin(string newAdmin) {
        if (!isAdmin(newAdmin) && isParticipant(newAdmin)) {
            admins.push_back(newAdmin);
            cout << "User " << newAdmin << " is now an admin.\n";
        }
        else {
            cout << "User " << newAdmin << "can't be added as an admin.\n";
        }
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        if (!isAdmin(admin)) {
            return false;
        }
        for (int i = 0;i < participants.size();i++) {
            if (participants[i] == userToRemove) {
                participants.erase(participants.begin() + i);
                for (int j = 0;j < admins.size();j++) {
                    if (admins[j] == userToRemove) {
                        admins.erase(admins.begin() + j);
                        break;
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool isAdmin(string username) const {
        for (int i = 0;i < admins.size();i++) {
            if (admins[i] == username) {
                return true;
            }
        }
        return false;
    }

    bool isParticipant(string username) const {
        for (int i = 0;i < participants.size();i++) {
            if (participants[i] == username) {
                return true;
            }
        }
        return false;
    }

    void setDescription(string desc) {
        description = desc;
    }

    void displayChat() const override {
        cout << "\n=== Group Chat: " << chatName << " ===" << endl;
        cout << "Description: " << description << endl;
        cout << "Participants (" << participants.size() << "): ";
        for (int i = 0;i < participants.size();i++) {
            cout << participants[i] << " ";
        }
        cout << endl;
        cout << "Admins (" << admins.size() << "): ";
        for (int i = 0;i < admins.size();i++) {
            cout << admins[i] << " ";
        }
        cout << endl;
        cout << "--- Messages ---\n";
        if (messages.empty()) {
            cout << "No messages yet.\n";
        }
        else {
            for (int i = 0;i < messages.size();i++) {
                cout << "[" << i << "]";
                messages[i].display();
            }
        }

    }

    void sendJoinRequest(const string& username) {
        cout << "User " << username << " sent a join request to group " << chatName << " .\n";
    }
    

};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getUsername() == username)
            {
                return i;
            }
        }
        return -1;
    }
    // .....
    bool isLoggedIn() const {
        if (currentUserIndex != -1)
        {
            return true;
        }
        return false;
    }

    string getCurrentUsername() const {
        if (isLoggedIn())
        {
            return users[currentUserIndex].getUsername();
        }
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp() {
        string username, password, phone;
        cout << "Enter Username: ";
        cin >> username;
        if (findUserIndex(username) != -1)
        {
            cout << "Username already exists!\n";
            return;
        }
        cout << "Enter Password: ";
        cin >> password;
        if (password.length() < 6) {
            cout << "Password must be at least 6 characters!\n";
            return;
        }
        cout << "Enter Phone Number: ";
        cin >> phone;
        users.push_back(User(username, password, phone));
        cout << "Account created successfully!\n";
    }

    void login() {
        string username, password;
        cout << "Enter Username: ";
        cin >> username;
        int index = findUserIndex(username);
        if (index == -1)
        {
            cout << "User not found! \n";
            return;
        }
        cout << "Enter Password: ";
        cin >> password;
        if (users[index].checkPassword(password))
        {
            currentUserIndex = index;
            users[index].setStatus("Online");
            cout << "Login Successfully!\n";
        }
        else {
            cout << "Incorrect password!\n";
        }
    }

    void startPrivateChat() {
        if (!isLoggedIn()) {
            cout << "Please Login First!\n";
            return;
        }
        string username;
        cout << "Enter Username: ";
        cin >> username;
        int index = findUserIndex(username);
        if (index == -1) {
            cout << "User Not Found!\n";
            return;
        }
        if (username == getCurrentUsername())
        {
            cout << "You can't chat with yourself! \n";
            return;
        }
        PrivateChat* newChat = new PrivateChat(getCurrentUsername(), username);
        chats.push_back(newChat);
        cout << "Private chat created successfully!\n";
    }

    void createGroup() {
        if (!isLoggedIn()) {
            cout << "Please Login First!\n";
            return;
        }
        string groupName;
        int numberOfUsers;
        cin.ignore(1000, '\n');
        cout << "Enter Group Name: ";
        getline(cin, groupName);
        cout << "Enter number of participants: ";
        cin >> numberOfUsers;
        if (groupName.empty() || numberOfUsers < 1) {
            cout << "Group must have a name & at least 2 participants!\n";
            return;
        }
        vector<string> groupUsers;
        for (int i = 0; i < numberOfUsers; i++)
        {
            string username;
            cout << "Enter Participant: " << i + 1 << ":";
            cin >> username;
            if (findUserIndex(username) == -1) {
                cout << "User not found!\n";
                return;
            }
            if (username == getCurrentUsername()) {
                cout << "You are already the group creator!\n";
                return;
            }
            bool exists = false;
            for (int j = 0; j < groupUsers.size(); j++) {
                if (groupUsers[j] == username) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                cout << "User already added!\n";
                return;
            }
            groupUsers.push_back(username);
        }
        GroupChat* newGroup = new GroupChat(groupUsers, groupName, getCurrentUsername());
        chats.push_back(newGroup);
        cout << "Group created successfully!\n";
    }

    void viewChats() const {
        if (!isLoggedIn()) {
            cout << "Please Login First!\n";
            return;
        }
        if (chats.empty()) {
            cout << "You have no chats yet!\n";
            return;
        }
        bool found = false;
        for (int i = 0; i < chats.size(); i++) {
            GroupChat* group = dynamic_cast<GroupChat*>(chats[i]);
            if (group != nullptr) {
                if (group->isParticipant(getCurrentUsername())) {
                    cout << "\nChat " << i + 1 << endl;
                    chats[i]->displayChat();
                    found = true;
                }
            }
            else {
                chats[i]->displayChat();
                found = true;
            }
        }
        if (!found) {
            cout << "You have no chats yet!\n";
        }
    }

    void logout() {
        if (isLoggedIn()) {
            users[currentUserIndex].updateLastSeen();
            users[currentUserIndex].setStatus("Offline");
            cout << getCurrentUsername() << " logged out successfully!\n";
            currentUserIndex = -1;
        }
    }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
