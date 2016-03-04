if (UNIX)
    message("Add cmake include path (Boost)")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/local/include/boost_1_59_0")
endif()

if (WIN32)
    message("Add cmake include path (Boost)")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:\\Program files\\boost\\boost_1_59_0\\")
    message("Add cmake prefix path (Qt)")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\QT\\QT5.5.0\\5.5\\mingw492_32\\")
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Boost 1.59.0 COMPONENTS system thread REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(codes)
add_subdirectory(hammingCodes)
add_subdirectory(cyclicCodes)