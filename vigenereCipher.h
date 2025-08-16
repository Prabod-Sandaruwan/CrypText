#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H
#include "baseClass.h"//base class
#include<string>
#include <cctype>
using namespace std;


class vigenere_cipher:public base_class{
private:
    string key;

public:
    void get_key(string k){//key getter
        key=k;//assign key
    }
    //encrypt function
    string encrypt(){
        int key_pos;//current key letter index
        int key_index=0;//current key index position
        int char_pos;//character position
        bool to_upper=false;//use this to handle upppercase and lowercase

        char msg_char;//store current letter of message
        char key_char;//store current letter of key

        int length = message.length();
        int key_len = key.length();

        //loo[ for travers each letter of message
        for(int i=0;i<length;i++){
            msg_char=message[i];
            key_char=tolower(key[key_index]);

            if (!isalpha(msg_char)){//if its not letter skip the letter
                key_index++;
                //if key comes maximum length then again it return to 0th position
                if(key_index==key_len){
                    key_index=0;
                }
                continue;
            }

            if(isupper(msg_char)){//uppercase convert  to lowercase before encrypt
                msg_char=tolower(msg_char);
                to_upper = true;//set uppercase status
            }

            key_pos=letters.find(key_char);//get key character position
            char_pos=letters.find(msg_char);//get message character position

            char_pos=(char_pos+key_pos)%26;//set new letter position useing key and letter positions
            msg_char=letters[char_pos];//replece new letter

            if(to_upper){//check the is it convert befor lower case. if it converted letter again it convert uppercase and set the bool value
                msg_char=toupper(msg_char);
                to_upper=false;
            }

            message[i]=msg_char;
            key_index++;//key letter increment by 1
            //if key comes maximum length then again it return to 0th position
            if(key_index==key_len){
                key_index=0;
            }
        }
        return message;//return message
    }
    //decrypt function
    string decrypt(){
        int key_pos;//current key letter index
        int key_index=0;//current key index position
        int char_pos;//character position
        bool to_upper=false;//use this to handle upppercase and lowercase

        char msg_char;//store current letter of message
        char key_char;//store current letter of key

        int length = message.length();
        int key_len = key.length();
        //loo[ for travers each letter of message
        for(int i=0;i<length;i++){
            msg_char=message[i];
            key_char=tolower(key[key_index]);

            if (!isalpha(msg_char)){//if its not letter skip the letter
                key_index++;
                //if key comes maximum length then again it return to 0th position
                if(key_index==key_len){
                    key_index=0;
                }
                continue;
            }

            if(isupper(msg_char)){//uppercase convert  to lowercase before encrypt
                msg_char=tolower(msg_char);
                to_upper = true;//set uppercase status
            }

            key_pos=letters.find(key_char);//get key character position
            char_pos=letters.find(msg_char);//get message character position

            char_pos=(char_pos-key_pos+26)%26;//set new letter position useing key and letter positions
            msg_char=letters[char_pos];//replece new letter

            if(to_upper){//check the is it convert befor lower case. if it converted letter again it convert uppercase and set the bool value
                msg_char=toupper(msg_char);
                to_upper=false;
            }

            message[i]=msg_char;
            key_index++;//key letter increment by 1
            //if key comes maximum length then again it return to 0th position
            if(key_index==key_len){
                key_index=0;
            }
        }
        return message;//return message
    }

};

#endif // VIGENERECIPHER_H
