add_library(dict dict.c)

target_include_directories(dict PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/dict>
)

install(EXPORT dict DESTINATION lib)
install(TARGETS dict
	EXPORT dict
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
