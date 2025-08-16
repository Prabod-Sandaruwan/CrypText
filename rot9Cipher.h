#ifndef ROT9CIPHER_H
#define ROT9CIPHER_H
#include"baseClass.h"//base class
using namespace std;

class rot9:public base_class{
public:
    //encrypt function
    string encrypt(){
        int length=message.size();//message length
        int index;//letter index
        bool to_upper=false;//use to handle uppercase lowercase
        for(int i =0;i<length;i++){//use to traverse each an every letter
            if(!isalpha(message[i])){//non alphabetic skip
                continue;
            }
            if(isupper(message[i])){//conver uppercase as lowecase
                message[i]=tolower(message[i]);
                to_upper=true;//set is upper value
            }
            int index=letters.find(message[i]);//find letter index
            index=(index+9)%26;//encrypted index
            message[i]=letters[index];//replace encrypt letter

            if(to_upper){//uppercase again convert
                message[i]=toupper(message[i]);
                to_upper=false;//set again is upper
            }
        }
        return message;
    }

    //decrypt function
    string decrypt(){
        int length=message.size();//message length
        int index;//letter index
        bool to_upper=false;//use to handle uppercase lowercase
        for(int i =0;i<length;i++){//use to traverse each an every letter
            if(!isalpha(message[i])){//non alphabetic skip
                continue;
            }
            if(isupper(message[i])){//conver uppercase as lowecase
                message[i]=tolower(message[i]);
                to_upper=true;//set is upper value
            }
            int index=letters.find(message[i]);//find letter index
            index=(index-9+26)%26;//encrypted index
            message[i]=letters[index];//replace encrypt letter

            if(to_upper){//uppercase again convert
                message[i]=toupper(message[i]);
                to_upper=false;//set again is upper
            }
        }
        return message;
    }

};

#endif // ROT9CIPHER_H
