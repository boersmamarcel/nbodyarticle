#include "integrator.h"
#include "particle.h"
#include <cmath>
#include <iostream>
#include <algorithm>

Integrator::Integrator() :
    timestep(0.1)
{
}

void Integrator::jerkIntegrator(std::vector<Particle>& particles)
{
    float globalMin;
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
            Vec3D jerkDelta = (((velocityDelta)/(l*l*l)) - 
                    ((positionDelta*(positionDelta*velocityDelta))/(l*l*l*l*l))*3)*p.mass();
            particle._jerk += jerkDelta;

            Vec3D accelerationDelta = jerkDelta * timestep;

            float minV = positionDelta.length() / velocityDelta.length();
            float minA = sqrt(positionDelta.length() / accelerationDelta.length());
            float minJ = powf(positionDelta.length() / jerkDelta.length(), 1.0/3);

            globalMin = minV < globalMin ? minV : globalMin;
            globalMin = minA < globalMin ? minA : globalMin;
            globalMin = minJ < globalMin ? minJ : globalMin;
    }

    //Taylor expansion around the current point
    particle._acceleration = particle._acceleration + particle._jerk*timestep;
    
    }

    timestep = fmin(globalMin, 0.01);

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
    //run simulation
    float globalMin = 1000000000;
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
            Vec3D accelerationDelta = (positionDelta * timestep * G * particle.mass()) / (l*l*l);
            particle._acceleration += accelerationDelta;

            float minV = positionDelta.length() / velocityDelta.length();
            float minA = sqrt(positionDelta.length() / accelerationDelta.length());

            globalMin = minV < globalMin ? minV : globalMin;
            globalMin = minA < globalMin ? minA : globalMin;
    }

    
    }

    timestep = fmin(globalMin, 0.01);

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
