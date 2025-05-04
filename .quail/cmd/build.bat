@echo off

@REM
@REM	VALIDATION FOR ARGUMENTS NEEDED!
@REM

set "project_dir=%~1"
set "vcvarsall=%~2"
set "profile=%~3"

echo %profile%

@REM
@REM Replaces '`' character with `"` character.
@REM  It's a good practise for passed strings because:
@REM  - Those strings might be passed from other shells (different quote escaping systems)
@REM  Especially when dealing with a string that contains a `quote escape`, spaces like 
@REM  the following where we have a program path and it's argument where program path can
@REM  have spaces and has to be surrounded with quotes that do not interfere with the argument.
@REM
set "vcvarsall=%vcvarsall:`="%"

@REM Calling vcvarsall.bat with architecture as argument, We're silencing it's output with '> nul'.
call %vcvarsall% > nul
call "cmake" --build "%project_dir%\build\%profile%"
@REM }

goto success

:error

echo "Wrong arguments used!"

:success
