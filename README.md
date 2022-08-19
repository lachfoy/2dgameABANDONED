# 2dgame

This is a ~~simple~~ 2D game project that uses SDL2 for rendering. I don't have any huge goals or ambitions for this project - I'm mainly working on this for fun and to improve my software design and C++ skills.

## Task List
General, (slightly out of date) todo list [todo.md](todo.md)

## Inheritance Diagram

Inheritance diagram generated from [inheritance.gv](inheritance.gv) using Graphviz.

![inheritance.gv.png](inheritance.gv.png)

## Building

If you would like to try and build this project (requires SDL2, sdl2_ttf, sdl2_image, sdl2_mixer and cmake)...

1. Clone the repo into any location

2. Create a build directory
    ```shell
    mkdir build
    ```

3. Generate the build files using cmake
    ```shell
    cmake -S . -B build
    ```

4. Build the program
    ```shell
    make -C build
    ```

5. Run the program!
    ```shell
    build/2dgame
    ```

Hopefully it works ;)

### For fun

Counting all the lines of code
```shell
find include/ src/ -regex '.*/.*\.\(h\|cpp\)$' | xargs wc -l
```

### Considerations for Future Projects

- Try using an ECS architecture
- Look into using a scripting system
