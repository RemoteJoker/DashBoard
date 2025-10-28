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

:: 完全清理构建目录
if exist "%BUILD_DIR%" (
    echo Performing deep clean of build directory...
    cd /d "%BUILD_DIR%"
    
    :: 保留output目录和python.out日志
    if exist "output" (
        echo Preserving existing output directory...
    )
    if exist "python.out" (
        echo Preserving python.out log...
    )
    
    :: 删除所有已知的中间目录
    echo Removing intermediate directories...
    for /d %%D in (*) do (
        if /i not "%%~nxD"=="output" (
            echo Removing directory: %%D
            rmdir /s /q "%%D" 2>nul
        )
    )
    
    :: 删除所有已知的中间文件
    echo Removing intermediate files...
    for %%F in (*) do (
        if /i not "%%~nxF"=="python.out" (
            if /i not "%%~nxF"=="error.txt" (
                del "%%F" 2>nul
            )
        )
    )
) else (
    mkdir "%BUILD_DIR%" > nul 2>&1
)

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

if not errorlevel 0 (
    echo Error: CMake generation failed for %PROJECT_NAME%
    goto :BuildFailed
)

echo Building %PROJECT_NAME% with MSBuild...
msbuild "%PROJECT_NAME%.sln" ^
    /p:Configuration=%CONFIG% ^
    /p:Platform=%PLATFORM% ^
    /m ^
    /verbosity:minimal

if not errorlevel 0 (
    echo Build failed for %PROJECT_NAME%! Check above errors.
    goto :BuildFailed
)

echo Build successful! Output in: %BUILD_DIR%\%CONFIG%

:: 编译成功时的处理
echo Performing post-build operations...

set "RELEASE_DIR=%BUILD_DIR%\Release"
set "OUTPUT_DIR=%BUILD_DIR%\output"

:: 如果output目录已存在，先删除它
if exist "%OUTPUT_DIR%" (
    echo Removing existing output directory...
    rmdir /s /q "%OUTPUT_DIR%" 2>nul
)

:: 重命名Release目录为output
if exist "%RELEASE_DIR%" (
    echo Moving build output to output directory...
    ren "%RELEASE_DIR%" "output" >nul
    echo Build successful! Clean output in: %OUTPUT_DIR%
    
    :: 彻底清理所有中间文件和目录
    echo Performing comprehensive cleanup of intermediate files...
    cd /d "%BUILD_DIR%"
    
    :: 删除所有CMake相关文件和目录
    echo Removing CMake files...
    if exist "CMakeCache.txt" del "CMakeCache.txt" 2>nul && echo Deleted: CMakeCache.txt
    if exist "CMakeFiles" rmdir /s /q "CMakeFiles" 2>nul && echo Deleted: CMakeFiles
    if exist "*.cmake" del "*.cmake" 2>nul && echo Deleted: *.cmake
    if exist "cmake_install.cmake" del "cmake_install.cmake" 2>nul && echo Deleted: cmake_install.cmake
    
    :: 删除所有Visual Studio项目文件
    echo Removing Visual Studio files...
    if exist "*.vcxproj*" del "*.vcxproj*" 2>nul && echo Deleted: *.vcxproj*
    if exist "*.filters" del "*.filters" 2>nul && echo Deleted: *.filters
    if exist "*.user" del "*.user" 2>nul && echo Deleted: *.user
    if exist "*.sln" del "*.sln" 2>nul && echo Deleted: *.sln
    
    :: 删除所有可能的中间目录
    echo Removing all intermediate directories...
    for /d %%D in (*) do (
        if /i not "%%~nxD"=="output" (
            echo Removing directory: %%D
            rmdir /s /q "%%D" 2>nul
        )
    )
    
    :: 删除所有可能的中间文件
    echo Removing all intermediate files...
    for %%F in (*.idb) do del "%%F" 2>nul && echo Deleted: %%F
    for %%F in (*.pdb) do del "%%F" 2>nul && echo Deleted: %%F
    for %%F in (*.ilk) do del "%%F" 2>nul && echo Deleted: %%F
    for %%F in (*.obj) do del "%%F" 2>nul && echo Deleted: %%F
    for %%F in (*.tlog) do del "%%F" 2>nul && echo Deleted: %%F
    for %%F in (*.log) do (
        if /i not "%%~nxF"=="python.out" (
            del "%%F" 2>nul && echo Deleted: %%F
        )
    )
    for %%F in (*.bat) do del "%%F" 2>nul && echo Deleted: %%F
    for %%F in (*.txt) do (
        if /i not "%%~nxF"=="python.out" (
            if /i not "%%~nxF"=="error.txt" (
                del "%%F" 2>nul && echo Deleted: %%F
            )
        )
    )
    
    :: 显示清理后的目录状态
    echo.
    echo Directory status after cleanup:
    dir /b
) else (
    echo Error: No Release directory found after build.
    echo Current directory contents:
    dir
    exit /b 1
)

:: ============================================
:: Python 脚本执行部分 - 修复版本
:: ============================================
echo.
echo ========================================
echo Python Script Execution
echo ========================================

:: 返回根目录并执行Python脚本
cd /d "%ROOT_DIR%"
set "SCRIPT_DIR=%ROOT_DIR%\Script\Build"
set "PYTHON_SCRIPT=%SCRIPT_DIR%\%PROJECT_NAME%.py"

echo Script directory: %SCRIPT_DIR%
echo Python script: %PYTHON_SCRIPT%
echo.

:: 详细检查脚本目录内容
echo Checking Script\Build directory contents:
dir "%SCRIPT_DIR%\*.py" /b
echo.

if exist "%PYTHON_SCRIPT%" (
    echo [SUCCESS] Python script found: %PROJECT_NAME%.py
    echo File details:
    dir "%PYTHON_SCRIPT%"
    echo.
    
    :: 检查Python环境
    echo Checking Python environment...
    python --version
    call :CheckPythonError
    echo.
    
    echo [INFO] Executing Python script...
    echo Command: python "%PYTHON_SCRIPT%"
    echo.
    
    :: 执行Python脚本
    python "%PYTHON_SCRIPT%"
    call :CheckPythonScriptError
    
    echo.
    echo [SUCCESS] Python packaging completed successfully!
) else (
    echo [ERROR] Python script not found: %PROJECT_NAME%.py
    echo.
    echo Expected path: %PYTHON_SCRIPT%
    echo.
    echo Available Python scripts in %SCRIPT_DIR%:
    dir "%SCRIPT_DIR%\*.py" /b
    echo.
    echo Current working directory: %CD%
    goto :BuildFailed
)

:: ============================================
:: 最终清理和完成
:: ============================================
echo.
echo Performing final verification cleanup...
cd /d "%BUILD_DIR%"

echo Current directory contents before final cleanup:
dir /b

:: 删除除了output和python.out之外的所有文件
for %%F in (*) do (
    if /i not "%%~nxF"=="python.out" (
        if /i not "%%~nxF"=="error.txt" (
            del "%%F" 2>nul
        )
    )
)

:: 删除除了output之外的所有目录
for /d %%D in (*) do (
    if /i not "%%~nxD"=="output" (
        rmdir /s /q "%%D" 2>nul
    )
)

echo.
echo Final directory contents:
dir /b

echo.
echo ========================================
echo BUILD SUCCESSFUL!
echo ========================================
echo Project: %PROJECT_NAME%
echo Output: %OUTPUT_DIR%
echo Log: %BUILD_DIR%\python.out
echo.
echo Clean build directory with only output folder remaining.
echo ========================================
echo.

exit /b 0

:CheckPythonError
if not errorlevel 0 (
    echo [ERROR] Python is not available in PATH
    goto :BuildFailed
)
exit /b 0

:CheckPythonScriptError
if not errorlevel 0 (
    echo [ERROR] Python script failed with exit code: %errorlevel%
    echo Please check the log file: %BUILD_DIR%\python.out
    echo.
    echo Last few lines of python.out:
    if exist "%BUILD_DIR%\python.out" (
        for /f "skip=%lines% tokens=*" %%i in ('type "%BUILD_DIR%\python.out" ^| find /c /v ""') do set /a lines=%%i-5
        more +%lines% "%BUILD_DIR%\python.out" 2>nul || type "%BUILD_DIR%\python.out"
    ) else (
        echo python.out file not found!
    )
    goto :BuildFailed
)
exit /b 0

:BuildFailed
echo.
echo ========================================
echo BUILD FAILED: %PROJECT_NAME%
echo ========================================
echo.
exit /b 1