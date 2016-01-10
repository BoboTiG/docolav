#!/bin/sh
[ -f CImg.h ] && rm CImg.h
wget -c https://raw.githubusercontent.com/dtschump/CImg/master/CImg.h -O - | gunzip - > CImg.h
