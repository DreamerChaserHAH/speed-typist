#include <storage.hpp>
#include <string>
#include <memory>

std::unique_ptr<StorageManagementModule> storageManagementModule = StorageManagementModuleFactory::createModule(SQLITE_STORAGE);

void process_data(StorageManagementModule& module){
    std::string key = "example key";
    std::string value = "example value";

    module.saveData(key, value);
}

int main(){

    process_data(*storageManagementModule);
    return 0;
}