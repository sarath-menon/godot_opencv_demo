
add_executable(cv_godot_demo 
src/main.cpp
src/aruco_functions.cpp
)

target_include_directories(cv_godot_demo PUBLIC include)

target_link_libraries(cv_godot_demo PRIVATE
${OpenCV_LIBS}
comm_lib
fastcdr 
fastrtps
)


