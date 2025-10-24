@echo off
chcp 65001 > nul 2>&1

:: 参数1：指定项目名（Insight/Launcher）
set "PROJECT_NAME=%~1"
if "%PROJECT_NAME%"=="" (
    echo Error: 请指定项目名(Insight/Launcher)
    exit /b 1
)

:: 根目录（当前工作区，即DashBoard）
set "ROOT_DIR=%cd%"
:: 源码目录（根据项目名动态切换）
set "SRC_DIR=%ROOT_DIR%\Src\%PROJECT_NAME%"
:: 构建目录（每个项目单独的构建目录）
set "BUILD_DIR=%ROOT_DIR%\Build\%PROJECT_NAME%"
:: 编译配置
set "CONFIG=Release"
set "PLATFORM=x64"

:: 创建并进入构建目录
mkdir "%BUILD_DIR%" > nul 2>&1
cd /d "%BUILD_DIR%" || (
    echo Error: Cannot enter Build directory: %BUILD_DIR%
    exit /b 1
)

:: 检查源码目录是否存在
if not exist "%SRC_DIR%\CMakeLists.txt" (
    echo Error: CMakeLists.txt not found in %SRC_DIR%
    exit /b 1
)

:: 1. 用CMake生成VS解决方案（动态适配项目）
echo Generating solution for %PROJECT_NAME%...
cmake -B "%BUILD_DIR%" -S "%SRC_DIR%" ^
    -G "Visual Studio 17 2022" -A x64 ^
    -DCMAKE_BUILD_TYPE=%CONFIG% ^
    -DCMAKE_PREFIX_PATH="D:/Qt/6.9.3/msvc2022_64"

if %errorlevel% neq 0 (
    echo Error: CMake generation failed for %PROJECT_NAME%
    exit /b 1
)

:: 2. 用MSBuild编译（动态使用项目名）
echo Building %PROJECT_NAME% with MSBuild...
msbuild "%PROJECT_NAME%.sln" /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /m

:: 编译结果提示
if %errorlevel% equ 0 (
    echo Build successful! Output in: %BUILD_DIR%\%CONFIG%
) else (
    echo Build failed for %PROJECT_NAME%! Check above errors.
    exit /b 1
)

:: 返回根目录
cd /d "%ROOT_DIR%"

:: 执行对应项目的Python脚本
set "PYTHON_SCRIPT=%ROOT_DIR%\Script\Build\%PROJECT_NAME%.py"
if exist "%PYTHON_SCRIPT%" (
    echo Executing %PROJECT_NAME%.py...
    python "%PYTHON_SCRIPT%"
) else (
    echo Warning: %PROJECT_NAME%.py not found in %ROOT_DIR%\Script
    exit /b 1
)