# AoC23
Advent Of Code 2023

# Building the Project

Clone the Repository:

``` bash
git clone [repository_url]
cd [repository_directory]
```

Activate the SDK Environment:

```bash
source sdk/activate.sh
```

Prepare the Environment:
```bash
prepare
```

Run the Project:
```bash
run
```

# Activation Script (activate.sh)

The activate.sh script contains functions to install and configure tools required for building the project. To start, activate the environment with the following command:

```bash
source sdk/activate.sh
```

# Activation Script Commands

- prepare: Installs necessary tools such as CMake, GTest, GCC, Clang, and Clang Format.
- build: Creates the build directory and compiles the project using CMake and make.
- rebuild: Removes the build directory and rebuilds the project.
- run: Builds and runs the project, accepting optional arguments.
- format: Formats the source code using clang-format with the settings defined in .clang-format.
- deactivate: Deactivates the SDK environment.