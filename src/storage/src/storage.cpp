#include <storage.hpp>
#include <sqlite3.h>
#include <lmdb.h>
#include <filesystem>

class Sqlite3Storage : public StorageManagementModule
{

    sqlite3 *db;

public:
    Sqlite3Storage()
    {
        sqlite3_open("database.db", &db);
        const char *sql = "CREATE TABLE IF NOT EXISTS data (key TEXT PRIMARY KEY, value TEXT)";
        sqlite3_exec(db, sql, NULL, NULL, NULL);
    }

    ~Sqlite3Storage()
    {
        sqlite3_close(db);
    }

    void saveData(std::string key, std::string data) override
    {
        sqlite3_stmt *stmt;
        const char *sql = "INSERT OR REPLACE INTO data (key, value) VALUES (?, ?)";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, key.c_str(), -1, NULL);
        sqlite3_bind_text(stmt, 2, data.c_str(), -1, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    std::string loadData(std::string key) override
    {
        sqlite3_stmt *stmt;
        const char *sql = "SELECT value FROM data WHERE key = ?";
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        sqlite3_bind_text(stmt, 1, key.c_str(), -1, NULL);
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::string result = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            sqlite3_finalize(stmt);
            return result;
        }
        return "";
    }
};

class LmdbStorage : public StorageManagementModule
{

    MDB_env *env;

public:
    LmdbStorage()
    {
        if(!std::filesystem::is_directory("lmdb_database")){
            std::filesystem::create_directory("lmdb_database");
        }
        mdb_env_create(&env);
        mdb_env_open(env, "./lmdb_database", 0, 0664);
    }

    ~LmdbStorage()
    {
        mdb_env_close(env);
    }
    void saveData(std::string key, std::string data) override
    {
        MDB_txn *txn; // Transaction handle
        mdb_txn_begin(env, NULL, 0, &txn);

        MDB_dbi dbi;
        mdb_open(txn, NULL, 0, &dbi);

        MDB_val key_val, data_val;
        key_val.mv_size = key.size();
        key_val.mv_data = (void *)key.c_str();
        data_val.mv_size = data.size();
        data_val.mv_data = (void *)data.c_str();
        mdb_put(txn, dbi, &key_val, &data_val, 0);
        mdb_txn_commit(txn);
        mdb_close(env, dbi);
    }

    std::string loadData(std::string key) override
    {
        MDB_txn *txn; // Transaction handle
        mdb_txn_begin(env, NULL, MDB_RDONLY, &txn);

        MDB_dbi dbi;
        mdb_open(txn, NULL, 0, &dbi);

        MDB_cursor *cursor;
        mdb_cursor_open(txn, dbi, &cursor);

        MDB_val key_val, data_val;
        key_val.mv_size = key.size();
        key_val.mv_data = (void *)key.c_str();
        auto rc = mdb_get(txn, dbi, &key_val, &data_val);
        std::string return_string;
        return_string = rc == 0? std::string(reinterpret_cast<char *>(data_val.mv_data), data_val.mv_size): "";
        mdb_cursor_close(cursor);
        mdb_txn_commit(txn);
        mdb_close(env, dbi);
        return return_string;
    }
};

std::unique_ptr<StorageManagementModule> StorageManagementModuleFactory::createModule(StorageManagementModuleType type)
{
    switch (type)
    {
    case SQLITE_STORAGE:
        return std::unique_ptr<Sqlite3Storage>(new Sqlite3Storage());
    case LMDB_STORAGE:
        return std::unique_ptr<LmdbStorage>(new LmdbStorage());
    default:
        return std::unique_ptr<Sqlite3Storage>(new Sqlite3Storage());
    }
};