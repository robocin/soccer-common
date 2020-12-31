#!/bin/bash

PARAMS=()
SCRIPTS=()
CHOSEN=""
PARAM_SIZE="${#@}"
folder="./ubuntu"
declare -A SCR
i=0
MODE=""

cd $folder	# goes to the desired folder

for file in ./*.sh; do 	# loop through every file in the folder
	SCR+=(["$i"]="$(basename "$file")")
	i=$((i+1))
done

echo "There are $i scripts in $folder:"
for key in ${!SCR[@]}; do
	echo "[${key}] - ${SCR[${key}]}"
done
echo " "
echo "[a] - Install all | [o] - Install only | [u] - Not install only | [q] - Quit"

read MODE

if [[ "$MODE" == "a" ]] ; then
	clear
	echo "[INSTALLING ALL SCRIPTS]"
	for key in ${!SCR[@]}; do
		bash ${SCR[${key}]}
	done
elif [[ "$MODE" == "o" ]] ; then
	clear
	echo "[INSTALL ONLY MODE]"
	echo " "
	echo "$i scripts found:"
	for key in ${!SCR[@]}; do
		echo "[${key}] - ${SCR[${key}]}"
	done
	echo " "
	echo "Choose the [index] of the script to install:"
	read CHOSEN
	for (( j=0; j<${#CHOSEN}; j++ )); do
  		if [[ "${CHOSEN:$j:1}" != " " ]]; then
  			bash ${SCR[${CHOSEN:$j:1}]}
  		fi
	done
elif [[ "$MODE" == "u" ]] ; then
clear
	echo "[NOT INSTALL ONLY MODE]"
	echo " "
	echo "$i scripts found:"
	for key in ${!SCR[@]}; do
		echo "[${key}] - ${SCR[${key}]}"
	done
	echo " "
	echo "Choose the [index] of the script to avoid it's installation:"
	read CHOSEN

	for key in ${!SCR[@]}; do
		if [[ ! "${CHOSEN[@]}" =~ "$key" ]]; then
			bash ${SCR[${key}]}
		fi
	done

elif [[ "$MODE" == "q" ]] ; then
	echo "Script finished."
else
	echo "Wrong input"
fi

echo "Happy coding!"
