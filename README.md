
# Concept Questions

* Describe how you used the matrix stack to model your scene

  > To draw a particular planet, we first push an identity, and then transform
  > it in the following order:
    * Inclination
    * Time of year
    * Distance to orbital center
    * Tilt
    * Recursively draw moon(s) using the current contents of stack
    * Implicit pop(s) at the end of recursive call(s)
    * Time of day
    * Planetary radius

* Describe how you implemented pan and zoom

  > To pan we simply translated the view matrix along the x-axis. Zoom scaled the
  > view matrix by 10%.

* How did you implement a moon around a planet?
  
  > Consult the solarData.txt file for more info, but moon data for the solar
  > system was put there directly after the planet that they orbit. Orbital
  > radius was defined as the distance from the moon to the planet that it
  > orbits. The process was described more specifically in the answer to the
  > first question, but clever application of recursion and the matrix stack
  > allowed us to draw moons with respect to the planet at a critical part
  > of drawPlanet().

# Quick Lab Survey

None of your answers to the questions below  will have an impact on your grade.
This is to help provide feedback and improve course quality


* Approximately, how many hours did you take to complete this lab?
  *  9 Hours

* How difficult did you find this lab?
  (1-5, with 5 being very difficult and 1 being very easy)
  * 3

* Describe the biggest challenge you faced on this lab.
  * Figuring out the correct ordering for the transformations on the stack
  was tough. For example, if you aren't careful, axial tilt and inclination
  can accidentally be combined into the same rotation.
