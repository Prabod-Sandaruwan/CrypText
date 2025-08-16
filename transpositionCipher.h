#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "baseClass.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class transposition_cipher : public base_class {
protected:
    string key;
    string message_en;
    string key_sort;
    int rows, cols;//row and col for matrix
    vector<vector<char>> matrix;//declare matrix

public:
    void get_key(string k) {
        key = k;//set key
        key_sort = key;//store for sort key
        sort(key_sort.begin(), key_sort.end());//sort key

        cols = key.length();//set cols
        rows = (message.length() + cols - 1) / cols;//set rows

        matrix = vector<vector<char>>(rows, vector<char>(cols, ' '));//resize matrix and fill with ' '

        int index = 0;//current index
        for (int r = 0; r < rows && index < message.length(); r++) {//traverse each row
            for (int c = 0; c < cols && index < message.length(); c++) {//traverse each column
                matrix[r][c] = message[index];//replace letter
                index++;
            }
        }
    }

    //encrypt function
    string encrypt() {
        string message_en = "";//message encrypt set default
        vector<bool> used(cols, false);//array for track column use details

        for (int i = 0; i < cols; i++) {//traverse each letter of sorted key
            for (int j = 0; j < cols; j++) {//loop for find sorted opsition key in original key
                if (used[j]==false && key_sort[i]==key[j]) {//if it not printed allow anstructions
                    used[j] = true;//mark it as used letter
                    for (int r = 0; r < rows; r++) {//according column it write each row letter
                            message_en += matrix[r][j];
                    }
                    break;
                }
            }
        }

        message = message_en;//set base class message
        return message;
    }
    //decrypt function
    string decrypt(string msg, string key) {
        string de_msg;//variable for decrypt message store befor return it base class
        int cols = key.length();//column set
        int rows = (msg.length() + cols - 1) / cols;//row set

        string key_sort = key;//variable for sort key and assign befor sorting original key
        sort(key_sort.begin(), key_sort.end());//key sorting

        vector<vector<char>> matrix(rows, vector<char>(cols, ' '));//vector for store letters
        vector<bool> used(cols, false);//vector for track used letters

        int position = 0;//store message current index
        for (int i = 0; i < cols; i++) {//travel sorted letters
            for (int j = 0; j < cols; j++) {//travel each column
                if (!used[j] && key[j] == key_sort[i]) {//check used letters and store values column by column
                    used[j] = true;//set letter as used
                    for (int r = 0; r < rows; r++) {//loop for travel each row
                        if (position < msg.length()) {
                            matrix[r][j] = msg[position];//set letters
                            position++;
                        }
                    }
                    break;
                }
            }
        }

        //print full matrix
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                    de_msg += matrix[r][c];
            }
        }

        return de_msg;
    }
};

#endif // TRANSPOSITIONCIPHER_H
