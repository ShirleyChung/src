#include "jsonfile.h"

// JsonObject 內的 parseValue 實作
JsonValue* JsonObject::parseValue(const std::string& s, size_t& pos) {
    skipWhitespace(s, pos);
    if (pos >= s.size()) throw std::runtime_error("Unexpected end of input");

    if (s[pos] == '{') {
        size_t end = findMatching(s, pos, '{', '}');
        std::string objStr = s.substr(pos, end - pos + 1);
        JsonObject* obj = new JsonObject();
        obj->parse(objStr);
        pos = end + 1;
        return obj;
    } else if (s[pos] == '[') {
        size_t end = findMatching(s, pos, '[', ']');
        std::string arrStr = s.substr(pos + 1, end - pos - 1);
        JsonArray* arr = new JsonArray();

        size_t arrPos = 0;
        while (true) {
            skipWhitespace(arrStr, arrPos);
            if (arrPos >= arrStr.size()) break;
            JsonValue* val = parseValue(arrStr, arrPos);
            arr->add(val);
            skipWhitespace(arrStr, arrPos);
            if (arrPos < arrStr.size() && arrStr[arrPos] == ',') ++arrPos;
        }
        pos = end + 1;
        return arr;
    } else if (s[pos] == '"') {
        std::string str = parseString(s, pos);
        return new JsonString(str);
    } else {
        throw std::runtime_error("Unsupported JSON value (only string/object/array supported)");
    }
}

// JsonObject 內尋找匹配括號函式
size_t JsonObject::findMatching(const std::string& s, size_t pos, char openChar, char closeChar) {
    if (s[pos] != openChar) throw std::runtime_error("Expected opening bracket");
    int depth = 0;
    for (size_t i = pos; i < s.size(); ++i) {
        if (s[i] == openChar) ++depth;
        else if (s[i] == closeChar) --depth;
        if (depth == 0) return i;
    }
    throw std::runtime_error("No matching closing bracket");
}

// JsonObject 解析函式實作
void JsonObject::parse(const std::string& json) {
    size_t pos = 0;
    data.clear();

    skipWhitespace(json, pos);
    if (pos >= json.size() || json[pos] != '{') throw std::runtime_error("Expected '{'");
    ++pos;
    skipWhitespace(json, pos);

    if (pos < json.size() && json[pos] == '}') {
        ++pos;
        return; // 空物件
    }

    while (true) {
        skipWhitespace(json, pos);
        std::string key = parseString(json, pos);
        skipWhitespace(json, pos);
        if (pos >= json.size() || json[pos] != ':') throw std::runtime_error("Expected ':'");
        ++pos;
        skipWhitespace(json, pos);

        JsonValue* val = parseValue(json, pos);
        add(key, val);

        skipWhitespace(json, pos);
        if (pos >= json.size()) throw std::runtime_error("Unexpected end of input");
        if (json[pos] == ',') {
            ++pos;
            continue;
        } else if (json[pos] == '}') {
            ++pos;
            break;
        } else {
            throw std::runtime_error("Expected ',' or '}'");
        }
    }
}