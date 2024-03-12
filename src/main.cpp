#include <storage.hpp>
#include <memory>
#include <iostream>
#include <gui.hpp>

std::unique_ptr<StorageManagementModule> storageManagementModule;
std::unique_ptr<GuiModule> guiManagementModule;
std::unique_ptr<GuiLogicStruct> guiLogicModule = std::make_unique<GuiLogicStruct>();

std::string test(){
    return "";
}

int main(int argc, char *argv[])
{
    storageManagementModule = StorageManagementModuleFactory::createModule(LMDB_STORAGE);

    guiLogicModule->load_highscore = [](){
        return storageManagementModule->loadData("key");
    };

    guiManagementModule = GuiModuleFactory::createModule(QT5, argc, argv, *guiLogicModule);

    storageManagementModule->saveData("key", "0");
    std::cout << storageManagementModule->loadData("key") << std::endl;
    return guiManagementModule->start_gui();
}
