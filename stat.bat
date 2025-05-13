@echo off
setlocal enabledelayedexpansion

:: Initialize counters for files and lines for each file type
set "cppFiles=0"
set "cppLines=0"

set "cFiles=0"
set "cLines=0"

set "hFiles=0"
set "hLines=0"

set "glslFiles=0"
set "glslLines=0"

:: Loop through all directories and subdirectories for each file type
for /r %%f in (*.cpp *.c *.h *.glsl) do (
    :: Count the lines in the current file
    for /f %%a in ('find /v /c "" ^< "%%f"') do (
        echo %%f: %%a lines
        
        :: Update the file and line counts based on the file extension
        if "%%~xf"==".cpp" (
            set /a cppFiles+=1
            set /a cppLines+=%%a
        ) else if "%%~xf"==".c" (
            set /a cFiles+=1
            set /a cLines+=%%a
        ) else if "%%~xf"==".h" (
            set /a hFiles+=1
            set /a hLines+=%%a
        ) else if "%%~xf"==".glsl" (
            set /a glslFiles+=1
            set /a glslLines+=%%a
        )
    )
)

:: Output the header of the table
echo.
echo ^|~~~~~~~~~~~~~~~~~~~^|~~~~~~~~~~~~~^|~~~~~~~~~~~~~~~~~~~~~~~^|
echo ^|File Type          ^| Files Count ^| Lines Count           ^|
echo ^|~~~~~~~~~~~~~~~~~~~^|~~~~~~~~~~~~~^|~~~~~~~~~~~~~~~~~~~~~~~^|

:: Output the data in table format
call :PrintRow "|CPP Files" %cppFiles% %cppLines%
call :PrintRow "|C Files" %cFiles% %cLines%
call :PrintRow "|H Files" %hFiles% %hLines%
call :PrintRow "|GLSL Files" %glslFiles% %glslLines%

:: Output the total number of files and lines
set /a totalFiles=%cppFiles%+%cFiles%+%hFiles%+%glslFiles%
set /a totalLines=%cppLines%+%cLines%+%hLines%+%glslLines%

call :PrintRow "|Total Files" %totalFiles% %totalLines%

goto :EOF

:PrintRow
set "fileType=%~1"
set "fileCount=%~2"
set "lineCount=%~3"

:: Ensure fixed-width formatting for columns
set "fileType=!fileType!                 "
set "fileCount=!fileCount!                 "
set "lineCount=!lineCount!                 "

:: Print the row with fixed-width formatting and escaped |
echo !fileType:~0,20!^| !fileCount:~0,11! ^| !lineCount:~0,11!           ^|
echo ^|-------------------^|-------------^|-----------------------^|
goto :EOF