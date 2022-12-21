# Liquid
Liquid is a media editor command-line interface (CLI)

# Installation for windows x64
1. run `.\bootstrap-vcpkg.bat` to download vcpkg.exe
2. run `.\vcpkg.exe install --triplet="x64-windows"` to install all dependencies
3. run `.\makebinary.bat` to build binary from source
4. the binary location is located in `.\build\Release\liquid.exe`

# Usage
```
liquid [OPTIONS] [FILES]
display or edit media files

 -h, --help     display help and exit
 -a, --all      show all info
```

# Transferring Source Code Offline
to create a clean environment for building from source when the source code is transferred to another computer, run the command `vcpkg env` to create a clean environment for building from source. This will set up the necessary environment variables and configure the system to use the vcpkg libraries and tools

# To-Do List
- [x] open single image file
- [x] open and navigate between multiples image file using the left key (h) and right key (l)
- [ ] edit image with simple feature

# Why Use It?
Liquid is fast
