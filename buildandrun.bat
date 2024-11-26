@echo off
echo Building...
call build.bat
if %ERRORLEVEL% neq 0 (
    echo Build failed.
    pause
    exit /b %ERRORLEVEL%
)
cd build
if exist game.exe (
    game.exe
) else (
    echo game.exe not found in build directory.
    pause
)