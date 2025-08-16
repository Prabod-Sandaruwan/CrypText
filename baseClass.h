#ifndef BASECLASS_H
#define BASECLASS_H



#include <ostream>
#include<string>
using namespace std;

//base class

class base_class{
protected:
    string message;//store every cipher message
    static string letters;//letter string for find letter position
public:
    void get_msg(string msg){//get msg
        message=msg;
    }
    string show_message(){//show message
        return message;
    }
    virtual  string encrypt(){//base class encrypt function
        string msg="this is base class";
        return msg;
    }
};

#endif // BASECLASS_H
