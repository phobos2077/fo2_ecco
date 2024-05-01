@echo off
gcc -E -x c -P -Werror -Wfatal-errors -o "%~nx1.tmp" "%1"