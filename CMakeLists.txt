cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JaPaSandbox VERSION 1.0.0 LANGUAGES C CXX)

set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON  OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL       OFF CACHE BOOL " " FORCE)
    
add_executable(Server Server.cpp Player/Player.h Player/Player.cpp Utility/Structs.h
											Networking/Server.h Networking/Server.cpp Networking/Client.h Networking/Client.cpp Networking/Connection.h Networking/Connection.cpp 
											Networking/Messages/Message.h Networking/Messages/Message.cpp
											Networking/Messages/MessageTrackRequest.h Networking/Messages/MessageTrackRequest.cpp 
											Networking/Messages/MessageTrackResponse.h Networking/Messages/MessageTrackResponse.cpp
											Networking/Messages/MessageDataRequest.h Networking/Messages/MessageDataRequest.cpp
											Networking/Messages/MessageDataResponse.h Networking/Messages/MessageDataResponse.cpp
											Networking/Messages/MessageFilesRequest.h Networking/Messages/MessageFilesRequest.cpp
											Networking/Messages/MessageFilesResponse.h Networking/Messages/MessageFilesResponse.cpp)
											
add_executable(Client Client.cpp Player/Player.h Player/Player.cpp Utility/Structs.h
											Networking/Server.h Networking/Server.cpp Networking/Client.h Networking/Client.cpp Networking/Connection.h Networking/Connection.cpp 
											Networking/Messages/Message.h Networking/Messages/Message.cpp 
											Networking/Messages/MessageTrackRequest.h Networking/Messages/MessageTrackRequest.cpp
											Networking/Messages/MessageTrackResponse.h Networking/Messages/MessageTrackResponse.cpp
											Networking/Messages/MessageDataRequest.h Networking/Messages/MessageDataRequest.cpp
											Networking/Messages/MessageDataResponse.h Networking/Messages/MessageDataResponse.cpp
											Networking/Messages/MessageFilesRequest.h Networking/Messages/MessageFilesRequest.cpp
											Networking/Messages/MessageFilesResponse.h Networking/Messages/MessageFilesResponse.cpp)

add_custom_target(BoostLibs
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Deps/boost_1_75_0/
    COMMAND ./bootstrap.sh "--with-libraries=serialization,exception" "--prefix=bin"
    COMMAND ./b2 "install")

add_library(boost_serialization STATIC IMPORTED)
if (WIN32)
    set_target_properties(boost_serialization PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Deps/boost_1_75_0/bin/lib/libboost_serialization.lib)
elseif(UNIX)
    set_target_properties(boost_serialization PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Deps/boost_1_75_0/bin/lib/libboost_serialization.a)
endif ()

find_package(Threads REQUIRED)

add_subdirectory(Deps/portaudio)
add_subdirectory(Deps/libsndfile)
add_subdirectory(Deps/nanogui)

set_property(TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies")
add_definitions(${NANOGUI_EXTRA_DEFS})
include_directories(${NANOGUI_EXTRA_INCS})

target_include_directories(Server PRIVATE Deps/libsndfile/include)
target_include_directories(Server PRIVATE Deps/boost_1_75_0)
target_link_libraries(Server PRIVATE Threads::Threads)
target_link_libraries(Server PRIVATE portaudio_static)
target_link_libraries(Server PRIVATE sndfile)
target_link_libraries(Server PRIVATE boost_serialization)

target_include_directories(Client PRIVATE Deps/libsndfile/include)
target_include_directories(Client PRIVATE Deps/boost_1_75_0)
target_include_directories(Client PRIVATE Deps/nanogui/include/)
target_link_libraries(Client PRIVATE Threads::Threads)
target_link_libraries(Client PRIVATE portaudio_static)
target_link_libraries(Client PRIVATE sndfile)
target_link_libraries(Client PRIVATE boost_serialization)
target_link_libraries(Client PRIVATE nanogui ${NANOGUI_EXTRA_LIBS})
