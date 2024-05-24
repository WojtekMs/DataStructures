project(Trie)

add_subdirectory(src)
add_subdirectory(test)

add_custom_target(${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME}_exe 
    COMMENT "Executing Trie example"
)

add_custom_target(${PROJECT_NAME}_test
    COMMAND ${PROJECT_NAME}_ut
    COMMENT "Executing Trie tests"
)
