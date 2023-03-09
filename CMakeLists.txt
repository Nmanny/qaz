cmake_minimum_required(VERSION 3.23)
project(Tannkii)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tannkii Tannkii.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


target_link_libraries(Tannkii PRIVATE sfml-graphics)
target_compile_features(Tannkii PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Tannkii POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Tannkii> $<TARGET_FILE_DIR:Tannkii> COMMAND_EXPAND_LISTS)
endif()