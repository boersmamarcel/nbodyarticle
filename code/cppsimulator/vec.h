#ifndef VEC_H_
#define VEC_H_

class Vec3D
{
    public:
        Vec3D(float x, float y, float z);
        Vec3D();
        static Vec3D createRandom(Vec3D min, Vec3D max);
        static Vec3D createRandom(float min, float max);
        Vec3D operator*(float scalar);
        Vec3D operator/(float scalar);
        float operator*(const Vec3D& vec) const;
        Vec3D operator+(const Vec3D& vec) const;
        Vec3D operator-(const Vec3D& vec) const;
        float length();
        void print();

        Vec3D& operator+=(const Vec3D& vec);
        float x() const {return _x;}
        float y() const {return _y;}
        float z() const {return _z;}
    private:
        float _x, _y, _z;
};

#endif // VEC_H_
