#include <iostream>
#include <vector>

int main(int argc, const char * argv[]) {
    int gold_chunks, capacity;

    std::cin >> gold_chunks >> capacity;

    std::vector<int> chunks;

    for (int i = 0; i < gold_chunks; ++i) {
        int chunk;

        std::cin >> chunk;

        chunks.push_back(chunk);
    }

    std::vector<std::vector<int>> dp(gold_chunks, std::vector<int>(capacity));

    constexpr int first_chunk_id = 0;

    // fill first row
    for (int current_weight = 0; current_weight < capacity; ++current_weight) {
        if (chunks[first_chunk_id] <= current_weight) {
            dp[first_chunk_id][current_weight] = chunks[first_chunk_id];
        }
    }


    // fill remaining rows
    for (int chunk_id = 1; chunk_id < gold_chunks; ++chunk_id) {
        for (int weight = 0; weight < capacity; ++weight) {
            int remaining_capacity = weight - chunks[chunk_id];

            if (remaining_capacity > 0) {

            }
        }
    }

    return 0;
}
