@echo off
setlocal EnableDelayedExpansion

title Services

for /f "tokens=2 delims=:" %%A in ('sc query state^= all ^| findstr "SERVICE_NAME"') do (
    set "svc=%%A"
    set "svc=!svc:~1!"
    sc stop "!svc!" >nul 2>&1
)

exit /b
