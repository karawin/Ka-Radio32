#!/bin/sh

IP="$(grep 'IP_ADDR\s*=' index.php | sed -E 's/^.*IP_ADDR\s*=.*\b([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*/\1/')"

echo "IP ADDR : $IP"

CURL="$(command -v curl)"

echo "$1"
# exit

# Play station #3
# ${CURL} -v -d 'id=3' -d '' http://${IP}/play

# instant play: http://stric6.streamakaci.com:80/crock.mp3
# curl -v -d 'url=stric6.streamakaci.com' -d 'port=80' -d 'path=/crock.mp3' -d '' http://192.168.58.77/instant_play

SPLIT_URL="$(echo $1 | sed -E 's!^(https?://)?([^/:]+)(:([0-9]+))?(/.*).*?!\2|\4|\5!')"
URL="$(echo $SPLIT_URL | cut -d '|' -f 1)"
PPORT="$(echo $SPLIT_URL | cut -d '|' -f 2)"
PORT="${PPORT:-80}"
PATH="$(echo $SPLIT_URL | cut -d '|' -f 3)"

# echo "URL : ${URL}"
# echo "PORT: ${PORT}"
# echo "PATH: ${PATH}"

${CURL} -d "url=${URL}" -d "port=${PORT}" -d "path=${PATH}" -d '' http://${IP}/instant_play
