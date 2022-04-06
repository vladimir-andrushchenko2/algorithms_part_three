#include <iostream>
#include <vector>
#include <cctype>
#include <string_view>
#include <stack>

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

struct BracketStack {
//    std::stack<char> brackets;
    int opening_bracket_counter{};
    
    int Size() const {
        return static_cast<int>(brackets.size());
    }
    
    bool Empty() const {
        return Size() == 0;
    }
    
    void AddClosingBracket() {
        if (brackets.empty()) {
            assert(false);
        }
        
        brackets.pop();
    }
    
    void AddOpeningBracket() {
        brackets.push('[');
    }
};

std::string_view GetCompressedPartInBrackets(std::string_view text) {
    assert(text.front() == '[');
    
    BracketStack stack;
    
    text.remove_prefix(1);
    
    stack.AddOpeningBracket();
    
    
}

std::string Unpack(std::string_view text) {
    std::string output;
    
    while (!text.empty()) {
        if (std::isdigit(text.front())) {
            
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
