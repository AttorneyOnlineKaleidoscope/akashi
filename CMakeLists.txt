cmake_minimum_required(VERSION 3.7.0)

project(akashi VERSION 1.8.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT KAL_BUILD_OUTPUT)
set(KAL_BUILD_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif()

option(KAL_AKASHI_BUILD_TESTS "(${PROJECT_NAME}) Build ${PROJECT_NAME} tests" ON)
option(KAL_AKASHI_DEBUG_NETWORK "(${PROJECT_NAME}) Debug network" OFF)

if(NOT KAL_BUILD_OUTPUT)
set(KAL_BUILD_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/bin")
endif()

find_package(QT NAMES Qt6)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network WebSockets Sql REQUIRED)

if(NOT KAL_QT_VERSION)
set(KAL_QT_VERSION 6.5.3)
endif()

if(NOT Qt${QT_VERSION_MAJOR}_VERSION VERSION_EQUAL KAL_QT_VERSION)
  message(FATAL_ERROR "Supported version is Qt ${KAL_QT_VERSION}, found: ${Qt${QT_VERSION_MAJOR}_VERSION}")
endif()

add_library(${PROJECT_NAME} STATIC
  src/typedefs.h
  src/testimony_recorder.cpp
  src/serverpublisher.cpp src/serverpublisher.h
  src/server.cpp src/server.h
  src/playerstateobserver.cpp src/playerstateobserver.h
  src/packets.cpp
  src/packet/packet_zz.cpp src/packet/packet_zz.h
  src/packet/packet_setcase.cpp src/packet/packet_setcase.h
  src/packet/packet_rt.cpp src/packet/packet_rt.h
  src/packet/packet_rm.cpp src/packet/packet_rm.h
  src/packet/packet_rd.cpp src/packet/packet_rd.h
  src/packet/packet_rc.cpp src/packet/packet_rc.h
  src/packet/packet_pw.cpp src/packet/packet_pw.h
  src/packet/packet_pr.cpp src/packet/packet_pr.h
  src/packet/packet_pe.cpp src/packet/packet_pe.h
  src/packet/packet_ms.cpp src/packet/packet_ms.h
  src/packet/packet_mc.cpp src/packet/packet_mc.h
  src/packet/packet_ma.cpp src/packet/packet_ma.h
  src/packet/packet_info.h
  src/packet/packet_id.cpp src/packet/packet_id.h
  src/packet/packet_hp.cpp src/packet/packet_hp.h
  src/packet/packet_hi.cpp src/packet/packet_hi.h
  src/packet/packet_generic.cpp src/packet/packet_generic.h
  src/packet/packet_factory.cpp src/packet/packet_factory.h
  src/packet/packet_ee.cpp src/packet/packet_ee.h
  src/packet/packet_de.cpp src/packet/packet_de.h
  src/packet/packet_ct.cpp src/packet/packet_ct.h
  src/packet/packet_ch.cpp src/packet/packet_ch.h
  src/packet/packet_cc.cpp src/packet/packet_cc.h
  src/packet/packet_casea.cpp src/packet/packet_casea.h
  src/packet/packet_askchaa.cpp src/packet/packet_askchaa.h
  src/network/network_socket.cpp src/network/network_socket.h
  src/network/aopacket.cpp src/network/aopacket.h
  src/music_manager.cpp src/music_manager.h
  src/logger/writer_modcall.cpp src/logger/writer_modcall.h
  src/logger/writer_full.cpp src/logger/writer_full.h
  src/logger/u_logger.cpp src/logger/u_logger.h
  src/discord.cpp src/discord.h
  src/db_manager.cpp src/db_manager.h
  src/data_types.h
  src/config_manager.cpp src/config_manager.h
  src/commands/roleplay.cpp
  src/commands/music.cpp
  src/commands/moderation.cpp
  src/commands/messaging.cpp
  src/commands/command_helper.cpp
  src/commands/casing.cpp
  src/commands/authentication.cpp
  src/commands/area.cpp
  src/command_extension.cpp src/command_extension.h
  src/area_data.cpp src/area_data.h
  src/aoclient.cpp src/aoclient.h
  src/akashiutils.h
  src/acl_roles_handler.cpp src/acl_roles_handler.h
)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::WebSockets
  Qt${QT_VERSION_MAJOR}::Sql
)

if(KAL_AKASHI_DEBUG_NETWORK)
target_compile_definitions(${PROJECT_NAME} PRIVATE KAL_AKASHI_DEBUG_NETWORK)
endif()

add_executable(${PROJECT_NAME}-runtime
  src/main.cpp
)

target_include_directories(${PROJECT_NAME}-runtime PUBLIC src)
target_link_libraries(${PROJECT_NAME}-runtime PRIVATE ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}-runtime PROPERTIES RUNTIME_OUTPUT_NAME "${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME}-runtime PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${KAL_BUILD_OUTPUT}")

if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET ${PROJECT_NAME}-runtime PROPERTY WIN32_EXECUTABLE true)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resource/${PROJECT_NAME}.rc")
    target_sources(${PROJECT_NAME}-runtime PRIVATE ${APP_ICON_RESOURCE_WINDOWS})
  endif()
endif()

if(KAL_AKASHI_BUILD_TESTS)
  message(WARNING "${PROJECT_NAME} tests are not yet available.")
endif()
