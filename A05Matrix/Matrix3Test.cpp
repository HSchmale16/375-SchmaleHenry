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
}

TEST_CASE("element ctor", "[matrix3]") {

}

TEST_CASE("vector ctor", "[matrix3]") {

}

TEST_CASE("vector and orthonormalize", "[matrix3]") {

}

TEST_CASE("set to identity", "[matrix3]") {
    Matrix3 t;
    t.setToIdentity();

    REQUIRE(t.getRight().x == 1.f);
    REQUIRE(t.getUp().x    == 0.f);
    REQUIRE(t.getBack().x  == 0.f);
    REQUIRE(t.getRight().y == 0.f);
    REQUIRE(t.getUp().y    == 1.f);
    REQUIRE(t.getBack().y  == 0.f);
    REQUIRE(t.getRight().z == 0.f);
    REQUIRE(t.getUp().z    == 0.f);
    REQUIRE(t.getBack().z  == 1.f);

}

TEST_CASE("setToZero", "[matrix3]") {
    Matrix3 t;
    t.setToZero();

    REQUIRE(t.getRight().x == 0.f);
    REQUIRE(t.getUp().x    == 0.f);
    REQUIRE(t.getBack().x  == 0.f);
    REQUIRE(t.getRight().y == 0.f);
    REQUIRE(t.getUp().y    == 0.f);
    REQUIRE(t.getBack().y  == 0.f);
    REQUIRE(t.getRight().z == 0.f);
    REQUIRE(t.getUp().z    == 0.f);
    REQUIRE(t.getBack().z  == 0.f);
}

TEST_CASE("data", "[matrix3]") {
    // no real way to test this. Pretty much addr of
}

TEST_CASE("const data", "[matrix3]") {
    // no real way to test this. Pretty much addr of
}

TEST_CASE("get/set right", "[matrix3]") {
    Matrix3 test;
    Vector3 set(5,4,3);

    REQUIRE(!(test.getRight() == set));
    
    test.setRight(set);

    REQUIRE(test.getRight() == set);
}

TEST_CASE("get/set up", "[matrix3]") {
    Matrix3 test;
    Vector3 set(5,4,3);

    REQUIRE(!(test.getUp() == set));
    
    test.setUp(set);

    REQUIRE(test.getUp() == set);
}

TEST_CASE("get/set back", "[matrix3]") {
    Matrix3 test;
    Vector3 set(5,4,3);

    REQUIRE(!(test.getBack() == set));
    
    test.setBack(set);

    REQUIRE(test.getBack() == set);
    REQUIRE(test.getForward() == -set); 
}

TEST_CASE("get/set forward", "[matrix3]") {
    Matrix3 test;
    Vector3 set(5,4,3);

    REQUIRE(!(test.getForward() == set));
    
    test.setForward(set);

    REQUIRE(test.getForward() == set); 
    REQUIRE(test.getBack() == -set); 
}

TEST_CASE("invert rotation", "[matrix3]") {

}

TEST_CASE("general invert", "[matrix3]") {

}

TEST_CASE("determinant", "[matrix3]") {
    // https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix
    const float expected = 74.f;    
    Matrix3 mat (1, 2, 4, 5, 4, 6, 3, 7, 2);

    REQUIRE(mat.determinant() == expected);
}

TEST_CASE ("transpose", "[matrix3]") {

}

TEST_CASE ("orthonormalize", "[matrix3]") {

}

TEST_CASE("setToScale", "[matrix3]") {
    SECTION ("single") {

    }

    SECTION("multiplei xyz") {

    }
}

TEST_CASE ("shear x by yz", "[matrix3]") {

}

TEST_CASE("shear y by xz", "[matrix3]") {

}

TEST_CASE("shear z by yx", "[matrix3]") {

}

TEST_CASE("rot x", "[matrix3]") {

}

TEST_CASE("rot y", "[matrix3]") {

}

TEST_CASE("rot z", "[matrix3]") {

}

TEST_CASE("angleAxis", "[matrix3]") {

}

TEST_CASE("negate", "[matrix3]") {

}

TEST_CASE("+=", "[matrix3]") {

}

TEST_CASE("-=", "[matrix3]") {

}

TEST_CASE("*= scalar", "[matrix3]") {
    Matrix3 target;

    Matrix3 expected;

    expected.setToScale(3.f);

    target *= 3.f;


    REQUIRE(expected == target);
}

TEST_CASE("Times Equals Mat3 is MatMul", "[matrix3]") {
    Matrix3 expected(30, 66, 102, 36, 81, 126, 42, 96, 150);
    Matrix3 input(1,4,7,2,5,8,3,6,9);
    Matrix3 res (input);

    res *= input;
    REQUIRE(res == expected);
}
