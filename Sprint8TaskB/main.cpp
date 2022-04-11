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
        Index current_node_index = kIndexOfRoot;

        for (char symbol : word) {
            if (nodes_.at(current_node_index).edges.count(symbol) == 0) {
                nodes_.at(current_node_index).edges[symbol] = nodes_.size();
                nodes_.emplace_back();
            }
            
            current_node_index = nodes_.at(current_node_index).edges[symbol];
        }
        
        nodes_.at(current_node_index).is_terminal = true;
        nodes_.at(current_node_index).word = word;
    }
    
    std::vector<std::string_view> FindPrefixesThatAreWords(std::string_view word) const {
        Index current_node_index = kIndexOfRoot;
        
        std::vector<std::string_view> output;
        
        for (char symbol : word) {
            if (nodes_.at(current_node_index).edges.count(symbol) == 0) {
                break;
            }
            
            current_node_index = nodes_.at(current_node_index).edges.at(symbol);
            
            if (nodes_.at(current_node_index).is_terminal) {
                output.push_back(nodes_.at(current_node_index).word);
            }
        }
        
        return output;
    }

private:
    using Index = std::size_t;
    
    static constexpr std::size_t kIndexOfRoot = 0;

    struct Node {
        std::unordered_map<char, Index> edges;
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
