#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

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
    QString file_name3;
    ifstream file1;
    ifstream file2;
    ofstream file3;
    QLineEdit *line_peso_gap;
    QLineEdit *line_peso_mismatch;
    QLabel *alert;
    QWidget* janela;

private slots:
    void selecionar_arquivo_1();
    void selecionar_arquivo_2();
    void processar();
    void nova_tela(const int& opcao);
    void novo_arquivo();
    void escolher_local_arquivo();
    vector<pair<int, int>> calcular_mismatchs_gaps();
    vector<pair<string, string>> ver_linhas_diferentes();
    vector<string> ver_porcentagem_linhas();
    double ver_porcentagem_arquivos();
};

#endif // WINDOW_H
