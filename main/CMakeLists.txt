set(COMPONENT_SRCS 		
	"addon.c"
	"addoncommon.c"
	"addonu8g2.c"
	"addonucg.c"
	"app_main.c"
	"cencode.c"
	"ClickButtons.c"
	"ClickEncoder.c"
	"ClickJoystick.c"
	"custom.c"
	"eeprom.c"
	"gpio.c"
	"interface.c"
	"irnec.c"
	"libsha1.c"
	"ntp.c"
	"ota.c"
	"servers.c"
	"telnet.c"
	"timezone.c"
	"vs1053.c"
	"vs1053b-patches.c"
	"webclient.c"
	"webserver.c"
	"websocket.c"
)

set(COMPONENT_ADD_INCLUDEDIRS 
	"./include/"
	"../webpage/"
	
	PRIV_REQUIRES wolfssl 
)

register_component()
component_compile_options(-Wno-error=unused-label -Wno-error=return-type -Wno-error=missing-braces 
-Wno-error=pointer-sign -Wno-error=parentheses -Wno-error=maybe-uninitialized -DWOLFSSL_USER_SETTINGS -DWOLFSSL_STATIC_RSA )

