
AM_LDFLAGS=
AM_CFLAGS=

DEFS+= \
    -Icsrc -Icppsrc -Idogmsrc -Inonarduino \
    `getconf LFS_CFLAGS` \
    `getconf LFS64_CFLAGS` \
    -D_GNU_SOURCE \
    -D_FILE_OFFSET_BITS=64 \
    $(NULL)

AM_CFLAGS+= \
    -I$(top_builddir)/include/ \
    $(NULL)

AM_LDFLAGS += \
    -L$(top_builddir)/ \
    `getconf LFS_LDFLAGS` \
    `getconf LFS64_LDFLAGS` \
    $(NULL)

if DEBUG
# use "valgrind --tool=memcheck --leak-check=yes" to check memory leak, MemWatch will drag the program.
#DEFS+=-DMEMWATCH
DEFS+= -DDEBUG=1
AM_CFLAGS+=-g -Wall

else
AM_CFLAGS+=-O3 -Wall
endif

EXT_FLAGS=
@MK@GITNUMTMP=$(shell cd "$(top_srcdir)"; A=$$(git show | head -n 1 | awk '{print $$2}'); echo $${A:0:7}; cd - > /dev/null )
#@MK@SVNNUMTMP=$(shell cd "$(top_srcdir)"; LC_ALL=C svn info | grep -i Revision | awk '{print $$2}'; cd - > /dev/null )
#@MK@ifeq ($(SVNNUMTMP),)
#EXT_FLAGS+= -DSVN_VERSION='"${GITNUMTMP}"'
#@MK@else
#EXT_FLAGS+= -DSVN_VERSION='"${SVNNUMTMP}"'
#@MK@endif
@MK@ifeq ($(GITNUMTMP),)
@MK@else
EXT_FLAGS+= -DSVN_VERSION='"${GITNUMTMP}"'
@MK@endif
DEFS+=$(EXT_FLAGS)

SRC_BASE= \
    csrc/ucg_line.c \
    csrc/ucg_dev_default_cb.c \
    csrc/ucg_dev_ic_ili9163.c \
    csrc/ucg_bitmap.c \
    csrc/ucg_circle.c \
    csrc/ucg_dev_tft_240x320_ili9341.c \
    csrc/ucg_dev_ic_ili9341.c \
    csrc/ucg_scale.c \
    csrc/ucg_dev_tft_128x160_st7735.c \
    csrc/ucg_clip.c \
    csrc/ucg_dev_msg_api.c \
    csrc/ucg_init.c \
    csrc/ucg_font.c \
    csrc/ucg_polygon.c \
    csrc/ucg_dev_oled_128x128_ilsoft.c \
    csrc/ucg_ccs.c \
    csrc/ucg_rotate.c \
    csrc/ucg_dev_oled_160x128_samsung.c \
    csrc/ucg_vector_font_data.c \
    csrc/ucg_dev_tft_240x320_ssd1289.c \
    csrc/ucg_dev_ic_pcf8833.c \
    csrc/ucg_dev_oled_128x128_ft.c \
    csrc/ucg_dev_tft_240x320_ili9325_spi.c \
    csrc/ucg_box.c \
    csrc/ucg_dev_ic_ld50t6160.c \
    csrc/ucg_pixel.c \
    csrc/ucg_dev_ic_ssd1351.c \
    csrc/ucg_dev_tft_240x320_itdb02.c \
    csrc/ucg_dev_ic_ssd1289.c \
    csrc/ucg_dev_ic_st7735.c \
    csrc/ucg_dev_tft_132x132_pcf8833.c \
    csrc/ucg_com_msg_api.c \
    csrc/ucg_dev_ic_ili9325_spi.c \
    csrc/ucg.h \
    csrc/ucg_dev_tft_128x128_ili9163.c \
    csrc/ucg_pixel_font_data.c \
    csrc/ucg_dev_ic_ili9325.c \
    $(NULL)

SRC_COMMON= \
    $(NULL)

SRC_WPI= \
    $(SRC_COMMON) \
    cppsrc/Ucglib.cpp \
    $(NULL)

SRC_SDL= \
    $(SRC_COMMON) \
    sys/sdl/dev/ucg_dev_sdl.c \
    $(NULL)

#include_HEADERS = \
    $(top_srcdir)/csrc/ucg.h \
    $(top_srcdir)/cppsrc/Ucglib.h \
    $(top_srcdir)/nonarduino/Printable.h \
    $(top_srcdir)/nonarduino/Print.h \
    $(top_srcdir)/nonarduino/WString.h \
    $(NULL)

noinst_HEADERS=

lib_LTLIBRARIES=libucgbase.la libucgsdl.la #libucgwpi.la

libucgbase_la_SOURCES=$(SRC_BASE)

libucgsdl_la_SOURCES=$(SRC_SDL)

libucgwpi_la_SOURCES=$(SRC_WPI)

libucgbase_la_CFLAGS=-Icsrc -Icppsrc -Inonarduino -DUCG_16BIT `sdl-config --cflags`
libucgbase_la_CPPFLAGS=$(libucgbase_la_CFLAGS)
libucgbase_la_LDFLAGS=

libucgsdl_la_CFLAGS=-Icsrc -Icppsrc -Inonarduino -DUCG_16BIT `sdl-config --cflags`
libucgsdl_la_CPPFLAGS=$(libucgsdl_la_CFLAGS)
libucgsdl_la_LDFLAGS=`sdl-config --libs`
libucgsdl_la_LIBADD=$(top_builddir)/libucgbase.la

libucgwpi_la_CFLAGS=-Icsrc -Icppsrc -Inonarduino -DUCG_16BIT -DUCG_WITH_PINLIST -DUCG_RASPBERRY_PI
libucgwpi_la_CPPFLAGS=$(libucgwpi_la_CFLAGS)
libucgwpi_la_LDFLAGS=-lwiringPi
libucgwpi_la_LIBADD=$(top_builddir)/libucgbase.la


BIN_SDL=ucgsdl_showtga ucgsdl_testdisk ucgsdl_testfont ucgsdl_testfontr ucgsdl_testrotate ucgsdl_testscale ucgsdl_logo

BIN_WPI=ucgwpi_testfont ucgwpi_gtest ucgwpi_logo

BIN_TOOLS=bdf2ucg
bdf2ucg_SOURCES= \
    tools/font/bdf2ucg/bdf2ucg.c \
    $(NULL)
test:
	./bdf2ucg -f 2 tools/font/bdf/9x18.bdf ucg_aafont_9x18 test_ucg_aafont_9x18.c

bin_PROGRAMS=$(BIN_TOOLS) $(BIN_SDL)
#noinst_PROGRAMS=$(BIN_WPI)

ucgsdl_showtga_SOURCES=sys/sdl/show_tga/main.c
ucgsdl_showtga_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_showtga_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

ucgsdl_testdisk_SOURCES=sys/sdl/test_disk/main.c
ucgsdl_testdisk_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_testdisk_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

ucgsdl_testfont_SOURCES=sys/sdl/test_font/main.c
ucgsdl_testfont_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_testfont_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

ucgsdl_testfontr_SOURCES=sys/sdl/test_font_rotate/main.c
ucgsdl_testfontr_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_testfontr_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

ucgsdl_testrotate_SOURCES=sys/sdl/test_rotate/main.c
ucgsdl_testrotate_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_testrotate_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

ucgsdl_testscale_SOURCES=sys/sdl/test_scale/main.c
ucgsdl_testscale_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_testscale_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

#ucgsdl_logo_SOURCES=sys/sdl/cpp_logo/main.cpp
#ucgsdl_logo_CPPFLAGS=$(libucgsdl_la_CFLAGS)
#ucgsdl_logo_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

ucgsdl_logo_SOURCES=sys/sdl/ucglib_logo/main.c
ucgsdl_logo_CPPFLAGS=$(libucgsdl_la_CFLAGS)
ucgsdl_logo_LDFLAGS=-lucgbase -lucgsdl $(libucgsdl_la_LDFLAGS)

.pde.cpp:
	cp $< $@
.ino.o:
	cp $< $@

#ucgwpi_logo_SOURCES=sys/arm/examples/u8g_logo/u8g_logo.c
#ucgwpi_logo_SOURCES=sys/atmega/u8g_logo/u8g_logo.c
ucgwpi_logo_SOURCES=nonarduino/wpimain.cpp sys/arduino/UcgLogo/UcgLogo.ino
ucgwpi_logo_CFLAGS=$(libucgwpi_la_CFLAGS)
ucgwpi_logo_CPPFLAGS=$(libucgwpi_la_CFLAGS)
ucgwpi_logo_LDFLAGS=-lucgbase -lucgwpi $(libucgwpi_la_LDFLAGS)

ucgwpi_gtest_SOURCES=nonarduino/wpimain.cpp sys/arduino/GraphicsTest/GraphicsTest.ino
ucgwpi_gtest_CPPFLAGS=$(libucgwpi_la_CFLAGS)
ucgwpi_gtest_LDFLAGS=-lucgbase -lucgwpi $(libucgwpi_la_LDFLAGS)

ucgwpi_testfont_SOURCES=nonarduino/wpimain.cpp sys/arduino/HowToUseFonts/HowToUseFonts.ino
ucgwpi_testfont_CPPFLAGS=$(libucgwpi_la_CFLAGS)
ucgwpi_testfont_LDFLAGS=-lucgbase -lucgwpi $(libucgwpi_la_LDFLAGS)
