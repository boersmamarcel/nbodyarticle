#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <vector>

class Particle;

class Integrator
{
    public:
        Integrator();
        void naiveIntegrator(std::vector<Particle>& particles, bool dynamic_timestep, float initial_timestep);
        void leapfrogIntegrator(std::vector<Particle>& particles, bool dynamic_timestep, float initial_timestep);
        void jerkIntegrator(std::vector<Particle>& particles, bool dynamic_timestep, float initial_timestep);
        float getTimestep() {return timestep;}
    private:
        float timestep;
};

#endif // INTEGRATOR_H_
