# Liquid
Liquid is a media editor command-line interface (CLI)

# Build from source for x86_64-pc-windows-gnu with MinGW
1. run `git submodule update --init` to install dependencies
```
cmake -B ./build/ -G "MinGW Makefiles" -S .
cmake --build ./build/ --config Release
```
2. run cmake commands to build from source

# Usage
```
liquid [OPTIONS] [FILES]
display or edit media files

 -h, --help     display help and exit
 -a, --all      show all info
```

# To-Do List
- [x] open single image file
- [x] open and navigate between multiples image file using the left key (h) and right key (l)
- [ ] edit image with simple feature

# Why Use It?
Liquid is fast
