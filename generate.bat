@echo off
echo Updating submodules
git submodule update --init --recursive

tools\premake5.exe vs2022