#!/bin/sh

# https://github.com/ndparker/rjsmin
# sudo -H pip3 install rjsmin
# python3 -m rjsmin < foo.js > foo.min.js
# same way with https://github.com/ndparker/rcssmin

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
ls -l *
for f in $(ls *); do
	g="$(echo $f | sed -E 's/\.[a-z]+$//')"
	xxd -i $f | sed 's/^\s*unsigned/const/' > ../tmp_$g
done

cd ..
rm -R $WORKDIR

exit

# Need python3. Install it with pacman -Sy python3
echo style
cp style.css style.ori
python3 ./css-html-js-minify.py style.css
gzip  style.min.css
mv style.min.css.gz style.css
xxd -i style.css > style
#sed -i 's/\[\]/\[\]/g' style
sed -i 's/unsigned/const/g' style
mv style.ori style.css

echo style1
cp style1.css style1.ori
python3 ./css-html-js-minify.py style1.css
gzip  style1.min.css
mv style1.min.css.gz style1.css
xxd -i style1.css > style1
#sed -i 's/\[\]/\[\]/g' style1
sed -i 's/unsigned/const/g' style1
mv style1.ori style1.css

echo script
cp script.js script.ori
#python3 ./css-html-js-minify.py script.js
gzip  script.js
mv script.js.gz script.js
xxd -i script.js > script
#sed -i 's/\[\]/\[\]/g' script
sed -i 's/unsigned/const/g' script
mv script.ori script.js

echo index
cp index.html index.htm
python3 ./css-html-js-minify.py index.htm
gzip index.html
mv index.html.gz index.html
xxd -i index.html > index
#sed -i 's/\[\]/\[\]/g' index
sed -i 's/unsigned/const/g' index
mv index.htm index.html

echo logo
cp logo.png logo.ori
gzip logo.png
mv logo.png.gz logo.png
xxd -i logo.png > logo
#sed -i 's/\[\]/\[\]/g' logo
sed -i 's/unsigned/const/g' logo
mv logo.ori logo.png

echo favicon
cp favicon.png favicon.ori
gzip favicon.png
mv favicon.png.gz favicon.png
xxd -i favicon.png > favicon
#sed -i 's/\[\]/\[\]/g' favicon
sed -i 's/unsigned/const/g' favicon
mv favicon.ori favicon.png
