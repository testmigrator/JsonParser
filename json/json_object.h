#pragma once
#include <string>
#include <map>
#include <vector>
#include <variant>

namespace json
{
    class JsonObject
    {
    public:
        using Map = std::map<std::wstring, JsonObject>;
        using Array = std::vector<JsonObject>;

    public:
        static JsonObject FromString(const std::wstring& json);

    public:
        JsonObject() = default;
        explicit JsonObject(const std::wstring& value);
        explicit JsonObject(double value);
        explicit JsonObject(bool value);
        explicit JsonObject(const Map&& jsonMap);
        explicit JsonObject(const Array&& jsonArray);

        std::wstring GetAsString() const;
        double GetAsDobule() const;
        int64_t GetAsInt64() const;
        bool GetAsBool() const;

        JsonObject& operator[](const std::wstring& key);
        JsonObject& operator[](int index);

        JsonObject& operator=(const std::wstring& value);
        JsonObject& operator=(double value);

        template <class T, class Y = std::enable_if_t<std::is_same<T, bool>{}>>
        JsonObject& operator=(T value)
        {
            m_container = value;
            return *this;
        }

        bool IsObject() const;
        bool IsArray() const;
        bool IsString() const;
        bool IsNumber() const;
        bool IsBool() const;
        bool IsEmpty() const;

    private:
        std::variant<std::monostate, Map, Array, std::wstring, double, bool> m_container;
    };
}
