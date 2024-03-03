#ifndef STORAGE_HPP_HEADER
#define STORAGE_HPP_HEADER

#include <string>
#include <memory>

enum StorageManagementModuleType{
    SQLITE_STORAGE,
    LMDB_STORAGE
};

class StorageManagementModule{
    public:
        StorageManagementModule(){};
        virtual void saveData(std::string key, std::string data) = 0;
        virtual void loadData(std::string key) = 0;
};

class StorageManagementModuleFactory{
    public:
        static std::unique_ptr<StorageManagementModule> createModule(StorageManagementModuleType type);
};

#endif