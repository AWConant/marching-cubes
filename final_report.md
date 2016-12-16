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
$ ./terrain {funky|plane|curve} {resolution} {field size} {1|0 (gradient normals?)}
```

{funky|plane|curve} specifies which of the three implemented density functions
to use to generate the mesh geometry.

{resolution} specifies the number of voxels per field side. Each voxel ends up
having side lengths equal to (resolution/fieldsize). Higher resolutions produce
more detailed geometries.

{field size} specifies the "length" of each side of the field. Basically, the
size of the cube that will be divided into voxels.

{1|0 (gradient normals?)} specifies whether gradient or face normals will be
used. Gradient normals are prettier, so we recommend that, but definitely
check out both options.

Some interesting examples:

```bash
$ ./terrain funky 5 100 1
$ ./terrain funky 10 100 1
$ ./terrain funky 20 100 1
$ ./terrain funky 40 100 1
$ ./terrain curve 5 100 1
$ ./terrain curve 10 100 1
$ ./terrain curve 20 100 1
$ ./terrain curve 40 100 1
$ ./terrain plane 5 100 1
```

## Features

### Marching Cubes

The biggest part of our project, both in terms of the time put into implementing
it and extent to which our final product is reliant on it, is the marching
cubes algorithm, which actually allows us to render a graphical representation
of an arbitrary density function. Marching cubes works by dividing the
cube-shaped scene into a three-dimensional grid of cubes (a.k.a. voxels, with
the number of cubes per side specified by the value of `m_res` in
`mypanelopengl.cpp`. For each voxel, the density at each vertex is calculated,
and then based on these values the 'shape' of the voxel is determined. If
linear interpolation between a pair of adjacent vertices reveals that the
0-isolevel of the density function passes through the cube, then the values of
the vertex densities relative to zero are used to index into a lookup table to
find the arrangement of up to five triangles which best represents the density
function within that voxel.


### Density Functions

We implemented several different density functions to use in the marching
cubes algorithm, which generate different types of terrain. For example,
`plane`
generate a flat plane extending in the *x* and *z* directions. `funky`
generates a somewhat less realistic landscape with some rounded hills and
'floating' chunks of earth. And `curve` represents a sort of bowl-shaped form
(essentially determined by `x*y*z`).



### Lighting
<!-- TODO -->


### Movement

Much as in the solar system lab, the user can move about our landscape using
keyboard controls which are printed out when the program begins. The user is
able to pan, zoom, and move about the scene, thanks to the use of a camera
object like the one we used in the solar system lab.


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

Finally, the terrain is necessarily enclosed in a 3-dimensional cube, but in
some of the examples we referenced, the terrain faded off into the distance
in the background instead of just ending at a cliff over a void. We had hoped
to be able to implement something like this for our project (or perhaps to just
constrain the user's movements so as to make it impossible to get high enough
or close enough to the edge to see the dropoff).


## References
- http://http.developer.nvidia.com/GPUGems3/gpugems3_ch01.html

## Code we Used
- http://paulbourke.net/geometry/polygonise/
- http://flafla2.github.io/2014/08/09/perlinnoise.html
