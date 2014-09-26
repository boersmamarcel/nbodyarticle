#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "vec.h"

class Particle
{
    public:
        Particle();
        void update(float timestep);
        void render();
    private:
        Vec3D _position;
        Vec3D _velocity;
        Vec3D _acceleration;
};

#endif // PARTICLE_H_
