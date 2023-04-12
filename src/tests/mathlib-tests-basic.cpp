#include "gtest/gtest.h"
#include "testbase.hpp"

#include <exception>

#include "../calc-lib.hpp"

const double precision = 0.00001;

TEST(Add, positiveInts){
    ASSERT_EQ(15, add(10, 5));
}

TEST(Add, negativeInts){
    ASSERT_EQ(-18, add(-10, -8));
}

TEST(Add, mixedInts){
    ASSERT_EQ(5, add(-10, 15));
}

TEST(Add, positiveDoubles){
    ASSERT_NEAR(16.4, add(10.8, 5.6), precision);
}

TEST(Add, negativeDoubles){
    ASSERT_NEAR(-18.7, add(-10.1, -8.6), precision);
}

TEST(Add, mixedDoubles){
    ASSERT_NEAR(5.7, add(-10.1, 15.8), precision);
}


TEST(Subtract, positiveInts){
    ASSERT_EQ(5, subtract(10, 5));
}

TEST(Subtract, negativeInts){
    ASSERT_EQ(-2, subtract(-10, -8));
}

TEST(Subtract, mixedInts){
    ASSERT_EQ(-25, subtract(-10, 15));
}

TEST(Subtract, positiveDoubles){
    ASSERT_NEAR(5.2, subtract(10.8, 5.6), precision);
}

TEST(Subtract, negativeDoubles){
    ASSERT_NEAR(-1.5, subtract(-10.1, -8.6), precision);
}

TEST(Subtract, mixedDoubles){
    ASSERT_NEAR(-25.9, subtract(-10.1, 15.8), precision);
}


TEST(Multiply, positiveInts){
    ASSERT_EQ(15, multiply(3, 5));
}

TEST(Multiply, negativeInts){
    ASSERT_EQ(20, multiply(-4, -5));
}

TEST(Multiply, mixedInts){
    ASSERT_EQ(-15, multiply(-3, 5));
}

TEST(Multiply, zeroInt){
    ASSERT_EQ(0, multiply(10, 0));
}

TEST(Multiply, positiveDoubles){
    ASSERT_NEAR(14.96, multiply(3.4, 4.4), precision);
}

TEST(Multiply, negativeDoubles){
    ASSERT_NEAR(-14.96, multiply(-3.4, 4.4), precision);
}

TEST(Multiply, mixedDoubles){
    ASSERT_NEAR(-14.96, multiply(3.4, -4.4), precision);
}

TEST(Multiply, zeroDouble){
    ASSERT_NEAR(0.0, multiply(10.2, 0.0), precision);
}


TEST(Divide, positiveInts){
    ASSERT_EQ(3, divide(15, 5));
}

TEST(Divide, negativeInts){
    ASSERT_EQ(2, divide(-10, -5));
}

TEST(Divide, mixedInts){
    ASSERT_EQ(-2, divide(-10, 5));
}

TEST(Divide, divideByZeroInt){
    ASSERT_THROW(divide(10, 0), std::runtime_error);
}

TEST(Divide, divideByZeroDouble){
    ASSERT_THROW(divide(10.8, 0.0), std::runtime_error);
}

TEST(Divide, positiveDoubles){
    ASSERT_NEAR(3.054, divide(15.27, 5.0), precision);
}

TEST(Divide, negativeDoubles){
    ASSERT_NEAR(-3.054, divide(-15.27, 5.0), precision);
}

TEST(Divide, mixedDoubles){
    ASSERT_NEAR(-3.054, divide(15.27, -5.0), precision);
}

TEST(Divide, divideZeroDouble){
    ASSERT_NEAR(0.0, divide(0.0, 10.2), precision);
}
