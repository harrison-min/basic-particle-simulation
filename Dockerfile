FROM alpine:latest

RUN apk add --no-cache g++ ffmpeg viu

COPY src/ /src/

RUN g++ src/main.cpp src/renderer.cpp src/particle.cpp src/simulation.cpp src/gravity.cpp -o main -Wall --std=c++20
RUN mkdir frames
RUN mkdir output
ENTRYPOINT ./main && ffmpeg -y -framerate 60 -i frames/test%05d.ppm -c:v libx264 -pix_fmt yuv420p output/output.mp4
# command to output file:docker run --mount type=bind,source="$(pwd)/output",target=/output basic-particle-simulation 