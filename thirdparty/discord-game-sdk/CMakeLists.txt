set(DISCORD_GAMESDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(DISCORD_GAMESDK_SOURCE_DIR "${DISCORD_GAMESDK_ROOT}/src")
set(DISCORD_GAMESDK_LIB_DIR "${DISCORD_GAMESDK_ROOT}/lib")
set(DISCORD_GAMESDK_LIB_IMP "${DISCORD_GAMESDK_LIB_DIR}/discord_game_sdk.dll.lib")
set(DISCORD_GAMESDK_LIB_BIN "${DISCORD_GAMESDK_LIB_DIR}/discord_game_sdk.dll")
set(DISCORD_GAMESDK_BIN_RUNTIME "${CMAKE_CURRENT_BINARY_DIR}/discord.dll" PARENT_SCOPE)
set(DISCORD_GAMESDK_LIB_BIN_RUNTIME ${DISCORD_GAMESDK_LIB_BIN} PARENT_SCOPE)
set(DISCORD_GAMESDK_INCLUDE_PATH "${DISCORD_GAMESDK_ROOT}/src" PARENT_SCOPE)
set(DISCORD_GAMESDK_LINK_PATH "${DISCORD_GAMESDK_ROOT}/lib" PARENT_SCOPE)
set(DISCORD_GAMESDK_SOURCES
        "${DISCORD_GAMESDK_SOURCE_DIR}/achievement_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/achievement_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/activity_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/activity_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/application_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/application_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/core.h" "${DISCORD_GAMESDK_SOURCE_DIR}/core.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/discord.h" "${DISCORD_GAMESDK_SOURCE_DIR}/event.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/ffi.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/image_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/image_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/lobby_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/lobby_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/network_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/network_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/overlay_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/overlay_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/relationship_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/relationship_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/storage_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/storage_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/store_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/store_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/types.h" "${DISCORD_GAMESDK_SOURCE_DIR}/types.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/user_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/user_manager.cpp"
        "${DISCORD_GAMESDK_SOURCE_DIR}/voice_manager.h"
        "${DISCORD_GAMESDK_SOURCE_DIR}/voice_manager.cpp"
        )
set(DISCORD_GAMESDK_IMPORT_TARGET "discord-import")
set(DISCORD_GAMESDK_TARGET "discord")

if (UNIX)
    set(DISCORD_GAMESDK_LIB_BIN "${DISCORD_GAMESDK_LIB_DIR}/discord_game_sdk.so")
    set(DISCORD_GAMESDK_BIN_RUNTIME "${CMAKE_CURRENT_BINARY_DIR}/libdiscord.so" PARENT_SCOPE)
    set(DISCORD_GAMESDK_LIB_BIN_RUNTIME "${CMAKE_CURRENT_BINARY_DIR}/discord_game_sdk.so" PARENT_SCOPE)
endif ()

add_library(${DISCORD_GAMESDK_IMPORT_TARGET} SHARED IMPORTED)
set_target_properties(${DISCORD_GAMESDK_IMPORT_TARGET} PROPERTIES
        IMPORTED_LOCATION "${DISCORD_GAMESDK_LIB_BIN}"
        )

if (WIN32)
    set_target_properties(${DISCORD_GAMESDK_IMPORT_TARGET} PROPERTIES
            IMPORTED_IMPLIB "${DISCORD_GAMESDK_LIB_IMP}"
            )
endif ()

add_library(${DISCORD_GAMESDK_TARGET} SHARED
        ${DISCORD_GAMESDK_SOURCES}
        )
set_target_properties(${DISCORD_GAMESDK_TARGET} PROPERTIES
        BUILD_WITH_INSTALL_RPATH FALSE
        LINK_FLAGS "-Wl,-rpath=$ORIGIN"
        )
target_include_directories(${DISCORD_GAMESDK_TARGET} PUBLIC
        ${DISCORD_GAMESDK_SOURCE_DIR}
        )
target_link_libraries(${DISCORD_GAMESDK_TARGET} PRIVATE
        ${DISCORD_GAMESDK_IMPORT_TARGET}
        )

if (WIN32)
    include(GenerateExportHeader)
    set_target_properties(${DISCORD_GAMESDK_TARGET} PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS ON
            PREFIX ""
            )
endif ()