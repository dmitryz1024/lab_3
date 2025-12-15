#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../KwayMerge.h"

TEST(KWayMergeTest, EmptyArray) {
    std::vector<int> v;
    auto res = KwayMergeSort(v);
    EXPECT_TRUE(res.empty());
}

TEST(KWayMergeTest, AlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto res = KwayMergeSort(v);
    EXPECT_EQ(res, v);
}

TEST(KWayMergeTest, ReverseSorted) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    auto res = KwayMergeSort(v);

    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(res, expected);
}

TEST(KWayMergeTest, RandomData) {
    std::vector<int> v = {7, 2, 9, 1, 5, 3, 8, 4, 6};
    auto res = KwayMergeSort(v, 3, 3);

    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(res, expected);
}

TEST(KWayMergeTest, WithDuplicates) {
    std::vector<int> v = {5, 1, 3, 5, 2, 1, 4};
    auto res = KwayMergeSort(v);

    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(res, expected);
}