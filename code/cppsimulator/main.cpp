#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "SDL.h"
#include "particle.h"

SDL_Window* initSDLAndOpenGL(int width, int height, bool vsync, bool fullscreen)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS , 1 );
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES , 4 );
    SDL_Window* screen;
    if (fullscreen)
    {
        screen = SDL_CreateWindow("N-Body simulator",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else
    {
        screen = SDL_CreateWindow("N-Body simulator",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width, height,
                SDL_WINDOW_OPENGL);
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(screen);

    if (SDL_GL_SetSwapInterval(vsync? 1 : 0) == -1) {
        std::cout << "could not set desired vsync mode: " << vsync << 
            std::endl;
    }
    glClearColor(0.1, 0.1, 0.15, 0);

    //glClearDepth(1);
    //glDepthFunc(GL_LESS);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, float(width)/height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(2);


    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "ERROR after opengl initialization" << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "NO error after opengl initialization" << std::endl;
    }

    
    return screen;
}


int main(int argc, char* argv[])
{
    int screenWidth = 800;
    int screenHeight = 600;
    bool vsync = true;
    bool fullscreen = false;

    SDL_Window* surface = initSDLAndOpenGL(screenWidth, screenHeight, vsync,
            fullscreen);

    std::vector<Particle> particles;
    for (int i = 0; i < 2000; i++)
    {
        particles.push_back(Particle());
    }


    bool running = true;
    float timestep = 0.1;

    float yRotate = 0;
    float xRotate = 0;
    float distance = -30;
    while (running)
    {
        //run model verification steps
        Vec3D totalMomentum;
        float totalKineticEnergy, totalPotentialEnergy;
        for(auto& particle: particles)
        {
            totalMomentum = totalMomentum + particle.momentum();
            totalKineticEnergy += particle.kineticEnergy();
            totalPotentialEnergy += particle.potentialEnergy();
        }
        totalPotentialEnergy *= -0.5;


        std::cout << "total momentum: (" << totalMomentum.length() << ") " ;
        totalMomentum.print();
        std::cout << "total kinetic energy: " << totalKineticEnergy << std::endl;
        std::cout << "total potential energy: " << totalPotentialEnergy << std::endl;
        std::cout << "total energy: " << totalPotentialEnergy + totalKineticEnergy  << std::endl;

        //run simulation
        for(auto& particle: particles)
        {
            particle.calculateAcceleration(particles, timestep);
        }
        for(auto& particle: particles)
        {
            particle.update(timestep);
        }

        //render universe
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0, 0, distance);
        glRotatef(xRotate, 1,0,0);
        glRotatef(yRotate, 0,1,0);
        for(auto& particle: particles)
        {
            particle.render();
        }
        SDL_GL_SwapWindow(surface);


        //check input
        SDL_Event event;    
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                if (event.motion.state & SDL_BUTTON(1))
                {
                    yRotate += event.motion.xrel * 0.5;
                    xRotate += event.motion.yrel * 0.5;
                    if (xRotate > 90) xRotate = 90;
                    if (xRotate < -90) xRotate = -90;
                }
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                distance += 0.3* event.wheel.y;
            }
        }
    }
}
