#!/bin/bash
#-------------------------------------------------------------------------------------------------------------------------------
#                   __     ___      _               _     ___           _ _ _                                
#                   \ \   / (_)_ __| |_ _   _  __ _| |   / _ \ ___  ___(_) | | ___  ___  ___ ___  _ __   ___ 
#                    \ \ / /| | '__| __| | | |/ _` | |  | | | / __|/ __| | | |/ _ \/ __|/ __/ _ \| '_ \ / _ \
#                     \ V / | | |  | |_| |_| | (_| | |  | |_| \__ \ (__| | | | (_) \__ \ (_| (_) | |_) |  __/
#                      \_/  |_|_|   \__|\__,_|\__,_|_|   \___/|___/\___|_|_|_|\___/|___/\___\___/| .__/ \___|
#                                                                                                |_|
#
# File:   winstall_postinstall.sh
#
# Author: Silvano Catinella <catinella@yahoo.com>
#
# Description:
#	This is the post-installation script. 
#	It creates a symbolic link to the default size icon, and add the link-filename to the added files list.
#
#-------------------------------------------------------------------------------------------------------------------------------

ICONFILE="$PREFIX/share/icons/virtualOscilloscope_32x32.png"
LINKFILE="$PREFIX/share/icons/virtualOscilloscope.png"

if ln -s "$ICONFILE" "$LINKFILE" ; then
	echo "$LINKFILE" >> "$DATALOGFOLDER/$PRJNAME"
else
	echo "WARNING! I cannot create the \"$LINKFILE\" link file"
	exit 16
fi

exit 0
