# Specify the necessary includes and required modules
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../model)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../helper)
include_directories(${NS3_INCLUDE_DIR}/core)
include_directories(${NS3_INCLUDE_DIR}/internet)
include_directories(${NS3_INCLUDE_DIR}/point-to-point)
include_directories(${NS3_INCLUDE_DIR}/applications)

build_lib_example(
    NAME sagin-example
    SOURCE_FILES sagin-example.cc
    LIBRARIES_TO_LINK ${libsagin} ${libcore} ${libinternet} ${libpoint_to_point} ${libapplications} ${libnetwork}
)
