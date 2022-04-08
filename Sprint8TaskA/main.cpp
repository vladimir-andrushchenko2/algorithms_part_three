#include <iostream>
#include <vector>
#include <cctype>
#include <string_view>
#include <cassert>

using namespace std::string_literals;

int ExtractNumber(std::string_view& text) {
    int output{};
    
    while (std::isdigit(text.front())) {
        output = output * 10 + (text.front() - '0');
        text.remove_prefix(1);
    }
    
    return output;
}

std::string_view GetCompressedPartInBrackets(std::string_view text) {
    assert(text.front() == '[');
    
    int opened_bracket_counter = 1;
    
    for (int i = 1; i < text.size(); ++i) {
        if (text[i] == '[') {
            ++opened_bracket_counter;
        }
        
        if (text[i] == ']') {
            --opened_bracket_counter;
            
            if (opened_bracket_counter == 0) {
                // - 1 to avoid closing bracket in output
                return text.substr(1, i - 1);
            }
        }
    }
    
    assert(false);
    return {};
}

std::string Multiply(std::string text, std::size_t times) {
    text.reserve(text.size() * times);
    std::string_view source = text;
    
    for (int i = 1; i < times; ++i) {
        text.append(source);
    }
    
    return text;
}

std::string Unpack(std::string_view text) {
    std::string prefix;
    
    while (!text.empty()) {
        if (std::isdigit(text.front())) {
            int n = ExtractNumber(text);
            
            std::string_view compressed_part = GetCompressedPartInBrackets(text);

            // + 2 for '[' and ']'
            text.remove_prefix(compressed_part.size() + 2);
            
            return prefix + Multiply(Unpack(compressed_part), n) + Unpack(text);
        }
        
        prefix.push_back(text.front());
        text.remove_prefix(1);
    }
    
    return prefix;
}

int LengthOfCommonPrefix(const std::vector<std::string>& strings) {
    int index_of_symbol = 0;

    for (;index_of_symbol < strings.front().size(); ++index_of_symbol) {
        char possibly_common_symbol = strings.front()[index_of_symbol];

        for (int index_of_another_string = 1; index_of_another_string < strings.size(); ++index_of_another_string) {
            if (strings[index_of_another_string][index_of_symbol] != possibly_common_symbol) {
                return index_of_symbol;
            }
        }
    }

    return index_of_symbol;
}

int main(int argc, const char * argv[]) {
    int n_packed_strings;

    std::cin >> n_packed_strings >> std::ws;

    std::vector<std::string> unpacked_strings;

    std::string packed_string;
    
    for (int i = 0; i < n_packed_strings; ++i) {
        std::getline(std::cin, packed_string);

        unpacked_strings.push_back(Unpack(packed_string));
    }

    std::string_view longest_common_prefix = std::string_view{unpacked_strings.front().data(), static_cast<size_t>(LengthOfCommonPrefix(unpacked_strings))};

    std::cout << longest_common_prefix << '\n';

    return 0;
}
