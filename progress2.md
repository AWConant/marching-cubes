# Progress Report 2

We have two main successes so far:

We've successfully hacked Paul Bourke's marching cubes implementation
to draw arbitrarily large x/y noise terrains. We spent a lot of time
reading literature about marching cubes, so our next goal is to roll
our own marching cubes using OpenGL that isn't from 1994.

We've also successfully created a skeleton for the final project
using the solar system lab. We will thus use QT to handle the window,
OpenGL for graphics, and potentially CUDA to make things fast. While
each individual calculation isn't hard, there are a lot of them, and
they're independent, why not parallelize them?
