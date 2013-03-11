#!/bin/sh
[ -f CImg.h ] && mv CImg.h CImg.h_$(date "+%s")
wget -c cimg.cvs.sourceforge.net/viewvc/cimg/CImg/CImg.h
