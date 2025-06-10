#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <sstream>

/**
 * @brief JSON 值的抽象基類
 */
class JsonValue {
public:
    virtual ~JsonValue() {}
    virtual std::string toString(int indent = 0) const = 0;
    virtual JsonValue* clone() const = 0; // 用於複製
};

/**
 * @brief JSON 字串值
 */
class JsonString : public JsonValue {
public:
    explicit JsonString(const std::string& val) : value(val) {}
    virtual ~JsonString() {}

    virtual std::string toString(int indent = 0) const {
        return "\"" + value + "\"";
    }
    virtual JsonValue* clone() const {
        return new JsonString(*this);
    }
    std::string value;
};

/**
 * @brief JSON 物件 (key-value map)
 */
class JsonObject : public JsonValue {
public:
    JsonObject() {}
    JsonObject(const JsonObject& other) {
        for (std::map<std::string, JsonValue*>::const_iterator it = other.data.begin(); it != other.data.end(); ++it) {
            data[it->first] = it->second->clone();
        }
    }
    virtual ~JsonObject() {
        clear();
    }

    void clear() {
        for (std::map<std::string, JsonValue*>::iterator it = data.begin(); it != data.end(); ++it) {
            delete it->second;
        }
        data.clear();
    }

    void add(const std::string& key, JsonValue* val) {
        // 若 key 已存在，先刪除原本的
        std::map<std::string, JsonValue*>::iterator it = data.find(key);
        if (it != data.end()) {
            delete it->second;
        }
        data[key] = val;
    }

    virtual std::string toString(int indent = 0) const {
        std::stringstream ss;
        std::string ind(indent, ' ');
        ss << "{\n";
        for (std::map<std::string, JsonValue*>::const_iterator it = data.begin(); it != data.end(); ++it) {
            ss << ind << "  \"" << it->first << "\": " << it->second->toString(indent + 2);
            std::map<std::string, JsonValue*>::const_iterator next = it; ++next;
            if (next != data.end()) ss << ",";
            ss << "\n";
        }
        ss << ind << "}";
        return ss.str();
    }

    virtual JsonValue* clone() const {
        return new JsonObject(*this);
    }

    // 解析字串並填充物件（簡單版，限定格式正確）
    void parse(const std::string& json);

private:
    std::map<std::string, JsonValue*> data;

    // 以下幾個輔助函式用於解析字串：
    static void skipWhitespace(const std::string& s, size_t& pos) {
        while (pos < s.size() && std::isspace(s[pos])) ++pos;
    }
    static std::string parseString(const std::string& s, size_t& pos) {
        if (s[pos] != '"') throw std::runtime_error("Expected string");
        ++pos;
        std::string result;
        while (pos < s.size()) {
            char c = s[pos];
            if (c == '"') {
                ++pos;
                return result;
            } else if (c == '\\') {
                ++pos;
                if (pos >= s.size()) throw std::runtime_error("Invalid escape");
                result += s[pos]; // 簡單轉義處理
            } else {
                result += c;
            }
            ++pos;
        }
        throw std::runtime_error("Unterminated string");
    }
    JsonValue* parseValue(const std::string& s, size_t& pos);
    size_t findMatching(const std::string& s, size_t pos, char openChar, char closeChar);
};

/**
 * @brief JSON 陣列類別
 */
class JsonArray : public JsonValue {
public:
    JsonArray() {}
    JsonArray(const JsonArray& other) {
        for (std::vector<JsonValue*>::const_iterator it = other.data.begin(); it != other.data.end(); ++it) {
            data.push_back((*it)->clone());
        }
    }
    virtual ~JsonArray() {
        clear();
    }

    void clear() {
        for (std::vector<JsonValue*>::iterator it = data.begin(); it != data.end(); ++it) {
            delete *it;
        }
        data.clear();
    }

    void add(JsonValue* val) {
        data.push_back(val);
    }

    virtual std::string toString(int indent = 0) const {
        std::stringstream ss;
        std::string ind(indent, ' ');
        ss << "[\n";
        for (size_t i = 0; i < data.size(); ++i) {
            ss << ind << "  " << data[i]->toString(indent + 2);
            if (i != data.size() - 1) ss << ",";
            ss << "\n";
        }
        ss << ind << "]";
        return ss.str();
    }

    virtual JsonValue* clone() const {
        return new JsonArray(*this);
    }

private:
    std::vector<JsonValue*> data;
};