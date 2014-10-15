#include "integrator.h"
#include "particle.h"

void Integrator::jerkIntegrator(std::vector<Particle>& particles)
{
    float timestep = 0.01;
    //run simulation
    for(auto& particle: particles)
    {
        //particle.calculateAcceleration(particles, timestep);
        particle._jerk = Vec3D();
        //_acceleration = Vec3D();

        particle._potentialEnergy = 0;
        const float G = 0.01;

        for (const auto& p: particles)
        {
            if (&p == &particle)
                continue;

            Vec3D positionDelta = (p._position - particle._position);
            Vec3D velocityDelta = p._velocity - particle._velocity;
            float l = positionDelta.length();
            particle._potentialEnergy += (particle._mass * p.mass() * G) / (l*l);
            particle._jerk += (((velocityDelta)/(l*l*l)) - 
                    ((positionDelta*(positionDelta*velocityDelta))/(l*l*l*l*l))*3)*p.mass();
            //_acceleration +=  (positionDelta * timestep * G * particle.mass()) / (l*l*l);

    }

    //Taylor expansion around the current point
    particle._acceleration = particle._acceleration + particle._jerk*timestep;
    
    }
    for(auto& particle: particles)
    {
        //Taylor expansion around the current point
        particle._position = particle._position +  particle._velocity * timestep + particle._acceleration*timestep*timestep/2 + (particle._jerk*timestep*timestep*timestep)/6;
        particle._velocity = particle._velocity + particle._acceleration * timestep + (particle._jerk*timestep*timestep)/2;

        const int historySize = 20;
        particle._positionHistory.push_back(particle._position);
        if (particle._positionHistory.size() > historySize)
        {
            particle._positionHistory.pop_front();
        }
    }
}

void Integrator::naiveIntegrator(std::vector<Particle>& particles)
{
    float timestep = 0.01;
    //run simulation
    for(auto& particle: particles)
    {
        particle._acceleration = Vec3D();

        particle._potentialEnergy = 0;
        const float G = 0.01;

        for (const auto& p: particles)
        {
            if (&p == &particle)
                continue;

            Vec3D positionDelta = (p._position - particle._position);
            Vec3D velocityDelta = p._velocity - particle._velocity;
            float l = positionDelta.length();
            particle._potentialEnergy += (particle._mass * p.mass() * G) / (l*l);
            particle._acceleration +=  (positionDelta * timestep * G * particle.mass()) / (l*l*l);

    }

    
    }
    for(auto& particle: particles)
    {
        //Taylor expansion around the current point
        particle._position = particle._position +  particle._velocity * timestep;
        particle._velocity = particle._velocity + particle._acceleration * timestep;

        const int historySize = 20;
        particle._positionHistory.push_back(particle._position);
        if (particle._positionHistory.size() > historySize)
        {
            particle._positionHistory.pop_front();
        }
    }
}
