# Chopp
Wood chopping game, like Timberman, in C++

## Setup
- Clone the repo
- Get the submodules, `git submodule update --init`
- Setup SFML
  - Open the SFML folder in CMake
  - Change the install path to `<Chopp folder>/vendor/SFML/install`
  - Build SFML in both Debug and Release
- Run premake, e.g., `premake5.exe vs2019`
- Open in Visual Studio, and build.