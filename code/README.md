Python n-body simulator and visualiser
======================================

Dependencies
------------
The program makes use of OpenGL. It makes use of the Pygame and PyOpenGL Python libraries. To install PyOpenGL you can use `pip install pyopengl`. To install you can download a Pygame installer from the [Pygame website](http://www.pygame.org/download.shtml). 

Mac OS X users that use Homebrew alternatively can install Pygame with `brew tap homebrew/python && brew update && brew install pygame`. And the following commands:
```
mkdir -p ~/Library/Python/2.7/lib/python/site-packages
echo '/usr/local/lib/python2.7/site-packages' > ~/Library/Python/2.7/lib/python/site-packages/homebrew.pth
```

Usage
-----
To run the program use `python main.py` on the command line.
