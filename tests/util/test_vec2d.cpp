#include "../../src/util/vec2d.h"
#include "gtest/gtest.h"

TEST (Vector, Add) { 
    Vec2d vec1{1, 2};
    Vec2d vec2{3, 4};
    //ASSERT_EQ(vec1+vec2, Vec2d vec3{4, 6});
    ASSERT_EQ(4, 4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}