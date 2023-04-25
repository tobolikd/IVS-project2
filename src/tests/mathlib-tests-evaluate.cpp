#include "gtest/gtest.h"

#include <exception>

#include "../calc-lib.hpp"

const double precisionFrac = 0.00001;
const double precisionInt = 0.5;


TEST(Eval, Add) {
    ASSERT_NEAR(evaluateExpression(parseExpression("1+4+3")), 8, precisionFrac);
}

TEST(Eval, Sub) {
    ASSERT_NEAR(evaluateExpression(parseExpression("10-6-2")), 2, precisionFrac);
}

TEST(Eval, Mul) {
    ASSERT_NEAR(evaluateExpression(parseExpression("1*9*5")), 45, precisionFrac);
}

TEST(Eval, Div) {
    ASSERT_NEAR(evaluateExpression(parseExpression("8/2/1")), 4, precisionFrac);
}

TEST(Eval, Fact) {
    ASSERT_NEAR(evaluateExpression(parseExpression("5!")), 120, precisionInt);
}

TEST(Eval, Root) {
    ASSERT_NEAR(evaluateExpression(parseExpression("2√25")), 5, precisionInt);
}

TEST(Eval, Binom) {
    ASSERT_NEAR(evaluateExpression(parseExpression("5C1")), 5, precisionInt);
}

TEST(Eval, Combination) {
    ASSERT_NEAR(evaluateExpression(parseExpression("(5!)/5*2-9+6^2")), 75, precisionInt);
}
