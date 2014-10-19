#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include <deque>
#include "vec.h"

class Particle
{
    public:
        Particle();
        void render();
        Vec3D _position;
        Vec3D momentum();
        float kineticEnergy();
        float mass() const {return _mass;}
        float potentialEnergy() {return _potentialEnergy;}
        friend class Integrator;
    private:
        std::deque<Vec3D> _positionHistory;
        float _potentialEnergy;
        Vec3D _velocity;
        Vec3D _acceleration;
        Vec3D _prevAcceleration;
        float _mass;
        Vec3D _jerk;
};

#endif // PARTICLE_H_
