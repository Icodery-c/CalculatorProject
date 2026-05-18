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

    if (!jobj[field].is_number_integer()) {
        throw std::runtime_error("Field '" + field + "' is not an integer");
    }

    auto value = jobj[field].get<long long>();

    if (value > INT_MAX || value < INT_MIN) {
        throw std::runtime_error("Field '" + field + "' overflows int");
    }

    return static_cast<int>(value);
}

Data Parser::parse(const std::string& jsonStr) {

    if (jsonStr.empty()) {
        throw std::runtime_error("Empty request");
    }

    json jobj = json::parse(jsonStr);

    if (!jobj.contains(KEY_OP)) {
        throw std::runtime_error("Missing required field: op");
    }

    Data data;
    std::string opStr = jobj[KEY_OP].get<std::string>();

    if      (opStr == "+") data.op = Operation::Add;
    else if (opStr == "-") data.op = Operation::Subtract;
    else if (opStr == "*") data.op = Operation::Multiply;
    else if (opStr == "/") data.op = Operation::Divide;
    else if (opStr == "^") data.op = Operation::Power;
    else if (opStr == "!") data.op = Operation::Factorial;
    else throw std::invalid_argument("Unknown operator: " + opStr);

    if (!jobj.contains(KEY_NUM1)) {
        throw std::runtime_error("Missing required field: num1");
    }

    data.num1 = parseJsonInt(jobj, KEY_NUM1);

    if (data.op != Operation::Factorial) {
        if (!jobj.contains(KEY_NUM2)) {
            throw std::runtime_error("num2 is required");
        }
        data.num2 = parseJsonInt(jobj, KEY_NUM2);
    }

    return data;
}