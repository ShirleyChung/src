#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <sstream>

/**
 * @brief JSON �Ȫ���H����
 */
class JsonValue {
public:
    virtual ~JsonValue() {}
    virtual std::string toString(int indent = 0) const = 0;
    virtual JsonValue* clone() const = 0; // �Ω�ƻs
};

/**
 * @brief JSON �r���
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
 * @brief JSON ���� (key-value map)
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
        // �Y key �w�s�b�A���R���쥻��
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

    // �ѪR�r��ö�R����]²�檩�A���w�榡���T�^
    void parse(const std::string& json);

private:
    std::map<std::string, JsonValue*> data;

    // �H�U�X�ӻ��U�禡�Ω�ѪR�r��G
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
                result += s[pos]; // ²����q�B�z
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
 * @brief JSON �}�C���O
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