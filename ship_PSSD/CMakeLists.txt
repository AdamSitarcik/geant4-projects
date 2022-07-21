cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(SHIP_PSSD_Detector)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

file(GLOB MACROS
"*.mac"
)
file(COPY ${MACROS} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(pssd ship_pssd.cc ${sources} ${headers})
target_link_libraries(pssd ${Geant4_LIBRARIES})

add_custom_target(SHIP_PSSD_Detector DEPENDS pssd)
