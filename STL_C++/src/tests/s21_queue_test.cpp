#include <gtest/gtest.h>
#include "../s21_queue.hpp"

#include <queue>

// ***** QUEUE *****
TEST(tests_queue, default_constructor) {
    // arrange and act
    s21::queue<int> aboba;
    std::queue<int> buba;

    // assert
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_queue, initializer_constructor) {
    // arrange and act
    s21::queue<int> aboba{1, 2, 3, 4};
    std::queue<int> buba({1, 2, 3, 4});

    // assert
    ASSERT_EQ(aboba.front(), buba.front());
    ASSERT_EQ(aboba.back(), buba.back());

    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, copy_constructor) {
    // arrange and act
    s21::queue<int> aboba{1, 2, 3, 4};
    s21::queue<int> aboba_copy(aboba);
    std::queue<int> buba({1, 2, 3, 4});
    std::queue<int> buba_copy(buba);

    // assert
    ASSERT_EQ(aboba_copy.front(), buba_copy.front());
    ASSERT_EQ(aboba_copy.back(), buba_copy.back());

    ASSERT_EQ(aboba.front(), buba.front());
    ASSERT_EQ(aboba.back(), buba.back());

    ASSERT_EQ(aboba_copy.size(), buba_copy.size());
    ASSERT_EQ(aboba.size(), buba.size());

    ASSERT_EQ(aboba.empty(),buba.empty());
    ASSERT_EQ(aboba_copy.empty(),buba_copy.empty());
}

TEST(tests_queue, move_constructor) {
    // arrange
    s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
    std::queue<int> buba({1, 2, 3, 4, 5, 6});

    // act
    s21::queue<int> aboba_move(std::move(aboba));
    std::queue<int> buba_move(std::move(buba));

    // assert
    ASSERT_EQ(aboba_move.front(), buba_move.front());
    ASSERT_EQ(aboba_move.back(), buba_move.back());

    ASSERT_EQ(aboba_move.size(), buba_move.size());
    ASSERT_EQ(aboba.size(), buba.size());

    ASSERT_EQ(aboba.empty(),buba.empty());
    ASSERT_EQ(aboba_move.empty(),buba_move.empty());
}

TEST(tests_queue, assignment_operator) {
    // arrange
    s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
    std::queue<int> buba({1, 2, 3, 4, 5, 6});

    // act
    s21::queue<int> aboba_move = aboba;
    std::queue<int> buba_move = buba;

    // assert
    ASSERT_EQ(aboba_move.front(), buba_move.front());
    ASSERT_EQ(aboba_move.back(), buba_move.back());

    ASSERT_EQ(aboba_move.size(), buba_move.size());
    ASSERT_EQ(aboba.size(), buba.size());

    ASSERT_EQ(aboba.empty(),buba.empty());
    ASSERT_EQ(aboba_move.empty(),buba_move.empty());
}

TEST(tests_queue, front_back) {
    // arrange
    s21::queue<int> aboba;
    std::queue<int> buba;
    auto a = 1;
    auto b = 2;
    auto c = 3;
    auto d = 4;

    // act
    aboba.push(a);
    aboba.push(b);
    aboba.push(c);
    aboba.push(d);
    buba.push(a);
    buba.push(b);
    buba.push(c);
    buba.push(d);

    // assert
    ASSERT_EQ(aboba.front(), buba.front());
    ASSERT_EQ(aboba.back(),buba.back());
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, empty) {
    // arrange
    s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
    std::queue<int> buba({1, 2, 3, 4, 5, 6});
    s21::queue<int> aboba_2;
    std::queue<int> buba_2;

    // act

    // assert
    ASSERT_EQ(aboba.empty(), buba.empty());
    ASSERT_EQ(aboba_2.empty(),buba_2.empty());
}

TEST(tests_queue, size) {
    // arrange
    s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
    std::queue<int> buba({1, 2, 3, 4, 5, 6});
    s21::queue<int> aboba_2;
    std::queue<int> buba_2;

    // act

    // assert
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba_2.size(),buba_2.size());
}

TEST(tests_queue, pop) {
    // arrange
    s21::queue<int> aboba;
    std::queue<int> buba;
    auto a = 1;
    auto b = 2;
    auto c = 3;
    auto d = 4;

    // act
    aboba.push(a);
    aboba.push(b);
    aboba.push(c);
    aboba.push(d);
    buba.push(a);
    buba.push(b);
    buba.push(c);
    buba.push(d);
    aboba.pop();
    buba.pop();

    // assert
    ASSERT_EQ(aboba.front(), buba.front());
    ASSERT_EQ(aboba.back(),buba.back());
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, push) {
    // arrange
    s21::queue<int> aboba;
    auto a = 1;
    auto b = 2;
    auto c = 3;
    auto d = 4;

    // act
    aboba.push(a);
    aboba.push(b);
    aboba.push(c);
    aboba.push(d);

    // assert
    ASSERT_EQ(aboba.front(), a);
    ASSERT_EQ(aboba.back(), d);

    ASSERT_EQ(aboba.size(), d);
    ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, swap) {
    // arrange
    s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
    s21::queue<int> aboba_swap{5, 6, 7};
    std::queue<int> buba({1, 2, 3, 4, 5, 6});
    std::queue<int> buba_swap({5, 6, 7});

    // act
    aboba.swap(aboba_swap);
    buba.swap(buba_swap);

    // assert
    ASSERT_EQ(aboba_swap.front(), buba_swap.front());
    ASSERT_EQ(aboba_swap.back(), buba_swap.back());

    ASSERT_EQ(aboba.front(), buba.front());
    ASSERT_EQ(aboba.back(), buba.back());

    ASSERT_EQ(aboba_swap.size(), buba_swap.size());
    ASSERT_EQ(aboba.size(), buba.size());

    ASSERT_EQ(aboba.empty(),buba.empty());
    ASSERT_EQ(aboba_swap.empty(),buba_swap.empty());
}

TEST(tests_queue_bonus_suit, emplace_back) {
    // arrange
    s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
    std::queue<int> buba({1, 2, 3, 4, 5, 6, 5, 9, 11, 7});

    // act
    aboba.emplace_back(5, 9, 11, 7);
    
    // assert
    ASSERT_EQ(aboba.front(), buba.front());
    ASSERT_EQ(aboba.back(),buba.back());
    ASSERT_EQ(aboba.size(), buba.size());
}
