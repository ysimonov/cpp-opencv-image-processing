cmake_minimum_required ( VERSION 3.8 )

PROJECT( cpp-opencv )

SET( NAME_HEADERS "include/header.hpp" )
SET( NAME_MAIN "src/main.cpp" )
SET( NAME_IMAGE_SCANNER "src/image_scanner.cpp" )

# allows cmake to automatically find opencv header files and libraries
find_package( OpenCV REQUIRED )

# header file to include
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

# Add source to this project's executable.
add_executable( cpp-opencv ${NAME_HEADERS} ${NAME_MAIN} ${NAME_IMAGE_SCANNER} )

# link opencv libraries
target_link_libraries( cpp-opencv ${OpenCV_LIBS} )

 if (CMAKE_VERSION VERSION_GREATER 3.12)
   set_property( TARGET cpp-opencv PROPERTY CXX_STANDARD 20 )
 endif()

