	.file	"fd.c"
	.text
Ltext0:
	.globl	_fd_init
	.def	_fd_init;	.scl	2;	.type	32;	.endef
_fd_init:
LFB0:
	.file 1 "fd.c"
	.loc 1 14 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 15 0
	movl	8(%ebp), %eax
	movl	$1, 8(%eax)
	.loc 1 16 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.globl	_fd_set_font
	.def	_fd_set_font;	.scl	2;	.type	32;	.endef
_fd_set_font:
LFB1:
	.loc 1 19 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 20 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 40(%eax)
	.loc 1 21 0
	addl	$1, 12(%ebp)
	.loc 1 22 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 41(%eax)
	.loc 1 23 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 42(%eax)
	.loc 1 24 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 43(%eax)
	.loc 1 25 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 44(%eax)
	.loc 1 26 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 45(%eax)
	.loc 1 27 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 46(%eax)
	.loc 1 28 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 47(%eax)
	.loc 1 29 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 48(%eax)
	.loc 1 30 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %edx
	movl	8(%ebp), %eax
	movb	%dl, 49(%eax)
	.loc 1 31 0
	addl	$1, 12(%ebp)
	.loc 1 32 0
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movb	%dl, 50(%eax)
	.loc 1 33 0
	addl	$1, 12(%ebp)
	.loc 1 35 0
	addl	$1, 12(%ebp)
	.loc 1 36 0
	addl	$1, 12(%ebp)
	.loc 1 37 0
	addl	$1, 12(%ebp)
	.loc 1 38 0
	addl	$1, 12(%ebp)
	.loc 1 40 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	8(%ebp), %eax
	movl	%edx, 52(%eax)
	.loc 1 41 0
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	sall	$8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 52(%eax)
	.loc 1 42 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %ecx
	movl	8(%ebp), %eax
	movl	52(%eax), %edx
	movzbl	%cl, %eax
	orl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 52(%eax)
	.loc 1 43 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	8(%ebp), %eax
	movl	%edx, 56(%eax)
	.loc 1 44 0
	movl	8(%ebp), %eax
	movl	56(%eax), %eax
	sall	$8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 56(%eax)
	.loc 1 45 0
	movl	12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 12(%ebp)
	movzbl	(%eax), %ecx
	movl	8(%ebp), %eax
	movl	56(%eax), %edx
	movzbl	%cl, %eax
	orl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 56(%eax)
	.loc 1 47 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 60(%eax)
	.loc 1 48 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE1:
	.globl	_fd_get_glyph_data
	.def	_fd_get_glyph_data;	.scl	2;	.type	32;	.endef
_fd_get_glyph_data:
LFB2:
	.loc 1 51 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	12(%ebp), %eax
	movb	%al, -20(%ebp)
	.loc 1 53 0
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 54 0
	cmpb	$96, -20(%ebp)
	jbe	L4
	.loc 1 56 0
	movl	8(%ebp), %eax
	movl	56(%eax), %eax
	addl	%eax, -4(%ebp)
	jmp	L5
L4:
	.loc 1 58 0
	cmpb	$64, -20(%ebp)
	jbe	L5
	.loc 1 60 0
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	addl	%eax, -4(%ebp)
L5:
	.loc 1 65 0
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	L11
	.loc 1 67 0
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-20(%ebp), %al
	jne	L8
	.loc 1 69 0
	movl	-4(%ebp), %eax
	jmp	L9
L8:
	.loc 1 71 0
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	addl	%eax, -4(%ebp)
	.loc 1 65 0
	jmp	L5
L11:
	.loc 1 66 0
	nop
	.loc 1 73 0
	movl	$0, %eax
L9:
	.loc 1 74 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2:
	.globl	_fd_get_unsigned_bits
	.def	_fd_get_unsigned_bits;	.scl	2;	.type	32;	.endef
_fd_get_unsigned_bits:
LFB3:
	.loc 1 77 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 79 0
	movl	8(%ebp), %eax
	movl	32(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 82 0
	movl	8(%ebp), %eax
	movl	36(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 83 0
	movl	$8, -12(%ebp)
	.loc 1 84 0
	movl	-8(%ebp), %eax
	subl	%eax, -12(%ebp)
	.loc 1 86 0
	movl	12(%ebp), %eax
	addl	%eax, -8(%ebp)
	.loc 1 87 0
	movl	12(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jb	L13
	.loc 1 89 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 90 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	8(%ebp), %eax
	movl	%edx, 36(%eax)
	.loc 1 92 0
	movl	8(%ebp), %eax
	movl	36(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	orl	%eax, -4(%ebp)
	.loc 1 94 0
	subl	$8, -8(%ebp)
	.loc 1 95 0
	movl	8(%ebp), %eax
	movl	36(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%eax, %ecx
	shrl	%cl, %edx
	movl	8(%ebp), %eax
	movl	%edx, 36(%eax)
	jmp	L14
L13:
	.loc 1 99 0
	movl	8(%ebp), %eax
	movl	36(%eax), %edx
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	shrl	%cl, %edx
	movl	8(%ebp), %eax
	movl	%edx, 36(%eax)
L14:
	.loc 1 101 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	andl	%eax, -4(%ebp)
	.loc 1 102 0
	movl	8(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, 32(%eax)
	.loc 1 103 0
	movl	-4(%ebp), %eax
	.loc 1 104 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE3:
	.globl	_fd_get_signed_bits
	.def	_fd_get_signed_bits;	.scl	2;	.type	32;	.endef
_fd_get_signed_bits:
LFB4:
	.loc 1 107 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$8, %esp
	.cfi_offset 3, -12
	.loc 1 108 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	12(%ebp), %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	sarl	%eax
	subl	%eax, %edx
	movl	%edx, %eax
	.loc 1 109 0
	addl	$8, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE4:
	.globl	_fd_draw_pixel
	.def	_fd_draw_pixel;	.scl	2;	.type	32;	.endef
_fd_draw_pixel:
LFB5:
	.loc 1 115 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 116 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	L19
	.loc 1 116 0 is_stmt 0 discriminator 1
	cmpl	$0, 16(%ebp)
	je	L21
L19:
	.loc 1 118 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	leal	(%edx,%eax), %ecx
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	addl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	call	_tga_draw_hline
	jmp	L18
L21:
	.loc 1 117 0
	nop
L18:
	.loc 1 119 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE5:
	.globl	_fd_decode_len
	.def	_fd_decode_len;	.scl	2;	.type	32;	.endef
_fd_decode_len:
LFB6:
	.loc 1 122 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 124 0
	movl	12(%ebp), %eax
	movl	%eax, -12(%ebp)
L25:
	.loc 1 127 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 128 0
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	subl	%eax, -16(%ebp)
	.loc 1 129 0
	movl	-12(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jb	L27
	.loc 1 131 0
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_draw_pixel
	.loc 1 132 0
	movl	-16(%ebp), %eax
	subl	%eax, -12(%ebp)
	.loc 1 133 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 134 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 16(%eax)
	.loc 1 127 0
	jmp	L25
L27:
	.loc 1 130 0
	nop
	.loc 1 136 0
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_draw_pixel
	.loc 1 137 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	-12(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 1 138 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE6:
	.globl	_fd_decode
	.def	_fd_decode;	.scl	2;	.type	32;	.endef
_fd_decode:
LFB7:
	.loc 1 148 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 1 151 0
	movl	$0, -12(%ebp)
	.loc 1 153 0
	movl	8(%ebp), %eax
	movl	$0, 32(%eax)
	.loc 1 155 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 156 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 158 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	8(%ebp), %eax
	movl	%edx, 36(%eax)
	.loc 1 160 0
	movl	8(%ebp), %eax
	movzbl	43(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 20(%eax)
	.loc 1 161 0
	movl	8(%ebp), %eax
	movzbl	44(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_unsigned_bits
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 1 162 0
	movl	8(%ebp), %eax
	movzbl	45(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_signed_bits
	movl	%eax, -16(%ebp)
	.loc 1 163 0
	movl	8(%ebp), %eax
	movzbl	46(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_signed_bits
	movl	%eax, -20(%ebp)
	.loc 1 164 0
	movl	8(%ebp), %eax
	movzbl	47(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_signed_bits
	movl	%eax, -12(%ebp)
	.loc 1 166 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	je	L29
	.loc 1 169 0
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-16(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 170 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	subl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 171 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	-20(%ebp), %eax
	subl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 173 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 174 0
	movl	8(%ebp), %eax
	movl	$0, 16(%eax)
L32:
	.loc 1 178 0
	movl	8(%ebp), %eax
	movzbl	41(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_unsigned_bits
	movl	%eax, -24(%ebp)
	.loc 1 179 0
	movl	8(%ebp), %eax
	movzbl	42(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_unsigned_bits
	movl	%eax, -28(%ebp)
L30:
	.loc 1 182 0 discriminator 1
	movl	$0, 8(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_decode_len
	.loc 1 183 0 discriminator 1
	movl	$1, 8(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_decode_len
	.loc 1 184 0 discriminator 1
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_unsigned_bits
	testl	%eax, %eax
	jne	L30
	.loc 1 186 0
	movl	8(%ebp), %eax
	movl	16(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	cmpl	%eax, %edx
	jnb	L34
	.loc 1 178 0
	jmp	L32
L34:
	.loc 1 187 0
	nop
L29:
	.loc 1 190 0
	movl	-12(%ebp), %eax
	.loc 1 191 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE7:
	.globl	_fd_draw_glyph
	.def	_fd_draw_glyph;	.scl	2;	.type	32;	.endef
_fd_draw_glyph:
LFB8:
	.loc 1 194 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	20(%ebp), %eax
	movb	%al, -28(%ebp)
	.loc 1 195 0
	movl	$0, -12(%ebp)
	.loc 1 196 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 197 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 4(%eax)
	.loc 1 198 0
	movzbl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_get_glyph_data
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 199 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	testl	%eax, %eax
	je	L36
	.loc 1 201 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_decode
	movl	%eax, -12(%ebp)
L36:
	.loc 1 203 0
	movl	-12(%ebp), %eax
	.loc 1 204 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE8:
	.globl	_fd_draw_string
	.def	_fd_draw_string;	.scl	2;	.type	32;	.endef
_fd_draw_string:
LFB9:
	.loc 1 207 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 208 0
	movl	$0, -12(%ebp)
	.loc 1 209 0
	jmp	L39
L40:
	.loc 1 211 0
	movl	20(%ebp), %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	12(%ebp), %ecx
	movl	-12(%ebp), %edx
	addl	%ecx, %edx
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_fd_draw_glyph
	addl	%eax, -12(%ebp)
	.loc 1 212 0
	addl	$1, 20(%ebp)
L39:
	.loc 1 209 0
	movl	20(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L40
	.loc 1 214 0
	movl	-12(%ebp), %eax
	.loc 1 215 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE9:
Letext0:
	.file 2 "/usr/include/machine/_default_types.h"
	.file 3 "/usr/include/sys/_stdint.h"
	.file 4 "fd.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x6c7
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "fd.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.ascii "__int8_t\0"
	.byte	0x2
	.byte	0x29
	.long	0x97
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0x2
	.ascii "__uint8_t\0"
	.byte	0x2
	.byte	0x2b
	.long	0xb7
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
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
	.long	0x87
	.uleb128 0x2
	.ascii "uint8_t\0"
	.byte	0x3
	.byte	0x18
	.long	0xa6
	.uleb128 0x4
	.long	0x13b
	.uleb128 0x5
	.ascii "fd_struct\0"
	.byte	0x40
	.byte	0x4
	.byte	0x8
	.long	0x343
	.uleb128 0x6
	.ascii "target_x\0"
	.byte	0x4
	.byte	0xa
	.long	0xf2
	.byte	0
	.uleb128 0x6
	.ascii "target_y\0"
	.byte	0x4
	.byte	0xb
	.long	0xf2
	.byte	0x4
	.uleb128 0x6
	.ascii "is_transparent\0"
	.byte	0x4
	.byte	0xc
	.long	0xf2
	.byte	0x8
	.uleb128 0x6
	.ascii "x\0"
	.byte	0x4
	.byte	0xe
	.long	0xf2
	.byte	0xc
	.uleb128 0x6
	.ascii "y\0"
	.byte	0x4
	.byte	0xf
	.long	0xf2
	.byte	0x10
	.uleb128 0x6
	.ascii "glyph_width\0"
	.byte	0x4
	.byte	0x10
	.long	0xf2
	.byte	0x14
	.uleb128 0x6
	.ascii "glyph_height\0"
	.byte	0x4
	.byte	0x11
	.long	0xf2
	.byte	0x18
	.uleb128 0x6
	.ascii "decode_ptr\0"
	.byte	0x4
	.byte	0x13
	.long	0x343
	.byte	0x1c
	.uleb128 0x6
	.ascii "decode_bit_pos\0"
	.byte	0x4
	.byte	0x14
	.long	0xf2
	.byte	0x20
	.uleb128 0x6
	.ascii "decode_byte\0"
	.byte	0x4
	.byte	0x15
	.long	0xf2
	.byte	0x24
	.uleb128 0x6
	.ascii "glyph_cnt\0"
	.byte	0x4
	.byte	0x17
	.long	0x13b
	.byte	0x28
	.uleb128 0x6
	.ascii "bits_per_0\0"
	.byte	0x4
	.byte	0x18
	.long	0x13b
	.byte	0x29
	.uleb128 0x6
	.ascii "bits_per_1\0"
	.byte	0x4
	.byte	0x19
	.long	0x13b
	.byte	0x2a
	.uleb128 0x6
	.ascii "bits_per_char_width\0"
	.byte	0x4
	.byte	0x1a
	.long	0x13b
	.byte	0x2b
	.uleb128 0x6
	.ascii "bits_per_char_height\0"
	.byte	0x4
	.byte	0x1b
	.long	0x13b
	.byte	0x2c
	.uleb128 0x6
	.ascii "bits_per_char_x\0"
	.byte	0x4
	.byte	0x1c
	.long	0x13b
	.byte	0x2d
	.uleb128 0x6
	.ascii "bits_per_char_y\0"
	.byte	0x4
	.byte	0x1d
	.long	0x13b
	.byte	0x2e
	.uleb128 0x6
	.ascii "bits_per_delta_x\0"
	.byte	0x4
	.byte	0x1e
	.long	0x13b
	.byte	0x2f
	.uleb128 0x6
	.ascii "char_width\0"
	.byte	0x4
	.byte	0x1f
	.long	0x13b
	.byte	0x30
	.uleb128 0x6
	.ascii "char_height\0"
	.byte	0x4
	.byte	0x20
	.long	0x13b
	.byte	0x31
	.uleb128 0x6
	.ascii "char_descent\0"
	.byte	0x4
	.byte	0x21
	.long	0x13b
	.byte	0x32
	.uleb128 0x6
	.ascii "capital_a_pos\0"
	.byte	0x4
	.byte	0x22
	.long	0xf2
	.byte	0x34
	.uleb128 0x6
	.ascii "small_a_pos\0"
	.byte	0x4
	.byte	0x23
	.long	0xf2
	.byte	0x38
	.uleb128 0x6
	.ascii "font\0"
	.byte	0x4
	.byte	0x25
	.long	0x349
	.byte	0x3c
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x14a
	.uleb128 0x7
	.byte	0x4
	.long	0x13b
	.uleb128 0x2
	.ascii "fd_t\0"
	.byte	0x4
	.byte	0x28
	.long	0x14f
	.uleb128 0x3
	.byte	0xc
	.byte	0x4
	.ascii "long double\0"
	.uleb128 0x8
	.ascii "fd_draw_string\0"
	.byte	0x1
	.byte	0xce
	.long	0xf2
	.long	LFB9
	.long	LFE9-LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x3cd
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0xce
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "x\0"
	.byte	0x1
	.byte	0xce
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x9
	.ascii "y\0"
	.byte	0x1
	.byte	0xce
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x9
	.ascii "s\0"
	.byte	0x1
	.byte	0xce
	.long	0x3d3
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0xa
	.ascii "dx\0"
	.byte	0x1
	.byte	0xd0
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x34f
	.uleb128 0x7
	.byte	0x4
	.long	0x3e1
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0x4
	.long	0x3d9
	.uleb128 0x8
	.ascii "fd_draw_glyph\0"
	.byte	0x1
	.byte	0xc1
	.long	0xf2
	.long	LFB8
	.long	LFE8-LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x44a
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0xc1
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "x\0"
	.byte	0x1
	.byte	0xc1
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x9
	.ascii "y\0"
	.byte	0x1
	.byte	0xc1
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0xb
	.secrel32	LASF0
	.byte	0x1
	.byte	0xc1
	.long	0x13b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xa
	.ascii "dx\0"
	.byte	0x1
	.byte	0xc3
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x8
	.ascii "fd_decode\0"
	.byte	0x1
	.byte	0x93
	.long	0xf2
	.long	LFB7
	.long	LFE7-LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x4b2
	.uleb128 0x9
	.ascii "f\0"
	.byte	0x1
	.byte	0x93
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xa
	.ascii "a\0"
	.byte	0x1
	.byte	0x95
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xa
	.ascii "b\0"
	.byte	0x1
	.byte	0x95
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xa
	.ascii "x\0"
	.byte	0x1
	.byte	0x96
	.long	0xeb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xa
	.ascii "y\0"
	.byte	0x1
	.byte	0x96
	.long	0xeb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.ascii "d\0"
	.byte	0x1
	.byte	0x97
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xc
	.ascii "fd_decode_len\0"
	.byte	0x1
	.byte	0x79
	.long	LFB6
	.long	LFE6-LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x517
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0x79
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "len\0"
	.byte	0x1
	.byte	0x79
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0xb
	.secrel32	LASF1
	.byte	0x1
	.byte	0x79
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0xa
	.ascii "cnt\0"
	.byte	0x1
	.byte	0x7b
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.ascii "rem\0"
	.byte	0x1
	.byte	0x7b
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xc
	.ascii "fd_draw_pixel\0"
	.byte	0x1
	.byte	0x72
	.long	LFB5
	.long	LFE5-LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x55f
	.uleb128 0x9
	.ascii "f\0"
	.byte	0x1
	.byte	0x72
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "cnt\0"
	.byte	0x1
	.byte	0x72
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0xb
	.secrel32	LASF1
	.byte	0x1
	.byte	0x72
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x8
	.ascii "fd_get_signed_bits\0"
	.byte	0x1
	.byte	0x6a
	.long	0xeb
	.long	LFB4
	.long	LFE4-LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x5a3
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0x6a
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "cnt\0"
	.byte	0x1
	.byte	0x6a
	.long	0xeb
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0xd
	.ascii "fd_get_unsigned_bits\0"
	.byte	0x1
	.byte	0x4c
	.long	0xf2
	.long	LFB3
	.long	LFE3-LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x61b
	.uleb128 0x9
	.ascii "f\0"
	.byte	0x1
	.byte	0x4c
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "cnt\0"
	.byte	0x1
	.byte	0x4c
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0xa
	.ascii "val\0"
	.byte	0x1
	.byte	0x4e
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0xa
	.ascii "bit_pos\0"
	.byte	0x1
	.byte	0x4f
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xa
	.ascii "rem_bits\0"
	.byte	0x1
	.byte	0x50
	.long	0xf2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0xd
	.ascii "fd_get_glyph_data\0"
	.byte	0x1
	.byte	0x32
	.long	0x349
	.long	LFB2
	.long	LFE2-LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x66d
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0x32
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xb
	.secrel32	LASF0
	.byte	0x1
	.byte	0x32
	.long	0x13b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.ascii "font\0"
	.byte	0x1
	.byte	0x35
	.long	0x349
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0xe
	.ascii "fd_set_font\0"
	.byte	0x1
	.byte	0x12
	.long	LFB1
	.long	LFE1-LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x6a7
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0x12
	.long	0x3cd
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.ascii "font\0"
	.byte	0x1
	.byte	0x12
	.long	0x349
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0xf
	.ascii "fd_init\0"
	.byte	0x1
	.byte	0xd
	.long	LFB0
	.long	LFE0-LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x9
	.ascii "fd\0"
	.byte	0x1
	.byte	0xd
	.long	0x3cd
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
LASF0:
	.ascii "encoding\0"
LASF1:
	.ascii "is_foreground\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_tga_draw_hline;	.scl	2;	.type	32;	.endef
