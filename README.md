<br />
<div align="center">
  <p align="center">
    Basic Particle Simulation
  </p>
</div>




## About The Project
<video src="https://raw.githubusercontent.com/harrison-min/basic-particle-simulation/main/output/output.mp4" 
       width="100%" 
       height="auto" 
       muted 
       controls 
       loop 
       autoplay>
</video>

This is a basic particle physics simulator using the CUDA API for parallelizing the simulation calculations. It is based on classical mechanics and Newtonian gravity. 

Renderer is a simple PPM image generator and individual frames are combined using FFMPEG. Thrust is the main CUDA library used. 

Physics Assumptions: 
- No particle-particle or particle-gravity well collisions.
- Gravity wells are fixed points in space. 


### Built With

1. CUDA (thrust library)
2. FFMPEG

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<!-- CONTACT -->
## Contact

Harrison Min - email:harrison0min@gmail.com
Github - github.com/harrison-min/basic-particle-simulation
