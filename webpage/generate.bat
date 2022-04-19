@echo off
echo style
copy style.css style.ori
python ./css-html-js-minify.py style.css
bin\gzip  style.min.css 
move style.min.css.gz style.css
bin\xxd -i style.css > style
bin\sed   -i "s/unsigned/const/g" style
move /Y style.ori style.css

echo style1
copy style1.css style1.ori
python ./css-html-js-minify.py style1.css
bin\gzip  style1.min.css 
move style1.min.css.gz style1.css
bin\xxd -i style1.css > style1
bin\sed   -i "s/unsigned/const/g" style1
move /Y style1.ori style1.css

echo script
copy script.js script.ori
bin\gzip  script.js 
move script.js.gz script.js
bin\xxd -i script.js > script
bin\sed   -i "s/unsigned/const/g" script
move /Y script.ori script.js

echo index
copy index.html index.htm
python ./css-html-js-minify.py index.htm
bin\gzip index.html
move index.html.gz index.html
bin\xxd -i index.html > index
bin\sed   -i "s/unsigned/const/g" index
move /Y index.htm index.html

echo logo
copy logo.png logo.ori
bin\gzip logo.png
move logo.png.gz logo.png
bin\xxd -i logo.png > logo
bin\sed   -i "s/unsigned/const/g" logo
move /Y logo.ori logo.png

echo favicon
copy favicon.png favicon.ori
bin\gzip favicon.png
move favicon.png.gz favicon.png
bin\xxd -i favicon.png > favicon
bin\sed   -i "s/unsigned/const/g" favicon
move /Y favicon.ori favicon.png
del sed*
