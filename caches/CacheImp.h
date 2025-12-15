#pragma once
#include "ICache.h"

#include <unordered_map>
#include <list>
#include <stdexcept>

template<typename Key, typename Value>
class LRUCache : public ICache<Key, Value> {
public:
    explicit LRUCache(std::size_t capacity)
        : capacity_(capacity) {}

    void set(const Key& key, const Value& value) override {
        if (capacity_ == 0) return;

        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second.first = value;
            touch(it);
            return;
        }

        if (map_.size() >= capacity_) {
            const Key& lru_key = usage_.back();
            map_.erase(lru_key);
            usage_.pop_back();
        }

        usage_.push_front(key);
        map_[key] = {value, usage_.begin()};
    }

    Value get(const Key& key) override {
        auto it = map_.find(key);
        if (it == map_.end()) {
            throw std::out_of_range("Key not found");
        }

        touch(it);
        return it->second.first;
    }

    bool contains(const Key& key) const override {
        return map_.find(key) != map_.end();
    }

    void clear() override {
        map_.clear();
        usage_.clear();
    }

    std::size_t size() const override {
        return map_.size();
    }

private:
    using ListIt = typename std::list<Key>::iterator;

    void touch(typename std::unordered_map<Key, std::pair<Value, ListIt>>::iterator it) {
        usage_.erase(it->second.second);
        usage_.push_front(it->first);
        it->second.second = usage_.begin();
    }

    std::size_t capacity_;
    std::list<Key> usage_;
    std::unordered_map<Key, std::pair<Value, ListIt>> map_;
};