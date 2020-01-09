#!/bin/sh

for item in $(grep 'href="playlists' infos.html | sed -E 's/.*href="playlists([^"]*).*/\1/'); do
	echo "$item"
	wget -O "playlists/$item" "http://karadio.karawin.fr/$item"
done
