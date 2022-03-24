#include <iostream>
#include <string>
#include <algorithm>

bool EvenLetter(char letter) {
    return (letter - 'a' + 1) % 2 == 0;
}

// Even word is a word that consists of letters that are on even spaces in the alphabet
std::string ReadEvenWord(std::istream& input) {
    std::string output;

    char another_char;

    another_char = input.get();

    while(!std::iswspace(another_char)) {
        if (EvenLetter(another_char)) {
            output.push_back(another_char);
        }

        another_char = input.get();
    }

    return output;
}

int main() {
    std::string left, right;

    left = ReadEvenWord(std::cin);

    right = ReadEvenWord(std::cin);

    if (left < right) {
        std::cout << -1;
    } else if (left > right) {
        std::cout << 1;
    } else {
        std::cout << 0;
    }

    std::cout << '\n';

    return 0;
}
