import os
import sys
import platform
import subprocess
import shutil
import datetime

def setup_logging(project_name):
    """设置日志输出到文件"""
    root_dir = os.getcwd()
    build_dir = os.path.join(root_dir, "Build", project_name)
    log_file = os.path.join(build_dir, "python.out")
    
    # 确保日志目录存在
    os.makedirs(os.path.dirname(log_file), exist_ok=True)
    
    # 创建日志文件并重定向标准输出
    log_stream = open(log_file, 'w', encoding='utf-8')
    sys.stdout = log_stream
    sys.stderr = log_stream
    
    print(f"Python packaging script started at: {datetime.datetime.now()}")
    print(f"Log file: {log_file}")
    return build_dir, log_stream

def main():
    project_name = "Insight"
    build_dir, log_stream = setup_logging(project_name)
    
    try:
        current_os = platform.system()
        print(f"Detected OS: {current_os}")

        # 根目录与构建目录
        root_dir = os.getcwd()
        print(f"Root directory: {root_dir}")
        print(f"Build directory: {build_dir}")

        # output目录路径
        output_dir = os.path.join(build_dir, "output")
        exe_name = "Insight.exe" if current_os == "Windows" else "Insight"
        exe_path = os.path.join(output_dir, exe_name)

        # QML文件所在目录
        qml_dir = os.path.join(root_dir, "Src", "Insight", "Qml")
        print(f"QML directory: {qml_dir}")

        # 检查必要文件/目录是否存在
        print(f"Checking executable: {exe_path}")
        if not os.path.exists(exe_path):
            print(f"Error: Executable not found - {exe_path}")
            print("Available files in output directory:")
            if os.path.exists(output_dir):
                for item in os.listdir(output_dir):
                    item_path = os.path.join(output_dir, item)
                    if os.path.isfile(item_path):
                        size = os.path.getsize(item_path)
                        print(f"  - {item} ({size} bytes)")
                    else:
                        print(f"  - {item}/ (directory)")
            return 1
        else:
            print("Executable found successfully")
            
        print(f"Checking QML directory: {qml_dir}")
        if not os.path.exists(qml_dir):
            print(f"Error: QML directory not found - {qml_dir}")
            return 1
        else:
            print("QML directory found successfully")

        # Windows 打包
        if current_os == "Windows":
            print("Packaging with windeployqt...")
            windeployqt_path = r"D:\Qt\6.9.3\msvc2022_64\bin\windeployqt.exe"

            print(f"Checking windeployqt: {windeployqt_path}")
            if not os.path.exists(windeployqt_path):
                print("Error: windeployqt.exe not found.")
                return 1
            else:
                print("windeployqt.exe found successfully")

            try:
                print(f"Running windeployqt on: {exe_path}")
                print(f"QML directory: {qml_dir}")
                
                # 运行 windeployqt
                result = subprocess.run(
                    [windeployqt_path, exe_path, "--qmldir", qml_dir, "--release", "--no-compiler-runtime"],
                    check=True,
                    capture_output=True,
                    text=True,
                    encoding='utf-8'
                )
                
                print("windeployqt completed successfully!")
                if result.stdout:
                    print("windeployqt output:", result.stdout)
                
                # 列出最终文件
                print("\nFinal directory contents:")
                for item in os.listdir(output_dir):
                    item_path = os.path.join(output_dir, item)
                    if os.path.isfile(item_path):
                        size = os.path.getsize(item_path)
                        print(f"  {item} ({size} bytes)")
                    else:
                        print(f"  {item}/")
                
                print(f"\nPackaging completed at: {datetime.datetime.now()}")
                return 0
                
            except subprocess.CalledProcessError as e:
                print(f"Packaging failed with error code {e.returncode}:")
                print(f"Error output: {e.stderr}")
                if e.stdout:
                    print(f"Standard output: {e.stdout}")
                return 1
            except Exception as e:
                print(f"Unexpected error: {str(e)}")
                return 1

        else:
            print(f"Unsupported OS for packaging: {current_os}")
            return 1
            
    except Exception as e:
        print(f"Fatal error in main: {str(e)}")
        return 1
    finally:
        # 确保日志文件被正确关闭
        if log_stream:
            log_stream.close()

if __name__ == "__main__":
    exit_code = main()
    sys.exit(exit_code)