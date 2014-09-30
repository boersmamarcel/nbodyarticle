#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <vector>
#include <deque>
#include "vec.h"

class Particle
{
    public:
        Particle();
        void calculateAcceleration(const std::vector<Particle>& particles, float timestep);
        void update(float timestep);
        void render();
        Vec3D _position;
        Vec3D momentum();
        float kineticEnergy();
        float mass() const {return _mass;}
        float potentialEnergy() {return _potentialEnergy;}
    private:
        std::deque<Vec3D> _positionHistory;
        float _potentialEnergy;
        Vec3D _velocity;
        Vec3D _acceleration;
        float _mass;
};

#endif // PARTICLE_H_
