#include <storage.hpp>
#include <sqlite3.h>

class Sqlite3Storage : public StorageManagementModule {
    public:

        Sqlite3Storage(){}
        void saveData(std::string key, std::string data) override {
            sqlite3* db;
            sqlite3_open("database.db", &db);
            sqlite3_stmt* stmt;
            const char* sql = "INSERT INTO data (key, value) VALUES (?, ?)";
            sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, key.c_str(), -1, NULL);
            sqlite3_bind_text(stmt, 2, data.c_str(), -1, NULL);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }

        void loadData(std::string key) override {
            
        }
};

std::unique_ptr<StorageManagementModule> StorageManagementModuleFactory::createModule(StorageManagementModuleType type){
    return std::unique_ptr<Sqlite3Storage>(new Sqlite3Storage());
};