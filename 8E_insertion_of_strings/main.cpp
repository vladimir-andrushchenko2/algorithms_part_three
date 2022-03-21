#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

int main(int argc, const char * argv[]) {
    std::string original_string;

    std::cin >> original_string;

    std::unordered_map<int, std::string> strings_to_insert;

    int n_strings_to_insert;

    std::cin >> n_strings_to_insert;

    for (int i = 0; i < n_strings_to_insert; ++i) {
        int insert_before_index;

        std::string string_to_insert;

        std::cin >> string_to_insert >> insert_before_index;

        strings_to_insert[insert_before_index] = std::move(string_to_insert);
    }

    int original_string_size = static_cast<int>(original_string.size());

    for (int i = 0; i < original_string_size; ++i) {
        if (strings_to_insert.count(i) > 0) {
            std::cout << strings_to_insert[i];
        }

        std::cout << original_string[i];
    }

    if (strings_to_insert.count(original_string_size) > 0) {
        std::cout << strings_to_insert[original_string_size];
    }

    std::cout << '\n';
    return 0;
}
