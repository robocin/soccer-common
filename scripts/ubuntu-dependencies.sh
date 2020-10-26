#!/bin/bash
# Dependencies able to be installed: qt, g++, open-gl, clang.

PARAMS=()
PARAM_SIZE="${#@}"
ans=" "

if [[ "$PARAM_SIZE" > 0 ]] ; then
	echo "You are not installing:"
	for var in "$@"
	do 
		PARAMS+=("$var")
		echo "$var "
	done
	echo "Proceed with installation? [y/n]"
	read ans

	if [[ "$ans" != y ]] ; then
		if [[ "$ans" != n ]] ; then
			echo "Invalid input"
		fi
		exit
	fi
fi

echo "Starting installation..."
if [[ ! "${PARAMS[@]}" =~ "-clang-format" ]] ; then
	echo $'Installing clang-format...'
	apt-get install clang-format
	echo $'clang-format installation finished'
fi

if [[ ! "${PARAMS[@]}" =~ "-g++" ]] ; then
	echo $'Installing g++...'
	apt-get install g++
	echo $'g++ installation finished'
fi

if [[ ! "${PARAMS[@]}" =~ "-gl" ]] ; then
	echo $'Installing open-gl...'
	apt-get install freeglut3 freeglut3-dev
	echo $'open-gl installation finished'
fi

if [[ ! "${PARAMS[@]}" =~ "-qt" ]] ; then
	echo 'Installing qt..'
	apt-get install build-essential libfontconfig1 mesa-common-dev libglu1-mesa-dev -y
	wget http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
	chmod +x qt-unified-linux-x64-online.run
	./qt-unified-linux-x64-online.run
	rm qt-unified-linux-x64-online.run
	echo $'qt installation finished'
fi
echo $'\nScript finished!\nHappy coding :)'
