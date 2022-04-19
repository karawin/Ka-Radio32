idf_component_register(SRCS "fdk_aac_decoder.c"
                    INCLUDE_DIRS "./include"
					"../common/include"	
					"../../main/include"
					PRIV_REQUIRES  fdk-aac-oreo-m8 audio_player audio_renderer driver
					)
