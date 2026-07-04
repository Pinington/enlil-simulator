# TO DO List
Renderer:
 - Clean the entire renderer.cpp code
 - Instantiate on command without predefined values 
 - Set an FPS
 - Maybe make a mesh factory class

Camera:
 - Fix how we pass the MVP matrices
 - Adapt renderer to make normals work at all scales for isntances
 - Clean the camera movement up, make it more modular

Core:
 - Make particles move around with gravity in a semi-sphere platform  
 - Link a particle system to the renderer
 - Make verlet integration the main update method

 Physics:  
 - Add forces that follow cursor
 - Add platforms

Menu:
 - Connect a GUI Menu to the renderer

Tidiness:
 - Document the code  
 - Throw errors in renderer
 - Add QDesc, QTitle, and other meta data when starting the app up