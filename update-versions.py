#!/usr/bin/python3
import sys, re, time

def progress_bar(toolbar_width: int):
  sleep_time = 1 / toolbar_width

  sys.stdout.write('[%s]' % (' ' * toolbar_width))
  sys.stdout.flush()
  sys.stdout.write('\b' * (toolbar_width+1))

  for i in range(toolbar_width):
    time.sleep(sleep_time)
    sys.stdout.write('-')
    sys.stdout.flush()

  sys.stdout.write(']\n')

filename = 'version.pri'

project_name = 'project-name'
ver_major    =    'ver-major'
ver_minor    =    'ver-minor'
ver_patch    =    'ver-patch'

key_regex = {(project_name, '(\A''PROJECT_NAME\s*=\s*)(.+)'), \
             (   ver_major, '(\A'   'VER_MAJOR\s*=\s*)(.+)'), \
             (   ver_minor, '(\A'   'VER_MINOR\s*=\s*)(.+)'), \
             (   ver_patch, '(\A'   'VER_PATCH\s*=\s*)(.+)')}

value = dict()

with open(filename, 'r+') as file:
  for line in file:
    for (key, regex) in key_regex:
      r = re.compile(regex)
      if (r.match(line)):
        value[key] = r.match(line).group(2)

assert(len(value) == 4)

original_message = 'RoboCIn\'s ' + value[project_name] + ' v' + value[ver_major] + \
                                                          '.' + value[ver_minor] + \
                                                          '.' + value[ver_patch]
                                                          
colored_message  = '\033[32m' + 'RoboCIn\'s ' + '\033[39m' + '\033[1m' + \
                                value[project_name] + '\033[0m' + ' v' + \
                        '\033[1m' + value[ver_major] + '\033[0m' + '.' + \
                        '\033[1m' + value[ver_minor] + '\033[0m' + '.' + \
                        '\033[1m' + value[ver_patch] + '\033[0m'

print(colored_message)

progress_bar(len(original_message) - 2)

version = None

if (len(sys.argv) >= 2):
  version = sys.argv[1].lower()
  if (version not in ['major', 'minor', 'patch']):
    print('Leaving without changes.')
    exit(0)
else:
  try:
    version = input('Which version do you want to update [major/minor/patch]?\n').lower()
  except (EOFError, KeyboardInterrupt) as exception:
    print('Leaving without changes.')
    exit(0)
while (version not in ['major', 'minor', 'patch']):
  try:
    version = input('Sorry, try again.\n').lower()
  except (EOFError, KeyboardInterrupt) as exception:
    print('Leaving without changes.')
    exit(0)

print('The project version ' + '\033[1m' + version + '\033[0m' + ' will be updated:')

new_major = value[ver_major]
new_minor = value[ver_minor]
new_patch = value[ver_patch]

print('\033[1m' + 'v' + value[ver_major] + '.' + value[ver_minor] + '.' + value[ver_patch] + '\033[0m', end = ' -> ')

if (version == "major"):
  new_major = str(int(value[ver_major]) + 1)
  new_minor = '0'
  new_patch = '0'
elif (version == "minor"):
  new_minor = str(int(value[ver_minor]) + 1)
  new_patch = '0'
elif (version == "patch"):
  new_patch = str(int(value[ver_patch]) + 1)

print('\033[1m' + 'v' + new_major + '.' + new_minor + '.' + new_patch + '\033[0m')

option = None

try:
  option = input('Do you want to continue [Y/n]?\n').lower()
except (EOFError, KeyboardInterrupt) as exception:
  print('Leaving without changes.')
  exit(0)

while (option not in ['y', 'n']):
  try:
    option = input('Sorry, try again.\n').lower()
  except (EOFError, KeyboardInterrupt) as exception:
    print('Leaving without changes.')
    exit(0)

if (option == 'n'):
  print('Leaving without changes.')
  exit(0)

with open(filename, 'r+') as file:
  lines = file.read().splitlines()
  for (index, line) in enumerate(lines):
    for (key, regex) in key_regex:
      r = re.compile(regex)
      if (r.match(line)):
        new_value = None
        if (key == ver_major):
          new_value = new_major
        elif (key == ver_minor):
          new_value = new_minor
        elif (key == ver_patch):
          new_value = new_patch
        else:
          continue
        lines[index] = r.match(line).group(1) + new_value
  file.seek(0)
  file.write('\n'.join(lines))
  file.truncate()

progress_bar(len(original_message) - 2)

print('The project version has been updated successfully.')
