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

    # 新的output目录路径（已在bat脚本中重命名）
    output_dir = os.path.join(build_dir, "output")
    exe_name = "Insight.exe" if current_os == "Windows" else "Insight"
    exe_path = os.path.join(output_dir, exe_name)

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

    # 现在只需要执行打包操作，清理和重命名已在bat脚本中完成
    if current_os == "Windows":
        print("Packaging with windeployqt (including QML files)...")
        windeployqt_path = r"D:\Qt\6.9.3\msvc2022_64\bin\windeployqt.exe"

        if not os.path.exists(windeployqt_path):
            print("Error: windeployqt.exe not found. Update path in script.")
            sys.exit(1)

        try:
            # 正确命令：windeployqt 程序.exe --qmldir "QML目录"
            subprocess.run(
                [windeployqt_path, exe_path, "--qmldir", qml_dir, "--release", "--no-compiler-runtime"],
                check=True,
                capture_output=True,
                text=True
            )
            print(f"Packaging completed. Final files in: {output_dir}")
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