#include "window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    window tela;
    tela.resize(800, 600);
    tela.setWindowTitle("Better Unix Diff");
    tela.show();
    return app.exec();
}
