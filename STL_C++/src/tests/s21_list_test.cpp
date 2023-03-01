#include "../s21_list.hpp"

#include <gtest/gtest.h>

#include <list>

bool areListsEqual(std::list<int> &expected_res, s21::list<int> &actual_res) {
    bool result = true;
    if (expected_res.size() != actual_res.size()) {
        result = false;
    } else {
        std::list<int>::iterator i = expected_res.begin();
        s21::list<int>::iterator j = actual_res.begin();
        for (i, j; i != expected_res.end(); ++i, ++j) {
            if (*i != *j) {
                result = false;
                break;
            }
        }
    }

    return result;
}

//  ***** LIST *****

TEST(tests_list, default_constructor) {
    // arrange
    s21::list<int> aboba;
    std::list<int> buba;

    // act and assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, size_constructor) {
    // arrange
    s21::list<int> aboba(3);
    std::list<int> buba(3);

    // act and assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, init_constructor) {
    // arrange
    s21::list<int> aboba{1, 2, 3, 4, 5, 6};
    std::list<int> buba{1, 2, 3, 4, 5, 6};

    // act and assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, copy_constructor) {
    // arrange
    s21::list<int> aboba{1, 2, 3, 4, 5, 6};
    s21::list<int> aboba_copy(aboba);
    std::list<int> buba{1, 2, 3, 4, 5, 6};
    std::list<int> buba_copy(buba);

    // act and assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areListsEqual(buba_copy, aboba_copy);
    ASSERT_TRUE(result);
}

TEST(tests_list, move_constructor) {
    // arrange
    s21::list<int> aboba{1, 2, 3, 4, 5, 6};
    s21::list<int> aboba_move(std::move(aboba));
    std::list<int> buba{1, 2, 3, 4, 5, 6};
    std::list<int> buba_move(buba);

    // act and assert
    bool result = areListsEqual(buba_move, aboba_move);
    ASSERT_TRUE(result);
}

TEST(tests_list, front_back) {
    // arrange
    s21::list<int> aboba{12, 3, -100, 1};
    std::list<int> buba{12, 3, -100, 1};

    // act and assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
    auto expected_res_front = buba.front();
    auto expected_res_back = buba.back();
    auto actual_res_front = aboba.front();
    auto actual_res_back = aboba.back();
    ASSERT_EQ(expected_res_front, actual_res_front);
    ASSERT_EQ(expected_res_back, actual_res_back);
}
TEST(tests_list, begin) {
    // arrange
    s21::list<int> aboba{12, 3, -100, 1};
    std::list<int> buba{12, 3, -100, 1};

    // act
    auto actual_res = *aboba.begin();
    auto expexted_res = *buba.begin();

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_list, end) {
    // arrange
    s21::list<int> aboba{12, 3, -100, 1};
    std::list<int> buba{12, 3, -100, 1};

    // act
    auto actual_res = aboba.end();
    auto expexted_res = buba.end();
    --expexted_res;
    --actual_res;

    // assert
    ASSERT_EQ(*expexted_res, *actual_res);
}

TEST(tests_list, empty) {
    // arrange
    s21::list<int> aboba{};
    std::list<int> buba{};

    // act and assert
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_list, size) {
    // arrange
    s21::list<int> aboba{12, 3, -100, 1};
    std::list<int> buba{12, 3, -100, 1};

    // act and assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(buba.size() == aboba.size());
    ASSERT_TRUE(result);
}

TEST(tests_list, max_size) {
    // arrange
    s21::list<int> aboba;
    std::list<int> buba;

    // act
    s21::list<int>::size_type actual_max = aboba.max_size();
    std::list<int>::size_type expected_max = buba.max_size();

    // assert
    ASSERT_EQ(expected_max, actual_max);
}

TEST(tests_list, clear) {
    // arrange
    s21::list<int> aboba{1, 2, 3, 4};
    std::list<int> buba{1, 2, 3, 4};

    // act
    aboba.clear();
    buba.clear();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, insert) {
    // arrange
    s21::list<int> aboba{2, 3, 4, 5, 6};
    std::list<int> buba{2, 3, 4, 5, 6};
    auto val = 10000;

    // act
    s21::list<int>::iterator iter = aboba.begin();
    iter = aboba.insert(iter, val);
    ++iter;
    ++iter;
    ++iter;
    iter = aboba.insert(iter, val);
    ++iter;
    ++iter;
    ++iter;
    iter = aboba.insert(iter, val);

    std::list<int>::iterator iter_2 = buba.begin();
    iter_2 = buba.insert(iter_2, val);
    ++iter_2;
    ++iter_2;
    ++iter_2;
    iter_2 = buba.insert(iter_2, val);
    ++iter_2;
    ++iter_2;
    ++iter_2;
    iter_2 = buba.insert(iter_2, val);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, erase) {
    // arrange
    std::list<int> buba{100, 200, 324, 33, 44, 53};
    s21::list<int> aboba{100, 200, 324, 33, 44, 53};

    // act
    s21::list<int>::iterator aboba_iter = aboba.begin();
    std::list<int>::iterator buba_iter = buba.begin();
    aboba.erase(aboba_iter);
    buba.erase(buba_iter);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, erase_2) {
    // arrange
    std::list<int> buba{100, 200, 324, 33, 44, 53};
    s21::list<int> aboba{100, 200, 324, 33, 44, 53};

    // act
    s21::list<int>::iterator aboba_iter = aboba.begin();
    std::list<int>::iterator buba_iter = buba.begin();
    ++aboba_iter;
    ++aboba_iter;
    ++buba_iter;
    ++buba_iter;

    aboba.erase(aboba_iter);
    buba.erase(buba_iter);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, erase_3) {
    // arrange
    std::list<int> buba{100, 200, 324, 33, 44, 53};
    s21::list<int> aboba{100, 200, 324, 33, 44, 53};

    // act
    s21::list<int>::iterator aboba_iter = aboba.end();
    std::list<int>::iterator buba_iter = buba.end();
    --aboba_iter;
    --buba_iter;
    aboba.erase(aboba_iter);
    buba.erase(buba_iter);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, push_back) {
    // arrange
    s21::list<int> aboba;
    std::list<int> buba;
    auto a = 1;
    auto b = 2;
    auto c = 3;
    auto d = 4;

    // act
    aboba.push_back(a);
    aboba.push_back(b);
    aboba.push_back(c);
    aboba.push_back(d);
    buba.push_back(a);
    buba.push_back(b);
    buba.push_back(c);
    buba.push_back(d);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, push_front) {
    // arrange
    s21::list<int> aboba;
    std::list<int> buba;
    auto a = 1;
    auto b = 2;
    auto c = 3;
    auto d = 4;

    // act
    aboba.push_front(a);
    aboba.push_front(b);
    aboba.push_front(c);
    aboba.push_front(d);
    buba.push_front(a);
    buba.push_front(b);
    buba.push_front(c);
    buba.push_front(d);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, pop_back) {
    // arrange
    s21::list<int> aboba{12, 3, -100, 1};
    std::list<int> buba{12, 3, -100, 1};

    // act
    aboba.pop_back();
    buba.pop_back();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, pop_front) {
    // arrange
    s21::list<int> aboba{12, 3, -100, 1};
    std::list<int> buba{12, 3, -100, 1};

    // act
    aboba.pop_front();
    buba.pop_front();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, swap) {
    // arrange
    s21::list<int> aboba{1, 2, 3, 4, 5, 6};
    s21::list<int> aboba_swap{1231, 13, 132, 124, 123423, 657, 44};
    std::list<int> buba{1, 2, 3, 4, 5, 6};
    std::list<int> buba_swap{1231, 13, 132, 124, 123423, 657, 44};

    // act
    aboba.swap(aboba_swap);
    buba.swap(buba_swap);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areListsEqual(buba_swap, aboba_swap);
    ASSERT_TRUE(result);
}

TEST(tests_list, merge) {
    // arrange
    s21::list<int> aboba{1, 2};
    s21::list<int> aboba_megre{100, 200, 324, 33, 44, 53};

    std::list<int> buba{1, 2};
    std::list<int> buba_megre{100, 200, 324, 33, 44, 53};

    // act
    aboba.sort();
    buba.sort();
    aboba.merge(aboba_megre);
    buba.merge(buba_megre);

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
    ASSERT_TRUE(aboba_megre.empty());
}

TEST(tests_list, splice) {
    // arrange
    s21::list<int> aboba{1, 2, 3};
    s21::list<int> aboba_splice{1231, 13, 132, 124};
    std::list<int> buba{1, 2, 3};
    std::list<int> buba_splice{1231, 13, 132, 124};
    // act
    s21::list<int>::const_iterator aboba_iter = aboba.cbegin();
    ++aboba_iter;
    ++aboba_iter;
    std::list<int>::const_iterator buba_iter = buba.cbegin();
    ++buba_iter;
    ++buba_iter;
    aboba.splice(aboba_iter, aboba_splice);
    buba.splice(buba_iter, buba_splice);
    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
    ASSERT_EQ(buba_splice.empty(), aboba_splice.empty());
}

TEST(tests_list, reverse) {
    // arrange
    std::list<int> buba{100, 200, 324, 33, 44, 53};
    s21::list<int> aboba{100, 200, 324, 33, 44, 53};

    // act
    aboba.reverse();
    buba.reverse();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, unique) {
    // arrange
    std::list<int> buba{1, 1, 1, 2, 324, 33, 44, 53};
    s21::list<int> aboba{1, 1, 1, 2, 324, 33, 44, 53};

    // act
    aboba.unique();
    buba.unique();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, unique_2) {
    // arrange
    std::list<int> buba{100, 200, 324, 33, 44, 53, 100, 100};
    s21::list<int> aboba{100, 200, 324, 33, 44, 53, 100, 100};

    // act
    aboba.unique();
    buba.unique();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, unique_3) {
    // arrange
    std::list<int> buba{100, 200, 324, 33, 33, 33, 33, 44, 53, 44, 100, 100};
    s21::list<int> aboba{100, 200, 324, 33, 33, 33, 33, 44, 53, 44, 100, 100};

    // act
    aboba.unique();
    buba.unique();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_list, sort) {
    // arrange
    s21::list<int> aboba{22, 123, 4, 3445, 56};
    std::list<int> buba{22, 123, 4, 3445, 56};

    // act
    aboba.sort();
    buba.sort();

    // assert
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(bonus_suit, emplace) {
    s21::list<int> aboba{1231, 13, 132, 124, 123423, 657, 44};
    std::list<int> buba{1231, 7, 11, 9, 5, 13, 132, 124, 123423, 657, 44};
    s21::list<int>::const_iterator aboba_iter = aboba.cbegin();
    ++aboba_iter;
    aboba.emplace(aboba_iter, 5, 9, 11, 7);
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(bonus_suit, emplace_back) {
    s21::list<int> aboba{1231, 13, 132, 124, 123423, 657, 44};
    std::list<int> buba{1231, 13, 132, 124, 123423, 657, 44, 5, 9, 11, 7};

    aboba.emplace_back(5, 9, 11, 7);
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(bonus_suit, emplace_front) {
    s21::list<int> aboba{1231, 13, 132, 124, 123423, 657, 44};
    std::list<int> buba{7, 11, 9, 5, 1231, 13, 132, 124, 123423, 657, 44};

    aboba.emplace_front(5, 9, 11, 7);
    bool result = areListsEqual(buba, aboba);
    ASSERT_TRUE(result);
}
