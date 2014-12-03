# Set up the project
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(ej299)
set(target ej299)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Locate sources and headers for this project
#----------------------------------------------------------------------------

# NB: headers are included so they will show up in IDEs
# NOTE: [^.]*.cc means match all files ending in .cc
# 	except those that start with a "." (period) (hidden)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE sources  
	${SRC_DIR}/[^.]*.cc 
	${SRC_DIR}/[^.]*.cpp 
	${SRC_DIR}/[^.]*.cxx 
	${SRC_DIR}/[^.]*.c
)

set(INC_DIR ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE headers 
	${INC_DIR}/[^.]*.hh 
	${INC_DIR}/[^.]*.h 
	${INC_DIR}/[^.]*.hpp 
	${INC_DIR}/[^.]*.hxx 
)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Set up Geant4
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
message(STATUS "Geant4_DIR = ${Geant4_DIR}")
message(STATUS "Geant4_USE_FILE = ${Geant4_USE_FILE}")
message(STATUS "Cmake module path = ${CMAKE_MODULE_PATH}")

# Setup Cern ROOT
#----------------------------------------------------------------------------
include(FindROOT.cmake)
include_directories( ${ROOT_INCLUDE_DIR} )

# Set up Gex
#----------------------------------------------------------------------------
include_directories($ENV{GEX_INCLUDE_DIR})

# Set up executable
#----------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -pipe -ftls-model=initial-exec -pthread -std=c++14")
add_executable(${target} main.cc ${sources} ${dictionaries} ${headers})
target_link_libraries(${target} ${Geant4_LIBRARIES})
target_link_libraries(${target} ${ROOT_LIBRARIES})
target_link_libraries(${target} $ENV{GEX_LIBS})
