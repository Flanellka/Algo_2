#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <string>

struct HashTable {
    size_t m_TableSize;
    std::vector<std::list<std::pair<std::string, int>>> m_Table;

    HashTable(int size) : m_TableSize(size), m_Table(size) {}

    /**
     * Хеш-функция
     */
    int Hash(std::string key) const {
        unsigned long long hashValue = 0;
        int p = 31; 

        for (char c : key) {
            hashValue = (hashValue * p + c) % m_TableSize;
        }
        return hashValue;
    }

    /**
     * Вставка пары (ключ, значение)
     */
    void Insert(std::string key, int value) {
        int index = Hash(key); 

        for (auto& entry : m_Table[index]) {
            if (entry.first == key) {
                entry.second = value; 
                return;               
            }
        }

        m_Table[index].push_back(std::make_pair(key, value));
    }

    /**
     * Получение значения по ключу
     */
    bool Get(std::string key, int& value) const {
        int index = Hash(key); 

        for (const auto& entry : m_Table[index]) {
            if (entry.first == key) {
                value = entry.second; 
                return true;       
            }
        }
        return false; 
    }

    /**
     * Удаление элемента по ключу
     */
    bool Remove(std::string key) {
        int index = Hash(key); 

        for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it) {
            if (it->first == key) {
                m_Table[index].erase(it); 
                return true;              
            }
        }
        return false; 
    }

    std::string getTable() const {
        std::string ans = "";
        for (int i = 0; i < m_TableSize; i++) {
            ans += "Bucket " + std::to_string(i) + ": ";
            for (const auto& entry : m_Table[i]) {
                ans += "[" + entry.first + ":" + std::to_string(entry.second) + "]";
            }
            ans += "\n";
        }
        return ans;
    }
};