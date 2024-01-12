# Getting Started

Now that you know that RTypeEngine is THE library for you, it's time to get ready !

## Downloading the library

The library is available on GitHub, you can download it by cloning the repository:

```bash
git clone https://github.com/Vive-le-LEX/RTypeRenderEngine.git
```

Or by using the cmake FetchContent module:

```cmake
FetchContent_Declare(
    RTypeRenderEngine
    GIT_REPOSITORY https://github.com/Vive-le-LEX/RTypeRenderEngine.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(RTypeRenderEngine)
```

## Building the library

First of all, you need to install the dependencies:
> CMake 3.10 or higher. You can download it [here](https://cmake.org/download/)

### Downloading the library

You can either download the library using git or using the cmake FetchContent module.

#### Using git

```bash
git clone -b main --single-branch https://github.com/Vive-le-LEX/RTypeRenderEngine.git
```

#### Using FetchContent

```cmake
FetchContent_Declare(
    RTypeRenderEngine
    GIT_REPOSITORY https://github.com/Vive-le-LEX/RTypeRenderEngine.git
    GIT_TAG main
)
```

### Configuring the library

Configuring is made possible by CMake variables, here is the list of the variables you can use:

Variable Name  | Description | Defaults
:---: | :---: | :---:
RTYPE_BUILD_SHARED_LIBS  | Whether to build the library as a shared library or not. | ON
RTYPE_CORE  | Whether to build the core module or not. | ON
RTYPE_GRAPHICS  | Whether to build the graphics module or not. | ON
RTYPE_AUDIO  | Whether to build the audio module or not. | ON
RTYPE_ANIMATION  | Whether to build the animation module or not. | ON
RTYPE_BUILD_TESTS | Whether to build the tests or not. | OFF
RTYPE_BUILD_DOC | Whether to build the documentation or not. | OFF

Those variables can be set using the cmake command line:

```bash
cmake -DRTYPE_BUILD_SHARED_LIBS=OFF -S . -B build
```

### Building the library

Once you have configured the library, you can build it using the following command:

```bash
cmake --build build --config Release
```

<div class="section_buttons">
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Home](Welcome.md) | [Window Tutorial](GraphicsModule.md) |
</div>
