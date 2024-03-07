#include <fmt/core.h>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton button ("Hello world !");
    button.show();
    return a.exec();
}

/*
int main(){
    return 0;
}*/