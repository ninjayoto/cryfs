#include "testutils/FuseStatfsReturnTest.h"

using ::testing::WithParamInterface;
using ::testing::Values;

class FuseStatfsReturnBfreeTest: public FuseStatfsReturnTest<fsblkcnt64_t>, public WithParamInterface<fsblkcnt64_t> {
private:
  void set(struct ::statvfs *stat, fsblkcnt64_t value) override {
    stat->f_bfree = value;
  }
};
INSTANTIATE_TEST_CASE_P(FuseStatfsReturnBfreeTest, FuseStatfsReturnBfreeTest, Values(
    0,
    10,
    256,
    1024,
    4096
));

TEST_P(FuseStatfsReturnBfreeTest, ReturnedBfreeIsCorrect) {
  struct ::statvfs result = CallStatfsWithValue(GetParam());
  EXPECT_EQ(GetParam(), result.f_bfree);
}
