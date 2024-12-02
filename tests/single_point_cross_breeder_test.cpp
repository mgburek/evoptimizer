#include <gtest/gtest.h>

#include <single_point_cross_breeder.h>

TEST(SinglePointCrossBreeder, Test1)
{
    const auto a = Evoptimizer::Gene<uint8_t, float>(0xFF);
    const auto b = Evoptimizer::Gene<uint8_t, float>(0x00);
    Evoptimizer::Individual<uint8_t, float, 1> ind1 = {a};
    Evoptimizer::Individual<uint8_t, float, 1> ind2 = {b};
    Evoptimizer::SinglePointCrossBreeder<uint8_t, float, 1, 2>::crossAtPoint(ind1, ind2, 4);

    EXPECT_EQ(ind1.at(0).get(), 0xF0);
    EXPECT_EQ(ind2.at(0).get(), 0x0F);
}

TEST(SinglePointCrossBreeder, Test2)
{
    const auto a = Evoptimizer::Gene<uint16_t, float>(0xFFFF);
    const auto b = Evoptimizer::Gene<uint16_t, float>(0x0000);
    Evoptimizer::Individual<uint16_t, float, 3> ind1 = {a, a, a};
    Evoptimizer::Individual<uint16_t, float, 3> ind2 = {b, b, b};
    Evoptimizer::SinglePointCrossBreeder<uint16_t, float, 3, 2>::crossAtPoint(ind1, ind2, 24);

    EXPECT_EQ(ind1.at(0).get(), 0xFFFF);
    EXPECT_EQ(ind1.at(1).get(), 0xFF00);
    EXPECT_EQ(ind1.at(2).get(), 0x0000);
    EXPECT_EQ(ind2.at(0).get(), 0x0000);
    EXPECT_EQ(ind2.at(1).get(), 0x00FF);
    EXPECT_EQ(ind2.at(2).get(), 0xFFFF);
}

TEST(SinglePointCrossBreeder, Test3)
{
    const auto a = Evoptimizer::Gene<uint8_t, float>(0xFF);
    const auto b = Evoptimizer::Gene<uint8_t, float>(0x00);

    Evoptimizer::Individual<uint8_t, float, 2> ind1 = {a, a};
    Evoptimizer::Individual<uint8_t, float, 2> ind2 = {b, b};
    Evoptimizer::SinglePointCrossBreeder<uint8_t, float, 2, 2>::crossAtPoint(ind1, ind2, 5);

    EXPECT_EQ(ind1.at(0).get(), 0xF8);
    EXPECT_EQ(ind1.at(1).get(), 0x00);
    EXPECT_EQ(ind2.at(0).get(), 0x07);
    EXPECT_EQ(ind2.at(1).get(), 0xFF);
}

TEST(SinglePointCrossBreeder, Test4)
{
    const auto a = Evoptimizer::Gene<uint32_t, float>(0xFFFF'FFFF);
    const auto b = Evoptimizer::Gene<uint32_t, float>(0x0000'0000);
    Evoptimizer::Individual<uint32_t, float, 2> ind1 = {a, a};
    Evoptimizer::Individual<uint32_t, float, 2> ind2 = {b, b};
    Evoptimizer::SinglePointCrossBreeder<uint32_t, float, 2, 2>::crossAtPoint(ind1, ind2, 60);

    EXPECT_EQ(ind1.at(0).get(), 0xFFFF'FFFF);
    EXPECT_EQ(ind1.at(1).get(), 0xFFFF'FFF0);
    EXPECT_EQ(ind2.at(0).get(), 0x0000'0000);
    EXPECT_EQ(ind2.at(1).get(), 0x0000'000F);
}

TEST(SinglePointCrossBreeder, Test5)
{
    const auto a = Evoptimizer::Gene<uint16_t, float>(0xFFFF);
    const auto b = Evoptimizer::Gene<uint16_t, float>(0x0000);
    Evoptimizer::Individual<uint16_t, float, 5> ind1 = {a, a, a, a, a};
    Evoptimizer::Individual<uint16_t, float, 5> ind2 = {b, b, b, b, b};
    Evoptimizer::SinglePointCrossBreeder<uint16_t, float, 5, 2>::crossAtPoint(ind1, ind2, 43);

    EXPECT_EQ(ind1.at(0).get(), 0xFFFF);
    EXPECT_EQ(ind1.at(1).get(), 0xFFFF);
    EXPECT_EQ(ind1.at(2).get(), 0xFFE0);
    EXPECT_EQ(ind1.at(3).get(), 0x0000);
    EXPECT_EQ(ind1.at(4).get(), 0x0000);

    EXPECT_EQ(ind2.at(0).get(), 0x0000);
    EXPECT_EQ(ind2.at(1).get(), 0x0000);
    EXPECT_EQ(ind2.at(2).get(), 0x001F);
    EXPECT_EQ(ind2.at(3).get(), 0xFFFF);
    EXPECT_EQ(ind2.at(4).get(), 0xFFFF);
}

TEST(SinglePointCrossBreeder, Test6)
{
    const auto a = Evoptimizer::Gene<uint8_t, float>(0xFF);
    const auto b = Evoptimizer::Gene<uint8_t, float>(0x00);

    Evoptimizer::Individual<uint8_t, float, 2> ind1 = {a, a};
    Evoptimizer::Individual<uint8_t, float, 2> ind2 = {b, b};
    Evoptimizer::SinglePointCrossBreeder<uint8_t, float, 2, 2>::crossAtPoint(ind1, ind2, 0);

    EXPECT_EQ(ind1.at(0).get(), 0x00);
    EXPECT_EQ(ind1.at(1).get(), 0x00);
    EXPECT_EQ(ind2.at(0).get(), 0xFF);
    EXPECT_EQ(ind2.at(1).get(), 0xFF);
}

TEST(SinglePointCrossBreeder, Test7)
{
    const auto a = Evoptimizer::Gene<uint8_t, float>(0xFF);
    const auto b = Evoptimizer::Gene<uint8_t, float>(0x00);

    Evoptimizer::Individual<uint8_t, float, 2> ind1 = {a, a};
    Evoptimizer::Individual<uint8_t, float, 2> ind2 = {b, b};
    Evoptimizer::SinglePointCrossBreeder<uint8_t, float, 2, 2>::crossAtPoint(ind1, ind2, 15);

    EXPECT_EQ(ind1.at(0).get(), 0xFF);
    EXPECT_EQ(ind1.at(1).get(), 0xFE);
    EXPECT_EQ(ind2.at(0).get(), 0x00);
    EXPECT_EQ(ind2.at(1).get(), 0x01);
}