cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR "C:/Users/abhin/workspace_vscode/wxWidgets-3.1.3")
set(wxWidgets_INCLUDE_DIRS "C:/Users/abhin/workspace_vscode/wxWidgets-3.1.3/include")
set(wxWidgets_LIB_DIR "C:/Users/abhin/workspace_vscode/wxWidgets-3.1.3/lib/vc_dll")
set(wxWidgets_LIBRARIES "C:/Users/abhin/workspace_vscode/wxWidgets-3.1.3/lib/vc_dll/wxbase31u.lib" "C:/Users/abhin/workspace_vscode/wxWidgets-3.1.3/lib/vc_dll/wxmsw31u_core.lib")

set(wxWidgets_DEFINITIONS WXUSINGDLL)

project(SoftwareUpdater)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB project_SRCS src/*.cpp)

add_executable(SoftwareUpdater ${project_SRCS})
target_link_libraries(SoftwareUpdater ${wxWidgets_LIBRARIES})
target_include_directories(SoftwareUpdater PRIVATE ${wxWidgets_INCLUDE_DIRS})