#include <gtest/gtest.h>

#include "my_math.h"

// Define your test cases and test functions using the TEST macro
TEST(MyTestCase, MyTestFunction) {
  // Test assertions
  EXPECT_EQ(2 + 2, 4);
  ASSERT_TRUE(true);
}

TEST(MyTestCase, MySqrt) {
  // Test assertions
  EXPECT_EQ(6.0, mySqrt(36.0));
  ASSERT_TRUE(true);
}

// Run the tests
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}