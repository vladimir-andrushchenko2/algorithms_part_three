// 67372293
#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <utility>
#include <memory>
#include <vector>
#include <unordered_set>

/*
-- ПРИНЦИП РАБОТЫ --
 Динамически запоминаю какой длинны префикс текста можно разложить на слова
 и если текст длинны на один меньше разложить можно, то запускаю бор с такущей позиции в тексте
 и выявляю на каких последующих размерах префикса оканчиваются слова

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 В наихудшем случае текс можно разбить на текст в каждой позиции и длинна самого большого шаблона помещенного в бор достаточно велика
 Например text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          patterns = ["a", "aaaaaaaaaaaaa"]
 таким образом при определенных условиях сложность может быть O(n^2)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 Для алгорима нужен бор, текст, и память для мемоизации равная размеру текста, таким образом O(2n + patterns_size).
*/


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

bool IsTextComposedOfWordsDynamic(std::string_view text, const PrefixTree& trie) {
    std::vector<bool> is_prefix_size_words(text.size() + 1, false);

    is_prefix_size_words[0] = true;

    for (int prefix_size = 1; prefix_size < is_prefix_size_words.size(); ++prefix_size) {
        if (is_prefix_size_words[prefix_size - 1]) {
            const Node* node = trie.root.get();

            int counter_of_nodes_traversed = 0;

            while (node->edges.count(text[prefix_size + counter_of_nodes_traversed - 1]) > 0) {
                node = node->edges.at(text[prefix_size + counter_of_nodes_traversed - 1]).get();

                if (node->is_terminal) {
                    is_prefix_size_words[prefix_size + counter_of_nodes_traversed] = true;
                }

                ++counter_of_nodes_traversed;
            }
        }
    }

    return is_prefix_size_words[text.size()];
}

bool IsTextComposedOfWordsDynamic(std::string_view text, const PrefixTree& trie) {
    std::vector<bool> is_prefix_size_words(text.size() + 1, false);
    
    is_prefix_size_words[0] = true;
    
    for (int i = 1; i <= text.size(); ++i) {
        if (is_prefix_size_words[i - 1]) {
            const Node* node = trie.root.get();
        
            int counter{};
            
            while (node->edges.count(text[i + counter - 1]) > 0) {
                node = node->edges.at(text[i + counter - 1]).get();
                
                if (node->is_terminal) {
                    is_prefix_size_words[i + counter] = true;
                }
                
                ++counter;
            }
        }
    }
    
    return is_prefix_size_words[text.size()];
}

int main() {
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

    if (IsTextComposedOfWordsDynamic(text, trie)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}
