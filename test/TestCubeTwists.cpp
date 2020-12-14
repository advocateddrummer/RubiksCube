#include "gtest/gtest.h"
#include "Cube.hpp"

class CubeTwistTest : public ::testing::Test {
  protected:
    void SetUp() override {
      a.RandomScramble();
      b = a;
    }

    Cube a;
    Cube b;
};

TEST_F(CubeTwistTest, d_equals_U) {

  a.d();
  b.U();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, f_equals_B) {

  a.f();
  b.B();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, r_equals_L) {

  a.r();
  b.L();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, b_equals_F) {

  a.b();
  b.F();

  ASSERT_EQ(a, b);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  const int testResults = RUN_ALL_TESTS();

  return testResults;
}
