#!/bin/bash
cmake -B ./build/ -S . -DCMAKE_TOOLCHAIN_FILE=./scripts/buildsystems/vcpkg.cmake; cmake --build ./build/ --config Release
