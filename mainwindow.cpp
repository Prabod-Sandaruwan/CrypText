#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>

//this is constructor for main window.in here i set caesar ceapher as dafault window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Cryptext");
    this->setFixedSize(this->size());

    ui->carsar_window->setVisible(true);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(false);
    //using this user cant decrypt message befor encrypt
    ui->decrypt->setEnabled(false);
    ui->key_description->setVisible(false);
    ui->key->setValidator(new QIntValidator(0, 25, this));//user cant enter out of range in caesar cipher

}

MainWindow::~MainWindow()
{
    delete ui;
}
//

//this is key string. im use this for encryption
string substitution_cipher::let_en = "qwertyuiopasdfghjklzxcvbnm";
string base_class::letters = "abcdefghijklmnopqrstuvwxyz";//this is the substitution table

//this value use for store the message status in file handling part. it helps me to restore file correctly
bool is_encrypt;

//this area functions for open own window for each cipher
void MainWindow::on_caesarBtn_clicked()
{
    ui->carsar_window->setVisible(true);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(false);
}

void MainWindow::on_atbashBtn_clicked()
{

    ui->carsar_window->setVisible(false);
    ui->atbash_window->setVisible(true);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(false);
}

void MainWindow::on_vigenereBtn_clicked()
{
    ui->carsar_window->setVisible(false);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(true);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(false);
}

void MainWindow::on_substitutionBtn_clicked()
{
    ui->carsar_window->setVisible(false);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(true);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(false);
}


void MainWindow::on_transpositionBtn_clicked()
{
    ui->carsar_window->setVisible(false);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(true);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(false);
}


void MainWindow::on_xorBtn_clicked()
{
    ui->carsar_window->setVisible(false);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(true);
    ui->rot_window->setVisible(false);
}


void MainWindow::on_rot9Btn_clicked()
{
    ui->carsar_window->setVisible(false);
    ui->atbash_window->setVisible(false);
    ui->vigenere_window->setVisible(false);
    ui->substitution_window->setVisible(false);
    ui->transposition_window->setVisible(false);
    ui->xor_window->setVisible(false);
    ui->rot_window->setVisible(true);
}

//here i saving all keys.i use them to choose correct key in decrypting time
int caesar_key_saved;
string transposition_key_saved;
string vigenere_key_saved;
char xor_key_saved;

//when user click caesar cipher encrypt button this function calling
//here i created obj on caesar cipher
//then get input details from input boxes and convert them Qstring to std string and int
void MainWindow::on_encrypt_clicked()
{
    QString Qmessage = ui->input->text();
    std::string message = Qmessage.toStdString();
    int key = ui->key->text().toInt();
    if(isalpha(key)){
        QMessageBox::critical(this, "Invalid Key", "Please enter a key between 0 and 25.");
        return;
    }
    caesar_key_saved=key;
    //using this if statement i checking key is between 1 snd 25. its not between show alert box and function return
    if(key<0||key>25){
        QMessageBox::critical(this, "Invalid Key", "Please enter a key between 0 and 25.");
        return;
    }
    Caesar_Cipher Caesar_Cipher_msg;
    //set message to object by calling function
    Caesar_Cipher_msg.get_msg(message);
    //here set key to obj
    Caesar_Cipher_msg.get_key(key);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=Caesar_Cipher_msg.encrypt_msg();
    QString outm = QString::fromStdString(en_m);
    ui->output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cand double encrypt
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->decrypt->setEnabled(true);
    ui->encrypt->setText("Encrypted");
    ui->encrypt->setEnabled(false);
    ui->key->setText("");
    ui->input->setText("");
    //show message to user to how decrypt
    ui->key_description->setVisible(true);
    is_encrypt=true;
}

//this wii work after user click the decrypt butten in caesar cipher
void MainWindow::on_decrypt_clicked()
{
    //here get encrypted message from display label
    //check user input key correct or incorrect
    //after create new object and decrypt message
    QString Qmessage = ui->output->text();
    std::string message = Qmessage.toStdString();
    int key = ui->key->text().toInt();
    if(key !=caesar_key_saved){
        QMessageBox::critical(this, "Invalid Key", "Decryption failed. Key may be incorrect!");
        return;
    }
    Caesar_Cipher Caesar_Cipher_msg;
    Caesar_Cipher_msg.get_msg(message);
    Caesar_Cipher_msg.get_key(key);
    string de_m=Caesar_Cipher_msg.decrypt_msg();
    QString outm = QString::fromStdString(de_m);
    ui->output->setText(outm);

    //after decrypt change encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->encrypt->setText("Encrypt");
    ui->encrypt->setEnabled(true);
    ui->key->setText("");
    ui->input->setText("");
    ui->key_description->setVisible(false);
    is_encrypt=false;
}

//this will work with atbach encript
void MainWindow::on_atbash_encrypt_clicked()
{
    QString Qmessage = ui->atbash_input->text();//get message
    std::string message = Qmessage.toStdString();//Qstring ->string

    atbash_Cipher atbash_Cipher_msg;//obj
    //set message to object by calling function
    atbash_Cipher_msg.get_msg(message);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=atbash_Cipher_msg.encrypt_msg();
    QString outm = QString::fromStdString(en_m);
    ui->atbash_output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cant encrypt again
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->atbash_decrypt->setEnabled(true);
    ui->atbash_encrypt->setText("Encrypted");
    ui->atbash_encrypt->setEnabled(false);
    ui->atbash_input->setText("");
    is_encrypt=true;//set message state to encrypted
}

//this will work with atbash decrypt button
void MainWindow::on_atbash_decrypt_clicked()
{
    //here get encrypted message from display label
    //after create new object and decrypt message
    QString Qmessage = ui->atbash_output->text();//get message
    std::string message = Qmessage.toStdString();//Qstring -> string
    atbash_Cipher atbash_Cipher_msg;//obj
    atbash_Cipher_msg.get_msg(message);
    string de_m=atbash_Cipher_msg.decrypt_msg();
    QString outm = QString::fromStdString(de_m);
    ui->atbash_output->setText(outm);

    //after decrypt change encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->atbash_encrypt->setText("Encrypt");
    ui->atbash_encrypt->setEnabled(true);
    is_encrypt=false;//set message status as encrypted
}

//call with viganere encrypt button
void MainWindow::on_vigenere_encrypt_clicked()
{
    QString Qmessage = ui->vigenere_input->text();//get message
    std::string message = Qmessage.toStdString();//Qstring to string
    string key=ui->vigenere_key->text().toStdString();
    vigenere_key_saved=key;//save key

    //loop for check the key
    for(int i=0;i<key.length();i++){
        if(!isalpha(key[i])){
            ui->vigenere_key->setText("");
            QMessageBox::critical(this, "Invalid Key", "Please enter alphabetic key");
            return;
        }
    }
    vigenere_cipher vigenere_cipher_msg;
    //set message snd key to object by calling function
    vigenere_cipher_msg.get_msg(message);
    vigenere_cipher_msg.get_key(key);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=vigenere_cipher_msg.encrypt();
    QString outm = QString::fromStdString(en_m);
    ui->vigenere_output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cand double encrypt
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->vigenere_decrypt->setEnabled(true);
    ui->vigenere_encrypt->setText("Encrypted");
    ui->vigenere_encrypt->setEnabled(false);
    ui->vigenere_input->setText("");
    ui->vigenere_key->setText("");
    is_encrypt=true;//set message status
}

//call with vigenere decrypt button
void MainWindow::on_vigenere_decrypt_clicked()
{
    string key=ui->vigenere_key->text().toStdString();//get msg
    if(key!=vigenere_key_saved){
        QMessageBox::critical(this, "Invalid Key", "Please enter correct key");
        return;
    }
    //loop for check the key
    for(int i=0;i<key.length();i++){
        if(!isalpha(key[i])){
            ui->vigenere_key->setText("");
            QMessageBox::critical(this, "Invalid Key", "Please enter alphabetic key");
            return;
        }
    }

    //here get encrypted message from display label
    //after create new object and decrypt message
    QString Qmessage = ui->vigenere_output->text();
    std::string message = Qmessage.toStdString();
    vigenere_cipher vigenere_cipher_msg;
    vigenere_cipher_msg.get_key(key);
    vigenere_cipher_msg.get_msg(message);
    string de_m=vigenere_cipher_msg.decrypt();
    QString outm = QString::fromStdString(de_m);
    ui->vigenere_output->setText(outm);

    //after decrypt change encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->vigenere_encrypt->setText("Encrypt");
    ui->vigenere_encrypt->setEnabled(true);
    ui->vigenere_key->setText("");
    ui->vigenere_input->setText("");
    ui->vigenere_decrypt->setEnabled(false);
    is_encrypt=false;//set message status
}

//call with substitution encrypt
void MainWindow::on_substitution_encrypt_clicked()
{
    QString Qmessage = ui->substitution_input->text();//get msg
    std::string message = Qmessage.toStdString();

    substitution_cipher substitution_cipher_msg;
    //set message to object by calling function
    substitution_cipher_msg.get_msg(message);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=substitution_cipher_msg.encrypt();
    QString outm = QString::fromStdString(en_m);
    ui->substitution_output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cand double encrypt
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->substitution_decrypt->setEnabled(true);
    ui->substitution_encrypt->setText("Encrypted");
    ui->substitution_encrypt->setEnabled(false);
    ui->substitution_input->setText("");
    is_encrypt=true;//set status
}

//call with substitution decrypt button
void MainWindow::on_substitution_decrypt_clicked()
{
    //here get encrypted message from display label
    //after create new object and decrypt message
    QString Qmessage = ui->substitution_output->text();
    std::string message = Qmessage.toStdString();
    substitution_cipher substitution_cipher_msg;
    substitution_cipher_msg.get_msg(message);
    string de_m=substitution_cipher_msg.decrypt();
    QString outm = QString::fromStdString(de_m);
    ui->substitution_output->setText(outm);

    //after decrypt change encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->substitution_encrypt->setText("Encrypt");
    ui->substitution_encrypt->setEnabled(true);
    is_encrypt=false;//set msg status
}

//call with transposition encrypt button
void MainWindow::on_transposition_encrypt_clicked()
{
    QString Qmessage = ui->transposition_input->text();//get msg
    std::string message = Qmessage.toStdString();
    string key = ui->transposition_key->text().toStdString();//get key
    transposition_key_saved=key;//save key

    //loop for check the key
    for(int i=0;i<key.length();i++){
        if(!isalpha(key[i])){
            QMessageBox::critical(this, "Invalid Key", "Please enter alphabetic key");
            return;
        }
    }
    transposition_cipher transposition_cipher_msg;
    //set message to object by calling function
    //here set key to obj
    transposition_cipher_msg.get_msg(message);
    transposition_cipher_msg.get_key(key);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=transposition_cipher_msg.encrypt();
    QString outm = QString::fromStdString(en_m);
    ui->transposition_output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cand double encrypt
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->transposition_decrypt->setEnabled(true);
    ui->transposition_encrypt->setText("Encrypted");
    ui->transposition_encrypt->setEnabled(false);
    ui->transposition_key->setText("");
    ui->transposition_input->setText("");
    is_encrypt=true;//set msg status
}

//call with transposition decrypt button
void MainWindow::on_transposition_decrypt_clicked()
{
    //here get encrypted message from display label
    //check user input key correct or incorrect
    //after create new object and decrypt message
    QString Qmessage = ui->transposition_output->text();
    string message=Qmessage.toStdString();
    string key = ui->transposition_key->text().toStdString();
    if(transposition_key_saved!=key){//check key
        QMessageBox::critical(this, "Incorrect Key", "Please enter correct key");
        return;
    }

    //loop for check the key
    for(int i=0;i<key.length();i++){
        if(!isalpha(key[i])){
            QMessageBox::critical(this, "Invalid Key", "Please enter alphabetic key");
            return;
        }
    }
    transposition_cipher transposition_cipher_msg;
    transposition_cipher_msg.get_msg(message);
    transposition_cipher_msg.get_key(key);
    string de_m=transposition_cipher_msg.decrypt(message,key);
    QString outm = QString::fromStdString(de_m);
    ui->transposition_output->setText(outm);

    //after decrypt change encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->transposition_encrypt->setText("Encrypt");
    ui->transposition_encrypt->setEnabled(true);
    ui->transposition_key->setText("");
    ui->transposition_input->setText("");
    is_encrypt=false;//set msg status
}

//call with xor encrypt
void MainWindow::on_xor_encrypt_clicked()
{
    char key;//get character key
    QString Qmessage = ui->xor_input->text();//get msg
    std::string message = Qmessage.toStdString();
    QString qkey=ui->xor_key->text();
    //check the key
    if(qkey.length()>1){
        QMessageBox::critical(this, "Invalid Key", "Please enter single character key");
        ui->xor_key->setText("");
        return;
    }
    else{
        key =qkey.toLatin1().at(0);//change it as std char
        if(!isalpha(key)){
            QMessageBox::critical(this, "Invalid Key", "Please enter character key");
            ui->xor_key->setText("");
            return;
        }
    }
    xor_key_saved=key;//save the key

    xor_cipher xor_cipher_msg;
    //set message to object by calling function
    //here set key to obj
    xor_cipher_msg.get_msg(message);
    xor_cipher_msg.get_key(key);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=xor_cipher_msg.encrypt();
    QString outm = QString::fromStdString(en_m);
    ui->xor_output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cand double encrypt
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->xor_decrypt->setEnabled(true);
    ui->xor_encrypt->setText("Encrypted");
    ui->xor_encrypt->setEnabled(false);
    ui->xor_key->setText("");
    ui->xor_input->setText("");
    is_encrypt=true;//set msg status
}

//call with xor decrypt
void MainWindow::on_xor_decrypt_clicked()
{
    char key;
    QString Qmessage = ui->xor_output->text();//get msg
    std::string message = Qmessage.toStdString();
    QString qkey=ui->xor_key->text();
    if(qkey.length()>1){
        QMessageBox::critical(this, "Invalid Key", "Please enter single character key");
        ui->xor_key->setText("");
        return;
    }
    else{
        key =qkey.toLatin1().at(0);//Qstring to std char
        if(!isalpha(key)){
            QMessageBox::critical(this, "Invalid Key", "Please enter character key");
            ui->xor_key->setText("");
            return;
        }
    }
    //check the key
    if(xor_key_saved!=key){
        QMessageBox::critical(this, "Incorrect Key", "Please enter correct key");
        ui->xor_key->setText("");
        return;
    }

    xor_cipher xor_cipher_msg;
    //set message to object by calling function
    //here set key to obj
    xor_cipher_msg.get_msg(message);
    xor_cipher_msg.get_key(key);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=xor_cipher_msg.decrypt();
    QString outm = QString::fromStdString(en_m);
    ui->xor_output->setText(outm);

    //after decrypt change the encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->xor_encrypt->setText("Encrypt");
    ui->xor_encrypt->setEnabled(true);
    ui->xor_key->setText("");
    ui->xor_input->setText("");
    is_encrypt=false;//set msg status
}

//call with rot9 encrypt
void MainWindow::on_rot_encrypt_clicked()
{
    QString Qmessage = ui->rot_input->text();//get msg
    std::string message = Qmessage.toStdString();

    rot9 rot_msg;
    //set message to object by calling function
    rot_msg.get_msg(message);
    //call encrypt msg and it return encrypted message
    //after convert that string to Qstring. then show it on label
    string en_m=rot_msg.encrypt();
    QString outm = QString::fromStdString(en_m);
    ui->rot_output->setText(outm);

    //after encrypt change encrypt button to encrypted and desable that button.then user cand double encrypt
    //and now decrypt button enable then user can decrypt message
    //and clear the input fields
    ui->rot_decrypt->setEnabled(true);
    ui->rot_encrypt->setText("Encrypted");
    ui->rot_encrypt->setEnabled(false);
    ui->rot_input->setText("");
    is_encrypt=true;
}

//call with rot9 decrypt
void MainWindow::on_rot_decrypt_clicked()
{
    //here get encrypted message from display label
    //after create new object and decrypt message
    QString Qmessage = ui->rot_output->text();
    std::string message = Qmessage.toStdString();
    rot9 rot_msg;
    rot_msg.get_msg(message);
    string de_m=rot_msg.decrypt();
    QString outm = QString::fromStdString(de_m);
    ui->rot_output->setText(outm);

    //after decrypt change encrypted button to encrypt and user can again use it for new message
    //and clear the input fields
    ui->rot_encrypt->setText("Encrypt");
    ui->rot_encrypt->setEnabled(true);
    ui->rot_decrypt->setEnabled(false);
    is_encrypt=false;
}


//************************************************************************************************************
//************************************************************************************************************
//file save code

//call with rot9 save
void MainWindow::on_rot_save_clicked()
{
    string window="rot_window";//window name. use with restore phase
    string message;
    //check message and key empty or not
    if(ui->rot_input->text()=="" && ui->rot_output->text()==""){
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){//if it encrypt message get message from output box
        message = ui->rot_output->text().toStdString();
    }
    else{
        if(ui->rot_input->text()==""){
            message = ui->rot_output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
        }
        else{
            message = ui->rot_input->text().toStdString();//if it not encrypted get message from input box
        }
    }

    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<<window<< endl;
        file<<message<< endl;
        file<<"no need key"<< endl;
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");//user message
    //error msg
    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//call with caesar save button
void MainWindow::on_caesar_save_clicked()
{
    string window="caesar_window";//window name
    string message;
    int key;

    if(ui->input->text()=="" && ui->output->text()==""){//theck message empty or not
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){
        message = ui->output->text().toStdString();//is incrypt get msg from output
        key=caesar_key_saved;//write saved key
    }
    else{
        if(ui->input->text()==""){
            message = ui->output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
            key=caesar_key_saved;//write saved key
        }
        else{
            message = ui->input->text().toStdString();//if it not encrypted get message from input box
            key=ui->key->text().toInt();//write input key
        }
    }
    //check key valid
    if(key<0||key>25){
        QMessageBox::critical(this, "Invalid Key", "Please enter a key between 0 and 25.");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<< window << endl;
        file<< message << endl;
        file<<key << endl;
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");

    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//call with atbash key save button
void MainWindow::on_atbash_save_clicked()
{
    string window="atbash_window";//window name. use with restore phase
    string message;

    if(ui->atbash_input->text()=="" && ui->atbash_output->text()==""){
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){
        message = ui->atbash_output->text().toStdString();//if it encrypt message get message from output box
    }
    else{
        if(ui->atbash_input->text()==""){
            message = ui->atbash_output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
        }
        else{
            message = ui->atbash_input->text().toStdString();//if it not encrypted get message from input box
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<< window << endl;
        file<< message << endl;
        file<<"no need key"<< endl;//not use key in this method
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");

    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//call with vigenere save button
void MainWindow::on_vigenere_save_clicked()
{
    string window="vigenere_window";//window name. use with restore phase
    string message;
    string key;

    if(ui->vigenere_input->text()=="" && ui->vigenere_output->text()==""){
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){
        message = ui->vigenere_output->text().toStdString();//if it encrypt message get message from output box
        key=vigenere_key_saved;//write saved key
    }
    else{
        if(ui->vigenere_input->text()==""){
            message = ui->vigenere_output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
            key=vigenere_key_saved;//write saved key
        }
        else{
            message = ui->vigenere_input->text().toStdString();//if it not encrypted get message from input box
            key=ui->vigenere_key->text().toStdString();//write input key
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<< window << endl;
        file<< message << endl;
        file<< key << endl;
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");

    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//call with substitution save button
void MainWindow::on_substitution_save_clicked()
{
    string window="substitution_window";//window name. use with restore phase
    string message;

    if(ui->substitution_input->text()=="" && ui->substitution_output->text()==""){
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){
        message = ui->substitution_output->text().toStdString();//if it encrypt message get message from output box
    }
    else{
        if(ui->substitution_input->text()==""){
            message = ui->substitution_output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
        }
        else{
            message = ui->substitution_input->text().toStdString();//if it not encrypted get message from input box
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<< window << endl;
        file<< message << endl;
        file<<"no need key"<< endl;//not use key in this method
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");

    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//call with xor save button
void MainWindow::on_xor_save_clicked()
{
    string window="xor_window";//window name. use with restore phase
    string message;
    char key;
    if(ui->xor_key->text().length()>1){
        QMessageBox::critical(this, "Invalid Key", "Please enter single character key");
        ui->xor_key->setText("");
        return;
    }
    if(ui->xor_input->text()=="" && ui->xor_output->text()==""){
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){
        message = ui->xor_output->text().toStdString();//if it encrypt message get message from output box
        key=xor_key_saved;//write saved key
    }
    else{
        if(ui->xor_input->text()==""){
            message = ui->xor_output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
            key=xor_key_saved;//write saved key
        }
        else{
            message = ui->xor_input->text().toStdString();//if it not encrypted get message from input box
            key=ui->xor_key->text().toLatin1().at(0);//write input key
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<< window << endl;
        file<< message << endl;
        file<< key << endl;
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");

    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//call with transposition save button
void MainWindow::on_transposition_save_clicked()
{
    string window="transposition_window";//window name. use with restore phase
    string message;
    string key;

    if(ui->transposition_input->text()=="" && ui->transposition_output->text()==""){
        QMessageBox::critical(this, "Invalid", "Please enter message befor save file");
        return;
    }
    if(is_encrypt){
        message = ui->transposition_output->text().toStdString();//if it encrypt message get message from output box
        key=transposition_key_saved;//write saved key
    }
    else{
        if(ui->transposition_input->text()==""){
            message = ui->transposition_output->text().toStdString();//if it encrypt->then decrypt->then save get msg from output box
            key=transposition_key_saved;//write saved key
        }
        else{
            message = ui->transposition_input->text().toStdString();//if it not encrypted get message from input box
            key=ui->transposition_key->text().toStdString();//write input key
        }
    }
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path to string
    ofstream file(string_path);//open file
    //write file includes
    if (file.is_open()) {
        file<< window << endl;
        file<< message << endl;
        file<< key << endl;
        file<<is_encrypt<<endl;
        file.close();
        QMessageBox::information(this, "Success", "File saved successfully!");

    } else {
        QMessageBox::critical(this, "error", "unknown error");
        return;
    }
}

//***************************************************
//              file restore part
//***************************************************
void MainWindow::on_open_file_clicked()//call with restore the file
{
    string window,key,message,encryption;//variables for store file content
    QString filePath = QFileDialog::getOpenFileName(this,"Open File",QDir::homePath(),"Text Files (*.txt)");//file path getting
    string string_path=filePath.toStdString();//convert path as std string
    ifstream file(string_path);//open file
    getline(file, window);
    getline(file, message);
    getline(file, key);
    getline(file, encryption);

    file.close();//close file

    //if else for load the correct window
    //here i use previos button onclick function for open the correct window
    if(window=="caesar_window"){
        on_caesarBtn_clicked();
        caesar_restor(message,key,encryption);
    }
    else if(window=="atbash_window"){
        on_atbashBtn_clicked();
        atbash_restor(message,key,encryption);
    }
    else if(window=="vigenere_window"){
        on_vigenereBtn_clicked();
        vigenere_restor(message,key,encryption);
    }
    else if(window=="substitution_window"){
        on_substitutionBtn_clicked();
        substitution_restor(message,key,encryption);
    }
    else if(window=="xor_window"){
        on_xorBtn_clicked();
        xor_restor(message,key,encryption);
    }
    else if(window=="transposition_window"){
        on_transpositionBtn_clicked();
        transposition_restor(message,key,encryption);
    }
    else if(window=="rot_window"){
        on_rot9Btn_clicked();
        rot_restor(message,key,encryption);
    }
    else{
        QMessageBox::critical(this, "error", "Invalid file format. Cannot encrypt or decrypt.");
    }
    return;
}

//if it caesar file this function will call
void MainWindow::caesar_restor(string msg,string k,string st){
    QString message,key;
    message=QString::fromStdString(msg);
    key=QString::fromStdString(k);
    if(st=="1"){//if it encrypted set values like this
        ui->output->setText(message);
        caesar_key_saved=key.toInt();
        ui->encrypt->setEnabled(false);
        ui->decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->input->setText(message);
        ui->key->setText(key);
        ui->encrypt->setEnabled(true);
        ui->decrypt->setEnabled(false);
        return;
    }
}

//if it atbash file this function will call
void MainWindow::atbash_restor(string msg,string k,string st){
    QString message;
    message=QString::fromStdString(msg);
    if(st=="1"){//if it encrypted set values like this
        ui->atbash_output->setText(message);
        ui->atbash_encrypt->setEnabled(false);
        ui->atbash_decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->atbash_input->setText(message);
        ui->atbash_encrypt->setEnabled(true);
        ui->atbash_decrypt->setEnabled(false);
        return;
    }
}

//if it vigenere file this function will call
void MainWindow::vigenere_restor(string msg,string k,string st){
    QString message,key;
    message=QString::fromStdString(msg);
    key=QString::fromStdString(k);
    if(st=="1"){//if it encrypted set values like this
        ui->vigenere_output->setText(message);
        vigenere_key_saved=k;
        ui->vigenere_encrypt->setEnabled(false);
        ui->vigenere_decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->vigenere_input->setText(message);
        ui->vigenere_key->setText(key);
        ui->vigenere_encrypt->setEnabled(true);
        ui->vigenere_decrypt->setEnabled(false);
        return;
    }
}

//if it substitution file this function will call
void MainWindow::substitution_restor(string msg,string k,string st){
    QString message;
    message=QString::fromStdString(msg);
    if(st=="1"){//if it encrypted set values like this
        ui->substitution_output->setText(message);
        ui->substitution_encrypt->setEnabled(false);
        ui->substitution_decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->substitution_input->setText(message);
        ui->substitution_encrypt->setEnabled(true);
        ui->substitution_decrypt->setEnabled(false);
        return;
    }
}

//if it transposition file this function will call
void MainWindow::transposition_restor(string msg,string k,string st){
    QString message,key;
    message=QString::fromStdString(msg);
    key=QString::fromStdString(k);
    if(st=="1"){//if it encrypted set values like this
        ui->transposition_output->setText(message);
        transposition_key_saved=k;
        ui->transposition_encrypt->setEnabled(false);
        ui->transposition_decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->transposition_input->setText(message);
        ui->transposition_key->setText(key);
        ui->transposition_encrypt->setEnabled(true);
        ui->transposition_decrypt->setEnabled(false);
        return;
    }
}

//if it xor file this function will call
void MainWindow::xor_restor(string msg,string k,string st){
    QString message,key;
    message=QString::fromStdString(msg);
    key=QString::fromStdString(k);
    if(st=="1"){//if it encrypted set values like this
        ui->xor_output->setText(message);
        xor_key_saved=k[0];
        ui->xor_encrypt->setEnabled(false);
        ui->xor_decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->xor_input->setText(message);
        ui->xor_key->setText(key);
        ui->xor_encrypt->setEnabled(true);
        ui->xor_decrypt->setEnabled(false);
        return;
    }
}

//if it rot9 file this function will call
void MainWindow::rot_restor(string msg,string k,string st){
    QString message,key;
    message=QString::fromStdString(msg);
    key=QString::fromStdString(k);
    if(st=="1"){//if it encrypted set values like this
        ui->rot_output->setText(message);
        ui->rot_encrypt->setEnabled(false);
        ui->rot_decrypt->setEnabled(true);
        return;
    }
    else{//if it not encrypt set values like this
        ui->rot_input->setText(message);
        ui->rot_encrypt->setEnabled(true);
        ui->rot_decrypt->setEnabled(false);
        return;
    }
}
