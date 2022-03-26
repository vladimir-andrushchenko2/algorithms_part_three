#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int LevenshteinDistance(const std::string& source, const std::string& target) {
    std::vector<std::vector<int>> dp(source.size() + 1, std::vector<int>(target.size() + 1));
    
    for (int i = 1; i <= source.size(); ++i) {
        dp[i][0] = i;
    }
    
    for (int j = 1; j <= target.size(); ++j) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= source.size(); ++i) {
        for (int j = 1; j <= target.size(); ++j) {
            int substitution_cost = source.at(i - 1) == target.at(j - 1) ? 0 : 1;
            
            dp[i][j] = std::min({
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + substitution_cost
            });
        }
    }
    
    return dp.back().back();
}

int main(int argc, const char * argv[]) {
    std::string source, target;
    
    std::getline(std::cin, source);
    std::getline(std::cin, target);
    
    std::cout << LevenshteinDistance(source, target) << '\n';
    return 0;
    
}
