#include "../third_party/googletest-1.14/googletest/include/gtest/gtest.h"
#include "../include/read_file.hpp"

TEST(ReadFrameRateFromFile, read_file_test1) {
    ReadFile readObj;
    EXPECT_EQ(readObj.read_file("/home/daniel/Desktop/opengles-workspace/src/data.txt"), 60);
}

TEST(ReadFrameRateFromFile, read_file_test2) {
    ReadFile readObj;
    EXPECT_FALSE(false);
}