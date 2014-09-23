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
        mag = 10
        self.x = ((random.randrange(-100,100))/100.0)*mag
        self.y = ((random.randrange(-100,100))/100.0)*mag
        self.z = ((random.randrange(-100,100))/100.0)*mag

        # generate random start velocity
        magnitude = 0.01
        self.vx = ((random.randrange(-100,100))/100.0)*magnitude
        self.vy = ((random.randrange(-100,100))/100.0)*magnitude
        self.vz = ((random.randrange(-100,100))/100.0)*magnitude

        self.mass = (random.random())*1000000000;
        self.ax = 0;
        self.ay = 0;
        self.az = 0;



    def render(self):
        #glColor3f(1,1,1)
        #glColor3f(math.sqrt(math.pow(self.vx,2)), math.sqrt(math.pow(self.vy,2)), math.sqrt(math.pow(self.vz,2)))
        #glVertex3f(self.x, self.y, self.z)
        glPointSize((self.mass/1000000000)*10)
        glBegin(GL_POINTS)
        glColor3f(1,1,1)
        glVertex3f(self.x, self.y, -10);
        glEnd()

    def mass(self):
        return self.mass;

    def update(self, particles):
        dt = 0.1

        self.acceleration(particles)

        # update velocity using acceleration vector
        self.vx += self.ax * dt
        self.vy += self.ay * dt
        self.vz += self.az * dt

        print(self.az)

        # update position using velocity vector
        self.x += self.vx * dt
        self.y += self.vy * dt
        self.z += self.vz * dt



    def acceleration(self, particles):
        G = 0.0000000000066;

        self.ax = 0;
        self.ay = 0;
        self.az = 0;
        for p in particles:
            if(p != self):
                r = math.sqrt((p.x - self.x)**2 + (p.y - self.y)**2 + (p.z - self.z)**2)
                self.ax = self.ax + p.mass*((p.x - self.x)/max(0.00000001, math.pow(r,3)))
                self.ay = self.ay + p.mass*((p.y - self.y)/max(0.00000001, math.pow(r,3)))
                self.az = self.az + p.mass*((p.z - self.z)/max(0.00000001, math.pow(r,3)))

        self.ax = G*self.ax;
        self.ay = G*self.ay;
        self.az = G*self.az;

        


def main():
    width = 800
    height = 600
    size = width, height

    pygame.init()
    screen = pygame.display.set_mode(size, pygame.DOUBLEBUF | pygame.OPENGL)
    init_opengl(width,height)

    # generate some particles
    particles = []
    for i in xrange(20):
        particles.append(Particle())

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()

        # run the simulation for all the particles
        for particle in particles:
            particle.update(particles)


        # render the particles
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()

        for particle in particles:
            particle.render()
        pygame.display.flip()


if __name__ == "__main__":
    main()

