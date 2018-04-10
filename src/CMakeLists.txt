set(core_SRCS
        ArkCLP.cpp ArkDatabaseInterface.hpp ArkDatabaseMySQL.cpp ArkDatabaseMySQL.hpp)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

add_library(core ${core_SRCS} ArkDatabaseInterface.hpp ArkDatabaseMySQL.cpp ArkDatabaseMySQL.hpp)
target_link_libraries(core)
target_link_libraries(core mysqlcppconn)
target_link_libraries(core mysqlclient)
