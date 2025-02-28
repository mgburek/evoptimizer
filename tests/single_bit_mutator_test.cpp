#include <gtest/gtest.h>

#include <classic_single_bit_mutator.h>

TEST(SingleBitMutator, Test1)
{
    const auto a = Evo::Classic::Gene<uint8_t, float>(0xFF);
    Evo::Classic::Individual<uint8_t, float, 1> ind = {a};
    Evo::Classic::SingleBitMutator<uint8_t, float, 1, 2>::mutateAtPoint(ind, 4);

    EXPECT_EQ(ind.at(0).get(), 0xF7);
}

TEST(SingleBitMutator, Test2)
{
    const auto a = Evo::Classic::Gene<uint8_t, float>(0xFF);
    Evo::Classic::Individual<uint8_t, float, 1> ind = {a};
    Evo::Classic::SingleBitMutator<uint8_t, float, 1, 2>::mutateAtPoint(ind, 0);

    EXPECT_EQ(ind.at(0).get(), 0x7F);
}

TEST(SingleBitMutator, Test3)
{
    const auto a = Evo::Classic::Gene<uint32_t, float>(0xFFFF'FFFF);
    Evo::Classic::Individual<uint32_t, float, 2> ind = {a, a};
    Evo::Classic::SingleBitMutator<uint32_t, float, 2, 2>::mutateAtPoint(ind, 47);

    EXPECT_EQ(ind.at(0).get(), 0xFFFF'FFFF);
    EXPECT_EQ(ind.at(1).get(), 0xFFFE'FFFF);
}

TEST(SingleBitMutator, Test4)
{
    const auto a = Evo::Classic::Gene<uint32_t, float>(0xFFFF'FFFF);
    Evo::Classic::Individual<uint32_t, float, 2> ind = {a, a};
    Evo::Classic::SingleBitMutator<uint32_t, float, 2, 2>::mutateAtPoint(ind, 63);

    EXPECT_EQ(ind.at(0).get(), 0xFFFF'FFFF);
    EXPECT_EQ(ind.at(1).get(), 0xFFFF'FFFE);
}

TEST(SingleBitMutator, Test5)
{
    const auto a = Evo::Classic::Gene<uint16_t, float>(0xFFFF);
    Evo::Classic::Individual<uint16_t, float, 3> ind = {a, a, a};
    Evo::Classic::SingleBitMutator<uint16_t, float, 3, 2>::mutateAtPoint(ind, 21);

    EXPECT_EQ(ind.at(0).get(), 0xFFFF);
    EXPECT_EQ(ind.at(1).get(), 0xFBFF);
    EXPECT_EQ(ind.at(2).get(), 0xFFFF);
}