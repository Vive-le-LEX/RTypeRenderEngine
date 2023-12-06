/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** Window-test
*/

#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(add, test1)
{
    EXPECT_EQ(add(1, 1), 2);
}

TEST(add, test2)
{
    EXPECT_EQ(add(1, 2), 3);
}

TEST(badadd, badtest3)
{
    EXPECT_EQ(add(69, 69), 4);
}
