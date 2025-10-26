add_library(
	singly_linked_list
	STATIC
	core/lists/singly_linked_list.c
)

target_include_directories(singly_linked_list
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

add_library(
	stack
	STATIC
	containers/stack.c
)

target_include_directories(stack
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

add_library(
	queue
	STATIC
	containers/queue.c
)

target_include_directories(queue
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(stack PUBLIC singly_linked_list)
target_link_libraries(queue PUBLIC singly_linked_list)
