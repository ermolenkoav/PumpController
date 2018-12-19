#include <gtest/gtest.h>

int add(int a, int b) {
	return a + b;
}

bool EvenDivide(int a) {
	return ((a%2) == 0);
}

TEST(addTestTest, add) {
	EXPECT_EQ(1, add(2, -1));
	EXPECT_EQ(5, add(2, 3));
}

TEST(EvenDivideTest, HandlesPositiveInput) {
	ASSERT_TRUE(EvenDivide(0));
	ASSERT_FALSE(EvenDivide(1));
	ASSERT_TRUE(EvenDivide(2));
	ASSERT_TRUE(EvenDivide(1));
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TEST();
}