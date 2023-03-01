#include "../s21_map.hpp"

#include <gtest/gtest.h>

#define initializeMap                                                                                      \
                                                                                                           \
    std::pair<int, int>(1000, 1000), std::pair<int, int>(500, 500), std::pair<int, int>(2000, 2000),       \
        std::pair<int, int>(250, 250), std::pair<int, int>(750, 750), std::pair<int, int>(1500, 1500),     \
        std::pair<int, int>(3000, 3000), std::pair<int, int>(125, 125), std::pair<int, int>(312, 312),     \
        std::pair<int, int>(625, 625), std::pair<int, int>(850, 850), std::pair<int, int>(1250, 1250),     \
        std::pair<int, int>(1750, 1750), std::pair<int, int>(2500, 2500), std::pair<int, int>(4000, 4000), \
        std::pair<int, int>(75, 75), std::pair<int, int>(200, 200), std::pair<int, int>(275, 275),         \
        std::pair<int, int>(400, 400), std::pair<int, int>(610, 610), std::pair<int, int>(900, 900)

#define initializeMap_2                                                                        \
    std::pair<int, int>(50, 50), std::pair<int, int>(30, 30), std::pair<int, int>(125, 125),   \
        std::pair<int, int>(25, 25), std::pair<int, int>(35, 35), std::pair<int, int>(99, 99), \
        std::pair<int, int>(263, 263), std::pair<int, int>(20, 20), std::pair<int, int>(29, 29),

#define initializeMap_3                                                                \
    std::pair<int, int>(50, 50), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3), \
        std::pair<int, int>(50, 50)

// ***** MAP *****

bool isMapEqual(std::map<int, int> *expected_res, s21::map<int, int> *actual_res) {
    bool testResult{true};
    auto expected_iter = expected_res->begin();
    auto actual_iter = actual_res->begin();

    auto actual_size = actual_res->size();
    auto expected_size = expected_res->size();

    if (actual_size == expected_size) {
        while (expected_iter != expected_res->end()) {
            int actual_first = (*actual_iter).first;
            int expected_first = (*expected_iter).first;
            int actual_second = (*actual_iter).second;
            int expected_second = (*expected_iter).second;

            if (actual_first != expected_first || actual_second != expected_second) {
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

TEST(tests_map, default_constructor) {
    // arrange
    s21::map<int, int> aboba;
    std::map<int, int> buba;

    // act and assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, initializer_constructor) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    std::map<int, int> buba{initializeMap_2};

    // act and assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, copy_constructor) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    s21::map<int, int> aboba_copy(aboba);
    std::map<int, int> buba{initializeMap_2};
    std::map<int, int> buba_copy(buba);

    // act and assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    result = isMapEqual(&buba_copy, &aboba_copy);
    ASSERT_TRUE(result);
}

TEST(tests_map, move_constructor) {
    // arrange
    s21::map<int, int> aboba_src{initializeMap_2};
    std::map<int, int> buba_src{initializeMap_2};

    // act
    s21::map<int, int> aboba(std::move(aboba_src));
    std::map<int, int> buba(std::move(buba_src));

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, assignment_operator) {
    // arrange
    s21::map<int, int> aboba_src{initializeMap_2};
    s21::map<int, int> aboba;
    std::map<int, int> buba_src{initializeMap_2};
    std::map<int, int> buba;

    // act
    aboba = std::move(aboba_src);
    buba = std::move(buba_src);

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, at) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};

    // act and assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, AccessBrackets_1) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    std::map<int, int> buba{initializeMap_2};

    int keyToAccess = 99;

    // act
    int actual_val = aboba[keyToAccess];
    int expected_val = buba[keyToAccess];

    // assert
    ASSERT_EQ(actual_val, expected_val);
}

TEST(tests_map, AccessBrackets_2) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    std::map<int, int> buba{initializeMap_2};

    int keyToAccess = 26;
    int valueToAsign = 100;

    // act
    aboba[keyToAccess] = valueToAsign;
    buba[keyToAccess] = valueToAsign;

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, begin) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};

    // act and assert
    ASSERT_EQ((*aboba.begin()).first, (*buba.begin()).first);
    ASSERT_EQ((*aboba.begin()).second, (*buba.begin()).second);
}

TEST(tests_map, end) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};

    // act and assert
    ASSERT_EQ((*(--aboba.end())).first, (*(--buba.end())).first);
    ASSERT_EQ((*(--aboba.end())).second, (*(--buba.end())).second);
}

TEST(tests_map, empty) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};
    s21::map<std::string, std::string> aboba_2;
    std::map<std::string, std::string> buba_2;

    // act and assert
    ASSERT_EQ(aboba.empty(), buba.empty());
    ASSERT_EQ(aboba_2.empty(), buba_2.empty());
}

TEST(tests_map, size) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};
    s21::map<std::string, std::string> aboba_2;
    std::map<std::string, std::string> buba_2;

    // act and assert
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba_2.size(), buba_2.size());
}

TEST(tests_map, max_size) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    std::map<int, int> buba{initializeMap_2};

    // act
    s21::map<int, int>::size_type actual_max = aboba.max_size();
    std::map<int, int>::size_type expected_max = buba.max_size();

    // assert
    ASSERT_EQ(expected_max, actual_max);
}

TEST(tests_map, clear) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};
    aboba.clear();
    buba.clear();

    // act and assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, insert_1) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    std::map<int, int> buba{initializeMap_2};

    // act
    std::pair<s21::BST<std::pair<const int, int>>::iterator, bool> ret_actual_pair =
        aboba.insert(std::pair<int, int>(70, 70));
    std::pair<std::conditional<false, std::map<int, int>::const_iterator,
                               std::_Rb_tree_iterator<std::pair<const int, int>>>::type,
              bool>
        ret_expected_pair = buba.insert(std::pair<int, int>(70, 70));

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
}

TEST(tests_map, insert_2) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};

    // act
    std::pair<s21::BST<std::pair<const int, int>>::iterator, bool> ret_actual_pair =
        aboba.insert(std::pair<int, int>(4, 4));
    std::pair<std::conditional<false, std::map<int, int>::const_iterator,
                               std::_Rb_tree_iterator<std::pair<const int, int>>>::type,
              bool>
        ret_expected_pair = buba.insert(std::pair<int, int>(4, 4));

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
    ASSERT_TRUE(result);
}

TEST(tests_map, insert_3) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

    // act

    std::pair<s21::BST<std::pair<const int, int>>::iterator, bool> ret_actual_pair = aboba.insert(4, 4);
    std::pair<std::conditional<false, std::map<int, int>::const_iterator,
                               std::_Rb_tree_iterator<std::pair<const int, int>>>::type,
              bool>
        ret_expected_pair = buba.insert(std::pair<int, int>(4, 4));

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
    ASSERT_TRUE(result);
}

TEST(tests_map, insert_4) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

    // act
    std::pair<s21::BST<std::pair<const int, int>>::iterator, bool> ret_actual_pair =
        aboba.insert(std::pair<int, int>(125, 125));
    std::pair<std::conditional<false, std::map<int, int>::const_iterator,
                               std::_Rb_tree_iterator<std::pair<const int, int>>>::type,
              bool>
        ret_expected_pair = buba.insert(std::pair<int, int>(125, 125));

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    ASSERT_FALSE(ret_actual_pair.second);
    ASSERT_FALSE(ret_expected_pair.second);
}

TEST(tests_map, insert_or_assign_1) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};
    int key = 125;
    int obj = 200;

    // act
    std::pair<s21::BST<std::pair<const int, int>>::iterator, bool> ret_actual_pair =
        aboba.insert_or_assign(key, obj);
    std::pair<std::conditional<false, std::map<int, int>::const_iterator,
                               std::_Rb_tree_iterator<std::pair<const int, int>>>::type,
              bool>
        ret_expected_pair = buba.insert_or_assign(key, obj);

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    ASSERT_FALSE(ret_actual_pair.second);
    ASSERT_FALSE(ret_expected_pair.second);
}

TEST(tests_map, insert_or_assign_2) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};
    int key = 40;
    int obj = 200;

    // act
    std::pair<s21::BST<std::pair<const int, int>>::iterator, bool> ret_actual_pair =
        aboba.insert_or_assign(key, obj);
    std::pair<std::conditional<false, std::map<int, int>::const_iterator,
                               std::_Rb_tree_iterator<std::pair<const int, int>>>::type,
              bool>
        ret_expected_pair = buba.insert_or_assign(key, obj);

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    ASSERT_TRUE(ret_actual_pair.second);
    ASSERT_TRUE(ret_expected_pair.second);
}

TEST(tests_map, erase_1) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

    // act
    aboba.erase(aboba.begin());
    buba.erase(buba.begin());

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_2) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

    // act
    auto actualIter = --aboba.end();
    auto expectedIter = --buba.end();
    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_3) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

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
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_4) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

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
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_5) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

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
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_6) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

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
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_7) {
    // arrange
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba{initializeMap};

    // act

    auto actualIter = aboba.begin();
    auto expectedIter = buba.begin();

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    actualIter = aboba.begin();
    expectedIter = buba.begin();

    aboba.erase(actualIter);
    buba.erase(expectedIter);

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, erase_8) {
    // arrange
    s21::map<int, int> aboba{initializeMap_2};
    std::map<int, int> buba{initializeMap_2};

    // act

    for (size_t i = 0; i < 9; i++) {
        auto actualIter = aboba.begin();
        auto expectedIter = buba.begin();

        aboba.erase(actualIter);
        buba.erase(expectedIter);
    }

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, swap) {
    // arrange
    s21::map<int, int> aboba_src{initializeMap_2};
    s21::map<int, int> aboba;
    std::map<int, int> buba_src{initializeMap_2};
    std::map<int, int> buba;

    // act
    aboba.swap(aboba_src);
    buba = buba_src;

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
}

TEST(tests_map, merge_1) {
    // arrange
    s21::map<int, int> aboba_src{initializeMap_2};
    s21::map<int, int> aboba{initializeMap};
    std::map<int, int> buba_src{initializeMap_2};
    std::map<int, int> buba{initializeMap};

    // act

    aboba.merge(aboba_src);
    buba.merge(buba_src);

    // assert
    bool result = isMapEqual(&buba, &aboba);
    ASSERT_TRUE(result);
    result = isMapEqual(&buba_src, &aboba_src);
    ASSERT_TRUE(result);
}

TEST(tests_map, contains) {
    // arrange
    s21::map<int, int> aboba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                             std::pair<int, int>(3, 3)};
    std::map<int, int> buba{std::pair<int, int>(1, 1), std::pair<int, int>(2, 2), std::pair<int, int>(3, 3)};

    // act and assert
    ASSERT_TRUE(aboba.contains(3));
    ASSERT_FALSE(aboba.contains(6));
}

TEST(tests_map, emplace_1) {
    s21::map<int, int> m{initializeMap_2};
    auto returned_vector = m.emplace(initializeMap_3);

    ASSERT_FALSE(returned_vector[0].second);

    ASSERT_EQ((*returned_vector[1].first).first, 2);
    ASSERT_EQ((*returned_vector[1].first).second, 2);
    ASSERT_TRUE(returned_vector[1].second);

    ASSERT_EQ((*returned_vector[2].first).first, 3);
    ASSERT_EQ((*returned_vector[2].first).second, 3);
    ASSERT_TRUE(returned_vector[2].second);

    ASSERT_FALSE(returned_vector[3].second);
}

TEST(tests_map, emplace_2) {
    s21::map<int, int> m;
    auto p = m.emplace(std::pair<int, int>(6, 6));

    ASSERT_EQ((*p[0].first).first, 6);
    ASSERT_EQ((*p[0].first).second, 6);
    ASSERT_TRUE(p[0].second);
}

TEST(tests_map, emplace_3) {
    s21::map<int, int> m{initializeMap_2};
    auto p = m.emplace();
    ASSERT_EQ(p.size(), 0);
}
