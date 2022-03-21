#include <iostream>
#include <string>
#include <cmath>

bool IsMoreThanOneEditDifferent(const std::string& left, const std::string& right) {
    int size_left = static_cast<int>(left.size());
    int size_right = static_cast<int>(right.size());
    
    if (std::abs(size_left - size_right) > 1) {
        return true;
    }
    
    int edit_count{};
    
    int i = 0, j = 0;
    
    while (i < size_left && j < size_right) {
        if (left[i] != right[j]) {
            // found another diff
            if (edit_count == 1) {
                return true;
            }
            
            ++edit_count;
            
            if (size_left > size_right) {
                ++i;
            } else if (size_right > size_left) {
                ++j;
            } else {
                ++i;
                ++j;
            }
            
        } else {
            ++i;
            ++j;
        }
    }
    
    return edit_count > 1;
}

int main(int argc, const char * argv[]) {
    std::string left, right;
    
    std::cin >> left >> right;
    
    if (IsMoreThanOneEditDifferent(left, right)) {
        std::cout << "FAIL\n";
    } else {
        std::cout << "OK\n";
    }
    return 0;
}
