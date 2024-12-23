//
// Created by amarnath on 12/22/24.
//

#include <qt6/QtWidgets/QApplication>
#include <qt6/QtWidgets/QPushButton>

int main(int argc, char *argv[]) {
        QApplication app(argc, argv);

        QPushButton button("Hello World");
        button.resize(200, 100);
        button.show();

        return app.exec();
}
