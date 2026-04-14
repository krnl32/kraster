file(GLOB_RECURSE KRASTER_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/main.c"

	"${CMAKE_CURRENT_SOURCE_DIR}/utility/logger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/logger.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/io.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/io.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/timer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/timer.c"

	"${CMAKE_CURRENT_SOURCE_DIR}/math/util.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/math/vector.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/math/vector.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/math/matrix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/math/matrix.c"

	"${CMAKE_CURRENT_SOURCE_DIR}/kraster.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/kraster.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/render.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/render.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/platform.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/platform.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/keyboard.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/keyboard.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/mesh.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/mesh.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/triangle.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/triangle.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/light.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/light.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/texture.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/texture.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/camera.h"
)

add_executable(${KRASTER_TARGET_NAME} ${KRASTER_SOURCES})

set_compile_options_for_target(${KRASTER_TARGET_NAME})

# STB
target_sources(${KRASTER_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/utility/stb_image.c")
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
	set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/utility/stb_image.c" PROPERTIES COMPILE_FLAGS "-w")
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
	set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/utility/stb_image.c" PROPERTIES COMPILE_FLAGS "/W0")
endif()

target_include_directories(${KRASTER_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${KRASTER_TARGET_NAME} PRIVATE SDL2 m stb_image)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:${LIB_NAME}>
		$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()
