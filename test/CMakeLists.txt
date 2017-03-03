find_library(UNITY_LIB NAMES unity
	PATH ${CMAKE_PREFIX_PATH}/lib)
find_path(UNITY_INC NAMES unity/unity.h
	PATH ${CMAKE_PREFIX_PATH}/include)

add_executable(test_dict test.c)
target_include_directories(test_dict
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${UNITY_INC})
target_link_libraries(test_dict dict ${UNITY_LIB})
