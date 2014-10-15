#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <vector>

class Particle;

class Integrator
{
    public:
        Integrator();
        void naiveIntegrator(std::vector<Particle>& particles);
        void jerkIntegrator(std::vector<Particle>& particles);
    private:
        float timestep;
};

#endif // INTEGRATOR_H_
