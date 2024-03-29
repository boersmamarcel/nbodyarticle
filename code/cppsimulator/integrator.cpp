#include "integrator.h"
#include "particle.h"
#include <cmath>
#include <iostream>
#include <algorithm>

#define GLOBAL_MINIMUM_TIMESTEP 0.1
#define GLOBAL_MAXIMUM_TIMESTEP 0.001

Integrator::Integrator() :
    timestep(0.1)
{
}

void Integrator::jerkIntegrator(std::vector<Particle>& particles, bool dynamic_time, float initial_timestep)
{
    float globalMin;
    //run simulation
    for(auto& particle: particles)
    {
        particle._jerk = Vec3D();
        particle._potentialEnergy = 0;
        const float G = 0.01;

        for (const auto& p: particles)
        {
            if (&p == &particle)
                continue;

            Vec3D positionDelta = (p._position - particle._position);
            Vec3D velocityDelta = p._velocity - particle._velocity;
            float l = positionDelta.length() + 0.1;
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

    timestep = (dynamic_time)?fmin(globalMin, GLOBAL_MINIMUM_TIMESTEP):initial_timestep;
    timestep = (dynamic_time)?fmin(timestep, GLOBAL_MAXIMUM_TIMESTEP):initial_timestep;

    for(auto& particle: particles)
    {
        //Taylor expansion around the current point
        particle._position = particle._position +  particle._velocity * timestep + particle._acceleration*timestep*timestep/2 + (particle._jerk*timestep*timestep*timestep)/6;
        particle._velocity = particle._velocity + particle._acceleration * timestep + (particle._jerk*timestep*timestep)/2;

        const int historySize = 40;
        particle._positionHistory.push_back(particle._position);
        if (particle._positionHistory.size() > historySize)
        {
            particle._positionHistory.pop_front();
        }
    }
}

void Integrator::naiveIntegrator(std::vector<Particle>& particles, bool dynamic_time, float initial_timestep)
{
    //run simulation
    float globalMin;
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
            float l = positionDelta.length() + 0.1;
            particle._potentialEnergy += (particle._mass * p.mass() * G) / (l*l);
            Vec3D accelerationDelta = (positionDelta * timestep * G * particle.mass()) / (l*l*l);
            particle._acceleration += accelerationDelta;

            float minV = positionDelta.length() / velocityDelta.length();
            float minA = sqrt(positionDelta.length() / accelerationDelta.length());

            globalMin = minV < globalMin ? minV : globalMin;
            globalMin = minA < globalMin ? minA : globalMin;
    }

    
    }

    timestep = (dynamic_time)?fmin(globalMin, GLOBAL_MINIMUM_TIMESTEP):initial_timestep;
    timestep = (dynamic_time)?fmin(timestep, GLOBAL_MAXIMUM_TIMESTEP):initial_timestep;

    for(auto& particle: particles)
    {
        //Taylor expansion around the current point
        particle._position = particle._position +  particle._velocity * timestep;
        particle._velocity = particle._velocity + particle._acceleration * timestep;

        const int historySize = 40;
        particle._positionHistory.push_back(particle._position);
        if (particle._positionHistory.size() > historySize)
        {
            particle._positionHistory.pop_front();
        }
    }
}

void Integrator::leapfrogIntegrator(std::vector<Particle>& particles, bool dynamic_time, float initial_timestep)
{
    //run simulation
    float globalMin;
    for(auto& particle: particles)
    {
        particle._prevAcceleration = particle._acceleration;
        particle._acceleration = Vec3D();

        particle._potentialEnergy = 0;
        const float G = 0.01;

        for (const auto& p: particles)
        {
            if (&p == &particle)
                continue;

            Vec3D positionDelta = (p._position - particle._position);
            Vec3D velocityDelta = p._velocity - particle._velocity;
            float l = positionDelta.length() + 0.1;
            particle._potentialEnergy += (particle._mass * p.mass() * G) / (l*l);
            Vec3D accelerationDelta = (positionDelta * timestep * G * particle.mass()) / (l*l*l);
            particle._acceleration += accelerationDelta;

            float minV = positionDelta.length() / velocityDelta.length();
            float minA = sqrt(positionDelta.length() / accelerationDelta.length());

            globalMin = minV < globalMin ? minV : globalMin;
            globalMin = minA < globalMin ? minA : globalMin;
    }

    
    }

    timestep = (dynamic_time)?fmin(globalMin, GLOBAL_MINIMUM_TIMESTEP):initial_timestep;
    timestep = (dynamic_time)?fmin(timestep, GLOBAL_MAXIMUM_TIMESTEP):initial_timestep;

    for(auto& particle: particles)
    {
        //Taylor expansion around the current point
        particle._position = particle._position +  particle._velocity * timestep + particle._prevAcceleration * 0.5 * timestep * timestep;
        particle._velocity = particle._velocity + (particle._acceleration + particle._prevAcceleration) * 0.5 * timestep;

        const int historySize = 40;
        particle._positionHistory.push_back(particle._position);
        if (particle._positionHistory.size() > historySize)
        {
            particle._positionHistory.pop_front();
        }
    }
}
