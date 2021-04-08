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

TEST_F(CubeTest, SetCubeStateDefaultArg) {
  a.SetCubeState();

  ASSERT_TRUE(a.IsSolved());
}

TEST_F(CubeTest, SetCubeStateCorrectNumOfArgs) {
  try {
    a.SetCubeState({ 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                     'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b',
                     'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
                     'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g',
                     'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y',
                     'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'});
    ASSERT_TRUE(a.IsSolved());
  } catch (const char * msg) {
    FAIL() << "Did not expected an exception";
  } catch (...) {
    FAIL() << "Did not expected an exception";
  }
}

TEST_F(CubeTest, SetCubeStateIncorrectNumOfArgs) {
  /* TODO: I do not love this, all the examples I found for using EXPECT_THROW
   * were confusing and I have settled on something like this which I am still
   * not sure is really correct.
   */
  try {
    a.SetCubeState({'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                    'b', 'b', 'o', 'r', 'b', 'b', 'b', 'b', 'b',
                    'w', 'w', 'r', 'w', 'w', 'w', 'r', 'g', 'w',
                    'g', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y',
                    'r', 'r', 'y', 'b', 'b', 'r', 'r', 'r', 'r'});
    FAIL() << "Expected an exception";
  } catch (const char * msg) {
    EXPECT_STREQ( "Cube::SetCubeState must have an input state with 54 elements!", msg );
  } catch (...) {
    FAIL() << "Expected a different exception";
  }
}

TEST_F(CubeTest, SetCubeStateSexyMove) {
  /* Use SetCubeState to set the cube state to the state after one 'sexy move'
   * has been performed.
   */
  a.SetCubeState({'o', 'o', 'w', 'o', 'o', 'o', 'o', 'o', 'o',
                  'b', 'b', 'o', 'r', 'b', 'b', 'b', 'b', 'b',
                  'w', 'w', 'r', 'w', 'w', 'w', 'r', 'g', 'w',
                  'g', 'w', 'w', 'g', 'g', 'g', 'g', 'g', 'g',
                  'g', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y',
                  'r', 'r', 'y', 'b', 'b', 'r', 'r', 'r', 'r'});

  b.SexyMove();

  ASSERT_EQ(a, b);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  const int testResults = RUN_ALL_TESTS();

  return testResults;
}
