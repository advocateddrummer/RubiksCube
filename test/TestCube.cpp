#include "gtest/gtest.h"
#include "Cube.hpp"

class CubeTest : public ::testing::Test {
  protected:
    void SetUp() override {
      //a.RandomScramble();
      //b = a;
    }

    //void TearDown override { }

    Cube a;
    Cube b;
};

TEST_F(CubeTest, IsSolvedWorksPositive) {
  ASSERT_TRUE(a.IsSolved());
}

TEST_F(CubeTest, IsSolvedWorksNegative) {
  a.RandomScramble(1);
  ASSERT_FALSE(a.IsSolved());
}

TEST_F(CubeTest, ResetCubeWorks) {
  a.RandomScramble();
  a.ResetCube();

  ASSERT_TRUE(a.IsSolved());
}

TEST_F(CubeTest, AssignmentOperatorOverloadWorks) {
  a.RandomScramble();
  b = a;

  ASSERT_EQ(a, b);
}

/* I think this is actually tested implicitly in the
 * AssignmentOperatorOverloadWorks test above.
 */
TEST_F(CubeTest, EqualityOperatorOverloadWorksPositive) {
  a.r();
  b.r();

  ASSERT_TRUE(a == b);
}

TEST_F(CubeTest, EqualityOperatorOverloadWorksNegative) {
  a.r();
  b.b();

  ASSERT_FALSE(a == b);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  const int testResults = RUN_ALL_TESTS();

  return testResults;
}
