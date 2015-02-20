# theEngine
A simple DirectX 3D game engine!

This engine is being written primarily in C++ and uses the Microsoft Foundation Classes (MFC) as a base for the GUI in the engine.


Update 3:

Its been a while but not much has changed. There is still only basic object functionality, however there is now a mesh and mesh renderer architecture in place. Cubes and planes can be loaded in and I am working on loading .Obj files into the engine. There is also a console window which displays text output. This will be used later to display errors during compiling.Some changes have also been made to the properties panel to support changing menus depending on which component is selected.There is also a simple saving and loading system in place which you can save scenes with, however to load a scene you have to change source code.

 
Update 2:

Basic gameobject functionality has been added, and by basic, i mean basic. There are no graphical elements to the game object yet. Only an empty instance of one which contains a transform object (translation, rotation, scale). Also basic UI functionality has been added. So you can change the values of an objects translation, rotation or scale using the panel to the right, and select the object you are editing using the panel to the left.


Update 1:

So far there nothing but a few basic dialog panels to change object properties. However these do not do anything yet as i am in the process of porting all the graphics and main engine functionality(of which there is not much) from another project. The reason for this is that i had previously been using Win32 but decided to go with MFC.
