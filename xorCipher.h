#ifndef XORCIPHER_H
#define XORCIPHER_H
#include"baseClass.h"//base class
#include<iostream>
#include<string>
using namespace std;

class xor_cipher:public base_class{
private:
    char key;//key for cipher
public:
    //use this for stire key
    void get_key(char k){
        key=k;
    }

    //encrypt function
    string encrypt(){
        int length=message.size();//length use to handle the loop
        for(int i=0;i<length;i++){
            message[i]=message[i]^key;//using this loop i apply xor operator for each letter
        }
        return message;//finally return the message
    }
    //decrypt function
    string decrypt(){
        int length=message.size();//length use to handle the loop
        for(int i=0;i<length;i++){
            message[i]=message[i]^key;//using this loop i apply xor operator for each letter
        }
        return message;//finally return the message
    }
};

#endif // XORCIPHER_H
