#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include"baseClass.h"
class Caesar_Cipher:public base_class{
protected:
    int key;//key variable

public:
    Caesar_Cipher():key(0){};//constructor for set key 0

    void get_key(int k){//get key and set key value
        key=k;
    }

    //encrypt function
    string encrypt_msg(){
        int position;//store letter position
        bool to_upper=false;//use for handle uppercase lowercase
        int length = message.size();//length for handle loop
        for(int m=0;m<length;m++){//loop for traverse each letter
            //skip other signs
            if(!isalpha(message[m])){
                continue;
            }
            if(isupper(message[m])){//uppercase convert as lowercase
                message[m]=tolower(message[m]);
                to_upper=true;//set is upper value
            }
            position=letters.find(message[m]);//find letter index
            position =(position+key)%26;//get new index after shift using key
            if(to_upper){//uppercase letters again convert
                message[m]=toupper(letters[position]);
                to_upper=false;//change is upper
            }
            else{
                message[m]=letters[position];//lowercase replace without convert to upper
            }
        }
        return message;
    }

    //decrypt function
    string decrypt_msg(){
        int position;//store letter position
        bool to_upper=false;//use for handle uppercase lowercase
        int length = message.size();//length for handle loop
        for(int m=0;m<length;m++){//loop for traverse each letter
            if(!isalpha(message[m])){
                continue;
            }
            if(isupper(message[m])){//uppercase convert as lowercase
                message[m]=tolower(message[m]);
                to_upper=true;//set is upper value
            }
            position=letters.find(message[m]);//find letter index
            position =(position-key+26)%26;//get new index after shift using key
            if(to_upper){//uppercase letters again convert
                message[m]=toupper(letters[position]);
                to_upper=false;//change is upper
            }
            else{
                message[m]=letters[position];//lowercase replace without convert to upper
            }
        }
        return message;
    }

};

#endif // CAESARCIPHER_H
