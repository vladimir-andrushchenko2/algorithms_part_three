#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

std::pair<std::vector<int>, std::vector<int>> ReadInput(std::istream& input_stream) {
    int size_of_first_vector;
    
    input_stream >> size_of_first_vector;
    
    std::vector<int> first_vector;
    
    for (int i = 0; i < size_of_first_vector; ++i) {
        input_stream >> first_vector.emplace_back();
    }
    
    int size_of_second_vector;
    
    input_stream >> size_of_second_vector;
    
    std::vector<int> second_vector;
    
    for (int i = 0; i < size_of_second_vector; ++i) {
        input_stream >> second_vector.emplace_back();
    }
    
    return {std::move(first_vector), std::move(second_vector)};
}

int main(int argc, const char * argv[]) {
    auto [first_vector, second_vector] = ReadInput(std::cin);
    
    std::vector<std::vector<int>> dp(first_vector.size() + 1, std::vector<int>(second_vector.size() + 1));
    
    for (int first_vector_size = 1; first_vector_size <= first_vector.size(); ++first_vector_size) {
        for (int second_vector_size = 1; second_vector_size <= second_vector.size(); ++second_vector_size) {
            if (first_vector[first_vector_size - 1] == second_vector[second_vector_size - 1]) {
                dp[first_vector_size][second_vector_size] = dp[first_vector_size - 1][second_vector_size - 1] + 1;
            } else {
                dp[first_vector_size][second_vector_size] = std::max(dp[first_vector_size - 1][second_vector_size], dp[first_vector_size][second_vector_size - 1]);
            }
        }
    }
    
    return 0;
}
