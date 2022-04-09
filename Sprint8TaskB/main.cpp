#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <utility>
#include <memory>
#include <vector>

using namespace std::string_view_literals;

struct Node {
    std::unordered_map<char, std::unique_ptr<Node>> edges;
    bool is_terminal = false;
    std::string_view word;
};

struct PrefixTree {
    Node root;
    
    void AddWord(std::string_view word) {
        Node* current_node = &root;
        
        for (char symbol : word) {
            if (current_node->edges.count(symbol) == 0) {
                current_node->edges[symbol] = std::make_unique<Node>();
            }
            
            current_node = current_node->edges.at(symbol).get();
        }
        
        current_node->is_terminal = true;
        current_node->word = word;
    }
    
    std::vector<const Node*> FindPrefixesThatAreWords(std::string_view word) const {
        const Node* current_node = &root;
        
        std::vector<const Node*> output;
        
        for (char symbol : word) {
            if (current_node->edges.count(symbol) == 0) {
                break;
            }
            
            current_node = current_node->edges.at(symbol).get();
            
            if (current_node->is_terminal) {
                output.push_back(current_node);
            }
        }
        
        return output;
    }
};

bool IsTextComposedOfWords(std::string_view text, const PrefixTree& trie) {
    if (text.empty()) {
        return true;
    }
    
    for (const Node* prefix : trie.FindPrefixesThatAreWords(text)) {
        std::string_view text_without_prefix = text;
        
        text_without_prefix.remove_prefix(prefix->word.size());
        
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
