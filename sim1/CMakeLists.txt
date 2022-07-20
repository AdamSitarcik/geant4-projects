cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation1)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACROS
  "*.mac"
)

file(COPY ${MACROS} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES
  "*.dat"
)

file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})


add_executable(sim1 sim1.cc ${sources} ${headers})
target_link_libraries(sim1 ${Geant4_LIBRARIES})

add_custom_target(Simulation1 DEPENDS sim1)
