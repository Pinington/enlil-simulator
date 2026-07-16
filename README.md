```
        "gilga.msh inc.
         _________           ___    ___            ________         ___       __  
       /"         `\\      /   \\  /   \\         /         \\    //  \\\\   /   \\ 
      //    ________/     /     \\/     \\      //    ..-.___\\   '      \\_/     . 
     /    /  ______       ;              \\     /    //    \"\"   |               |
    \\    \ |____  \    /    /\\    /\\   \\   \\    \\    ___    |       _       |
     \\    \____/   /  /    /  \\__/  \\   \\   \\    '--'   //   '      / \\     ' 
      \\ __________/   \\__/          \\___/     \\_________/      \\___/   \\___/ 

```

# Enlil
Basic physics engine for Lagrangian particle simulation built in C++ for experimentation.
Enlil lets you simulate two types of patticles in any desired amount on a platform of your choice, the engine will be made extensible to add future Eulerian simulation.

# Requirements
 - C++17 or newer
 - CMake
 - MSVC
 - Qt


# Build
cmake --build build

# Versions

----------  
## Ver 0.1.0-beta.1 (16 - jul - 2026)  

### Hello World

#### First beta public release 
First version is officially out.  
This first version is just an MVP (minimum viable product) to get a simulation running, we can now successfully simulate gravity on a sphere.  
Platforms are missing for now and the camera angle isn't optimal to watch the simulation happenning; I haven't added collisions or multiple spheres in a simulation either.  
The next versions will tackle these issues. (although they may be delayed for a couple months)

----------  
# Ver 0.2.0-alpha.1

### Halley collides
This newer version will tackle the issue of GUI and collisions for multiple spheres.  
  
----------  
# Ver 0.3.0-alpha.1

### Bouncy
This version will solve UX and add multiple platforms for the simulation to happen in.
Hopefully this will be the final version before the v1