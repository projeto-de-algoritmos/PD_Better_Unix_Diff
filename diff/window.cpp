#include "window.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>
#include <QFormLayout>

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

    if(align_text_option) {
        this->novo_arquivo();
    }
}

void window::nova_tela(const int& opcao) {
    QFont font("Times", 15, QFont::Bold);
    QWidget* new_window = new QWidget(nullptr);
    new_window->resize(1000, 800);
    QHBoxLayout *tela = new QHBoxLayout();

    QListWidget *lista = new QListWidget();
    lista->setFont(font);

    tela->addWidget(lista);

    if(opcao == 1) {
        new_window->setWindowTitle("Quantidade de Mismatchs e Gaps");
        vector<pair<int, int>> mismatch_gap = calcular_mismatchs_gaps();

        QListWidget *lista2 = new QListWidget();
        lista2->setFont(font);
        tela->addWidget(lista2);

        for(size_t i = 0; i < mismatch_gap.size(); ++i) {
            lista->addItem(QString::fromStdString(to_string(i+1)) + ": " + QString::fromStdString(to_string(mismatch_gap[i].first)) + " Mismatchs");
            lista2->addItem(QString::fromStdString(to_string(i+1)) + ": " + QString::fromStdString(to_string(mismatch_gap[i].second)) + " Gaps");
        }
    }
    else if(opcao == 2) {
        new_window->setWindowTitle("Mostrar linhas diferentes");
        vector<pair<string, string>> diferencas = ver_linhas_diferentes();

        QListWidget *lista2 = new QListWidget();
        lista2->setFont(font);
        tela->addWidget(lista2);

        for(const auto& d : diferencas) {
            lista->addItem(QString::fromStdString(d.first));
            lista2->addItem(QString::fromStdString(d.second));
        }
    }
    else if(opcao == 3) {
        new_window->setWindowTitle("Porcentagem de igualdade por linha");
        vector<string> porcentagem = ver_porcentagem_linhas();

        for(const auto& p : porcentagem)
            lista->addItem(QString::fromStdString(p));
    }
    else if(opcao == 4) {
        new_window->setWindowTitle("Porcentagem de igualdade entre os arquivos");
        double p = ver_porcentagem_arquivos();
        QFont novo("Times", 50, QFont::Bold);
        lista->setFont(novo);
        lista->addItem(QString::fromStdString(to_string(p) + "%"));
        new_window->setFixedSize(410, 120);
    }

    new_window->setLayout(tela);
    new_window->show();
}

void window::novo_arquivo() {
    janela = new QWidget(nullptr);
    janela->setFixedSize(600, 220);
    janela->setWindowTitle("Adicionar Tarefa");

    QFont buttonFont("Times", 20);
    const int button_size = 200;
    QFont labelFont("Times", 20, QFont::Bold);
    QFont campoFont("Times", 20);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QLabel *main_label = new QLabel("Insira as penalidades");
    main_label->setFont(labelFont);
    main_label->setAlignment(Qt::AlignCenter);
    QLabel *label_gap = new QLabel("Penalidade do Gap:");
    label_gap->setFont(labelFont);
    QLabel *label_mismatch = new QLabel("Penalidade do Mismatch:");
    label_mismatch->setFont(labelFont);

    line_peso_gap = new QLineEdit();
    line_peso_gap->setFont(campoFont);
    line_peso_gap->setValidator(new QIntValidator());

    line_peso_mismatch = new QLineEdit();
    line_peso_mismatch->setFont(campoFont);
    line_peso_mismatch->setValidator(new QIntValidator());

    QPushButton *salvar_arquivo = new QPushButton("Salvar");
    salvar_arquivo->setMinimumWidth(button_size);
    salvar_arquivo->setFont(buttonFont);
    connect(salvar_arquivo, &QPushButton::clicked, this, &window::escolher_local_arquivo);

    formLayout->addWidget(main_label);
    formLayout->addRow(label_gap, line_peso_gap);
    formLayout->addRow(label_mismatch, line_peso_mismatch);

    alert = new QLabel(" ");
    alert->setAlignment(Qt::AlignCenter);
    alert->setMaximumHeight(20);

    formLayout->addWidget(salvar_arquivo);
    formLayout->addWidget(alert);

    janela->setLayout(formLayout);
    janela->show();
}

void window::escolher_local_arquivo() {
    const int gap = line_peso_gap->text().toInt();
    if(gap < 0) {
        alert->setText("Peso do Gap deve ser 0 ou maior");
        return;
    }

    const int mismatch = line_peso_mismatch->text().toInt();
    if(mismatch < 0) {
        alert->setText("Peso do Mismatch deve ser 0 ou maior");
        return;
    }

    QString temp = QFileDialog::getSaveFileName(
                this,
                "Salvar Arquivo",
                QDir::currentPath(),
                "Todos os arquivos (*.*)");

    if(temp.size()) {
        file_name3 = temp;
        janela->close();
        file3.open(file_name3.toStdString());

        // Funcao de Sequence Alignment

        file3.close();
    }
}

vector<pair<int, int>> window::calcular_mismatchs_gaps() {
    file1.open(file_name1.toStdString());
    file2.open(file_name2.toStdString());

    vector<pair<int, int>> mismatch_gap;

    string s1, s2;
    bool read_f1 = true, read_f2 = true;

    while(1) {
        if(!getline(file1, s1))
            read_f1 = false;
        if(!getline(file2, s2))
            read_f2 = false;

        if(read_f1 && read_f2) {
            int tamanho = max(s1.size(), s2.size());
            int n = min(s1.size(), s2.size());
            int mismatch = 0;

            for(int x = 0; x < n; ++x) {
                if(s1[x]!=s2[x])
                    mismatch++;
            }

            int gap = tamanho - n;

            mismatch_gap.push_back(make_pair(mismatch, gap));
        }
        else if(read_f1 && !read_f2) {
            mismatch_gap.push_back(make_pair(0, s1.size()));
            while(getline(file1, s1)) {
                mismatch_gap.push_back(make_pair(0, s1.size()));
            }
            break;
        }
        else if(!read_f1 && read_f2) {
            mismatch_gap.push_back(make_pair(0, s2.size()));
            while(getline(file2, s2)) {
                mismatch_gap.push_back(make_pair(0, s2.size()));
            }
            break;
        }
        else {
            break;
        }
    }

    file1.close();
    file2.close();
    return mismatch_gap;
}

vector<pair<string, string>> window::ver_linhas_diferentes() {
    file1.open(file_name1.toStdString());
    file2.open(file_name2.toStdString());

    vector<pair<string, string>> diferencas;

    string s1, s2;
    bool read_f1 = true, read_f2 = true;

    int i = 1;

    while(1) {
        if(!getline(file1, s1))
            read_f1 = false;
        if(!getline(file2, s2))
            read_f2 = false;

        if(read_f1 && read_f2) {
            if(s1!=s2) {
                diferencas.push_back(make_pair(to_string(i) + ": " + s1, to_string(i) + ": " + s2));
            }
            i++;
        }
        else if(read_f1 && !read_f2) {
            diferencas.push_back(make_pair(to_string(i) + ": " + s1, ""));
            i++;
            while(getline(file1, s1)) {
                diferencas.push_back(make_pair(to_string(i) + ": " + s1, ""));
                i++;
            }
            break;
        }
        else if(!read_f1 && read_f2) {
            diferencas.push_back(make_pair("", to_string(i) + ": " + s2));
            i++;
            while(getline(file2, s2)) {
                diferencas.push_back(make_pair("", to_string(i) + ": " + s2));
                i++;
            }
            break;
        }
        else {
            break;
        }
    }

    file1.close();
    file2.close();
    return diferencas;
}

vector<string> window::ver_porcentagem_linhas() {
    file1.open(file_name1.toStdString());
    file2.open(file_name2.toStdString());

    vector<string> porcentagem;

    string s1, s2;
    bool read_f1 = true, read_f2 = true;

    int i = 1;

    while(1) {
        if(!getline(file1, s1))
            read_f1 = false;
        if(!getline(file2, s2))
            read_f2 = false;

        if(read_f1 && read_f2) {
            int tamanho = max(s1.size(), s2.size());
            int n = min(s1.size(), s2.size());
            int qtd = 0;

            for(int x = 0; x < n; ++x) {
                if(s1[x]==s2[x])
                    qtd++;
            }

            double igualdade = qtd/(double)tamanho;
            porcentagem.push_back(to_string(i) + ": " + to_string(igualdade*100) + "%");
            i++;
        }
        else if(read_f1 && !read_f2) {
            porcentagem.push_back(to_string(i) + ": 0,00%");
            i++;
            while(getline(file1, s1)) {
                porcentagem.push_back(to_string(i) + ": 0,00%");
                i++;
            }
            break;
        }
        else if(!read_f1 && read_f2) {
            porcentagem.push_back(to_string(i) + ": 0,00%");
            i++;
            while(getline(file2, s2)) {
                porcentagem.push_back(to_string(i) + ": 0,00%");
                i++;
            }
            break;
        }
        else {
            break;
        }
    }

    file1.close();
    file2.close();
    return porcentagem;
}

double window::ver_porcentagem_arquivos() {
    file1.open(file_name1.toStdString());
    file2.open(file_name2.toStdString());

    int total = 0, igualdade = 0;

    string s1, s2;
    bool read_f1 = true, read_f2 = true;

    while(1) {
        if(!getline(file1, s1))
            read_f1 = false;
        if(!getline(file2, s2))
            read_f2 = false;

        if(read_f1 && read_f2) {
            total += max(s1.size(), s2.size());
            int n = min(s1.size(), s2.size());

            for(int x = 0; x < n; ++x) {
                if(s1[x]==s2[x])
                    igualdade++;
            }
        }
        else if(read_f1 && !read_f2) {
            total += s1.size();
            while(getline(file1, s1)) {
                total += s1.size();
            }
            break;
        }
        else if(!read_f1 && read_f2) {
            total += s2.size();
            while(getline(file2, s2)) {
                total += s2.size();
            }
            break;
        }
        else {
            break;
        }
    }

    file1.close();
    file2.close();
    return (igualdade/(double)total)*100;
}
