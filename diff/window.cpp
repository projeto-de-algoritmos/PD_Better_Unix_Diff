#include "window.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>

window::window(QWidget *parent) : QWidget(parent) {
    int maximum_label_height = 30;
    QFont labelFont("Times", 20, QFont::Bold);
    QFont buttonFont("Times", 25);

    file_name1 = "";
    file_name2 = "";

    QVBoxLayout *tela = new QVBoxLayout(this);
    QGridLayout *arquivos = new QGridLayout();
    QGridLayout *opcoes = new QGridLayout();
    QGridLayout *botao = new QGridLayout();

    label_file1 = new QLabel("Arquivo 1", this);
    arquivos->addWidget(label_file1, 0, 0);
    label_file1->setAlignment(Qt::AlignCenter);
    label_file1->setMaximumHeight(maximum_label_height);
    label_file1->setFont(labelFont);

    QPushButton *selecionar_arquivo1 = new QPushButton("Selecionar Arquivo", this);
    selecionar_arquivo1->setFixedWidth(150);
    selecionar_arquivo1->setFixedHeight(30);
    connect(selecionar_arquivo1, &QPushButton::clicked, this, &window::selecionar_arquivo_1);
    arquivos->addWidget(selecionar_arquivo1, 1, 0);

    label_file2 = new QLabel("Arquivo 2", this);
    arquivos->addWidget(label_file2, 0, 1);
    label_file2->setAlignment(Qt::AlignCenter);
    label_file2->setMaximumHeight(maximum_label_height);
    label_file2->setFont(labelFont);

    QPushButton *selecionar_arquivo2 = new QPushButton("Selecionar Arquivo", this);
    selecionar_arquivo2->setFixedWidth(150);
    selecionar_arquivo2->setFixedHeight(30);
    connect(selecionar_arquivo2, &QPushButton::clicked, this, &window::selecionar_arquivo_2);
    arquivos->addWidget(selecionar_arquivo2, 1, 1);

    QLabel *label_opcoes = new QLabel("Opções", this);
    opcoes->addWidget(label_opcoes, 0, 1);
    label_opcoes->setAlignment(Qt::AlignCenter);
    label_opcoes->setMaximumHeight(maximum_label_height);
    label_opcoes->setFont(labelFont);

    gap_mismatch = new QCheckBox("Quantidade de Mismatchs e Gaps", this);
    opcoes->addWidget(gap_mismatch, 1, 0);

    diff_lines = new QCheckBox("Mostrar linhas diferentes", this);
    opcoes->addWidget(diff_lines, 1, 1);

    equal_lines = new QCheckBox("Porcentagem de igualdade por linha", this);
    opcoes->addWidget(equal_lines, 1, 2);

    equal_files = new QCheckBox("Porcentagem de igualdade entre os arquivos", this);
    opcoes->addWidget(equal_files, 2, 0);

    align_text = new QCheckBox("Alinhar texto em novo arquivo", this);
    opcoes->addWidget(align_text, 2, 1);

    QPushButton *button = new QPushButton("Processar", this);
    button->setFixedWidth(150);
    button->setFixedHeight(50);
    button->setFont(buttonFont);
    connect(button, &QPushButton::clicked, this, &window::processar);
    botao->addWidget(button, 1, 0);

    QGroupBox *group_files = new QGroupBox(this);
    QGroupBox *group_opcoes = new QGroupBox(this);

    group_files->setLayout(arquivos);
    group_opcoes->setLayout(opcoes);

    tela->addWidget(group_files);
    tela->addWidget(group_opcoes);
    tela->addItem(botao);
    setLayout(tela);
}

void window::selecionar_arquivo_1() {
    QString temp = QFileDialog::getOpenFileName(
                this,
                "Escolher Arquivo",
                QDir::currentPath(),
                "Todos os arquivos (*.*)");

    if(temp.size()) {
        file_name1 = temp;
        string s = file_name1.toStdString();
        size_t found = s.find_last_of("/\\");
        label_file1->setText(QString::fromStdString(s.substr(found+1)));
    }
}

void window::selecionar_arquivo_2() {
    QString temp = QFileDialog::getOpenFileName(
                this,
                "Escolher Arquivo",
                QDir::currentPath(),
                "Todos os arquivos (*.*)");

    if(temp.size()) {
        file_name2 = temp;
        string s = file_name2.toStdString();
        size_t found = s.find_last_of("/\\");
        label_file2->setText(QString::fromStdString(s.substr(found+1)));
    }
}

void window::processar() {
    bool gap_mismatch_option = gap_mismatch->isChecked();
    bool diff_lines_option = diff_lines->isChecked();
    bool equal_lines_option = equal_lines->isChecked();
    bool equal_files_option = equal_files->isChecked();
    bool align_text_option = align_text->isChecked();

    QWidget* new_window = new QWidget(nullptr);

    if(!file_name1.size()) {
        QMessageBox::information(new_window, tr("Aviso"), tr("Você não escolheu o Arquivo 1"));
        return;
    }

    if(!file_name2.size()) {
        QMessageBox::information(new_window, tr("Aviso"), tr("Você não escolheu o Arquivo 2"));
        return;
    }

    if(!gap_mismatch_option && !diff_lines_option && !equal_lines_option && !equal_files_option &&
       !align_text_option) {
        QMessageBox::information(new_window, tr("Aviso"), tr("É necessário marcar pelo menos uma opção"));
        return;
    }

    if(gap_mismatch_option) {
        this->nova_tela(1);
    }

    if(diff_lines_option) {
        this->nova_tela(2);
    }

    if(equal_lines_option) {
        this->nova_tela(3);
    }

    if(equal_files_option) {
        this->nova_tela(4);
    }
}

void window::nova_tela(const int& opcao) {
    QFont font("Times", 15, QFont::Bold);
    QWidget* new_window = new QWidget(nullptr);
    QVBoxLayout *tela = new QVBoxLayout();

    if(opcao == 1) {
        new_window->setWindowTitle("Quantidade de Mismatchs e Gaps");
    }
    else if(opcao == 2) {
        new_window->setWindowTitle("Mostrar linhas diferentes");
    }
    else if(opcao == 3) {
        new_window->setWindowTitle("Porcentagem de igualdade por linha");
    }
    else if(opcao == 4) {
        new_window->setWindowTitle("Porcentagem de igualdade entre os arquivos");
    }

    QListWidget *lista = new QListWidget();
    lista->setFont(font);

    lista->addItem(QString::number(opcao));

    tela->addWidget(lista);
    new_window->setLayout(tela);
    new_window->setFixedSize(650, 330);
    new_window->show();
}
