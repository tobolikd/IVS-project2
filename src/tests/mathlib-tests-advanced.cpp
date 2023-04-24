#include "gtest/gtest.h"

#include <exception>
#include <stdexcept>

#include "../calc-lib.hpp"

const double precision = 0.00001;

TEST(Power, positiveInts){
    ASSERT_EQ(125, power(5, 3));
}

TEST(Power, negativeInts){
    ASSERT_EQ(-125, power(-5, 3));
}

TEST(Power, mixedInts){
    ASSERT_EQ(-8, power(-2, 3));
}

TEST(Power, zeroInt){
    ASSERT_EQ(1, power(-10, 0));
}

TEST(Power, positiveDouble){
    ASSERT_NEAR(2.25, power(1.5, 2), precision);
}

TEST(Power, negativeDouble){
    ASSERT_NEAR(-3.375, power(-1.5, 3), precision);
}

TEST(Power, zeroDouble){
    ASSERT_NEAR(1.0, power(10.2, 0), precision);
}

TEST(Power, zeroZero){
    ASSERT_THROW(power(0, 0), std::runtime_error);
}

TEST(Factorial, Zero){
    ASSERT_EQ(1, factorial(0));
}

TEST(Factorial, PositiveInteger){
    ASSERT_EQ(24, factorial(4));
}

TEST(Factorial, NegativeInteger){
    ASSERT_THROW(factorial(-5), std::runtime_error);
}

TEST(Factorial, LargeNumber){
    ASSERT_EQ(6'227'020'800, factorial(13));
}


TEST(Root, PositiveNumber_PositiveRoot){
    ASSERT_NEAR(3.0, root(27.0, 3.0), precision);
    ASSERT_NEAR(2.0, root(16.0, 4.0), precision);
    ASSERT_NEAR(2.0, root(8.0, 3.0), precision);
}

TEST(Root, Zero){
    ASSERT_NEAR(0.0, root(0.0, 5.0), precision);
}

TEST(Root, NegativeNumber_PositiveEvenRoot){
    ASSERT_THROW(root(-8.0, 6.0), std::runtime_error);
}

TEST(Root, NegativeNumber_PositiveOddRoot){
    ASSERT_NEAR(-3.0, root(-27.0, 3.0), precision);
    ASSERT_NEAR(-2.0, root(-8.0, 3.0), precision);
}

TEST(Root, NegativeNumber_NegativeEvenRoot){
    ASSERT_THROW(root(-27.0, -2.0), std::runtime_error);
}

TEST(Root, NegativeNumber_NegativeOddRoot){
    ASSERT_THROW(root(-27.0, -3.0), std::runtime_error);
}

TEST(BinomialCoefficient, ValidInput) {
    ASSERT_EQ(binomial_coefficient(5, 2), 10);
}

TEST(BinomialCoefficient, LargeNumber) {
    ASSERT_NEAR(binomial_coefficient(50, 20), 47'129'212'243'960, 0.5);
}

TEST(BinomialCoefficient, n_LessThan_k) {
    ASSERT_THROW(binomial_coefficient(5, 10), std::runtime_error);
}

TEST(BinomialCoefficient, Negative_n) {
    ASSERT_THROW(binomial_coefficient(-5, 2), std::runtime_error);
}

TEST(BinomialCoefficient, Negative_k) {
    ASSERT_THROW(binomial_coefficient(5, -2), std::runtime_error);
}

