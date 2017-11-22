mkdir ../../../../Ucglib_Arduino/examples/HelloWorld
mkdir ../../../../Ucglib_Arduino/examples/FPS
mkdir ../../../../Ucglib_Arduino/examples/Box3D
mkdir ../../../../Ucglib_Arduino/examples/UcgLogo
mkdir ../../../../Ucglib_Arduino/examples/Scale
mkdir ../../../../Ucglib_Arduino/examples/GraphicsTest
mkdir ../../../../Ucglib_Arduino/examples/HowToUseFonts
mkdir ../../../../Ucglib_Arduino/extras
mkdir ../../../../Ucglib_Arduino/src
mkdir ../../../../Ucglib_Arduino/src/clib
cp ../../../ChangeLog ../../../../Ucglib_Arduino/extras/.
# cp ../../../license.txt ../../../../Ucglib_Arduino/extra/.
cp INSTALL.TXT ../../../../Ucglib_Arduino/extras/.
cp ../../../cppsrc/*.cpp ../../../../Ucglib_Arduino/src/.
cp ../../../cppsrc/*.h ../../../../Ucglib_Arduino/src/.
sed -i 's|ucg.h|clib/ucg.h|g' ../../../../Ucglib_Arduino/src/Ucglib.h
cp ../../../csrc/*.c ../../../../Ucglib_Arduino/src/clib/.
cp ../../../csrc/*.h ../../../../Ucglib_Arduino/src/clib/.
cp ../../../sys/arduino/HelloWorld/*.ino ../../../../Ucglib_Arduino/examples/HelloWorld/.
cp ../../../sys/arduino/FPS/*.ino ../../../../Ucglib_Arduino/examples/FPS/.
cp ../../../sys/arduino/Box3D/*.ino ../../../../Ucglib_Arduino/examples/Box3D/.
cp ../../../sys/arduino/UcgLogo/*.ino ../../../../Ucglib_Arduino/examples/UcgLogo/.
cp ../../../sys/arduino/Scale/*.ino ../../../../Ucglib_Arduino/examples/Scale/.
cp ../../../sys/arduino/GraphicsTest/*.ino ../../../../Ucglib_Arduino/examples/GraphicsTest/.
cp ../../../sys/arduino/HowToUseFonts/*.ino ../../../../Ucglib_Arduino/examples/HowToUseFonts/.

pushd ../../../../ucglib.wiki/
pandoc -f markdown_github reference.md -t latex -o ../Ucglib_Arduino/extras/reference.pdf
pandoc -f markdown_github displays.md -t latex -o ../Ucglib_Arduino/extras/displays.pdf
pandoc -f markdown_github fontsize.md -t latex -o ../Ucglib_Arduino/extras/fontsize.pdf
popd

ver=`../print_release.sh`
sed -i -e "s/version=.*/version=${ver}/" library.properties
cp library.properties ../../../../Ucglib_Arduino/.

cd ../../../../Ucglib_Arduino

git commit -a -m `../ucglib/tools/release/print_release.sh`
git push

echo now create a release in gitub for Ucglib_Arduino, tag/namex = 1.2.3
# Relases in github:
# Tag: 1.02pre3
# Release  name: 1.02pre3
