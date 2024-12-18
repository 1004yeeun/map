//
//  Map.cpp
//  FinalPP2
//
//  Created by jjeoung on 1/29/24.
//

#include "Map.h"

//do i have to delete any Pair* variable that i made/initialized in each implementation? ****************************************************
//make test cases for copy constructor Map(const Map& other) **********************

Map::Map() {
    m_size = 0;
    head = new Pair; //dummy node
    head->next = head; //itself
    head->previous = head; //itself (using a circular doubly linked list with a dummy node
}

Map::Map(const Map& other) {
    m_size = other.m_size; //set size to m_size of other Map
    
    head = new Pair; //dummy node
    head->next = head; //itself
    head->previous = head; //itself (using a circular doubly linked list with a dummy node
    
    //if other holds one pair, manually copy it in
    if (other.size()==1) {
        Pair* newPair = new Pair;
        head->next = newPair;
        head->previous = newPair;
        newPair->next = head;
        newPair->previous = head;
        newPair->m_key = (other.head->next)->m_key;
        newPair->m_value = (other.head->next)->m_value;
    }
    //if other is empty(), do nothing else
    //otherwise, iterate through the pairs in other. for each pair, create a new Pair and add it to the linked list being constructed (not other).
    else if (!other.empty()) {
        Pair* temp = other.head->next;
        Pair* pTemp = head->next;
        while (temp != other.head) {
            Pair* newPair = new Pair;
            newPair->previous = pTemp->previous;
            newPair->next = pTemp;
            (pTemp->previous)->next = newPair;
            pTemp->previous = newPair;
            newPair->m_key = temp->m_key;
            newPair->m_value = temp->m_value;

            temp = temp->next;
        }
    }
}

Map& Map::operator=(const Map& rhs) {
    Map temp = rhs;
    this->swap(temp);
        
    return* this;
}

Map::~Map() {
    Pair* p;
    Pair* temp;
    for (p = head->next; p != head;) {
        temp = p;
        p = p->next;
        delete temp;
    }
    
    delete p;
}

bool Map::empty() const {
    if (size()==0) {
        return true;
    }
    
    return false;
}

int Map::size() const {
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    //if the map contains key already, do nothing and return false
    if (contains(key)) {
        return false;
    }
    
    //if the Map is empty, manually add the first Pair to the Map
    if (empty()) {
        Pair* newPair = new Pair;
        head->next = newPair;
        head->previous = newPair;
        newPair->next = head;
        newPair->previous = head;
        newPair->m_key = key;
        newPair->m_value = value;
        m_size++;
        return true;
    }
    
    //if the Map is not empty, iterate through the Pairs comparing keys and find the Pair with a key that is greater than key. insert the Pair in a place before this Pair
    for (Pair* p = head->next; p!=head; p = p->next) {
        if (p->m_key > key) {
            Pair* newPair = new Pair;
            newPair->previous = p->previous;
            newPair->next = p;
            (p->previous)->next = newPair;
            p->previous = newPair;
            newPair->m_key = key;
            newPair->m_value = value;
            m_size++;
            return true;
        }
    }
    
    //if the key is not less than that of any of the Pairs in the Map, meaning that it is last in the alphabetization, manually add the new Pair at the end of the Map
    Pair* newPair = new Pair;
    newPair->previous = head->previous;
    newPair->next = head;
    (head->previous)->next = newPair;
    head->previous = newPair;
    newPair->m_key = key;
    newPair->m_value = value;
    m_size++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    //if Map does not contain key, do not do anything and return false
    if (!contains(key)) {
        return false;
    }
    
    //if Map does contain key, find where key is located and update its m_value to value and return true
    for (Pair* p = head->next; p!=head; p = p->next) {
        if (p->m_key == key) {
            p->m_value = value;
            return true;
        }
    }
    
    return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    //if Map contains key, update the corresponding value
    if (contains(key)) {
        for (Pair* p = head->next; p!=head; p = p->next) {
            if (p->m_key == key) {
                p->m_value = value;
                return true;
            }
        }
        
        return true;
    }
    
    //if Map does not already contain key, insert the new Pair
    //if the Map is empty, manually add the first Pair to the Map
    if (empty()) {
        Pair* newPair = new Pair;
        head->next = newPair;
        head->previous = newPair;
        newPair->next = head;
        newPair->previous = head;
        newPair->m_key = key;
        newPair->m_value = value;
        m_size++;
        return true;
    }
    
    //if the Map is not empty, iterate through the Pairs comparing keys and find the Pair with a key that is greater than key. insert the Pair in a place before this Pair
    for (Pair* p = head->next; p!=head; p = p->next) {
        if (p->m_key > key) {
            Pair* newPair = new Pair;
            newPair->previous = p->previous;
            newPair->next = p;
            (p->previous)->next = newPair;
            p->previous = newPair;
            newPair->m_key = key;
            newPair->m_value = value;
            m_size++;
            return true;
        }
    }
    
    //if the key is not less than that of any of the Pairs in the Map, meaning that it is last in the alphabetization, manually add the new Pair at the end of the Map
    Pair* newPair = new Pair;
    newPair->previous = head->previous;
    newPair->next = head;
    (head->previous)->next = newPair;
    head->previous = newPair;
    newPair->m_key = key;
    newPair->m_value = value;
    m_size++;
    return true;
}

bool Map::erase(const KeyType& key) {
    //if the key does not exist in Map, do nothing and return false
    if (!contains(key)) {
        return false;
    }
    
    //if the key exists but is the only key existing in the map, manually remove the pair from the map
    Pair* p = head->next;
    if (size()==1 && (p->m_key)==key) {
        head->next = head;
        head->previous = head;
        delete p;
        m_size--;
        return true;
    }
    
    //otherwise if the key exists in a Map with more than one pair, iterate through the pairs in Map and find where it is located. once located, remove it from the doubly linked list and return true
    for (Pair* p = head->next; p!=head; p = p->next) {
        if (p->m_key == key) {
            (p->previous)->next = p->next;
            (p->next)->previous = p->previous;
            delete p;
            m_size--;
            return true;
        }
    }
    
    return true;
}


bool Map::contains(const KeyType& key) const {
    //starting at the Pair after the dummy node (since dummy node is always of no value) iterate through each Pair in the Map until key is found. if key is found before p has come back to the dummy node, return true. else, return false.
    for (Pair* p = head->next; p!=head; p = p->next) {
        if (p->m_key == key) {
            return true;
        }
    }
    
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    //if the map does not contain key, do nothing and return false
    if (!contains(key)) {
        return false;
    }
    
    //iterate through the map and find key. once found, set value equal to the value in the map corresponding with key
    for (Pair* p = head->next; p!=head; p = p->next) {
        if (p->m_key == key) {
            value = p->m_value;
            return true;
        }
    }
    
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    //if i is negative (nonsense) or greater than the m_size, do nothing and return false. if m_size is 2 and i=2, this is nonsense. there are only two Pairs, in which none of them will be or could be greater than two Pairs in the map
    if (i <0 || i>=m_size) {
        return false;
    }
    
    //if Map is empty, there is nothing to return. do nothing and return false
    if (empty()) {
        return false;
    }
    
    //if m_size is 1, manually return the corresponding values
    if (size()==1) {
        if (i==0) {
            key = (head->next)->m_key;
            value = (head->next)->m_value;
            return true;
        }
        else {
            return false;
        }
    }
    
    //for any other Map size, if i=0, manually return the corresponding values
    if (i==0) {
        key = (head->next)->m_key;
        value = (head->next)->m_value;
        return true;
    }
    
    //for any other Map size, if i=1, manually return the corresponding values
    if (i==1) {
        key = ((head->next)->next)->m_key;
        value = ((head->next)->next)->m_value;
        return true;
    }
    
    //for any other Map size, iterate through the map until temp pointer p is pointing at the Pair that is greater than i Pairs.
    Pair* p = head->next;
    for (int k=0; k<i; k++) {
        p = p->next;
    }
    
    //assign the m_key and m_value of this Pair to key and value. return true
    key = p->m_key;
    value = p->m_value;
    return true;
}

//Another requirement is that as in Problem 5 of Homework 1, the number of statement executions when swapping two maps must be the same no matter how many key/value pairs are in the maps. ********************************************
void Map::swap(Map& other) {
    //switch map sizes
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    //switch head pointers
    Pair* temp_head = head;
    head = other.head;
    other.head = temp_head;
}

//so should we begin by clearing Map& result? or do we consider repeats already in the Map? ***************
bool merge(const Map& m1, const Map& m2, Map& result) {
    //clear the result Map of any pairs in it
    bool isItTrue = true;
    Map m1_temp = m1;
    Map m2_temp = m2;
    if (!result.empty()) {
        Map emptyTemp;
        result = emptyTemp;
    }
    
    //start with m1. add all of the keys and values into result
    result = m1_temp;
    
    //now, iterate through each key in m2. if result contains the key, check if the corresponding values match. if they do match, do nothing (don't add a duplicate) and move on to the next key. if they do not match, delete the key entirely from the result map and move on to the next key until i==m_size
    KeyType k_temp;
    ValueType v_temp;
    for (int i=0; i<m2_temp.size(); i++) {
        m2_temp.get(i,k_temp,v_temp);
        if (result.contains(k_temp)) {
            ValueType v_tempResult;
            result.get(k_temp,v_tempResult);
            if (v_tempResult != v_temp) {
                result.erase(k_temp);
                isItTrue = false;
            }
        }
        else {
            m2_temp.get(i,k_temp,v_temp);
            result.insert(k_temp,v_temp);
        }
    }
    
    return isItTrue;
}

void reassign(const Map& m, Map& result) {
    //initialize the result map to be empty
    if (!result.empty()) {
        Map emptyMap;
        result = emptyMap;
    }
    
    //if m is empty, do nothing.
    
    //if m only has one item, set result to itself.
    result = m;
    
    //if m has more than one items
    if (m.size()>1) {
        //iterate through m and add each item to result
        for (int i=0; i<m.size(); i++) {
            KeyType keyTemp;
            ValueType valueTemp;
            m.get(i,keyTemp,valueTemp);
            result.insert(keyTemp,valueTemp);
        }
        
        //iterate through result. get the value at i
        KeyType trashIt;
        ValueType valueForLast;
        result.get(0,trashIt,valueForLast);
        for (int i=0; i<m.size()-1; i++) {
            KeyType keyTempCurrent;
            ValueType valueNew;
            result.get(i,keyTempCurrent,valueNew);
            result.get(i+1,trashIt,valueNew);
            result.update(keyTempCurrent,valueNew);
        }
        ValueType trashV;
        result.get((result.size()-1),trashIt, trashV);
        result.update(trashIt,valueForLast);
    }
}
