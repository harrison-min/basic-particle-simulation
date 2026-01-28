FROM nvidia/cuda:12.6.0-devel-ubuntu24.04

RUN apt-get update && apt-get install -y ffmpeg && rm -rf /var/lib/apt/lists/*

COPY src/ /src/

RUN nvcc src/main.cu src/renderer.cu src/particle.cu src/simulation.cu src/gravity.cu  -std=c++20 --extended-lambda -arch=sm_75 -o main

RUN mkdir frames output

ENTRYPOINT ./main && ffmpeg -y -framerate 60 -i frames/test%05d.ppm -c:v libx264 -pix_fmt yuv420p output/output.mp4

#docker run --mount type=bind,source="$(pwd)/output",target=/output --gpus all -e LD_LIBRARY_PATH=/usr/lib/wsl/lib basic-particle-simulation 