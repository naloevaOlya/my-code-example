#include "../s21_set.hpp"

#include <gtest/gtest.h>

#define initializeSet                                                                                     \
    1000, 500, 2000, 250, 750, 1500, 3000, 125, 312, 625, 850, 1250, 1750, 2500, 4000, 75, 200, 275, 400, \
        610, 900

#define initializeSet_2 50, 30, 125, 25, 35, 99, 263, 20, 29, 3

#define initializeSet_3 50, 2, 100000, 50

bool isSetEqual(std::set<int> *expected_res, s21::set<int> *actual_res) {
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

TEST(tests_set, default_constructor) {
    // arrange
    s21::set<int> aboba;
    std::set<int> buba;

    // act and assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, initializer_constructor) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act and assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, copy_constructor) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    s21::set<int> aboba_copy(aboba);
    std::set<int> buba{initializeSet_2};
    std::set<int> buba_copy(buba);

    // act and assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    result = isSetEqual(&buba_copy, &aboba_copy);
    ASSERT_TRUE(result);
}

TEST(tests_set, move_constructor) {
    // arrange
    s21::set<int> aboba_src{initializeSet_2};
    std::set<int> buba_src{initializeSet_2};

    // act
    s21::set<int> aboba(std::move(aboba_src));
    std::set<int> buba(std::move(buba_src));

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, assignment_operator) {
    // arrange
    s21::set<int> aboba_src{initializeSet_2};
    s21::set<int> aboba;
    std::set<int> buba_src{initializeSet_2};
    std::set<int> buba;

    // act
    aboba = std::move(aboba_src);
    buba = buba_src;

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, begin) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act and assert
    ASSERT_EQ((*aboba.begin()), (*buba.begin()));
    ASSERT_EQ((*aboba.begin()), (*buba.begin()));
}

TEST(tests_set, end) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act and assert
    ASSERT_EQ((*(--aboba.end())), (*(--buba.end())));
    ASSERT_EQ((*(--aboba.end())), (*(--buba.end())));
}

TEST(tests_set, empty) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act and assert
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_set, size) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act and assert
    ASSERT_EQ(aboba.size(), buba.size());
}
TEST(tests_set, max_size) {
    // arrange
    s21::set<int> aboba;
    std::set<int> buba;

    // act and assert
    ASSERT_EQ(aboba.max_size(), buba.max_size());
}

TEST(tests_set, clear) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act
    aboba.clear();
    buba.clear();

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, insert_1) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act
    std::pair<s21::BST<int>::iterator, bool> ret_actual_pair = aboba.insert(70);
    std::pair<std::set<int>::iterator, bool> ret_expected_pair = buba.insert(70);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
}

TEST(tests_set, insert_2) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act
    std::pair<s21::BST<int>::iterator, bool> ret_actual_pair = aboba.insert(4);
    std::pair<std::set<int>::iterator, bool> ret_expected_pair = buba.insert(4);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
    ASSERT_TRUE(result);
}

TEST(tests_set, insert_3) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

    // act

    std::pair<s21::BST<int>::iterator, bool> ret_actual_pair = aboba.insert(4);
    std::pair<std::set<int>::iterator, bool> ret_expected_pair = buba.insert(4);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
    ASSERT_TRUE(result);
}

TEST(tests_set, erase_1) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

    // act
    aboba.erase(aboba.begin());
    buba.erase(buba.begin());

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, erase_2) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

    // act
    auto actualIter = --aboba.end();
    auto expectedIter = --buba.end();
    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, erase_3) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

    // act
    auto actualIter = aboba.begin();
    auto expectedIter = buba.begin();

    for (size_t i = 0; i < 1; i++) {
        ++actualIter;
        ++expectedIter;
    }

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, erase_4) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

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
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, erase_5) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

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
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, erase_6) {
    // arrange
    s21::set<int> aboba{initializeSet};
    std::set<int> buba{initializeSet};

    // act

    auto actualIter = aboba.begin();
    auto expectedIter = buba.begin();

    for (size_t i = 0; i < 13; i++) {
        ++actualIter;
        ++expectedIter;
    }

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, swap) {
    // arrange
    s21::set<int> aboba_src{initializeSet_2};
    s21::set<int> aboba;
    std::set<int> buba_src{initializeSet_2};
    std::set<int> buba;

    // act
    aboba.swap(aboba_src);
    buba = buba_src;

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_set, merge_1) {
    // arrange
    s21::set<int> aboba_src{initializeSet};
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba_src{initializeSet};
    std::set<int> buba{initializeSet_2};

    // act

    aboba.merge(aboba_src);
    buba.merge(buba_src);

    // assert
    bool result = isSetEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    result = isSetEqual(&buba_src, &aboba_src);
    ASSERT_TRUE(result);
}

TEST(tests_set, find_1) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act
    bool actual_result = aboba.find(1453) == aboba.end();
    bool expected_result = buba.find(1453) == buba.end();

    // assert
    ASSERT_TRUE(actual_result && expected_result);
}

TEST(tests_set, find_2) {
    // arrange
    s21::set<int> aboba{initializeSet_2};
    std::set<int> buba{initializeSet_2};

    // act and assert
    ASSERT_EQ(*(aboba.find(3)), *(buba.find(3)));
}

TEST(tests_set, contains) {
    // arrange
    s21::set<int> aboba{initializeSet_2};

    // act and assert
    ASSERT_TRUE(aboba.contains(3));
    ASSERT_FALSE(aboba.contains(6));
}

TEST(tests_set, emplace_1) {
    s21::set<int> s{initializeSet_2};
    auto returned_vector = s.emplace(initializeSet_3);

    ASSERT_FALSE(returned_vector[0].second);

    ASSERT_EQ((*returned_vector[1].first), 2);
    ASSERT_TRUE(returned_vector[1].second);

    ASSERT_EQ((*returned_vector[2].first), 100000);
    ASSERT_TRUE(returned_vector[2].second);

    ASSERT_FALSE(returned_vector[3].second);
}

TEST(tests_set, emplace_2) {
    s21::set<int> s;
    auto p = s.emplace(6);

    ASSERT_EQ((*p[0].first), 6);
    ASSERT_TRUE(p[0].second);
}

TEST(tests_set, emplace_3) {
    s21::set<int> s{initializeSet_2};
    auto p = s.emplace();
    ASSERT_EQ(p.size(), 0);
}
