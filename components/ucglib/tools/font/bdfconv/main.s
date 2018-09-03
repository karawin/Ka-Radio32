	.file	"main.c"
	.text
Ltext0:
	.globl	_get_str_arg
	.def	_get_str_arg;	.scl	2;	.type	32;	.endef
_get_str_arg:
LFB12:
	.file 1 "main.c"
	.loc 1 11 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 12 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$45, %al
	jne	L2
	.loc 1 14 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	cmpl	12(%ebp), %eax
	jne	L2
	.loc 1 16 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	addl	$2, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L3
	.loc 1 18 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 19 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	jmp	L4
L3:
	.loc 1 23 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	leal	2(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
L4:
	.loc 1 25 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 26 0
	movl	$1, %eax
	jmp	L5
L2:
	.loc 1 29 0
	movl	$0, %eax
L5:
	.loc 1 30 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_get_num_arg
	.def	_get_num_arg;	.scl	2;	.type	32;	.endef
_get_num_arg:
LFB13:
	.loc 1 34 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 35 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$45, %al
	jne	L7
	.loc 1 37 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	cmpl	12(%ebp), %eax
	jne	L7
	.loc 1 40 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	addl	$2, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L8
	.loc 1 42 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	L10
	.loc 1 44 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 45 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	_strtoul
	movl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	jmp	L10
L8:
	.loc 1 50 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	addl	$2, %eax
	movl	$10, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	_strtoul
	movl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
L10:
	.loc 1 52 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 53 0
	movl	$1, %eax
	jmp	L11
L7:
	.loc 1 56 0
	movl	$0, %eax
L11:
	.loc 1 57 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.globl	_is_arg
	.def	_is_arg;	.scl	2;	.type	32;	.endef
_is_arg:
LFB14:
	.loc 1 60 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 61 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$45, %al
	jne	L13
	.loc 1 63 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	cmpl	12(%ebp), %eax
	jne	L13
	.loc 1 65 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 66 0
	movl	$1, %eax
	jmp	L14
L13:
	.loc 1 69 0
	movl	$0, %eax
L14:
	.loc 1 70 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.section .rdata,"dr"
LC0:
	.ascii "bdfconv [options] filename\0"
LC1:
	.ascii "-h          Display this help\0"
	.align 4
LC2:
	.ascii "-v          Print log messages\0"
	.align 4
LC3:
	.ascii "-b <n>      Font build mode, 0: proportional, 1: common height, 2: monospace, 3: multiple of 8\0"
	.align 4
LC4:
	.ascii "-f <n>      Font format, 0: ucglib font, 1: u8g2 font, 2: u8g2 uncompressed 8x8 font (enforces -b 3)\0"
	.align 4
LC5:
	.ascii "-m 'map'    Unicode ASCII mapping\0"
LC6:
	.ascii "-o <file>   C output file\0"
	.align 4
LC7:
	.ascii "-n <name>   C indentifier (font name)\0"
	.align 4
LC8:
	.ascii "-d <file>   Overview picture: Enable generation of bdf.tga and assign BDF font <file> for description\0"
	.align 4
LC9:
	.ascii "-l <margin> Overview picture: Set left margin\0"
	.align 4
LC10:
	.ascii "-a          Overview picture: Additional font information (background, orange&blue dot)\0"
	.align 4
LC11:
	.ascii "-t          Overview picture: Test string (Woven silk pyjamas exchanged for blue quartz.)\0"
LC12:
	.ascii "-r          Runtime test\0"
	.align 4
LC13:
	.ascii "map := <mapcmd> { \",\" <mapcmd> }\0"
	.align 4
LC14:
	.ascii "mapcmd := <default> | <maprange> | <exclude>\0"
LC15:
	.ascii "default := \"*\"\0"
	.align 4
LC16:
	.ascii "maprange := <range> [  \">\" <addexpr> ]        Move specified glyph <range> to target code <num>\0"
LC17:
	.ascii "exclude := \"~\" <range> \0"
	.align 4
LC18:
	.ascii "range := <addexpr> [ \"-\" <addexpr> ]          Select glyphs within specified range\0"
	.align 4
LC19:
	.ascii "addexpr := <mulexpr> [ \"+\" <mulexpr> ]\0"
	.align 4
LC20:
	.ascii "mulexpr := <num> [ \"*\" <num> ]\0"
LC21:
	.ascii "num := <hexnum> | <decnum>\0"
	.align 4
LC22:
	.ascii "hexnum := \"$\" <hexdigit> { <hexdigit> }\0"
	.align 4
LC23:
	.ascii "decnum := <decdigit> { <decdigit> }\0"
	.align 4
LC24:
	.ascii "decdigit := \"0\" | \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\"\0"
	.align 4
LC25:
	.ascii "hexdigit := \"a\" | \"b\" | \"c\" | \"d\" | \"e\" | \"f\" | \"A\" | \"B\" | \"C\" | \"D\" | \"E\" | \"F\" | <decdigit>\0"
	.align 4
LC26:
	.ascii "{ } zero, one ore more, [ ] zero or once, | alternative\0"
LC27:
	.ascii "example:\0"
	.align 4
LC28:
	.ascii "  -m '32-255'     select gylphs from encoding 32 to 255\0"
	.align 4
LC29:
	.ascii "  -m '32-255,~64' select gylphs from encoding 32 to 255, exclude '@'\0"
	.align 4
LC30:
	.ascii "  -m '32,48-57'   select space, '1', '2', ... '9'\0"
LC31:
	.ascii "build modes:\0"
	.align 4
LC32:
	.ascii " -b 0: Most compact, glyph bitmap is minimal\0"
	.align 4
LC33:
	.ascii " -b 1: Like -b 0, but glyph bitmap is extended to the height of the largest glyph within the selected glyph list.\0"
	.align 4
LC34:
	.ascii "       Also the width of the gylphs is extended to cover the delta x advance.\0"
	.align 4
LC35:
	.ascii " -b 2: Like -b 1, but glyph width is set to the width of the largest glyph within the selected gylph list.\0"
	.align 4
LC36:
	.ascii " -b 3: Like -b 2, but width and height are forced to be a multiple of 8.\0"
	.text
	.globl	_help
	.def	_help;	.scl	2;	.type	32;	.endef
_help:
LFB15:
	.loc 1 74 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 75 0
	movl	$LC0, (%esp)
	call	_puts
	.loc 1 76 0
	movl	$LC1, (%esp)
	call	_puts
	.loc 1 77 0
	movl	$LC2, (%esp)
	call	_puts
	.loc 1 78 0
	movl	$LC3, (%esp)
	call	_puts
	.loc 1 79 0
	movl	$LC4, (%esp)
	call	_puts
	.loc 1 80 0
	movl	$LC5, (%esp)
	call	_puts
	.loc 1 81 0
	movl	$LC6, (%esp)
	call	_puts
	.loc 1 82 0
	movl	$LC7, (%esp)
	call	_puts
	.loc 1 83 0
	movl	$LC8, (%esp)
	call	_puts
	.loc 1 84 0
	movl	$LC9, (%esp)
	call	_puts
	.loc 1 85 0
	movl	$LC10, (%esp)
	call	_puts
	.loc 1 86 0
	movl	$LC11, (%esp)
	call	_puts
	.loc 1 87 0
	movl	$LC12, (%esp)
	call	_puts
	.loc 1 88 0
	movl	$10, (%esp)
	call	_putchar
	.loc 1 90 0
	movl	$LC13, (%esp)
	call	_puts
	.loc 1 91 0
	movl	$LC14, (%esp)
	call	_puts
	.loc 1 92 0
	movl	$LC15, (%esp)
	call	_puts
	.loc 1 93 0
	movl	$LC16, (%esp)
	call	_puts
	.loc 1 94 0
	movl	$LC17, (%esp)
	call	_puts
	.loc 1 95 0
	movl	$LC18, (%esp)
	call	_puts
	.loc 1 96 0
	movl	$LC19, (%esp)
	call	_puts
	.loc 1 97 0
	movl	$LC20, (%esp)
	call	_puts
	.loc 1 98 0
	movl	$LC21, (%esp)
	call	_puts
	.loc 1 99 0
	movl	$LC22, (%esp)
	call	_puts
	.loc 1 100 0
	movl	$LC23, (%esp)
	call	_puts
	.loc 1 101 0
	movl	$LC24, (%esp)
	call	_puts
	.loc 1 102 0
	movl	$LC25, (%esp)
	call	_puts
	.loc 1 104 0
	movl	$LC26, (%esp)
	call	_puts
	.loc 1 106 0
	movl	$LC27, (%esp)
	call	_puts
	.loc 1 107 0
	movl	$LC28, (%esp)
	call	_puts
	.loc 1 108 0
	movl	$LC29, (%esp)
	call	_puts
	.loc 1 109 0
	movl	$LC30, (%esp)
	call	_puts
	.loc 1 110 0
	movl	$LC31, (%esp)
	call	_puts
	.loc 1 111 0
	movl	$LC32, (%esp)
	call	_puts
	.loc 1 112 0
	movl	$LC33, (%esp)
	call	_puts
	.loc 1 113 0
	movl	$LC34, (%esp)
	call	_puts
	.loc 1 114 0
	movl	$LC35, (%esp)
	call	_puts
	.loc 1 115 0
	movl	$LC36, (%esp)
	call	_puts
	.loc 1 117 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_left_margin
	.data
	.align 4
_left_margin:
	.long	1
	.globl	_build_bbx_mode
	.bss
	.align 4
_build_bbx_mode:
	.space 4
	.globl	_font_format
	.align 4
_font_format:
	.space 4
	.globl	_font_picture_extra_info
	.align 4
_font_picture_extra_info:
	.space 4
	.globl	_font_picture_test_string
	.align 4
_font_picture_test_string:
	.space 4
	.globl	_runtime_test
	.align 4
_runtime_test:
	.space 4
	.globl	_c_filename
	.align 4
_c_filename:
	.space 4
	.globl	_target_fontname
	.section .rdata,"dr"
LC37:
	.ascii "bdf_font\0"
	.data
	.align 4
_target_fontname:
	.long	LC37
	.text
	.globl	_tga_get_line_height
	.def	_tga_get_line_height;	.scl	2;	.type	32;	.endef
_tga_get_line_height:
LFB16:
	.loc 1 133 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 135 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_tga_set_font
	.loc 1 136 0
	call	_tga_get_char_height
	movl	%eax, -12(%ebp)
	.loc 1 137 0
	movl	12(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_tga_set_font
	.loc 1 138 0
	call	_tga_get_char_height
	cmpl	-12(%ebp), %eax
	jbe	L17
	.loc 1 139 0
	call	_tga_get_char_height
	jmp	L18
L17:
	.loc 1 140 0
	movl	-12(%ebp), %eax
L18:
	.loc 1 141 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.section .rdata,"dr"
LC38:
	.ascii "%3ld/0x%02lx\0"
	.text
	.globl	_tga_draw_font_line
	.def	_tga_draw_font_line;	.scl	2;	.type	32;	.endef
_tga_draw_font_line:
LFB17:
	.loc 1 144 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$80, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	.loc 1 150 0
	movl	$1, -20(%ebp)
	.loc 1 151 0
	movl	$0, -12(%ebp)
	jmp	L20
L23:
	.loc 1 153 0
	movl	-12(%ebp), %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movzbl	%al, %eax
	movl	%eax, (%esp)
	call	_tga_get_glyph_data
	testl	%eax, %eax
	je	L21
	.loc 1 154 0
	movl	$0, -20(%ebp)
L21:
	.loc 1 151 0 discriminator 2
	addl	$1, -12(%ebp)
L20:
	.loc 1 151 0 is_stmt 0 discriminator 1
	cmpl	$15, -12(%ebp)
	jg	L22
	.loc 1 151 0 discriminator 3
	cmpl	$0, -20(%ebp)
	jne	L23
L22:
	.loc 1 157 0 is_stmt 1
	cmpl	$0, -20(%ebp)
	je	L24
	.loc 1 158 0
	movl	$0, %eax
	jmp	L29
L24:
	.loc 1 160 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC38, 4(%esp)
	leal	-52(%ebp), %eax
	movl	%eax, (%esp)
	call	_sprintf
	.loc 1 162 0
	movl	_left_margin, %eax
	movl	%eax, -16(%ebp)
	.loc 1 163 0
	cmpl	$0, 16(%ebp)
	je	L26
	.loc 1 165 0
	movl	16(%ebp), %eax
	movl	1176(%eax), %eax
	testl	%eax, %eax
	je	L26
	.loc 1 167 0
	movl	16(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_tga_set_font
	.loc 1 168 0
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	leal	-52(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_draw_string
	addl	%eax, -16(%ebp)
L26:
	.loc 1 171 0
	addl	$4, -16(%ebp)
	.loc 1 173 0
	movl	20(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_tga_set_font
	.loc 1 174 0
	movl	$0, -12(%ebp)
	jmp	L27
L28:
	.loc 1 176 0 discriminator 3
	movl	_font_picture_extra_info, %esi
	movl	12(%ebp), %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	%al, %ebx
	call	_tga_get_char_width
	addl	$2, %eax
	imull	-12(%ebp), %eax
	movl	%eax, %edx
	movl	-16(%ebp), %eax
	addl	%eax, %edx
	movl	%esi, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	_tga_draw_glyph
	.loc 1 174 0 discriminator 3
	addl	$1, -12(%ebp)
L27:
	.loc 1 174 0 is_stmt 0 discriminator 1
	cmpl	$15, -12(%ebp)
	jle	L28
	.loc 1 179 0 is_stmt 1
	movl	_left_margin, %edx
	movl	-16(%ebp), %eax
	leal	(%edx,%eax), %ebx
	call	_tga_get_char_width
	addl	$2, %eax
	sall	$4, %eax
	addl	%ebx, %eax
L29:
	.loc 1 180 0 discriminator 1
	addl	$80, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.section .rdata,"dr"
LC39:
	.ascii "Max width %u, max height %u\0"
LC40:
	.ascii "'A' height %d, font size %d \0"
	.text
	.globl	_tga_draw_font_info
	.def	_tga_draw_font_info;	.scl	2;	.type	32;	.endef
_tga_draw_font_info:
LFB18:
	.loc 1 183 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	.loc 1 188 0
	movl	$0, -12(%ebp)
	.loc 1 189 0
	movl	$65, 4(%esp)
	movl	20(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_GetIndexByEncoding
	movl	%eax, -16(%ebp)
	.loc 1 190 0
	cmpl	$0, -16(%ebp)
	js	L31
	.loc 1 192 0
	movl	20(%ebp), %eax
	movl	4(%eax), %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	24(%eax), %edx
	movl	20(%ebp), %eax
	movl	4(%eax), %eax
	movl	-16(%ebp), %ecx
	sall	$2, %ecx
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	32(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
L31:
	.loc 1 195 0
	cmpl	$0, 16(%ebp)
	je	L32
	.loc 1 197 0
	movl	16(%ebp), %eax
	movl	1176(%eax), %eax
	testl	%eax, %eax
	je	L32
	.loc 1 200 0
	movl	16(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_tga_set_font
	.loc 1 202 0
	call	_tga_get_char_height
	addl	$1, %eax
	addl	%eax, 8(%ebp)
	.loc 1 203 0
	movl	_left_margin, %eax
	movl	%eax, -20(%ebp)
	.loc 1 204 0
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_draw_string
	addl	%eax, -20(%ebp)
	.loc 1 206 0
	call	_tga_get_char_height
	addl	$1, %eax
	addl	%eax, 8(%ebp)
	.loc 1 207 0
	call	_tga_get_char_height
	movl	%eax, %ebx
	call	_tga_get_char_width
	movl	%ebx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC39, 4(%esp)
	movl	$_s.3888, (%esp)
	call	_sprintf
	.loc 1 208 0
	movl	_left_margin, %eax
	movl	%eax, -20(%ebp)
	.loc 1 209 0
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$_s.3888, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_draw_string
	addl	%eax, -20(%ebp)
	.loc 1 211 0
	call	_tga_get_char_height
	addl	$1, %eax
	addl	%eax, 8(%ebp)
	.loc 1 212 0
	movl	20(%ebp), %eax
	movl	1184(%eax), %eax
	movl	%eax, 12(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC40, 4(%esp)
	movl	$_s.3888, (%esp)
	call	_sprintf
	.loc 1 213 0
	movl	_left_margin, %eax
	movl	%eax, -20(%ebp)
	.loc 1 214 0
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$_s.3888, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_draw_string
	addl	%eax, -20(%ebp)
	.loc 1 215 0
	call	_tga_get_char_height
	leal	1(%eax), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	jmp	L33
L32:
	.loc 1 218 0
	movl	$0, %eax
L33:
	.loc 1 219 0
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.section .rdata,"dr"
	.align 4
LC41:
	.ascii "Woven silk pyjamas exchanged for blue quartz.\0"
	.text
	.globl	_tga_draw_font
	.def	_tga_draw_font;	.scl	2;	.type	32;	.endef
_tga_draw_font:
LFB19:
	.loc 1 223 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 1 226 0
	movl	$0, -16(%ebp)
	.loc 1 228 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_draw_font_info
	addl	%eax, 8(%ebp)
	.loc 1 230 0
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_get_line_height
	addl	$1, %eax
	addl	%eax, 8(%ebp)
	.loc 1 233 0
	movl	$0, -12(%ebp)
	jmp	L35
L38:
	.loc 1 235 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_draw_font_line
	movl	%eax, -20(%ebp)
	.loc 1 236 0
	cmpl	$0, -20(%ebp)
	je	L36
	.loc 1 238 0
	movl	-16(%ebp), %eax
	cmpl	-20(%ebp), %eax
	jnb	L37
	.loc 1 239 0
	movl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
L37:
	.loc 1 240 0
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_get_line_height
	addl	$1, %eax
	addl	%eax, 8(%ebp)
L36:
	.loc 1 233 0 discriminator 2
	addl	$16, -12(%ebp)
L35:
	.loc 1 233 0 is_stmt 0 discriminator 1
	cmpl	$255, -12(%ebp)
	jle	L38
	.loc 1 244 0 is_stmt 1
	movl	20(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_tga_set_font
	.loc 1 248 0
	movl	_font_picture_test_string, %eax
	testl	%eax, %eax
	je	L39
	.loc 1 250 0
	movl	_left_margin, %eax
	movl	-16(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	$LC41, 8(%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_draw_string
	.loc 1 251 0
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_get_line_height
	addl	$1, %eax
	addl	%eax, 8(%ebp)
L39:
	.loc 1 253 0
	movl	8(%ebp), %eax
	.loc 1 254 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC42:
	.ascii "*\0"
LC43:
	.ascii "\0"
	.align 4
LC44:
	.ascii "Note: For font format 1 BBX mode has been set to 3\0"
LC46:
	.ascii "Runtime test: %.2lf sec\0"
LC47:
	.ascii "bdf.tga\0"
LC48:
	.ascii "  \0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB20:
	.loc 1 261 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$160, %esp
	.loc 1 261 0
	call	___main
LVL0:
	.loc 1 264 0
	movl	$0, 152(%esp)
	.loc 1 265 0
	movl	$0, 148(%esp)
	.loc 1 266 0
	movl	$LC42, 128(%esp)
	.loc 1 267 0
	movl	$LC43, 124(%esp)
	.loc 1 270 0
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, 12(%ebp)
L50:
	.loc 1 280 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	L64
	.loc 1 282 0
	movl	$104, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_is_arg
	testl	%eax, %eax
	je	L44
	.loc 1 284 0
	call	_help
	.loc 1 285 0
	movl	$1, (%esp)
	call	_exit
L44:
	.loc 1 287 0
	movl	$118, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_is_arg
	testl	%eax, %eax
	je	L45
	.loc 1 289 0
	movl	$1, 148(%esp)
	jmp	L50
L45:
	.loc 1 291 0
	movl	$97, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_is_arg
	testl	%eax, %eax
	je	L47
	.loc 1 293 0
	movl	$1, _font_picture_extra_info
	jmp	L50
L47:
	.loc 1 295 0
	movl	$116, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_is_arg
	testl	%eax, %eax
	je	L48
	.loc 1 297 0
	movl	$1, _font_picture_test_string
	jmp	L50
L48:
	.loc 1 299 0
	movl	$114, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_is_arg
	testl	%eax, %eax
	je	L49
	.loc 1 301 0
	movl	$1, _runtime_test
	jmp	L50
L49:
	.loc 1 303 0
	movl	$_build_bbx_mode, 8(%esp)
	movl	$98, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_num_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 306 0
	movl	$_font_format, 8(%esp)
	movl	$102, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_num_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 309 0
	movl	$_left_margin, 8(%esp)
	movl	$108, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_num_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 312 0
	leal	124(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$100, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_str_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 315 0
	movl	$_c_filename, 8(%esp)
	movl	$111, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_str_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 318 0
	movl	$_target_fontname, 8(%esp)
	movl	$110, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_str_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 321 0
	leal	128(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$109, 4(%esp)
	leal	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_str_arg
	testl	%eax, %eax
	jne	L50
	.loc 1 326 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, 152(%esp)
	.loc 1 327 0
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, 12(%ebp)
	.loc 1 280 0
	jmp	L50
L64:
	.loc 1 281 0
	nop
	.loc 1 331 0
	cmpl	$0, 152(%esp)
	jne	L51
	.loc 1 333 0
	call	_help
	.loc 1 334 0
	movl	$1, (%esp)
	call	_exit
L51:
	.loc 1 337 0
	movl	$0, 156(%esp)
	.loc 1 338 0
	movl	124(%esp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	L52
	.loc 1 340 0
	movl	124(%esp), %eax
	movl	$0, 16(%esp)
	movl	$LC42, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	_bf_OpenFromFile
	movl	%eax, 156(%esp)
	.loc 1 341 0
	cmpl	$0, 156(%esp)
	jne	L52
	.loc 1 343 0
	movl	$1, (%esp)
	call	_exit
L52:
	.loc 1 347 0
	movl	_font_format, %eax
	cmpl	$2, %eax
	jne	L53
	.loc 1 349 0
	movl	$3, _build_bbx_mode
L53:
	.loc 1 354 0
	movl	_font_format, %eax
	movl	%eax, %ecx
	movl	128(%esp), %eax
	movl	_build_bbx_mode, %edx
	movl	%ecx, 16(%esp)
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	148(%esp), %eax
	movl	%eax, 4(%esp)
	movl	152(%esp), %eax
	movl	%eax, (%esp)
	call	_bf_OpenFromFile
	movl	%eax, 140(%esp)
	.loc 1 356 0
	cmpl	$0, 140(%esp)
	jne	L54
	.loc 1 358 0
	movl	$1, (%esp)
	call	_exit
L54:
	.loc 1 361 0
	movl	_font_format, %eax
	cmpl	$2, %eax
	jne	L55
	.loc 1 364 0
	movl	$LC44, 4(%esp)
	movl	140(%esp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
L55:
	.loc 1 367 0
	cmpl	$0, 156(%esp)
	je	L56
	.loc 1 369 0
	movl	$600, 4(%esp)
	movl	$1024, (%esp)
	call	_tga_init
	.loc 1 370 0
	movl	140(%esp), %eax
	movl	%eax, 12(%esp)
	movl	156(%esp), %eax
	movl	%eax, 8(%esp)
	movl	152(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_tga_draw_font
	movl	%eax, 136(%esp)
	.loc 1 372 0
	movl	_runtime_test, %eax
	testl	%eax, %eax
	je	L57
LBB2:
	.loc 1 375 0
	call	_clock
	movl	%eax, 132(%esp)
	.loc 1 377 0
	leal	60(%esp), %eax
	movl	%eax, (%esp)
	call	_fd_init
	.loc 1 378 0
	movl	140(%esp), %eax
	movl	1176(%eax), %eax
	movl	%eax, 4(%esp)
	leal	60(%esp), %eax
	movl	%eax, (%esp)
	call	_fd_set_font
	.loc 1 379 0
	movl	$0, 144(%esp)
	jmp	L58
L59:
	.loc 1 380 0 discriminator 3
	movl	_left_margin, %eax
	movl	$LC41, 12(%esp)
	movl	136(%esp), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	leal	60(%esp), %eax
	movl	%eax, (%esp)
	call	_fd_draw_string
	.loc 1 379 0 discriminator 3
	addl	$1, 144(%esp)
L58:
	.loc 1 379 0 is_stmt 0 discriminator 1
	cmpl	$9999, 144(%esp)
	jle	L59
	.loc 1 381 0 is_stmt 1
	call	_clock
	subl	132(%esp), %eax
	movl	%eax, 32(%esp)
	movl	$0, 36(%esp)
	fildq	32(%esp)
	fstpl	40(%esp)
	fldl	40(%esp)
	fldl	LC45
	fdivrp	%st, %st(1)
	fstpl	8(%esp)
	movl	$LC46, 4(%esp)
	movl	140(%esp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
L57:
LBE2:
	.loc 1 384 0
	movl	$LC47, (%esp)
	call	_tga_save
L56:
	.loc 1 388 0
	movl	_c_filename, %eax
	testl	%eax, %eax
	je	L60
	.loc 1 391 0
	movl	_font_format, %eax
	testl	%eax, %eax
	jne	L61
	.loc 1 393 0
	movl	_target_fontname, %edx
	movl	_c_filename, %eax
	movl	$LC48, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	140(%esp), %eax
	movl	%eax, (%esp)
	call	_bf_WriteUCGCByFilename
	jmp	L60
L61:
	.loc 1 398 0
	movl	_target_fontname, %edx
	movl	_c_filename, %eax
	movl	$LC48, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	140(%esp), %eax
	movl	%eax, (%esp)
	call	_bf_WriteU8G2CByFilename
L60:
	.loc 1 403 0
	movl	140(%esp), %eax
	movl	%eax, (%esp)
	call	_bf_Close
	.loc 1 404 0
	movl	$0, %eax
	.loc 1 405 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
.lcomm _s.3888,256,32
	.section .rdata,"dr"
	.align 8
LC45:
	.long	0
	.long	1083129856
	.text
Letext0:
	.file 2 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 3 "/usr/include/machine/_default_types.h"
	.file 4 "/usr/include/sys/lock.h"
	.file 5 "/usr/include/sys/_types.h"
	.file 6 "/usr/include/sys/reent.h"
	.file 7 "/usr/include/stdlib.h"
	.file 8 "/usr/include/sys/_stdint.h"
	.file 9 "/usr/include/sys/types.h"
	.file 10 "/usr/include/time.h"
	.file 11 "/usr/include/cygwin/time.h"
	.file 12 "/usr/include/cygwin/signal.h"
	.file 13 "/usr/include/stdio.h"
	.file 14 "bdf_glyph.h"
	.file 15 "bdf_font.h"
	.file 16 "fd.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x18cc
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "main.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.uleb128 0x3
	.ascii "size_t\0"
	.byte	0x2
	.byte	0xd8
	.long	0x9e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.uleb128 0x2
	.byte	0xc
	.byte	0x4
	.ascii "long double\0"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0x3
	.ascii "__uint8_t\0"
	.byte	0x3
	.byte	0x2b
	.long	0x104
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "long unsigned int\0"
	.uleb128 0x3
	.ascii "_LOCK_T\0"
	.byte	0x4
	.byte	0xc
	.long	0x160
	.uleb128 0x4
	.byte	0x4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii "long int\0"
	.uleb128 0x3
	.ascii "_off64_t\0"
	.byte	0x5
	.byte	0x5e
	.long	0xc4
	.uleb128 0x3
	.ascii "_fpos_t\0"
	.byte	0x5
	.byte	0x72
	.long	0x162
	.uleb128 0x3
	.ascii "_fpos64_t\0"
	.byte	0x5
	.byte	0x78
	.long	0x16e
	.uleb128 0x3
	.ascii "_ssize_t\0"
	.byte	0x5
	.byte	0x91
	.long	0x89
	.uleb128 0x5
	.ascii "wint_t\0"
	.byte	0x2
	.word	0x165
	.long	0x9e
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0xa6
	.long	0x1e1
	.uleb128 0x7
	.ascii "__wch\0"
	.byte	0x5
	.byte	0xa8
	.long	0x1ae
	.uleb128 0x7
	.ascii "__wchb\0"
	.byte	0x5
	.byte	0xa9
	.long	0x1e1
	.byte	0
	.uleb128 0x8
	.long	0x104
	.long	0x1f1
	.uleb128 0x9
	.long	0x1f1
	.byte	0x3
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "sizetype\0"
	.uleb128 0xa
	.byte	0x8
	.byte	0x5
	.byte	0xa3
	.long	0x226
	.uleb128 0xb
	.ascii "__count\0"
	.byte	0x5
	.byte	0xa5
	.long	0x89
	.byte	0
	.uleb128 0xb
	.ascii "__value\0"
	.byte	0x5
	.byte	0xaa
	.long	0x1bd
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.ascii "_mbstate_t\0"
	.byte	0x5
	.byte	0xab
	.long	0x1fd
	.uleb128 0x3
	.ascii "_flock_t\0"
	.byte	0x5
	.byte	0xaf
	.long	0x151
	.uleb128 0xc
	.byte	0x4
	.long	0x24e
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0xd
	.long	0x24e
	.uleb128 0x3
	.ascii "__ULong\0"
	.byte	0x6
	.byte	0x16
	.long	0x13c
	.uleb128 0xe
	.ascii "_Bigint\0"
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.long	0x2ca
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x31
	.long	0x2ca
	.byte	0
	.uleb128 0xb
	.ascii "_k\0"
	.byte	0x6
	.byte	0x32
	.long	0x89
	.byte	0x4
	.uleb128 0xb
	.ascii "_maxwds\0"
	.byte	0x6
	.byte	0x32
	.long	0x89
	.byte	0x8
	.uleb128 0xb
	.ascii "_sign\0"
	.byte	0x6
	.byte	0x32
	.long	0x89
	.byte	0xc
	.uleb128 0xb
	.ascii "_wds\0"
	.byte	0x6
	.byte	0x32
	.long	0x89
	.byte	0x10
	.uleb128 0xb
	.ascii "_x\0"
	.byte	0x6
	.byte	0x33
	.long	0x2d0
	.byte	0x14
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x26a
	.uleb128 0x8
	.long	0x25b
	.long	0x2e0
	.uleb128 0x9
	.long	0x1f1
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__tm\0"
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.long	0x38e
	.uleb128 0xb
	.ascii "__tm_sec\0"
	.byte	0x6
	.byte	0x39
	.long	0x89
	.byte	0
	.uleb128 0xb
	.ascii "__tm_min\0"
	.byte	0x6
	.byte	0x3a
	.long	0x89
	.byte	0x4
	.uleb128 0xb
	.ascii "__tm_hour\0"
	.byte	0x6
	.byte	0x3b
	.long	0x89
	.byte	0x8
	.uleb128 0xb
	.ascii "__tm_mday\0"
	.byte	0x6
	.byte	0x3c
	.long	0x89
	.byte	0xc
	.uleb128 0xb
	.ascii "__tm_mon\0"
	.byte	0x6
	.byte	0x3d
	.long	0x89
	.byte	0x10
	.uleb128 0xb
	.ascii "__tm_year\0"
	.byte	0x6
	.byte	0x3e
	.long	0x89
	.byte	0x14
	.uleb128 0xb
	.ascii "__tm_wday\0"
	.byte	0x6
	.byte	0x3f
	.long	0x89
	.byte	0x18
	.uleb128 0xb
	.ascii "__tm_yday\0"
	.byte	0x6
	.byte	0x40
	.long	0x89
	.byte	0x1c
	.uleb128 0xb
	.ascii "__tm_isdst\0"
	.byte	0x6
	.byte	0x41
	.long	0x89
	.byte	0x20
	.byte	0
	.uleb128 0xf
	.secrel32	LASF0
	.word	0x108
	.byte	0x6
	.byte	0x4a
	.long	0x3e3
	.uleb128 0xb
	.ascii "_fnargs\0"
	.byte	0x6
	.byte	0x4b
	.long	0x3e3
	.byte	0
	.uleb128 0xb
	.ascii "_dso_handle\0"
	.byte	0x6
	.byte	0x4c
	.long	0x3e3
	.byte	0x80
	.uleb128 0x10
	.ascii "_fntypes\0"
	.byte	0x6
	.byte	0x4e
	.long	0x25b
	.word	0x100
	.uleb128 0x10
	.ascii "_is_cxa\0"
	.byte	0x6
	.byte	0x51
	.long	0x25b
	.word	0x104
	.byte	0
	.uleb128 0x8
	.long	0x160
	.long	0x3f3
	.uleb128 0x9
	.long	0x1f1
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.ascii "_atexit\0"
	.word	0x190
	.byte	0x6
	.byte	0x5d
	.long	0x439
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x5e
	.long	0x439
	.byte	0
	.uleb128 0xb
	.ascii "_ind\0"
	.byte	0x6
	.byte	0x5f
	.long	0x89
	.byte	0x4
	.uleb128 0xb
	.ascii "_fns\0"
	.byte	0x6
	.byte	0x61
	.long	0x43f
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF0
	.byte	0x6
	.byte	0x62
	.long	0x38e
	.byte	0x88
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x3f3
	.uleb128 0x8
	.long	0x44f
	.long	0x44f
	.uleb128 0x9
	.long	0x1f1
	.byte	0x1f
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x455
	.uleb128 0x13
	.uleb128 0xe
	.ascii "__sbuf\0"
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.long	0x482
	.uleb128 0xb
	.ascii "_base\0"
	.byte	0x6
	.byte	0x76
	.long	0x482
	.byte	0
	.uleb128 0xb
	.ascii "_size\0"
	.byte	0x6
	.byte	0x77
	.long	0x89
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x104
	.uleb128 0x14
	.long	0x19e
	.long	0x4a6
	.uleb128 0x15
	.long	0x4a6
	.uleb128 0x15
	.long	0x160
	.uleb128 0x15
	.long	0x248
	.uleb128 0x15
	.long	0x90
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x4b1
	.uleb128 0xd
	.long	0x4a6
	.uleb128 0x16
	.ascii "_reent\0"
	.word	0x440
	.byte	0x6
	.word	0x239
	.long	0x650
	.uleb128 0x17
	.ascii "_errno\0"
	.byte	0x6
	.word	0x23b
	.long	0x89
	.byte	0
	.uleb128 0x17
	.ascii "_stdin\0"
	.byte	0x6
	.word	0x240
	.long	0x8d5
	.byte	0x4
	.uleb128 0x17
	.ascii "_stdout\0"
	.byte	0x6
	.word	0x240
	.long	0x8d5
	.byte	0x8
	.uleb128 0x17
	.ascii "_stderr\0"
	.byte	0x6
	.word	0x240
	.long	0x8d5
	.byte	0xc
	.uleb128 0x17
	.ascii "_inc\0"
	.byte	0x6
	.word	0x242
	.long	0x89
	.byte	0x10
	.uleb128 0x17
	.ascii "_emergency\0"
	.byte	0x6
	.word	0x243
	.long	0xb7b
	.byte	0x14
	.uleb128 0x17
	.ascii "_unspecified_locale_info\0"
	.byte	0x6
	.word	0x246
	.long	0x89
	.byte	0x30
	.uleb128 0x17
	.ascii "_locale\0"
	.byte	0x6
	.word	0x247
	.long	0xb97
	.byte	0x34
	.uleb128 0x17
	.ascii "__sdidinit\0"
	.byte	0x6
	.word	0x249
	.long	0x89
	.byte	0x38
	.uleb128 0x17
	.ascii "__cleanup\0"
	.byte	0x6
	.word	0x24b
	.long	0xba8
	.byte	0x3c
	.uleb128 0x17
	.ascii "_result\0"
	.byte	0x6
	.word	0x24e
	.long	0x2ca
	.byte	0x40
	.uleb128 0x17
	.ascii "_result_k\0"
	.byte	0x6
	.word	0x24f
	.long	0x89
	.byte	0x44
	.uleb128 0x17
	.ascii "_p5s\0"
	.byte	0x6
	.word	0x250
	.long	0x2ca
	.byte	0x48
	.uleb128 0x17
	.ascii "_freelist\0"
	.byte	0x6
	.word	0x251
	.long	0xbae
	.byte	0x4c
	.uleb128 0x17
	.ascii "_cvtlen\0"
	.byte	0x6
	.word	0x254
	.long	0x89
	.byte	0x50
	.uleb128 0x17
	.ascii "_cvtbuf\0"
	.byte	0x6
	.word	0x255
	.long	0x248
	.byte	0x54
	.uleb128 0x17
	.ascii "_new\0"
	.byte	0x6
	.word	0x278
	.long	0xb52
	.byte	0x58
	.uleb128 0x18
	.ascii "_atexit\0"
	.byte	0x6
	.word	0x27c
	.long	0x439
	.word	0x148
	.uleb128 0x18
	.ascii "_atexit0\0"
	.byte	0x6
	.word	0x27d
	.long	0x3f3
	.word	0x14c
	.uleb128 0x18
	.ascii "_sig_func\0"
	.byte	0x6
	.word	0x281
	.long	0xbbf
	.word	0x2dc
	.uleb128 0x18
	.ascii "__sglue\0"
	.byte	0x6
	.word	0x286
	.long	0x891
	.word	0x2e0
	.uleb128 0x18
	.ascii "__sf\0"
	.byte	0x6
	.word	0x288
	.long	0xbcb
	.word	0x2f0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x488
	.uleb128 0x14
	.long	0x19e
	.long	0x674
	.uleb128 0x15
	.long	0x4a6
	.uleb128 0x15
	.long	0x160
	.uleb128 0x15
	.long	0x674
	.uleb128 0x15
	.long	0x90
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x256
	.uleb128 0xc
	.byte	0x4
	.long	0x656
	.uleb128 0x14
	.long	0x17e
	.long	0x69e
	.uleb128 0x15
	.long	0x4a6
	.uleb128 0x15
	.long	0x160
	.uleb128 0x15
	.long	0x17e
	.uleb128 0x15
	.long	0x89
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x680
	.uleb128 0x14
	.long	0x89
	.long	0x6b8
	.uleb128 0x15
	.long	0x4a6
	.uleb128 0x15
	.long	0x160
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x6a4
	.uleb128 0x8
	.long	0x104
	.long	0x6ce
	.uleb128 0x9
	.long	0x1f1
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.long	0x104
	.long	0x6de
	.uleb128 0x9
	.long	0x1f1
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__sFILE64\0"
	.byte	0x70
	.byte	0x6
	.byte	0xef
	.long	0x85e
	.uleb128 0xb
	.ascii "_p\0"
	.byte	0x6
	.byte	0xf0
	.long	0x482
	.byte	0
	.uleb128 0xb
	.ascii "_r\0"
	.byte	0x6
	.byte	0xf1
	.long	0x89
	.byte	0x4
	.uleb128 0xb
	.ascii "_w\0"
	.byte	0x6
	.byte	0xf2
	.long	0x89
	.byte	0x8
	.uleb128 0xb
	.ascii "_flags\0"
	.byte	0x6
	.byte	0xf3
	.long	0x115
	.byte	0xc
	.uleb128 0xb
	.ascii "_file\0"
	.byte	0x6
	.byte	0xf4
	.long	0x115
	.byte	0xe
	.uleb128 0xb
	.ascii "_bf\0"
	.byte	0x6
	.byte	0xf5
	.long	0x456
	.byte	0x10
	.uleb128 0xb
	.ascii "_lbfsize\0"
	.byte	0x6
	.byte	0xf6
	.long	0x89
	.byte	0x18
	.uleb128 0xb
	.ascii "_data\0"
	.byte	0x6
	.byte	0xf8
	.long	0x4a6
	.byte	0x1c
	.uleb128 0xb
	.ascii "_cookie\0"
	.byte	0x6
	.byte	0xfb
	.long	0x160
	.byte	0x20
	.uleb128 0xb
	.ascii "_read\0"
	.byte	0x6
	.byte	0xfd
	.long	0x650
	.byte	0x24
	.uleb128 0xb
	.ascii "_write\0"
	.byte	0x6
	.byte	0xff
	.long	0x67a
	.byte	0x28
	.uleb128 0x17
	.ascii "_seek\0"
	.byte	0x6
	.word	0x102
	.long	0x69e
	.byte	0x2c
	.uleb128 0x17
	.ascii "_close\0"
	.byte	0x6
	.word	0x103
	.long	0x6b8
	.byte	0x30
	.uleb128 0x17
	.ascii "_ub\0"
	.byte	0x6
	.word	0x106
	.long	0x456
	.byte	0x34
	.uleb128 0x17
	.ascii "_up\0"
	.byte	0x6
	.word	0x107
	.long	0x482
	.byte	0x3c
	.uleb128 0x17
	.ascii "_ur\0"
	.byte	0x6
	.word	0x108
	.long	0x89
	.byte	0x40
	.uleb128 0x17
	.ascii "_ubuf\0"
	.byte	0x6
	.word	0x10b
	.long	0x6be
	.byte	0x44
	.uleb128 0x17
	.ascii "_nbuf\0"
	.byte	0x6
	.word	0x10c
	.long	0x6ce
	.byte	0x47
	.uleb128 0x17
	.ascii "_lb\0"
	.byte	0x6
	.word	0x10f
	.long	0x456
	.byte	0x48
	.uleb128 0x17
	.ascii "_blksize\0"
	.byte	0x6
	.word	0x112
	.long	0x89
	.byte	0x50
	.uleb128 0x17
	.ascii "_flags2\0"
	.byte	0x6
	.word	0x113
	.long	0x89
	.byte	0x54
	.uleb128 0x17
	.ascii "_offset\0"
	.byte	0x6
	.word	0x115
	.long	0x16e
	.byte	0x58
	.uleb128 0x17
	.ascii "_seek64\0"
	.byte	0x6
	.word	0x116
	.long	0x87c
	.byte	0x60
	.uleb128 0x17
	.ascii "_lock\0"
	.byte	0x6
	.word	0x119
	.long	0x238
	.byte	0x64
	.uleb128 0x17
	.ascii "_mbstate\0"
	.byte	0x6
	.word	0x11b
	.long	0x226
	.byte	0x68
	.byte	0
	.uleb128 0x14
	.long	0x18d
	.long	0x87c
	.uleb128 0x15
	.long	0x4a6
	.uleb128 0x15
	.long	0x160
	.uleb128 0x15
	.long	0x18d
	.uleb128 0x15
	.long	0x89
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x85e
	.uleb128 0x5
	.ascii "__FILE\0"
	.byte	0x6
	.word	0x11d
	.long	0x6de
	.uleb128 0x19
	.ascii "_glue\0"
	.byte	0xc
	.byte	0x6
	.word	0x123
	.long	0x8cf
	.uleb128 0x17
	.ascii "_next\0"
	.byte	0x6
	.word	0x125
	.long	0x8cf
	.byte	0
	.uleb128 0x17
	.ascii "_niobs\0"
	.byte	0x6
	.word	0x126
	.long	0x89
	.byte	0x4
	.uleb128 0x17
	.ascii "_iobs\0"
	.byte	0x6
	.word	0x127
	.long	0x8d5
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x891
	.uleb128 0xc
	.byte	0x4
	.long	0x882
	.uleb128 0x19
	.ascii "_rand48\0"
	.byte	0xe
	.byte	0x6
	.word	0x13f
	.long	0x919
	.uleb128 0x17
	.ascii "_seed\0"
	.byte	0x6
	.word	0x140
	.long	0x919
	.byte	0
	.uleb128 0x17
	.ascii "_mult\0"
	.byte	0x6
	.word	0x141
	.long	0x919
	.byte	0x6
	.uleb128 0x17
	.ascii "_add\0"
	.byte	0x6
	.word	0x142
	.long	0xae
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.long	0xae
	.long	0x929
	.uleb128 0x9
	.long	0x1f1
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.word	0x259
	.long	0xad6
	.uleb128 0x17
	.ascii "_unused_rand\0"
	.byte	0x6
	.word	0x25b
	.long	0x9e
	.byte	0
	.uleb128 0x17
	.ascii "_strtok_last\0"
	.byte	0x6
	.word	0x25c
	.long	0x248
	.byte	0x4
	.uleb128 0x17
	.ascii "_asctime_buf\0"
	.byte	0x6
	.word	0x25d
	.long	0xad6
	.byte	0x8
	.uleb128 0x17
	.ascii "_localtime_buf\0"
	.byte	0x6
	.word	0x25e
	.long	0x2e0
	.byte	0x24
	.uleb128 0x17
	.ascii "_gamma_signgam\0"
	.byte	0x6
	.word	0x25f
	.long	0x89
	.byte	0x48
	.uleb128 0x17
	.ascii "_rand_next\0"
	.byte	0x6
	.word	0x260
	.long	0x122
	.byte	0x50
	.uleb128 0x17
	.ascii "_r48\0"
	.byte	0x6
	.word	0x261
	.long	0x8db
	.byte	0x58
	.uleb128 0x17
	.ascii "_mblen_state\0"
	.byte	0x6
	.word	0x262
	.long	0x226
	.byte	0x68
	.uleb128 0x17
	.ascii "_mbtowc_state\0"
	.byte	0x6
	.word	0x263
	.long	0x226
	.byte	0x70
	.uleb128 0x17
	.ascii "_wctomb_state\0"
	.byte	0x6
	.word	0x264
	.long	0x226
	.byte	0x78
	.uleb128 0x17
	.ascii "_l64a_buf\0"
	.byte	0x6
	.word	0x265
	.long	0xae6
	.byte	0x80
	.uleb128 0x17
	.ascii "_signal_buf\0"
	.byte	0x6
	.word	0x266
	.long	0xaf6
	.byte	0x88
	.uleb128 0x17
	.ascii "_getdate_err\0"
	.byte	0x6
	.word	0x267
	.long	0x89
	.byte	0xa0
	.uleb128 0x17
	.ascii "_mbrlen_state\0"
	.byte	0x6
	.word	0x268
	.long	0x226
	.byte	0xa4
	.uleb128 0x17
	.ascii "_mbrtowc_state\0"
	.byte	0x6
	.word	0x269
	.long	0x226
	.byte	0xac
	.uleb128 0x17
	.ascii "_mbsrtowcs_state\0"
	.byte	0x6
	.word	0x26a
	.long	0x226
	.byte	0xb4
	.uleb128 0x17
	.ascii "_wcrtomb_state\0"
	.byte	0x6
	.word	0x26b
	.long	0x226
	.byte	0xbc
	.uleb128 0x17
	.ascii "_wcsrtombs_state\0"
	.byte	0x6
	.word	0x26c
	.long	0x226
	.byte	0xc4
	.uleb128 0x17
	.ascii "_h_errno\0"
	.byte	0x6
	.word	0x26d
	.long	0x89
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.long	0x24e
	.long	0xae6
	.uleb128 0x9
	.long	0x1f1
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.long	0x24e
	.long	0xaf6
	.uleb128 0x9
	.long	0x1f1
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.long	0x24e
	.long	0xb06
	.uleb128 0x9
	.long	0x1f1
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.word	0x272
	.long	0xb32
	.uleb128 0x17
	.ascii "_nextf\0"
	.byte	0x6
	.word	0x275
	.long	0xb32
	.byte	0
	.uleb128 0x17
	.ascii "_nmalloc\0"
	.byte	0x6
	.word	0x276
	.long	0xb42
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.long	0x482
	.long	0xb42
	.uleb128 0x9
	.long	0x1f1
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.long	0x9e
	.long	0xb52
	.uleb128 0x9
	.long	0x1f1
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.word	0x257
	.long	0xb7b
	.uleb128 0x1c
	.ascii "_reent\0"
	.byte	0x6
	.word	0x26e
	.long	0x929
	.uleb128 0x1c
	.ascii "_unused\0"
	.byte	0x6
	.word	0x277
	.long	0xb06
	.byte	0
	.uleb128 0x8
	.long	0x24e
	.long	0xb8b
	.uleb128 0x9
	.long	0x1f1
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.ascii "__locale_t\0"
	.uleb128 0xc
	.byte	0x4
	.long	0xb8b
	.uleb128 0x1e
	.long	0xba8
	.uleb128 0x15
	.long	0x4a6
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xb9d
	.uleb128 0xc
	.byte	0x4
	.long	0x2ca
	.uleb128 0x1e
	.long	0xbbf
	.uleb128 0x15
	.long	0x89
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xbc5
	.uleb128 0xc
	.byte	0x4
	.long	0xbb4
	.uleb128 0x8
	.long	0x882
	.long	0xbdb
	.uleb128 0x9
	.long	0x1f1
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.ascii "_impure_ptr\0"
	.byte	0x6
	.word	0x307
	.long	0x4a6
	.uleb128 0x1f
	.ascii "_global_impure_ptr\0"
	.byte	0x6
	.word	0x308
	.long	0x4ac
	.uleb128 0x20
	.ascii "suboptarg\0"
	.byte	0x7
	.byte	0x63
	.long	0x248
	.uleb128 0x3
	.ascii "uint8_t\0"
	.byte	0x8
	.byte	0x18
	.long	0xf3
	.uleb128 0xd
	.long	0xc1b
	.uleb128 0x3
	.ascii "clock_t\0"
	.byte	0x9
	.byte	0x7b
	.long	0x13c
	.uleb128 0x20
	.ascii "_timezone\0"
	.byte	0xa
	.byte	0x9a
	.long	0x162
	.uleb128 0x20
	.ascii "_daylight\0"
	.byte	0xa
	.byte	0x9b
	.long	0x89
	.uleb128 0x8
	.long	0x248
	.long	0xc70
	.uleb128 0x9
	.long	0x1f1
	.byte	0x1
	.byte	0
	.uleb128 0x20
	.ascii "_tzname\0"
	.byte	0xa
	.byte	0x9e
	.long	0xc60
	.uleb128 0x21
	.ascii "daylight\0"
	.byte	0xb
	.byte	0x1e
	.ascii "__daylight\0"
	.long	0x89
	.uleb128 0x21
	.ascii "timezone\0"
	.byte	0xb
	.byte	0x21
	.ascii "__timezone\0"
	.long	0x162
	.uleb128 0x8
	.long	0x674
	.long	0xcc0
	.uleb128 0x22
	.byte	0
	.uleb128 0x1f
	.ascii "sys_sigabbrev\0"
	.byte	0xc
	.word	0x1b9
	.long	0xcb5
	.uleb128 0x1f
	.ascii "sys_siglist\0"
	.byte	0xc
	.word	0x1ba
	.long	0xcb5
	.uleb128 0x3
	.ascii "FILE\0"
	.byte	0xd
	.byte	0x42
	.long	0x882
	.uleb128 0x3
	.ascii "bf_t\0"
	.byte	0xe
	.byte	0x9
	.long	0xd02
	.uleb128 0x11
	.ascii "_bdf_font_struct\0"
	.word	0x4a4
	.byte	0xf
	.byte	0x10
	.long	0xfc9
	.uleb128 0x12
	.secrel32	LASF1
	.byte	0xf
	.byte	0x12
	.long	0x89
	.byte	0
	.uleb128 0xb
	.ascii "glyph_list\0"
	.byte	0xf
	.byte	0x14
	.long	0x11ae
	.byte	0x4
	.uleb128 0x12
	.secrel32	LASF2
	.byte	0xf
	.byte	0x15
	.long	0x89
	.byte	0x8
	.uleb128 0xb
	.ascii "glyph_max\0"
	.byte	0xf
	.byte	0x16
	.long	0x89
	.byte	0xc
	.uleb128 0xb
	.ascii "line_buf\0"
	.byte	0xf
	.byte	0x19
	.long	0x11ba
	.byte	0x10
	.uleb128 0x10
	.ascii "line_pos\0"
	.byte	0xf
	.byte	0x1a
	.long	0x89
	.word	0x410
	.uleb128 0x10
	.ascii "is_bitmap_parsing\0"
	.byte	0xf
	.byte	0x1b
	.long	0x89
	.word	0x414
	.uleb128 0x23
	.secrel32	LASF3
	.byte	0xf
	.byte	0x1d
	.long	0x162
	.word	0x418
	.uleb128 0x23
	.secrel32	LASF4
	.byte	0xf
	.byte	0x1f
	.long	0x162
	.word	0x41c
	.uleb128 0x23
	.secrel32	LASF5
	.byte	0xf
	.byte	0x20
	.long	0x162
	.word	0x420
	.uleb128 0x10
	.ascii "bbx_w\0"
	.byte	0xf
	.byte	0x22
	.long	0x162
	.word	0x424
	.uleb128 0x10
	.ascii "bbx_h\0"
	.byte	0xf
	.byte	0x23
	.long	0x162
	.word	0x428
	.uleb128 0x10
	.ascii "bbx_x\0"
	.byte	0xf
	.byte	0x24
	.long	0x162
	.word	0x42c
	.uleb128 0x10
	.ascii "bbx_y\0"
	.byte	0xf
	.byte	0x25
	.long	0x162
	.word	0x430
	.uleb128 0x10
	.ascii "bitmap_x\0"
	.byte	0xf
	.byte	0x27
	.long	0x89
	.word	0x434
	.uleb128 0x10
	.ascii "bitmap_y\0"
	.byte	0xf
	.byte	0x28
	.long	0x89
	.word	0x438
	.uleb128 0x10
	.ascii "glyph_pos\0"
	.byte	0xf
	.byte	0x29
	.long	0x89
	.word	0x43c
	.uleb128 0x10
	.ascii "fp\0"
	.byte	0xf
	.byte	0x2a
	.long	0x11cb
	.word	0x440
	.uleb128 0x10
	.ascii "str_font\0"
	.byte	0xf
	.byte	0x2c
	.long	0x248
	.word	0x444
	.uleb128 0x10
	.ascii "str_copyright\0"
	.byte	0xf
	.byte	0x2d
	.long	0x248
	.word	0x448
	.uleb128 0x10
	.ascii "selected_glyphs\0"
	.byte	0xf
	.byte	0x2f
	.long	0x162
	.word	0x44c
	.uleb128 0x10
	.ascii "bbx_mode\0"
	.byte	0xf
	.byte	0x31
	.long	0x89
	.word	0x450
	.uleb128 0x10
	.ascii "max\0"
	.byte	0xf
	.byte	0x33
	.long	0x1006
	.word	0x454
	.uleb128 0x10
	.ascii "enc_w\0"
	.byte	0xf
	.byte	0x36
	.long	0x162
	.word	0x464
	.uleb128 0x10
	.ascii "enc_h\0"
	.byte	0xf
	.byte	0x37
	.long	0x162
	.word	0x468
	.uleb128 0x10
	.ascii "enc_x\0"
	.byte	0xf
	.byte	0x38
	.long	0x162
	.word	0x46c
	.uleb128 0x10
	.ascii "enc_y\0"
	.byte	0xf
	.byte	0x39
	.long	0x162
	.word	0x470
	.uleb128 0x10
	.ascii "dx_min\0"
	.byte	0xf
	.byte	0x3c
	.long	0x162
	.word	0x474
	.uleb128 0x10
	.ascii "dx_max\0"
	.byte	0xf
	.byte	0x3d
	.long	0x162
	.word	0x478
	.uleb128 0x10
	.ascii "x_min\0"
	.byte	0xf
	.byte	0x40
	.long	0x162
	.word	0x47c
	.uleb128 0x10
	.ascii "x_max\0"
	.byte	0xf
	.byte	0x41
	.long	0x162
	.word	0x480
	.uleb128 0x10
	.ascii "bbx_x_max_bit_size\0"
	.byte	0xf
	.byte	0x44
	.long	0x89
	.word	0x484
	.uleb128 0x10
	.ascii "bbx_y_max_bit_size\0"
	.byte	0xf
	.byte	0x45
	.long	0x89
	.word	0x488
	.uleb128 0x10
	.ascii "bbx_w_max_bit_size\0"
	.byte	0xf
	.byte	0x46
	.long	0x89
	.word	0x48c
	.uleb128 0x10
	.ascii "bbx_h_max_bit_size\0"
	.byte	0xf
	.byte	0x47
	.long	0x89
	.word	0x490
	.uleb128 0x10
	.ascii "dx_max_bit_size\0"
	.byte	0xf
	.byte	0x48
	.long	0x89
	.word	0x494
	.uleb128 0x23
	.secrel32	LASF6
	.byte	0xf
	.byte	0x4b
	.long	0x119c
	.word	0x498
	.uleb128 0x23
	.secrel32	LASF7
	.byte	0xf
	.byte	0x4c
	.long	0x89
	.word	0x49c
	.uleb128 0x23
	.secrel32	LASF8
	.byte	0xf
	.byte	0x4d
	.long	0x89
	.word	0x4a0
	.byte	0
	.uleb128 0xe
	.ascii "_bbx_struct\0"
	.byte	0x10
	.byte	0xe
	.byte	0xc
	.long	0x1006
	.uleb128 0xb
	.ascii "w\0"
	.byte	0xe
	.byte	0xe
	.long	0x162
	.byte	0
	.uleb128 0xb
	.ascii "h\0"
	.byte	0xe
	.byte	0xf
	.long	0x162
	.byte	0x4
	.uleb128 0xb
	.ascii "x\0"
	.byte	0xe
	.byte	0x10
	.long	0x162
	.byte	0x8
	.uleb128 0xb
	.ascii "y\0"
	.byte	0xe
	.byte	0x11
	.long	0x162
	.byte	0xc
	.byte	0
	.uleb128 0x3
	.ascii "bbx_t\0"
	.byte	0xe
	.byte	0x13
	.long	0xfc9
	.uleb128 0xe
	.ascii "_bdf_glyph_struct\0"
	.byte	0x60
	.byte	0xe
	.byte	0x16
	.long	0x1196
	.uleb128 0xb
	.ascii "bf\0"
	.byte	0xe
	.byte	0x18
	.long	0x1196
	.byte	0
	.uleb128 0x12
	.secrel32	LASF3
	.byte	0xe
	.byte	0x1a
	.long	0x162
	.byte	0x4
	.uleb128 0xb
	.ascii "map_to\0"
	.byte	0xe
	.byte	0x1b
	.long	0x162
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF4
	.byte	0xe
	.byte	0x1d
	.long	0x162
	.byte	0xc
	.uleb128 0x12
	.secrel32	LASF5
	.byte	0xe
	.byte	0x1e
	.long	0x162
	.byte	0x10
	.uleb128 0xb
	.ascii "bbx\0"
	.byte	0xe
	.byte	0x20
	.long	0x1006
	.byte	0x14
	.uleb128 0xb
	.ascii "shift_x\0"
	.byte	0xe
	.byte	0x21
	.long	0x162
	.byte	0x24
	.uleb128 0xb
	.ascii "bitmap_data\0"
	.byte	0xe
	.byte	0x23
	.long	0x119c
	.byte	0x28
	.uleb128 0xb
	.ascii "bitmap_width\0"
	.byte	0xe
	.byte	0x24
	.long	0x89
	.byte	0x2c
	.uleb128 0xb
	.ascii "bitmap_height\0"
	.byte	0xe
	.byte	0x25
	.long	0x89
	.byte	0x30
	.uleb128 0x12
	.secrel32	LASF6
	.byte	0xe
	.byte	0x2a
	.long	0x119c
	.byte	0x34
	.uleb128 0x12
	.secrel32	LASF7
	.byte	0xe
	.byte	0x2b
	.long	0x89
	.byte	0x38
	.uleb128 0x12
	.secrel32	LASF8
	.byte	0xe
	.byte	0x2c
	.long	0x89
	.byte	0x3c
	.uleb128 0xb
	.ascii "target_bit_pos\0"
	.byte	0xe
	.byte	0x2d
	.long	0x89
	.byte	0x40
	.uleb128 0xb
	.ascii "rle_bits_per_0\0"
	.byte	0xe
	.byte	0x31
	.long	0x9e
	.byte	0x44
	.uleb128 0xb
	.ascii "rle_bits_per_1\0"
	.byte	0xe
	.byte	0x32
	.long	0x9e
	.byte	0x48
	.uleb128 0xb
	.ascii "rle_is_first\0"
	.byte	0xe
	.byte	0x34
	.long	0x89
	.byte	0x4c
	.uleb128 0xb
	.ascii "rle_bitcnt\0"
	.byte	0xe
	.byte	0x35
	.long	0x9e
	.byte	0x50
	.uleb128 0xb
	.ascii "rle_last_0\0"
	.byte	0xe
	.byte	0x36
	.long	0x9e
	.byte	0x54
	.uleb128 0xb
	.ascii "rle_last_1\0"
	.byte	0xe
	.byte	0x37
	.long	0x9e
	.byte	0x58
	.uleb128 0xb
	.ascii "width_deviation\0"
	.byte	0xe
	.byte	0x39
	.long	0x162
	.byte	0x5c
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xcf6
	.uleb128 0xc
	.byte	0x4
	.long	0xc1b
	.uleb128 0x3
	.ascii "bg_t\0"
	.byte	0xe
	.byte	0x3c
	.long	0x1013
	.uleb128 0xc
	.byte	0x4
	.long	0x11b4
	.uleb128 0xc
	.byte	0x4
	.long	0x11a2
	.uleb128 0x8
	.long	0x24e
	.long	0x11cb
	.uleb128 0x24
	.long	0x1f1
	.word	0x3ff
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xcea
	.uleb128 0xe
	.ascii "fd_struct\0"
	.byte	0x40
	.byte	0x10
	.byte	0x8
	.long	0x13bf
	.uleb128 0xb
	.ascii "target_x\0"
	.byte	0x10
	.byte	0xa
	.long	0x9e
	.byte	0
	.uleb128 0xb
	.ascii "target_y\0"
	.byte	0x10
	.byte	0xb
	.long	0x9e
	.byte	0x4
	.uleb128 0xb
	.ascii "is_transparent\0"
	.byte	0x10
	.byte	0xc
	.long	0x9e
	.byte	0x8
	.uleb128 0xb
	.ascii "x\0"
	.byte	0x10
	.byte	0xe
	.long	0x9e
	.byte	0xc
	.uleb128 0xb
	.ascii "y\0"
	.byte	0x10
	.byte	0xf
	.long	0x9e
	.byte	0x10
	.uleb128 0xb
	.ascii "glyph_width\0"
	.byte	0x10
	.byte	0x10
	.long	0x9e
	.byte	0x14
	.uleb128 0xb
	.ascii "glyph_height\0"
	.byte	0x10
	.byte	0x11
	.long	0x9e
	.byte	0x18
	.uleb128 0xb
	.ascii "decode_ptr\0"
	.byte	0x10
	.byte	0x13
	.long	0x13bf
	.byte	0x1c
	.uleb128 0xb
	.ascii "decode_bit_pos\0"
	.byte	0x10
	.byte	0x14
	.long	0x9e
	.byte	0x20
	.uleb128 0xb
	.ascii "decode_byte\0"
	.byte	0x10
	.byte	0x15
	.long	0x9e
	.byte	0x24
	.uleb128 0x12
	.secrel32	LASF2
	.byte	0x10
	.byte	0x17
	.long	0xc1b
	.byte	0x28
	.uleb128 0xb
	.ascii "bits_per_0\0"
	.byte	0x10
	.byte	0x18
	.long	0xc1b
	.byte	0x29
	.uleb128 0xb
	.ascii "bits_per_1\0"
	.byte	0x10
	.byte	0x19
	.long	0xc1b
	.byte	0x2a
	.uleb128 0xb
	.ascii "bits_per_char_width\0"
	.byte	0x10
	.byte	0x1a
	.long	0xc1b
	.byte	0x2b
	.uleb128 0xb
	.ascii "bits_per_char_height\0"
	.byte	0x10
	.byte	0x1b
	.long	0xc1b
	.byte	0x2c
	.uleb128 0xb
	.ascii "bits_per_char_x\0"
	.byte	0x10
	.byte	0x1c
	.long	0xc1b
	.byte	0x2d
	.uleb128 0xb
	.ascii "bits_per_char_y\0"
	.byte	0x10
	.byte	0x1d
	.long	0xc1b
	.byte	0x2e
	.uleb128 0xb
	.ascii "bits_per_delta_x\0"
	.byte	0x10
	.byte	0x1e
	.long	0xc1b
	.byte	0x2f
	.uleb128 0xb
	.ascii "char_width\0"
	.byte	0x10
	.byte	0x1f
	.long	0xc1b
	.byte	0x30
	.uleb128 0xb
	.ascii "char_height\0"
	.byte	0x10
	.byte	0x20
	.long	0xc1b
	.byte	0x31
	.uleb128 0xb
	.ascii "char_descent\0"
	.byte	0x10
	.byte	0x21
	.long	0xc1b
	.byte	0x32
	.uleb128 0xb
	.ascii "capital_a_pos\0"
	.byte	0x10
	.byte	0x22
	.long	0x9e
	.byte	0x34
	.uleb128 0xb
	.ascii "small_a_pos\0"
	.byte	0x10
	.byte	0x23
	.long	0x9e
	.byte	0x38
	.uleb128 0xb
	.ascii "font\0"
	.byte	0x10
	.byte	0x25
	.long	0x119c
	.byte	0x3c
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xc2a
	.uleb128 0x3
	.ascii "fd_t\0"
	.byte	0x10
	.byte	0x28
	.long	0x11d1
	.uleb128 0x25
	.ascii "left_margin\0"
	.byte	0x1
	.byte	0x79
	.long	0x13c
	.uleb128 0x5
	.byte	0x3
	.long	_left_margin
	.uleb128 0x25
	.ascii "build_bbx_mode\0"
	.byte	0x1
	.byte	0x7a
	.long	0x13c
	.uleb128 0x5
	.byte	0x3
	.long	_build_bbx_mode
	.uleb128 0x25
	.ascii "font_format\0"
	.byte	0x1
	.byte	0x7b
	.long	0x13c
	.uleb128 0x5
	.byte	0x3
	.long	_font_format
	.uleb128 0x25
	.ascii "font_picture_extra_info\0"
	.byte	0x1
	.byte	0x7c
	.long	0x89
	.uleb128 0x5
	.byte	0x3
	.long	_font_picture_extra_info
	.uleb128 0x25
	.ascii "font_picture_test_string\0"
	.byte	0x1
	.byte	0x7d
	.long	0x89
	.uleb128 0x5
	.byte	0x3
	.long	_font_picture_test_string
	.uleb128 0x25
	.ascii "runtime_test\0"
	.byte	0x1
	.byte	0x7e
	.long	0x89
	.uleb128 0x5
	.byte	0x3
	.long	_runtime_test
	.uleb128 0x25
	.ascii "c_filename\0"
	.byte	0x1
	.byte	0x7f
	.long	0x248
	.uleb128 0x5
	.byte	0x3
	.long	_c_filename
	.uleb128 0x25
	.ascii "target_fontname\0"
	.byte	0x1
	.byte	0x80
	.long	0x248
	.uleb128 0x5
	.byte	0x3
	.long	_target_fontname
	.uleb128 0x26
	.ascii "main\0"
	.byte	0x1
	.word	0x104
	.long	0x89
	.long	LFB20
	.long	LFE20-LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x15ad
	.uleb128 0x27
	.ascii "argc\0"
	.byte	0x1
	.word	0x104
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "argv\0"
	.byte	0x1
	.word	0x104
	.long	0x15ad
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x28
	.secrel32	LASF9
	.byte	0x1
	.word	0x106
	.long	0x1196
	.uleb128 0x3
	.byte	0x74
	.sleb128 156
	.uleb128 0x29
	.ascii "bf\0"
	.byte	0x1
	.word	0x107
	.long	0x1196
	.uleb128 0x3
	.byte	0x74
	.sleb128 140
	.uleb128 0x29
	.ascii "bdf_filename\0"
	.byte	0x1
	.word	0x108
	.long	0x248
	.uleb128 0x3
	.byte	0x74
	.sleb128 152
	.uleb128 0x28
	.secrel32	LASF1
	.byte	0x1
	.word	0x109
	.long	0x89
	.uleb128 0x3
	.byte	0x74
	.sleb128 148
	.uleb128 0x29
	.ascii "map_str\0"
	.byte	0x1
	.word	0x10a
	.long	0x248
	.uleb128 0x3
	.byte	0x74
	.sleb128 128
	.uleb128 0x29
	.ascii "desc_font_str\0"
	.byte	0x1
	.word	0x10b
	.long	0x248
	.uleb128 0x3
	.byte	0x74
	.sleb128 124
	.uleb128 0x29
	.ascii "y\0"
	.byte	0x1
	.word	0x10c
	.long	0x9e
	.uleb128 0x3
	.byte	0x74
	.sleb128 136
	.uleb128 0x2a
	.long	LBB2
	.long	LBE2-LBB2
	.uleb128 0x29
	.ascii "i\0"
	.byte	0x1
	.word	0x176
	.long	0x162
	.uleb128 0x3
	.byte	0x74
	.sleb128 144
	.uleb128 0x29
	.ascii "c\0"
	.byte	0x1
	.word	0x177
	.long	0xc2f
	.uleb128 0x3
	.byte	0x74
	.sleb128 132
	.uleb128 0x29
	.ascii "fd\0"
	.byte	0x1
	.word	0x178
	.long	0x13c5
	.uleb128 0x2
	.byte	0x74
	.sleb128 60
	.byte	0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x248
	.uleb128 0x2b
	.ascii "tga_draw_font\0"
	.byte	0x1
	.byte	0xde
	.long	0x9e
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x1633
	.uleb128 0x2c
	.ascii "y\0"
	.byte	0x1
	.byte	0xde
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.secrel32	LASF10
	.byte	0x1
	.byte	0xde
	.long	0x674
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2d
	.secrel32	LASF9
	.byte	0x1
	.byte	0xde
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2c
	.ascii "bf\0"
	.byte	0x1
	.byte	0xde
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0xe0
	.long	0x162
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "x\0"
	.byte	0x1
	.byte	0xe1
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x2e
	.ascii "xmax\0"
	.byte	0x1
	.byte	0xe1
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x2b
	.ascii "tga_draw_font_info\0"
	.byte	0x1
	.byte	0xb6
	.long	0x9e
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x16d3
	.uleb128 0x2c
	.ascii "y\0"
	.byte	0x1
	.byte	0xb6
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.secrel32	LASF10
	.byte	0x1
	.byte	0xb6
	.long	0x674
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2d
	.secrel32	LASF9
	.byte	0x1
	.byte	0xb6
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2c
	.ascii "bf\0"
	.byte	0x1
	.byte	0xb6
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x2e
	.ascii "x\0"
	.byte	0x1
	.byte	0xb8
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x2e
	.ascii "cap_a\0"
	.byte	0x1
	.byte	0xb9
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x2e
	.ascii "cap_a_height\0"
	.byte	0x1
	.byte	0xb9
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "s\0"
	.byte	0x1
	.byte	0xba
	.long	0x16d3
	.uleb128 0x5
	.byte	0x3
	.long	_s.3888
	.byte	0
	.uleb128 0x8
	.long	0x24e
	.long	0x16e3
	.uleb128 0x9
	.long	0x1f1
	.byte	0xff
	.byte	0
	.uleb128 0x2b
	.ascii "tga_draw_font_line\0"
	.byte	0x1
	.byte	0x8f
	.long	0x9e
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x1780
	.uleb128 0x2c
	.ascii "y\0"
	.byte	0x1
	.byte	0x8f
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2c
	.ascii "enc_start\0"
	.byte	0x1
	.byte	0x8f
	.long	0x162
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2d
	.secrel32	LASF9
	.byte	0x1
	.byte	0x8f
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2c
	.ascii "bf\0"
	.byte	0x1
	.byte	0x8f
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0x91
	.long	0x162
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "x\0"
	.byte	0x1
	.byte	0x92
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x2e
	.ascii "is_empty\0"
	.byte	0x1
	.byte	0x93
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x2e
	.ascii "pre\0"
	.byte	0x1
	.byte	0x94
	.long	0x1780
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x8
	.long	0x24e
	.long	0x1790
	.uleb128 0x9
	.long	0x1f1
	.byte	0x1f
	.byte	0
	.uleb128 0x2b
	.ascii "tga_get_line_height\0"
	.byte	0x1
	.byte	0x84
	.long	0x9e
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x17e1
	.uleb128 0x2d
	.secrel32	LASF9
	.byte	0x1
	.byte	0x84
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2c
	.ascii "bf\0"
	.byte	0x1
	.byte	0x84
	.long	0x1196
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2e
	.ascii "h\0"
	.byte	0x1
	.byte	0x86
	.long	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2f
	.ascii "help\0"
	.byte	0x1
	.byte	0x49
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x30
	.ascii "is_arg\0"
	.byte	0x1
	.byte	0x3b
	.long	0x89
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x182b
	.uleb128 0x2c
	.ascii "argv\0"
	.byte	0x1
	.byte	0x3b
	.long	0x182b
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2c
	.ascii "c\0"
	.byte	0x1
	.byte	0x3b
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x15ad
	.uleb128 0x2b
	.ascii "get_num_arg\0"
	.byte	0x1
	.byte	0x21
	.long	0x89
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x187f
	.uleb128 0x2c
	.ascii "argv\0"
	.byte	0x1
	.byte	0x21
	.long	0x182b
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2c
	.ascii "c\0"
	.byte	0x1
	.byte	0x21
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2c
	.ascii "result\0"
	.byte	0x1
	.byte	0x21
	.long	0x187f
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x13c
	.uleb128 0x31
	.ascii "get_str_arg\0"
	.byte	0x1
	.byte	0xa
	.long	0x89
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2c
	.ascii "argv\0"
	.byte	0x1
	.byte	0xa
	.long	0x182b
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2c
	.ascii "c\0"
	.byte	0x1
	.byte	0xa
	.long	0x89
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2c
	.ascii "result\0"
	.byte	0x1
	.byte	0xa
	.long	0x15ad
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.byte	0
	.section	.debug_abbrev,"dr"
Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0x8
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"dr"
	.long	0x1c
	.word	0x2
	.secrel32	Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	Ltext0
	.long	Letext0-Ltext0
	.long	0
	.long	0
	.section	.debug_line,"dr"
Ldebug_line0:
	.section	.debug_str,"dr"
LASF2:
	.ascii "glyph_cnt\0"
LASF9:
	.ascii "bf_desc_font\0"
LASF7:
	.ascii "target_max\0"
LASF10:
	.ascii "fontname\0"
LASF8:
	.ascii "target_cnt\0"
LASF4:
	.ascii "dwidth_x\0"
LASF5:
	.ascii "dwidth_y\0"
LASF0:
	.ascii "_on_exit_args\0"
LASF3:
	.ascii "encoding\0"
LASF1:
	.ascii "is_verbose\0"
LASF6:
	.ascii "target_data\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_strtoul;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef
	.def	_tga_set_font;	.scl	2;	.type	32;	.endef
	.def	_tga_get_char_height;	.scl	2;	.type	32;	.endef
	.def	_tga_get_glyph_data;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	_tga_draw_string;	.scl	2;	.type	32;	.endef
	.def	_tga_get_char_width;	.scl	2;	.type	32;	.endef
	.def	_tga_draw_glyph;	.scl	2;	.type	32;	.endef
	.def	_bf_GetIndexByEncoding;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_bf_OpenFromFile;	.scl	2;	.type	32;	.endef
	.def	_bf_Log;	.scl	2;	.type	32;	.endef
	.def	_tga_init;	.scl	2;	.type	32;	.endef
	.def	_clock;	.scl	2;	.type	32;	.endef
	.def	_fd_init;	.scl	2;	.type	32;	.endef
	.def	_fd_set_font;	.scl	2;	.type	32;	.endef
	.def	_fd_draw_string;	.scl	2;	.type	32;	.endef
	.def	_tga_save;	.scl	2;	.type	32;	.endef
	.def	_bf_WriteUCGCByFilename;	.scl	2;	.type	32;	.endef
	.def	_bf_WriteU8G2CByFilename;	.scl	2;	.type	32;	.endef
	.def	_bf_Close;	.scl	2;	.type	32;	.endef
