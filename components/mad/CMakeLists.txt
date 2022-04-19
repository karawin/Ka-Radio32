idf_component_register(SRCS 
							"align.c"
							"bit.c"
							"decoder.c"
							"fixed.c"
							"frame.c"
							"huffman.c"
							"layer12.c"
							"layer3.c"
							"stream.c"
							"synth_stereo.c"
							"timer.c"
							"version.c"
                    INCLUDE_DIRS "."
					
					)
component_compile_options(-Wno-error=unused-label -Wno-error=return-type -Wno-error=missing-braces 
-Wno-error=pointer-sign -Wno-error=parentheses -Wno-error=maybe-uninitialized )