#!/bin/sh

# https://github.com/ndparker/rjsmin
# sudo -H pip3 install rjsmin
# python3 -m rjsmin < foo.js > foo.min.js
# same way with https://github.com/ndparker/rcssmin

cd "$(dirname $0)"
echo "jump into $PWD directory"

WORKDIR="workdir"
mkdir -p $WORKDIR

# clean up !!!
rm -f "$WORKDIR/*"
rm -f tmp_*

for f in $(ls *.js); do
	echo $f
	cat $f | python3 -m rjsmin | gzip -c > "$WORKDIR/$f"
done

for f in $(ls *.css); do
	echo $f
	cat $f | python3 -m rcssmin | gzip -c > "$WORKDIR/$f"
done

for f in $(ls *.html *.png); do
	echo $f
	cat $f | gzip -c > "$WORKDIR/$f"
done

cd $WORKDIR
for f in $(ls *); do
	g="$(echo $f | sed -E 's/\.[a-z]+$//')"
	xxd -i $f | sed 's/^\s*unsigned/const/' > ../tmp_$g
done

cd ..
echo
ls -1sh tmp_*

rm -R $WORKDIR
