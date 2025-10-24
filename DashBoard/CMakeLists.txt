cmake_minimum_required(VERSION 3.10)
project(DashBoard)

# 设置全局编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)  # 可被命令行覆盖（如-DCMAKE_BUILD_TYPE=Release）

add_compile_options(-Wall -g)

# 子项目路径定义
set(INSIGHT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src/Insight)
set(LAUNCHER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src/Launcher)
set(UPLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src/Upload)

# 检查子项目CMakeLists.txt是否存在
if(NOT EXISTS ${INSIGHT_DIR}/CMakeLists.txt)
    message(FATAL_ERROR "Insight子项目CMake不存在: ${INSIGHT_DIR}")
endif()
if(NOT EXISTS ${LAUNCHER_DIR}/CMakeLists.txt)
    message(FATAL_ERROR "Launcher子项目CMake不存在: ${LAUNCHER_DIR}")
endif()
if(NOT EXISTS ${UPLOAD_DIR}/CMakeLists.txt)
    message(FATAL_ERROR "Upload子项目CMake不存在: ${UPLOAD_DIR}")
endif()

# -------------------------- 核心：通过脚本参数控制构建目标 --------------------------
# 接收脚本传递的参数（例如：-DBUILD_TARGET=Insight）
# 若未传递参数，默认全构建
set(BUILD_TARGET "" CACHE STRING "指定要构建的子项目（Insight/Launcher/Upload）")

# 根据BUILD_TARGET参数设置子项目开关
if(BUILD_TARGET STREQUAL "Insight")
    # 只构建Insight
    set(BUILD_INSIGHT ON)
    set(BUILD_LAUNCHER OFF)
    set(BUILD_UPLOAD OFF)
elseif(BUILD_TARGET STREQUAL "Launcher")
    # 只构建Launcher
    set(BUILD_INSIGHT OFF)
    set(BUILD_LAUNCHER ON)
    set(BUILD_UPLOAD OFF)
elseif(BUILD_TARGET STREQUAL "Upload")
    # 只构建Upload
    set(BUILD_INSIGHT OFF)
    set(BUILD_LAUNCHER OFF)
    set(BUILD_UPLOAD ON)
else()
    # 无效参数
    message(FATAL_ERROR "无效的BUILD_TARGET: ${BUILD_TARGET}，可选值：Insight/Launcher/Upload")
endif()

# -------------------------- 添加子项目 --------------------------
if(BUILD_INSIGHT)
    add_subdirectory(${INSIGHT_DIR} Build/Insight)
endif()
if(BUILD_LAUNCHER)
    add_subdirectory(${LAUNCHER_DIR} Build/Launcher)
endif()
if(BUILD_UPLOAD)
    add_subdirectory(${UPLOAD_DIR} Build/Upload)
endif()

# 定义"all"目标（依赖所有启用的子项目）
add_custom_target(full_build
    DEPENDS 
    $<TARGET_NAME_IF_EXISTS:Insight>
    $<TARGET_NAME_IF_EXISTS:Launcher>
    $<TARGET_NAME_IF_EXISTS:Upload>
)