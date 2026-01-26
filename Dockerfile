FROM alpine:latest

RUN apk add --no-cache g++ ffmpeg imagemagick

COPY src/ /src/

RUN g++ src/main.cpp -o main -Wall 