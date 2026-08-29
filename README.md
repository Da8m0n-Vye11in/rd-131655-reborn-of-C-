# README

This branch contains an initial full-port attempt from Java to C (c-rewrite branch).

Notes:
- Java sources in src/main/java were not deleted by the converter (GitHub API limitations for deletions via this tool). Instead they remain in the repository root. Please remove them manually if you want them deleted.
- This port targets Windows/macOS/Linux via GLFW + GLAD + stb_image. The CMake configuration fetches these dependencies automatically.
- To build on Windows:
  - Install CMake and a C compiler (MSVC or MinGW)
  - Run: mkdir build && cd build && cmake -G "Visual Studio 17 2022" .. && cmake --build . --config Release
  - The terrain.png resource will be copied to the executable folder on build.

This is an initial runnable port. Tile rendering is a PoC and may not reproduce exact visuals; next steps include completing Tessellator -> VBO rendering and porting remaining game logic.
