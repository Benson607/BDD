#!/bin/bash

if dpkg -l | grep -q "^ii  g++ "; then
	echo "check g++ install"
else
	read -p "g++ not install, do you want to install? y/n[y] " check
	check=${check:-y}

	if [[ "$check" == "y" || "$check" == "Y" ]]; then
		sudo apt-get update
		sudo apt-get install g++
	else
		echo "not allow to install g++"
	fi
fi

if dpkg -l | grep -q "^ii  g++ "; then
        g++ main.cpp -o main
	echo "compile finish"
else
	echo "g++ not install, can not build code"
fi
