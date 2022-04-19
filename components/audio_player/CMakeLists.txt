idf_component_register(SRCS "audio_player.c"
                    INCLUDE_DIRS "include"
					PRIV_REQUIRES u8g2 ucglib common fifo mp3_decoder fdk-aac_decoder audio_renderer main
					)
