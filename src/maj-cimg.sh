#!/bin/sh
[ -f CImg.h ] && mv CImg.h CImg.h_$(date "+%s")
wget -c https://raw.githubusercontent.com/dtschump/CImg/master/CImg.h -O - | gunzip - > CImg.h
