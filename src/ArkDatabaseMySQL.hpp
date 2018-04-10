//
// Created by Fangzhou Wang on 3/23/18.
//

#ifndef ARKLIBRARY_ARKDATABASEMYSQL_HPP
#define ARKLIBRARY_ARKDATABASEMYSQL_HPP

#include "ArkDatabaseInterface.hpp"
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <list>
#include <string>

class ArkDatabaseMySQL : public ArkDatabaseInterface {
    sql::Driver *driver_;
    sql::Connection *conn_;
    sql::ResultSet *res_;

    std::list<std::string> batch_query_q_;
    std::list<std::vector<std::string>> batch_query_param_q_;

public:
    ArkDatabaseMySQL();
    virtual ~ArkDatabaseMySQL();
    virtual bool Connect(const DatabaseConfig &database_config);
    virtual bool Connect(const std::string &database_config_file);
    virtual void Disconnect();

    virtual bool RunQuery(const std::string &query);
    virtual bool RunQuery(const std::string &query,
                          const std::vector<std::string> &str_params,
                          const std::vector<int> &int_params);
    virtual bool RunBatchQuery(const std::string &query);
    virtual bool RunBatchQuery(const std::string &query,
                               const std::vector<std::string> &str_params,
                               const std::vector<int> &int_params);

    virtual bool GetQueryResult(std::vector<std::unordered_map<std::string, std::string>> &ret);
};

#endif //ARKLIBRARY_ARKDATABASEMYSQL_HPP
