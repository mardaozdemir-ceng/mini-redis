#include "kvstore.hpp"

void KVStore::set(const std::string& key, const std::string& value) {
    store_[key] = value;
}

std::optional<std::string> KVStore::get(const std::string& key) const {
    auto it = store_.find(key);
    if (it != store_.end()) {
        return it->second;
    }
    return std::nullopt; // Anahtar bulunamadı
}

bool KVStore::del(const std::string& key) {
    auto it = store_.find(key);
    if (it != store_.end()) {
        store_.erase(it);
        return true;
    }
    return false;
}