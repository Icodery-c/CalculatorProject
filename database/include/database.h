#pragma once

#include <string>
#include <vector>
#include <memory>


namespace database {
     
    struct OperationRecord {

        int num1; int num2;
        std::string operation;
        int result;
        int status;
        bool hasNum2;


    };

    class Database {

        struct Impl;
        std::unique_ptr<Impl> impl;


        public:

            Database(const std::string& connectionString);
            ~Database();

            Database(const Database&)            = delete;
            Database& operator=(const Database&) = delete;

            Database(Database&&)            = default;
            Database& operator=(Database&&) = default;

            void saveOperation(const OperationRecord& record);
            std::vector<OperationRecord> loadAllOperations();


    };


}
