cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME bpl)
project(${PROJECT_NAME})

# Set the base path for the current module
set(MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Common Sources
file(GLOB_RECURSE bpl_common_sources ${MODULE_PATH}/common/*.c*)

# Common libraries
set(BPL_LIBS bridge ubus nl-3 nl-route-3)

find_package(elpp REQUIRED)

# UGW
if (TARGET_PLATFORM STREQUAL "ugw")
    
    # UGW specific includes
    include_directories(${MODULE_PATH}/ugw/cfg/cal)

    # Platform specific includes
    include_directories(${PLATFORM_BUILD_DIR}/libnl-3.2.25/include)
    include_directories(${PLATFORM_BUILD_DIR}/linux-lantiq_xrx500/bridge-utils-1.4/libbridge)
    include_directories(${PLATFORM_INCLUDE_DIR})

    # libbridge 
    link_directories(${PLATFORM_BUILD_DIR}/linux-lantiq_xrx500/bridge-utils-1.4/libbridge)

    # UGW specific sources
    file(GLOB_RECURSE bpl_platform_sources ${MODULE_PATH}/ugw/*.c*)

    # UGW specific libraries
    list(APPEND BPL_LIBS ugwhelper msgapi cal capi blobmsg_json)

elseif (TARGET_PLATFORM STREQUAL "rdkb")

    # Platform specific includes
    include_directories(${PLATFORM_INCLUDE_DIR})
    include_directories(${PLATFORM_INCLUDE_DIR}/libnl3)
    include_directories(${PLATFORM_INCLUDE_DIR}/bridge-utils)

    if (PASSIVE_MODE)
        add_definitions(-DBPL_PASSIVE_MODE)
    endif()

    # RDKB specific sources
    file(GLOB_RECURSE bpl_platform_sources ${MODULE_PATH}/rdkb/*.c*)

    list(APPEND BPL_LIBS dl swpal slibc)

else()

    message(WARNING "${BoldWhite}Skipping ${BoldGreen}${PROJECT_NAME}${BoldWhite} build for unsupported platform...${ColourReset}")
    return()

endif()

message("${BoldWhite}Preparing ${BoldGreen}${PROJECT_NAME}${BoldWhite} for the ${BoldGreen}${TARGET_PLATFORM}${BoldWhite} platform${ColourReset}")

# Build the library
add_library(${PROJECT_NAME} SHARED ${bpl_common_sources} ${bpl_platform_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${${PROJECT}_VERSION_STRING} SOVERSION ${${PROJECT}_VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} PRIVATE mapf::elpp common ${BPL_LIBS})

# Install
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

install(TARGETS ${PROJECT_NAME} EXPORT bplConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(EXPORT bplConfig NAMESPACE mapf:: DESTINATION lib/cmake/${PROJECT_NAME})

if(BUILD_TESTS)
  add_subdirectory(test)
endif()
