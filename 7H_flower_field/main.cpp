#include <iostream>
#include <vector>
#include <string>

int ToInt(char digit) {
    return digit - '0';
}

int main(int argc, const char * argv[]) {
    int rows, cols;
    
    std::cin >> rows >> cols >> std::ws;
    
    std::vector<std::string> table(rows);
    
    for (auto reverse_it = table.rbegin(); reverse_it != table.rend(); ++reverse_it) {
        std::getline(std::cin, *reverse_it);
    }
    
    std::vector<std::vector<int>> memo(rows, std::vector<int>(cols));
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int bottom = row > 0 ? memo[row - 1][col] : 0;
            
            int left = col > 0 ? memo[row][col - 1] : 0;
            
            int cur_value = ToInt(table[row][col]);
            
            memo[row][col] = std::max(bottom, left) + cur_value;
        }
    }
    
    std::cout << memo.back().back() << '\n';
    
    return 0;
}
