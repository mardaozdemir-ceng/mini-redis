#pragma once

#include <string>
#include <unordered_map>
#include <optional>

class KVStore {
public:
    KVStore() = default;

    // Bir anahtar-değer çifti kaydeder
    void set(const std::string& key, const std::string& value);

    // Anahtara karşılık gelen değeri döner. Yoksa std::nullopt döner.
    std::optional<std::string> get(const std::string& key) const;

    // Anahtarı siler. Silindiyse true, anahtar yoksa false döner.
    bool del(const std::string& key);

private:
    std::unordered_map<std::string, std::string> store_;
};