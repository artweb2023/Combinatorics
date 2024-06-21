@echo off

REM Путь к вашей программе передается через 1-й аргумент командной строки
SET MyProgram="%~1"

if %MyProgram%=="" (
    echo Please specify path to program
    exit /B 1
)

REM Некорректое количеством аргументов
echo Testing with invalid arguments count
%MyProgram% >nul && goto err
echo Test 1 passed

REM Проверка если файлы пустые
echo empty file
%MyProgram% empty1.txt empty2.txt>nul && goto err
echo Test 2 passed

REM Проверка результата
echo Testing result
%MyProgram% matrix10x10.txt > "%TEMP%\output.txt" || goto err
fc result.txt "%TEMP%\output.txt">nul|| goto err
echo Test 3 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Сюда попадаем в случае ошибки
:err
echo Test failed
exit /B 1
