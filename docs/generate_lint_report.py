##
## EPITECH PROJECT, 2023
## RTypeRenderEngine
## File description:
## generate_report
##

if __name__ != '__main__':
    print('This script is not meant to be imported')
    exit(0)

import re
import sys
import subprocess

shouldFail = '--fail-on-exit' in sys.argv

result = subprocess.run(['cpplint --filter=-legal,-build/header_guard --output=emacs --exclude="gameExample" --exclude="tests/*" --exclude=build/_deps --exclude=include/RTypeEngine/Graphics/stb_image.h --exclude=build/CMakeFiles --recursive .'], shell=True, capture_output=True, text=True)
errors = {}

readme_file = open('docs/LINT_REPORT.md', 'w')
readme_file.write('# Lint report\n\n')

lint_line_reg = r'([^:]*):(\d+):\s+(.*)\[(.*)\]\s\[(.*)\]'

lines = result.stderr
lines = lines.split('\n')
lines = [line for line in lines if line != '']

matches = 0

for line in lines:
    match = re.match(lint_line_reg, line)
    if not match:
        continue
    matches += 1
    filepath, line_number, message, error_type, error_level = match.groups()

    categories = error_type.split('/')
    tmpDict = errors
    for category in categories:
        if category not in tmpDict:
            tmpDict[category] = {}
        tmpDict = tmpDict[category]

    tmpDict[filepath] = {
        'line_number': line_number,
        'message': message,
        'error_level': error_level
    }

category_emojis = {
    'build': '🛠️',
    'runtime': '🏃',
    'whitespace': '🌌',
    'readability': '📕'
}

error_levels = {
    '1': '🟢',
    '2': '🟡',
    '3': '🟠',
    '4': '🔴',
    '5': '☢️'
}

def print_final(files):
    for file in files:
        line_number, message, error_level = files[file].values()
        readme_file.write(f'  * [{error_levels[error_level]} In {file} at line {line_number}]({file})\n')
        readme_file.write(f'    * {message}\n')

def treat_category(dict, key):
    for sub in dict[key]:
        subcat = f'* {sub.replace("_", " ").capitalize()}\n'
        readme_file.write(subcat)
        if type(sub) != str:
            treat_category(dict[key], sub)
        else:
            print_final(dict[key][sub])

for key in errors.keys():
    category_hey = f'## {category_emojis.get(key, "!")} {key.capitalize()}\n'
    readme_file.write(category_hey)

    treat_category(errors, key)
readme_file.close()

if shouldFail:
    sys.exit(1 if matches > 0 else 0)
else:
    sys.exit(0)
