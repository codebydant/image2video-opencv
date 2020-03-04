##############################################################################
# CMAKE CONFIGURATION
##############################################################################
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(image2video VERSION 1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

message("\n" "=========================================")
message("Project: ${PROJECT_NAME} ")
message("=========================================")

# set corresponding library directory
set(OpenCV_DIR /opt/opencv-4.1.2/build)
# set bin folder ON/OFF
# (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)
##############################################################################
# LIBRARIES CONFIG FILE
##############################################################################
message("***********************")
message("Boost Library")
message("***********************")

find_package(Boost REQUIRED system filesystem)
if(Boost_FOUND)
    message(STATUS "Boost status:")
    message(STATUS "    version: ${Boost_LIB_VERSION}")
else()
     message(FATAL_ERROR "    ERROR: Boost ${Boost_LIB_VERSION} not found")    
endif()

message("***********************")
message("OpenCV Library")
message("***********************")

find_package(OpenCV 4 PATHS ${OpenCV_DIR} QUIET)
if(OpenCV_FOUND)
   	message(STATUS "OpenCV status:")
   	message(STATUS "    version: ${OpenCV_VERSION}")
else()
    message(WARNING "   OpenCV 4 not found, attempting 3.4 ...")
    find_package(OpenCV 3.4 REQUIRED QUIET)
    if(OpenCV_FOUND)
        message(STATUS "OpenCV status:")
   		  message(STATUS "    version: ${OpenCV_VERSION}")
    else()
        message(FATAL_ERROR "    ERROR: OpenCV ${OpenCV_VERSION} not found")
    endif()
endif()

##############################################################################
# HEADERS DIRECTORY
##############################################################################
include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS} 
)

##############################################################################
# LIBRARIES DIRECTORY
##############################################################################
link_directories(
	${OpenCV_LIBRARIES}
  ${Boost_LIBRARY_DIRS}              
)

##############################################################################
# SOURCE CODE
##############################################################################
set(MAIN_SOURCE "src/image2video.cpp"
)

##############################################################################
# EXECUTABLES
##############################################################################
add_executable(${PROJECT_NAME}             
               ${MAIN_SOURCE}
)
               
##############################################################################
# TARGET LIBRARIES
##############################################################################
target_link_libraries(${PROJECT_NAME}
                      ${OpenCV_LIBS}
                      ${Boost_LIBRARIES}
)    
                
message("=========================================")
message("Project: ${PROJECT_NAME} COMPILED WITH CMAKE " ${CMAKE_VERSION})
message("=========================================")
