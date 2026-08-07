#!/bin/bash
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
#	This is the pre-installation script. 
#	It checks for unresolved dependences. It it fails no file will be copied
#
#-------------------------------------------------------------------------------------------------------------------------------

dbgPause() {
	local -i count=0
	local -i end=$1
	while [ $count -lt $end ]
	do
		echo -ne "\r$count/$end"
		sleep 1
		count=$(($count + 1))
	done
	echo ""
	return 0
}

err=0
myPwd=${0%/*}
[ -z "$myPwd" ] && myPwd="."
cd $myPwd

pwd

echo "Checking for unresolved dependences"
echo ""

./checkFordep.sh $(cat depsListFile) || err=127

#dbgPause 5

exit $err
