# ------------------------------------------------------------------------------
# Main CMakeLists.txt
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

project("WebServer" VERSION ${PROJECT_VERSION} LANGUAGES CXX)
message(NOTICE "${PROJECT_NAME}: ${PROJECT_VERSION}")

# ------------------------------------------------------------------------------

set(API_LIBRARY "API")
add_subdirectory(${API_LIBRARY})

set(WEB_SERVER_LIBRARY "Server")
add_subdirectory(${WEB_SERVER_LIBRARY})

# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} "main.cpp"
        ${API_LIBRARY}
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${WEB_SERVER_LIBRARY}
        )
