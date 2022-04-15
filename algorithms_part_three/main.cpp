#include <iostream>
#include <map>
#include <string>
#include <string_view>

using Dict = std::map<char, int>;

Dict CountLetters(std::string_view text) {
    Dict output;

    for (char symbol : text) {
        ++output[symbol];
    }

    return output;
}

std::string GetLongesAnagram(const Dict& dict) {
    std::string output;

    bool is_middle_letter_found = false;

    char middle_letter = '\0';

    for (auto [symbol, count] : dict) {
        if (!is_middle_letter_found) {
            // if odd
            if (count % 2 == 1) {
                is_middle_letter_found = true;

                middle_letter = symbol;
            }
        }

        int pairs = count / 2;

        for (int i = 0; i < pairs; ++i) {
            output.push_back(symbol);
        }
    }

    int first_half_size = static_cast<int>(output.size());

    if (is_middle_letter_found) {
        output.push_back(middle_letter);
    }

    for (int i = first_half_size - 1; i >= 0; --i) {
        output.push_back(output[i]);
    }

    return output;
}

int main(int argc, const char * argv[]) {
    std::string text;

    std::getline(std::cin, text);
    std::cout << GetLongesAnagram(CountLetters(text)) << '\n';
    return 0;
}
