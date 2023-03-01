#include "../s21_vector.hpp"

#include <gtest/gtest.h>

#include <vector>

// ***** VECTOR *****

bool areVectorsEqual(std::vector<int> expected_res, s21::vector<int> actual_res) {
    bool result = true;
    if (expected_res.size() != actual_res.size()) {
        result = false;
    } else {
        for (auto i = 0; i != expected_res.size(); ++i) {
            if (expected_res.at(i) != actual_res.at(i)) {
                result = false;
                break;
            }
        }
    }

    return result;
}

TEST(tests_vector, default_constructor) {
    // arrange and act
    s21::vector<int> aboba;
    std::vector<int> buba;

    // assert
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_vector, size_constructor) {
    // arrange and act
    s21::vector<int> aboba(5);
    std::vector<int> buba(5);

    // assert
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_vector, initializer_constructor) {
    // arrange ans act
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_vector, copy_constructor) {
    // arrange and act
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    s21::vector<int> aboba_copy(aboba);
    std::vector<int> buba{1, 2, 3, 4, 5};
    std::vector<int> buba_copy(buba);

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areVectorsEqual(buba_copy, aboba_copy);
    ASSERT_TRUE(result);
}

TEST(tests_vector, move_constructor) {
    // arrange and act
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    s21::vector<int> aboba_move(std::move(aboba));
    std::vector<int> buba{1, 2, 3, 4, 5};
    std::vector<int> buba_move(std::move(buba));

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areVectorsEqual(buba_move, aboba_move);
    ASSERT_TRUE(result);
}

TEST(tests_vector, assignment_operator) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    s21::vector<int> aboba_2 = std::move(aboba);
    std::vector<int> buba_2 = std::move(buba);

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areVectorsEqual(buba_2, aboba_2);
    ASSERT_TRUE(result);
}

TEST(tests_vector, at) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act and  assert
    ASSERT_EQ(aboba.at(3), buba.at(3));
}

TEST(tests_vector, access_specified_element) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_EQ(aboba[3], buba[3]);
}

TEST(tests_vector, front) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_EQ(aboba.front(), buba.front());
}

TEST(tests_vector, back) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_EQ(aboba.back(), buba.back());
}

TEST(tests_vector, data) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    auto aboba_data = aboba.data();
    auto buba_data = buba.data();

    // assert
    ASSERT_EQ(*aboba_data, *buba_data);
}

TEST(tests_vector, begin) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    auto aboba_begin = aboba.begin();
    auto buba_begin = buba.begin();

    // assert
    ASSERT_EQ(*aboba_begin, *buba_begin);
}

TEST(tests_vector, end) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    auto aboba_end = aboba.end();
    auto buba_end = buba.end();
    --aboba_end;
    --buba_end;

    // assert
    ASSERT_EQ(*aboba_end, *buba_end);
}

TEST(tests_vector, empty) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_vector, size) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_EQ(aboba.size(), 5);
}

TEST(tests_vector, max_size) {
    s21::vector<int> aboba{0, 1, 2, 3, 4};
    std::vector<int> buba{0, 1, 2, 3, 4};
    ASSERT_EQ(aboba.max_size(), buba.max_size());
}

TEST(tests_vector, reserve) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    aboba.reserve(10);
    buba.reserve(10);

    auto expected_capacity = buba.capacity();
    auto actual_capacity = aboba.capacity();

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    ASSERT_EQ(expected_capacity, actual_capacity);
}

TEST(tests_vector, capacity) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    auto expected_capacity = buba.capacity();
    auto actual_capacity = aboba.capacity();

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    ASSERT_EQ(expected_capacity, actual_capacity);
}

TEST(tests_vector, srink_to_fit) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    aboba.reserve(10);
    buba.reserve(10);

    aboba.shrink_to_fit();
    buba.shrink_to_fit();

    auto expected_capacity = buba.capacity();
    auto actual_capacity = aboba.capacity();

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    ASSERT_EQ(expected_capacity, actual_capacity);
}

TEST(tests_vector, clear) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    aboba.clear();
    buba.clear();

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_vector, iterator) {
    // arrange
    s21::vector<int> aboba{9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<int> buba{9, 8, 7, 6, 5, 4, 3, 2};
    s21::vector<int>::iterator aboba_iter = aboba.begin();
    std::vector<int>::iterator buba_iter = buba.begin();

    // act and assert
    ASSERT_EQ(*aboba_iter, *buba_iter);
    ++aboba_iter;
    ++buba_iter;
    ASSERT_EQ(*aboba_iter, *buba_iter);
    ++aboba_iter;
    ++aboba_iter;
    ++aboba_iter;
    ++buba_iter;
    ++buba_iter;
    ++buba_iter;
    ASSERT_EQ(*aboba_iter, *buba_iter);
    --aboba_iter;
    --buba_iter;
    ASSERT_EQ(*aboba_iter, *buba_iter);
    *aboba_iter = 100;
    *buba_iter = 100;
    ASSERT_EQ(*aboba_iter, *buba_iter);
}

TEST(tests_vector, insert) {
    // arrange
    s21::vector<int> aboba{0, 1, 2, 3, 4};
    s21::vector<int>::iterator aboba_iter = aboba.begin();
    s21::vector<int>::value_type val = 100;

    std::vector<int> buba{0, 1, 2, 3, 4};
    std::vector<int>::iterator buba_iter = buba.begin();

    // act
    ++aboba_iter;
    ++aboba_iter;
    ++buba_iter;
    ++buba_iter;
    aboba_iter = aboba.insert(aboba_iter, val);
    buba_iter = buba.insert(buba_iter, val);

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    ASSERT_EQ(*aboba_iter, *buba_iter);
}

TEST(tests_vector, erase) {
    // arrange
    s21::vector<int> aboba{0, 1, 2, 3, 4};
    s21::vector<int>::iterator aboba_iter = aboba.begin();

    std::vector<int> buba{0, 1, 2, 3, 4};
    std::vector<int>::iterator buba_iter = buba.begin();

    // act
    ++aboba_iter;
    ++aboba_iter;
    ++buba_iter;
    ++buba_iter;
    aboba.erase(aboba_iter);
    buba.erase(buba_iter);

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_vector, push_back) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};
    auto push_value = 100;

    // act
    aboba.push_back(push_value);
    buba.push_back(push_value);

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_vector, pop_back) {
    // arrange
    s21::vector<int> aboba{1, 2, 3, 4, 5};
    std::vector<int> buba{1, 2, 3, 4, 5};

    // act
    aboba.pop_back();
    buba.pop_back();

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_vector, swap) {
    // arrange
    s21::vector<int> aboba{0, 1, 2, 3, 4};
    s21::vector<int> aboba_swap{5, 6, 7};
    std::vector<int> buba{0, 1, 2, 3, 4};
    std::vector<int> buba_swap{5, 6, 7};

    // act
    aboba.swap(aboba_swap);
    buba.swap(buba_swap);

    // assert
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
    result = areVectorsEqual(buba_swap, aboba_swap);
    ASSERT_TRUE(result);
}

TEST(tests_vector_bonus_suit, emplace) {
    s21::vector<int> aboba{1231, 13, 132, 124, 123423, 657, 44};
    std::vector<int> buba{1231, 7, 11, 9, 5, 13, 132, 124, 123423, 657, 44};
    s21::vector<int>::const_iterator aboba_iter = aboba.cbegin();
    ++aboba_iter;
    aboba.emplace(aboba_iter, 5, 9, 11, 7);
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}

TEST(tests_vector_bonus_suit, emplace_back) {
    s21::vector<int> aboba{1231, 13, 132, 124, 123423, 657, 44};
    std::vector<int> buba{1231, 13, 132, 124, 123423, 657, 44, 5, 9, 11, 7};

    aboba.emplace_back(5, 9, 11, 7);
    bool result = areVectorsEqual(buba, aboba);
    ASSERT_TRUE(result);
}
