@echo off

echo Formats standards
call :super_test image.png 161-174-73
call :super_test image.jpg 161-173-72
call :super_test image.bmp 161-174-73
call :super_test image.tif 161-173-72
call :super_test image.gif 159-174-70
call :super_test image.ppm 160-173-72
call :super_test image.tga 161-174-73

echo.
echo Formats exotiques
call :super_test image.ico 161-174-73
call :super_test image.xpm 160-173-72
call :super_test image.pnm 160-173-72
call :super_test image.pcx 160-173-72
call :super_test image.fit 160-160-160
call :super_test image.pbm 187-187-187
call :super_test image.pgm 163-163-163
call :super_test image.xbm 184-184-184


echo.
pause
goto :eof


:super_test
for /f "tokens=1" %%A in ('call ..\docolav.exe "%%d-%%d-%%d" %~1 2^>NUL') do set couleurs=%%A
if not "%couleurs%" == "%~2" echo "%~1 [attendu : %~2] => %couleurs% : Erreur"
if     "%couleurs%" == "%~2" echo "%~1 [attendu : %~2] => %couleurs% : Ok"
goto :eof
