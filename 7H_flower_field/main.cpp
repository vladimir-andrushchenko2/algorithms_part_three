#include <iostream>
#include <vector>
#include <string>

int ToInt(char digit) {
    return digit - '0';
}

using Matrix = std::vector<std::vector<int>>;

using Field = std::vector<std::string>;

Field ReadField(std::istream& input) {
    int rows, cols;

    input >> rows >> cols >> std::ws;

    std::vector<std::string> table(rows);

    for (auto reverse_it = table.rbegin(); reverse_it != table.rend(); ++reverse_it) {
        std::getline(input, *reverse_it);
    }

    return table;
}

Matrix TraverseField(const Field& field) {
    int rows = static_cast<int>(field.size());

    int cols = static_cast<int>(field.front().size());

    std::vector<std::vector<int>> memo(rows, std::vector<int>(cols));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int bottom = row > 0 ? memo[row - 1][col] : 0;

            int left = col > 0 ? memo[row][col - 1] : 0;

            int cur_value = ToInt(field[row][col]);

            memo[row][col] = std::max(bottom, left) + cur_value;
        }
    }

    return memo;
}

int main(int argc, const char * argv[]) {
    std::cout << TraverseField(ReadField(std::cin)).back().back() << '\n';
    
    return 0;
}
