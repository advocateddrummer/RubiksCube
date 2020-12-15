#include "gtest/gtest.h"
#include "Cube.hpp"

TEST(CubeRotationTest, x_equals_solved) {
  Cube a;

  a.x();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, xp_equals_solved) {
  Cube a;

  a.xp();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, xx_equals_solved) {
  Cube a;

  a.xx();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, y_equals_solved) {
  Cube a;

  a.y();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, yp_equals_solved) {
  Cube a;

  a.yp();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, yy_equals_solved) {
  Cube a;

  a.yy();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, z_equals_solved) {
  Cube a;

  a.z();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, zp_equals_solved) {
  Cube a;

  a.zp();

  ASSERT_TRUE(a.IsSolved());
}

TEST(CubeRotationTest, zz_equals_solved) {
  Cube a;

  a.zz();

  ASSERT_TRUE(a.IsSolved());
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  const int testResults = RUN_ALL_TESTS();

  return testResults;
}
