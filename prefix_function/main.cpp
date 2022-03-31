#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunction(const std::string& data) {
    std::vector<int> dp(data.size());
    
    for (int i = 1; i < data.size(); ++i) {
        int k = dp[i - 1];
        
        while (k > 0 && data[k] != data[i]) {
            k = dp[k - 1];
        }
        
        if (data[k] == data[i]) {
            ++k;
        }
        
        dp[i] = k;
    }
    
    return dp;
}

int main(int argc, const char * argv[]) {
    std::string data;
    
    std::getline(std::cin, data);
    
    for (auto i : PrefixFunction(data)) {
        std::cout << i << ' ';
    }
    
    std::cout << '\n';
    return 0;
}
