@echo off
set EXTERN_PATH=%~dp0..\extern
pushd %~dp0..\build
cmake -G "Visual Studio 14 Win64" -DGLM_ROOT_DIR=%EXTERN_PATH%\glm -DGLFW_ROOT=%EXTERN_PATH%\glfw^
 -DCMAKE_PREFIX_PATH=%EXTERN_PATH%\DevIL;%EXTERN_PATH%\DevIL\lib\x64\Release^
 -DBOOST_ROOT=C:\Development\boost_1_64_0 ..
popd
