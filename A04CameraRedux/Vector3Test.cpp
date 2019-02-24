#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vector3.h"
#include <cmath>

TEST_CASE("Vector3()", "[vector3]") {
    Vector3 a;

    REQUIRE(a.x == 0);
    REQUIRE(a.y == 0);
    REQUIRE(a.z == 0);
}

TEST_CASE("Vector3(float xyz)", "[vector3]") {
    const float value = 5.f;
    Vector3 a(value);

    REQUIRE(a.x == value);
    REQUIRE(a.y == value);
    REQUIRE(a.z == value);
}


TEST_CASE("Vector3(x, y, z)", "[vector3]") {
    const float v1 = 5.f, v2 = 3.f, v3 = 1.f;
    Vector3 a(v1, v2, v3);

    REQUIRE(a.x == v1);
    REQUIRE(a.y == v2);
    REQUIRE(a.z == v3);
}

TEST_CASE("Set All", "[vector3]") {
    Vector3 a;
    REQUIRE(a.x == 0);
    REQUIRE(a.y == 0);
    REQUIRE(a.z == 0);

    const float value = 5.f;
    a.set(value);

    REQUIRE(a.x == value);
    REQUIRE(a.y == value);
    REQUIRE(a.z == value);
}

TEST_CASE("Set different", "[vector3]") {
    const float v1 = 5.f, v2 = 3.f, v3 = 1.f;
    Vector3 a;

    a.set(v1, v2, v3);

    REQUIRE(a.x == v1);
    REQUIRE(a.y == v2);
    REQUIRE(a.z == v3);
}

TEST_CASE("Negate", "[vector3]") {
    const float v1 = 5.f, v2 = 3.f, v3 = 1.f;
    Vector3 a(v1, v2, v3);

    a.negate();

    REQUIRE(a.x == -v1);
    REQUIRE(a.y == -v2);
    REQUIRE(a.z == -v3);
}

TEST_CASE("dot", "[vector3]") {
    Vector3 a, b(1,2,3), c(5,6,7), ones(1);

    SECTION ("Dot product of a zero vector is always zero") {
        REQUIRE(a.dot(b) == 0);
        REQUIRE(b.dot(a) == 0);
    }

    SECTION ("Dot product of 2 normal vectors") {
        REQUIRE(b.dot(c) == (float)(5 + 2 * 6 + 3 * 7));
        REQUIRE(c.dot(b) == (float)(5 + 2 * 6 + 3 * 7));
    }



}

TEST_CASE("angleBetween", "[vector3]") {

}


TEST_CASE("cross", "[vector3]") {
    // Based on examples found here: 
    // https://www.mathsisfun.com/algebra/vectors-cross-product.html

    SECTION ("mathisfun") {
        Vector3 a(2,3,4), b(5,6,7), expected(-3, 6, -3);

        REQUIRE( a.cross(b) == expected);
        REQUIRE( b.cross(a) == -expected);
    }
}


TEST_CASE("length", "[vector3]") {
    const Vector3 ones(1), twos(2), a(1,2,3);
    
    SECTION("Ones vector length is sqrt(3)") {
        REQUIRE(ones.length() == (float)sqrt(3.f));
    }

    SECTION("Twos Vector is sqrt(12)") {
        REQUIRE(twos.length() == (float)sqrt(12.f));
    }

    SECTION("1,2,3 is sqrt(14)") {
        REQUIRE(a.length() == (float)sqrt(14.f));
    }
}


TEST_CASE ("normalize", "[vector3]") {

}


TEST_CASE ("Add Assign", "[vector3]") {
    
}

TEST_CASE ("Minus Assign", "[vector3]") {
}

TEST_CASE ("Scaler Multiply Assign", "[vector3]") {
    const float scalar = 5.f;

    SECTION("Ones") {
        Vector3 ones(1.f);
        const Vector3 expected(scalar);

        ones *= scalar;

        REQUIRE(ones == expected);
    }
}

TEST_CASE("Scalar Divide Assign", "[vector3]") {
}

TEST_CASE("Infix Add Create New", "[vector3]") {

}

TEST_CASE ("Infix Subtract Create New", "[vector3]") {
}

TEST_CASE ("Unary Negation", "[vector3]") {
    const float value = 5.f;

    SECTION ("All same value") {
        Vector3 a(value), b(-value);

        REQUIRE(-a == b);
        REQUIRE(b == -a);
        REQUIRE(a == -b);
        REQUIRE(-b == a);
    }

    SECTION ("All different value") {
        Vector3 a(1.f, 2.f, 3.f), b(-1.f, -2.f, -3.f);

        REQUIRE(-a == b);
        REQUIRE(b == -a);
        REQUIRE(a == -b);
        REQUIRE(-b == a);
    }
}

TEST_CASE ("Infix Scalar Multiply", "[vector3]") {
    SECTION ("float vec3") {
        
    }

    SECTION ("vec3 float") {

    }
}

TEST_CASE ("Infix Scalar Divide" "[vector3]") {
    SECTION ("float vec3") {

    }

    SECTION ("vec3 float") {

    }
}

TEST_CASE("equality testing", "[vector3]") {
    Vector3 ones(1.f), twos(2.f), another_one(1.f);

    REQUIRE(ones == ones);
    REQUIRE(twos == twos);
    REQUIRE(ones == another_one);

    // Diffs should be false
    REQUIRE(!(ones == twos));
}




