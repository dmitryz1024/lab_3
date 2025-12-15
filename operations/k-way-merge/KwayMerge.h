#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <cstddef>

template<typename T>
std::vector<T> KwayMergeSort(const std::vector<T>& array,
                            std::size_t k = 4,
                            std::size_t block_size = 8)
{
    if (array.empty()) {
        return {};
    }

    std::vector<std::vector<T>> blocks;
    for (std::size_t i = 0; i < array.size(); i += block_size) {
        std::vector<T> block(
            array.begin() + i,
            array.begin() + std::min(i + block_size, array.size())
        );
        std::sort(block.begin(), block.end());
        blocks.push_back(std::move(block));
    }

    while (blocks.size() > 1) {
        std::vector<std::vector<T>> next_level;

        for (std::size_t i = 0; i < blocks.size(); i += k) {
            std::size_t end = std::min(i + k, blocks.size());

            struct Node {
                T value;
                std::size_t block_idx;
                std::size_t elem_idx;

                bool operator>(const Node& other) const {
                    return value > other.value;
                }
            };

            std::priority_queue<Node, std::vector<Node>, std::greater<Node>> heap;

            for (std::size_t j = i; j < end; ++j) {
                if (!blocks[j].empty()) {
                    heap.push({blocks[j][0], j - i, 0});
                }
            }

            std::vector<std::vector<T>> current(
                blocks.begin() + i,
                blocks.begin() + end
            );

            std::vector<T> merged;
            while (!heap.empty()) {
                Node n = heap.top();
                heap.pop();
                merged.push_back(n.value);

                std::size_t next = n.elem_idx + 1;
                if (next < current[n.block_idx].size()) {
                    heap.push({
                        current[n.block_idx][next],
                        n.block_idx,
                        next
                    });
                }
            }
            next_level.push_back(std::move(merged));
        }
        blocks = std::move(next_level);
    }
    return blocks.front();
}