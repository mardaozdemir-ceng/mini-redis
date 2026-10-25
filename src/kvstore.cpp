#include "kvstore.hpp"


bool KVStore::is_expired(const ValueEntry& entry) const{
    if (!entry.expires_at.has_value()){
        return false;
    }
    return std::chrono::steady_clock::now() >= entry.expires_at.value();
}

void KVStore::set(const std::string& key, const std::string& value) {
    store_[key] = ValueEntry{value, std::nullopt};
}

void KVStore::set(const std::string& key, const std::string& value, int seconds) {
    auto expire_time = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    store_[key] = ValueEntry{value, expire_time};
}

std::optional<std::string> KVStore::get(const std::string& key) {
    auto it = store_.find(key);
    if (it == store_.end()) {
        return std::nullopt;
    }
    if (is_expired(it->second)) {
        store_.erase(it);
        return std::nullopt;
    }
    return it->second.value; // Anahtar bulunamadı
}

bool KVStore::del(const std::string& key) {
    auto it = store_.find(key);
    if (it == store_.end()) {
        return false;
    }
    if (is_expired(it->second)) {
        store_.erase(it);
        return false;
    }

    store_.erase(it);
    return true;
}

bool KVStore::expire(const std::string& key, int seconds) {
    auto it = store_.find(key);
    if (it == store_.end() || is_expired(it->second)) {
        if (it != store_.end()) {
            store_.erase(it);
        }
        return false;
    }

    it->second.expires_at = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    return true;
}

std::optional<int> KVStore::ttl(const std::string& key) {
    auto it = store_.find(key);
    if (it == store_.end()){
        return std::nullopt;
    }

    if (is_expired(it->second)){
        store_.erase(it);
        return std::nullopt;
    }

    if (!it->second.expires_at.has_value()){
        return -1;  
    }

    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(it->second.expires_at.value() - now).count();
    return static_cast<int>(remaining);
}