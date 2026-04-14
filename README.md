# ray-tracer
A raytracer in C++ with IMGui and vulkan

# Windows
Clone the repo and run this in powershell to build and run
```
powershell -ExecutionPolicy Bypass -File scripts/install_vulkan_sdk.ps1
premake5 ninja
ninja -C build
./bin/Release/raytracer.exe
```

# Mac / Linux
Clone the repo and run this in powershell to build and run 
```
./scripts/install_vulkan_sdk.sh
premake5 gmake2
make config=release
./bin/Release/raytracer
```