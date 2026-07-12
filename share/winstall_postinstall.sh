#!/bin/bash

ICONFILE="$PREFIX/share/icons/virtualOscilloscope_32x32.png"
LINKFILE="$PREFIX/share/icons/virtualOscilloscope.png"

if ln -s "$ICONFILE" "$LINKFILE" ; then
	echo "$LINKFILE" >> "$DATALOGFOLDER/$PRJNAME"
else
	echo "WARNING! I cannot create the \"$LINKFILE\" link file"
	exit 16
fi

exit 0
