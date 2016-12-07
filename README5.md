
# Concept Questions

* Describe how implemented right and pitch in your camera class. Do you rebuild
  the LookAt matrix from scratch or do you multiply the current LookAt matrix
  by a translation/rotation? If the latter, is the multiplication on the left
  or right. 

  > We're multiplying the current LookAt matrix on the *left* by a x-axis 
  > translation (for right) or rotation (for pitch) matrix. Thus, we are *not*
  > rebuilding the LookAt matrix each time.

* Describe the additional effect (besides adding the camera class and
  perspective matrix) you implemented.

  > Pressing the space bar starts and ends "spacequake" mode. In this mode,
  > the camera is perturbed in random directions by amounts depending on the
  > sine of the "time" since the beginning of the spacequake. The sine causes
  > the spacequake to oscillate in magnitude.

* Given a 4x4 LookAt matrix could you recover any of the original parameters,
  eye, at, and up just by inspecting the matrix? If you can extract a
  parameter, describe which parameter you can extract and how. If you cannot
  recover a parameter, briefly describe why? 

  > Given a LookAt matrix of the form:
  >
  > ```a b c d```  
  > ```e f g h```  
  > ```i j k l```  
  > ```0 0 0 m```  
  >
  > it is fairly easy, if tedious, to extract the original eye parameter by
  > backtracing through the translation (matrix multiplication) of the LookAt 
  > matrix. This is done by solving the following system of equations for x, y, 
  > and z, the components of the eye vector:
  >
  > ```-ax - by - cz = d```  
  > ```-ex - fy - gz = h```  
  > ```-ix - jy - kz = l```  
  >
  > However, the exact up and at parameters cannot be recovered, because, while
  > a, b, c, e, f, g, h, i, j, k, l are all based on the values of those
  > parameters, there are several normalizations along the way, along with some
  > cross products, both of which are impossible to "trace back" through in this
  > case, given that we only have the final LookAt matrix.

# Quick Lab Survey

None of your answers to the questions below  will have an impact on your grade.
This is to help provide feedback and improve course quality

* Approximately, how many hours did you take to complete this lab?
  > 12 Hours

* How difficult did you find this lab?  (1-5, with 5 being very difficult and 1
  being very easy)
  > 4

* Describe the biggest challenge you faced on this lab.
  > For a while, our rotations would rotate about the sun rather than the
  > "spaceship", so to speak. This was solved by applying the transformations
  > on the opposite side.
