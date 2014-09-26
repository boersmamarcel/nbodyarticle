#include "particle.h"

#include <iostream>
#include <OpenGL/gl.h>

Particle::Particle()
{
    _position = Vec3D::createRandom(-10, 10);
    _velocity = Vec3D::createRandom(-0.1, 0.1);
}

void Particle::calculateAcceleration(const std::vector<Particle>& particles, float timestep)
{
    //set acceleration to zero vector
    _acceleration = Vec3D();
    const float G = 0.01;

    for (const auto& particle: particles)
    {
        if (&particle == this)
            continue;

        Vec3D positionDelta = (particle._position - _position);
        float l = positionDelta.length();
        _acceleration +=  (positionDelta * timestep * G) / (l*l*l);
    }
}

void Particle::update(float timestep)
{
    _position += _velocity * timestep;
    _velocity += _acceleration * timestep;
}

void Particle::render()
{
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    glVertex3f(_position.x(), _position.y(), _position.z());
    glEnd();
}
