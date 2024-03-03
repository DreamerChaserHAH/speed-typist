#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <storage.hpp>
#include <memory>
#include <iostream>

std::unique_ptr<StorageManagementModule> storageManagementModule = StorageManagementModuleFactory::createModule(LMDB_STORAGE);

int main(int argc, char *argv[])
{
    storageManagementModule->saveData("key", "test day working here");
    std::cout << storageManagementModule->loadData("key") << std::endl;

    QApplication a(argc, argv);
    QPushButton button ("Hello world !");
    button.show();
    return a.exec();
}
