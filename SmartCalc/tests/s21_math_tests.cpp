#include "tests.h"

Model calc;

void test(const std::string &expression, const long double &expect) {
  long double result = calc.calculate(expression, 0);
  if (isinf(expect) || isinf(result)) {
    ASSERT_DOUBLE_EQ(expect, std::numeric_limits<long double>::infinity());
    ASSERT_DOUBLE_EQ(result, std::numeric_limits<long double>::infinity());
  } else if (isnan(expect) || isnan(result)) {
    ASSERT_EQ(isnan(expect), isnan(result));
  } else
    ASSERT_FLOAT_EQ(result, expect);
}

TEST(MathSuite, X) {
  ASSERT_FLOAT_EQ(calc.calculate("x+3", 1), 4);
  ASSERT_FLOAT_EQ(calc.calculate("sin(x)", 2), sin(2));
  ASSERT_FLOAT_EQ(calc.calculate("-x+2", 2), 0);
}

TEST(MathSuite, Add) {
  test(" 2+2+3", 2. + 2. + 3.);
  test("-2.25+2.25+3.73", -2.25 + 2.25 + 3.73);
  test("421451243.24124+512425.2151243+4421.73",
       421451243.24124 + 512425.2151243 + 4421.73);
}

TEST(MathSuite, uuMinus) {
  test("2+-2+3", 2. + -2. + 3.);
  test("-2.25+(-2.25)+3.73", -2.25 + (-2.25) + 3.73);
  test("421451243.24124+-512425.2151243+4421.73",
       421451243.24124 + -512425.2151243 + 4421.73);
}

TEST(MathSuite, Sub) {
  test("2-2-3", 2. - 2. - 3.);
  test("-2.25-+2.25-3.73", -2.25 - +2.25 - 3.73);
  test("421451243.24124-512425.2151243-4421.73",
       421451243.24124 - 512425.2151243 - 4421.73);
}

TEST(MathSuite, Mul) {
  test("2*2*3", 2. * 2. * 3.);
  test("-2.25*2.25*3.73", -2.25 * 2.25 * 3.73);
  test("421451243.24124*512425.2151243*4421.73",
       421451243.24124 * 512425.2151243 * 4421.73);
}

TEST(MathSuite, Div) {
  test("2/2/3", 2. / 2. / 3.);
  test("-2.25/2.25/3.73", -2.25 / 2.25 / 3.73);
  test("421451243.24124/512425.2151243/4421.73",
       421451243.24124 / 512425.2151243 / 4421.73);
}

TEST(MathSuite, Pow) {
  test("2^2^3", pow(pow(2., 2.), 3.));
  test("-2.25^2.25^3.73", pow(pow(-2.25, 2.25), 3.73));
  test("3.24124^5.2151243^1.7233", pow(pow(3.24124, 5.2151243), 1.7233));
}

TEST(MathSuite, Mod) {
  test("2mod2mod3", (double)(2 % 2 % 3));
  test("-5.25mod2.25mod3.73", fmod(fmod(-5.25, 2.25), 3.73));
  test("3.24124mod5.2151243mod1.7233", fmod(fmod(3.24124, 5.2151243), 1.7233));
}

TEST(MathSuite, uPlus) {
  test("+2", 2.);
  test("+5.25", 5.25);
  test("+421451243.24124", 421451243.24124);
}

TEST(MathSuite, uMinus) {
  test("-2", -2.);
  test("-5.25", -5.25);
  test("-421451243.24124", -421451243.24124);
}

TEST(MathSuite, Cos) {
  long double num1 = 2;
  long double num2 = -5.25;
  long double num3 = -42145.24124;
  test("cos(2)", cosl(num1));
  test("cos(-5.25)", cosl(num2));
  test("cos(-42145.24124)", cosl(num3));
}

TEST(MathSuite, Sin) {
  test("sin(2)", sin(2));
  test("sin(-5.25)", sin(-5.25));
  test("sin(-42145.24124)", sin(-42145.24124));
}

TEST(MathSuite, Tan) {
  test("tan(2)", tan(2));
  test("tan(-5.25)", tan(-5.25));
  test("tan(-42145.24124)", tan(-42145.24124));
}

TEST(MathSuite, Acos) {
  test("acos(0.2)", acos(0.2));
  test("acos(-0.525)", acos(-0.525));
  test("acos(-0.4214524124)", acos(-0.4214524124));
}

TEST(MathSuite, Asin) {
  test("asin(0.2)", asin(0.2));
  test("asin(-0.525)", asin(-0.525));
  test("asin(-0.4214524124)", asin(-0.4214524124));
}

TEST(MathSuite, Atan) {
  test("atan(0.2)", atan(0.2));
  test("atan(-0.525)", atan(-0.525));
  test("atan(-0.4214524124)", atan(-0.4214524124));
}

TEST(MathSuite, Sqrt) {
  test("sqrt(2)", sqrt(2));
  test("sqrt(5.25)", sqrt(5.25));
  test("sqrt(42145.24124)", sqrt(42145.24124));
}

TEST(MathSuite, Ln) {
  test("ln(2)", log(2));
  test("ln(5.25)", log(5.25));
  test("ln(42145.24124)", log(42145.24124));
}

TEST(MathSuite, Log) {
  test("log(2)", log10(2));
  test("log(5.25)", log10(5.25));
  test("log(42145.24124)", log10(42145.24124));
}

TEST(MathSuite, Brackets) {
  test("(2+2)*2", (2. + 2.) * 2.);
  test("sqrt(25)+2", sqrt(25) + 2.);
  test("(sqrt(25)+2)*(2+2)", (sqrt(25) + 2.) * (2. + 2.));
}

// TEST(MathSuite, Nan) { test("0/0", 0.0 / 0.0); }

// TEST(MathSuite, Inf) { test("2/0", 2.0 / 0.0); }

TEST(MathSuite, Exp) {
  test("1242.24e-6+214E5", 1242.24e-6 + 214E5);
  test("(sqrt(0.25e2)+2)*(0.0002e4+2)", (sqrt(0.25e2) + 2) * (0.0002e4 + 2));
}

TEST(MathSuite, LargeExpr) {
  test("15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
       "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))",
       15. / (7. - (1. + 1.)) * 3. -
           (2. + (1. + 1.)) * 15. / (7. - (200. + 1.)) * 3. -
           (2. + (1. + 1.)) * (15. / (7. - (1. + 1.)) * 3. - (2. + (1. + 1.)) +
                               15. / (7. - (1. + 1.)) * 3. - (2. + (1. + 1.))));
}

TEST(MathSuite, Exceptions) {
  ASSERT_THROW(calc.calculate("2+(2-2", 0), MathException);
  ASSERT_THROW(calc.calculate("2+2)-2", 0), MathException);
  ASSERT_THROW(calc.calculate("2+2.2.2-2", 0), MathException);
  ASSERT_THROW(calc.calculate("", 0), MathException);
  ASSERT_THROW(calc.calculate("sss(2)", 0), MathException);
  ASSERT_THROW(calc.calculate("(3*)", 0), MathException);
  ASSERT_THROW(calc.calculate("3/0", 0), MathException);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
