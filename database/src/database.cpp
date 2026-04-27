#include "database.h"

#include <libpq-fe.h>
#include <stdexcept>
#include <string>

namespace database {

struct Database::Impl {
    PGconn* conn = nullptr;

    ~Impl() {
        if (conn != nullptr) {
            PQfinish(conn);
        }
    }
};

Database::Database(const std::string& connectionString) : impl(std::make_unique<Impl>()) {

    impl->conn = PQconnectdb(connectionString.c_str());

    if (PQstatus(impl->conn) != CONNECTION_OK) {
        std::string error = PQerrorMessage(impl->conn);
        throw std::runtime_error("Failed to connect to database: " + error);
    }
}

Database::~Database() = default;

void Database::saveOperation(const OperationRecord& record) {

    const char* query;
    const char* paramValues[5];
    std::string num1Str = std::to_string(record.num1);
    std::string num2Str = std::to_string(record.num2);
    std::string resultStr = std::to_string(record.result);
    std::string statusStr = std::to_string(record.status);

    if (record.hasNum2) {
        query = "INSERT INTO operations (num1, num2, operation, result, status) VALUES ($1, $2, $3, $4, $5)";
        paramValues[0] = num1Str.c_str();
        paramValues[1] = num2Str.c_str();
        paramValues[2] = record.operation.c_str();
        paramValues[3] = resultStr.c_str();
        paramValues[4] = statusStr.c_str();

        PGresult* res = PQexecParams(impl->conn, query, 5, nullptr, paramValues, nullptr, nullptr, 0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::string error = PQerrorMessage(impl->conn);
            PQclear(res);
            throw std::runtime_error("Insert failed: " + error);
        }

        PQclear(res);
    } else {
        query = "INSERT INTO operations (num1, operation, result, status) VALUES ($1, $2, $3, $4)";
        paramValues[0] = num1Str.c_str();
        paramValues[1] = record.operation.c_str();
        paramValues[2] = resultStr.c_str();
        paramValues[3] = statusStr.c_str();

        PGresult* res = PQexecParams(impl->conn, query, 4, nullptr, paramValues, nullptr, nullptr, 0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::string error = PQerrorMessage(impl->conn);
            PQclear(res);
            throw std::runtime_error("Insert failed: " + error);
        }

        PQclear(res);
    }
}

std::vector<OperationRecord> Database::loadAllOperations() {

    std::vector<OperationRecord> records;

    PGresult* res = PQexec(impl->conn, "SELECT num1, num2, operation, result, status FROM operations");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::string error = PQerrorMessage(impl->conn);
        PQclear(res);
        throw std::runtime_error("Select failed: " + error);
    }

    int rows = PQntuples(res);

    for (int i = 0; i < rows; i++) {
        OperationRecord record;
        record.num1      = std::stoi(PQgetvalue(res, i, 0));
        record.hasNum2   = !PQgetisnull(res, i, 1);
        record.num2      = record.hasNum2 ? std::stoi(PQgetvalue(res, i, 1)) : 0;
        record.operation = PQgetvalue(res, i, 2);
        record.result    = std::stoi(PQgetvalue(res, i, 3));
        record.status    = std::stoi(PQgetvalue(res, i, 4));
        records.push_back(record);
    }

    PQclear(res);
    return records;
}

} 