#
# Build configuration
#
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_C_STANDARD 11)
project(practica1)


# Enable ccache by default and as early as possible because project() performs
# checks on the compiler
option(ENABLE_CCACHE "Enable ccache support" ON)
if(ENABLE_CCACHE)
  message(STATUS "Trying to enable ccache")
  find_program(BIN_CCACHE ccache)

  string(ASCII 27 esc)
  if(NOT BIN_CCACHE)
    message(STATUS "${esc}[33mCouldn't locate ccache, disabling ccache...${esc}[0m")
  else()
    # Enable only if the binary is found
    message(STATUS "${esc}[32mUsing compiler cache ${BIN_CCACHE}${esc}[0m")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${BIN_CCACHE})
  endif()
endif()

###############################################################################
## file globbing ##############################################################
###############################################################################
# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables
file(GLOB objs    obj/*.o)

###############################################################################
## target definitions #########################################################
###############################################################################
add_library(practica1 OBJECT src/parser.c ${objs})
add_executable(ping_noc      src/ping_noc.c      $<TARGET_OBJECTS:practica1>)
add_executable(ping_noc_serv src/ping_noc_serv.c $<TARGET_OBJECTS:practica1>)
add_executable(ping_oc       src/ping_oc.c       $<TARGET_OBJECTS:practica1>)
add_executable(ping_oc_serv  src/ping_oc_serv.c  $<TARGET_OBJECTS:practica1>)

# This allows to include files relative to the root of the include directory with a <> pair
target_include_directories(practica1     PUBLIC include)
target_include_directories(ping_noc      PUBLIC include)
target_include_directories(ping_noc_serv PUBLIC include)
target_include_directories(ping_oc       PUBLIC include)
target_include_directories(ping_oc_serv  PUBLIC include)
