#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Record {
    std::string key;
    std::string value1;
    std::string value2;
    std::string value3;

    bool operator==(const Record& other) const {
        return key == other.key && value1 == other.value1 && value2 == other.value2 && value3 == other.value3;
    }
};

struct RecordHash {
    std::size_t operator()(const Record& record) const {
        return std::hash<std::string>()(record.key);
    }
};

int main() {
    std::ifstream file("test1.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }

    std::unordered_map<Record, std::vector<Record>, RecordHash> hashTable;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;

        std::getline(ss, item, ',');
        std::string key = item;
        std::getline(ss, item, ',');
        std::string value1 = item;
        std::getline(ss, item, ',');
        std::string value2 = item;
        std::getline(ss, item, ',');
        std::string value3 = item;

        Record record;
        record.key = key;
        record.value1 = value1;
        record.value2 = value2;
        record.value3 = value3;

        hashTable[record].push_back(record);
    }

    file.close();

    for (const auto& pair : hashTable) {
        const std::vector<Record>& chain = pair.second;
        std::cout << "Key: " << chain[0].key << std::endl;
        for (const Record& record : chain) {
            std::cout << "Value1: " << record.value1 << std::endl;
            std::cout << "Value2: " << record.value2 << std::endl;
            std::cout << "Value3: " << record.value3 << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
