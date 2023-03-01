#include "../s21_stack.hpp"

#include <gtest/gtest.h>

#include <stack>

// ***** STACK *****

TEST(tests_stack, default_constructor) {
    // arrange and act
    s21::stack<int> aboba;
    std::stack<int> buba;

    // assert
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, init_constructor) {
    // arrange and act
    s21::stack<int> aboba{1, 2, 3, 4, 5};
    std::stack<int> buba({1, 2, 3, 4, 5});

    // assert
    ASSERT_EQ(aboba.top(), buba.top());
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack, copy_constructor) {
    // arrange and act
    s21::stack<int> aboba{1, 2, 3, 4, 5};
    s21::stack<int> aboba_copy(aboba);
    std::stack<int> buba({1, 2, 3, 4, 5});
    std::stack<int> buba_copy(buba);

    // assert
    ASSERT_EQ(aboba_copy.top(), buba_copy.top());
    ASSERT_EQ(aboba.top(), buba.top());
    ASSERT_EQ(aboba_copy.size(), buba_copy.size());
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack, move_constructor) {
    // arrange and act
    s21::stack<int> aboba{1, 2, 3, 4, 5};
    s21::stack<int> aboba_move(std::move(aboba));
    std::stack<int> buba({1, 2, 3, 4, 5});
    std::stack<int> buba_move(std::move(buba));

    // assert
    ASSERT_EQ(aboba_move.top(), buba_move.top());
    ASSERT_EQ(aboba_move.size(), buba_move.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, assignment_operator) {
    // arrange and act
    s21::stack<int> aboba{1, 2, 3, 4, 5};
    s21::stack<int> aboba_2 = std::move(aboba);
    std::stack<int> buba({1, 2, 3, 4, 5});
    std::stack<int> buba_2 = std::move(buba);

    // assert
    ASSERT_EQ(aboba_2.top(), buba_2.top());
    ASSERT_EQ(aboba_2.size(), buba_2.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}


TEST(tests_stack, empty) {
    // arrange
    s21::stack<int> aboba{1, 2, 3, 4, 5};
    std::stack<int> buba({1, 2, 3, 4, 5});

    // act and assert
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, size) {
    // arrange
    s21::stack<int> aboba{1, 2, 3, 4, 5};

    // act and assert
    ASSERT_EQ(aboba.size(), 5);
}


TEST(tests_stack, push) {
    // arrange
    s21::stack<int> aboba;
    std::stack<int> buba;
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
    ASSERT_EQ(aboba.top(), buba.top());
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack, pop) {
    // arrange
    s21::stack<int> aboba{1, 2, 3, 4};
    std::stack<int> buba({1, 2, 3, 4});

    // act
    aboba.pop();
    buba.pop();

    // assert
    ASSERT_EQ(aboba.top(), buba.top());
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, swap) {
    // arrange
    s21::stack<int> aboba{1, 2, 3, 4, 5};
    s21::stack<int> aboba_2{6, 7, 8};
    std::stack<int> buba({1, 2, 3, 4, 5});
    std::stack<int> buba_2({6, 7, 8});

    // act
    aboba.swap(aboba_2);
    buba.swap(buba_2);

    // assert
    ASSERT_EQ(aboba_2.top(), buba_2.top());
    ASSERT_EQ(aboba_2.size(), buba_2.size());
    ASSERT_EQ(aboba.top(), buba.top());
    ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack_bonus_suit, emplace_front) {
    // arrange
    s21::stack<int> aboba{1, 2, 3, 4, 5, 6};
    std::stack<int> buba({1, 2, 3, 4, 5, 6, 5, 9, 11, 7});

    // act
    aboba.emplace_front(5, 9, 11, 7);
    // assert
    ASSERT_EQ(aboba.top(), buba.top());
    ASSERT_EQ(aboba.size(), buba.size());
    ASSERT_EQ(aboba.empty(), buba.empty());
}
