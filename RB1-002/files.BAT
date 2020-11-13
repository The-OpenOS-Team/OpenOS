@echo off
echo          R B 1 - 0 0 2
echo.
echo CONFIDENTIAL TO ZEROAIR INFINITY
echo IF YOU HAVE THIS AND NOT PART OF
echo ZEROAIR INFINITY THEN YOU WILL BE
echo TRACKED BY KK64.
pause
cls
echo FILE EXPLORER
cd C:\
dir /w
SET /P M=Type File or Folder then press ENTER:
IF %M%==File GOTO FILE
IF %M%==Folder GOTO FOLDER

:START
cls
echo FILE EXPLORER
dir /w
SET /P M=Type File or Folder then press ENTER:
IF %M%==File GOTO FILE
IF %M%==Folder GOTO FOLDER

:FILE
echo What file?
SET /P E=Type file then ENTER:
SET /P D=What type? (.bat, .exe, .com):
%E% %D%

:FOLDER
echo What file?
SET /P E=Type folder then ENTER:
cd %E%
GOTO START





