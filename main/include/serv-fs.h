#include "esp_system.h"

//#define CACHE_FLASH __attribute__((section(".irom0.rodata")))

struct servFile
{
	const char name[32];
	const char type[16];
	uint16_t size;
	const char* content;
	struct servFile *next;
};

//ICACHE_STORE_ATTR ICACHE_RODATA_ATTR
#define ICACHE_STORE_TYPEDEF_ATTR __attribute__((aligned(4),packed))
#define ICACHE_STORE_ATTR __attribute__((aligned(4)))
#define ICACHE_RAM_ATTR __attribute__((section(".iram0.text")))

#include "../../webpage/tmp_index"
#include "../../webpage/tmp_genuine"
#include "../../webpage/tmp_style"
#include "../../webpage/tmp_style1"
#include "../../webpage/tmp_script"
#include "../../webpage/tmp_logo"
#include "../../webpage/tmp_favicon"

const struct servFile genuineFile = {
	"/genuine",
	"text/html",
	sizeof(genuine_html),
	(const char*)genuine_html,
	(struct servFile*)NULL
};
const struct servFile faviconFile = {
	"/favicon.png",
	"image/png",
	sizeof(favicon_png),
	(const char*)favicon_png,
	(struct servFile*)&genuineFile
};
const struct servFile logoFile = {
	"/logo.png",
	"image/png",
	sizeof(logo_png),
	(const char*)logo_png,
	(struct servFile*)&faviconFile
};

const struct servFile scriptFile = {
	"/script.js",
	"text/javascript",
	sizeof(script_js),
	(const char*)script_js,
	(struct servFile*)&logoFile
};

const struct servFile styleFile = {
	"/style.css",
	"text/css",
	sizeof(style_css),
	(const char*)style_css,
	(struct servFile*)&scriptFile
};

const struct servFile styleFile1 = {
	"/style1.css",
	"text/css",
	sizeof(style1_css),
	(const char*)style1_css,
	(struct servFile*)&styleFile
};
const struct servFile indexFile = {
	"/",
	"text/html",
	sizeof(index_html),
	(const char*)index_html,
	(struct servFile*)&styleFile1
};
