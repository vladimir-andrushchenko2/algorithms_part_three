#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <utility>
#include <memory>
#include <vector>

using namespace std::string_view_literals;


class PrefixTree {

public:
    void AddWord(std::string_view word) {
        auto& root = nodes_.front();

        
    }
    
    std::vector<std::string_view> FindPrefixesThatAreWords(std::string_view word) const {
        assert(false);
        return {};
    }

private:
    using IndexOfNext = int;

    struct Node {
        std::unordered_map<char, IndexOfNext> edges;
        bool is_terminal = false;
        std::string_view word;
    };

private:
    std::vector<Node> nodes_ = std::vector<Node>(1);
};

bool IsTextComposedOfWords(std::string_view text, const PrefixTree& trie) {
    if (text.empty()) {
        return true;
    }
    
    for (auto prefix : trie.FindPrefixesThatAreWords(text)) {
        std::string_view text_without_prefix = text;
        
        text_without_prefix.remove_prefix(prefix.size());
        
        if (IsTextComposedOfWords(text_without_prefix, trie)) {
            return true;
        }
    }

    return false;
}

int main(int argc, const char * argv[]) {
    std::string text;
    
    std::getline(std::cin, text);
    
    int n_words;
    
    std::cin >> n_words >> std::ws;
    
    std::vector<std::string> correct_words;
    
    for (int i = 0; i < n_words; ++i) {
        std::string& another_word = correct_words.emplace_back();
        std::getline(std::cin, another_word);
    }
    
    PrefixTree trie;
    
    for (std::string_view word : correct_words) {
        trie.AddWord(word);
    }
    
    if (IsTextComposedOfWords(text, trie)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    
    return 0;
}
