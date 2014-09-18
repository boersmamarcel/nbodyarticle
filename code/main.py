import pygame
import sys
import random
import math
from OpenGL.GL import *
from OpenGL.GLU import *

# general OpenGL initialization
def init_opengl(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(90.0, float(width)/height, 0.1, 100.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)
    glClearColor(0.1, 0.1, 0.15, 0.0)
    glPointSize(2)
    


class Particle:
    def __init__(self):
        # generate random start position
        self.x = random.random() * 10 - 5
        self.y = random.random() * 10 - 5
        self.z = random.random() * -10

        # generate random start velocity
        magnitude = 2
        self.vx = (random.random() - 0.5)*magnitude
        self.vy = (random.random() - 0.5)*magnitude
        self.vz = (random.random() - 0.5)*magnitude


    def render(self):
        glColor3f(1, 1, 1)
        glVertex3f(self.x, self.y, self.z)

    def update(self):
        dt = 0.1
        gravity_strength = 0.5

        # create acceleration vector by taking difference from particle's 
        # position and (0,0,-5), which we're using as the source of gravity
        ax = - self.x * dt * gravity_strength
        ay = - self.y * dt * gravity_strength
        az = (-5 - self.z) * dt * gravity_strength

        # update velocity using acceleration vector
        self.vx += ax * dt
        self.vy += ay * dt
        self.vz += az * dt

        # update position using velocity vector
        self.x += self.vx * dt
        self.y += self.vy * dt
        self.z += self.vz * dt
        

def main():
    width = 800
    height = 600
    size = width, height

    pygame.init()
    screen = pygame.display.set_mode(size, pygame.DOUBLEBUF | pygame.OPENGL)
    init_opengl(width,height)

    # generate some particles
    particles = []
    for i in xrange(1000):
        particles.append(Particle())

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()

        # run the simulation for all the particles
        for particle in particles:
            particle.update()


        # render the particles
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_POINTS)
        for particle in particles:
            particle.render()
        glEnd()
        pygame.display.flip()


if __name__ == "__main__":
    main()
