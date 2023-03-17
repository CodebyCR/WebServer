# ------------------------------------------------------------------------------
# API - Subdirectory
# ------------------------------------------------------------------------------

set(API_SOURCES
        "Rest.hpp")

add_library(${API_LIBRARY} INTERFACE ${API_SOURCES} )


target_include_directories( ${API_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR} )
