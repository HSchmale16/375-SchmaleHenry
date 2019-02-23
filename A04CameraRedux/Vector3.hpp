#ifndef VECTOR_H_INC
#define VECTOR_H_INC

#include <iostream>

class Vector3 {
public:
    Vector3();

    Vector3(float xyz);

    Vector3(float x, float y, float z);

    void
    set(float xyz);

    void
    set(float x, float y, float z);

    float
    dot(const Vector3& v) const;

    float
    angleBetween (const Vector3& v) const;

    Vector3
    cross (const Vector3& v) const;

    float
    length () const;

    void
    normalize ();

    Vector3&
    operator += (const Vector3& v);

    Vector3&
    operator -= (const Vector3& v);

    Vector3&
    operator *= (float s);

    Vector3&
    operator /= (float s);


    float x,y,z;
};

Vector3
operator+ (const Vector3& v1, const Vector3& v2);

Vector3
operator- (const Vector3& v1, const Vector3& v2);

Vector3
operator- (const Vector3& v);

Vector3
operator* (float s, const Vector3& v);

Vector3
operator* (const Vector3& v, float s);

Vector3
operator/ (const Vector3& v, float s);

std::ostream&
operator<< (std::ostream& out, const Vector3& v);

bool
operator== (const Vector3& v1, const Vector3& v2);


#endif // VECTOR_H_INC
