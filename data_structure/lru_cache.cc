#include "lru_cache.h"

namespace ZP {

LRUCache::LRUCache(int capacity)
    :size(0), capacity(capacity) {
}

int LRUCache::get(int key) {
    if (lru.find(key) == lru.end()) {
        return -1;
    }
    int value = lru[key]->second;
    cache.erase(lru[key]);
    cache.push_front(std::make_pair(key, value));
    lru[key] = cache.begin();
    return value;
}

void LRUCache::put(int key, int value) {
    if (lru.find(key) != lru.end()) {
        auto it = lru.find(key);
        cache.erase(lru[key]);
        lru.erase(key);
        cache.push_front(std::make_pair(key, value));
        lru[key] = cache.begin();
    } else if (size < capacity) {
        cache.push_front(std::make_pair(key, value));
        lru[key] = cache.begin();
        size++;
    } else {
        auto back = cache.back();
        lru.erase(back.first);
        cache.pop_back();
        cache.push_front(std::make_pair(key, value));
        lru[key] = cache.begin();
    }
}

}