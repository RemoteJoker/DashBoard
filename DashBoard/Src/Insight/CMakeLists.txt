cmake_minimum_required(VERSION 3.16)
project(Insight VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定 Qt 路径（确保正确）
set(Qt6_DIR "D:/Qt/6.9.3/msvc2022_64/lib/cmake/Qt6")

# 查找 Qt 组件（QML 必需）
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

# 启用 Qt 工具链
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 收集源文件
file(GLOB SOURCES
    main.cpp
    Global/*.cpp
    Utils/*.cpp
    Service/*.cpp
    Model/*.cpp
)

# 收集头文件
file(GLOB HEADERS
    Global/*.h
    Utils/*.h
    Service/*.h
    Model/*.h
)

qt_add_executable(Insight
    ${SOURCES}
    ${HEADERS}
)

qt_add_qml_module(Insight
    URI Insight
    VERSION ${PROJECT_VERSION}
    QML_FILES
        Qml/Main.qml
    RESOURCE_PREFIX "/qt/qml/Insight"
)

# 链接 Qt 库
target_link_libraries(Insight PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# 包含头文件目录
target_include_directories(Insight PRIVATE
    Global
    Utils
    Service
    Model
)

# 解决 Vulkan 警告
if (Qt6_VERSION VERSION_GREATER_EQUAL 6.5)
    target_compile_definitions(Insight PRIVATE QT_QUICK_BACKEND=software)
endif()

# 设置输出目录
set_target_properties(Insight PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
)