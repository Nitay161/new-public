#include <gtest/gtest.h>
#include "../src/compression/Compressor.h"

// Sanity tests for compress function.
TEST(CompressorTest, CompressingCorrectly) {
    EXPECT_EQ(compress("ttthhiiiiss iss teesssst"), "t3h2i4s2 1i1s2 1t1e2s4t1");
    EXPECT_EQ(compress("test number two"), "t1e1s1t1 1n1u1m1b1e1r1 1t1w1o1");
    EXPECT_EQ(compress("AAAAAbbUUU tTTeEEesSSt"), "A5b2U3 1t1T2e1E2e1s1S2t1");
}

// Sanity tests for decompress function.
TEST(CompressorTest, DecompressingCorrectly) {
    EXPECT_EQ(decompress("t3h2i4s2 1i1s2 1t1e2s4t1"), "ttthhiiiiss iss teesssst");
    EXPECT_EQ(decompress("t1e1s1t1 1n1u1m1b1e1r1 1t1w1o1"), "test number two");
    EXPECT_EQ(decompress("A5b2U3 1t1T2e1E2e1s1S2t1"), "AAAAAbbUUU tTTeEEesSSt");
}

// Negative tests for decompress function. Thetext should be in RLE format.
TEST(CompressorTest, NonRLEDecompression) {
    EXPECT_THROW(decompress("t3h"), invalid_argument);
    EXPECT_THROW(decompress("t3h22"), invalid_argument);
    EXPECT_THROW(decompress("t3h5qq"), invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}