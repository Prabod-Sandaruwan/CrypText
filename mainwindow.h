#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "caesarCipher.h"
#include "atbashCipher.h"
#include"vigenereCipher.h"
#include"substitutionCipher.h"
#include"transpositionCipher.h"
#include"xorCipher.h"
#include"rot9Cipher.h"
#include<string>
#include <fstream>
#include<QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_caesarBtn_clicked();

    void on_vigenereBtn_clicked();

    void on_atbashBtn_clicked();

    void on_substitutionBtn_clicked();

    void on_transpositionBtn_clicked();

    void on_xorBtn_clicked();

    void on_rot9Btn_clicked();

    void on_encrypt_clicked();

    void on_decrypt_clicked();

    void on_atbash_encrypt_clicked();

    void on_atbash_decrypt_clicked();

    void on_vigenere_encrypt_clicked();

    void on_vigenere_decrypt_clicked();

    void on_substitution_encrypt_clicked();

    void on_substitution_decrypt_clicked();

    void on_transposition_encrypt_clicked();

    void on_transposition_decrypt_clicked();

    void on_xor_encrypt_clicked();

    void on_xor_decrypt_clicked();

    void on_rot_encrypt_clicked();

    void on_rot_decrypt_clicked();

    void on_rot_save_clicked();

    void on_caesar_save_clicked();

    void on_atbash_save_clicked();

    void on_vigenere_save_clicked();

    void on_substitution_save_clicked();

    void on_xor_save_clicked();

    void on_transposition_save_clicked();

    void on_open_file_clicked();

    void caesar_restor(std::string msg, std::string k, std::string st);
    void atbash_restor(std::string msg, std::string k, std::string st);
    void vigenere_restor(std::string msg, std::string k, std::string st);
    void substitution_restor(std::string msg, std::string k, std::string st);
    void transposition_restor(std::string msg, std::string k, std::string st);
    void xor_restor(std::string msg, std::string k, std::string st);
    void rot_restor(std::string msg, std::string k, std::string st);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
