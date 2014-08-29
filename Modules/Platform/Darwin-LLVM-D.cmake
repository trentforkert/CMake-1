# Enable rpath support for 10.5 and greater where it is known to work.
if("${DARWIN_MAJOR_VERSION}" GREATER 8)
  set(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG "-L=-rpath=")
endif()
