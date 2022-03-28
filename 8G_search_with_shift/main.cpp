#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<int> GetChanges(std::vector<int> values) {
    assert(values.size() > 1);
    
    std::vector<int> output(values.size() - 1);
    
    for (int i = 0; i < output.size(); ++i) {
        output[i] = values.at(i + 1) - values.at(i);
    }
    
    return output;
}

std::vector<int> ReadArray(std::istream& input_stream, int n_values) {
    assert(n_values > 0);
    
    std::vector<int> output;
    output.reserve(n_values);
    
    int value;
    while (n_values--) {
        input_stream >> value;
        output.push_back(value);
    }
    
    return output;
}

int Find(const std::vector<int>& data, const std::vector<int>& pattern, int start) {
    assert(pattern.size() <= data.size());
    
    int last_possible_position = static_cast<int>(data.size()) - static_cast<int>(pattern.size());
    
    for (; start <= last_possible_position; ++start) {
        bool match = true;
        
        for (int offset = 0; offset < pattern.size(); ++offset) {
            if (data[start + offset] != pattern[offset]) {
                match = false;
                break;
            }
        }
        
        if (match) {
            return start;
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    int n_values;
    
    std::cin >> n_values;
    
    auto values = GetChanges(ReadArray(std::cin, n_values));
    
    int pattern_size;
    
    std::cin >> pattern_size;
    
    auto pattern = GetChanges(ReadArray(std::cin, pattern_size));
    
    int starting_position_of_search = 0;
    
    for (int i = 0; i < n_values; ++i) {
        starting_position_of_search = Find(values, pattern, starting_position_of_search);
        
        if (starting_position_of_search == -1) {
            break;
        }
        
        std::cout << ++starting_position_of_search << ' ';
    }
    
    std::cout << '\n';

    return 0;
}
