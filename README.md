# phased_array

An interactive simulation of a phased array

## Build

From this cloned repository's root directory:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target phased_array
```

## External libraries

- [GLFW](https://github.com/glfw/glfw) for the window and inputs
- [Dear ImGui](https://github.com/ocornut/imgui) for the user interface

## License

This software is released under [MIT License](LICENSE).

