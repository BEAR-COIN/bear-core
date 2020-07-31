
Debian
====================
This directory contains files used to package beard/bear-qt
for Debian-based Linux systems. If you compile beard/bear-qt yourself, there are some useful files here.

## bear: URI support ##


bear-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bear-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bearqt binary to `/usr/bin`
and the `../../share/pixmaps/bear128.png` to `/usr/share/pixmaps`

bear-qt.protocol (KDE)

