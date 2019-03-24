#include "catch.hpp"
#include "Matrix3.h"

/**
 *
 * Matrix3Test.cpp
 *
 * Henry J Schmale
 * Tests my Matrix 3 class
 * CSCI 375 Computer Graphics
 * Spring 2019
 */

TEST_CASE("default ctor is identity", "[matrix3]") {
    Matrix3 testing;

    
}

TEST_CASE("determinant", "[matrix3]") {
    // https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix
    const float expected = 74.f;    
    Matrix3 mat (1, 2, 4, 5, 4, 6, 3, 7, 2);

    REQUIRE(mat.determinant() == expected);
}

TEST_CASE("Times Equals Mat3 is MatMul", "[matrix3]") {
    Matrix3 expected(30, 66, 102, 36, 81, 126, 42, 96, 150);
    Matrix3 input(1,4,7,2,5,8,3,6,9);
    Matrix3 res (input);

    res *= input;
    REQUIRE(res == expected);
}
