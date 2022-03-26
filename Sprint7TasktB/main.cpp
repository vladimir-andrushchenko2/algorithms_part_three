#include <iostream>
#include <vector>
#include <ios>
#include <numeric>
#include <string>

using namespace std::string_literals;

bool IsEven(int number) {
    return number % 2 == 0;
}

bool IsSubsetSum(const std::vector<int> set, int target_sum) {
    std::vector<std::vector<bool>> dp(set.size() + 1, std::vector<bool>(target_sum + 1));
    
    for (int subset_size = 0; subset_size < dp.size(); ++subset_size) {
        static constexpr int target_sum_of_zero = 0;
        
        dp[subset_size][target_sum_of_zero] = true;
    }
    
    // start loop when subset size is 2
    for (int subset_size = 1; subset_size <= set.size(); ++subset_size) {
        for (int current_sum = 1; current_sum <= target_sum; ++current_sum) {
            if (set[subset_size - 1] > current_sum) {
                dp[subset_size][current_sum] = dp[subset_size - 1][current_sum];
            } else {
                int remainder = current_sum - set[subset_size - 1];
                dp[subset_size][current_sum] = dp[subset_size - 1][remainder] || dp[subset_size - 1][current_sum];
            }
        }
    }
    
    return dp.back().back();
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
