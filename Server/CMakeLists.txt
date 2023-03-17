# ------------------------------------------------------------------------------
# Web Server - Subdirectory
# ------------------------------------------------------------------------------

set(WEB_SERVER_SOURCES
        "WebServer.hpp")

add_library(${WEB_SERVER_LIBRARY} INTERFACE ${WEB_SERVER_SOURCES} )


target_include_directories( ${WEB_SERVER_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR} )
