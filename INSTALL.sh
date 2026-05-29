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

[ -z "$cmd" ] && cmd="install"

case "$cmd" in
	"install")
		cd src && qmake6 && make install
		cd $myPwd
		cp -v share/virtualOscilloscope_*.png    /usr/share/icons
		cp -v share/virtualOscilloscope.desktop  /usr/share/applications
	;;
	"uninstall")
	;;
	*)
		echo "ERROR! use $0 [{install|uninstall}]"
		exit 127
	;;
esac

exit 0
