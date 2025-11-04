## Build and Run
SFML library is added as a git submodule, so after cloning you need to update git submodules.
```
cd corners-game
git submodule update --init --recursive
```
After it you can build CMake project from your IDE or from bash terminal if your system has [cmake installed](https://cmake.org/download/):
```
mkdir build && cd build
cmake .. && cmake --build . && ./corners
```

### Comments
#### Memory management
For memory allocation I use std::unique_ptr mostly. Usually I don't call new or delete manually.<br>
When one has to use an allocated object - it's okay to pass a raw pointer, because I never call delete manually on any raw pointer.<br>
I use smart pointers for ownership and raw pointers for access.<br>

#### Classes
GameField -> contains all game data.<br>
TextureStreamer -> load all textures for render. Renderer is an owner.<br>
Renderer -> gets GameField's data and renders it in a sfml window.<br>
Input -> uses Renderer's sprites to handles player's input.<br>
AIEnemy -> simulate enemy's moves. I didn't have time to make this class any good :(
