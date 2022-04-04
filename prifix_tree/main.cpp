#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <optional>
#include <utility>
#include <unordered_set>
#include <forward_list>

using namespace std::string_view_literals;

using CapitalAndAllLetters = std::pair<std::string, std::string>;

struct Node {
    std::unordered_map<char, Node> edges;
    bool is_terminal = false;
    std::unordered_set<std::string_view> words_that_containt_current_prefix;
};

struct PrefixTree {
    Node root;
    std::forward_list<std::string> word_storage;
    
    std::string_view SaveWord(std::string word) {
        word_storage.push_front(std::move(word));
        return word_storage.front();
    }
    
    void AddString(std::string_view pattern, std::string word) {
        std::string_view stored_word = SaveWord(std::move(word));
        
        Node* current_node = &root;
        
        for (char symbol : pattern) {
            if (current_node->edges.count(symbol) == 0) {
                current_node->edges[symbol] = Node{};
            }
            
            current_node = &current_node->edges.at(symbol);
            
            current_node->words_that_containt_current_prefix.insert(stored_word);
        }
        
        current_node->is_terminal = true;
    }
    
    const Node* FindNode(std::string_view word) const {
        const Node* current_node = &root;
        
        for (char symbol : word) {
            if (current_node->edges.count(symbol) == 0) {
                return nullptr;
            }
            
            current_node = &current_node->edges.at(symbol);
        }
        
        return current_node;
    }
};

CapitalAndAllLetters ReadWord(std::istream& input) {
    input >> std::ws;
    
    std::string capital_letters;
    
    std::string word;
    
    while (!std::iswspace(input.peek())) {
        char current_letter = input.get();
        
        word.push_back(current_letter);
        
        if (std::isupper(current_letter)) {
            capital_letters.push_back(current_letter);
        }
    }
    
    input >> std::ws;
    
    return {std::move(capital_letters), std::move(word)};
}

int main(int argc, const char * argv[]) {
    int n_words_in_dictionary{};
    
    std::cin >> n_words_in_dictionary;
    
    PrefixTree trie;
    
    for (int i = 0; i < n_words_in_dictionary; ++i) {
        auto [capital_letters, word] = ReadWord(std::cin);
        
        trie.AddString(capital_letters, std::move(word));
    }
    
    int n_search_requests{};
    
    std::cin >> n_search_requests >> std::ws;
    
    std::string search_request;
    
    for (int i = 0; i < n_search_requests; ++i) {
        std::getline(std::cin, search_request);
        
        if (const Node* node = trie.FindNode(search_request)) {
            for (std::string_view word : node->words_that_containt_current_prefix) {
                std::cout << word << '\n';
            }
        }
    }
    
    return 0;
}
