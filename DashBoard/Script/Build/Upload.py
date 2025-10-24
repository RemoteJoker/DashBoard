import os
import sys
import platform
import shutil

def main():
    current_os = platform.system()
    print(f"Detected OS: {current_os}")

    # 根目录与Upload构建目录（适配动态库项目路径）
    root_dir = os.getcwd()
    build_dir = os.path.join(root_dir, "Build", "Upload")  # Upload专属构建目录
    print(f"Build directory: {build_dir}")

    # 原始Release目录路径（动态库编译输出目录）
    original_release_dir = os.path.join(build_dir, "Release")
    # 动态库文件名（Windows为.dll，Linux为.so，macOS为.dylib）
    if current_os == "Windows":
        lib_name = "Upload.dll"
    elif current_os == "Linux":
        lib_name = "libUpload.so"
    elif current_os == "Darwin":
        lib_name = "libUpload.dylib"
    else:
        print(f"Unsupported OS: {current_os}")
        sys.exit(1)
    lib_path = os.path.join(original_release_dir, lib_name)

    # 检查动态库是否存在（动态库核心输出文件）
    if not os.path.exists(lib_path):
        print(f"Error: Dynamic library not found - {lib_path}")
        sys.exit(1)

    # 1. 彻底清理build/Upload下除Release外的所有文件和文件夹
    print("Cleaning all redundant files and folders...")
    for item in os.listdir(build_dir):
        item_path = os.path.join(build_dir, item)
        if item != "Release":  # 只保留Release目录（动态库输出目录）
            try:
                if os.path.isdir(item_path):
                    shutil.rmtree(item_path)
                    print(f"Deleted folder: {item_path}")
                else:
                    os.remove(item_path)
                    print(f"Deleted file: {item_path}")
            except Exception as e:
                print(f"Warning: Failed to delete {item_path} - {str(e)}")

    # 2. 重命名Release目录为固定的"output"（统一输出目录名）
    new_release_dir = os.path.join(build_dir, "output")
    print(f"Renaming Release to: {new_release_dir}")

    # 若旧的output目录存在，先删除（确保输出目录最新）
    if os.path.exists(new_release_dir):
        shutil.rmtree(new_release_dir)
    # 移动Release目录为output（动态库最终输出目录）
    shutil.move(original_release_dir, new_release_dir)

    # 动态库无需打包，直接提示完成
    print(f"Dynamic library processing completed.")
    print(f"Final library in: {new_release_dir}")
    print(f"Library name: {lib_name}")

if __name__ == "__main__":
    main()