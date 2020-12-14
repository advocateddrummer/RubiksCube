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

/********************************************************************/
/* Single face rotation versus opposite double face rotation tests. */
/********************************************************************/

/********************************************************************/
/********************** Up/down rotation tests **********************/
/********************************************************************/
TEST_F(CubeTwistTest, d_equals_U) {

  a.d();
  b.U();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, D_equals_u) {

  a.D();
  b.u();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, dp_equals_Up) {

  a.dp();
  b.Up();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, Dp_equals_up) {

  a.Dp();
  b.up();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, dd_equals_UU) {

  a.dd();
  b.UU();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, DD_equals_uu) {

  a.DD();
  b.uu();

  ASSERT_EQ(a, b);
}

/********************************************************************/
/******************** Front/back rotation tests *********************/
/********************************************************************/
TEST_F(CubeTwistTest, f_equals_B) {

  a.f();
  b.B();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, F_equals_b) {

  a.F();
  b.b();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, fp_equals_Bp) {

  a.fp();
  b.Bp();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, Fp_equals_bp) {

  a.Fp();
  b.bp();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, ff_equals_BB) {

  a.ff();
  b.BB();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, FF_equals_bb) {

  a.FF();
  b.bb();

  ASSERT_EQ(a, b);
}

/********************************************************************/
/********************* Right/left rotation tests ********************/
/********************************************************************/
TEST_F(CubeTwistTest, r_equals_L) {

  a.r();
  b.L();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, R_equals_l) {

  a.R();
  b.l();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, rp_equals_Lp) {

  a.rp();
  b.Lp();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, Rp_equals_lp) {

  a.Rp();
  b.lp();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, rr_equals_LL) {

  a.rr();
  b.LL();

  ASSERT_EQ(a, b);
}

TEST_F(CubeTwistTest, RR_equals_ll) {

  a.RR();
  b.ll();

  ASSERT_EQ(a, b);
}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  const int testResults = RUN_ALL_TESTS();

  return testResults;
}
