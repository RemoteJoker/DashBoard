cmake_minimum_required(VERSION 3.16)
project(Upload VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 统一 Qt 路径（与 Insight/Launcher 一致）
set(Qt6_DIR "D:/Qt/6.9.3/msvc2022_64/lib/cmake/Qt6")

# 查找 Qt 核心组件（动态库基础依赖）
find_package(Qt6 REQUIRED COMPONENTS Core Network)  # 网络模块用于上传功能

# 启用 Qt 元对象编译（动态库必须）
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)  # 如需资源文件保留，无则可注释

# 收集源文件（直接放在 Upload 根目录，无额外子目录）
file(GLOB SOURCES
    main.cpp          # 动态库入口/核心逻辑
    UploadManager.cpp # 上传管理类
    NetworkHelper.cpp # 网络请求类
)

# 收集头文件（与源文件对应，放在根目录）
file(GLOB HEADERS
    Upload_global.h   # 动态库导出宏头文件（必需）
    UploadManager.h
    NetworkHelper.h
)

# 关键：创建动态库（SHARED 表示动态库）
qt_add_library(Upload SHARED
    ${SOURCES}
    ${HEADERS}
)

# 动态库符号导出（与 Upload_global.h 中的宏对应，必需）
target_compile_definitions(Upload PRIVATE
    UPLOAD_LIBRARY
)

# 链接 Qt 库（仅保留核心依赖，无多余组件）
target_link_libraries(Upload PRIVATE
    Qt6::Core
    Qt6::Network
)

# 头文件包含（允许其他项目引用）
target_include_directories(Upload PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  # 直接引用根目录下的头文件
)

# 设置输出目录（与其他项目统一，方便引用）
set_target_properties(Upload PROPERTIES
    # Windows 动态库（.dll）输出目录
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
    # 非 Windows 动态库（.so/.dylib）输出目录
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
    VERSION ${PROJECT_VERSION}
)