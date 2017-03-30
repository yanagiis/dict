add_library(dict dict.c)

target_include_directories(dict PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
set_target_properties(dict PROPERTIES C_STANDARD 99)
install(TARGETS dict
    EXPORT dict
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    )
