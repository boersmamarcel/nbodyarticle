#include "particle.h"

#include <iostream>
#include <OpenGL/gl.h>

Particle::Particle()
{
    _position = Vec3D::createRandom(-10, 10);
    _velocity = Vec3D::createRandom(-0.1, 0.1);
    _mass = 1;
}

void Particle::calculateAcceleration(const std::vector<Particle>& particles, float timestep)
{
    //set acceleration to zero vector
    _acceleration = Vec3D();

    _potentialEnergy = 0;
    const float G = 0.01;

    for (const auto& particle: particles)
    {
        if (&particle == this)
            continue;

        Vec3D positionDelta = (particle._position - _position);
        float l = positionDelta.length();
        _potentialEnergy += 1 / (l*l);
        _acceleration +=  (positionDelta * timestep * G) / (l*l*l);

    }
}

void Particle::update(float timestep)
{
    _position += _velocity * timestep;
    _velocity += _acceleration * timestep;

    const int historySize = 20;
    _positionHistory.push_back(_position);
    if (_positionHistory.size() > historySize)
    {
        _positionHistory.pop_front();
    }
}

void Particle::render()
{
    float redness = _potentialEnergy / 100;
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
