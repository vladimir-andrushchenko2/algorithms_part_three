#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <string_view>
#include <queue>

using ID = int;

struct Vertex {
    std::unordered_map<char, ID> children;
    bool leaf = false;
    ID parent = -1;
    ID suffix_link = -1;
    ID word_id = -1;
    ID end_word_link = -1;
    char parent_char = '\0';
};

struct Aho {
    Aho(const std::vector<std::string>& patterns) {
        int counter{};
        for (auto pattern : patterns) {
            AddString(pattern, counter++);
        }

        PrepareAho();
    }

private:
    void AddString(std::string_view word, ID word_id) {
        ID current_vertex = kRootId_;

        for (int i = 0; i < word.size(); ++i) {
            char current_char = word[i];

            if (trie_[current_vertex].children.count(current_char) == 0) {
                Vertex& new_vertex = trie_.emplace_back();

                new_vertex.parent = current_vertex;
                new_vertex.parent_char = current_char;

                trie_[current_vertex].children[current_char] = size_;

                ++size_;
            }

            current_vertex = trie_[current_vertex].children[current_char];
        }

        trie_[current_vertex].leaf = true;
        trie_[current_vertex].word_id = word_id;
        words_length_.push_back(word.size());
    }

    void CalculateSuffixLink(ID vertex_id) {
        if (vertex_id == kRootId_) {
            trie_[vertex_id].suffix_link = kRootId_;
            trie_[vertex_id].end_word_link = kRootId_;
            return;
        }

        if (trie_[vertex_id].parent == kRootId_) {
            trie_[vertex_id].suffix_link = kRootId_;

            if (trie_[vertex_id].leaf) {
                trie_[vertex_id].end_word_link = vertex_id;

            } else {
                trie_[vertex_id].end_word_link = trie_[trie_[vertex_id].suffix_link].end_word_link;
            }

            return;
        }

        ID current_better_vertex = trie_[trie_[vertex_id].parent].suffix_link;
        char parent_char = trie_[vertex_id].parent_char;

        while (true) {
            if (trie_[current_better_vertex].children.count(parent_char) > 0) {
                trie_[vertex_id].suffix_link = trie_[current_better_vertex].children[parent_char];
                break;
            }

            if (current_better_vertex == kRootId_) {
                trie_[vertex_id].suffix_link = kRootId_;
                break;
            }

            current_better_vertex = trie_[current_better_vertex].suffix_link;
        }

        if (trie_[vertex_id].leaf) {
            trie_[vertex_id].end_word_link = vertex_id;
        } else {
            trie_[vertex_id].end_word_link = trie_[trie_[vertex_id].suffix_link].end_word_link;
        }
    }

    void PrepareAho() {
        std::queue<ID> vertex_queue;

        vertex_queue.push(kRootId_);

        while (!vertex_queue.empty()) {
            ID current_vertex = vertex_queue.front();

            vertex_queue.pop();

            CalculateSuffixLink(current_vertex);

            for (auto [edge, child_id] : trie_[current_vertex].children) {
                vertex_queue.push(child_id);
            }
        }

    }

private:
    std::vector<Vertex> trie_ = {{}};
    std::vector<std::size_t> words_length_;
    int size_ = 1;
    static constexpr ID kRootId_ = 0;
};

int main() {
    Aho aho({"he", "she"});

    std::cout << "Hello, World!\n";
    return 0;
}
