cmake_minimum_required(VERSION 3.16)
project(Example)


find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})


set(INC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MAC "${CMAKE_CURRENT_SOURCE_DIR}/macros")
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")


add_executable(example
    "${INC}/ActionInitialization.hh"
    "${INC}/DetectorConstruction.hh"
    "${INC}/DetectorHit.hh"
    "${INC}/DataManager.hh"
    "${INC}/DataMessenger.hh"
    "${INC}/EventAction.hh"
    "${INC}/PhysicsList.hh"
    "${INC}/PrimaryGeneratorAction.hh"
    "${INC}/SensitiveDetector.hh"

    "${SRC}/ActionInitialization.cc"
    "${SRC}/DetectorConstruction.cc"
    "${SRC}/DetectorHit.cc"
    "${SRC}/DataManager.cc"
    "${SRC}/DataMessenger.cc"
    "${SRC}/EventAction.cc"
    "${SRC}/Main.cc"
    "${SRC}/PhysicsList.cc"
    "${SRC}/PrimaryGeneratorAction.cc"
    "${SRC}/SensitiveDetector.cc"
)

target_include_directories(example PRIVATE "${INC}")
target_link_libraries(example PRIVATE ${Geant4_LIBRARIES})


set(MACRO_FILES
    "init_vis.mac"
)

foreach(file ${MACRO_FILES})
    configure_file("${MAC}/${file}" "${PROJECT_BINARY_DIR}/macros/${file}" COPYONLY)
endforeach()