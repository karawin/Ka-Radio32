#!/bin/sh

SRC="infos.html"
TARGET="playlists"
rm -f "$TARGET/*"

grep 'href="playlists\/' "$SRC" | \
sed -E 's/.*href="playlists\/([^"]*).*/\1/' | \
while read item; do
	echo "$item"
	wget -O "$TARGET/$item" "http://karadio.karawin.fr/$item"
done
