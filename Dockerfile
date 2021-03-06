# Builder image for building project and running tests
FROM rikorose/gcc-cmake as builder

# Get SDL, GTest (testing) and Doxygen (docs)
RUN apt-get update -y
RUN apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev libgtest-dev doxygen

# Set up project structure
RUN mkdir -p /usr/src/sumo/{src, tests, build, docs}

# Copy over project resources
COPY CMakeLists.txt /usr/src/sumo/
COPY src /usr/src/sumo/src
COPY tests /usr/src/sumo/tests
COPY docs /usr/src/sumo/docs

# Run cmake then make to build
WORKDIR /usr/src/sumo/build
RUN cmake ..
RUN make

# Unit tests
RUN ./tests/runTestVector2d


# Lightweight image for deployment
FROM ubuntu:latest

# Get only SDL. noninteractive flag to avoid tzinfo prompts
RUN apt-get update -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev

# Set up structure for deployed application
RUN mkdir -p /usr/src/sumo/assets
WORKDIR /usr/src/sumo/

# Copy over only compiled executable and art assets
COPY --from=builder /usr/src/sumo/build/sumo .
COPY --from=builder /usr/src/sumo/build/assets ./assets/
COPY --from=builder /usr/src/sumo/build/docs/built_docs ./docs/

# Run the game
CMD ["./sumo"]