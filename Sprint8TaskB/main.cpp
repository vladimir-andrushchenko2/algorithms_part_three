#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <utility>
#include <memory>
#include <vector>
#include <unordered_set>

using namespace std::string_view_literals;

struct Node {
    std::unordered_map<char, std::unique_ptr<Node>> edges;
    bool is_terminal = false;
};

struct PrefixTree {
    std::unique_ptr<Node> root = std::make_unique<Node>();
    
    void AddWord(std::string_view word) {
        Node* current_node = root.get();
        
        for (char symbol : word) {
            if (current_node->edges.count(symbol) == 0) {
                current_node->edges[symbol] = std::make_unique<Node>();
            }
            
            current_node = current_node->edges.at(symbol).get();
        }
        
        current_node->is_terminal = true;
    }
};

bool IsTextComposedOfWords(std::string_view text, const PrefixTree& trie) {
    std::unordered_set<const Node*> current_nodes;
    current_nodes.insert(trie.root.get());
    
    for (char symbol : text) {
        std::unordered_set<const Node*> next_nodes;
        
        for (auto node : current_nodes) {
            if (node->edges.count(symbol) > 0) {
                next_nodes.insert(node->edges.at(symbol).get());
                
                if (node->edges.at(symbol)->is_terminal) {
                    next_nodes.insert(trie.root.get());
                }
            }
        }
        
        std::swap(next_nodes, current_nodes);
    }
    
    for (auto& node : current_nodes) {
        if (node->is_terminal) {
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
