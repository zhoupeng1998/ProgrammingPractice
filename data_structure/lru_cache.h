#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <list>
#include <unordered_map>

namespace ZP {

class LRUCache {
    int size;
    const int capacity;
    std::list<std::pair<int, int>> cache;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> lru;
public:
    LRUCache(int capacity);
    
    int get(int key);
    void put(int key, int value);
};

}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

#endif