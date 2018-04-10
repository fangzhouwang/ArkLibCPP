//
// Created by Fangzhou Wang on 3/22/18.
//

#ifndef ARKLIBRARY_ARKDATABASEINTERFACE_HPP
#define ARKLIBRARY_ARKDATABASEINTERFACE_HPP

#include <string>
#include <vector>
#include <unordered_map>

#define DB_BATCH_SIZE 100

typedef struct TagDatabaseConfig {
    std::string host;
    std::string user;
    std::string password;
    std::string schema;
    int port;
} DatabaseConfig;

class ArkDatabaseInterface {
public:
    virtual ~ArkDatabaseInterface() = default;
    virtual bool Connect(const DatabaseConfig &database_config) = 0;
    virtual bool Connect(const std::string &database_config_file) = 0;
    virtual void Disconnect() = 0;
    virtual bool RunQuery(const std::string &query) = 0;
    virtual bool RunQuery(const std::string &query,
                          const std::vector<std::string> &str_params,
                          const std::vector<int> &int_params) = 0;
    virtual bool RunBatchQuery(const std::string &query) = 0;
    virtual bool RunBatchQuery(const std::string &query,
                               const std::vector<std::string> &str_params,
                               const std::vector<int> &int_params) = 0;
    virtual bool GetQueryResult(std::vector<std::unordered_map<std::string, std::string>> &ret) = 0;
protected:
    ArkDatabaseInterface() = default;
};

#endif //ARKLIBRARY_ARKDATABASEINTERFACE_HPP
