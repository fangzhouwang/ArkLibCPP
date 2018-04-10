//
// Created by Fangzhou Wang on 3/23/18.
//

#include "ArkDBMySQL_test.hpp"

#define TEST_DB_HOST  "localhost"
#define TEST_DB_USER  "tester"
#define TEST_DB_PASSWORD  "tester"
#define TEST_DB_SCHEMA  "gtest"

TEST(ArkDatabaseMySQL, init) {
    DatabaseConfig db = {TEST_DB_HOST, TEST_DB_USER, TEST_DB_PASSWORD, TEST_DB_SCHEMA, 3306};
    auto *arkdb = new ArkDatabaseMySQL();
    EXPECT_TRUE(arkdb->Connect(db));
    arkdb->Disconnect();
}

TEST(ArkDatabaseMySQL, init_with_file) {
    auto *arkdb = new ArkDatabaseMySQL();
    EXPECT_TRUE(arkdb->Connect("/Users/Ark/.db_configs/db_config_local_tester.txt"));
    arkdb->Disconnect();
}

TEST(ArkDatabaseMySQL, init_fail) {
    DatabaseConfig db = {TEST_DB_HOST, "tes", TEST_DB_PASSWORD, TEST_DB_SCHEMA, 3306};
    auto *arkdb = new ArkDatabaseMySQL();
    EXPECT_FALSE(arkdb->Connect(db));
    arkdb->Disconnect();
}

TEST(ArkDatabaseMySQL, create_table) {
    DatabaseConfig db = {TEST_DB_HOST, TEST_DB_USER, TEST_DB_PASSWORD, TEST_DB_SCHEMA, 3306};
    auto *arkdb = new ArkDatabaseMySQL();
    EXPECT_TRUE(arkdb->Connect(db));
    EXPECT_TRUE(arkdb->RunQuery("DROP TABLE IF EXISTS gtest_lib"));
    EXPECT_TRUE(arkdb->RunQuery("CREATE TABLE gtest_lib (str_col VARCHAR(20), int_col INT)"));
    arkdb->Disconnect();
}

TEST(ArkDatabaseMySQL, insert_value) {
    DatabaseConfig db = {TEST_DB_HOST, TEST_DB_USER, TEST_DB_PASSWORD, TEST_DB_SCHEMA, 3306};
    auto *arkdb = new ArkDatabaseMySQL();
    EXPECT_TRUE(arkdb->Connect(db));
    EXPECT_TRUE(arkdb->RunQuery("DROP TABLE IF EXISTS gtest_lib"));

    std::vector<std::string> str_params;
    std::vector<int> int_params;
    EXPECT_TRUE(arkdb->RunQuery("CREATE TABLE gtest_lib (str_col VARCHAR(20), int_col INT)", str_params, int_params));

    str_params.push_back("20");
    int_params.push_back(20);
    std::string query = "INSERT INTO gtest_lib (str_col, int_col) VALUES (?, ?)";
    EXPECT_TRUE(arkdb->RunQuery(query, str_params, int_params));

    arkdb->Disconnect();
}

TEST(ArkDatabaseMySQL, create_table_param) {
    DatabaseConfig db = {TEST_DB_HOST, TEST_DB_USER, TEST_DB_PASSWORD, TEST_DB_SCHEMA, 3306};
    auto *arkdb = new ArkDatabaseMySQL();
    EXPECT_TRUE(arkdb->Connect(db));
    EXPECT_TRUE(arkdb->RunQuery("DROP TABLE IF EXISTS gtest_lib"));

    std::vector<std::string> str_params;
    std::vector<int> int_params;
    EXPECT_TRUE(arkdb->RunQuery("CREATE TABLE gtest_lib (str_col VARCHAR(20), int_col INT)", str_params, int_params));

    std::string query = " select COLUMN_NAME, CHARACTER_MAXIMUM_LENGTH AS MAX_LEN ";
    query += " from information_schema.columns ";
    query += " where table_schema = DATABASE() AND ";
    query += "      table_name = 'gtest_lib' AND ";
    query += "      COLUMN_NAME = 'str_col' ";

    EXPECT_TRUE(arkdb->RunQuery(query));
    std::vector<std::unordered_map<std::string, std::string>> ret;
    EXPECT_TRUE(arkdb->GetQueryResult(ret));

    EXPECT_EQ(ret.size(), 1);
    EXPECT_EQ(ret[0]["MAX_LEN"], "20");

    arkdb->Disconnect();
}

