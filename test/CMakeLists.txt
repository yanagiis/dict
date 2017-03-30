find_package(unity MODULE REQUIRED)

add_executable(test_dict test.c)
target_include_directories(test_dict
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${UNITY_INCLUDE_DIRS})
target_link_libraries(test_dict dict ${UNITY_LIBRARIES})
