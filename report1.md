# Progress Report #1

Most of our progress thus far in implemented our procedurally generated terrain
creator has involved an implementation of the marching cubes algorithm that we
found at from [Paul Bourke](http://paulbourke.net/geometry/polygonise).

In its original state, the source code that we found used the marching cubes
algorithm to produce several different shape-shifting animations within a cube-
shaped scene. None of these animations used any sort of noise or terrain-related
methods. Therefore, we have added our own method which, instead of animating a
shifting shape like the original methods, uses Perlin noise to generate a 2D
array of floating point values. We linked that to the marching cubes source code
so that now, instead of animating shapes, the code produces a square landscape
(with elevations determined by the noise function) within the original cube
scene.

This is a good start for us, but it leaves quite a few things still left to
accomplish. In particular, we need to find a way to spread the landscape beyond
the bounds of the cube which the original animations took place in, and to have
it fade into the distance in some fairly realistic-looking way. We also need to
fine-tune the noise function so that it produces the most interesting and
realistic landscape possible. After that, we will work on texture mapping, to
hopefully make the landscape appear even more realistic by classifying different
parts of it as different sorts of terrain.
