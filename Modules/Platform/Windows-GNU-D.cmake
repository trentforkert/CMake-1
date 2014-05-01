include(Platform/Windows-GNU)
__windows_compiler_gnu(D)

# Set these to spaces to prevent MSVC's flags from being passed to GDC
set(CMAKE_D_CREATE_CONSOLE_EXE " ")
set(CMAKE_D_CREATE_WIN32_EXE " ")
set(CMAKE_D_EXE_LINKER_FLAGS " ")
