#include "Interval.h"
#include "Primes_Calculator.h"
#include "Xml_Loader.h"
#include "settings.h"

#include <string>
#include <vector>
#include "gtest/gtest.h"

TEST(IntervalTest, Invalid_Interval) {
  try {
    Interval in(1, 00);
    FAIL() << "Expected Interval_Exception";
  } catch(Interval_Exception& e) {
    SUCCEED();
  } catch(...) {
    FAIL() << "Expected Interval_Exception";
  }
}

TEST(IntervalTest, One_Value_Interval) {
  try {
    Interval in(0, 0);
    SUCCEED();
  } catch(Interval_Exception& e) {
    FAIL() << "Unexpected Interval_Exception";
  } catch(...) {
    FAIL() << "Unexpected Interval_Exception";
  }
}

TEST(IntervalTest, Valid_Interval) {
  try {
    Interval in(0, 1);
    SUCCEED();
  } catch(Interval_Exception& e) {
    FAIL() << "Unexpected Interval_Exception";
  } catch(...) {
    FAIL() << "Unexpected Interval_Exception";
  }
}

TEST(Xml_LoaderTest, Valid_Xml) {
  const std::string input_filepath = "test1.xml";
  Xml_Loader xl(input_filepath);
  std::vector<Interval> vi{Interval(100,200), Interval(700, 900)};
  ASSERT_EQ(vi, xl.parse<Interval>(interval_xs));
}

TEST(Xml_LoaderTest, Empty_Intervals_In_Xml) {
  const std::string input_filepath = "test2.xml";
  Xml_Loader xl(input_filepath);
  std::vector<Interval> vi;
  ASSERT_EQ(vi, xl.parse<Interval>(interval_xs));
}

TEST(Xml_LoaderTest, Invalid_Interval_Xml) {
  const std::string input_filepath = "test3.xml";
  try {
    Xml_Loader xl(input_filepath);
    xl.parse<Interval>(interval_xs);
    FAIL() << "Expected Xml_Exception";
  } catch (Xml_Exception& xe) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected Xml_Exception";
  }
}

TEST(Primes_CalculatorTest, One_Interval) {
  std::vector<Interval> vi{ Interval{0, 30} };
  Primes_Calculator pc;
  pc.calculate(vi);
  std::vector<int> vp{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  ASSERT_EQ(vp, pc.get_primes());
}

TEST(Primes_CalculatorTest, Two_Disjoin_Intervals) {
  std::vector<Interval> vi{ Interval{0, 20}, Interval{21, 40} };
  Primes_Calculator pc;
  pc.calculate(vi);
  std::vector<int> vp{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  ASSERT_EQ(vp, pc.get_primes());
}

TEST(Primes_CalculatorTest, Two_Overlapping_Intervals) {
  std::vector<Interval> vi{ Interval{10, 40}, Interval{0, 29} };
  Primes_Calculator pc;
  pc.calculate(vi);
  std::vector<int> vp{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  ASSERT_EQ(vp, pc.get_primes());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
