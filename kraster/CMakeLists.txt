file(GLOB_RECURSE KRASTER_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/main.c"

	"${CMAKE_CURRENT_SOURCE_DIR}/utility/logger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/logger.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/io.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/utility/io.c"

	"${CMAKE_CURRENT_SOURCE_DIR}/kraster.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/kraster.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/render.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/render.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/platform.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/platform.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/math.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/math.c"
)

add_executable(${KRASTER_TARGET_NAME} ${KRASTER_SOURCES})

set_compile_options_for_target(${KRASTER_TARGET_NAME})

target_include_directories(${KRASTER_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
 target_link_libraries(${KRASTER_TARGET_NAME} PRIVATE SDL2 m)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:${LIB_NAME}>
		$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()
