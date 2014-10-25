C++ n-body simulator and visualiser
======================================

Dependencies
------------
The program makes use of OpenGL and SDL2. The OpenGL includes and the OpenGL library compiler flag in the Makefile are Mac OS X specific, though trivial to change for e.g. Linux.

To install SDL2 you can use `brew install sdl2` when using Homebrew on Mac OS X.

Usage
-----
To compile use `make`. To run the program use `./sim` on the command line. The application has the following command line options: 
* `position=<number>` scales the starting position of the bodies
* `speed=<number>` scales the starting velocities of the bodies
* `timestep=<number>` runs the simulation with a different timestep scale than the standard one (0.01)
* `time=<number>` runs the simulation for a custom total simulation time
* `timetrial=<number>` runs the simulation for <number> run while doubling the number of bodies for each run
* `demo=<number>` runs the simulation repeatedly, for <number> runs, without logging any data
* `naive` uses the naive Euler integrator
* `leapfrog` uses the leapfrog integrator
* `jerk` uses the Taylor integrator with jerk term
* `dynamic` uses dynamic time-step scale
* `norender` turns off rendering
