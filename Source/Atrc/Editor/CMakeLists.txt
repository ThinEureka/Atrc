FILE(GLOB_RECURSE EDITOR_SRC "*.cpp" "*.h"  "*.inl")
ADD_EXECUTABLE(Editor ${EDITOR_SRC})
FOREACH(_SRC IN ITEMS ${EDITOR_SRC})
    GET_FILENAME_COMPONENT(EDITOR_SRC "${_SRC}" PATH)
    STRING(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" _GRP_PATH "${EDITOR_SRC}")
    STRING(REPLACE "/" "\\" _GRP_PATH "${_GRP_PATH}")
    SOURCE_GROUP("${_GRP_PATH}" FILES "${_SRC}")
ENDFOREACH()

TARGET_INCLUDE_DIRECTORIES(Editor PRIVATE
	${GLEW_INCLUDE_DIRS}
	${glfw3_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Editor PRIVATE
	ImGui GLEW::GLEW glfw ${OPENGL_LIBRARIES}
	Mgr Core AGZUtils cnpy ${STDFS_LD_LIB})