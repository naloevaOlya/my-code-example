#include "../s21_multiset.hpp"

#include <gtest/gtest.h>
#include <math.h>

#define initializeMultiset                                                                                \
    1000, 500, 2000, 250, 750, 1500, 3000, 125, 312, 625, 850, 1250, 1750, 2500, 4000, 75, 200, 275, 400, \
        610, 900

#define initializeMultiset_2 50, 50, 50, 100, 50, 100, 100, 30, 25, 5, 4, 3

#define initializeMultiset_3 50, 2, 100000, 50

bool isMultisetEqual(std::multiset<int> *expected_res, s21::multiset<int> *actual_res) {
    bool testResult{true};
    auto expected_iter = expected_res->begin();
    auto actual_iter = actual_res->begin();

    auto actual_size = actual_res->size();
    auto expected_size = expected_res->size();

    if (actual_size == expected_size) {
        while (expected_iter != expected_res->end()) {
            int actual_first = *actual_iter;
            int expected_first = *expected_iter;

            if (actual_first != expected_first) {
                testResult = false;
                break;
            }
            ++actual_iter;
            ++expected_iter;
        }
    } else {
        testResult = false;
    }
    return testResult;
}

TEST(tests_multiset, default_constructor) {
    // arrange
    s21::multiset<int> aboba;
    std::multiset<int> buba;

    // act and assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, initializer_constructor_1) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act and assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, initializer_constructor_2) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, copy_constructor) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    s21::multiset<int> aboba_copy(aboba);
    std::multiset<int> buba{initializeMultiset_2};
    std::multiset<int> buba_copy(buba);

    // act and assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    result = isMultisetEqual(&buba_copy, &aboba_copy);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, move_constructor) {
    // arrange
    s21::multiset<int> aboba_src{initializeMultiset_2};
    std::multiset<int> buba_src{initializeMultiset_2};

    // act
    s21::multiset<int> aboba(std::move(aboba_src));
    std::multiset<int> buba(std::move(buba_src));

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, assignment_operator) {
    // arrange
    s21::multiset<int> aboba_src{initializeMultiset_2};
    s21::multiset<int> aboba;
    std::multiset<int> buba_src{initializeMultiset_2};
    std::multiset<int> buba;

    // act
    aboba = std::move(aboba_src);
    buba = buba_src;

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, begin) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_EQ((*aboba.begin()), (*buba.begin()));
    ASSERT_EQ((*aboba.begin()), (*buba.begin()));
}

TEST(tests_multiset, end) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_EQ((*(--aboba.end())), (*(--buba.end())));
    ASSERT_EQ((*(--aboba.end())), (*(--buba.end())));
}

TEST(tests_multiset, empty) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};
    s21::multiset<int> aboba_2;
    std::multiset<int> buba_2;

    // act and assert
    ASSERT_EQ(aboba.empty(), buba.empty());
    ASSERT_EQ(aboba_2.empty(), buba_2.empty());
}

TEST(tests_multiset, size) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act and assert
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_multiset, max_size) {
    // arrange
    s21::multiset<int> aboba;
    std::multiset<int> buba;

    // act and assert
    ASSERT_EQ(aboba.max_size(), buba.max_size());
}

TEST(tests_multiset, clear) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act
    aboba.clear();
    buba.clear();

    // assert
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_multiset, insert_1) {
    // arrange
    s21::multiset<int> aboba;
    std::multiset<int> buba;

    // act
    s21::BST<int>::iterator ret_actual_pair = aboba.insert(70);
    std::multiset<int>::iterator ret_expected_pair = buba.insert(70);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, insert_2) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act
    s21::BST<int>::iterator ret_actual_pair = aboba.insert(4);
    std::multiset<int>::iterator ret_expected_pair = buba.insert(4);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, insert_3) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act

    s21::BST<int>::iterator ret_actual_pair = aboba.insert(3);
    std::multiset<int>::iterator ret_expected_pair = buba.insert(3);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, insert_4) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act

    s21::BST<int>::iterator ret_actual_pair = aboba.insert(50);
    std::multiset<int>::iterator ret_expected_pair = buba.insert(50);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, erase_1) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act
    aboba.erase(aboba.begin());
    buba.erase(buba.begin());

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, erase_2) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act
    auto actualIter = --aboba.end();
    auto expectedIter = --buba.end();
    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, erase_3) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act

    auto actualIter = aboba.begin();
    auto expectedIter = buba.begin();

    for (size_t i = 0; i < 10; i++) {
        ++actualIter;
        ++expectedIter;
    }

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, erase_4) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act

    auto actualIter_one = aboba.begin();
    auto expectedIter_one = buba.begin();

    for (size_t i = 0; i < 5; i++) {
        ++actualIter_one;
        ++expectedIter_one;
    }

    aboba.erase(actualIter_one);
    buba.erase(expectedIter_one);

    auto actualIter_two = aboba.begin();
    auto expectedIter_two = buba.begin();

    for (size_t i = 0; i < 6; i++) {
        ++actualIter_two;
        ++expectedIter_two;
    }

    aboba.erase(actualIter_two);
    buba.erase(expectedIter_two);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, erase_5) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset};
    std::multiset<int> buba{initializeMultiset};

    // act

    auto actualIter = aboba.begin();
    auto expectedIter = buba.begin();

    for (size_t i = 0; i < 12; i++) {
        ++actualIter;
        ++expectedIter;
    }

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, erase_6) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act

    auto actualIter = aboba.begin();
    auto expectedIter = buba.begin();
    ++actualIter;
    ++expectedIter;
    ++actualIter;
    ++expectedIter;

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, swap) {
    // arrange
    s21::multiset<int> aboba_src{initializeMultiset_2};
    s21::multiset<int> aboba;
    std::multiset<int> buba_src{initializeMultiset_2};
    std::multiset<int> buba;

    // act
    aboba.swap(aboba_src);
    buba = buba_src;

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, merge_1) {
    // arrange
    s21::multiset<int> aboba_src{initializeMultiset};
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba_src{initializeMultiset};
    std::multiset<int> buba{initializeMultiset_2};

    // act
    aboba.merge(aboba_src);
    buba.merge(buba_src);

    // assert
    bool result = isMultisetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    result = isMultisetEqual(&buba_src, &aboba_src);
    ASSERT_TRUE(result);
}

TEST(tests_multiset, count) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_EQ(aboba.count(50), buba.count(50));
    ASSERT_EQ(aboba.count(200), buba.count(200));
}

TEST(tests_multiset, find_1) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_TRUE(aboba.find(1453) == aboba.find(1453));
}

TEST(tests_multiset, find_2) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_EQ(*(aboba.find(3)), *(buba.find(3)));
}

TEST(tests_multiset, contains) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};

    // act and assert
    ASSERT_TRUE(aboba.contains(3));
    ASSERT_FALSE(aboba.contains(6));
}

TEST(tests_multiset, equal_range_1) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act
    auto actual_result = aboba.equal_range(50);
    auto expected_res = buba.equal_range(50);

    // assert
    ASSERT_EQ(*(actual_result.first), *(expected_res.first));
    ASSERT_EQ(*(--actual_result.second), *(--expected_res.second));
}

TEST(tests_multiset, equal_range_2) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act
    auto actual_result = aboba.equal_range(4);
    auto expected_res = buba.equal_range(4);

    // assert
    ASSERT_EQ(*(actual_result.first), *(expected_res.first));
    ASSERT_EQ(*(--actual_result.second), *(--expected_res.second));
}

TEST(tests_multiset, equal_range_3) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act
    auto actual_result = aboba.equal_range(100);
    auto expected_res = buba.equal_range(100);

    // assert
    ASSERT_EQ(*(--actual_result.first), *(--expected_res.first));
    ASSERT_EQ(*(--actual_result.second), *(--expected_res.second));
}

TEST(tests_multiset, lower_bound) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_EQ(*(aboba.lower_bound(25)), *(buba.lower_bound(25)));
    ASSERT_EQ(*(--aboba.lower_bound(123)), *(--buba.lower_bound(123)));
}

TEST(tests_multiset, upper_bound) {
    // arrange
    s21::multiset<int> aboba{initializeMultiset_2};
    std::multiset<int> buba{initializeMultiset_2};

    // act and assert
    ASSERT_EQ(*(aboba.upper_bound(25)), *(buba.upper_bound(25)));
    ASSERT_EQ(*(--aboba.upper_bound(123)), *(--buba.upper_bound(123)));
}

TEST(tests_multiset, emplace_1) {
    s21::multiset<int> s{initializeMultiset_2};
    auto returned_vector = s.emplace(initializeMultiset_3);

    ASSERT_EQ(*returned_vector[0], 50);

    ASSERT_EQ(*returned_vector[1], 2);

    ASSERT_EQ(*returned_vector[2], 100000);

    ASSERT_EQ(*returned_vector[3], 50);
}

TEST(tests_multiset, emplace_2) {
    s21::multiset<int> s;
    auto p = s.emplace(6);

    ASSERT_EQ(*p[0], 6);
}

TEST(tests_multiset, emplace_3) {
    s21::multiset<int> s{initializeMultiset_2};
    auto p = s.emplace();
    ASSERT_EQ(p.size(), 0);
}
