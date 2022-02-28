#include "ForwardList.hpp"

#include <gtest/gtest.h>
#include <vector>

std::vector<int> getVector(const ForwardList<int>& list)
{
    std::vector<int> v;
    v.reserve(list.size());
    for (const auto* current = list.head(); current; current = current->next_) {
        v.push_back(current->value_);
    }
    // const auto* current = list.head();
    // while(current) {
    // current = current->next_;
    // }
    return v;
}
class ForwardListTest : public ::testing::Test
{
   public:
    ForwardList<int> listSUT{};
};

TEST_F(ForwardListTest, WhenDefaultListIsCreated_ThenItShouldHaveSize0)
{
    EXPECT_EQ(listSUT.size(), 0);
}

TEST_F(ForwardListTest,
       GivenDefaultList_WhenValuesAreInserted_ThenListShouldHaveIncreasedSize)
{
    listSUT.insert(1);
    listSUT.insert(2);
    listSUT.insert(3);
    listSUT.insert(4);
    EXPECT_EQ(listSUT.size(), 4);
}

TEST_F(ForwardListTest,
       GivenDefaultList_WhenValueIsInserted_ThenListHeadShouldHaveGivenValue)
{
    constexpr int value = 178;
    listSUT.insert(value);
    EXPECT_EQ(listSUT.head()->value_, value);
}

TEST_F(ForwardListTest,
       GivenDefaultList_WhenMultipleValuesAreInserted_ThenListElementsShouldBeLinked)
{
    const std::vector<int> values{178, 200, 6798, -2100, 0, 231311};
    for (auto val : values) {
        listSUT.insert(val);
    }
    EXPECT_EQ(getVector(listSUT), values);
}

TEST_F(ForwardListTest,
       GivenListOfValues_WhenCopied_ThenCopyContainsTheSameValuesButDifferentAddresses)
{
    const std::vector<int> values{178, 200, 6798, -2100, 0, 231311};
    for (auto val : values) {
        listSUT.insert(val);
    }
    ForwardList<int> copy = listSUT;
    EXPECT_EQ(getVector(copy), values);
    EXPECT_NE(listSUT.head(), copy.head());
}

class ForwardListReverseTest :
  public ::testing::TestWithParam<std::pair<std::vector<int>, std::vector<int>>>
{
   public:
    ForwardList<int> listSUT{};
};

TEST_P(ForwardListReverseTest,
       GivenListOfValues_WhenReverseCalled_ThenListShouldHaveValuesInReverseOrder)
{
   const auto& [values, expectedReversedValues] = GetParam();
    for (auto val : values) {
        listSUT.insert(val);
    }
    listSUT.reverse();
    EXPECT_EQ(getVector(listSUT), expectedReversedValues);
}

INSTANTIATE_TEST_CASE_P(
    ReverseTestWithManyValues,
    ForwardListReverseTest,
    ::testing::Values(
        std::make_pair(std::vector<int>{1, 2, 3, 4, 5}, std::vector<int>{5, 4, 3, 2, 1}),
        std::make_pair(std::vector<int>{7, -21, 0, 245, 100}, std::vector<int>{100, 245, 0, -21, 7}),
        std::make_pair(std::vector<int>{1}, std::vector<int>{1}),
        std::make_pair(std::vector<int>{1, 2}, std::vector<int>{2, 1}),
        std::make_pair(std::vector<int>{-1, -2, -3}, std::vector<int>{-3, -2, -1})));
