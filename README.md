# ray-tracer
A raytracer in C++ with IMGui and vulkan

# Windows
Clone the repo and run this in powershell to build and run
```
powershell -ExecutionPolicy Bypass -File scripts/bootstrap.ps1
premake5 ninja
ninja -C build
./bin/Release/raytracer.exe
```

# Mac / Linux
Clone the repo and run this in powershell to build and run 
```
./scripts/bootstrap.sh
premake5 gmake2
make config=release
./bin/Release/raytracer
```