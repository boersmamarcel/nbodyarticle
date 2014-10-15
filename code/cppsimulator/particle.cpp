#include "particle.h"

#include <iostream>
#include <OpenGL/gl.h>

Particle::Particle()
{
    _position = Vec3D::createRandom(-10, 10);
    _velocity = Vec3D::createRandom(-1, 1);
    _acceleration = Vec3D();
    _mass = 1;
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
