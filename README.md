# SDL2 Learn OpenGL

I'm learning OpenGL using Joey de Vries's excellent book Learn OpenGL, except I'm using SDL2 instead of GLFW. The code follows the book examples and exercices.

## My VS Code set up

1. Install VS Code and Visual Studio Community (vcpkg and cmake are included in the 2022 version).
1. In VS code, install the C++, the CMake and the CMakeTools extensions, all by Microsoft.
1. Add the following to the workspace settings :

    ```

    "cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE" : "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake",
    "VCPKG_BUILD" : "ON",
  },

    ```

1. Start the "Developper PowerShell for VS 2022", go to the folder you're coding in and run

    ```

    vcpkg integrate install

    ```

    followed by (to be changed when new vcpkg is released in september 2023)

    ```

    vcpkg install --triplet x64-windows

    ```

1. In VS Code, select the toolkit to compile with (here Visual Studio Community 2022 Release - amd64), then hit run.
