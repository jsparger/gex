#----------------------------------------------------------------------------
# Set up the project

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Gex)
set(target Gex)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#----------------------------------------------------------------------------
# Locate sources and headers for this project

# NB: headers are included so they will show up in IDEs
# NOTE: [^.]*.cc means match all files ending in .cc
# 	except those that start with a "." (period) (hidden)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/gex)
file(GLOB_RECURSE sources  
	${SRC_DIR}/[^.]*.cc 
	${SRC_DIR}/[^.]*.cpp 
	${SRC_DIR}/[^.]*.cxx 
	${SRC_DIR}/[^.]*.c
)

set(INC_DIR ${PROJECT_SOURCE_DIR}/include/gex)
add_definitions(-DGEX_INCLUDE_DIR=${INC_DIR})
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


#----------------------------------------------------------------------------
# Setup Cern ROOT

include(FindROOT.cmake)
include_directories( ${ROOT_INCLUDE_DIR} )

# # Set up CLHEP #
# #----------------------------------------------------------------------------
# # clhep libs
# # apparently only this one lib needs to be loaded.
# file(GLOB clheplibs $ENV{CLHEP_LIB_DIR}/libCLHEP.so)
# message(STATUS ${clheplibs})


#----------------------------------------------------------------------------
# Add the library
#
# TODO: THIS SUCKS!: Geant4 sets compilation flags, but they include a -Wshadow which causes a ton of useless warnings. There must be a better way to remove it than this.
# Cmake flags from Geant4 =  -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -ftls-model=initial-exec -pthread -std=c++11
# set the cmake flags minus -Wshadow
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -pipe -ftls-model=initial-exec -pthread -std=c++14")

add_library(${target} SHARED ${sources} ${headers})
target_link_libraries(${target} ${Geant4_LIBRARIES})
target_link_libraries(${target} ${ROOT_LIBRARIES})
# target_link_libraries(${target} ${clheplibs})