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

    struct Node {
        T value;
        std::size_t block_idx;
        std::size_t elem_idx;

        bool operator>(const Node& other) const {
            return value > other.value;
        }
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> heap;

    for (std::size_t i = 0; i < blocks.size(); ++i) {
        if (!blocks[i].empty()) {
            heap.push({blocks[i][0], i, 0});
        }
    }

    std::vector<T> result;
    result.reserve(array.size());

    while (!heap.empty()) {
        Node node = heap.top();
        heap.pop();

        result.push_back(node.value);

        std::size_t next_idx = node.elem_idx + 1;
        if (next_idx < blocks[node.block_idx].size()) {
            heap.push({
                blocks[node.block_idx][next_idx],
                node.block_idx,
                next_idx
            });
        }
    }

    return result;
}