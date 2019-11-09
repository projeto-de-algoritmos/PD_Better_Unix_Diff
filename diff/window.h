#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <iostream>
#include <fstream>

using namespace std;

class window : public QWidget {

public:
    explicit window(QWidget *parent = nullptr);

private:
    QCheckBox *gap_mismatch;
    QCheckBox *diff_lines;
    QCheckBox *equal_lines;
    QCheckBox *equal_files;
    QCheckBox *align_text;
    QLabel *label_file1;
    QLabel *label_file2;
    QString file_name1;
    QString file_name2;
    ifstream file1;
    ifstream file2;

private slots:
    void selecionar_arquivo_1();
    void selecionar_arquivo_2();
    void processar();
    void nova_tela(const int& opcao);
};

#endif // WINDOW_H
