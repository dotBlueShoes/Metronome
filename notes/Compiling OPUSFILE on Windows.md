***DATE** : 25.04.2025* 

**Minimal Requirements**

- Microsoft Visual Studio 2022
- CMake
- GIT

- Git Clone **opusfile** https://github.com/xiph/opusfile.git
- Git Clone **opus**  https://github.com/xiph/opus.git
- Git Clone **ogg**  https://github.com/xiph/ogg.git


>[!Note] OpenSSL 
> Compiling against **OpenSSL** is not necessary the following dependency can be omitted. However if the functionality is by you required simply download the compiled source, binaries and libraries from a provider or compile them yourself from: https://github.com/openssl/openssl and attach them to **opusfile Visual Studio solution** just as other dependencies.


## Static Library

1. Clone Repositories

```bash
git clone https://github.com/xiph/ogg.git
git clone https://github.com/xiph/opus.git
git clone -b master https://github.com/xiph/opusfile.git
```

2. Build ogg and opus

```bash
# Build libogg
cd ogg
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"  # Use the right VS version here
cmake --build . --config Release

# Build opus
cd ../../opus
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

With this you should have created `.sln` files. 

 - Open `ogg.sln` with **Visual Studio**
 - Right click the **ogg** solution and select **build**

 - Open `Opus.sln` with **Visual Studio**
 - Right click the **opus** solution and select **build**

Now you should have `.lib` and `.h` files for both.

3. **Configure `opusfile` project in Visual Studio**

- Open the `opusfile` project - `win32/VS2025/opusfile.sln`
- Add the paths to the header files and libraries of both `libogg` and `opus`.

##### In Visual Studio:

- Right-click your project - **opusfile** > **Properties**
- Select All Configurations & All Platforms
- Go to **C/C++ > General > Additional Include Directories**:
    - Add paths to `ogg/include`, `opus/include`, etc.
- Go to **Librarian > General > Additional Library Directories**:
    - Add paths to `ogg/build/Release` and `opus/build/Release`

- If the .lib is supposed to be linked using different then msvc linker also Disable /GL
    - Go to **Configuration Properties → C/C++ → Optimization**
    - Set Whole Program Optimalization to none.

- Right click the **opusfile** solution and select **build**

#### Disabling OpenSSL

##### In Visual Studio:

1. **Right-click your `opusfile` project** → select **Properties**
2. Go to:  
    `Configuration Properties > C/C++ > Preprocessor`
3. Find **Preprocessor Definitions**
4. Add:
    `OP_DISABLE_HTTP`

If after hitting compile an error still occurs right click `wincerts.c` file in solution explorer and click `Exclude From Project`. Recompile.

This should successfully compile a static library file.
## Import Library

TODO
