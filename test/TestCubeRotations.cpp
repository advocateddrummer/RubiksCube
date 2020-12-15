#include "gtest/gtest.h"
#include "Cube.hpp"

/* TODO: maybe use a gtest fixture here. */

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

TEST(CubeRotationTest, x_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.x();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, xp_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.xp();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, xx_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.xx();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, y_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.y();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, yp_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.yp();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, yy_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.yy();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, z_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.z();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, zp_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.zp();

  ASSERT_EQ(a, b);
}

TEST(CubeRotationTest, zz_does_not_change_state) {
  Cube a;
  Cube b;

  a.RandomScramble();
  b = a;

  a.zz();

  ASSERT_EQ(a, b);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  const int testResults = RUN_ALL_TESTS();

  return testResults;
}
