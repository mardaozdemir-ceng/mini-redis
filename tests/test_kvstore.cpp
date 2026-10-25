#include <gtest/gtest.h>
#include "kvstore.hpp"

TEST(KVStoreTest, SetAndGetBasic) {
    KVStore store;
    store.set("key","value");

    auto val = store.get("key");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(),"value");
}

TEST(KVStoreTest, GetNonExistentKeyReturnsNullopt) {
    KVStore store;
    auto val = store.get("olmayan_anahtar");
    EXPECT_FALSE(val.has_value());
}

TEST(KVStoreTest, OverwriteExistingKey) {
    KVStore store;
    store.set("KEY", "VALUE1");
    store.set("KEY", "VALUE2");

    auto val = store.get("KEY");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "VALUE2");
}

TEST(KVStoreTest, DeleteKeyProperly) {
    KVStore store;
    store.set("KEY", "VALUE");

    EXPECT_TRUE(store.del("KEY"));

    EXPECT_FALSE(store.get("KEY").has_value());

    EXPECT_FALSE(store.del("KEY"));
}

TEST(KVStoreTest, KeyExpiresAfterTTL) {
    KVStore store;
    store.set("temp", "data", 1);

    auto val1 = store.get("temp");
    ASSERT_TRUE(val1.has_value());
    EXPECT_EQ(val1.value(), "data");

    std::this_thread::sleep_for(std::chrono::milliseconds(1100));

    auto val2 = store.get("temp");
    EXPECT_FALSE(val2.has_value());
}

TEST(KVStoreTest, ExpireCommandWorks) {
    KVStore store;
    store.set("perma", "123");

    EXPECT_EQ(store.ttl("perma").value_or(-2), -1);

    EXPECT_TRUE(store.expire("perma", 2));
    EXPECT_GT(store.ttl("perma").value_or(0), 0);
}