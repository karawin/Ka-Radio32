rm -rf libraries
mkdir libraries
mkdir libraries/Ucglib
mkdir libraries/Ucglib/examples
mkdir libraries/Ucglib/examples/HelloWorld
mkdir libraries/Ucglib/examples/FPS
mkdir libraries/Ucglib/examples/Box3D
mkdir libraries/Ucglib/examples/UcgLogo
mkdir libraries/Ucglib/examples/Scale
mkdir libraries/Ucglib/examples/GraphicsTest
mkdir libraries/Ucglib/examples/HowToUseFonts
mkdir libraries/Ucglib/utility
cp ../../../ChangeLog ./libraries/Ucglib/.
cp ../../../license.txt ./libraries/Ucglib/.
cp INSTALL.TXT ./libraries/Ucglib/.
cp ../../../cppsrc/*.cpp ./libraries/Ucglib/.
cp ../../../cppsrc/*.h ./libraries/Ucglib/.
sed -i 's|ucg.h|utility/ucg.h|g' ./libraries/Ucglib/Ucglib.h
cp ../../../csrc/*.c ./libraries/Ucglib/utility/.
cp ../../../csrc/*.h ./libraries/Ucglib/utility/.
cp ../../../sys/arduino/HelloWorld/*.ino ./libraries/Ucglib/examples/HelloWorld/.
cp ../../../sys/arduino/FPS/*.ino ./libraries/Ucglib/examples/FPS/.
cp ../../../sys/arduino/Box3D/*.ino ./libraries/Ucglib/examples/Box3D/.
cp ../../../sys/arduino/UcgLogo/*.ino ./libraries/Ucglib/examples/UcgLogo/.
cp ../../../sys/arduino/Scale/*.ino ./libraries/Ucglib/examples/Scale/.
cp ../../../sys/arduino/GraphicsTest/*.ino ./libraries/Ucglib/examples/GraphicsTest/.
cp ../../../sys/arduino/HowToUseFonts/*.ino ./libraries/Ucglib/examples/HowToUseFonts/.

chmod -R g=u libraries
chmod -R o+r libraries
cd libraries 
rm ../ucglib_arduino_`../../print_release.sh`.zip
zip -r ../ucglib_arduino_`../../print_release.sh`.zip *
cd ..

