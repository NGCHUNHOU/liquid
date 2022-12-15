media editor cli

# install for x64 windows
1. run `.\bootstrap-vcpkg.bat` to download vcpkg.exe
2. run `.\vcpkg.exe install --triplet="x64-windows"` to install all dependencies
3. run `.\makebinary.bat` to build binary from source
4. the binary location is located in `.\build\Release\liquid.exe`

# the usage
```
liquid.exe [FILES]
```
