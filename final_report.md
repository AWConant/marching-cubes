# Procedural Terrain Generation Using the Marching Cubes Algorithm
Andrew Conant and Oliver Newman

- What methods did you use (Shaders, CUDA, straight C++, others)?
- What third party tools did you use, if any?
- How do I compile run your program? Do I need any external data files? If so, where are they?
- What where the primary features you implemented?
- Is there anything missing that you wanted to add?

## Methods and Tools

To implement the marching cubes algorithm and to render the scene that we 
generated, we used only standard OpenGL with vertex and fragment shaders.

We used the GL math library in our density functions in order to generate
realistically and interestingly shaped terrain using the noise functions
included in the GLM library.


## Usage

No external data files or plugins are needed; just compile and run as follows:

```bash
$ git clone git@github.swarthmore.edu:CS40-F16/final-aconant1-onewman1.git
$ cd final-aconant1-onewman1
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
$ ./terrain
```

## Features

### Marching Cubes 
The biggest part of our project, both in terms of the time put into implementing
it and extent to which our final product is reliant on it, is the marching
cubes algorithm, which actually allows us to render a graphical representation
of the density function we use.

### Lighting

### Density Functions

We also implemented several different density functions to use in the marching
cubes algorithm, which generate different types of terrain. For example,
`plane` and `plain` generate a flat plane extending in the *x* and *z* 
directions. `funky` generates a sort of Arches National Park-esque landscape
with some rounded hills and even some floating chunks of earth.



## Further work


## References
- http://http.developer.nvidia.com/GPUGems3/gpugems3_ch01.html

## Code we Used
- http://paulbourke.net/geometry/polygonise/
- http://flafla2.github.io/2014/08/09/perlinnoise.html
