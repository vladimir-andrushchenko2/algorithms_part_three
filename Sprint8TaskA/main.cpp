#include <iostream>
#include <vector>
#include <cctype>
#include <string_view>
#include <stack>

using namespace std::string_literals;

static constexpr int kBasisForHashing = 1283;

static constexpr int kModuloForHashing = 9001;

std::vector<int> GenerateSizeOfPrefixToHash(std::string_view string_to_hash, int basis_for_hashing, int modulo) {
    std::vector<int> hashes_of_prefixes(string_to_hash.size() + 1);
    
    for (int i = 1; i < string_to_hash.size() + 1; ++i) {
        hashes_of_prefixes[i] = (((hashes_of_prefixes[i - 1] * basis_for_hashing) % modulo) + string_to_hash[i - 1] % modulo) % modulo;
    }
    
    return hashes_of_prefixes;
}

int ReadNumber(std::string_view& text) {
    int output{};
    
    while (std::isdigit(text.front())) {
        output = output * 10 + text.front();
        text.remove_prefix(1);
    }
    
    return output;
}

std::string_view GetCompressedPartInBrackets(std::string_view text) {
    assert(text.front() == '[');
    
    int opened_bracket_counter = 1;
    
    for (int i = 0; i < text.size(); ++i) {
        if (text[i] == '[') {
            ++opened_bracket_counter;
        }
        
        if (text[i] == ']') {
            --opened_bracket_counter;
            
            if (opened_bracket_counter == 0) {
                return text.substr(1, i);
            }
        }
    }
    
    assert(false);
    return {};
}

std::string Multiply(std::string text, std::size_t times) {
    std::string_view source = text;
    
    for (int i = 0; i < times; ++i) {
        text.append(source);
    }
    
    return text;
}

std::string Unpack(std::string_view text) {
    std::string prefix;
    
    while (!text.empty()) {
        if (std::isdigit(text.front())) {
            int n = ReadNumber(text);
            
            std::string_view compressed_part = GetCompressedPartInBrackets(text);
            
            text.remove_prefix(compressed_part.size());
            
            return prefix + Multiply(Unpack(compressed_part), n) + Unpack(text);
        }
        
        prefix.push_back(text.front());
        text.remove_prefix(1);
    }
    
    return prefix;
}

int main(int argc, const char * argv[]) {
    std::string unpacked = Unpack("2[a]2[ab]"s);
    
    assert(unpacked == "aaabab"s);
    return 0;
}
