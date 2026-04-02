#include "parser.h"

#include <stdexcept>
#include <string>
#include <climits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static const std::string KEY_OP   = "op";
static const std::string KEY_NUM1 = "num1";
static const std::string KEY_NUM2 = "num2";

static inline int parseJsonInt(const json& jobj, const std::string& field) {

    if (!jobj[field].is_number_integer()) { throw std::runtime_error("Field '" + field + "' is not an integer"); }

    auto value = jobj[field].get<long long>();

    if (value > INT_MAX || value < INT_MIN) { throw std::runtime_error("Field '" + field + "' overflows int"); }

    return static_cast<int>(value);
}

static Operation parseOperation(const std::string& opStr) {
    if (opStr == "+") return Operation::Add;
    if (opStr == "-") return Operation::Subtract;
    if (opStr == "*") return Operation::Multiply;
    if (opStr == "/") return Operation::Divide;
    if (opStr == "^") return Operation::Power;
    if (opStr == "!") return Operation::Factorial;
    if (opStr == "h") return Operation::Help;
    throw std::runtime_error("Unknown operator: " + opStr);
}

Data Parser::parse(int argc, char** argv) {

    if (argc < 2) { throw std::runtime_error("There is no input data in JSON format."); }

    json jobj = json::parse(argv[1]);

    if (!jobj.contains(KEY_OP)) { throw std::runtime_error("Missing required field: op"); }

    Data data;

    data.op = parseOperation(jobj[KEY_OP].get<std::string>());

    if (data.op == Operation::Help) { return data; }

    if (!jobj.contains(KEY_NUM1)) { throw std::runtime_error("Missing required field: num1"); }

    data.num1 = parseJsonInt(jobj, KEY_NUM1);

    if (data.op != Operation::Factorial) {

        if (!jobj.contains(KEY_NUM2)) { throw std::runtime_error("num2 is required for arithmetic operations."); }

        data.num2 = parseJsonInt(jobj, KEY_NUM2);
    }

    return data;
}