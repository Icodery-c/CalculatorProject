#include "database.h"

#include <libpq-fe.h>
#include <stdexcept>
#include <string>
#include <memory>

namespace database {

struct PGconnDeleter {
    void operator()(PGconn* conn) const noexcept {
        if (conn != nullptr) {
            PQfinish(conn);
        }
    }
};

struct PGresultDeleter {
    void operator()(PGresult* res) const noexcept {
        if (res != nullptr) {
            PQclear(res);
        }
    }
};

using ConnectionPtr = std::unique_ptr<PGconn, PGconnDeleter>;
using ResultPtr     = std::unique_ptr<PGresult, PGresultDeleter>;

struct Database::Impl {
    ConnectionPtr conn;
};

Database::Database(const std::string& connectionString) : impl(std::make_unique<Impl>()) {

    impl->conn.reset(PQconnectdb(connectionString.c_str()));

    if (PQstatus(impl->conn.get()) != CONNECTION_OK) {
        std::string error = PQerrorMessage(impl->conn.get());
        throw std::runtime_error("Failed to connect to database: " + error);
    }
}

Database::~Database() = default;

void Database::saveOperation(const OperationRecord& record) {

    std::string num1Str   = std::to_string(record.num1);
    std::string num2Str   = std::to_string(record.num2);
    std::string resultStr = std::to_string(record.result);
    std::string statusStr = std::to_string(record.status);

    ResultPtr res;

    if (record.hasNum2) {
        const char* query = "INSERT INTO operations (num1, num2, operation, result, status) VALUES ($1, $2, $3, $4, $5)";
        const char* paramValues[5] = {
            num1Str.c_str(),
            num2Str.c_str(),
            record.operation.c_str(),
            resultStr.c_str(),
            statusStr.c_str()
        };

        res.reset(PQexecParams(impl->conn.get(), query, 5, nullptr, paramValues, nullptr, nullptr, 0));
    } else {
        const char* query = "INSERT INTO operations (num1, operation, result, status) VALUES ($1, $2, $3, $4)";
        const char* paramValues[4] = {
            num1Str.c_str(),
            record.operation.c_str(),
            resultStr.c_str(),
            statusStr.c_str()
        };

        res.reset(PQexecParams(impl->conn.get(), query, 4, nullptr, paramValues, nullptr, nullptr, 0));
    }

    if (PQresultStatus(res.get()) != PGRES_COMMAND_OK) {
        std::string error = PQerrorMessage(impl->conn.get());
        throw std::runtime_error("Insert failed: " + error);
    }
}

std::vector<OperationRecord> Database::loadAllOperations() {

    std::vector<OperationRecord> records;

    ResultPtr res(PQexec(impl->conn.get(), "SELECT num1, num2, operation, result, status FROM operations"));

    if (PQresultStatus(res.get()) != PGRES_TUPLES_OK) {
        std::string error = PQerrorMessage(impl->conn.get());
        throw std::runtime_error("Select failed: " + error);
    }

    int rows = PQntuples(res.get());

    for (int i = 0; i < rows; i++) {
        OperationRecord record;
        record.num1      = std::stoi(PQgetvalue(res.get(), i, 0));
        record.hasNum2   = !PQgetisnull(res.get(), i, 1);
        record.num2      = record.hasNum2 ? std::stoi(PQgetvalue(res.get(), i, 1)) : 0;
        record.operation = PQgetvalue(res.get(), i, 2);
        record.result    = std::stoi(PQgetvalue(res.get(), i, 3));
        record.status    = std::stoi(PQgetvalue(res.get(), i, 4));
        records.push_back(record);
    }

    return records;
}

} 