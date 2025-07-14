@echo off

pushd .\build
del *.exe
del *.pdb
del *.ilk
cl /I ..\include\ /Od /Zi /EHsc /DPLATFORM_WIN32=1 ..\src\main.cpp ..\src\glad.c ..\src\shader.cpp ..\src\utils.cpp ..\src\nmath.cpp  ..\src\Texture2D.cpp ..\src\Game.cpp ..\src\sprite.cpp ..\src\ResourceManager\ResourceManager.cpp /link /DEBUG glfw3_mt.lib opengl32.lib user32.lib gdi32.lib Shell32.lib Kernel32.lib assimp.lib /LIBPATH:..\lib
del *.obj
popd
