#include "parser.h"

#include <stdexcept>
#include <string>
#include <climits>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static inline int parseJsonInt (const json& j, const std::string& field) {

    if (!j[field].is_number_integer()) { throw std::runtime_error("Field '" + field + "' is not an integer"); }

    auto value = j[field].get<long long>();
    
    if (value > INT_MAX || value < INT_MIN) { throw std::runtime_error("Field '" + field + "' overflows int"); }

    return static_cast<int>(value);

}

Data Parser::parse(int argc, char **argv) {

    if (argc < 2) { throw std::runtime_error("There is no input data in JSON format."); }

    json jobj = json::parse(argv[1]);

    if (!jobj.contains("op")) { throw std::runtime_error("Missing required field: op"); }

    Data data;

    data.op = jobj["op"].get<std::string>()[0];

    if (data.op == 'h') { return data; }

    if (!jobj.contains("num1")) { throw std::runtime_error("Missing required field: num1"); }

    data.num1 = parseJsonInt(jobj, "num1");

    if (data.op != '!') {

        if (!jobj.contains("num2")) { throw std::runtime_error("num2 is required for arithmetic operations."); }

        data.num2 = parseJsonInt(jobj, "num2");

    }

    return data;
}