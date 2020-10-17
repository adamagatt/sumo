#include <gtest/gtest.h>

#include "../../src/util/vec2d.h"

class VectorTests :public ::testing::TestWithParam<std::tuple<Vec2d, Vec2d, Vec2d>> { };

TEST_P(VectorTests, Add) {
    ASSERT_EQ(std::get<0>(GetParam()) + std::get<1>(GetParam()), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_CASE_P(
  Vector,
  VectorTests,
  ::testing::Values(
    std::make_tuple(Vec2d(1, 2), Vec2d(3, 4), Vec2d(4, 6)),
    std::make_tuple(Vec2d(5, 5), Vec2d(-5, -5), Vec2d(0, 0))
  )
);

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}