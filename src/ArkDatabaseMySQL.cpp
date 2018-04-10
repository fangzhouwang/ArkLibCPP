//
// Created by Fangzhou Wang on 3/23/18.
//

#include "ArkDatabaseMySQL.hpp"

#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <unordered_map>
#include <fstream>

ArkDatabaseMySQL::ArkDatabaseMySQL() {
    driver_ = nullptr;
    conn_ = nullptr;
    res_ = nullptr;
}

ArkDatabaseMySQL::~ArkDatabaseMySQL() {
}

bool ArkDatabaseMySQL::Connect(const std::string &database_config_file) {
    std::ifstream db_fonfig(database_config_file);
    DatabaseConfig databaseConfig;
    db_fonfig >> databaseConfig.host;
    db_fonfig >> databaseConfig.user;
    db_fonfig >> databaseConfig.password;
    db_fonfig >> databaseConfig.schema;
    db_fonfig >> databaseConfig.port;
    return Connect(databaseConfig);
}

bool ArkDatabaseMySQL::Connect(const DatabaseConfig &database_config) {
    bool is_successful = true;
    try {
        sql::ConnectOptionsMap connection_properties;

        connection_properties["hostName"] = sql::Variant(database_config.host);
        connection_properties["userName"] = sql::Variant(database_config.user);
        connection_properties["password"] = sql::Variant(database_config.password);
        connection_properties["schema"] = sql::Variant(database_config.schema);
        connection_properties["port"] = sql::Variant(database_config.port);
        connection_properties["OPT_RECONNECT"] = true;

        driver_ = get_driver_instance();
        conn_ = driver_->connect(connection_properties);

    } catch (sql::SQLException &e) {
        is_successful = false;
        conn_ = nullptr;
    }
    return is_successful;
}

void ArkDatabaseMySQL::Disconnect() {
    if (conn_ != nullptr) {
        conn_->close();
        delete conn_;
    }
}

bool ArkDatabaseMySQL::RunQuery(const std::string &query) {
    return RunQuery(query, {}, {});
}

bool ArkDatabaseMySQL::RunQuery(const std::string &query,
                                const std::vector<std::string> &str_params,
                                const std::vector<int> &int_params) {
    bool is_successful = true;

    try {
        sql::SQLString temp(query);
        sql::PreparedStatement *prep_stmt = conn_->prepareStatement(temp);
        unsigned int param_cnt = 0;
        for (auto &param : str_params) {
            prep_stmt->setString(++param_cnt, param);
        }
        for (auto &param : int_params) {
            prep_stmt->setInt(++param_cnt, param);
        }

        res_ = prep_stmt->executeQuery();

        delete prep_stmt;

    } catch (sql::SQLException &e) {
        is_successful = false;
        if (res_)
            delete res_;
        res_ = nullptr;
    }

    return is_successful;
}

bool ArkDatabaseMySQL::RunBatchQuery(const std::string &query) {
    return true;
}

bool ArkDatabaseMySQL::RunBatchQuery(const std::string &query,
                                     const std::vector<std::string> &str_params,
                                     const std::vector<int> &int_params) {
    return true;
}

bool ArkDatabaseMySQL::GetQueryResult(std::vector<std::unordered_map<std::string, std::string>> &ret) {
    if (res_ == nullptr) return false;

    sql::ResultSetMetaData *res_meta = res_->getMetaData();

    unsigned int col_cnt = res_meta->getColumnCount();
    while (res_->next()) {
        std::unordered_map<std::string, std::string> temp_row;
        for (unsigned int i = 1; i <= col_cnt; ++i) {
            temp_row[res_meta->getColumnLabel(i)] = res_->getString(i);
        }
        ret.push_back(temp_row);
    }

    return true;
};
