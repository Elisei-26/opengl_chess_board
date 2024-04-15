#include "gtest/gtest.h"
#include "../include/read_file.hpp"

TEST(ReadFrameRateFromFile, read_file_test1) {
    ReadFile readObj;
    EXPECT_EQ(readObj.read_file("src/data.txt"), 200);
}

TEST(ReadFrameRateFromFile, read_file_test2) {
    ReadFile readObj;
    EXPECT_FALSE(false);
}