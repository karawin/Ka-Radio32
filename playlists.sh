#!/bin/sh

SRC="infos.html"
TARGET="playlists"

mkdir -p "$TARGET"
rm -f "$TARGET/*"

grep 'href="playlists\/' "$SRC" | \
sed -E 's/.*href="playlists\/([^"]*).*/\1/' | \
while read item; do
	echo "$item"
	# wget -O "$TARGET/$item" "http://karadio.karawin.fr/$item"
	wget -P "$TARGET" "http://karadio.karawin.fr/$item"
done
