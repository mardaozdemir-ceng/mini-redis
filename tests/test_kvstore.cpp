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