#include "BST.hpp"

#include "gtest/gtest.h"

class BSTTest : public ::testing::Test
{
   protected:
    BST<int> bst;
};

TEST_F(BSTTest, WhenBSTCreated_ThenRootShouldBeNullptr)
{
    ASSERT_EQ(bst.root(), nullptr);
}

TEST_F(BSTTest, WhenBSTCreated_ThenSizeShouldBe0)
{
    ASSERT_EQ(bst.getSize(), 0);
}

TEST_F(BSTTest, WhenBSTCreated_ThenGetHeightShouldBe0)
{
    ASSERT_EQ(bst.getHeight(), 0);
}

TEST_F(BSTTest, WhenBSTCreated_ThenGetDepthShouldBe0)
{
    ASSERT_EQ(bst.getDepth(bst.root()), 0);
}

