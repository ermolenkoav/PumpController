#include <gtest/gtest.h>
#include <gmock/gmock.h>


        int add(int a, int b) {
            return a + b;
        }

        TEST(addTestTest, add) {
            EXPECT_EQ(1, add(2, -1));
            EXPECT_EQ(5, add(2, 3));
        }

        bool EvenDivide(int a) {
            return ((a % 2) == 0);
        }

        TEST(EvenDivideTest, HandlesPositiveInput) {
            ASSERT_TRUE(EvenDivide(0));
            ASSERT_FALSE(EvenDivide(1));
            ASSERT_TRUE(EvenDivide(2));
        }

        bool ToZeroCast(int zero) {
            return (zero == static_cast<char>(0));
        }

        TEST(ToZeroCastTest, ToZeroCast) {
            ASSERT_TRUE(ToZeroCast(0));
        }
