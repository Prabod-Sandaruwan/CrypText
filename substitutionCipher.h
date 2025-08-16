#ifndef SUBSTITUTIONCIPHER_H
#define SUBSTITUTIONCIPHER_H
#include<string>
#include"baseClass.h"
using namespace std;

class substitution_cipher:public base_class{
protected:
    static string let_en;//pre defined substitution table

public:
    //encrypt function
    string encrypt(){
        int length=message.size();//message length
        int pos;//letter index
        bool up_low;//for handle uppercase
        for(int a=0;a<length;a++)//use to traverse each letter
        {
            char c=message[a];//set current character
            if(!isalpha(c)){
                continue;//non alphabetic skip
            }
            if(isupper(c)){//uppercase convert as lowercase
                c=tolower(c);
                up_low = true;//set is upper value
            }

            pos=letters.find(c);//find letter index
            if(up_low){//uppercase replace after convert again uppercase
                message[a]=toupper(let_en[pos]);
                up_low=0;
            }
            else{
                message[a]=let_en[pos];//lowercase replace without converting
            }
        }
        return message;
    }

    //decrypt function
    string decrypt(){
        int length=message.size();//message length
        int pos;//letter index
        bool up_low;//for handle uppercase
        for(int a=0;a<length;a++)//use to traverse each letter
        {
            char c=message[a];//set current character

            if(!isalpha(c)){//non alphabetic skip
                continue;
            }

            if(isupper(c)){//uppercase convert as lowercase
                c=tolower(c);
                up_low = 1;//set is upper value
            }

            pos=let_en.find(c);//find letter index
            if(up_low){//uppercase replace after convert again uppercase
                message[a]=toupper(letters[pos]);
                up_low=0;
            }
            else{
                message[a]=letters[pos];//lowercase replace without converting
            }
        }
        return message;
    }
};

#endif // SUBSTITUTIONCIPHER_H
