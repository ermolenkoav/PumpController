        Sequence of steps to build a project:
  1 Install software:
1.1 Visual Studio https://visualstudio.microsoft.com/
1.2 Cmake https://cmake.org/download/
1.3 git https://git-scm.com/
  2 Download & compille:
2.1 vcpkg;
    > git clone https://github.com/Microsoft/vcpkg.git
    > cd vcpkg
    PS> .\bootstrap-vcpkg.bat
2.2 Add vcpkg to system environment path;
2.3 Install c++ packages:
    > vcpkg install cpprestsdk pthreads gtest qt5-serialport --triplet x64-windows
2.4 Add path to ../vcpkg/scripts/buildsystems/vcpkg.cmake in CMake tollchain file 
    in MSVC CMake settings;
  3 Compile project.