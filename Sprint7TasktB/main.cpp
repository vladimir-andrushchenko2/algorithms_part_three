#include <iostream>
#include <vector>
#include <ios>
#include <numeric>
#include <string>

/*
-- ПРИНЦИП РАБОТЫ --
 Eсли сумма чисел не четная тогда ее нельзя разложить на 2 равные части и если в подмножестве содержатся элементы из которых можно сложить половину суммы всех элементов значит элементы не включенные в это множество будут образовывать другую половину. Нужно найти если из элементов множества можно собрать половину суммы. Используем алгоритм похожий на алгоритм собирания рюкзака. Где будем последовательно увеличивать искомую сумму пока она не станет равна требуемой и будем увеличивать количество элементов пока оно не будет включать в себя все элементы множества.
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 O(N * M) где N это количество элементов, а M это половина искомой суммы. Нам необходимо посчитать все значения таблицы мемоизации N * M.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 Для решения алгоритма нужно хранить таблицу мемоизации O(N * M).
*/

using namespace std::string_literals;

bool IsEven(int number) {
    return number % 2 == 0;
}

bool IsSubsetSum(const std::vector<int>& elements, int target_sum) {
    std::vector<std::vector<bool>> subset_size_to_sums(elements.size() + 1, std::vector<bool>(target_sum + 1));
    
    // it is possible to reach target sum of zero by taking zero elements
    for (int subset_size = 0; subset_size < subset_size_to_sums.size(); ++subset_size) {
        static constexpr int target_sum_of_zero = 0;
        
        subset_size_to_sums[subset_size][target_sum_of_zero] = true;
    }
    
    for (int n_elements = 1; n_elements <= elements.size(); ++n_elements) {
        for (int current_sum = 1; current_sum <= target_sum; ++current_sum) {
            bool is_subset_sum_without_current_element = subset_size_to_sums[n_elements - 1][current_sum];
            
            int current_element = elements[n_elements - 1];
            
            if (current_element > current_sum) {
                subset_size_to_sums[n_elements][current_sum] = is_subset_sum_without_current_element;
                
            } else {
                int remainder = current_sum - current_element;
                
                bool is_subset_sum_with_currrent_element = subset_size_to_sums[n_elements - 1][remainder];
                
                subset_size_to_sums[n_elements][current_sum] = is_subset_sum_with_currrent_element || is_subset_sum_without_current_element;
            }
        }
    }
    
    return subset_size_to_sums.back().back();
}

int main(int argc, const char * argv[]) {
    int n;
    
    std::cin >> n;
    
    std::vector<int> set(n);
    
    for (int i = 0; i < set.size(); ++i) {
        std::cin >> set[i];
    }
    
    int sum = std::accumulate(set.begin(), set.end(), 0);
    
    
    if (IsEven(sum)) {
        std::cout << (IsSubsetSum(set, sum / 2) ? "True"s : "False"s);
    } else {
        std::cout << "False"s;
    }
    
    std::cout << '\n';
    
    return 0;
}
