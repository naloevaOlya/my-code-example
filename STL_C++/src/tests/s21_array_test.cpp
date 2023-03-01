#include "../s21_array.hpp"

#include <gtest/gtest.h>

// ***** ARRAY *****

template <std::size_t SIZE>

bool areArraysEqual(std::array<int, SIZE>& expected_res, s21::array<int, SIZE>& actual_res) {
    bool result = true;
    for (size_t i = 0; i < expected_res.size(); i++) {
        if (expected_res.at(i) != actual_res.at(i)) {
            result = false;
            break;
        }
    }
    return result;
}

TEST(tests_array, default_constructor) {
    // arrange
    s21::array<int, 4> aboba;
    std::array<int, 4> buba;
    // assert
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_array, initializer_constructor) {
    // arrange
    s21::array<int, 4> aboba{1, 2, 3, 4};
    std::array<int, 4> buba{1, 2, 3, 4};
    bool result = areArraysEqual(buba, aboba);
    // assert
    ASSERT_TRUE(result);
}

TEST(tests_array, copy_constructor) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    s21::array<int, 5> aboba_copy(aboba);
    std::array<int, 5> buba = {1, 2, 3, 4, 5};
    std::array<int, 5> buba_copy = (buba);
    // act
    // assert
    bool result = areArraysEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areArraysEqual(buba_copy, aboba_copy);
    ASSERT_TRUE(result);
}

TEST(tests_array, move_constructor) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    s21::array<int, 5> aboba_move(std::move(aboba));
    std::array<int, 5> buba = {1, 2, 3, 4, 5};
    std::array<int, 5> buba_move = (std::move(buba));
    // assert
    bool result = areArraysEqual(buba_move, aboba_move);
    ASSERT_TRUE(result);
    result = areArraysEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_array, assignment_operator) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    s21::array<int, 5> aboba_src;
    aboba_src = std::move(aboba);
    std::array<int, 5> buba{1, 2, 3, 4, 5};
    std::array<int, 5> buba_src;
    buba_src = buba;
    // act and assert
    bool result = areArraysEqual(buba_src, aboba_src);
    ASSERT_TRUE(result);
    result = areArraysEqual(buba_src, aboba_src);
    ASSERT_TRUE(result);
}

TEST(tests_array, at) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = aboba.at(2);
    auto expexted_res = buba.at(2);

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_array, operator_access) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = aboba[3];
    auto expexted_res = buba[3];

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_array, front) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = aboba.front();
    auto expexted_res = buba.front();

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_array, back) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = aboba.back();
    auto expexted_res = buba.back();

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_array, data) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = *aboba.data();
    auto expexted_res = *buba.data();

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_array, begin) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = *aboba.begin();
    auto expexted_res = *buba.begin();

    // assert
    ASSERT_EQ(expexted_res, actual_res);
}

TEST(tests_array, end) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};

    // act
    auto actual_res = aboba.end();
    auto expexted_res = buba.end();
    --expexted_res;
    --actual_res;

    // assert
    ASSERT_EQ(*expexted_res, *actual_res);
}

TEST(tests_array, empty) {
    // arrange
    s21::array<int, 4> aboba;
    s21::array<int, 0> buba;

    // assert
    ASSERT_FALSE(aboba.empty());
    ASSERT_TRUE(buba.empty());
}

TEST(tests_array, size) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_TRUE(buba.size() == aboba.size());
}

TEST(tests_array, max_size) {
    // arrange
    s21::array<int, 5> aboba;
    std::array<int, 5> buba;

    // act and assert
    ASSERT_TRUE(buba.max_size() == aboba.max_size());
}

TEST(tests_array, max_size_1) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    std::array<int, 5> buba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_TRUE(buba.max_size() == aboba.max_size());
}

TEST(tests_array, swap) {
    // arrange
    s21::array<int, 5> aboba{1, 2, 3, 4, 5};
    s21::array<int, 5> aboba_swap{6, 7, 8, 9, 10};
    std::array<int, 5> buba = {1, 2, 3, 4, 5};
    std::array<int, 5> buba_swap = {6, 7, 8, 9, 10};
    // act
    aboba.swap(aboba_swap);
    buba.swap(buba_swap);

    // assert
    bool result = areArraysEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areArraysEqual(buba_swap, aboba_swap);
    ASSERT_TRUE(result);
}

TEST(tests_array, fill) {
    // arrange
    s21::array<int, 5> aboba;
    std::array<int, 5> buba;
    auto a = 5;

    // act
    aboba.fill(a);
    buba.fill(a);

    // assert
    bool result = areArraysEqual(buba, aboba);
    ASSERT_TRUE(result);
}
