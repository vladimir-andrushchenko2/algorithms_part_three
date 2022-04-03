#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <optional>
#include <utility>

using namespace std::string_view_literals;

struct Node {
    std::unordered_map<char, Node> edges;
    bool is_terminal = false;
    std::string data;
};

struct PrefixTree {
    Node root;
    
    Node* AddString(std::string_view word) {
        Node* current_node = &root;
        
        for (char symbol : word) {
            if (current_node->edges.count(symbol) == 0) {
                current_node->edges.insert({symbol, {}});
            }
            
            current_node = &current_node->edges.at(symbol);
        }
        
        current_node->is_terminal = true;
        
        return current_node;
    }
    
    static Node& AddEdgeOrGetAt(char letter, Node& node) {
        if (node.edges.count(letter) == 0) {
            node.edges.insert({letter, {}});
        }
        
        return node.edges[letter];
    }
    
    const Node* FindNode(std::string_view word) const {
        const Node* current_node = &root;
        
        for (char symbol : word) {
            if (current_node->edges.count(symbol) == 0) {
                return {};
            }
            
            current_node = &current_node->edges.at(symbol);
        }
        
        return current_node;
    }
};



int main(int argc, const char * argv[]) {
    PrefixTree trie;
    
    trie.AddString("Hi"sv);
    trie.AddString("Bye"sv);
    
    if (auto ptr = trie.FindNode("Hi"sv)) {
        assert(true);
    }
    
    if (auto ptr = trie.FindNode("Potato"sv); !ptr) {
        assert(true);
    }
    
    return 0;
}
