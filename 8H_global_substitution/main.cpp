#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_set>

using Indexes = std::unordered_set<int>;

Indexes Find(const std::string& pattern, const std::string& text) {
    Indexes output;
    
    std::string data = pattern + '#' + text;
    int data_size = static_cast<int>(data.size());
    
    std::vector<int> prefix_functions_of_pattern(pattern.size());
    
    int previous_prefix_function = 0;
    
    for (int i = 1; i < data_size; ++i) {
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
            output.insert(i - 2 * static_cast<int>(pattern.size()));
        }
    }
    
    return output;
}

void PrintReplace(std::string_view text, std::string_view replacement, Indexes indexes_to_replace, std::size_t letters_to_skip_at_replacement) {
    for (int i = 0; i < text.size();) {
        if (indexes_to_replace.count(i) > 0) {
            std::cout << replacement;
            
            i += letters_to_skip_at_replacement;
            
        } else {
            std::cout << text[i];
            
            ++i;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::string text;
    
    std::getline(std::cin, text);
    
    std::string pattern;
    
    std::getline(std::cin, pattern);
    
    std::string replacement;
    
    std::getline(std::cin, replacement);
    
    auto indexes = Find(pattern, text);
    
    PrintReplace(text, replacement, indexes, pattern.size());
    return 0;
}
