#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include "vec.h"

class Particle
{
    public:
        Particle();
        void calculateAcceleration(const std::vector<Particle>& particles, float timestep);
        void update(float timestep);
        void render();
        Vec3D _position;
    private:
        Vec3D _velocity;
        Vec3D _acceleration;
};

#endif // PARTICLE_H_
