#!/bin/bash

# 获取主目录（脚本在.vscode目录下，主目录是其上级）
WORKSPACE_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)

# 项目路径配置
PROJECT_BASE_DIR="$WORKSPACE_DIR/Src"
INSIGHT_DIR="$PROJECT_BASE_DIR/Insight"
LAUNCHER_DIR="$PROJECT_BASE_DIR/Launcher"
UPLOAD_DIR="$PROJECT_BASE_DIR/Upload"

# 构建输出目录（全构建时统一用build/all目录，避免与单独构建冲突）
BUILD_BASE_DIR="$WORKSPACE_DIR/Build"
INSIGHT_BUILD_DIR="$BUILD_BASE_DIR/Insight"
LAUNCHER_BUILD_DIR="$BUILD_BASE_DIR/Launcher"
UPLOAD_BUILD_DIR="$BUILD_BASE_DIR/Upload"
ALL_BUILD_DIR="$BUILD_BASE_DIR/All"  # 全构建专用目录

# 构建函数（支持单个项目和全构建）
build_project() {
    local proj_name=$1
    local build_dir=$2

    echo "===== 开始构建 $proj_name ====="

    # 全构建时检查所有项目目录
    if [ "$proj_name" = "All" ]; then
        if [ ! -d "$INSIGHT_DIR" ] || [ ! -d "$LAUNCHER_DIR" ] || [ ! -d "$UPLOAD_DIR" ]; then
            echo "错误：部分子项目目录不存在！"
            exit 1
        fi
    else
        # 单个项目构建时检查对应目录
        local src_dir="$PROJECT_BASE_DIR/$proj_name"
        if [ ! -d "$src_dir" ]; then
            echo "错误：项目目录 $src_dir 不存在！"
            exit 1
        fi
    fi

    # 创建并进入构建目录
    mkdir -p "$build_dir" && cd "$build_dir" || {
        echo "错误：无法创建构建目录 $build_dir"
        exit 1
    }

    # 调用CMake，传递BUILD_TARGET参数（适配All和单个项目）
    cmake "$WORKSPACE_DIR" \
        -DBUILD_TARGET="$proj_name" \
        -DCMAKE_BUILD_TYPE=Debug && \
    make -j4 || {
        echo "===== $proj_name 构建失败 ====="
        exit 1
    }

    cd "$WORKSPACE_DIR"
    echo "===== $proj_name 构建成功 ====="
}

# 运行函数（单个项目运行，全构建不自动运行）
run_project() {
    local proj_name=$1
    local build_dir=$2

    echo "===== 开始运行 $proj_name ====="
    local exec_path="$build_dir/$proj_name"
    if [ -f "$exec_path" ]; then
        "$exec_path" || {
            echo "===== $proj_name 运行失败 ====="
            exit 1
        }
    else
        echo "错误：可执行文件 $exec_path 不存在！"
        exit 1
    fi
    echo "===== $proj_name 运行结束 ====="
}

# 清理函数
clean_all() {
    echo "===== 清理所有构建文件 ====="
    if [ -d "$BUILD_BASE_DIR" ]; then
        rm -rf "$BUILD_BASE_DIR"
        echo "已删除构建目录：$BUILD_BASE_DIR"
    else
        echo "没有需要清理的构建文件"
    fi
    echo "===== 清理完成 ====="
}

# 主逻辑（新增All处理）
case $1 in
    "Insight")
        build_project "Insight" "$INSIGHT_BUILD_DIR"
        run_project "Insight" "$INSIGHT_BUILD_DIR"
        ;;
    "Launcher")
        build_project "Launcher" "$LAUNCHER_BUILD_DIR"
        run_project "Launcher" "$LAUNCHER_BUILD_DIR"
        ;;
    "Upload")
        build_project "Upload" "$UPLOAD_BUILD_DIR"
        run_project "Upload" "$UPLOAD_BUILD_DIR"
        ;;
    "All")  # 全构建逻辑（只构建不自动运行，避免多程序同时启动）
        build_project "All" "$ALL_BUILD_DIR"
        echo "===== 全构建完成，可手动运行各项目 ====="
        ;;
    "Clean")
        clean_all
        ;;
    *)
        echo "用法: $0 [Insight|Launcher|Upload|All|Clean]"
        exit 1
        ;;
esac