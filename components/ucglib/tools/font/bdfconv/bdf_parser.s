	.file	"bdf_parser.c"
	.text
Ltext0:
	.def	_bf_curr;	.scl	3;	.type	32;	.endef
_bf_curr:
LFB12:
	.file 1 "bdf_parser.c"
	.loc 1 9 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 10 0
	movl	8(%ebp), %eax
	movl	1040(%eax), %eax
	cmpl	$1023, %eax
	jle	L2
	.loc 1 11 0
	movl	$0, %eax
	jmp	L3
L2:
	.loc 1 12 0
	movl	8(%ebp), %eax
	movl	1040(%eax), %eax
	movl	8(%ebp), %edx
	movzbl	16(%edx,%eax), %eax
	movsbl	%al, %eax
L3:
	.loc 1 13 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.def	_bf_next;	.scl	3;	.type	32;	.endef
_bf_next:
LFB13:
	.loc 1 16 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	.loc 1 17 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	testl	%eax, %eax
	je	L8
	.loc 1 19 0
	movl	8(%ebp), %eax
	movl	1040(%eax), %eax
	cmpl	$1023, %eax
	jg	L9
	.loc 1 21 0
	movl	8(%ebp), %eax
	movl	1040(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1040(%eax)
	jmp	L4
L8:
	.loc 1 18 0
	nop
	jmp	L4
L9:
	.loc 1 20 0
	nop
L4:
	.loc 1 22 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.def	_bf_skipspace;	.scl	3;	.type	32;	.endef
_bf_skipspace:
LFB14:
	.loc 1 25 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
L14:
	.loc 1 30 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	movl	%eax, -4(%ebp)
	.loc 1 31 0
	cmpl	$0, -4(%ebp)
	je	L15
	.loc 1 33 0
	cmpl	$32, -4(%ebp)
	jg	L16
	.loc 1 35 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 30 0
	jmp	L14
L15:
	.loc 1 32 0
	nop
	jmp	L10
L16:
	.loc 1 34 0
	nop
L10:
	.loc 1 37 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.def	_bf_get_identifier;	.scl	3;	.type	32;	.endef
_bf_get_identifier:
LFB15:
	.loc 1 40 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 43 0
	movl	$0, -4(%ebp)
	.loc 1 44 0
	movb	$0, _buf.3442
L21:
	.loc 1 47 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	movl	%eax, -8(%ebp)
	.loc 1 48 0
	cmpl	$32, -8(%ebp)
	jle	L23
	.loc 1 50 0
	cmpl	$1021, -4(%ebp)
	jg	L24
	.loc 1 52 0
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movl	-8(%ebp), %edx
	movb	%dl, _buf.3442(%eax)
	.loc 1 53 0
	movl	-4(%ebp), %eax
	addl	$_buf.3442, %eax
	movb	$0, (%eax)
	.loc 1 54 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 47 0
	jmp	L21
L23:
	.loc 1 49 0
	nop
	jmp	L19
L24:
	.loc 1 51 0
	nop
L19:
	.loc 1 56 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
	.loc 1 57 0
	movl	$_buf.3442, %eax
	.loc 1 58 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.def	_bf_get_string;	.scl	3;	.type	32;	.endef
_bf_get_string:
LFB16:
	.loc 1 61 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 63 0
	movl	$0, -4(%ebp)
	.loc 1 66 0
	movb	$0, _buf.3450
	.loc 1 68 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	cmpl	$34, %eax
	je	L26
	.loc 1 69 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_identifier
	jmp	L27
L26:
	.loc 1 71 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
L32:
	.loc 1 75 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	movl	%eax, -8(%ebp)
	.loc 1 76 0
	cmpl	$0, -8(%ebp)
	je	L34
	.loc 1 78 0
	cmpl	$34, -8(%ebp)
	je	L35
	.loc 1 80 0
	cmpl	$1021, -4(%ebp)
	jg	L36
	.loc 1 82 0
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movl	-8(%ebp), %edx
	movb	%dl, _buf.3450(%eax)
	.loc 1 83 0
	movl	-4(%ebp), %eax
	addl	$_buf.3450, %eax
	movb	$0, (%eax)
	.loc 1 84 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 75 0
	jmp	L32
L34:
	.loc 1 77 0
	nop
	jmp	L29
L35:
	.loc 1 79 0
	nop
	jmp	L29
L36:
	.loc 1 81 0
	nop
L29:
	.loc 1 86 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	cmpl	$34, %eax
	jne	L33
	.loc 1 87 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
L33:
	.loc 1 89 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
	.loc 1 90 0
	movl	$_buf.3450, %eax
L27:
	.loc 1 91 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.def	_bf_get_eol_string;	.scl	3;	.type	32;	.endef
_bf_get_eol_string:
LFB17:
	.loc 1 94 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 96 0
	movl	$0, -4(%ebp)
	.loc 1 99 0
	movb	$0, _buf.3458
	.loc 1 101 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	cmpl	$34, %eax
	jne	L38
	.loc 1 102 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_string
	jmp	L39
L38:
	.loc 1 103 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
L43:
	.loc 1 107 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	movl	%eax, -8(%ebp)
	.loc 1 108 0
	cmpl	$0, -8(%ebp)
	je	L44
	.loc 1 110 0
	cmpl	$10, -8(%ebp)
	je	L41
	.loc 1 110 0 is_stmt 0 discriminator 1
	cmpl	$13, -8(%ebp)
	je	L41
	.loc 1 112 0 is_stmt 1
	cmpl	$1021, -4(%ebp)
	jg	L45
	.loc 1 114 0
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movl	-8(%ebp), %edx
	movb	%dl, _buf.3458(%eax)
	.loc 1 115 0
	movl	-4(%ebp), %eax
	addl	$_buf.3458, %eax
	movb	$0, (%eax)
	.loc 1 116 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 107 0
	jmp	L43
L44:
	.loc 1 109 0
	nop
	jmp	L41
L45:
	.loc 1 113 0
	nop
L41:
	.loc 1 119 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
	.loc 1 120 0
	movl	$_buf.3458, %eax
L39:
	.loc 1 121 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.def	_bf_get_long;	.scl	3;	.type	32;	.endef
_bf_get_long:
LFB18:
	.loc 1 124 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 126 0
	movl	$0, -4(%ebp)
	.loc 1 127 0
	movl	$1, -8(%ebp)
	.loc 1 129 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	cmpl	$45, %eax
	jne	L47
	.loc 1 131 0
	movl	$-1, -8(%ebp)
	.loc 1 132 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 133 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
L47:
	.loc 1 138 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	movl	%eax, -12(%ebp)
	.loc 1 139 0
	cmpl	$47, -12(%ebp)
	jle	L52
	.loc 1 141 0
	cmpl	$57, -12(%ebp)
	jg	L53
	.loc 1 143 0
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -4(%ebp)
	.loc 1 144 0
	movl	-12(%ebp), %eax
	subl	$48, %eax
	addl	%eax, -4(%ebp)
	.loc 1 145 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 138 0
	jmp	L47
L52:
	.loc 1 140 0
	nop
	jmp	L49
L53:
	.loc 1 142 0
	nop
L49:
	.loc 1 147 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
	.loc 1 149 0
	movl	-4(%ebp), %eax
	imull	-8(%ebp), %eax
	.loc 1 150 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "Can not add glyph (memory error?)\0"
	.align 4
LC1:
	.ascii "Can not create bitmap (memory error?)\0"
	.text
	.def	_bf_add_glyph_to_list;	.scl	3;	.type	32;	.endef
_bf_add_glyph_to_list:
LFB19:
	.loc 1 182 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 184 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddGlyph
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1084(%eax)
	.loc 1 185 0
	movl	8(%ebp), %eax
	movl	1084(%eax), %eax
	testl	%eax, %eax
	jns	L55
	.loc 1 187 0
	movl	$LC0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Error
	.loc 1 188 0
	movl	$0, %eax
	jmp	L56
L55:
	.loc 1 191 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	1084(%eax), %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
	.loc 1 194 0
	movl	8(%ebp), %eax
	movl	1048(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 195 0
	movl	8(%ebp), %eax
	movl	1052(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 1 196 0
	movl	8(%ebp), %eax
	movl	1056(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 16(%eax)
	.loc 1 197 0
	movl	8(%ebp), %eax
	movl	1060(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 20(%eax)
	.loc 1 198 0
	movl	8(%ebp), %eax
	movl	1064(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 1 199 0
	movl	8(%ebp), %eax
	movl	1068(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 200 0
	movl	8(%ebp), %eax
	movl	1072(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 32(%eax)
	.loc 1 202 0
	movl	8(%ebp), %eax
	movl	1064(%eax), %edx
	movl	8(%ebp), %eax
	movl	1060(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_SetBitmapSize
	testl	%eax, %eax
	jne	L57
	.loc 1 204 0
	movl	$LC1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Error
	.loc 1 205 0
	movl	$0, %eax
	jmp	L56
L57:
	.loc 1 208 0
	movl	8(%ebp), %eax
	movl	1060(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 44(%eax)
	.loc 1 209 0
	movl	8(%ebp), %eax
	movl	1064(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 48(%eax)
	.loc 1 217 0
	movl	$1, %eax
L56:
	.loc 1 218 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.section .rdata,"dr"
LC2:
	.ascii "bf->glyph_list != NULL\0"
LC3:
	.ascii "bdf_parser.c\0"
	.text
	.def	_bf_set_pixel_by_halfbyte;	.scl	3;	.type	32;	.endef
_bf_set_pixel_by_halfbyte:
LFB20:
	.loc 1 221 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 225 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	jne	L59
	.loc 1 225 0 is_stmt 0 discriminator 1
	movl	$LC2, 12(%esp)
	movl	$___func__.3481, 8(%esp)
	movl	$225, 4(%esp)
	movl	$LC3, (%esp)
	call	___assert_func
L59:
	.loc 1 227 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	1084(%eax), %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 229 0
	movl	$0, -12(%ebp)
	jmp	L60
L62:
	.loc 1 231 0
	movl	12(%ebp), %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	L61
	.loc 1 233 0
	movl	8(%ebp), %eax
	movl	1080(%eax), %edx
	movl	8(%ebp), %eax
	movl	1076(%eax), %eax
	movl	$1, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_SetBitmapPixel
L61:
	.loc 1 235 0 discriminator 2
	sall	12(%ebp)
	.loc 1 236 0 discriminator 2
	movl	8(%ebp), %eax
	movl	1076(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1076(%eax)
	.loc 1 229 0 discriminator 2
	addl	$1, -12(%ebp)
L60:
	.loc 1 229 0 is_stmt 0 discriminator 1
	cmpl	$3, -12(%ebp)
	jle	L62
	.loc 1 238 0 is_stmt 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.def	_bf_set_pixel_by_hex_char;	.scl	3;	.type	32;	.endef
_bf_set_pixel_by_hex_char:
LFB21:
	.loc 1 241 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 242 0
	cmpl	$47, 12(%ebp)
	jle	L64
	.loc 1 242 0 is_stmt 0 discriminator 1
	cmpl	$57, 12(%ebp)
	jg	L64
	.loc 1 243 0 is_stmt 1
	movl	12(%ebp), %eax
	subl	$48, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_set_pixel_by_halfbyte
	jmp	L63
L64:
	.loc 1 244 0
	cmpl	$96, 12(%ebp)
	jle	L66
	.loc 1 244 0 is_stmt 0 discriminator 1
	cmpl	$102, 12(%ebp)
	jg	L66
	.loc 1 245 0 is_stmt 1
	movl	12(%ebp), %eax
	subl	$87, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_set_pixel_by_halfbyte
	jmp	L63
L66:
	.loc 1 246 0
	cmpl	$64, 12(%ebp)
	jle	L67
	.loc 1 246 0 is_stmt 0 discriminator 1
	cmpl	$70, 12(%ebp)
	jg	L67
	.loc 1 247 0 is_stmt 1
	movl	12(%ebp), %eax
	subl	$55, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_set_pixel_by_halfbyte
	jmp	L63
L67:
	.loc 1 248 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_set_pixel_by_halfbyte
L63:
	.loc 1 249 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.section .rdata,"dr"
LC4:
	.ascii "STARTFONT\0"
LC5:
	.ascii "FONT\0"
LC6:
	.ascii "SIZE\0"
LC7:
	.ascii "FONTBOUNDINGBOX\0"
LC8:
	.ascii "STARTPROPERTIES\0"
LC9:
	.ascii "FONTNAME_REGISTRY\0"
LC10:
	.ascii "FOUNDRY\0"
LC11:
	.ascii "FAMILY_NAME\0"
LC12:
	.ascii "WEIGHT_NAME\0"
LC13:
	.ascii "SLANT\0"
LC14:
	.ascii "SETWIDTH_NAME\0"
LC15:
	.ascii "ADD_STYLE_NAME\0"
LC16:
	.ascii "PIXEL_SIZE\0"
LC17:
	.ascii "POINT_SIZE\0"
LC18:
	.ascii "RESOLUTION_X\0"
LC19:
	.ascii "RESOLUTION_Y\0"
LC20:
	.ascii "SPACING\0"
LC21:
	.ascii "AVERAGE_WIDTH\0"
LC22:
	.ascii "CHARSET_REGISTRY\0"
LC23:
	.ascii "CHARSET_ENCODING\0"
LC24:
	.ascii "DESTINATION\0"
LC25:
	.ascii "COPYRIGHT\0"
LC26:
	.ascii "_XMBDFED_INFO\0"
LC27:
	.ascii "CAP_HEIGHT\0"
LC28:
	.ascii "X_HEIGHT\0"
LC29:
	.ascii "WEIGHT\0"
LC30:
	.ascii "QUAD_WIDTH\0"
LC31:
	.ascii "DEFAULT_CHAR\0"
LC32:
	.ascii "FONT_DESCENT\0"
LC33:
	.ascii "FONT_ASCENT\0"
LC34:
	.ascii "ENDPROPERTIES\0"
LC35:
	.ascii "CHARS\0"
LC36:
	.ascii "STARTCHAR\0"
LC37:
	.ascii "ENCODING\0"
LC38:
	.ascii "SWIDTH\0"
LC39:
	.ascii "DWIDTH\0"
LC40:
	.ascii "BBX\0"
LC41:
	.ascii "BITMAP\0"
LC42:
	.ascii "ENDCHAR\0"
LC43:
	.ascii "Unexpected ENDCHAR found\0"
	.text
	.def	_bf_parse_line;	.scl	3;	.type	32;	.endef
_bf_parse_line:
LFB22:
	.loc 1 252 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 255 0
	movl	8(%ebp), %eax
	movl	$0, 1040(%eax)
	.loc 1 256 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
	.loc 1 258 0
	movl	8(%ebp), %eax
	movl	1044(%eax), %eax
	testl	%eax, %eax
	jne	L69
	.loc 1 261 0
	movl	8(%ebp), %eax
	movl	$0, 1080(%eax)
	.loc 1 262 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_string
	movl	%eax, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcpy
	.loc 1 264 0
	movl	$_cmd.3492, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L70
	.loc 1 266 0
	movl	$1, %eax
	jmp	L71
L70:
	.loc 1 268 0
	movl	$LC4, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 271 0
	movl	$LC5, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L73
	.loc 1 273 0
	movl	8(%ebp), %eax
	movl	1092(%eax), %eax
	testl	%eax, %eax
	je	L74
	.loc 1 274 0
	movl	8(%ebp), %eax
	movl	1092(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L74:
	.loc 1 275 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_eol_string
	movl	%eax, (%esp)
	call	_strdup
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1092(%eax)
	jmp	L72
L73:
	.loc 1 277 0
	movl	$LC6, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 280 0
	movl	$LC7, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 283 0
	movl	$LC8, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 286 0
	movl	$LC9, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 289 0
	movl	$LC10, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 292 0
	movl	$LC11, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 295 0
	movl	$LC12, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 298 0
	movl	$LC13, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 301 0
	movl	$LC14, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 304 0
	movl	$LC15, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 307 0
	movl	$LC16, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 310 0
	movl	$LC17, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 313 0
	movl	$LC18, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 316 0
	movl	$LC19, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 319 0
	movl	$LC20, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 322 0
	movl	$LC21, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 325 0
	movl	$LC22, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 328 0
	movl	$LC23, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 331 0
	movl	$LC24, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 334 0
	movl	$LC25, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L75
	.loc 1 336 0
	movl	8(%ebp), %eax
	movl	1096(%eax), %eax
	testl	%eax, %eax
	je	L76
	.loc 1 337 0
	movl	8(%ebp), %eax
	movl	1096(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L76:
	.loc 1 338 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_eol_string
	movl	%eax, (%esp)
	call	_strdup
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1096(%eax)
	jmp	L72
L75:
	.loc 1 340 0
	movl	$LC26, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 343 0
	movl	$LC27, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 346 0
	movl	$LC28, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 349 0
	movl	$LC29, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 352 0
	movl	$LC30, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 355 0
	movl	$LC31, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 358 0
	movl	$LC32, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 361 0
	movl	$LC33, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 364 0
	movl	$LC34, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 367 0
	movl	$LC35, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 370 0
	movl	$LC36, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 373 0
	movl	$LC37, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L77
	.loc 1 375 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1048(%eax)
	jmp	L72
L77:
	.loc 1 378 0
	movl	$LC38, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	je	L72
	.loc 1 381 0
	movl	$LC39, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L78
	.loc 1 383 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1052(%eax)
	.loc 1 384 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1056(%eax)
	jmp	L72
L78:
	.loc 1 387 0
	movl	$LC40, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L79
	.loc 1 389 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1060(%eax)
	.loc 1 390 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1064(%eax)
	.loc 1 391 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1068(%eax)
	.loc 1 392 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_long
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1072(%eax)
	jmp	L72
L79:
	.loc 1 394 0
	movl	$LC41, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L80
	.loc 1 396 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_add_glyph_to_list
	testl	%eax, %eax
	jne	L81
	.loc 1 397 0
	movl	$0, %eax
	jmp	L71
L81:
	.loc 1 398 0
	movl	8(%ebp), %eax
	movl	$1, 1044(%eax)
	jmp	L72
L80:
	.loc 1 400 0
	movl	$LC42, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L72
	.loc 1 402 0
	movl	$LC43, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Error
	.loc 1 403 0
	movl	$0, %eax
	jmp	L71
L69:
LBB2:
	.loc 1 410 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_get_string
	movl	%eax, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcpy
	.loc 1 411 0
	movl	$LC42, 4(%esp)
	movl	$_cmd.3492, (%esp)
	call	_strcmp
	testl	%eax, %eax
	jne	L82
	.loc 1 413 0
	movl	8(%ebp), %eax
	movl	$0, 1044(%eax)
	jmp	L72
L82:
	.loc 1 418 0
	movl	8(%ebp), %eax
	movl	$0, 1040(%eax)
	.loc 1 419 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_skipspace
	.loc 1 422 0
	movl	8(%ebp), %eax
	movl	$0, 1076(%eax)
L85:
	.loc 1 427 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_curr
	movl	%eax, -12(%ebp)
	.loc 1 428 0
	cmpl	$47, -12(%ebp)
	jle	L87
	.loc 1 430 0
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_set_pixel_by_hex_char
	.loc 1 431 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_next
	.loc 1 427 0
	jmp	L85
L87:
	.loc 1 429 0
	nop
	.loc 1 434 0
	movl	8(%ebp), %eax
	movl	1080(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1080(%eax)
L72:
LBE2:
	.loc 1 437 0
	movl	$1, %eax
L71:
	.loc 1 438 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.section .rdata,"dr"
LC44:
	.ascii "perse error in line %ld\0"
	.text
	.def	_bf_parse_file;	.scl	3;	.type	32;	.endef
_bf_parse_file:
LFB23:
	.loc 1 441 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 442 0
	movl	$0, -12(%ebp)
	.loc 1 443 0
	movl	8(%ebp), %eax
	movl	$0, 1044(%eax)
L93:
	.loc 1 446 0
	addl	$1, -12(%ebp)
	.loc 1 447 0
	movl	8(%ebp), %eax
	movl	1088(%eax), %eax
	movl	8(%ebp), %edx
	addl	$16, %edx
	movl	%eax, 8(%esp)
	movl	$1024, 4(%esp)
	movl	%edx, (%esp)
	call	_fgets
	testl	%eax, %eax
	je	L95
	.loc 1 449 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_parse_line
	testl	%eax, %eax
	jne	L93
	.loc 1 451 0
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC44, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Error
	.loc 1 452 0
	movl	$0, %eax
	jmp	L92
L95:
	.loc 1 448 0
	nop
	.loc 1 455 0
	movl	$1, %eax
L92:
	.loc 1 456 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE23:
	.section .rdata,"dr"
LC45:
	.ascii "r\0"
LC46:
	.ascii "Can not open bdf file '%s'\0"
	.align 4
LC47:
	.ascii "Parse File %s: %d glyph(s) found\0"
	.text
	.globl	_bf_ParseFile
	.def	_bf_ParseFile;	.scl	2;	.type	32;	.endef
_bf_ParseFile:
LFB24:
	.loc 1 459 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 461 0
	movl	$LC45, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fopen
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1088(%eax)
	.loc 1 462 0
	movl	8(%ebp), %eax
	movl	1088(%eax), %eax
	testl	%eax, %eax
	jne	L97
	.loc 1 464 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC46, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Error
	.loc 1 465 0
	movl	$0, %eax
	jmp	L98
L97:
	.loc 1 467 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_parse_file
	movl	%eax, -12(%ebp)
	.loc 1 468 0
	movl	8(%ebp), %eax
	movl	1088(%eax), %eax
	movl	%eax, (%esp)
	call	_fclose
	.loc 1 469 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC47, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 470 0
	movl	-12(%ebp), %eax
L98:
	.loc 1 471 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
.lcomm _buf.3442,1024,32
.lcomm _buf.3450,1024,32
.lcomm _buf.3458,1024,32
	.section .rdata,"dr"
	.align 4
___func__.3481:
	.ascii "bf_set_pixel_by_halfbyte\0"
.lcomm _cmd.3492,1024,32
	.text
Letext0:
	.file 2 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 3 "/usr/include/machine/_default_types.h"
	.file 4 "/usr/include/sys/lock.h"
	.file 5 "/usr/include/sys/_types.h"
	.file 6 "/usr/include/sys/reent.h"
	.file 7 "/usr/include/stdlib.h"
	.file 8 "/usr/include/sys/_stdint.h"
	.file 9 "/usr/include/stdio.h"
	.file 10 "bdf_glyph.h"
	.file 11 "bdf_font.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x151a
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_parser.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.ascii "size_t\0"
	.byte	0x2
	.byte	0xd8
	.long	0x9d
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.uleb128 0x3
	.byte	0xc
	.byte	0x4
	.ascii "long double\0"
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0x2
	.ascii "__uint8_t\0"
	.byte	0x3
	.byte	0x2b
	.long	0x10a
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "long unsigned int\0"
	.uleb128 0x2
	.ascii "_LOCK_T\0"
	.byte	0x4
	.byte	0xc
	.long	0x166
	.uleb128 0x4
	.byte	0x4
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii "long int\0"
	.uleb128 0x2
	.ascii "_off64_t\0"
	.byte	0x5
	.byte	0x5e
	.long	0xca
	.uleb128 0x2
	.ascii "_fpos_t\0"
	.byte	0x5
	.byte	0x72
	.long	0x168
	.uleb128 0x2
	.ascii "_fpos64_t\0"
	.byte	0x5
	.byte	0x78
	.long	0x174
	.uleb128 0x2
	.ascii "_ssize_t\0"
	.byte	0x5
	.byte	0x91
	.long	0xc3
	.uleb128 0x5
	.ascii "wint_t\0"
	.byte	0x2
	.word	0x165
	.long	0x9d
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0xa6
	.long	0x1e7
	.uleb128 0x7
	.ascii "__wch\0"
	.byte	0x5
	.byte	0xa8
	.long	0x1b4
	.uleb128 0x7
	.ascii "__wchb\0"
	.byte	0x5
	.byte	0xa9
	.long	0x1e7
	.byte	0
	.uleb128 0x8
	.long	0x10a
	.long	0x1f7
	.uleb128 0x9
	.long	0x1f7
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "sizetype\0"
	.uleb128 0xa
	.byte	0x8
	.byte	0x5
	.byte	0xa3
	.long	0x22c
	.uleb128 0xb
	.ascii "__count\0"
	.byte	0x5
	.byte	0xa5
	.long	0xc3
	.byte	0
	.uleb128 0xb
	.ascii "__value\0"
	.byte	0x5
	.byte	0xaa
	.long	0x1c3
	.byte	0x4
	.byte	0
	.uleb128 0x2
	.ascii "_mbstate_t\0"
	.byte	0x5
	.byte	0xab
	.long	0x203
	.uleb128 0x2
	.ascii "_flock_t\0"
	.byte	0x5
	.byte	0xaf
	.long	0x157
	.uleb128 0xc
	.byte	0x4
	.long	0x254
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0xd
	.long	0x254
	.uleb128 0x2
	.ascii "__ULong\0"
	.byte	0x6
	.byte	0x16
	.long	0x142
	.uleb128 0xe
	.ascii "_Bigint\0"
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.long	0x2d0
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x31
	.long	0x2d0
	.byte	0
	.uleb128 0xb
	.ascii "_k\0"
	.byte	0x6
	.byte	0x32
	.long	0xc3
	.byte	0x4
	.uleb128 0xb
	.ascii "_maxwds\0"
	.byte	0x6
	.byte	0x32
	.long	0xc3
	.byte	0x8
	.uleb128 0xb
	.ascii "_sign\0"
	.byte	0x6
	.byte	0x32
	.long	0xc3
	.byte	0xc
	.uleb128 0xb
	.ascii "_wds\0"
	.byte	0x6
	.byte	0x32
	.long	0xc3
	.byte	0x10
	.uleb128 0xb
	.ascii "_x\0"
	.byte	0x6
	.byte	0x33
	.long	0x2d6
	.byte	0x14
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x270
	.uleb128 0x8
	.long	0x261
	.long	0x2e6
	.uleb128 0x9
	.long	0x1f7
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__tm\0"
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.long	0x394
	.uleb128 0xb
	.ascii "__tm_sec\0"
	.byte	0x6
	.byte	0x39
	.long	0xc3
	.byte	0
	.uleb128 0xb
	.ascii "__tm_min\0"
	.byte	0x6
	.byte	0x3a
	.long	0xc3
	.byte	0x4
	.uleb128 0xb
	.ascii "__tm_hour\0"
	.byte	0x6
	.byte	0x3b
	.long	0xc3
	.byte	0x8
	.uleb128 0xb
	.ascii "__tm_mday\0"
	.byte	0x6
	.byte	0x3c
	.long	0xc3
	.byte	0xc
	.uleb128 0xb
	.ascii "__tm_mon\0"
	.byte	0x6
	.byte	0x3d
	.long	0xc3
	.byte	0x10
	.uleb128 0xb
	.ascii "__tm_year\0"
	.byte	0x6
	.byte	0x3e
	.long	0xc3
	.byte	0x14
	.uleb128 0xb
	.ascii "__tm_wday\0"
	.byte	0x6
	.byte	0x3f
	.long	0xc3
	.byte	0x18
	.uleb128 0xb
	.ascii "__tm_yday\0"
	.byte	0x6
	.byte	0x40
	.long	0xc3
	.byte	0x1c
	.uleb128 0xb
	.ascii "__tm_isdst\0"
	.byte	0x6
	.byte	0x41
	.long	0xc3
	.byte	0x20
	.byte	0
	.uleb128 0xf
	.secrel32	LASF0
	.word	0x108
	.byte	0x6
	.byte	0x4a
	.long	0x3e9
	.uleb128 0xb
	.ascii "_fnargs\0"
	.byte	0x6
	.byte	0x4b
	.long	0x3e9
	.byte	0
	.uleb128 0xb
	.ascii "_dso_handle\0"
	.byte	0x6
	.byte	0x4c
	.long	0x3e9
	.byte	0x80
	.uleb128 0x10
	.ascii "_fntypes\0"
	.byte	0x6
	.byte	0x4e
	.long	0x261
	.word	0x100
	.uleb128 0x10
	.ascii "_is_cxa\0"
	.byte	0x6
	.byte	0x51
	.long	0x261
	.word	0x104
	.byte	0
	.uleb128 0x8
	.long	0x166
	.long	0x3f9
	.uleb128 0x9
	.long	0x1f7
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.ascii "_atexit\0"
	.word	0x190
	.byte	0x6
	.byte	0x5d
	.long	0x43f
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x5e
	.long	0x43f
	.byte	0
	.uleb128 0xb
	.ascii "_ind\0"
	.byte	0x6
	.byte	0x5f
	.long	0xc3
	.byte	0x4
	.uleb128 0xb
	.ascii "_fns\0"
	.byte	0x6
	.byte	0x61
	.long	0x445
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF0
	.byte	0x6
	.byte	0x62
	.long	0x394
	.byte	0x88
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x3f9
	.uleb128 0x8
	.long	0x455
	.long	0x455
	.uleb128 0x9
	.long	0x1f7
	.byte	0x1f
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x45b
	.uleb128 0x13
	.uleb128 0xe
	.ascii "__sbuf\0"
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.long	0x488
	.uleb128 0xb
	.ascii "_base\0"
	.byte	0x6
	.byte	0x76
	.long	0x488
	.byte	0
	.uleb128 0xb
	.ascii "_size\0"
	.byte	0x6
	.byte	0x77
	.long	0xc3
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x10a
	.uleb128 0x14
	.long	0x1a4
	.long	0x4ac
	.uleb128 0x15
	.long	0x4ac
	.uleb128 0x15
	.long	0x166
	.uleb128 0x15
	.long	0x24e
	.uleb128 0x15
	.long	0x8f
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x4b7
	.uleb128 0xd
	.long	0x4ac
	.uleb128 0x16
	.ascii "_reent\0"
	.word	0x440
	.byte	0x6
	.word	0x239
	.long	0x656
	.uleb128 0x17
	.ascii "_errno\0"
	.byte	0x6
	.word	0x23b
	.long	0xc3
	.byte	0
	.uleb128 0x17
	.ascii "_stdin\0"
	.byte	0x6
	.word	0x240
	.long	0x8db
	.byte	0x4
	.uleb128 0x17
	.ascii "_stdout\0"
	.byte	0x6
	.word	0x240
	.long	0x8db
	.byte	0x8
	.uleb128 0x17
	.ascii "_stderr\0"
	.byte	0x6
	.word	0x240
	.long	0x8db
	.byte	0xc
	.uleb128 0x17
	.ascii "_inc\0"
	.byte	0x6
	.word	0x242
	.long	0xc3
	.byte	0x10
	.uleb128 0x17
	.ascii "_emergency\0"
	.byte	0x6
	.word	0x243
	.long	0xb81
	.byte	0x14
	.uleb128 0x17
	.ascii "_unspecified_locale_info\0"
	.byte	0x6
	.word	0x246
	.long	0xc3
	.byte	0x30
	.uleb128 0x17
	.ascii "_locale\0"
	.byte	0x6
	.word	0x247
	.long	0xb9d
	.byte	0x34
	.uleb128 0x17
	.ascii "__sdidinit\0"
	.byte	0x6
	.word	0x249
	.long	0xc3
	.byte	0x38
	.uleb128 0x17
	.ascii "__cleanup\0"
	.byte	0x6
	.word	0x24b
	.long	0xbae
	.byte	0x3c
	.uleb128 0x17
	.ascii "_result\0"
	.byte	0x6
	.word	0x24e
	.long	0x2d0
	.byte	0x40
	.uleb128 0x17
	.ascii "_result_k\0"
	.byte	0x6
	.word	0x24f
	.long	0xc3
	.byte	0x44
	.uleb128 0x17
	.ascii "_p5s\0"
	.byte	0x6
	.word	0x250
	.long	0x2d0
	.byte	0x48
	.uleb128 0x17
	.ascii "_freelist\0"
	.byte	0x6
	.word	0x251
	.long	0xbb4
	.byte	0x4c
	.uleb128 0x17
	.ascii "_cvtlen\0"
	.byte	0x6
	.word	0x254
	.long	0xc3
	.byte	0x50
	.uleb128 0x17
	.ascii "_cvtbuf\0"
	.byte	0x6
	.word	0x255
	.long	0x24e
	.byte	0x54
	.uleb128 0x17
	.ascii "_new\0"
	.byte	0x6
	.word	0x278
	.long	0xb58
	.byte	0x58
	.uleb128 0x18
	.ascii "_atexit\0"
	.byte	0x6
	.word	0x27c
	.long	0x43f
	.word	0x148
	.uleb128 0x18
	.ascii "_atexit0\0"
	.byte	0x6
	.word	0x27d
	.long	0x3f9
	.word	0x14c
	.uleb128 0x18
	.ascii "_sig_func\0"
	.byte	0x6
	.word	0x281
	.long	0xbc5
	.word	0x2dc
	.uleb128 0x18
	.ascii "__sglue\0"
	.byte	0x6
	.word	0x286
	.long	0x897
	.word	0x2e0
	.uleb128 0x18
	.ascii "__sf\0"
	.byte	0x6
	.word	0x288
	.long	0xbd1
	.word	0x2f0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x48e
	.uleb128 0x14
	.long	0x1a4
	.long	0x67a
	.uleb128 0x15
	.long	0x4ac
	.uleb128 0x15
	.long	0x166
	.uleb128 0x15
	.long	0x67a
	.uleb128 0x15
	.long	0x8f
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x25c
	.uleb128 0xc
	.byte	0x4
	.long	0x65c
	.uleb128 0x14
	.long	0x184
	.long	0x6a4
	.uleb128 0x15
	.long	0x4ac
	.uleb128 0x15
	.long	0x166
	.uleb128 0x15
	.long	0x184
	.uleb128 0x15
	.long	0xc3
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x686
	.uleb128 0x14
	.long	0xc3
	.long	0x6be
	.uleb128 0x15
	.long	0x4ac
	.uleb128 0x15
	.long	0x166
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x6aa
	.uleb128 0x8
	.long	0x10a
	.long	0x6d4
	.uleb128 0x9
	.long	0x1f7
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.long	0x10a
	.long	0x6e4
	.uleb128 0x9
	.long	0x1f7
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__sFILE64\0"
	.byte	0x70
	.byte	0x6
	.byte	0xef
	.long	0x864
	.uleb128 0xb
	.ascii "_p\0"
	.byte	0x6
	.byte	0xf0
	.long	0x488
	.byte	0
	.uleb128 0xb
	.ascii "_r\0"
	.byte	0x6
	.byte	0xf1
	.long	0xc3
	.byte	0x4
	.uleb128 0xb
	.ascii "_w\0"
	.byte	0x6
	.byte	0xf2
	.long	0xc3
	.byte	0x8
	.uleb128 0xb
	.ascii "_flags\0"
	.byte	0x6
	.byte	0xf3
	.long	0x11b
	.byte	0xc
	.uleb128 0xb
	.ascii "_file\0"
	.byte	0x6
	.byte	0xf4
	.long	0x11b
	.byte	0xe
	.uleb128 0xb
	.ascii "_bf\0"
	.byte	0x6
	.byte	0xf5
	.long	0x45c
	.byte	0x10
	.uleb128 0xb
	.ascii "_lbfsize\0"
	.byte	0x6
	.byte	0xf6
	.long	0xc3
	.byte	0x18
	.uleb128 0xb
	.ascii "_data\0"
	.byte	0x6
	.byte	0xf8
	.long	0x4ac
	.byte	0x1c
	.uleb128 0xb
	.ascii "_cookie\0"
	.byte	0x6
	.byte	0xfb
	.long	0x166
	.byte	0x20
	.uleb128 0xb
	.ascii "_read\0"
	.byte	0x6
	.byte	0xfd
	.long	0x656
	.byte	0x24
	.uleb128 0xb
	.ascii "_write\0"
	.byte	0x6
	.byte	0xff
	.long	0x680
	.byte	0x28
	.uleb128 0x17
	.ascii "_seek\0"
	.byte	0x6
	.word	0x102
	.long	0x6a4
	.byte	0x2c
	.uleb128 0x17
	.ascii "_close\0"
	.byte	0x6
	.word	0x103
	.long	0x6be
	.byte	0x30
	.uleb128 0x17
	.ascii "_ub\0"
	.byte	0x6
	.word	0x106
	.long	0x45c
	.byte	0x34
	.uleb128 0x17
	.ascii "_up\0"
	.byte	0x6
	.word	0x107
	.long	0x488
	.byte	0x3c
	.uleb128 0x17
	.ascii "_ur\0"
	.byte	0x6
	.word	0x108
	.long	0xc3
	.byte	0x40
	.uleb128 0x17
	.ascii "_ubuf\0"
	.byte	0x6
	.word	0x10b
	.long	0x6c4
	.byte	0x44
	.uleb128 0x17
	.ascii "_nbuf\0"
	.byte	0x6
	.word	0x10c
	.long	0x6d4
	.byte	0x47
	.uleb128 0x17
	.ascii "_lb\0"
	.byte	0x6
	.word	0x10f
	.long	0x45c
	.byte	0x48
	.uleb128 0x17
	.ascii "_blksize\0"
	.byte	0x6
	.word	0x112
	.long	0xc3
	.byte	0x50
	.uleb128 0x17
	.ascii "_flags2\0"
	.byte	0x6
	.word	0x113
	.long	0xc3
	.byte	0x54
	.uleb128 0x17
	.ascii "_offset\0"
	.byte	0x6
	.word	0x115
	.long	0x174
	.byte	0x58
	.uleb128 0x17
	.ascii "_seek64\0"
	.byte	0x6
	.word	0x116
	.long	0x882
	.byte	0x60
	.uleb128 0x17
	.ascii "_lock\0"
	.byte	0x6
	.word	0x119
	.long	0x23e
	.byte	0x64
	.uleb128 0x17
	.ascii "_mbstate\0"
	.byte	0x6
	.word	0x11b
	.long	0x22c
	.byte	0x68
	.byte	0
	.uleb128 0x14
	.long	0x193
	.long	0x882
	.uleb128 0x15
	.long	0x4ac
	.uleb128 0x15
	.long	0x166
	.uleb128 0x15
	.long	0x193
	.uleb128 0x15
	.long	0xc3
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x864
	.uleb128 0x5
	.ascii "__FILE\0"
	.byte	0x6
	.word	0x11d
	.long	0x6e4
	.uleb128 0x19
	.ascii "_glue\0"
	.byte	0xc
	.byte	0x6
	.word	0x123
	.long	0x8d5
	.uleb128 0x17
	.ascii "_next\0"
	.byte	0x6
	.word	0x125
	.long	0x8d5
	.byte	0
	.uleb128 0x17
	.ascii "_niobs\0"
	.byte	0x6
	.word	0x126
	.long	0xc3
	.byte	0x4
	.uleb128 0x17
	.ascii "_iobs\0"
	.byte	0x6
	.word	0x127
	.long	0x8db
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x897
	.uleb128 0xc
	.byte	0x4
	.long	0x888
	.uleb128 0x19
	.ascii "_rand48\0"
	.byte	0xe
	.byte	0x6
	.word	0x13f
	.long	0x91f
	.uleb128 0x17
	.ascii "_seed\0"
	.byte	0x6
	.word	0x140
	.long	0x91f
	.byte	0
	.uleb128 0x17
	.ascii "_mult\0"
	.byte	0x6
	.word	0x141
	.long	0x91f
	.byte	0x6
	.uleb128 0x17
	.ascii "_add\0"
	.byte	0x6
	.word	0x142
	.long	0xad
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.long	0xad
	.long	0x92f
	.uleb128 0x9
	.long	0x1f7
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.word	0x259
	.long	0xadc
	.uleb128 0x17
	.ascii "_unused_rand\0"
	.byte	0x6
	.word	0x25b
	.long	0x9d
	.byte	0
	.uleb128 0x17
	.ascii "_strtok_last\0"
	.byte	0x6
	.word	0x25c
	.long	0x24e
	.byte	0x4
	.uleb128 0x17
	.ascii "_asctime_buf\0"
	.byte	0x6
	.word	0x25d
	.long	0xadc
	.byte	0x8
	.uleb128 0x17
	.ascii "_localtime_buf\0"
	.byte	0x6
	.word	0x25e
	.long	0x2e6
	.byte	0x24
	.uleb128 0x17
	.ascii "_gamma_signgam\0"
	.byte	0x6
	.word	0x25f
	.long	0xc3
	.byte	0x48
	.uleb128 0x17
	.ascii "_rand_next\0"
	.byte	0x6
	.word	0x260
	.long	0x128
	.byte	0x50
	.uleb128 0x17
	.ascii "_r48\0"
	.byte	0x6
	.word	0x261
	.long	0x8e1
	.byte	0x58
	.uleb128 0x17
	.ascii "_mblen_state\0"
	.byte	0x6
	.word	0x262
	.long	0x22c
	.byte	0x68
	.uleb128 0x17
	.ascii "_mbtowc_state\0"
	.byte	0x6
	.word	0x263
	.long	0x22c
	.byte	0x70
	.uleb128 0x17
	.ascii "_wctomb_state\0"
	.byte	0x6
	.word	0x264
	.long	0x22c
	.byte	0x78
	.uleb128 0x17
	.ascii "_l64a_buf\0"
	.byte	0x6
	.word	0x265
	.long	0xaec
	.byte	0x80
	.uleb128 0x17
	.ascii "_signal_buf\0"
	.byte	0x6
	.word	0x266
	.long	0xafc
	.byte	0x88
	.uleb128 0x17
	.ascii "_getdate_err\0"
	.byte	0x6
	.word	0x267
	.long	0xc3
	.byte	0xa0
	.uleb128 0x17
	.ascii "_mbrlen_state\0"
	.byte	0x6
	.word	0x268
	.long	0x22c
	.byte	0xa4
	.uleb128 0x17
	.ascii "_mbrtowc_state\0"
	.byte	0x6
	.word	0x269
	.long	0x22c
	.byte	0xac
	.uleb128 0x17
	.ascii "_mbsrtowcs_state\0"
	.byte	0x6
	.word	0x26a
	.long	0x22c
	.byte	0xb4
	.uleb128 0x17
	.ascii "_wcrtomb_state\0"
	.byte	0x6
	.word	0x26b
	.long	0x22c
	.byte	0xbc
	.uleb128 0x17
	.ascii "_wcsrtombs_state\0"
	.byte	0x6
	.word	0x26c
	.long	0x22c
	.byte	0xc4
	.uleb128 0x17
	.ascii "_h_errno\0"
	.byte	0x6
	.word	0x26d
	.long	0xc3
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.long	0x254
	.long	0xaec
	.uleb128 0x9
	.long	0x1f7
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.long	0x254
	.long	0xafc
	.uleb128 0x9
	.long	0x1f7
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.long	0x254
	.long	0xb0c
	.uleb128 0x9
	.long	0x1f7
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.word	0x272
	.long	0xb38
	.uleb128 0x17
	.ascii "_nextf\0"
	.byte	0x6
	.word	0x275
	.long	0xb38
	.byte	0
	.uleb128 0x17
	.ascii "_nmalloc\0"
	.byte	0x6
	.word	0x276
	.long	0xb48
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.long	0x488
	.long	0xb48
	.uleb128 0x9
	.long	0x1f7
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.long	0x9d
	.long	0xb58
	.uleb128 0x9
	.long	0x1f7
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.word	0x257
	.long	0xb81
	.uleb128 0x1c
	.ascii "_reent\0"
	.byte	0x6
	.word	0x26e
	.long	0x92f
	.uleb128 0x1c
	.ascii "_unused\0"
	.byte	0x6
	.word	0x277
	.long	0xb0c
	.byte	0
	.uleb128 0x8
	.long	0x254
	.long	0xb91
	.uleb128 0x9
	.long	0x1f7
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.ascii "__locale_t\0"
	.uleb128 0xc
	.byte	0x4
	.long	0xb91
	.uleb128 0x1e
	.long	0xbae
	.uleb128 0x15
	.long	0x4ac
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xba3
	.uleb128 0xc
	.byte	0x4
	.long	0x2d0
	.uleb128 0x1e
	.long	0xbc5
	.uleb128 0x15
	.long	0xc3
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xbcb
	.uleb128 0xc
	.byte	0x4
	.long	0xbba
	.uleb128 0x8
	.long	0x888
	.long	0xbe1
	.uleb128 0x9
	.long	0x1f7
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.ascii "_impure_ptr\0"
	.byte	0x6
	.word	0x307
	.long	0x4ac
	.uleb128 0x1f
	.ascii "_global_impure_ptr\0"
	.byte	0x6
	.word	0x308
	.long	0x4b2
	.uleb128 0x20
	.ascii "suboptarg\0"
	.byte	0x7
	.byte	0x63
	.long	0x24e
	.uleb128 0x2
	.ascii "uint8_t\0"
	.byte	0x8
	.byte	0x18
	.long	0xf9
	.uleb128 0x2
	.ascii "FILE\0"
	.byte	0x9
	.byte	0x42
	.long	0x888
	.uleb128 0x2
	.ascii "bf_t\0"
	.byte	0xa
	.byte	0x9
	.long	0xc48
	.uleb128 0x11
	.ascii "_bdf_font_struct\0"
	.word	0x4a4
	.byte	0xb
	.byte	0x10
	.long	0xf1c
	.uleb128 0xb
	.ascii "is_verbose\0"
	.byte	0xb
	.byte	0x12
	.long	0xc3
	.byte	0
	.uleb128 0xb
	.ascii "glyph_list\0"
	.byte	0xb
	.byte	0x14
	.long	0x1101
	.byte	0x4
	.uleb128 0xb
	.ascii "glyph_cnt\0"
	.byte	0xb
	.byte	0x15
	.long	0xc3
	.byte	0x8
	.uleb128 0xb
	.ascii "glyph_max\0"
	.byte	0xb
	.byte	0x16
	.long	0xc3
	.byte	0xc
	.uleb128 0xb
	.ascii "line_buf\0"
	.byte	0xb
	.byte	0x19
	.long	0x110d
	.byte	0x10
	.uleb128 0x10
	.ascii "line_pos\0"
	.byte	0xb
	.byte	0x1a
	.long	0xc3
	.word	0x410
	.uleb128 0x10
	.ascii "is_bitmap_parsing\0"
	.byte	0xb
	.byte	0x1b
	.long	0xc3
	.word	0x414
	.uleb128 0x21
	.secrel32	LASF1
	.byte	0xb
	.byte	0x1d
	.long	0x168
	.word	0x418
	.uleb128 0x21
	.secrel32	LASF2
	.byte	0xb
	.byte	0x1f
	.long	0x168
	.word	0x41c
	.uleb128 0x21
	.secrel32	LASF3
	.byte	0xb
	.byte	0x20
	.long	0x168
	.word	0x420
	.uleb128 0x10
	.ascii "bbx_w\0"
	.byte	0xb
	.byte	0x22
	.long	0x168
	.word	0x424
	.uleb128 0x10
	.ascii "bbx_h\0"
	.byte	0xb
	.byte	0x23
	.long	0x168
	.word	0x428
	.uleb128 0x10
	.ascii "bbx_x\0"
	.byte	0xb
	.byte	0x24
	.long	0x168
	.word	0x42c
	.uleb128 0x10
	.ascii "bbx_y\0"
	.byte	0xb
	.byte	0x25
	.long	0x168
	.word	0x430
	.uleb128 0x10
	.ascii "bitmap_x\0"
	.byte	0xb
	.byte	0x27
	.long	0xc3
	.word	0x434
	.uleb128 0x10
	.ascii "bitmap_y\0"
	.byte	0xb
	.byte	0x28
	.long	0xc3
	.word	0x438
	.uleb128 0x10
	.ascii "glyph_pos\0"
	.byte	0xb
	.byte	0x29
	.long	0xc3
	.word	0x43c
	.uleb128 0x10
	.ascii "fp\0"
	.byte	0xb
	.byte	0x2a
	.long	0x111e
	.word	0x440
	.uleb128 0x10
	.ascii "str_font\0"
	.byte	0xb
	.byte	0x2c
	.long	0x24e
	.word	0x444
	.uleb128 0x10
	.ascii "str_copyright\0"
	.byte	0xb
	.byte	0x2d
	.long	0x24e
	.word	0x448
	.uleb128 0x10
	.ascii "selected_glyphs\0"
	.byte	0xb
	.byte	0x2f
	.long	0x168
	.word	0x44c
	.uleb128 0x10
	.ascii "bbx_mode\0"
	.byte	0xb
	.byte	0x31
	.long	0xc3
	.word	0x450
	.uleb128 0x10
	.ascii "max\0"
	.byte	0xb
	.byte	0x33
	.long	0xf59
	.word	0x454
	.uleb128 0x10
	.ascii "enc_w\0"
	.byte	0xb
	.byte	0x36
	.long	0x168
	.word	0x464
	.uleb128 0x10
	.ascii "enc_h\0"
	.byte	0xb
	.byte	0x37
	.long	0x168
	.word	0x468
	.uleb128 0x10
	.ascii "enc_x\0"
	.byte	0xb
	.byte	0x38
	.long	0x168
	.word	0x46c
	.uleb128 0x10
	.ascii "enc_y\0"
	.byte	0xb
	.byte	0x39
	.long	0x168
	.word	0x470
	.uleb128 0x10
	.ascii "dx_min\0"
	.byte	0xb
	.byte	0x3c
	.long	0x168
	.word	0x474
	.uleb128 0x10
	.ascii "dx_max\0"
	.byte	0xb
	.byte	0x3d
	.long	0x168
	.word	0x478
	.uleb128 0x10
	.ascii "x_min\0"
	.byte	0xb
	.byte	0x40
	.long	0x168
	.word	0x47c
	.uleb128 0x10
	.ascii "x_max\0"
	.byte	0xb
	.byte	0x41
	.long	0x168
	.word	0x480
	.uleb128 0x10
	.ascii "bbx_x_max_bit_size\0"
	.byte	0xb
	.byte	0x44
	.long	0xc3
	.word	0x484
	.uleb128 0x10
	.ascii "bbx_y_max_bit_size\0"
	.byte	0xb
	.byte	0x45
	.long	0xc3
	.word	0x488
	.uleb128 0x10
	.ascii "bbx_w_max_bit_size\0"
	.byte	0xb
	.byte	0x46
	.long	0xc3
	.word	0x48c
	.uleb128 0x10
	.ascii "bbx_h_max_bit_size\0"
	.byte	0xb
	.byte	0x47
	.long	0xc3
	.word	0x490
	.uleb128 0x10
	.ascii "dx_max_bit_size\0"
	.byte	0xb
	.byte	0x48
	.long	0xc3
	.word	0x494
	.uleb128 0x21
	.secrel32	LASF4
	.byte	0xb
	.byte	0x4b
	.long	0x10ef
	.word	0x498
	.uleb128 0x21
	.secrel32	LASF5
	.byte	0xb
	.byte	0x4c
	.long	0xc3
	.word	0x49c
	.uleb128 0x21
	.secrel32	LASF6
	.byte	0xb
	.byte	0x4d
	.long	0xc3
	.word	0x4a0
	.byte	0
	.uleb128 0xe
	.ascii "_bbx_struct\0"
	.byte	0x10
	.byte	0xa
	.byte	0xc
	.long	0xf59
	.uleb128 0xb
	.ascii "w\0"
	.byte	0xa
	.byte	0xe
	.long	0x168
	.byte	0
	.uleb128 0xb
	.ascii "h\0"
	.byte	0xa
	.byte	0xf
	.long	0x168
	.byte	0x4
	.uleb128 0xb
	.ascii "x\0"
	.byte	0xa
	.byte	0x10
	.long	0x168
	.byte	0x8
	.uleb128 0xb
	.ascii "y\0"
	.byte	0xa
	.byte	0x11
	.long	0x168
	.byte	0xc
	.byte	0
	.uleb128 0x2
	.ascii "bbx_t\0"
	.byte	0xa
	.byte	0x13
	.long	0xf1c
	.uleb128 0xe
	.ascii "_bdf_glyph_struct\0"
	.byte	0x60
	.byte	0xa
	.byte	0x16
	.long	0x10e9
	.uleb128 0xb
	.ascii "bf\0"
	.byte	0xa
	.byte	0x18
	.long	0x10e9
	.byte	0
	.uleb128 0x12
	.secrel32	LASF1
	.byte	0xa
	.byte	0x1a
	.long	0x168
	.byte	0x4
	.uleb128 0xb
	.ascii "map_to\0"
	.byte	0xa
	.byte	0x1b
	.long	0x168
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF2
	.byte	0xa
	.byte	0x1d
	.long	0x168
	.byte	0xc
	.uleb128 0x12
	.secrel32	LASF3
	.byte	0xa
	.byte	0x1e
	.long	0x168
	.byte	0x10
	.uleb128 0xb
	.ascii "bbx\0"
	.byte	0xa
	.byte	0x20
	.long	0xf59
	.byte	0x14
	.uleb128 0xb
	.ascii "shift_x\0"
	.byte	0xa
	.byte	0x21
	.long	0x168
	.byte	0x24
	.uleb128 0xb
	.ascii "bitmap_data\0"
	.byte	0xa
	.byte	0x23
	.long	0x10ef
	.byte	0x28
	.uleb128 0xb
	.ascii "bitmap_width\0"
	.byte	0xa
	.byte	0x24
	.long	0xc3
	.byte	0x2c
	.uleb128 0xb
	.ascii "bitmap_height\0"
	.byte	0xa
	.byte	0x25
	.long	0xc3
	.byte	0x30
	.uleb128 0x12
	.secrel32	LASF4
	.byte	0xa
	.byte	0x2a
	.long	0x10ef
	.byte	0x34
	.uleb128 0x12
	.secrel32	LASF5
	.byte	0xa
	.byte	0x2b
	.long	0xc3
	.byte	0x38
	.uleb128 0x12
	.secrel32	LASF6
	.byte	0xa
	.byte	0x2c
	.long	0xc3
	.byte	0x3c
	.uleb128 0xb
	.ascii "target_bit_pos\0"
	.byte	0xa
	.byte	0x2d
	.long	0xc3
	.byte	0x40
	.uleb128 0xb
	.ascii "rle_bits_per_0\0"
	.byte	0xa
	.byte	0x31
	.long	0x9d
	.byte	0x44
	.uleb128 0xb
	.ascii "rle_bits_per_1\0"
	.byte	0xa
	.byte	0x32
	.long	0x9d
	.byte	0x48
	.uleb128 0xb
	.ascii "rle_is_first\0"
	.byte	0xa
	.byte	0x34
	.long	0xc3
	.byte	0x4c
	.uleb128 0xb
	.ascii "rle_bitcnt\0"
	.byte	0xa
	.byte	0x35
	.long	0x9d
	.byte	0x50
	.uleb128 0xb
	.ascii "rle_last_0\0"
	.byte	0xa
	.byte	0x36
	.long	0x9d
	.byte	0x54
	.uleb128 0xb
	.ascii "rle_last_1\0"
	.byte	0xa
	.byte	0x37
	.long	0x9d
	.byte	0x58
	.uleb128 0xb
	.ascii "width_deviation\0"
	.byte	0xa
	.byte	0x39
	.long	0x168
	.byte	0x5c
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xc3c
	.uleb128 0xc
	.byte	0x4
	.long	0xc21
	.uleb128 0x2
	.ascii "bg_t\0"
	.byte	0xa
	.byte	0x3c
	.long	0xf66
	.uleb128 0xc
	.byte	0x4
	.long	0x1107
	.uleb128 0xc
	.byte	0x4
	.long	0x10f5
	.uleb128 0x8
	.long	0x254
	.long	0x111e
	.uleb128 0x22
	.long	0x1f7
	.word	0x3ff
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xc30
	.uleb128 0x23
	.ascii "bf_ParseFile\0"
	.byte	0x1
	.word	0x1ca
	.long	0xc3
	.long	LFB24
	.long	LFE24-LFB24
	.uleb128 0x1
	.byte	0x9c
	.long	0x1173
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.word	0x1ca
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "name\0"
	.byte	0x1
	.word	0x1ca
	.long	0x67a
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x25
	.ascii "r\0"
	.byte	0x1
	.word	0x1cc
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x26
	.ascii "bf_parse_file\0"
	.byte	0x1
	.word	0x1b8
	.long	0xc3
	.long	LFB23
	.long	LFE23-LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0x11ba
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.word	0x1b8
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "line_cnt\0"
	.byte	0x1
	.word	0x1ba
	.long	0x168
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x27
	.ascii "bf_parse_line\0"
	.byte	0x1
	.byte	0xfb
	.long	0xc3
	.long	LFB22
	.long	LFE22-LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x1213
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0xfb
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "cmd\0"
	.byte	0x1
	.byte	0xfd
	.long	0x110d
	.uleb128 0x5
	.byte	0x3
	.long	_cmd.3492
	.uleb128 0x2a
	.long	LBB2
	.long	LBE2-LBB2
	.uleb128 0x25
	.ascii "c\0"
	.byte	0x1
	.word	0x199
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x2b
	.ascii "bf_set_pixel_by_hex_char\0"
	.byte	0x1
	.byte	0xf0
	.long	LFB21
	.long	LFE21-LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0x1259
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0xf0
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x28
	.ascii "hex\0"
	.byte	0x1
	.byte	0xf0
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x2b
	.ascii "bf_set_pixel_by_halfbyte\0"
	.byte	0x1
	.byte	0xdc
	.long	LFB20
	.long	LFE20-LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x12d1
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0xdc
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x28
	.ascii "halfbyte\0"
	.byte	0x1
	.byte	0xdc
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x29
	.ascii "i\0"
	.byte	0x1
	.byte	0xde
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x29
	.ascii "bg\0"
	.byte	0x1
	.byte	0xdf
	.long	0x1107
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x2c
	.ascii "__func__\0"
	.long	0x12e1
	.uleb128 0x5
	.byte	0x3
	.long	___func__.3481
	.byte	0
	.uleb128 0x8
	.long	0x25c
	.long	0x12e1
	.uleb128 0x9
	.long	0x1f7
	.byte	0x18
	.byte	0
	.uleb128 0xd
	.long	0x12d1
	.uleb128 0x27
	.ascii "bf_add_glyph_to_list\0"
	.byte	0x1
	.byte	0xb5
	.long	0xc3
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x132b
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0xb5
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "bg\0"
	.byte	0x1
	.byte	0xb7
	.long	0x1107
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x27
	.ascii "bf_get_long\0"
	.byte	0x1
	.byte	0x7b
	.long	0x168
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x1381
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0x7b
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "c\0"
	.byte	0x1
	.byte	0x7d
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x29
	.ascii "v\0"
	.byte	0x1
	.byte	0x7e
	.long	0x168
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x29
	.ascii "sign\0"
	.byte	0x1
	.byte	0x7f
	.long	0x168
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x27
	.ascii "bf_get_eol_string\0"
	.byte	0x1
	.byte	0x5d
	.long	0x67a
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x13df
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0x5d
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "buf\0"
	.byte	0x1
	.byte	0x5f
	.long	0x110d
	.uleb128 0x5
	.byte	0x3
	.long	_buf.3458
	.uleb128 0x29
	.ascii "i\0"
	.byte	0x1
	.byte	0x60
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x29
	.ascii "c\0"
	.byte	0x1
	.byte	0x61
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x27
	.ascii "bf_get_string\0"
	.byte	0x1
	.byte	0x3c
	.long	0x67a
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x1439
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0x3c
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "buf\0"
	.byte	0x1
	.byte	0x3e
	.long	0x110d
	.uleb128 0x5
	.byte	0x3
	.long	_buf.3450
	.uleb128 0x29
	.ascii "i\0"
	.byte	0x1
	.byte	0x3f
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x29
	.ascii "c\0"
	.byte	0x1
	.byte	0x40
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x27
	.ascii "bf_get_identifier\0"
	.byte	0x1
	.byte	0x27
	.long	0x67a
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x1497
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0x27
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "buf\0"
	.byte	0x1
	.byte	0x29
	.long	0x110d
	.uleb128 0x5
	.byte	0x3
	.long	_buf.3442
	.uleb128 0x29
	.ascii "c\0"
	.byte	0x1
	.byte	0x2a
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x29
	.ascii "i\0"
	.byte	0x1
	.byte	0x2b
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x2b
	.ascii "bf_skipspace\0"
	.byte	0x1
	.byte	0x18
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x14cf
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0x18
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x29
	.ascii "c\0"
	.byte	0x1
	.byte	0x1a
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x2b
	.ascii "bf_next\0"
	.byte	0x1
	.byte	0xf
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x14f6
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0xf
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x2d
	.ascii "bf_curr\0"
	.byte	0x1
	.byte	0x8
	.long	0xc3
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x28
	.ascii "bf\0"
	.byte	0x1
	.byte	0x8
	.long	0x10e9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
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
	.uleb128 0x3
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
	.uleb128 0x22
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x2e
	.byte	0x1
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
LASF3:
	.ascii "dwidth_y\0"
LASF1:
	.ascii "encoding\0"
LASF6:
	.ascii "target_cnt\0"
LASF4:
	.ascii "target_data\0"
LASF2:
	.ascii "dwidth_x\0"
LASF0:
	.ascii "_on_exit_args\0"
LASF5:
	.ascii "target_max\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_bf_AddGlyph;	.scl	2;	.type	32;	.endef
	.def	_bf_Error;	.scl	2;	.type	32;	.endef
	.def	_bg_SetBitmapSize;	.scl	2;	.type	32;	.endef
	.def	___assert_func;	.scl	2;	.type	32;	.endef
	.def	_bg_SetBitmapPixel;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_strdup;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_bf_Log;	.scl	2;	.type	32;	.endef
