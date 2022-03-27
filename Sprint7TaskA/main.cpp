// 66488008
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>

/*
-- ПРИНЦИП РАБОТЫ --
Источником вдохновения послужил https://en.wikipedia.org/wiki/Levenshtein_distance в котором используется только две строки матицы
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 O(N * M) где N это количество элементов в первой строке, а M это размер второй строки. Нам необходимо заполнить эту таблицу.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 Для решения алгоритма нужно хранить 2 строки длинны M и таким образом пространственная сложность O(M).
*/

int LevenshteinDistance(const std::string& source, const std::string& target) {
    std::vector<int> previous_column(target.size() + 1);
    std::vector<int> current_column(target.size() + 1);
    
    std::iota(previous_column.begin(), previous_column.end(), 0);
    
    for (int i = 0; i < source.size(); ++i) {
        current_column.front() = i + 1;
        
        for (int j = 0; j < target.size(); ++j) {
            int deletion_cost = previous_column[j + 1] + 1;
            
            int insertion_cost = current_column[j] + 1;
            
            int substitution_cost = source[i] == target[j] ? previous_column[j] : previous_column[j] + 1;
            
            current_column[j + 1] = std::min({deletion_cost, insertion_cost, substitution_cost});
        }
        
        std::swap(current_column, previous_column);
    }
    
    return previous_column.back();
}

int main(int argc, const char * argv[]) {
    std::string source, target;
    
    std::getline(std::cin, source);
    std::getline(std::cin, target);
    
    std::cout << LevenshteinDistance(source, target) << '\n';
    return 0;
    
}
