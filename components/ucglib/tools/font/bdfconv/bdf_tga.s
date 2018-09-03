	.file	"bdf_tga.c"
	.text
Ltext0:
.lcomm _tga_width,2,2
.lcomm _tga_height,2,2
.lcomm _tga_data,4,4
.lcomm _tga_font,4,4
.lcomm _glyph_cnt,4,4
.lcomm _bits_per_0,4,4
.lcomm _bits_per_1,4,4
.lcomm _bits_per_char_width,4,4
.lcomm _bits_per_char_height,4,4
.lcomm _bits_per_char_x,4,4
.lcomm _bits_per_char_y,4,4
.lcomm _bits_per_delta_x,4,4
.lcomm _char_width,4,4
.lcomm _char_height,4,4
.lcomm _char_descent,4,4
	.globl	_tga_get_char_width
	.def	_tga_get_char_width;	.scl	2;	.type	32;	.endef
_tga_get_char_width:
LFB12:
	.file 1 "bdf_tga.c"
	.loc 1 63 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 64 0
	movl	_char_width, %eax
	.loc 1 65 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_tga_get_char_height
	.def	_tga_get_char_height;	.scl	2;	.type	32;	.endef
_tga_get_char_height:
LFB13:
	.loc 1 68 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 69 0
	movl	_char_height, %eax
	.loc 1 70 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.globl	_tga_init
	.def	_tga_init;	.scl	2;	.type	32;	.endef
_tga_init:
LFB14:
	.loc 1 73 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movw	%dx, -12(%ebp)
	movw	%ax, -16(%ebp)
	.loc 1 74 0
	movw	$0, _tga_width
	.loc 1 75 0
	movw	$0, _tga_height
	.loc 1 76 0
	movl	_tga_data, %eax
	testl	%eax, %eax
	je	L6
	.loc 1 77 0
	movl	_tga_data, %eax
	movl	%eax, (%esp)
	call	_free
L6:
	.loc 1 78 0
	movzwl	-12(%ebp), %edx
	movzwl	-16(%ebp), %eax
	imull	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, _tga_data
	.loc 1 79 0
	movl	_tga_data, %eax
	testl	%eax, %eax
	jne	L7
	.loc 1 80 0
	movl	$0, %eax
	jmp	L8
L7:
	.loc 1 81 0
	movzwl	-12(%ebp), %eax
	movw	%ax, _tga_width
	.loc 1 82 0
	movzwl	-16(%ebp), %eax
	movw	%ax, _tga_height
	.loc 1 83 0
	movzwl	_tga_width, %eax
	movzwl	%ax, %edx
	movzwl	_tga_height, %eax
	movzwl	%ax, %eax
	imull	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	_tga_data, %eax
	movl	%edx, 8(%esp)
	movl	$255, 4(%esp)
	movl	%eax, (%esp)
	call	_memset
	.loc 1 84 0
	movl	$1, %eax
L8:
	.loc 1 85 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.globl	_tga_set_pixel
	.def	_tga_set_pixel;	.scl	2;	.type	32;	.endef
_tga_set_pixel:
LFB15:
	.loc 1 88 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
	movl	24(%ebp), %eax
	movw	%si, -28(%ebp)
	movw	%bx, -32(%ebp)
	movb	%cl, -36(%ebp)
	movb	%dl, -40(%ebp)
	movb	%al, -44(%ebp)
	.loc 1 90 0
	movzwl	_tga_height, %eax
	cmpw	%ax, -32(%ebp)
	jnb	L13
	.loc 1 92 0
	movzwl	_tga_width, %eax
	cmpw	%ax, -28(%ebp)
	jnb	L14
	.loc 1 94 0
	movl	_tga_data, %ecx
	movzwl	_tga_height, %eax
	movzwl	%ax, %edx
	movzwl	-32(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, %edx
	movzwl	_tga_width, %eax
	movzwl	%ax, %eax
	imull	%eax, %edx
	movzwl	-28(%ebp), %eax
	addl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	addl	%ecx, %eax
	movl	%eax, -12(%ebp)
	.loc 1 95 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movzbl	-44(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 96 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movzbl	-40(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 97 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movzbl	-36(%ebp), %edx
	movb	%dl, (%eax)
	jmp	L9
L13:
	.loc 1 91 0
	nop
	jmp	L9
L14:
	.loc 1 93 0
	nop
L9:
	.loc 1 98 0
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_tga_write_byte
	.def	_tga_write_byte;	.scl	2;	.type	32;	.endef
_tga_write_byte:
LFB16:
	.loc 1 101 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	movb	%al, -12(%ebp)
	.loc 1 102 0
	movzbl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_fputc
	.loc 1 103 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.globl	_tga_write_word
	.def	_tga_write_word;	.scl	2;	.type	32;	.endef
_tga_write_word:
LFB17:
	.loc 1 106 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	movw	%ax, -12(%ebp)
	.loc 1 107 0
	movzwl	-12(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 108 0
	movzwl	-12(%ebp), %eax
	shrw	$8, %ax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 109 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.section .rdata,"dr"
LC0:
	.ascii "wb\0"
LC1:
	.ascii "TRUEVISION-XFILE.\0"
	.text
	.globl	_tga_save
	.def	_tga_save;	.scl	2;	.type	32;	.endef
_tga_save:
LFB18:
	.loc 1 112 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 114 0
	movl	$LC0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fopen
	movl	%eax, -12(%ebp)
	.loc 1 115 0
	cmpl	$0, -12(%ebp)
	je	L19
	.loc 1 117 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 118 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 119 0
	movl	$2, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 120 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 121 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 122 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 123 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 124 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 125 0
	movzwl	_tga_width, %eax
	movzwl	%ax, %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 126 0
	movzwl	_tga_height, %eax
	movzwl	%ax, %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 127 0
	movl	$24, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 128 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_byte
	.loc 1 129 0
	movzwl	_tga_width, %eax
	movzwl	%ax, %edx
	movzwl	_tga_height, %eax
	movzwl	%ax, %eax
	imull	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%eax, %ecx
	movl	_tga_data, %eax
	movl	-12(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	$1, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_fwrite
	.loc 1 130 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 131 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 132 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 133 0
	movl	$0, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_write_word
	.loc 1 134 0
	movl	-12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$1, 8(%esp)
	movl	$18, 4(%esp)
	movl	$LC1, (%esp)
	call	_fwrite
	.loc 1 135 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fclose
L19:
	.loc 1 137 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.globl	_tga_set_font
	.def	_tga_set_font;	.scl	2;	.type	32;	.endef
_tga_set_font:
LFB19:
	.loc 1 173 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 174 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _glyph_cnt
	.loc 1 175 0
	addl	$1, 8(%ebp)
	.loc 1 176 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_0
	.loc 1 177 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_1
	.loc 1 178 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_char_width
	.loc 1 179 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_char_height
	.loc 1 180 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_char_x
	.loc 1 181 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_char_y
	.loc 1 182 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _bits_per_delta_x
	.loc 1 183 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _char_width
	.loc 1 184 0
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, _char_height
	.loc 1 185 0
	addl	$1, 8(%ebp)
	.loc 1 186 0
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, _char_descent
	.loc 1 187 0
	addl	$1, 8(%ebp)
	.loc 1 189 0
	addl	$1, 8(%ebp)
	.loc 1 190 0
	addl	$1, 8(%ebp)
	.loc 1 191 0
	addl	$1, 8(%ebp)
	.loc 1 192 0
	addl	$1, 8(%ebp)
	.loc 1 194 0
	addl	$1, 8(%ebp)
	.loc 1 195 0
	addl	$1, 8(%ebp)
	.loc 1 196 0
	addl	$1, 8(%ebp)
	.loc 1 197 0
	addl	$1, 8(%ebp)
	.loc 1 199 0
	movl	8(%ebp), %eax
	movl	%eax, _tga_font
	.loc 1 201 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.globl	_tga_get_glyph_data
	.def	_tga_get_glyph_data;	.scl	2;	.type	32;	.endef
_tga_get_glyph_data:
LFB20:
	.loc 1 221 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	8(%ebp), %eax
	movb	%al, -20(%ebp)
	.loc 1 222 0
	movl	_tga_font, %eax
	movl	%eax, -4(%ebp)
L26:
	.loc 1 225 0
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	L28
	.loc 1 227 0
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-20(%ebp), %al
	jne	L24
	.loc 1 229 0
	movl	-4(%ebp), %eax
	jmp	L25
L24:
	.loc 1 231 0
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	addl	%eax, -4(%ebp)
	.loc 1 225 0
	jmp	L26
L28:
	.loc 1 226 0
	nop
	.loc 1 233 0
	movl	$0, %eax
L25:
	.loc 1 234 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.globl	_tga_fd_inc
	.def	_tga_fd_inc;	.scl	2;	.type	32;	.endef
_tga_fd_inc:
LFB21:
	.loc 1 265 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 266 0
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 267 0
	addl	$1, -4(%ebp)
	.loc 1 268 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	cmpl	-4(%ebp), %eax
	jne	L30
	.loc 1 270 0
	movl	$0, -4(%ebp)
	.loc 1 271 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 16(%eax)
L30:
	.loc 1 273 0
	movl	8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%edx, 12(%eax)
	.loc 1 274 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.globl	_tga_fd_get_unsigned_bits
	.def	_tga_fd_get_unsigned_bits;	.scl	2;	.type	32;	.endef
_tga_fd_get_unsigned_bits:
LFB22:
	.loc 1 278 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 280 0
	movl	8(%ebp), %eax
	movl	32(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 282 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, -4(%ebp)
	.loc 1 284 0
	movl	-8(%ebp), %eax
	movl	%eax, %ecx
	shrl	%cl, -4(%ebp)
	.loc 1 285 0
	movl	-8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	cmpl	$7, %eax
	jbe	L32
	.loc 1 287 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 288 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$8, %eax
	subl	-8(%ebp), %eax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	orl	%eax, -4(%ebp)
	.loc 1 289 0
	subl	$8, -8(%ebp)
L32:
	.loc 1 291 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	andl	%eax, -4(%ebp)
	.loc 1 292 0
	movl	12(%ebp), %eax
	addl	%eax, -8(%ebp)
	.loc 1 294 0
	movl	8(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, 32(%eax)
	.loc 1 295 0
	movl	-4(%ebp), %eax
	.loc 1 296 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.globl	_tga_fd_get_signed_bits
	.def	_tga_fd_get_signed_bits;	.scl	2;	.type	32;	.endef
_tga_fd_get_signed_bits:
LFB23:
	.loc 1 313 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$8, %esp
	.cfi_offset 3, -12
	.loc 1 314 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	12(%ebp), %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	sarl	%eax
	subl	%eax, %edx
	movl	%edx, %eax
	.loc 1 315 0
	addl	$8, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE23:
	.globl	_tga_fd_draw_fg_pixel
	.def	_tga_fd_draw_fg_pixel;	.scl	2;	.type	32;	.endef
_tga_fd_draw_fg_pixel:
LFB24:
	.loc 1 319 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 322 0
	jmp	L37
L38:
	.loc 1 324 0
	subl	$1, 12(%ebp)
	.loc 1 325 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	addl	%edx, %eax
	movzwl	%ax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	addl	%eax, %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	movzwl	%ax, %eax
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_set_pixel
L37:
	.loc 1 322 0
	cmpl	$0, 12(%ebp)
	jne	L38
	.loc 1 327 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
	.globl	_tga_fd_draw_bg_pixel
	.def	_tga_fd_draw_bg_pixel;	.scl	2;	.type	32;	.endef
_tga_fd_draw_bg_pixel:
LFB25:
	.loc 1 330 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 333 0
	jmp	L40
L41:
	.loc 1 335 0
	subl	$1, 12(%ebp)
	.loc 1 336 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L40
	.loc 1 337 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	addl	%edx, %eax
	movzwl	%ax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	addl	%eax, %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	movzwl	%ax, %eax
	movl	$232, 16(%esp)
	movl	$232, 12(%esp)
	movl	$232, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_set_pixel
L40:
	.loc 1 333 0
	cmpl	$0, 12(%ebp)
	jne	L41
	.loc 1 339 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE25:
	.globl	_tga_draw_hline
	.def	_tga_draw_hline;	.scl	2;	.type	32;	.endef
_tga_draw_hline:
LFB26:
	.loc 1 342 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 343 0
	jmp	L43
L45:
	.loc 1 345 0
	subl	$1, 16(%ebp)
	.loc 1 346 0
	cmpl	$0, 20(%ebp)
	jne	L44
	.loc 1 347 0
	movl	12(%ebp), %eax
	movzwl	%ax, %edx
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	movl	16(%ebp), %eax
	addl	%ecx, %eax
	movzwl	%ax, %eax
	movl	$232, 16(%esp)
	movl	$232, 12(%esp)
	movl	$232, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_set_pixel
	jmp	L43
L44:
	.loc 1 349 0
	movl	12(%ebp), %eax
	movzwl	%ax, %edx
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	movl	16(%ebp), %eax
	addl	%ecx, %eax
	movzwl	%ax, %eax
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$255, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_set_pixel
L43:
	.loc 1 343 0
	cmpl	$0, 16(%ebp)
	jne	L45
	.loc 1 351 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.globl	_tga_fd_draw_pixel
	.def	_tga_fd_draw_pixel;	.scl	2;	.type	32;	.endef
_tga_fd_draw_pixel:
LFB27:
	.loc 1 355 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 356 0
	cmpl	$0, 16(%ebp)
	je	L47
	.loc 1 358 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_draw_fg_pixel
	.loc 1 364 0
	jmp	L49
L47:
	.loc 1 362 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_draw_bg_pixel
L49:
	.loc 1 364 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE27:
	.globl	_tga_fd_decode_len
	.def	_tga_fd_decode_len;	.scl	2;	.type	32;	.endef
_tga_fd_decode_len:
LFB28:
	.loc 1 367 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$28, %esp
	.loc 1 369 0
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
L53:
	.loc 1 372 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 373 0
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	subl	%eax, -8(%ebp)
	.loc 1 374 0
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jb	L55
	.loc 1 376 0
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_draw_pixel
	.loc 1 377 0
	movl	-8(%ebp), %eax
	subl	%eax, -4(%ebp)
	.loc 1 378 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 379 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 16(%eax)
	.loc 1 372 0
	jmp	L53
L55:
	.loc 1 375 0
	nop
	.loc 1 381 0
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_draw_pixel
	.loc 1 382 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	-4(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 1 383 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE28:
	.globl	_tga_fd_decode
	.def	_tga_fd_decode;	.scl	2;	.type	32;	.endef
_tga_fd_decode:
LFB29:
	.loc 1 386 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$44, %esp
	.loc 1 390 0
	movl	$0, -4(%ebp)
	.loc 1 392 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 28(%eax)
	.loc 1 393 0
	movl	8(%ebp), %eax
	movl	$0, 32(%eax)
	.loc 1 395 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 396 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 398 0
	movl	_bits_per_char_width, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 20(%eax)
	.loc 1 399 0
	movl	_bits_per_char_height, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 1 400 0
	movl	_bits_per_char_x, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_signed_bits
	movl	%eax, -8(%ebp)
	.loc 1 401 0
	movl	_bits_per_char_y, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_signed_bits
	movl	%eax, -12(%ebp)
	.loc 1 402 0
	movl	_bits_per_delta_x, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_signed_bits
	movl	%eax, -4(%ebp)
	.loc 1 404 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	je	L57
	.loc 1 407 0
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-8(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 408 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	subl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 409 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	-12(%ebp), %eax
	subl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 412 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 413 0
	movl	8(%ebp), %eax
	movl	$0, 16(%eax)
L60:
	.loc 1 418 0
	movl	_bits_per_0, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, -16(%ebp)
	.loc 1 419 0
	movl	_bits_per_1, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, -20(%ebp)
L58:
	.loc 1 422 0 discriminator 1
	movl	$0, 8(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_decode_len
	.loc 1 423 0 discriminator 1
	movl	$1, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_decode_len
	.loc 1 424 0 discriminator 1
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	testl	%eax, %eax
	jne	L58
	.loc 1 426 0
	movl	8(%ebp), %eax
	movl	16(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	cmpl	%eax, %edx
	jnb	L62
	.loc 1 418 0
	jmp	L60
L62:
	.loc 1 427 0
	nop
L57:
	.loc 1 430 0
	movl	-4(%ebp), %eax
	.loc 1 431 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE29:
	.globl	_tga_fd_decode_old
	.def	_tga_fd_decode_old;	.scl	2;	.type	32;	.endef
_tga_fd_decode_old:
LFB30:
	.loc 1 434 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 438 0
	movl	$0, -8(%ebp)
	.loc 1 443 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 28(%eax)
	.loc 1 444 0
	movl	8(%ebp), %eax
	movl	$0, 32(%eax)
	.loc 1 446 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 449 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 451 0
	movl	_bits_per_char_width, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 20(%eax)
	.loc 1 452 0
	movl	_bits_per_char_height, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 1 453 0
	movl	_bits_per_char_x, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_signed_bits
	movl	%eax, -12(%ebp)
	.loc 1 454 0
	movl	_bits_per_char_y, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_signed_bits
	movl	%eax, -16(%ebp)
	.loc 1 455 0
	movl	_bits_per_delta_x, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_signed_bits
	movl	%eax, -8(%ebp)
	.loc 1 459 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	je	L64
	.loc 1 468 0
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 469 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	subl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 470 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	-16(%ebp), %eax
	subl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 474 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 475 0
	movl	8(%ebp), %eax
	movl	$0, 16(%eax)
L71:
	.loc 1 484 0
	movl	_bits_per_0, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, -20(%ebp)
	.loc 1 485 0
	movl	_bits_per_1, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	movl	%eax, -24(%ebp)
L69:
	.loc 1 489 0
	movl	$0, -4(%ebp)
	jmp	L65
L66:
	.loc 1 491 0 discriminator 3
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_draw_bg_pixel
	.loc 1 492 0 discriminator 3
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_inc
	.loc 1 489 0 discriminator 3
	addl	$1, -4(%ebp)
L65:
	.loc 1 489 0 is_stmt 0 discriminator 1
	movl	-4(%ebp), %eax
	cmpl	-20(%ebp), %eax
	jb	L66
	.loc 1 506 0 is_stmt 1
	movl	$0, -4(%ebp)
	jmp	L67
L68:
	.loc 1 508 0 discriminator 3
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_draw_fg_pixel
	.loc 1 509 0 discriminator 3
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_inc
	.loc 1 506 0 discriminator 3
	addl	$1, -4(%ebp)
L67:
	.loc 1 506 0 is_stmt 0 discriminator 1
	movl	-4(%ebp), %eax
	cmpl	-24(%ebp), %eax
	jb	L68
	.loc 1 512 0 is_stmt 1
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_get_unsigned_bits
	testl	%eax, %eax
	jne	L69
	.loc 1 514 0
	movl	8(%ebp), %eax
	movl	16(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	cmpl	%eax, %edx
	jnb	L73
	.loc 1 484 0
	jmp	L71
L73:
	.loc 1 515 0
	nop
L64:
	.loc 1 524 0
	movl	-8(%ebp), %eax
	.loc 1 525 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE30:
	.globl	_tga_draw_glyph
	.def	_tga_draw_glyph;	.scl	2;	.type	32;	.endef
_tga_draw_glyph:
LFB31:
	.loc 1 528 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$88, %esp
	movl	16(%ebp), %eax
	movb	%al, -68(%ebp)
	.loc 1 529 0
	movl	$0, -4(%ebp)
	.loc 1 531 0
	movl	8(%ebp), %eax
	movl	%eax, -52(%ebp)
	.loc 1 532 0
	movl	12(%ebp), %eax
	movl	%eax, -48(%ebp)
	.loc 1 533 0
	cmpl	$0, 20(%ebp)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -44(%ebp)
	.loc 1 534 0
	movzbl	-68(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_get_glyph_data
	movl	%eax, -8(%ebp)
	.loc 1 535 0
	cmpl	$0, -8(%ebp)
	je	L75
	.loc 1 537 0
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-52(%ebp), %eax
	movl	%eax, (%esp)
	call	_tga_fd_decode
	movl	%eax, -4(%ebp)
	.loc 1 538 0
	cmpl	$0, 20(%ebp)
	je	L75
	.loc 1 540 0
	movl	12(%ebp), %eax
	movzwl	%ax, %edx
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movzwl	%ax, %eax
	movl	$240, 16(%esp)
	movl	$133, 12(%esp)
	movl	$28, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_set_pixel
	.loc 1 541 0
	movl	12(%ebp), %eax
	movzwl	%ax, %edx
	movl	8(%ebp), %eax
	movzwl	%ax, %eax
	movl	$0, 16(%esp)
	movl	$164, 12(%esp)
	movl	$255, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_tga_set_pixel
L75:
	.loc 1 544 0
	movl	-4(%ebp), %eax
	.loc 1 545 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE31:
	.globl	_tga_draw_string
	.def	_tga_draw_string;	.scl	2;	.type	32;	.endef
_tga_draw_string:
LFB32:
	.loc 1 548 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$32, %esp
	.loc 1 549 0
	movl	$0, -4(%ebp)
	.loc 1 550 0
	jmp	L78
L81:
	.loc 1 552 0
	movl	16(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	8(%ebp), %ecx
	movl	-4(%ebp), %edx
	addl	%edx, %ecx
	movl	20(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	_tga_draw_glyph
	addl	%eax, -4(%ebp)
	.loc 1 553 0
	cmpl	$0, 24(%ebp)
	je	L79
	.loc 1 554 0
	movl	-4(%ebp), %eax
	cmpl	24(%ebp), %eax
	ja	L83
L79:
	.loc 1 556 0
	addl	$1, 16(%ebp)
L78:
	.loc 1 550 0
	movl	16(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L81
	jmp	L80
L83:
	.loc 1 555 0
	nop
L80:
	.loc 1 558 0
	movl	-4(%ebp), %eax
	.loc 1 559 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE32:
Letext0:
	.file 2 "/usr/include/machine/_default_types.h"
	.file 3 "/usr/include/sys/_stdint.h"
	.file 4 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 5 "/usr/include/sys/lock.h"
	.file 6 "/usr/include/sys/_types.h"
	.file 7 "/usr/include/sys/reent.h"
	.file 8 "/usr/include/stdio.h"
	.file 9 "/usr/include/stdlib.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x1621
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_tga.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.ascii "__int8_t\0"
	.byte	0x2
	.byte	0x29
	.long	0x9c
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0x2
	.ascii "__uint8_t\0"
	.byte	0x2
	.byte	0x2b
	.long	0xbc
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.uleb128 0x2
	.ascii "__uint16_t\0"
	.byte	0x2
	.byte	0x39
	.long	0xec
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.uleb128 0x2
	.ascii "int8_t\0"
	.byte	0x3
	.byte	0x14
	.long	0x8c
	.uleb128 0x2
	.ascii "uint8_t\0"
	.byte	0x3
	.byte	0x18
	.long	0xab
	.uleb128 0x4
	.long	0x152
	.uleb128 0x2
	.ascii "uint16_t\0"
	.byte	0x3
	.byte	0x24
	.long	0xda
	.uleb128 0x2
	.ascii "size_t\0"
	.byte	0x4
	.byte	0xd8
	.long	0x109
	.uleb128 0x3
	.byte	0xc
	.byte	0x4
	.ascii "long double\0"
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0x4
	.long	0x193
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "long unsigned int\0"
	.uleb128 0x2
	.ascii "_LOCK_T\0"
	.byte	0x5
	.byte	0xc
	.long	0x1c4
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii "long int\0"
	.uleb128 0x2
	.ascii "_off64_t\0"
	.byte	0x6
	.byte	0x5e
	.long	0x119
	.uleb128 0x2
	.ascii "_fpos_t\0"
	.byte	0x6
	.byte	0x72
	.long	0x1c6
	.uleb128 0x2
	.ascii "_fpos64_t\0"
	.byte	0x6
	.byte	0x78
	.long	0x1d2
	.uleb128 0x2
	.ascii "_ssize_t\0"
	.byte	0x6
	.byte	0x91
	.long	0x102
	.uleb128 0x6
	.ascii "wint_t\0"
	.byte	0x4
	.word	0x165
	.long	0x109
	.uleb128 0x7
	.byte	0x4
	.byte	0x6
	.byte	0xa6
	.long	0x245
	.uleb128 0x8
	.ascii "__wch\0"
	.byte	0x6
	.byte	0xa8
	.long	0x212
	.uleb128 0x8
	.ascii "__wchb\0"
	.byte	0x6
	.byte	0xa9
	.long	0x245
	.byte	0
	.uleb128 0x9
	.long	0xbc
	.long	0x255
	.uleb128 0xa
	.long	0x255
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "sizetype\0"
	.uleb128 0xb
	.byte	0x8
	.byte	0x6
	.byte	0xa3
	.long	0x28a
	.uleb128 0xc
	.ascii "__count\0"
	.byte	0x6
	.byte	0xa5
	.long	0x102
	.byte	0
	.uleb128 0xc
	.ascii "__value\0"
	.byte	0x6
	.byte	0xaa
	.long	0x221
	.byte	0x4
	.byte	0
	.uleb128 0x2
	.ascii "_mbstate_t\0"
	.byte	0x6
	.byte	0xab
	.long	0x261
	.uleb128 0x2
	.ascii "_flock_t\0"
	.byte	0x6
	.byte	0xaf
	.long	0x1b5
	.uleb128 0x2
	.ascii "__ULong\0"
	.byte	0x7
	.byte	0x16
	.long	0x1a0
	.uleb128 0xd
	.ascii "_Bigint\0"
	.byte	0x18
	.byte	0x7
	.byte	0x2f
	.long	0x31b
	.uleb128 0xc
	.ascii "_next\0"
	.byte	0x7
	.byte	0x31
	.long	0x31b
	.byte	0
	.uleb128 0xc
	.ascii "_k\0"
	.byte	0x7
	.byte	0x32
	.long	0x102
	.byte	0x4
	.uleb128 0xc
	.ascii "_maxwds\0"
	.byte	0x7
	.byte	0x32
	.long	0x102
	.byte	0x8
	.uleb128 0xc
	.ascii "_sign\0"
	.byte	0x7
	.byte	0x32
	.long	0x102
	.byte	0xc
	.uleb128 0xc
	.ascii "_wds\0"
	.byte	0x7
	.byte	0x32
	.long	0x102
	.byte	0x10
	.uleb128 0xc
	.ascii "_x\0"
	.byte	0x7
	.byte	0x33
	.long	0x321
	.byte	0x14
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x2bb
	.uleb128 0x9
	.long	0x2ac
	.long	0x331
	.uleb128 0xa
	.long	0x255
	.byte	0
	.byte	0
	.uleb128 0xd
	.ascii "__tm\0"
	.byte	0x24
	.byte	0x7
	.byte	0x37
	.long	0x3df
	.uleb128 0xc
	.ascii "__tm_sec\0"
	.byte	0x7
	.byte	0x39
	.long	0x102
	.byte	0
	.uleb128 0xc
	.ascii "__tm_min\0"
	.byte	0x7
	.byte	0x3a
	.long	0x102
	.byte	0x4
	.uleb128 0xc
	.ascii "__tm_hour\0"
	.byte	0x7
	.byte	0x3b
	.long	0x102
	.byte	0x8
	.uleb128 0xc
	.ascii "__tm_mday\0"
	.byte	0x7
	.byte	0x3c
	.long	0x102
	.byte	0xc
	.uleb128 0xc
	.ascii "__tm_mon\0"
	.byte	0x7
	.byte	0x3d
	.long	0x102
	.byte	0x10
	.uleb128 0xc
	.ascii "__tm_year\0"
	.byte	0x7
	.byte	0x3e
	.long	0x102
	.byte	0x14
	.uleb128 0xc
	.ascii "__tm_wday\0"
	.byte	0x7
	.byte	0x3f
	.long	0x102
	.byte	0x18
	.uleb128 0xc
	.ascii "__tm_yday\0"
	.byte	0x7
	.byte	0x40
	.long	0x102
	.byte	0x1c
	.uleb128 0xc
	.ascii "__tm_isdst\0"
	.byte	0x7
	.byte	0x41
	.long	0x102
	.byte	0x20
	.byte	0
	.uleb128 0xf
	.secrel32	LASF0
	.word	0x108
	.byte	0x7
	.byte	0x4a
	.long	0x434
	.uleb128 0xc
	.ascii "_fnargs\0"
	.byte	0x7
	.byte	0x4b
	.long	0x434
	.byte	0
	.uleb128 0xc
	.ascii "_dso_handle\0"
	.byte	0x7
	.byte	0x4c
	.long	0x434
	.byte	0x80
	.uleb128 0x10
	.ascii "_fntypes\0"
	.byte	0x7
	.byte	0x4e
	.long	0x2ac
	.word	0x100
	.uleb128 0x10
	.ascii "_is_cxa\0"
	.byte	0x7
	.byte	0x51
	.long	0x2ac
	.word	0x104
	.byte	0
	.uleb128 0x9
	.long	0x1c4
	.long	0x444
	.uleb128 0xa
	.long	0x255
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.ascii "_atexit\0"
	.word	0x190
	.byte	0x7
	.byte	0x5d
	.long	0x48a
	.uleb128 0xc
	.ascii "_next\0"
	.byte	0x7
	.byte	0x5e
	.long	0x48a
	.byte	0
	.uleb128 0xc
	.ascii "_ind\0"
	.byte	0x7
	.byte	0x5f
	.long	0x102
	.byte	0x4
	.uleb128 0xc
	.ascii "_fns\0"
	.byte	0x7
	.byte	0x61
	.long	0x490
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF0
	.byte	0x7
	.byte	0x62
	.long	0x3df
	.byte	0x88
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x444
	.uleb128 0x9
	.long	0x4a0
	.long	0x4a0
	.uleb128 0xa
	.long	0x255
	.byte	0x1f
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x4a6
	.uleb128 0x13
	.uleb128 0xd
	.ascii "__sbuf\0"
	.byte	0x8
	.byte	0x7
	.byte	0x75
	.long	0x4d3
	.uleb128 0xc
	.ascii "_base\0"
	.byte	0x7
	.byte	0x76
	.long	0x4d3
	.byte	0
	.uleb128 0xc
	.ascii "_size\0"
	.byte	0x7
	.byte	0x77
	.long	0x102
	.byte	0x4
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xbc
	.uleb128 0x14
	.long	0x202
	.long	0x4f7
	.uleb128 0x15
	.long	0x4f7
	.uleb128 0x15
	.long	0x1c4
	.uleb128 0x15
	.long	0x6a1
	.uleb128 0x15
	.long	0x176
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x502
	.uleb128 0x4
	.long	0x4f7
	.uleb128 0x16
	.ascii "_reent\0"
	.word	0x440
	.byte	0x7
	.word	0x239
	.long	0x6a1
	.uleb128 0x17
	.ascii "_errno\0"
	.byte	0x7
	.word	0x23b
	.long	0x102
	.byte	0
	.uleb128 0x17
	.ascii "_stdin\0"
	.byte	0x7
	.word	0x240
	.long	0x92c
	.byte	0x4
	.uleb128 0x17
	.ascii "_stdout\0"
	.byte	0x7
	.word	0x240
	.long	0x92c
	.byte	0x8
	.uleb128 0x17
	.ascii "_stderr\0"
	.byte	0x7
	.word	0x240
	.long	0x92c
	.byte	0xc
	.uleb128 0x17
	.ascii "_inc\0"
	.byte	0x7
	.word	0x242
	.long	0x102
	.byte	0x10
	.uleb128 0x17
	.ascii "_emergency\0"
	.byte	0x7
	.word	0x243
	.long	0xbd2
	.byte	0x14
	.uleb128 0x17
	.ascii "_unspecified_locale_info\0"
	.byte	0x7
	.word	0x246
	.long	0x102
	.byte	0x30
	.uleb128 0x17
	.ascii "_locale\0"
	.byte	0x7
	.word	0x247
	.long	0xbee
	.byte	0x34
	.uleb128 0x17
	.ascii "__sdidinit\0"
	.byte	0x7
	.word	0x249
	.long	0x102
	.byte	0x38
	.uleb128 0x17
	.ascii "__cleanup\0"
	.byte	0x7
	.word	0x24b
	.long	0xbff
	.byte	0x3c
	.uleb128 0x17
	.ascii "_result\0"
	.byte	0x7
	.word	0x24e
	.long	0x31b
	.byte	0x40
	.uleb128 0x17
	.ascii "_result_k\0"
	.byte	0x7
	.word	0x24f
	.long	0x102
	.byte	0x44
	.uleb128 0x17
	.ascii "_p5s\0"
	.byte	0x7
	.word	0x250
	.long	0x31b
	.byte	0x48
	.uleb128 0x17
	.ascii "_freelist\0"
	.byte	0x7
	.word	0x251
	.long	0xc05
	.byte	0x4c
	.uleb128 0x17
	.ascii "_cvtlen\0"
	.byte	0x7
	.word	0x254
	.long	0x102
	.byte	0x50
	.uleb128 0x17
	.ascii "_cvtbuf\0"
	.byte	0x7
	.word	0x255
	.long	0x6a1
	.byte	0x54
	.uleb128 0x17
	.ascii "_new\0"
	.byte	0x7
	.word	0x278
	.long	0xba9
	.byte	0x58
	.uleb128 0x18
	.ascii "_atexit\0"
	.byte	0x7
	.word	0x27c
	.long	0x48a
	.word	0x148
	.uleb128 0x18
	.ascii "_atexit0\0"
	.byte	0x7
	.word	0x27d
	.long	0x444
	.word	0x14c
	.uleb128 0x18
	.ascii "_sig_func\0"
	.byte	0x7
	.word	0x281
	.long	0xc16
	.word	0x2dc
	.uleb128 0x18
	.ascii "__sglue\0"
	.byte	0x7
	.word	0x286
	.long	0x8e8
	.word	0x2e0
	.uleb128 0x18
	.ascii "__sf\0"
	.byte	0x7
	.word	0x288
	.long	0xc22
	.word	0x2f0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x193
	.uleb128 0xe
	.byte	0x4
	.long	0x4d9
	.uleb128 0x14
	.long	0x202
	.long	0x6cb
	.uleb128 0x15
	.long	0x4f7
	.uleb128 0x15
	.long	0x1c4
	.uleb128 0x15
	.long	0x6cb
	.uleb128 0x15
	.long	0x176
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x19b
	.uleb128 0xe
	.byte	0x4
	.long	0x6ad
	.uleb128 0x14
	.long	0x1e2
	.long	0x6f5
	.uleb128 0x15
	.long	0x4f7
	.uleb128 0x15
	.long	0x1c4
	.uleb128 0x15
	.long	0x1e2
	.uleb128 0x15
	.long	0x102
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x6d7
	.uleb128 0x14
	.long	0x102
	.long	0x70f
	.uleb128 0x15
	.long	0x4f7
	.uleb128 0x15
	.long	0x1c4
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x6fb
	.uleb128 0x9
	.long	0xbc
	.long	0x725
	.uleb128 0xa
	.long	0x255
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.long	0xbc
	.long	0x735
	.uleb128 0xa
	.long	0x255
	.byte	0
	.byte	0
	.uleb128 0xd
	.ascii "__sFILE64\0"
	.byte	0x70
	.byte	0x7
	.byte	0xef
	.long	0x8b5
	.uleb128 0xc
	.ascii "_p\0"
	.byte	0x7
	.byte	0xf0
	.long	0x4d3
	.byte	0
	.uleb128 0xc
	.ascii "_r\0"
	.byte	0x7
	.byte	0xf1
	.long	0x102
	.byte	0x4
	.uleb128 0xc
	.ascii "_w\0"
	.byte	0x7
	.byte	0xf2
	.long	0x102
	.byte	0x8
	.uleb128 0xc
	.ascii "_flags\0"
	.byte	0x7
	.byte	0xf3
	.long	0xcd
	.byte	0xc
	.uleb128 0xc
	.ascii "_file\0"
	.byte	0x7
	.byte	0xf4
	.long	0xcd
	.byte	0xe
	.uleb128 0xc
	.ascii "_bf\0"
	.byte	0x7
	.byte	0xf5
	.long	0x4a7
	.byte	0x10
	.uleb128 0xc
	.ascii "_lbfsize\0"
	.byte	0x7
	.byte	0xf6
	.long	0x102
	.byte	0x18
	.uleb128 0xc
	.ascii "_data\0"
	.byte	0x7
	.byte	0xf8
	.long	0x4f7
	.byte	0x1c
	.uleb128 0xc
	.ascii "_cookie\0"
	.byte	0x7
	.byte	0xfb
	.long	0x1c4
	.byte	0x20
	.uleb128 0xc
	.ascii "_read\0"
	.byte	0x7
	.byte	0xfd
	.long	0x6a7
	.byte	0x24
	.uleb128 0xc
	.ascii "_write\0"
	.byte	0x7
	.byte	0xff
	.long	0x6d1
	.byte	0x28
	.uleb128 0x17
	.ascii "_seek\0"
	.byte	0x7
	.word	0x102
	.long	0x6f5
	.byte	0x2c
	.uleb128 0x17
	.ascii "_close\0"
	.byte	0x7
	.word	0x103
	.long	0x70f
	.byte	0x30
	.uleb128 0x17
	.ascii "_ub\0"
	.byte	0x7
	.word	0x106
	.long	0x4a7
	.byte	0x34
	.uleb128 0x17
	.ascii "_up\0"
	.byte	0x7
	.word	0x107
	.long	0x4d3
	.byte	0x3c
	.uleb128 0x17
	.ascii "_ur\0"
	.byte	0x7
	.word	0x108
	.long	0x102
	.byte	0x40
	.uleb128 0x17
	.ascii "_ubuf\0"
	.byte	0x7
	.word	0x10b
	.long	0x715
	.byte	0x44
	.uleb128 0x17
	.ascii "_nbuf\0"
	.byte	0x7
	.word	0x10c
	.long	0x725
	.byte	0x47
	.uleb128 0x17
	.ascii "_lb\0"
	.byte	0x7
	.word	0x10f
	.long	0x4a7
	.byte	0x48
	.uleb128 0x17
	.ascii "_blksize\0"
	.byte	0x7
	.word	0x112
	.long	0x102
	.byte	0x50
	.uleb128 0x17
	.ascii "_flags2\0"
	.byte	0x7
	.word	0x113
	.long	0x102
	.byte	0x54
	.uleb128 0x17
	.ascii "_offset\0"
	.byte	0x7
	.word	0x115
	.long	0x1d2
	.byte	0x58
	.uleb128 0x17
	.ascii "_seek64\0"
	.byte	0x7
	.word	0x116
	.long	0x8d3
	.byte	0x60
	.uleb128 0x17
	.ascii "_lock\0"
	.byte	0x7
	.word	0x119
	.long	0x29c
	.byte	0x64
	.uleb128 0x17
	.ascii "_mbstate\0"
	.byte	0x7
	.word	0x11b
	.long	0x28a
	.byte	0x68
	.byte	0
	.uleb128 0x14
	.long	0x1f1
	.long	0x8d3
	.uleb128 0x15
	.long	0x4f7
	.uleb128 0x15
	.long	0x1c4
	.uleb128 0x15
	.long	0x1f1
	.uleb128 0x15
	.long	0x102
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x8b5
	.uleb128 0x6
	.ascii "__FILE\0"
	.byte	0x7
	.word	0x11d
	.long	0x735
	.uleb128 0x19
	.ascii "_glue\0"
	.byte	0xc
	.byte	0x7
	.word	0x123
	.long	0x926
	.uleb128 0x17
	.ascii "_next\0"
	.byte	0x7
	.word	0x125
	.long	0x926
	.byte	0
	.uleb128 0x17
	.ascii "_niobs\0"
	.byte	0x7
	.word	0x126
	.long	0x102
	.byte	0x4
	.uleb128 0x17
	.ascii "_iobs\0"
	.byte	0x7
	.word	0x127
	.long	0x92c
	.byte	0x8
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x8e8
	.uleb128 0xe
	.byte	0x4
	.long	0x8d9
	.uleb128 0x19
	.ascii "_rand48\0"
	.byte	0xe
	.byte	0x7
	.word	0x13f
	.long	0x970
	.uleb128 0x17
	.ascii "_seed\0"
	.byte	0x7
	.word	0x140
	.long	0x970
	.byte	0
	.uleb128 0x17
	.ascii "_mult\0"
	.byte	0x7
	.word	0x141
	.long	0x970
	.byte	0x6
	.uleb128 0x17
	.ascii "_add\0"
	.byte	0x7
	.word	0x142
	.long	0xec
	.byte	0xc
	.byte	0
	.uleb128 0x9
	.long	0xec
	.long	0x980
	.uleb128 0xa
	.long	0x255
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x7
	.word	0x259
	.long	0xb2d
	.uleb128 0x17
	.ascii "_unused_rand\0"
	.byte	0x7
	.word	0x25b
	.long	0x109
	.byte	0
	.uleb128 0x17
	.ascii "_strtok_last\0"
	.byte	0x7
	.word	0x25c
	.long	0x6a1
	.byte	0x4
	.uleb128 0x17
	.ascii "_asctime_buf\0"
	.byte	0x7
	.word	0x25d
	.long	0xb2d
	.byte	0x8
	.uleb128 0x17
	.ascii "_localtime_buf\0"
	.byte	0x7
	.word	0x25e
	.long	0x331
	.byte	0x24
	.uleb128 0x17
	.ascii "_gamma_signgam\0"
	.byte	0x7
	.word	0x25f
	.long	0x102
	.byte	0x48
	.uleb128 0x17
	.ascii "_rand_next\0"
	.byte	0x7
	.word	0x260
	.long	0x12a
	.byte	0x50
	.uleb128 0x17
	.ascii "_r48\0"
	.byte	0x7
	.word	0x261
	.long	0x932
	.byte	0x58
	.uleb128 0x17
	.ascii "_mblen_state\0"
	.byte	0x7
	.word	0x262
	.long	0x28a
	.byte	0x68
	.uleb128 0x17
	.ascii "_mbtowc_state\0"
	.byte	0x7
	.word	0x263
	.long	0x28a
	.byte	0x70
	.uleb128 0x17
	.ascii "_wctomb_state\0"
	.byte	0x7
	.word	0x264
	.long	0x28a
	.byte	0x78
	.uleb128 0x17
	.ascii "_l64a_buf\0"
	.byte	0x7
	.word	0x265
	.long	0xb3d
	.byte	0x80
	.uleb128 0x17
	.ascii "_signal_buf\0"
	.byte	0x7
	.word	0x266
	.long	0xb4d
	.byte	0x88
	.uleb128 0x17
	.ascii "_getdate_err\0"
	.byte	0x7
	.word	0x267
	.long	0x102
	.byte	0xa0
	.uleb128 0x17
	.ascii "_mbrlen_state\0"
	.byte	0x7
	.word	0x268
	.long	0x28a
	.byte	0xa4
	.uleb128 0x17
	.ascii "_mbrtowc_state\0"
	.byte	0x7
	.word	0x269
	.long	0x28a
	.byte	0xac
	.uleb128 0x17
	.ascii "_mbsrtowcs_state\0"
	.byte	0x7
	.word	0x26a
	.long	0x28a
	.byte	0xb4
	.uleb128 0x17
	.ascii "_wcrtomb_state\0"
	.byte	0x7
	.word	0x26b
	.long	0x28a
	.byte	0xbc
	.uleb128 0x17
	.ascii "_wcsrtombs_state\0"
	.byte	0x7
	.word	0x26c
	.long	0x28a
	.byte	0xc4
	.uleb128 0x17
	.ascii "_h_errno\0"
	.byte	0x7
	.word	0x26d
	.long	0x102
	.byte	0xcc
	.byte	0
	.uleb128 0x9
	.long	0x193
	.long	0xb3d
	.uleb128 0xa
	.long	0x255
	.byte	0x19
	.byte	0
	.uleb128 0x9
	.long	0x193
	.long	0xb4d
	.uleb128 0xa
	.long	0x255
	.byte	0x7
	.byte	0
	.uleb128 0x9
	.long	0x193
	.long	0xb5d
	.uleb128 0xa
	.long	0x255
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x7
	.word	0x272
	.long	0xb89
	.uleb128 0x17
	.ascii "_nextf\0"
	.byte	0x7
	.word	0x275
	.long	0xb89
	.byte	0
	.uleb128 0x17
	.ascii "_nmalloc\0"
	.byte	0x7
	.word	0x276
	.long	0xb99
	.byte	0x78
	.byte	0
	.uleb128 0x9
	.long	0x4d3
	.long	0xb99
	.uleb128 0xa
	.long	0x255
	.byte	0x1d
	.byte	0
	.uleb128 0x9
	.long	0x109
	.long	0xba9
	.uleb128 0xa
	.long	0x255
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x7
	.word	0x257
	.long	0xbd2
	.uleb128 0x1c
	.ascii "_reent\0"
	.byte	0x7
	.word	0x26e
	.long	0x980
	.uleb128 0x1c
	.ascii "_unused\0"
	.byte	0x7
	.word	0x277
	.long	0xb5d
	.byte	0
	.uleb128 0x9
	.long	0x193
	.long	0xbe2
	.uleb128 0xa
	.long	0x255
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.ascii "__locale_t\0"
	.uleb128 0xe
	.byte	0x4
	.long	0xbe2
	.uleb128 0x1e
	.long	0xbff
	.uleb128 0x15
	.long	0x4f7
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xbf4
	.uleb128 0xe
	.byte	0x4
	.long	0x31b
	.uleb128 0x1e
	.long	0xc16
	.uleb128 0x15
	.long	0x102
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc1c
	.uleb128 0xe
	.byte	0x4
	.long	0xc0b
	.uleb128 0x9
	.long	0x8d9
	.long	0xc32
	.uleb128 0xa
	.long	0x255
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.ascii "_impure_ptr\0"
	.byte	0x7
	.word	0x307
	.long	0x4f7
	.uleb128 0x1f
	.ascii "_global_impure_ptr\0"
	.byte	0x7
	.word	0x308
	.long	0x4fd
	.uleb128 0x2
	.ascii "FILE\0"
	.byte	0x8
	.byte	0x42
	.long	0x8d9
	.uleb128 0x20
	.ascii "suboptarg\0"
	.byte	0x9
	.byte	0x63
	.long	0x6a1
	.uleb128 0xe
	.byte	0x4
	.long	0x161
	.uleb128 0xe
	.byte	0x4
	.long	0x152
	.uleb128 0x21
	.ascii "tga_width\0"
	.byte	0x1
	.byte	0x2c
	.long	0x166
	.uleb128 0x5
	.byte	0x3
	.long	_tga_width
	.uleb128 0x21
	.ascii "tga_height\0"
	.byte	0x1
	.byte	0x2d
	.long	0x166
	.uleb128 0x5
	.byte	0x3
	.long	_tga_height
	.uleb128 0x21
	.ascii "tga_data\0"
	.byte	0x1
	.byte	0x2e
	.long	0xc84
	.uleb128 0x5
	.byte	0x3
	.long	_tga_data
	.uleb128 0x21
	.ascii "tga_font\0"
	.byte	0x1
	.byte	0x30
	.long	0xc84
	.uleb128 0x5
	.byte	0x3
	.long	_tga_font
	.uleb128 0x21
	.ascii "glyph_cnt\0"
	.byte	0x1
	.byte	0x31
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_glyph_cnt
	.uleb128 0x21
	.ascii "bits_per_0\0"
	.byte	0x1
	.byte	0x32
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_0
	.uleb128 0x21
	.ascii "bits_per_1\0"
	.byte	0x1
	.byte	0x33
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_1
	.uleb128 0x21
	.ascii "bits_per_char_width\0"
	.byte	0x1
	.byte	0x34
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_char_width
	.uleb128 0x21
	.ascii "bits_per_char_height\0"
	.byte	0x1
	.byte	0x35
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_char_height
	.uleb128 0x21
	.ascii "bits_per_char_x\0"
	.byte	0x1
	.byte	0x36
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_char_x
	.uleb128 0x21
	.ascii "bits_per_char_y\0"
	.byte	0x1
	.byte	0x37
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_char_y
	.uleb128 0x21
	.ascii "bits_per_delta_x\0"
	.byte	0x1
	.byte	0x38
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_bits_per_delta_x
	.uleb128 0x21
	.ascii "char_width\0"
	.byte	0x1
	.byte	0x39
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_char_width
	.uleb128 0x21
	.ascii "char_height\0"
	.byte	0x1
	.byte	0x3a
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_char_height
	.uleb128 0x21
	.ascii "char_descent\0"
	.byte	0x1
	.byte	0x3b
	.long	0x102
	.uleb128 0x5
	.byte	0x3
	.long	_char_descent
	.uleb128 0xd
	.ascii "tga_fd_struct\0"
	.byte	0x2c
	.byte	0x1
	.byte	0xee
	.long	0xf4f
	.uleb128 0xc
	.ascii "target_x\0"
	.byte	0x1
	.byte	0xf0
	.long	0x109
	.byte	0
	.uleb128 0xc
	.ascii "target_y\0"
	.byte	0x1
	.byte	0xf1
	.long	0x109
	.byte	0x4
	.uleb128 0xc
	.ascii "is_transparent\0"
	.byte	0x1
	.byte	0xf2
	.long	0x109
	.byte	0x8
	.uleb128 0xc
	.ascii "x\0"
	.byte	0x1
	.byte	0xf4
	.long	0x109
	.byte	0xc
	.uleb128 0xc
	.ascii "y\0"
	.byte	0x1
	.byte	0xf5
	.long	0x109
	.byte	0x10
	.uleb128 0xc
	.ascii "glyph_width\0"
	.byte	0x1
	.byte	0xf6
	.long	0x109
	.byte	0x14
	.uleb128 0xc
	.ascii "glyph_height\0"
	.byte	0x1
	.byte	0xf7
	.long	0x109
	.byte	0x18
	.uleb128 0xc
	.ascii "decode_ptr\0"
	.byte	0x1
	.byte	0xfa
	.long	0xc7e
	.byte	0x1c
	.uleb128 0xc
	.ascii "decode_bit_pos\0"
	.byte	0x1
	.byte	0xfb
	.long	0x109
	.byte	0x20
	.uleb128 0xc
	.ascii "bbx_x_max_bit_size\0"
	.byte	0x1
	.byte	0xfd
	.long	0x152
	.byte	0x24
	.uleb128 0xc
	.ascii "bbx_y_max_bit_size\0"
	.byte	0x1
	.byte	0xfe
	.long	0x152
	.byte	0x25
	.uleb128 0xc
	.ascii "bbx_w_max_bit_size\0"
	.byte	0x1
	.byte	0xff
	.long	0x152
	.byte	0x26
	.uleb128 0x17
	.ascii "bbx_h_max_bit_size\0"
	.byte	0x1
	.word	0x100
	.long	0x152
	.byte	0x27
	.uleb128 0x17
	.ascii "dx_max_bit_size\0"
	.byte	0x1
	.word	0x101
	.long	0x152
	.byte	0x28
	.byte	0
	.uleb128 0x6
	.ascii "tga_fd_t\0"
	.byte	0x1
	.word	0x104
	.long	0xe12
	.uleb128 0x22
	.ascii "tga_draw_string\0"
	.byte	0x1
	.word	0x223
	.long	0x109
	.long	LFB32
	.long	LFE32-LFB32
	.uleb128 0x1
	.byte	0x9c
	.long	0xfdd
	.uleb128 0x23
	.ascii "x\0"
	.byte	0x1
	.word	0x223
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "y\0"
	.byte	0x1
	.word	0x223
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x23
	.ascii "s\0"
	.byte	0x1
	.word	0x223
	.long	0x6cb
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x24
	.secrel32	LASF1
	.byte	0x1
	.word	0x223
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x23
	.ascii "max_dx\0"
	.byte	0x1
	.word	0x223
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x25
	.ascii "dx\0"
	.byte	0x1
	.word	0x225
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x22
	.ascii "tga_draw_glyph\0"
	.byte	0x1
	.word	0x20f
	.long	0x109
	.long	LFB31
	.long	LFE31-LFB31
	.uleb128 0x1
	.byte	0x9c
	.long	0x1066
	.uleb128 0x23
	.ascii "x\0"
	.byte	0x1
	.word	0x20f
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "y\0"
	.byte	0x1
	.word	0x20f
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x24
	.secrel32	LASF2
	.byte	0x1
	.word	0x20f
	.long	0x152
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x24
	.secrel32	LASF1
	.byte	0x1
	.word	0x20f
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x25
	.ascii "dx\0"
	.byte	0x1
	.word	0x211
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x25
	.ascii "f\0"
	.byte	0x1
	.word	0x212
	.long	0xf4f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x26
	.secrel32	LASF3
	.byte	0x1
	.word	0x216
	.long	0xc84
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x22
	.ascii "tga_fd_decode_old\0"
	.byte	0x1
	.word	0x1b1
	.long	0x109
	.long	LFB30
	.long	LFE30-LFB30
	.uleb128 0x1
	.byte	0x9c
	.long	0x10f9
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x1b1
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.secrel32	LASF3
	.byte	0x1
	.word	0x1b1
	.long	0xc84
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x25
	.ascii "a\0"
	.byte	0x1
	.word	0x1b3
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x25
	.ascii "b\0"
	.byte	0x1
	.word	0x1b3
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x25
	.ascii "i\0"
	.byte	0x1
	.word	0x1b4
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x25
	.ascii "x\0"
	.byte	0x1
	.word	0x1b5
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "y\0"
	.byte	0x1
	.word	0x1b5
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "d\0"
	.byte	0x1
	.word	0x1b6
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xf4f
	.uleb128 0x22
	.ascii "tga_fd_decode\0"
	.byte	0x1
	.word	0x181
	.long	0x109
	.long	LFB29
	.long	LFE29-LFB29
	.uleb128 0x1
	.byte	0x9c
	.long	0x1181
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x181
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.secrel32	LASF3
	.byte	0x1
	.word	0x181
	.long	0xc84
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x25
	.ascii "a\0"
	.byte	0x1
	.word	0x183
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "b\0"
	.byte	0x1
	.word	0x183
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x25
	.ascii "x\0"
	.byte	0x1
	.word	0x185
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x25
	.ascii "y\0"
	.byte	0x1
	.word	0x185
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "d\0"
	.byte	0x1
	.word	0x186
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x27
	.ascii "tga_fd_decode_len\0"
	.byte	0x1
	.word	0x16e
	.long	LFB28
	.long	LFE28-LFB28
	.uleb128 0x1
	.byte	0x9c
	.long	0x11ef
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x16e
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "len\0"
	.byte	0x1
	.word	0x16e
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x24
	.secrel32	LASF4
	.byte	0x1
	.word	0x16e
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x25
	.ascii "cnt\0"
	.byte	0x1
	.word	0x170
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x25
	.ascii "rem\0"
	.byte	0x1
	.word	0x170
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x27
	.ascii "tga_fd_draw_pixel\0"
	.byte	0x1
	.word	0x162
	.long	LFB27
	.long	LFE27-LFB27
	.uleb128 0x1
	.byte	0x9c
	.long	0x123f
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x162
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "cnt\0"
	.byte	0x1
	.word	0x162
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x24
	.secrel32	LASF4
	.byte	0x1
	.word	0x162
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x27
	.ascii "tga_draw_hline\0"
	.byte	0x1
	.word	0x155
	.long	LFB26
	.long	LFE26-LFB26
	.uleb128 0x1
	.byte	0x9c
	.long	0x1299
	.uleb128 0x23
	.ascii "x\0"
	.byte	0x1
	.word	0x155
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "y\0"
	.byte	0x1
	.word	0x155
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x23
	.ascii "cnt\0"
	.byte	0x1
	.word	0x155
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x24
	.secrel32	LASF4
	.byte	0x1
	.word	0x155
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.byte	0
	.uleb128 0x27
	.ascii "tga_fd_draw_bg_pixel\0"
	.byte	0x1
	.word	0x149
	.long	LFB25
	.long	LFE25-LFB25
	.uleb128 0x1
	.byte	0x9c
	.long	0x12dd
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x149
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "cnt\0"
	.byte	0x1
	.word	0x149
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x27
	.ascii "tga_fd_draw_fg_pixel\0"
	.byte	0x1
	.word	0x13e
	.long	LFB24
	.long	LFE24-LFB24
	.uleb128 0x1
	.byte	0x9c
	.long	0x1321
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x13e
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "cnt\0"
	.byte	0x1
	.word	0x13e
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x22
	.ascii "tga_fd_get_signed_bits\0"
	.byte	0x1
	.word	0x138
	.long	0x102
	.long	LFB23
	.long	LFE23-LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0x136b
	.uleb128 0x23
	.ascii "t\0"
	.byte	0x1
	.word	0x138
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "cnt\0"
	.byte	0x1
	.word	0x138
	.long	0x102
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x28
	.ascii "tga_fd_get_unsigned_bits\0"
	.byte	0x1
	.word	0x115
	.long	0x109
	.long	LFB22
	.long	LFE22-LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x13d9
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x115
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "cnt\0"
	.byte	0x1
	.word	0x115
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x25
	.ascii "val\0"
	.byte	0x1
	.word	0x117
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x25
	.ascii "bit_pos\0"
	.byte	0x1
	.word	0x118
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x29
	.ascii "tga_fd_inc\0"
	.byte	0x1
	.word	0x108
	.long	LFB21
	.long	LFE21-LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0x1411
	.uleb128 0x23
	.ascii "f\0"
	.byte	0x1
	.word	0x108
	.long	0x10f9
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "x\0"
	.byte	0x1
	.word	0x10a
	.long	0x109
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x2a
	.ascii "tga_get_glyph_data\0"
	.byte	0x1
	.byte	0xdc
	.long	0xc84
	.long	LFB20
	.long	LFE20-LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x1457
	.uleb128 0x2b
	.secrel32	LASF2
	.byte	0x1
	.byte	0xdc
	.long	0x152
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x21
	.ascii "font\0"
	.byte	0x1
	.byte	0xde
	.long	0xc84
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x2c
	.ascii "tga_set_font\0"
	.byte	0x1
	.byte	0xac
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x1485
	.uleb128 0x2d
	.ascii "font\0"
	.byte	0x1
	.byte	0xac
	.long	0xc84
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x2e
	.ascii "tga_save\0"
	.byte	0x1
	.byte	0x6f
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x14bc
	.uleb128 0x2d
	.ascii "name\0"
	.byte	0x1
	.byte	0x6f
	.long	0x6cb
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x21
	.ascii "fp\0"
	.byte	0x1
	.byte	0x71
	.long	0x14bc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc61
	.uleb128 0x2e
	.ascii "tga_write_word\0"
	.byte	0x1
	.byte	0x69
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x14ff
	.uleb128 0x2d
	.ascii "fp\0"
	.byte	0x1
	.byte	0x69
	.long	0x14bc
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.ascii "word\0"
	.byte	0x1
	.byte	0x69
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2e
	.ascii "tga_write_byte\0"
	.byte	0x1
	.byte	0x64
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x153c
	.uleb128 0x2d
	.ascii "fp\0"
	.byte	0x1
	.byte	0x64
	.long	0x14bc
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.ascii "byte\0"
	.byte	0x1
	.byte	0x64
	.long	0x152
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2c
	.ascii "tga_set_pixel\0"
	.byte	0x1
	.byte	0x57
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x15a4
	.uleb128 0x2d
	.ascii "x\0"
	.byte	0x1
	.byte	0x57
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2d
	.ascii "y\0"
	.byte	0x1
	.byte	0x57
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2d
	.ascii "r\0"
	.byte	0x1
	.byte	0x57
	.long	0x152
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2d
	.ascii "g\0"
	.byte	0x1
	.byte	0x57
	.long	0x152
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2d
	.ascii "b\0"
	.byte	0x1
	.byte	0x57
	.long	0x152
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x21
	.ascii "p\0"
	.byte	0x1
	.byte	0x59
	.long	0xc84
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2f
	.ascii "tga_init\0"
	.byte	0x1
	.byte	0x48
	.long	0x102
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x15db
	.uleb128 0x2d
	.ascii "w\0"
	.byte	0x1
	.byte	0x48
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2d
	.ascii "h\0"
	.byte	0x1
	.byte	0x48
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x30
	.ascii "tga_get_char_height\0"
	.byte	0x1
	.byte	0x43
	.long	0x102
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x30
	.ascii "tga_get_char_width\0"
	.byte	0x1
	.byte	0x3e
	.long	0x102
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
	.uleb128 0x5
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
	.uleb128 0x27
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
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
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
	.uleb128 0x30
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
	.ascii "glyph_data\0"
LASF4:
	.ascii "is_foreground\0"
LASF1:
	.ascii "is_hints\0"
LASF0:
	.ascii "_on_exit_args\0"
LASF2:
	.ascii "encoding\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
