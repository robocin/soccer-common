#!/usr/bin/python3

import os
import re
import sys
import subprocess
from typing import List


class ColorPrint:
    def __init__(self, color: str):
        self.color = color

    def __call__(self, *args, **kwargs):
        print(self.color, end='')
        print(*args, **kwargs)
        print('\033[0m', end='')


def endl():
    print('------------------------\n')


def cprint(color: str) -> ColorPrint:
    return ColorPrint(color=color)


def is_sudo():
    return os.geteuid() == 0


def run(command):
    subprocess.check_call(command, shell=True, stdout=sys.stdout, stderr=subprocess.STDOUT)


def check_is_sudo():
    cprint('\x1B[01;94m')('checking is sudo...')
    if is_sudo():
        cprint('\x1B[32m')('[OK] sudo privileges are allowed.')
    else:
        cprint('\x1B[31m')('[ERROR] this script should run with sudo privileges.')
        exit(-1)


def check_current_path():
    cprint('\x1B[01;94m')('checking current path...')
    directory_path = os.path.dirname(os.path.abspath(__file__))
    if directory_path != os.getcwd():
        cprint('\x1B[01;93m')('[WARNING] this script should run inside the folder where it exists.')
        cprint('\x1B[01;93m')('changing workdir from \'' + os.getcwd() + '\' to \'' + directory_path + '\'.')
        os.chdir(directory_path)
        cprint('\x1B[32m')('[OK] workdir has been changed.')
    else:
        cprint('\x1B[32m')('[OK] nothing to do here.')


def check_script(script: str) -> bool:
    return script in get_scripts()


def get_scripts() -> List[str]:
    return [script for script in os.listdir('ubuntu/') if re.match(r'.*\.sh', script)]


def run_multiple_scripts(scripts: List[str]):
    cprint('\x1B[01;95m')('Running apt-get update && apt-get upgrade first...'), print()

    run('apt-get update && apt-get upgrade -y'), endl()

    for script in scripts:
        cprint('\x1B[01;95m')('Running \'', script, '\'...', sep='')
        print()
        if check_script(script + '.sh'):
            run('bash ubuntu/' + script + '.sh')
        else:
            cprint('\x1B[31m')('[ERROR] Script', script, 'has ambiguous name or was not found.')
            cprint('\x1B[31m')('Please, verify the name and remove extension (if it was inserted).')
            exit(-1)
        cprint('\x1B[32m')('\n[OK] \'', script, '\' ✓', sep=''), endl()


def help_command():
    print('Usage\n')
    print('  ./setup.py [option] <script-name-0> <script-name-1> ... <script-name-N>')
    print('  ./setup.py [mode]')
    print('\nSpecify the correct mode or option and its requirements.\n')

    print('Options\n')
    print(' --help, -help, --h, -h, --H, -H     \t=\tPrint usage information and exit.')
    print(' --show, -show, --list, -list        \t=\tShow available scripts.')
    print(' --essentials, -essentials           \t=\tInstall just what is needed to run the project.')
    print(' --install, -install [<f>]           \t=\tRun the chosen scripts (without extension).')
    print()


def show_command():
    scripts = get_scripts()
    cprint('\x1B[01;95m')('There are', len(scripts), 'scripts available:')
    for script in scripts:
        cprint('\x1B[01;96m')('  ', script, sep='')


def essentials_command():
    with open('essentials.txt', 'r') as essentials_file:
        run_multiple_scripts(essentials_file.read().splitlines())


def install_command(scripts: List[str]):
    run_multiple_scripts(scripts)


def eval_args(commands: List[str]):
    allowed_commands = [('help', re.compile(r'(--?help)|(--?[h|H])'), False),
                        ('show', re.compile(r'(--?show)|(--?list)'), False),
                        ('essentials', re.compile(r'--?essentials'), False),
                        ('install', re.compile(r'--?install'), True)]

    match_performed = False

    for command, regex, has_args in allowed_commands:
        if commands and regex.match(commands[0]):
            f = globals()[command + '_command']
            if has_args:
                f(commands[1:])
            else:
                f()
            match_performed = True

    if not match_performed:
        print('Run \'./setup.py --help\' for more information.\n')


if __name__ == '__main__':
    check_is_sudo(), endl()
    check_current_path(), endl()
    eval_args(sys.argv[1:])
