#include <iostream>
#include <string>
#include <algorithm>

bool EvenLetter(char letter) {
    return (letter - 'a' + 1) % 2 == 0;
}

struct EvenString {
    EvenString(const std::string& data) : data(data) {
        while (index < data.size() && !EvenLetter(data[index])) {
            ++index;
        }

        if (!EvenLetter(data[index])) {
            ++index;
        }
    }

    char GetNextChar() {
        while (!EvenLetter(data[index]) && index < data.size()) {
            ++index;
        }

        if (index == data.size()) {
            assert(false);
        }

        return data[index];
    }

    bool IsEmpty() const {
        return index == data.size();
    }

    int index{};

    const std::string& data;
};

int main() {
    std::string left, right;
    
    std::cin >> left >> right;


    
    return 0;
}
