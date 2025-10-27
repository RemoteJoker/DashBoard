@echo off
chcp 65001 > nul 2>&1

set "PROJECT_NAME=%~1"

if "%PROJECT_NAME%"=="" (
    echo "Error: Lack of project name"
    exit /b 1
)

set "ROOT_DIR=%cd%"
set "SRC_DIR=%ROOT_DIR%\Src\%PROJECT_NAME%"
set "BUILD_DIR=%ROOT_DIR%\Build\%PROJECT_NAME%"
set "CONFIG=Release"
set "PLATFORM=x64"

mkdir "%BUILD_DIR%" > nul 2>&1
cd /d "%BUILD_DIR%" || (
    echo Error: Cannot enter Build directory: %BUILD_DIR%
    exit /b 1
)

if not exist "%SRC_DIR%\CMakeLists.txt" (
    echo Error: CMakeLists.txt not found in %SRC_DIR%
    exit /b 1
)

echo Generating solution for %PROJECT_NAME%...
cmake -B "%BUILD_DIR%" -S "%SRC_DIR%" ^
    -G "Visual Studio 17 2022" -A x64 ^
    -DCMAKE_BUILD_TYPE=%CONFIG% ^
    -DCMAKE_PREFIX_PATH="D:/Qt/6.9.3/msvc2022_64"

if %errorlevel% neq 0 (
    echo Error: CMake generation failed for %PROJECT_NAME%
    goto :BuildFailed
)

echo Building %PROJECT_NAME% with MSBuild...
msbuild "%PROJECT_NAME%.sln" ^
    /p:Configuration=%CONFIG% ^
    /p:Platform=%PLATFORM% ^
    /m ^
    /verbosity:detailed ^
    /fl ^
    /flp:logfile="%BUILD_DIR%\msbuild_detailed.log";verbosity=detailed ^
    /flp:errorsonly;logfile="%BUILD_DIR%\msbuild_errors.log"

if %errorlevel% neq 0 (
    echo Build failed for %PROJECT_NAME%! Check above errors.
    goto :BuildFailed
)

echo Build successful! Output in: %BUILD_DIR%\%CONFIG%

:: 编译成功时的处理
echo Performing post-build cleanup and organization for SUCCESS...

set "ORIGINAL_RELEASE_DIR=%BUILD_DIR%\Release"
set "NEW_RELEASE_DIR=%BUILD_DIR%\output"
set "TEMP_DIR=%BUILD_DIR%\_temp_clean"

:: 如果Release目录存在，先将其移动到临时位置
if exist "%ORIGINAL_RELEASE_DIR%" (
    echo Moving Release files to temporary location...
    if exist "%TEMP_DIR%" rmdir /s /q "%TEMP_DIR%"
    mkdir "%TEMP_DIR%"
    xcopy "%ORIGINAL_RELEASE_DIR%\*" "%TEMP_DIR%\" /s /e /y >nul
)

:: 清理整个构建目录（除了临时文件）
echo Cleaning build directory...
cd /d "%ROOT_DIR%"
rmdir /s /q "%BUILD_DIR%" 2>nul
mkdir "%BUILD_DIR%"

:: 将Release文件移回并重命名为output
if exist "%TEMP_DIR%" (
    echo Restoring and renaming to output...
    move "%TEMP_DIR%" "%NEW_RELEASE_DIR%" >nul
    echo Build successful! Clean output in: %NEW_RELEASE_DIR%
    
    :: 返回根目录并执行Python脚本
    cd /d "%ROOT_DIR%"
    set "PYTHON_SCRIPT=%ROOT_DIR%\Script\Build\%PROJECT_NAME%.py"
    if exist "%PYTHON_SCRIPT%" (
        echo Executing %PROJECT_NAME%.py...
        python "%PYTHON_SCRIPT%"
    ) else (
        echo Warning: %PROJECT_NAME%.py not found in %ROOT_DIR%\Script
        exit /b 1
    )
) else (
    echo Warning: No Release files found after build.
    exit /b 1
)

exit /b 0

:BuildFailed
:: 编译失败时的处理
echo Performing post-build cleanup and organization for FAILED build...

set "ERROR_OUTPUT_DIR=%BUILD_DIR%\output"
set "TEMP_ERROR_DIR=%BUILD_DIR%\_temp_errors"

:: 创建临时目录保存错误文件
echo Collecting error files...
if exist "%TEMP_ERROR_DIR%" rmdir /s /q "%TEMP_ERROR_DIR%"
mkdir "%TEMP_ERROR_DIR%"

:: 复制所有错误日志和重要文件到临时目录
if exist "%BUILD_DIR%\msbuild_errors.log" (
    copy "%BUILD_DIR%\msbuild_errors.log" "%TEMP_ERROR_DIR%\" >nul
    echo Copied msbuild_errors.log
)
if exist "%BUILD_DIR%\msbuild_detailed.log" (
    copy "%BUILD_DIR%\msbuild_detailed.log" "%TEMP_ERROR_DIR%\" >nul
    echo Copied msbuild_detailed.log
)
if exist "%BUILD_DIR%\CMakeCache.txt" (
    copy "%BUILD_DIR%\CMakeCache.txt" "%TEMP_ERROR_DIR%\" >nul
    echo Copied CMakeCache.txt
)
if exist "%BUILD_DIR%\CMakeFiles" (
    xcopy "%BUILD_DIR%\CMakeFiles" "%TEMP_ERROR_DIR%\CMakeFiles\" /s /e /y >nul
    echo Copied CMakeFiles
)

:: 创建错误说明文件
echo Creating error description file...
(
    echo Build Failed: %PROJECT_NAME%
    echo ===============================
    echo Timestamp: %date% %time%
    echo Project: %PROJECT_NAME%
    echo Configuration: %CONFIG%
    echo Platform: %PLATFORM%
    echo.
    echo Error Files:
    echo - msbuild_errors.log : Contains only error messages
    echo - msbuild_detailed.log : Contains full build log
    echo - CMakeCache.txt : CMake configuration cache
    echo - CMakeFiles/ : CMake generated files
    echo.
    echo Please check the error logs above for details.
) > "%TEMP_ERROR_DIR%\BUILD_ERROR_README.txt"

:: 清理整个构建目录
echo Cleaning build directory...
cd /d "%ROOT_DIR%"
rmdir /s /q "%BUILD_DIR%" 2>nul
mkdir "%BUILD_DIR%"

:: 将错误文件移动到output目录
if exist "%TEMP_ERROR_DIR%" (
    echo Moving error files to output directory...
    move "%TEMP_ERROR_DIR%" "%ERROR_OUTPUT_DIR%" >nul
    echo Build failed! Error information saved in: %ERROR_OUTPUT_DIR%
) else (
    echo No error files collected.
)

:: 创建最终的错误标记文件
(
    echo BUILD FAILED
    echo Project: %PROJECT_NAME%
    echo Time: %date% %time%
    echo Error details are in the log files in this directory.
) > "%ERROR_OUTPUT_DIR%\BUILD_STATUS_FAILED.txt"

echo.
echo ========================================
echo Build failed for %PROJECT_NAME%!
echo Error information saved in: %ERROR_OUTPUT_DIR%
echo ========================================
echo.

exit /b 1