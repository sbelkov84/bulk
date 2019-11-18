cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
   project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
   project(bulk VERSION 0.0.1)
endif()

find_package(Boost COMPONENTS filesystem REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
configure_file(version.h.in version.h)
add_executable(bulk main.cpp)
add_library(bulk_lib bulk_manager.h bulk_manager.cpp single_bulk.h single_bulk.cpp)
set_target_properties(bulk bulk_lib
   PROPERTIES
   CXX_STANDARD 17
   CXX_STANDARD_REQUIRED ON
   LINKER_LANGUAGE CXX
)
set_target_properties(bulk_lib PROPERTIES
   COMPILE_DEFINITIONS #BOOST_FILESYSTEM_DYN_LINK
   INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_include_directories(bulk_lib
   PRIVATE "${CMAKE_BINARY_DIR}" ${Boost_INCLUDE_DIR}
)
target_link_libraries(bulk_lib PRIVATE
   ${Boost_FILESYSTEM_LIBRARY}  ${Boost_SYSTEM_LIBRARY}
#    stdc++fs
)
target_link_libraries(bulk PRIVATE
   bulk_lib #${Boost_LIBRARIES}
)
if (MSVC)
   target_compile_options(bulk PRIVATE
       /W4
   )
   target_compile_options(bulk_lib PRIVATE
       /W4
   )
else ()
   target_compile_options(bulk PRIVATE
       -Wall -Wextra -pedantic -Werror
   )
   target_compile_options(bulk_lib PRIVATE
       -Wall -Wextra -pedantic -Werror
   )
endif()
install(TARGETS bulk RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)