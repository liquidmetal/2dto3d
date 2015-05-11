# 2dto3d
This is a Simple modelling tool wcich would generate 3D Models(.ply) from a single image.
The current version allows modelling of primitives such as Cuboid/Cube and Cylinders.


Libraries/Dependencies
------------------------------------------------------------
- GLEW 
- OpenGL
- Glut
- Glui
- Soil (http://www.lonesock.net/soil.html)

Installing MeshLab would make it convenient to view the output ply file

Launching
------------------------------------------------------------
g++ src/* -libglew -libglut -libGL -libSOIL -libglui

./2DTO3D "name of the output ply" width height

* width and height would be the size of the image to be loaded

