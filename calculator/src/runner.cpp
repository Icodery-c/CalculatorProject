#include "runner.h"
#include "logger.h"
#include "config.h"

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <exception>
#include <string>

using json = nlohmann::json;

static const std::string CONFIG_PATH = "/etc/calculator/calculator.conf";

static const std::unordered_map<Operation, std::string> OPERATION_NAMES = {
    {Operation::Add,       "Add"},
    {Operation::Subtract,  "Subtract"},
    {Operation::Multiply,  "Multiply"},
    {Operation::Divide,    "Divide"},
    {Operation::Power,     "Power"},
    {Operation::Factorial, "Factorial"}
};

static std::string operationToName(Operation op) {
    auto it = OPERATION_NAMES.find(op);
    return it != OPERATION_NAMES.end() ? it->second : "Unknown";
}

Runner::Runner() {

    auto& log = logger::Logger::Initialize();

    // Загружаем конфиг
    Config config;
    
    try {
        
        config.load(CONFIG_PATH);
    
    } catch (const std::exception& e) {
    
        log.warn("Cannot load config from " + CONFIG_PATH + ", using defaults: " + e.what());
    
    }

    // Строим строку подключения к БД из конфига
    std::string connStr =
        "host="     + config.getString("database.host", "localhost") +
        " dbname="  + config.getString("database.dbname", "calculator_db") +
        " user="    + config.getString("database.user", "calculator") +
        " password=" + config.getString("database.password", "calculator");

    db = std::make_unique<database::Database>(connStr);

    log.debug("Warming up cache from database...");

    auto records = db->loadAllOperations();

    for (const auto& record : records) {
        Data data;
        data.num1 = record.num1;
        data.num2 = record.num2;

        if      (record.operation == "Add")       data.op = Operation::Add;
        else if (record.operation == "Subtract")  data.op = Operation::Subtract;
        else if (record.operation == "Multiply")  data.op = Operation::Multiply;
        else if (record.operation == "Divide")    data.op = Operation::Divide;
        else if (record.operation == "Power")     data.op = Operation::Power;
        else if (record.operation == "Factorial") data.op = Operation::Factorial;
        else continue;

        if (record.status == 0) {
            cache.put(Cache::makeKey(data), record.result);
        }
    }

    
    log.info("Cache warmed up with " + std::to_string(records.size()) + " records");

    unsigned short port = static_cast<unsigned short>(config.getInt("server.port", 5555));
    
    // Создаём сервер с handler-ом, который вызывает наш handleRequest
    srv = std::make_unique<server::Server>(
        port,
        [this](const std::string& req) { return handleRequest(req); }
    );

    
}

void Runner::run() {
    auto& log = logger::Logger::Initialize();
    log.info("Server starting...");
    srv->run();
}

void Runner::stop() {
    auto& log = logger::Logger::Initialize();
    log.info("Stopping server...");
    if (srv) {
        srv->stop();
    }
}

std::string Runner::handleRequest(const std::string& request) {

    auto& log = logger::Logger::Initialize();
    json response;

    try {
        log.debug("Parsing request: " + request);

        Data data = parser.parse(request);

        checker.check(data);

        std::string key = Cache::makeKey(data);

        if (cache.contains(key)) {
            log.info("Cache hit");
            response["result"] = cache.get(key);
            response["status"] = 0;
            return response.dump();
        }

        int result = calculator.calculate(data);
        cache.put(key, result);

        database::OperationRecord record;
        record.num1      = data.num1;
        record.num2      = data.num2;
        record.operation = operationToName(data.op);
        record.result    = result;
        record.status    = 0;
        record.hasNum2   = (data.op != Operation::Factorial);
        db->saveOperation(record);

        response["result"] = result;
        response["status"] = 0;

    } catch (const std::exception& e) {
        log.error(std::string("Error: ") + e.what());
        response["result"] = 0;
        response["status"] = 1;
        response["error"]  = e.what();
    }

    return response.dump();
}