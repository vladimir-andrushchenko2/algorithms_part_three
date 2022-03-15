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

std::string GetOptimalRoute(Matrix matrix) {
    int x = static_cast<int>(matrix.front().size()) - 1;

    int y = static_cast<int>(matrix.size()) - 1;

    std::string output;
    while (x > 0 || y > 0) {
        if (x == 0) {
            output.push_back('U');

            --y;

            continue;
        }

        if (y == 0) {
            output.push_back('R');

            --x;

            continue;
        }

        if (matrix[y][x - 1] < matrix[y - 1][x]) {
            output.push_back('U');

            --y;

        } else {
            output.push_back('R');

            --x;
        }
    }

    return {output.rbegin(), output.rend()};
}

int main(int argc, const char * argv[]) {
    auto matrix = TraverseField(ReadField(std::cin));

    std::cout << matrix.back().back() << '\n';

    std::cout << GetOptimalRoute(std::move(matrix)) << '\n';

    return 0;
}
