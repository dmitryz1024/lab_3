#include <gtest/gtest.h>
#include "../CacheImp.h"

TEST(LRUCacheTest, BasicPutGet) {
    LRUCache<int, int> cache(2);

    cache.set(1, 10);
    cache.set(2, 20);

    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(2), 20);
    EXPECT_EQ(cache.size(), 2);
}

TEST(LRUCacheTest, EvictionWorks) {
    LRUCache<int, int> cache(2);

    cache.set(1, 10);
    cache.set(2, 20);
    cache.get(1);
    cache.set(3, 30);

    EXPECT_TRUE(cache.contains(1));
    EXPECT_FALSE(cache.contains(2));
    EXPECT_TRUE(cache.contains(3));
}

TEST(LRUCacheTest, UpdateMovesToFront) {
    LRUCache<int, int> cache(2);

    cache.set(1, 10);
    cache.set(2, 20);
    cache.set(1, 100);

    cache.set(3, 30);

    EXPECT_EQ(cache.get(1), 100);
    EXPECT_FALSE(cache.contains(2));
}

TEST(LRUCacheTest, GetMissingThrows) {
    LRUCache<int, int> cache(1);
    EXPECT_THROW(cache.get(42), std::out_of_range);
}