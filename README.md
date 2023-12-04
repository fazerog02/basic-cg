# basic-cg

https://kdb.tsukuba.ac.jp/syllabi/2023/GB13704/jpn/

## Get Started

1. `sudo apt install libglu1-mesa-dev mesa-common-dev freeglut3-dev`
2. `g++ main.cpp -lglut -lGLU -lGL`
3. `./a.out`

|
v

1. replace `#include <GL/glut>` to

```cpp
#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
```

2. `g++ -lm -framework OpenGL -framework GLUT -framework Foundation main.cpp`
3. `./a.out`

## Enviroment

- Ubuntu 22.04.3 LTS

|
v

- macOS Ventura 13.4
- Apple silicon M2
