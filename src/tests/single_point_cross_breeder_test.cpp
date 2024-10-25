#include <gtest/gtest.h>

#include <global_engine.h>
#include <single_point_cross_breeder.h>

TEST(SinglePointCrossBreeder, Test1)
{
    Random::engine.seed(156165);

    auto a = Evoptimizer::Gene<uint8_t, float>(0xFF);
    auto b = Evoptimizer::Gene<uint8_t, float>(0x00);
    auto cross = Evoptimizer::SinglePointCrossBreeder<uint8_t, float, 1, 2>(1.0);
    auto crossed = cross({{{a}, {b}}});

    EXPECT_EQ(crossed.at(0).at(0).get(), 0x0F);
    EXPECT_EQ(crossed.at(1).at(0).get(), 0xF0);
}