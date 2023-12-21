#!/bin/sh
cpplint --filter=-legal,-build/header_guard --output=emacs --exclude="gameExample" --exclude="tests/*" --exclude=build/_deps --exclude=include/RTypeEngine/Graphics/stb_image.h --exclude=build/CMakeFiles --recursive . 2> lint_report.junit
cat lint_report.junit | python generate_lint_report.py
rm lint_report.junit
