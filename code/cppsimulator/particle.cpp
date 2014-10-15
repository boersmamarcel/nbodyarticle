#include "particle.h"

#include <iostream>
#include <OpenGL/gl.h>

Particle::Particle()
{
    _position = Vec3D::createRandom(-10, 10);
    _velocity = Vec3D::createRandom(-1, 1);
    _mass = 1;
}



void Particle::calculateAcceleration(const std::vector<Particle>& particles, float timestep)
{
    //set acceleration to zero vector
    _jerk = Vec3D();
    _acceleration = Vec3D();

    _potentialEnergy = 0;
    const float G = 0.01;

    for (const auto& particle: particles)
    {
        if (&particle == this)
            continue;

        Vec3D positionDelta = (particle._position - _position);
        Vec3D velocityDelta = particle._velocity - _velocity;
        float l = positionDelta.length();
        _potentialEnergy += (_mass * particle.mass() * G) / (l*l);
        _jerk += (((velocityDelta)/(l*l*l)) - ((positionDelta*(positionDelta*velocityDelta))/(l*l*l*l*l))*3)*particle.mass();
        _acceleration +=  (positionDelta * timestep * G * particle.mass()) / (l*l*l);

    }

    //Taylor expansion around the current point
    _acceleration = _acceleration + _jerk*timestep;
    
}

void Particle::update(float timestep)
{

    //Taylor expansion around the current point
    _position = _position +  _velocity * timestep + _acceleration*timestep*timestep/2 + (_jerk*timestep*timestep*timestep)/6;
    _velocity = _velocity + _acceleration * timestep + (_jerk*timestep*timestep)/2;

    const int historySize = 20;
    _positionHistory.push_back(_position);
    if (_positionHistory.size() > historySize)
    {
        _positionHistory.pop_front();
    }
}

void Particle::render()
{
    float redness = _potentialEnergy / 10;
    if (redness > 1)
        redness = 1;
    glColor3f(1,1-redness,1-redness);
    glBegin(GL_POINTS);
    glVertex3f(_position.x(), _position.y(), _position.z());
    glEnd();

    glBegin(GL_LINE_STRIP);
    int i = 0;
    for (auto position: _positionHistory)
    {
        float c = float(i) / _positionHistory.size();
        glColor3f(c,c,c);
        i++;
        glVertex3f(position.x(), position.y(), position.z());
    }
    glEnd();
}

Vec3D Particle::momentum()
{
    return _velocity * _mass;
}

float Particle::kineticEnergy()
{
    float v = _velocity.length();
    return 0.5 * _mass * v * v;
}
