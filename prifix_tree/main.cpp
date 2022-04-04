#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <optional>
#include <utility>
#include <unordered_set>
#include <set>
#include <memory>

using namespace std::string_view_literals;

using CapitalAndAllLetters = std::pair<std::string, std::string>;

struct Node {
    std::unordered_map<char, std::unique_ptr<Node>> edges;
    bool is_terminal = false;
    std::unordered_set<std::string_view> words_that_containt_current_prefix;
};

struct PrefixTree {
    Node root;
    std::set<std::string> word_storage;
    
    std::string_view SaveWord(std::string word) {
        auto [iterator, is_inserted] = word_storage.insert(std::move(word));
        return *iterator;
    }
    
    const auto& GetStoredWords() const {
        return word_storage;
    }
    
    void AddString(std::string_view pattern, std::string word) {
        std::string_view stored_word = SaveWord(std::move(word));
        
        Node* current_node = &root;
        
        for (char symbol : pattern) {
            if (current_node->edges.count(symbol) == 0) {
                current_node->edges[symbol] = std::make_unique<Node>();
            }
            
            current_node = current_node->edges.at(symbol).get();
            
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
            
            current_node = current_node->edges.at(symbol).get();
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
    
    std::cin >> n_search_requests;
    
    std::cin.get();
    
    std::string search_request;
    
    for (int i = 0; i < n_search_requests; ++i) {
        std::getline(std::cin, search_request);
        
        if (search_request.empty()) {
            for (auto word : trie.GetStoredWords()) {
                std::cout << word << '\n';
            }
            
            continue;
        }
        
        if (const Node* node = trie.FindNode(search_request)) {
            for (std::string_view word : node->words_that_containt_current_prefix) {
                std::cout << word << '\n';
            }
        } else {
            std::cout << '\n';
        }
    }
    
    return 0;
}
