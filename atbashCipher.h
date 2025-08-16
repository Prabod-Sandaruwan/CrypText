#ifndef ATBASHCIPHER_H
#define ATBASHCIPHER_H

#include<string>
#include"baseClass.h"//base class
using namespace std;


class  atbash_Cipher:public base_class{
public:
    //encrypt function
    string encrypt_msg(){
        int length = message.size();//length
        for(int i=0;i<length;i++){//loop for traverse each letter

            //uppercase letter encrypt
            if(isupper(message[i])){
                char ch=message[i];
                message[i]=('Z'-(ch-'A'));
            }

            //lowercase letter encryption
            else if(islower(message[i])){
                char ch=message[i];
                message[i]=('z'-(ch-'a'));
            }
            else{
                continue;//non letter skip
            }
        }
        return message;//return message
    }

    //decrypt function
    string decrypt_msg(){
        int length = message.size();//length
        for(int i=0;i<length;i++){//loop for traverse each letter

            //uppercase letter decrypt
            if(isupper(message[i])){
                char ch=message[i];
                message[i]=('Z'-(ch-'A'));
            }

            //lowercase letter decrypt
            else if(islower(message[i])){
                char ch=message[i];
                message[i]=('z'-(ch-'a'));
            }
            else{
                continue;//non letter skip
            }
        }
        return message;//return message
    }
};



#endif // ATBASHCIPHER_H
