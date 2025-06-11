message("SUBFOLDER") #è di src
message(${CMAKE_CURRENT_BINARY_DIR}) 
message(${CMAKE_BINARY_DIR})
message(${CMAKE_SOURCE_DIR}) 
message(${CMAKE_CURRENT_SOURCE_DIR}) 
message(${PROJECT_NAME})
message(${CMAKE_PROJECT_NAME}) 
#qua current è src

list(APPEND src_headers "${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp") #se aggiungo file header devo aggiungere questa
list(APPEND src_headers "${CMAKE_CURRENT_SOURCE_DIR}/PolyhedronMesh.hpp")


list(APPEND src_sources "${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp")#se aggiungo cpp qua



list(APPEND src_includes ${CMAKE_CURRENT_SOURCE_DIR})


set(src_headers ${src_headers} PARENT_SCOPE)
set(src_sources ${src_sources} PARENT_SCOPE)
set(src_includes ${src_includes} PARENT_SCOPE)