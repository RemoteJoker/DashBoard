import os
import sys
import platform
import subprocess
import shutil

def main():
    current_os = platform.system()
    print(f"Detected OS: {current_os}")

    # 根目录与构建目录
    root_dir = os.getcwd()
    build_dir = os.path.join(root_dir, "Build", "Insight")
    print(f"Build directory: {build_dir}")

    # 原始Release目录路径
    original_release_dir = os.path.join(build_dir, "Release")
    exe_name = "Insight.exe" if current_os == "Windows" else "Insight"
    exe_path = os.path.join(original_release_dir, exe_name)

    # QML文件所在目录（根目录/Src/Insight/Qml/）
    qml_dir = os.path.join(root_dir, "Src", "Insight", "Qml")
    print(f"QML directory: {qml_dir}")

    # 检查必要文件/目录是否存在
    if not os.path.exists(exe_path):
        print(f"Error: Executable not found - {exe_path}")
        sys.exit(1)
    if not os.path.exists(qml_dir):
        print(f"Error: QML directory not found - {qml_dir}")
        sys.exit(1)

    # 1. 彻底清理build/Insight下除Release外的所有文件和文件夹
    print("Cleaning all redundant files and folders...")
    for item in os.listdir(build_dir):
        item_path = os.path.join(build_dir, item)
        if item != "Release":  # 只保留Release目录
            try:
                if os.path.isdir(item_path):
                    shutil.rmtree(item_path)
                    print(f"Deleted folder: {item_path}")
                else:
                    os.remove(item_path)
                    print(f"Deleted file: {item_path}")
            except Exception as e:
                print(f"Warning: Failed to delete {item_path} - {str(e)}")

    # 2. 重命名Release目录为固定的"output"
    new_release_dir = os.path.join(build_dir, "output")
    print(f"Renaming Release to: {new_release_dir}")

    # 若旧的output目录存在，先删除
    if os.path.exists(new_release_dir):
        shutil.rmtree(new_release_dir)
    # 移动Release目录为output
    shutil.move(original_release_dir, new_release_dir)

    # 3. Windows下使用正确的windeployqt命令打包（含QML目录）
    if current_os == "Windows":
        print("Packaging with windeployqt (including QML files)...")
        windeployqt_path = r"D:\Qt\6.9.3\msvc2022_64\bin\windeployqt.exe"
        new_exe_path = os.path.join(new_release_dir, exe_name)

        if not os.path.exists(windeployqt_path):
            print("Error: windeployqt.exe not found. Update path in script.")
            sys.exit(1)

        try:
            # 正确命令：windeployqt 程序.exe --qmldir "QML目录"
            subprocess.run(
                [windeployqt_path, new_exe_path, "--qmldir", qml_dir, "--release", "--no-compiler-runtime"],
                check=True,
                capture_output=True,
                text=True
            )
            print(f"Packaging completed. Final files in: {new_release_dir}")
        except subprocess.CalledProcessError as e:
            print(f"Packaging error: {e.stderr}")
            sys.exit(1)

    elif current_os in ["Linux", "Darwin"]:
        print(f"{current_os} packaging framework - to be implemented.")
    else:
        print(f"Unsupported OS: {current_os}")
        sys.exit(1)

if __name__ == "__main__":
    main()