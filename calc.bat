@echo off
color 0A
goto main

:main
echo.
echo ---------------------------
echo.
echo OpenOS Calculator 1.0
echo.
echo ---------------------------
echo.
echo /////////////////////////////////////////////
echo //Your previous Calulated number was %sum%//
echo ///////////////////////////////////////////
echo.
echo Enter the specified alphabet to continue..
echo.
echo a)Addition
echo.
echo b)Subtraction
echo.
echo c)Divison
echo.
echo d)Multipication
echo.
echo e)Square, Cube or any power.
echo.
set /p do=Value.
if %do%== a goto add
if %do%== A goto add
if %do%== b goto sub
if %do%== B goto sub
if %do%== c goto div
if %do%== C goto div
if %do%== d goto mul
if %do%== D goto mul
if %do%== e goto power1
if %do%== E goto power1
echo.
cls
echo Invalid value = %do%
echo.
pause
cls
goto main

:add
cls
echo ADDITON
echo.
set /p no1="num1. "
echo       +
set /p no2="num2. "
set /a sum=no1+no2
echo ------------
echo %sum%
echo.
pause
cls
goto menus


:sub
cls
echo SUBTACTION
echo.
set /p no1="num1. "
echo       -
set /p no2="num2. "
set /a sum=no1-no2
echo ------------
echo %sum%
echo.
pause
cls
goto menus


:div
cls
echo DIVISON
echo.
set /p no1="num1. "
echo       /
set /p no2="num2. "
set /a sum=no1/no2
echo ------------
echo %sum%
echo.
pause
cls
goto menus


:mul
cls
echo MULTIPLICATION
echo.
set /p no1="num1. "
echo       *
set /p no2="num2. "
set /a sum=no1*no2
echo ------------
echo %sum%
echo.
pause
cls
goto menus

:power1
cls
echo Square, Cube or any power (by Prof.Pickle)
echo.
echo Select the number
set /p num=
cls
echo Select the power
set /p pow=
set /a pow=%pow%+1
set ans=%num%
cls
:power2
set /a pow=%pow%-1
if %pow% LSS 1 goto next
set /a ans=%ans%*%num%
goto power2
:next
echo Your answer is %ans%
pause
goto menus

:menus
cls
echo.
echo Press 1 to exit and 2 to calculate another problem.
set /p open=
if %open%== 1 exit
if %open%== 2 goto main
goto main