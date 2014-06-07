# The Matrix
![Alt text](/Debug/screenshot.png?raw=true "The Matrix")
<b>You are trapped inside the code, the goal is to find your way outside.</b>
![Alt text](/Debug/rooms.png?raw=true "The halls")
When you stand in a hall the code makes sure that the two edges of the hall have two edges attached to each one of them.
Try to find the glitch to escape the code!

Use WASD to move camera position and the mouse to change the camera direction  

<b>The project:</b>
The project is fully object oriented. 
The environment generates 14 halls dynamically and puts them around the camera, creating the picture shown above.
When the camera moves around, the halls changes position without the user seeing that(se picture above).
Each hall contains several images of a texture loaded by DevIL and later are sent to the shaders throw a shader program.
Since we are using OpenGL 2.1, we can only modify vertex and fragment shader. 
The texture is then croped dynamically to give the illusion of the matrix falling text effect. 
<br />
The project was developed in Eclipse, Ubuntu

<b>Tags:</b> C++ , Object Oriented , GLEW, GLFW , DeviIL, OpenGL 2.1 , GLSL 1.2, Vertex shader, Fragment shader, GLM
<br />

<b>Code age: </b> Codes was written in 2014-05
