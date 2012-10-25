
docolav
=======

Tous droits (C) 2012 par BoboTiG.
 
docolav est livré avec ABSOLUMENT AUCUNE GARANTIE.
C'est une programe libre, et vous pouvez le redistribuer sous certaines
conditions. Voir la GNU General Public Licence pour plus de détails.

docolav détermine la couleur moyenne dominante d'une image. 


Dépendance
----------

ImageMagick


Installation
------------

make  
make install


Usage
-----

docolav FORMAT FICHIER

Où FORMAT est une chaîne de caractères passée à printf().  
3 arguments sont valables, dans l'ordre : R, G puis B.

Voici quelques exemples :

	docolav "R=%d G=%d B=%d" image.jpg  
	docolav "HEX(%02X,%02X,%02X)" image.jpg
