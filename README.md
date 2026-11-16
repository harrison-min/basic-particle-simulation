# GPU-Accelerated Particle Simulator in C++ & CUDA

A basic particle physics simulator built on classical mechanics and Newtonian gravity, accelerated using the CUDA Thrust library.

## Features

* **PPM Based Rendering:** Frames are generated using the PPM image format (due to simplicity) and stitched together with FFMPEG
* **Classical Mechanics Engine:** Models gravity wells as fixed points with no particle-particle or particle-well collisions (chosen for ease of parallelization).
* **CUDA Acceleration:** Uses CUDA thrust library for GPU acceleration for position/velocity data. 
