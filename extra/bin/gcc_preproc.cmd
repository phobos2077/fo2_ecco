@echo off
gcc -E -x c -Werror -Wfatal-errors -o "%~nx1.tmp" "%1"