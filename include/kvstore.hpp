#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <chrono>

struct ValueEntry {
    std::string value;
    std::optional<std::chrono::steady_clock::time_point> expires_at;
};
class KVStore {
public:
    KVStore() = default;

    
    void set(const std::string& key, const std::string& value);
    void set(const std::string& key, const std::string& value, int seconds);

    std::optional<std::string> get(const std::string& key);
    bool del(const std::string& key);

    bool expire(const std::string& key, int seconds);
    std::optional<int> ttl(const std::string& key);

private:
    std::unordered_map<std::string, ValueEntry> store_;
    bool is_expired(const ValueEntry& entry) const;
};