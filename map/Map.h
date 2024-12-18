//
//  Map.h
//  FinalPP2
//
//  Created by jjeoung on 1/29/24.
//

#ifndef Map_h
#define Map_h

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map {
  public:
    Map();
    
    Map(const Map& other);
    
    Map& operator=(const Map& rhs);
    
    ~Map();
    
    bool empty() const;
    
    int size() const;
    
    bool insert(const KeyType& key, const ValueType& value);
    
    bool update(const KeyType& key, const ValueType& value);
    
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    
    bool erase(const KeyType& key);
    
    bool contains(const KeyType& key) const;
    
    bool get(const KeyType& key, ValueType& value) const;
    
    bool get(int i, KeyType& key, ValueType& value) const;
    
    void swap(Map& other);
        
  private:
    struct Pair {
        KeyType m_key;
        ValueType m_value;
        Pair* next;
        Pair* previous;
    };
    
    int m_size;
    Pair* head;
};

bool merge(const Map& m1, const Map& m2, Map& result);

void reassign(const Map& m, Map& result);

#endif /* Map_h */
