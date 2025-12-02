# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.12...3.31)

project( lp_solver )


# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()

endif()


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()

endif()

# include for local directory

# include for local package


# Creating entries for target: lp_solver
# ############################

add_executable( lp_solver  src/mainMin.cpp )
# add_executable( lp_solver  src/main_no8.cpp )
# add_executable( lp_solver  src/main.cpp )
# add_executable( lp_solver  src/mainFull.cpp )
# add_executable( lp_solver  src/c4_finder.cpp )

add_to_cached_list( CGAL_EXECUTABLE_TARGETS lp_solver )

# Link the executable to CGAL and third-party libraries
target_link_libraries(lp_solver PRIVATE CGAL::CGAL )

