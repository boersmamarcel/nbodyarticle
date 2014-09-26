#include "vec.h"

#include <cstdlib>

Vec3D::Vec3D():
   _x(0), _y(0), _z(0) 
{
}

Vec3D::Vec3D(float x, float y, float z):
   _x(x), _y(y), _z(z) 
{
}

Vec3D Vec3D::createRandom(Vec3D min, Vec3D max)
{
    float x = ((max._x-min._x)*((float)rand()/RAND_MAX))+min._x;
    float y = ((max._y-min._y)*((float)rand()/RAND_MAX))+min._y;
    float z = ((max._z-min._z)*((float)rand()/RAND_MAX))+min._z;
    return Vec3D(x, y, z);
}

Vec3D Vec3D::createRandom(float min, float max)
{
    return createRandom(Vec3D(min, min, min), Vec3D(max, max, max));
}


Vec3D Vec3D::operator*(float scalar)
{
    return Vec3D(_x*scalar, _y*scalar, _z*scalar);
}

Vec3D& Vec3D::operator+=(const Vec3D& vec)
{
    _x += vec._x;
    _y += vec._y;
    _z += vec._z;
    return (*this);
}
