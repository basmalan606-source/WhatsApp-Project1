#include <iostream>
#include <string>
#include <ctime>
using namespace std;

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