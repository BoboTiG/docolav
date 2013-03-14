#!/bin/sh

super_test() {
	echo -n "\"../docolav '%d-%d-%d' $1\" [attendu : $2] => "
	couleurs=$(../docolav '%d-%d-%d' $1)
	echo -n "$couleurs : "
	if [ "$couleurs" = "$2" ]; then
		echo "\033[32mOk\033[0m"
	else
		echo "\033[31mKo\033[0m"
	fi
}

echo "Formats standards"
super_test image.png 161-174-73
super_test image.jpg 161-173-72
super_test image.bmp 161-174-73
super_test image.tif 161-173-72
super_test image.gif 159-174-70
super_test image.ppm 160-173-72
super_test image.tga 161-174-73

echo
echo "Formats exotiques"
super_test image.ico 161-174-73
super_test image.dcm 160-173-72
super_test image.xpm 160-173-72
super_test image.pnm 160-173-72
super_test image.pcx 160-173-72
super_test image.fit 160-160-160
super_test image.pbm 187-187-187
super_test image.pgm 163-163-163
super_test image.xbm 184-184-184
