import os
import sys
import shutil
import configparser

def read_project_version():
    """读取 Config/Project.ini 中的版本号"""
    root_dir = os.getcwd()
    ini_path = os.path.join(root_dir, "Config", "Project.ini")
    
    if not os.path.exists(ini_path):
        print(f"错误：Config/Project.ini 文件不存在 → {ini_path}")
        sys.exit(1)
    
    config = configparser.ConfigParser()
    config.read(ini_path, encoding="utf-8")
    
    if not config.has_section("Project"):
        print("错误：Project.ini 中缺少 [Project] 节点")
        sys.exit(1)
    if not config.has_option("Project", "version"):
        print("错误：Project.ini 中缺少 version 配置项")
        sys.exit(1)
    
    version = config.get("Project", "version").strip()
    if not version:
        print("错误：version 配置项为空")
        sys.exit(1)
    
    print(f"读取到项目版本号 → {version}")
    return version

def check_build_dir(project_name):
    """检查项目构建目录是否存在"""
    root_dir = os.getcwd()
    build_output_dir = os.path.join(root_dir, "Build", project_name, "output")
    if not os.path.exists(build_output_dir):
        print(f"错误：{project_name} 构建输出目录不存在 → {build_output_dir}")
        print(f"请先编译 {project_name} 项目（执行 build_and_run.bat {project_name}）")
        sys.exit(1)
    return build_output_dir

def check_bootconf_db():
    """检查 Config/Databases 目录下的 bootconf.db 是否存在"""
    root_dir = os.getcwd()
    db_path = os.path.join(root_dir, "Config", "Databases", "bootconf.db")
    
    if not os.path.exists(db_path):
        print(f"错误：Config/Databases 目录下未找到 bootconf.db → {db_path}")
        sys.exit(1)
    
    print(f"找到 bootconf.db 数据库 → {db_path}")
    return db_path

def clean_build_dir():
    """清理 Build 目录：保留 DashBoard,删除其他所有目录/文件"""
    root_dir = os.getcwd()
    build_dir = os.path.join(root_dir, "Build")
    
    print("\n=== 开始清理 Build 目录 ===")
    for item in os.listdir(build_dir):
        item_path = os.path.join(build_dir, item)
        if item != "DashBoard":
            try:
                if os.path.isdir(item_path):
                    print(f"删除目录 → {item_path}")
                    shutil.rmtree(item_path)
                else:
                    print(f"删除文件 → {item_path}")
                    os.remove(item_path)
            except Exception as e:
                print(f"警告：删除 {item_path} 失败 → {str(e)}")
    print("Build 目录清理完成！")

def install_software():
    """执行安装逻辑：新增bootconf.db复制到Launcher同级bin目录"""
    root_dir = os.getcwd()
    version = read_project_version()

    # 1. 定义核心目录路径
    main_dashboard_dir = os.path.join(root_dir, "Build", "DashBoard")  # Launcher 主目录（含 Launcher.exe）
    launcher_bin_dir = os.path.join(main_dashboard_dir, "bin")  # Launcher 同级 bin 目录（目标目录）
    sub_software_dir = os.path.join(main_dashboard_dir, "Software")
    insight_version_dir = os.path.join(sub_software_dir, version)
    # Insight 同级目录
    insight_bin_dir = os.path.join(insight_version_dir, "bin")
    insight_configure_dir = os.path.join(insight_version_dir, "configure")

    # 2. 检查 bootconf.db 数据库
    bootconf_db_path = check_bootconf_db()

    # 3. 清理旧目录
    if os.path.exists(main_dashboard_dir):
        print(f"\n正在清理旧安装目录 → {main_dashboard_dir}")
        shutil.rmtree(main_dashboard_dir)

    # 4. 检查构建结果
    print("\n=== 检查项目构建结果 ===")
    launcher_source_dir = check_build_dir("Launcher")
    insight_source_dir = check_build_dir("Insight")

    # 5. 安装 Launcher 到主目录
    print("\n=== 安装 Launcher ===")
    print(f"从 → {launcher_source_dir} → 复制到 → {main_dashboard_dir}")
    shutil.copytree(launcher_source_dir, main_dashboard_dir)
    print("Launcher 安装完成！")

    # 6. 创建所有目录结构
    print("\n=== 创建目录结构 ===")
    # 创建 Launcher 同级 bin 目录（用于放 bootconf.db）
    os.makedirs(launcher_bin_dir, exist_ok=True)
    print(f"创建 Launcher 同级 bin 文件夹 → {launcher_bin_dir}")
    # 创建 Insight 相关目录
    os.makedirs(insight_version_dir, exist_ok=True)
    os.makedirs(insight_bin_dir, exist_ok=True)
    os.makedirs(insight_configure_dir, exist_ok=True)
    print(f"创建 Insight 版本目录 → {insight_version_dir}")
    print(f"创建 Insight 同级 bin 文件夹 → {insight_bin_dir}")
    print(f"创建 Insight 同级 configure 文件夹 → {insight_configure_dir}")

    # 7. 复制 bootconf.db 到 Launcher 同级 bin 目录
    print("\n=== 复制 bootconf.db 数据库 ===")
    target_db_path = os.path.join(launcher_bin_dir, "bootconf.db")
    shutil.copy2(bootconf_db_path, target_db_path)  # copy2 保留文件元信息
    print(f"从 → {bootconf_db_path} → 复制到 → {target_db_path}")
    print("bootconf.db 复制完成！")

    # 8. 安装 Insight 到版本号目录
    print("\n=== 安装 Insight ===")
    print(f"从 → {insight_source_dir} → 复制到 → {insight_version_dir}")
    shutil.copytree(insight_source_dir, insight_version_dir, dirs_exist_ok=True)
    print("Insight 安装完成！")

    # 9. 清理 Build 目录
    clean_build_dir()

    # 10. 输出最终目录结构
    print("\n=== 安装完成！最终目录结构 ===")
    print(f"Build/")
    print(f"└─ DashBoard/                # Launcher 主目录（含 Launcher.exe）")
    print(f"    ├─ bin/                  # Launcher 同级 bin 文件夹")
    print(f"    │   └─ bootconf.db       # 复制的 SQLite 数据库（新增）")
    print(f"    ├─ Launcher.exe          # Launcher 可执行文件")
    print(f"    └─ Software/             # 子 Software 文件夹")
    print(f"        └─ {version}/        # Insight 版本号目录")
    print(f"            ├─ Insight.exe   # Insight 可执行文件")
    print(f"            ├─ bin/          # Insight 同级 bin 文件夹")
    print(f"            ├─ configure/    # Insight 同级 configure 文件夹")
    print(f"            └─ （其他 Insight 依赖文件）")

if __name__ == "__main__":
    print("=====================================")
    print("          开始安装 DashBoard         ")
    print("=====================================")
    
    try:
        install_software()
        print("\n=====================================")
        print("          安装成功！                 ")
        print("=====================================")
    except Exception as e:
        print(f"\n错误：安装失败 → {str(e)}")
        sys.exit(1)