//
// Created by 2ToThe10th
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "ClassForTest.h"

TEST(OneLetter, A) {
  ClassForTest test("a*", "aaaaa");
  EXPECT_EQ(test.Do(), 5);
}
TEST(OneLetter, B) {
  ClassForTest test("b*", "bbbb");
  EXPECT_EQ(test.Do(), 4);
}
TEST(OneLetter, C) {
  ClassForTest test("c*", "cccccc");
  EXPECT_EQ(test.Do(), 6);
}
TEST(Middle, First) {
  ClassForTest test("c*bb..", "cccacccbb");
  EXPECT_EQ(test.Do(), 5);
}
TEST(Middle, Second) {
  ClassForTest test("a*b.a*.", "aaabaaabaa");
  EXPECT_EQ(test.Do(), 6);
}
TEST(Middle, Third) {
  ClassForTest test("ab.*", "ababbbbbabcabababa");
  EXPECT_EQ(test.Do(), 0);
}
TEST(Middle, Forth) {
  ClassForTest test("ab.*", "ababbbbbabcbababab");
  EXPECT_EQ(test.Do(), 7);
}
TEST(Middle, Fifth) {
  ClassForTest test("ab+*", "aacbcabacabbaababb");
  EXPECT_EQ(test.Do(), 9);
}
TEST(Middle, Sixth) {
  ClassForTest test("ab.c.", "aacbcabacabbaababbc");
  EXPECT_EQ(test.Do(), 2);
}
TEST(Middle, Seventh) {
  ClassForTest test("ab.c.", "aacbcabacabbaabababc");
  EXPECT_EQ(test.Do(), 3);
}
TEST(Middle, Eighth) {
  ClassForTest test("ab.c.", "aacbcabacabbaabababcaa");
  EXPECT_EQ(test.Do(), 0);
}
TEST(Hard, First) {
  ClassForTest test("ab+c+*ab+*c..", "aacbcabacabbaacbababc");
  EXPECT_EQ(test.Do(), 21);
}
TEST(Hard, Second) {
  ClassForTest test("ab.cb.ac.++*", "bbcabcb");
  EXPECT_EQ(test.Do(), 5);
}