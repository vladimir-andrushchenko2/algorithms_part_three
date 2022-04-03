#include <iostream>
#include <vector>
#include <string>

using Indexes = std::vector<int>;

Indexes Find(const std::string& pattern, const std::string& text) {
    Indexes output;
    
    std::string data = pattern + '#' + text;
    int data_size = static_cast<int>(data.size());
    
    std::vector<int> prefix_functions_of_pattern(pattern.size());
    
    int previous_prefix_function = 0;
    
    for (int i = 0; i < data_size; ++i) {
        int k = previous_prefix_function;
        
        while (k > 0 && data[k] != data[i]) {
            k = prefix_functions_of_pattern.at(k - 1);
        }
        
        if (data[k] == data[i]) {
            ++k;
        }
        
        if (i < pattern.size()) {
            prefix_functions_of_pattern[i] = k;
        }
        
        previous_prefix_function = k;
        
        if (k == pattern.size()) {
            output.push_back(i - 1 - 2 * pattern.size());
        }
    }
    
    return output;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
