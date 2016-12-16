# Procedural Terrain Generation Using the Marching Cubes Algorithm

### *Andrew Conant and Oliver Newman*

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
of the density function we use. Marching cubes works by dividing the 
cube-shaped scene into a three-dimensional grid of cubes (a.k.a. voxels, with 
the number of cubes per side specified by the value of `m_res` in
`mypanelopengl.cpp`. For each voxel, the density at each vertex is calculated,
and then based on these values the 'shape' of the voxel is determined. If a
linear interpolation between each adjacent pair of vertices reveals that the
0-isolevel of the density function passes through the cube, then the values of
the vertex densities relative to zero are used to index into a lookup table to
find the arrangement of up to five triangles which best represents the density
function 0-isolevel within that voxel.


### Density Functions

We also implemented several different density functions to use in the marching
cubes algorithm, which generate different types of terrain. For example,
`plane` and `plain` (we couldn't decide which name was more appropriate)
generate a flat plane extending in the *x* and *z* directions. `funky`
generates a somewhat less realistic landscape with some rounded hills and 
'floating' chunks of earth. And `curve` represents a sort of bowl-shaped form
(essentially determined by `x*y*z`).


### Lighting
<!-- TODO -->


## Further work

We had hoped to be able to apply different textures to our landscape in order
to make it even more realistic by giving the appearance of having grass, rock,
dirt, snow, etc., but implementing and debugging the marching cubes algorithm
proved to be a more daunting task than we had anticipated.

We had also planned to make landscape that looked as high-definition and
realistic as do the examples in [NVIDIA's procedural terrain
generator](http://http.developer.nvidia.com/GPUGems3/gpugems3_ch01.html) that
we referenced. This would have been more plausible if we had used CUDA to
do march the cubes; since the number of cubes in the scene increases
cubically as the resolution increases, it is a fairly slow process and takes
an obnoxiously long time to run beyond a resolution of 100 or so voxels per
side (which isn't quite enough to get really smooth-looking terrain).

<!-- TODO just add another paragraph -->


## References
- http://http.developer.nvidia.com/GPUGems3/gpugems3_ch01.html

## Code we Used
- http://paulbourke.net/geometry/polygonise/
- http://flafla2.github.io/2014/08/09/perlinnoise.html
