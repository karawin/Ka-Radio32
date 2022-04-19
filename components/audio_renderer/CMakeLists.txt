idf_component_register(SRCS "audio_renderer.c"
                    INCLUDE_DIRS "include"
					"../../main/include"
					PRIV_REQUIRES driver MerusAudio  common fifo fdk-aac_decoder main 
					)
