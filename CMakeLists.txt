cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(bulk VERSION 0.0.1)
endif()

#!!! for correct build on Windows set BOOST_ROOT environment variable !!!

set(Boost_NO_BOOST_CMAKE ON)
#set(Boost_NO_SYSTEM_PATHS TRUE)

if (WIN32)  
  set(Boost_ARCHITECTURE "-x32")
  
  set(BOOST_USE_STATIC_LIBS ON)
  set(BOOST_USE_MULTITHREADED ON)
  set(BOOST_USE_STATIC_RUNTIME ON)
endif()

find_package(Boost COMPONENTS system filesystem REQUIRED)

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_subdirectory("${PROJECT_SOURCE_DIR}/googletest" "googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

configure_file(version.h.in version.h)

add_executable(bulk main.cpp)
add_library(bulk_lib bulk_manager.h bulk_manager.cpp single_bulk.h single_bulk.cpp)
add_executable(test_bulk test_bulk.cpp)

set_target_properties(bulk bulk_lib test_bulk
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(bulk_lib PROPERTIES
    #COMPILE_DEFINITIONS #BOOST_FILESYSTEM_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(bulk_lib
    PRIVATE "${CMAKE_BINARY_DIR}" ${Boost_INCLUDE_DIRS}
)

target_link_libraries(bulk_lib PRIVATE 
    ${Boost_LIBRARIES}
)

target_link_libraries(bulk PRIVATE
    ${Boost_LIBRARIES}
    bulk_lib 
)

target_link_libraries(test_bulk PRIVATE
     bulk_lib gtest gmock gtest_main
)

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )
    target_compile_options(bulk_lib PRIVATE
        /W4
    )
    target_compile_options(test_bulk PRIVATE
       /W4
    )
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(bulk_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_bulk test_bulk)