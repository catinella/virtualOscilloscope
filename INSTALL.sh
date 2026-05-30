#!/bin/bash
#-------------------------------------------------------------------------------------------------------------------------------
#                   __     ___      _               _     ___           _ _ _                                
#                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
#                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
#                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
#                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
#                                                                                                |_|
#
# File:   INSTALL.sh
#
# Author: Silvano Catinella <catinella@yahoo.com>
#
# Description:
#
#
#-------------------------------------------------------------------------------------------------------------------------------

cmd="$1"
cd ${0%/*}
myPwd=$PWD
PREFIX="/usr/local"
ICONSIZE="64x64"

[ -z "$cmd" ] && cmd="install"

numOfProcs=$(cat /proc/cpuinfo |grep processor |wc -l |sed 's/[ \t]//g')

case "$cmd" in
	"install")
		answ="###"
		while [ ! -d "$answ" ]
		do
			echo -n "Type the installation PREFIX folder [def. $PREFIX]: "; read answ
			[ -z "$answ" ] && answ="$PREFIX"
		done
		PREFIX="$answ"

		cd src && qmake6 && PREFIX="$PREFIX" make -j${numOfProcs} install
		cd $myPwd

		answ="###"
		while [ "$answ" != "128x128" -a "$answ" != "64x64" -a "$answ" != "32x32" ]
		do
			echo -n "Type prefered icon size [def. $ICONSIZE]: "; read answ
			[ -z "$answ" ] && answ="$ICONSIZE"
		done
		cp -v share/virtualOscilloscope_*.png                         $PREFIX/share/icons
		cp -v share/virtualOscilloscope.desktop                       $PREFIX/share/applications
		ln -s $PREFIX/share/icons/virtualOscilloscope_${ICONSIZE}.png $PREFIX/share/icons/virtualOscilloscope.png

		# Configuration data updating...
		echo "PREFIX=\"$PREFIX\"" > INSTALL.conf
	;;
	"uninstall")
		# Last configuration loading...
		[ -e INSTALL.conf ] && source INSTALL.conf

		cd src && qmake6 && PREFIX="$PREFIX" make uninstall
		cd $myPwd
		rm -fv $PREFIX/share/icons/virtualOscilloscope*.png    
		rm -fv $PREFIX/share/applications/virtualOscilloscope.desktop  
	;;
	*)
		echo "ERROR! use $0 [{install|uninstall}]"
		exit 127
	;;
esac

exit 0
