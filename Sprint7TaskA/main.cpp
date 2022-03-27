#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
-- ПРИНЦИП РАБОТЫ --
Источником вдохновения послужил https://en.wikipedia.org/wiki/Wagner-Fischer_algorithm в котором мы создаем матрицу для хранения размеров префиксов и вычисляем растояние левенштайна между ними
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 O(N * M) где N это количество элементов в первой строке, а M это размер второй строки. Нам необходимо заполнить эту таблицу.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 Для решения алгоритма нужно хранить таблицу мемоизации O(N * M).
*/

int LevenshteinDistance(const std::string& source, const std::string& target) {
    std::vector<std::vector<int>> dp(source.size() + 1, std::vector<int>(target.size() + 1));
    
    // source of n char can be tranformed to empty target by deleting n elementns
    static constexpr int kTargetZeroSize = 0;
        
    for (int source_prefix_size = 1; source_prefix_size <= source.size(); ++source_prefix_size) {
        dp[source_prefix_size][kTargetZeroSize] = source_prefix_size;
    }
    
    // empty source can be transformed into target by inserting n elements
    static constexpr int kSourceZeroSize = 0;
    
    for (int target_prefix_size = 1; target_prefix_size <= target.size(); ++target_prefix_size) {
        dp[kSourceZeroSize][target_prefix_size] = target_prefix_size;
    }
    
    for (int source_prefix_size = 1; source_prefix_size <= source.size(); ++source_prefix_size) {
        for (int target_prefix_size = 1; target_prefix_size <= target.size(); ++target_prefix_size) {
            int substitution_cost = source.at(source_prefix_size - 1) == target.at(target_prefix_size - 1) ? 0 : 1;
            
            dp[source_prefix_size][target_prefix_size] = std::min({
                dp[source_prefix_size - 1][target_prefix_size] + 1,
                dp[source_prefix_size][target_prefix_size - 1] + 1,
                dp[source_prefix_size - 1][target_prefix_size - 1] + substitution_cost
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
