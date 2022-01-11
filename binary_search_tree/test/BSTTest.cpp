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
    ASSERT_EQ(bst.countHeight(), 0);
}

TEST_F(BSTTest, WhenBSTCreated_ThenGetDepthShouldBe0)
{
    ASSERT_EQ(bst.getDepth(bst.root()), 0);
}

TEST_F(BSTTest, WhenBSTCreated_ThenFindNodeShouldThrowNoElementError)
{
    ASSERT_THROW(bst.findNode(1), NoElementError);
}

TEST_F(BSTTest, WhenValueInserted_ThenGetSizeShouldBe1)
{
    bst.insert(5);
    ASSERT_EQ(bst.getSize(), 1);
}

TEST_F(BSTTest, WhenDuplicateValuesInserted_ThenDoNotAddDuplicates)
{
    bst.insert(5);
    bst.insert(5);
    bst.insert(5);

    ASSERT_EQ(bst.getSize(), 1);
    ASSERT_TRUE(bst.root()->isLeaf());
}

TEST_F(BSTTest, WhenMultipleValuesInserted_ThenGetSizeReturnsNumberOfInsertedValues)
{
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);

    ASSERT_EQ(bst.getSize(), 3);
}

class BSTHeightTest : public ::testing::TestWithParam<std::pair<std::vector<int>, int>>
{
   protected:
    BST<int> bst;
};

TEST_P(BSTHeightTest, TestingGetHeightWithMultipleValues)
{
    const auto& [values, expectedHeight] = GetParam();
    for (const int val : values) {
        bst.insert(val);
    }

    ASSERT_EQ(bst.countHeight(), expectedHeight);
}

INSTANTIATE_TEST_CASE_P(BSTHeightTests,
                        BSTHeightTest,
                        testing::Values(std::make_pair(std::vector<int>{1, 2, 3, 4}, 4),
                                        std::make_pair(std::vector<int>{4, 2, 5}, 2),
                                        std::make_pair(std::vector<int>{5, 2, 3, 4, 1},
                                                       4)));

class BSTFindNodeTest : public ::testing::TestWithParam<std::pair<std::vector<int>, int>>
{
   protected:
    BST<int> bst;
};

TEST_P(BSTFindNodeTest, TestingFindNodeWithMultipleValues)
{
    const auto& [values, valueToBeFound] = GetParam();
    for (const int val : values) {
        bst.insert(val);
    }

    const auto node = bst.findNode(valueToBeFound);
    ASSERT_TRUE(node);
    ASSERT_EQ(node->value_, valueToBeFound);
}

INSTANTIATE_TEST_CASE_P(BSTFindNodeTests,
                        BSTFindNodeTest,
                        testing::Values(std::make_pair(std::vector<int>{1, 2, 3, 4}, 3),
                                        std::make_pair(std::vector<int>{4, 2, 5}, 2),
                                        std::make_pair(std::vector<int>{5, 2, 3, 4, 1},
                                                       5)));

TEST_F(BSTTest, WhenNoElementWithGivenValue_ThenFindNodeThrowNoElementError) {
    bst.insert(10);

    ASSERT_THROW(bst.findNode(1), NoElementError);
    ASSERT_THROW(bst.findNode(3), NoElementError);
    ASSERT_THROW(bst.findNode(8), NoElementError);
}
