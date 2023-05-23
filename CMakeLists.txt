cmake_minimum_required(VERSION 3.16)

project(
    "2d-plat"
    LANGUAGES
    CXX
    VERSION
    0.0.0
)


# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
# 	"${CMAKE_SOURCE_DIR}/cmake/"
# )

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-O2
	-std=c17
)
add_executable(app
	${SRC_FILES}
)

# target_include_directories(app
# 	PRIVATE
# 	"${PROJECT_SOURCE_DIR}/include"
# 	"${PROJECT_SOURCE_DIR}/include/objects"
# )

find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)
include_directories(
	${SDL2_INCLUDE_DIRS}
	# ${SDL2_IMAGE_INCLUDE_DIRS}
	# ${SDL2_TTF_INCLUDE_DIRS}
)
target_link_libraries(app
	${SDL2_LIBRARIES}
	# ${SDL2_IMAGE_LIBRARIES}
	# ${SDL2_TTF_LIBRARIES}
	m
)

set_target_properties(app
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin
)
