#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::unordered_map;

class LruCache {
    unordered_map<int, pair<int, int>> map;
    int capacity;
    int opcode;

    void eviction() {
        int min = opcode + 1;
        int isbn;
        
        for (auto book : map) {
            if (min > book.second.second) {
                min = book.second.second;
                isbn = book.first;
            }
        }
        map.erase(isbn);
    }

  public:
    LruCache(size_t c) {
        capacity = c;
    }
    int Lookup(int isbn) {
        if (map.find(isbn) == map.end()) {
            return -1;
        }
        opcode += 1;
        map[isbn].second = opcode;
        return map[isbn].first;
    }
    void Insert(int isbn, int price) {
        opcode += 1;
        if (map.find(isbn) == map.end()) {
            map.insert({isbn, {price, opcode}});
        } else {
            map[isbn].second = opcode;
        }
        if (map.size() > capacity) {
            eviction();
        }
        return;
    }
    bool Erase(int isbn) {
        if (map.find(isbn) == map.end()) {
            return false;
        }
        map.erase(isbn);
        return true;
    }
};
struct Op {
    std::string code;
    int arg1;
    int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
    if (commands.empty() || commands[0].code != "LruCache") {
        throw std::runtime_error("Expected LruCache as first command");
    }
    LruCache cache(commands[0].arg1);

    for (int i = 1; i < commands.size(); i++) {
        auto& cmd = commands[i];
        if (cmd.code == "lookup") {
            int result = cache.Lookup(cmd.arg1);
            if (result != cmd.arg2) {
                throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                                  ", got " + std::to_string(result));
            }
        } else if (cmd.code == "insert") {
            cache.Insert(cmd.arg1, cmd.arg2);
        } else if (cmd.code == "erase") {
            bool result = cache.Erase(cmd.arg1);
            if (result != cmd.arg2) {
                throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                                  ", got " + std::to_string(result));
            }
        } else {
            throw std::runtime_error("Unexpected command " + cmd.code);
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"commands"};
    return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                           DefaultComparator{}, param_names);
}
