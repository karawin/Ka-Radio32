	.file	"bdf_glyph.c"
	.text
Ltext0:
	.globl	_bg_Open
	.def	_bg_Open;	.scl	2;	.type	32;	.endef
_bg_Open:
LFB12:
	.file 1 "bdf_glyph.c"
	.loc 1 11 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 14 0
	movl	$96, (%esp)
	call	_malloc
	movl	%eax, -12(%ebp)
	.loc 1 15 0
	cmpl	$0, -12(%ebp)
	je	L2
	.loc 1 17 0
	movl	-12(%ebp), %eax
	movl	$0, 4(%eax)
	.loc 1 18 0
	movl	-12(%ebp), %eax
	movl	$-1, 8(%eax)
	.loc 1 19 0
	movl	-12(%ebp), %eax
	movl	$0, 40(%eax)
	.loc 1 20 0
	movl	-12(%ebp), %eax
	movl	$0, 52(%eax)
	.loc 1 21 0
	movl	-12(%ebp), %eax
	movl	$0, 56(%eax)
	.loc 1 22 0
	movl	-12(%ebp), %eax
	movl	$0, 60(%eax)
	.loc 1 23 0
	movl	-12(%ebp), %eax
	movl	$0, 36(%eax)
	.loc 1 25 0
	movl	-12(%ebp), %eax
	jmp	L3
L2:
	.loc 1 27 0
	movl	$0, %eax
L3:
	.loc 1 28 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_bg_Close
	.def	_bg_Close;	.scl	2;	.type	32;	.endef
_bg_Close:
LFB13:
	.loc 1 32 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 33 0
	movl	8(%ebp), %eax
	movl	40(%eax), %eax
	testl	%eax, %eax
	je	L5
	.loc 1 34 0
	movl	8(%ebp), %eax
	movl	40(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L5:
	.loc 1 35 0
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	testl	%eax, %eax
	je	L6
	.loc 1 36 0
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L6:
	.loc 1 37 0
	movl	8(%ebp), %eax
	movl	$0, 40(%eax)
	.loc 1 38 0
	movl	8(%ebp), %eax
	movl	$0, 52(%eax)
	.loc 1 39 0
	movl	8(%ebp), %eax
	movl	$0, 56(%eax)
	.loc 1 40 0
	movl	8(%ebp), %eax
	movl	$0, 60(%eax)
	.loc 1 41 0
	movl	8(%ebp), %eax
	movl	$0, 64(%eax)
	.loc 1 42 0
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	.loc 1 43 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_free
	.loc 1 44 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.def	_bg_extend_target_data;	.scl	3;	.type	32;	.endef
_bg_extend_target_data:
LFB14:
	.loc 1 47 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 48 0
	movl	$16, -20(%ebp)
	.loc 1 51 0
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	testl	%eax, %eax
	jne	L8
	.loc 1 53 0
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, -16(%ebp)
	.loc 1 54 0
	movl	8(%ebp), %eax
	movl	$0, 56(%eax)
	jmp	L9
L8:
	.loc 1 58 0
	movl	8(%ebp), %eax
	movl	56(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_realloc
	movl	%eax, -16(%ebp)
L9:
	.loc 1 60 0
	cmpl	$0, -16(%ebp)
	jne	L10
	.loc 1 61 0
	movl	$0, %eax
	jmp	L11
L10:
	.loc 1 62 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 52(%eax)
	.loc 1 63 0
	movl	8(%ebp), %eax
	movl	56(%eax), %eax
	movl	%eax, -12(%ebp)
	jmp	L12
L13:
	.loc 1 64 0 discriminator 3
	movl	8(%ebp), %eax
	movl	52(%eax), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 63 0 discriminator 3
	addl	$1, -12(%ebp)
L12:
	.loc 1 63 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	56(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	cmpl	-12(%ebp), %eax
	jg	L13
	.loc 1 65 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	56(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 56(%eax)
	.loc 1 66 0
	movl	$1, %eax
L11:
	.loc 1 67 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.globl	_bg_AddTargetData
	.def	_bg_AddTargetData;	.scl	2;	.type	32;	.endef
_bg_AddTargetData:
LFB15:
	.loc 1 70 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	movb	%al, -12(%ebp)
	.loc 1 71 0
	jmp	L15
L17:
	.loc 1 72 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_extend_target_data
	testl	%eax, %eax
	jne	L15
	.loc 1 73 0
	movl	$-1, %eax
	jmp	L16
L15:
	.loc 1 71 0
	movl	8(%ebp), %eax
	movl	56(%eax), %edx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	cmpl	%eax, %edx
	jle	L17
	.loc 1 74 0
	movl	8(%ebp), %eax
	movl	52(%eax), %edx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	addl	%eax, %edx
	movzbl	-12(%ebp), %eax
	movb	%al, (%edx)
	.loc 1 75 0
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 60(%eax)
	.loc 1 76 0
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	subl	$1, %eax
L16:
	.loc 1 77 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_bg_ClearTargetData
	.def	_bg_ClearTargetData;	.scl	2;	.type	32;	.endef
_bg_ClearTargetData:
LFB16:
	.loc 1 80 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 82 0
	movl	$0, -4(%ebp)
	jmp	L19
L20:
	.loc 1 83 0 discriminator 3
	movl	8(%ebp), %eax
	movl	52(%eax), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 82 0 discriminator 3
	addl	$1, -4(%ebp)
L19:
	.loc 1 82 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	56(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	L20
	.loc 1 84 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	$0, 60(%eax)
	.loc 1 85 0
	movl	8(%ebp), %eax
	movl	$0, 64(%eax)
	.loc 1 86 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.section .rdata,"dr"
LC0:
	.ascii "val < (1<<cnt)\0"
LC1:
	.ascii "bdf_glyph.c\0"
	.text
	.globl	_bg_AddTargetBits
	.def	_bg_AddTargetBits;	.scl	2;	.type	32;	.endef
_bg_AddTargetBits:
LFB17:
	.loc 1 97 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	.loc 1 99 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	cmpl	16(%ebp), %eax
	ja	L23
	.loc 1 99 0 is_stmt 0 discriminator 1
	movl	$LC0, 12(%esp)
	movl	$___func__.3328, 8(%esp)
	movl	$99, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert_func
L25:
	.loc 1 102 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_extend_target_data
	testl	%eax, %eax
	jne	L23
	.loc 1 103 0
	movl	$0, %eax
	jmp	L24
L23:
	.loc 1 101 0
	movl	8(%ebp), %eax
	movl	56(%eax), %edx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	addl	$1, %eax
	cmpl	%eax, %edx
	jle	L25
	.loc 1 105 0
	movl	8(%ebp), %eax
	movl	52(%eax), %edx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	52(%eax), %ecx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	addl	%ecx, %eax
	movzbl	(%eax), %eax
	movb	%al, -9(%ebp)
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	movl	16(%ebp), %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	orb	-9(%ebp), %al
	movb	%al, (%edx)
	.loc 1 107 0
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	cmpl	$7, %eax
	jbe	L26
	.loc 1 109 0
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 60(%eax)
	.loc 1 111 0
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	movl	$8, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %ecx
	shrl	%cl, 16(%ebp)
	.loc 1 112 0
	movl	8(%ebp), %eax
	movl	52(%eax), %edx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	addl	%edx, %eax
	movl	16(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 114 0
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 64(%eax)
	.loc 1 115 0
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	leal	-8(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 64(%eax)
	jmp	L27
L26:
	.loc 1 119 0
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 64(%eax)
L27:
	.loc 1 122 0
	movl	$1, %eax
L24:
	.loc 1 123 0
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.globl	_bg_FlushTargetBits
	.def	_bg_FlushTargetBits;	.scl	2;	.type	32;	.endef
_bg_FlushTargetBits:
LFB18:
	.loc 1 126 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 127 0
	jmp	L29
L31:
	.loc 1 128 0
	movl	$0, 8(%esp)
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L29
	.loc 1 129 0
	movl	$0, %eax
	jmp	L30
L29:
	.loc 1 127 0
	movl	8(%ebp), %eax
	movl	64(%eax), %eax
	testl	%eax, %eax
	jne	L31
	.loc 1 130 0
	movl	$1, %eax
L30:
	.loc 1 131 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.globl	_bg_SetBitmapSizeInBytes
	.def	_bg_SetBitmapSizeInBytes;	.scl	2;	.type	32;	.endef
_bg_SetBitmapSizeInBytes:
LFB19:
	.loc 1 135 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 136 0
	movl	8(%ebp), %eax
	movl	40(%eax), %eax
	testl	%eax, %eax
	je	L33
	.loc 1 137 0
	movl	8(%ebp), %eax
	movl	40(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L33:
	.loc 1 138 0
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 40(%eax)
	.loc 1 139 0
	movl	8(%ebp), %eax
	movl	40(%eax), %eax
	testl	%eax, %eax
	jne	L34
	.loc 1 140 0
	movl	$0, %eax
	jmp	L35
L34:
	.loc 1 141 0
	movl	8(%ebp), %eax
	movl	40(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	_memset
	.loc 1 142 0
	movl	$1, %eax
L35:
	.loc 1 143 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.globl	_bg_SetBitmapSize
	.def	_bg_SetBitmapSize;	.scl	2;	.type	32;	.endef
_bg_SetBitmapSize:
LFB20:
	.loc 1 146 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 147 0
	movl	12(%ebp), %eax
	imull	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_SetBitmapSizeInBytes
	.loc 1 148 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.section .rdata,"dr"
LC2:
	.ascii "x < bg->bitmap_width\0"
LC3:
	.ascii "y < bg->bitmap_height\0"
LC4:
	.ascii "x >= 0\0"
LC5:
	.ascii "y >= 0\0"
	.text
	.globl	_bg_SetBitmapPixel
	.def	_bg_SetBitmapPixel;	.scl	2;	.type	32;	.endef
_bg_SetBitmapPixel:
LFB21:
	.loc 1 151 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 152 0
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	cmpl	12(%ebp), %eax
	jg	L39
	.loc 1 152 0 is_stmt 0 discriminator 1
	movl	$LC2, 12(%esp)
	movl	$___func__.3353, 8(%esp)
	movl	$152, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert_func
L39:
	.loc 1 153 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	cmpl	16(%ebp), %eax
	jg	L40
	.loc 1 153 0 is_stmt 0 discriminator 1
	movl	$LC3, 12(%esp)
	movl	$___func__.3353, 8(%esp)
	movl	$153, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert_func
L40:
	.loc 1 154 0 is_stmt 1
	cmpl	$0, 12(%ebp)
	jns	L41
	.loc 1 154 0 is_stmt 0 discriminator 1
	movl	$LC4, 12(%esp)
	movl	$___func__.3353, 8(%esp)
	movl	$154, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert_func
L41:
	.loc 1 155 0 is_stmt 1
	cmpl	$0, 16(%ebp)
	jns	L42
	.loc 1 155 0 is_stmt 0 discriminator 1
	movl	$LC5, 12(%esp)
	movl	$___func__.3353, 8(%esp)
	movl	$155, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert_func
L42:
	.loc 1 156 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	40(%eax), %edx
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	imull	16(%ebp), %eax
	movl	%eax, %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	addl	%edx, %eax
	movl	20(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 157 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.globl	_bg_GetBitmapPixel
	.def	_bg_GetBitmapPixel;	.scl	2;	.type	32;	.endef
_bg_GetBitmapPixel:
LFB22:
	.loc 1 160 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 161 0
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	cmpl	12(%ebp), %eax
	jg	L44
	.loc 1 162 0
	movl	$0, %eax
	jmp	L45
L44:
	.loc 1 164 0
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	cmpl	16(%ebp), %eax
	jg	L46
	.loc 1 165 0
	movl	$0, %eax
	jmp	L45
L46:
	.loc 1 166 0
	cmpl	$0, 12(%ebp)
	jns	L47
	.loc 1 167 0
	movl	$0, %eax
	jmp	L45
L47:
	.loc 1 168 0
	cmpl	$0, 16(%ebp)
	jns	L48
	.loc 1 169 0
	movl	$0, %eax
	jmp	L45
L48:
	.loc 1 171 0
	movl	8(%ebp), %eax
	movl	40(%eax), %edx
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	imull	16(%ebp), %eax
	movl	%eax, %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
L45:
	.loc 1 172 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.globl	_bg_GetBBXPixel
	.def	_bg_GetBBXPixel;	.scl	2;	.type	32;	.endef
_bg_GetBBXPixel:
LFB23:
	.loc 1 179 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$44, %esp
	.loc 1 187 0
	movl	8(%ebp), %eax
	movl	36(%eax), %eax
	addl	%eax, 12(%ebp)
	.loc 1 190 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 191 0
	movl	8(%ebp), %eax
	movl	32(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 192 0
	movl	8(%ebp), %eax
	movl	28(%eax), %edx
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	.loc 1 193 0
	movl	8(%ebp), %eax
	movl	32(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -16(%ebp)
	.loc 1 195 0
	movl	12(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jge	L50
	.loc 1 196 0
	movl	$0, %eax
	jmp	L51
L50:
	.loc 1 197 0
	movl	12(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jl	L52
	.loc 1 198 0
	movl	$0, %eax
	jmp	L51
L52:
	.loc 1 200 0
	movl	16(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jge	L53
	.loc 1 201 0
	movl	$0, %eax
	jmp	L51
L53:
	.loc 1 202 0
	movl	16(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jl	L54
	.loc 1 203 0
	movl	$0, %eax
	jmp	L51
L54:
	.loc 1 205 0
	movl	12(%ebp), %eax
	subl	-4(%ebp), %eax
	movl	%eax, -20(%ebp)
	.loc 1 206 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	leal	-1(%eax), %edx
	movl	16(%ebp), %eax
	subl	-8(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -24(%ebp)
	.loc 1 208 0
	movl	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBitmapPixel
L51:
	.loc 1 210 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE23:
	.section .rdata,"dr"
	.align 4
LC6:
	.ascii "Encoding %ld, mapped to %ld, w=%ld, h=%ld, x=%ld, y=%ld\12\0"
LC7:
	.ascii "%03d \0"
LC8:
	.ascii " .\0"
LC9:
	.ascii " #\0"
	.text
	.globl	_bg_ShowBitmap
	.def	_bg_ShowBitmap;	.scl	2;	.type	32;	.endef
_bg_ShowBitmap:
LFB24:
	.loc 1 214 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	.loc 1 217 0
	cmpl	$0, 12(%ebp)
	jne	L56
	.loc 1 218 0
	movl	8(%ebp), %eax
	addl	$20, %eax
	movl	%eax, 12(%ebp)
L56:
	.loc 1 220 0
	movl	8(%ebp), %eax
	movl	32(%eax), %edi
	movl	8(%ebp), %eax
	movl	28(%eax), %esi
	movl	8(%ebp), %eax
	movl	24(%eax), %ebx
	movl	8(%ebp), %eax
	movl	20(%eax), %ecx
	movl	8(%ebp), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%edi, 24(%esp)
	movl	%esi, 20(%esp)
	movl	%ebx, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$LC6, (%esp)
	call	_printf
	.loc 1 221 0
	movl	12(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	addl	%edx, %eax
	subl	$1, %eax
	movl	%eax, -32(%ebp)
	jmp	L57
L62:
	.loc 1 223 0
	movl	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC7, (%esp)
	call	_printf
	.loc 1 224 0
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -28(%ebp)
	jmp	L58
L61:
	.loc 1 226 0
	movl	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBBXPixel
	testl	%eax, %eax
	jne	L59
	.loc 1 228 0
	movl	$LC8, (%esp)
	call	_printf
	jmp	L60
L59:
	.loc 1 232 0
	movl	$LC9, (%esp)
	call	_printf
L60:
	.loc 1 224 0 discriminator 2
	addl	$1, -28(%ebp)
L58:
	.loc 1 224 0 is_stmt 0 discriminator 1
	movl	12(%ebp), %eax
	movl	8(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	cmpl	-28(%ebp), %eax
	jg	L61
	.loc 1 236 0 is_stmt 1 discriminator 2
	movl	$10, (%esp)
	call	_putchar
	.loc 1 221 0 discriminator 2
	subl	$1, -32(%ebp)
L57:
	.loc 1 221 0 is_stmt 0 discriminator 1
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	-32(%ebp), %eax
	jle	L62
	.loc 1 238 0 is_stmt 1
	nop
	addl	$60, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
	.globl	_bg_IsColZero
	.def	_bg_IsColZero;	.scl	2;	.type	32;	.endef
_bg_IsColZero:
LFB25:
	.loc 1 241 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$28, %esp
	.loc 1 243 0
	movl	$0, -4(%ebp)
	jmp	L64
L67:
	.loc 1 245 0
	movl	-4(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBitmapPixel
	testl	%eax, %eax
	je	L65
	.loc 1 246 0
	movl	$0, %eax
	jmp	L66
L65:
	.loc 1 243 0 discriminator 2
	addl	$1, -4(%ebp)
L64:
	.loc 1 243 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	L67
	.loc 1 248 0 is_stmt 1
	movl	$1, %eax
L66:
	.loc 1 249 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE25:
	.globl	_bg_IsRowZero
	.def	_bg_IsRowZero;	.scl	2;	.type	32;	.endef
_bg_IsRowZero:
LFB26:
	.loc 1 252 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$28, %esp
	.loc 1 254 0
	movl	$0, -4(%ebp)
	jmp	L69
L72:
	.loc 1 256 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBitmapPixel
	testl	%eax, %eax
	je	L70
	.loc 1 257 0
	movl	$0, %eax
	jmp	L71
L70:
	.loc 1 254 0 discriminator 2
	addl	$1, -4(%ebp)
L69:
	.loc 1 254 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	L72
	.loc 1 259 0 is_stmt 1
	movl	$1, %eax
L71:
	.loc 1 260 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.globl	_bg_DeleteFirstCol
	.def	_bg_DeleteFirstCol;	.scl	2;	.type	32;	.endef
_bg_DeleteFirstCol:
LFB27:
	.loc 1 263 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 265 0
	movl	$0, -16(%ebp)
	jmp	L74
L77:
	.loc 1 266 0
	movl	$0, -12(%ebp)
	jmp	L75
L76:
	.loc 1 268 0 discriminator 3
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBitmapPixel
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_SetBitmapPixel
	.loc 1 266 0 discriminator 3
	addl	$1, -12(%ebp)
L75:
	.loc 1 266 0 is_stmt 0 discriminator 1
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	cmpl	%eax, %edx
	jl	L76
	.loc 1 265 0 is_stmt 1 discriminator 2
	addl	$1, -16(%ebp)
L74:
	.loc 1 265 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	cmpl	-16(%ebp), %eax
	jg	L77
	.loc 1 270 0 is_stmt 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE27:
	.globl	_bg_DeleteFirstRow
	.def	_bg_DeleteFirstRow;	.scl	2;	.type	32;	.endef
_bg_DeleteFirstRow:
LFB28:
	.loc 1 273 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 275 0
	movl	$0, -16(%ebp)
	jmp	L79
L82:
	.loc 1 276 0
	movl	$0, -12(%ebp)
	jmp	L80
L81:
	.loc 1 278 0 discriminator 3
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBitmapPixel
	movl	%eax, 12(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_SetBitmapPixel
	.loc 1 276 0 discriminator 3
	addl	$1, -12(%ebp)
L80:
	.loc 1 276 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	44(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L81
	.loc 1 275 0 is_stmt 1 discriminator 2
	addl	$1, -16(%ebp)
L79:
	.loc 1 275 0 is_stmt 0 discriminator 1
	movl	-16(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	cmpl	%eax, %edx
	jl	L82
	.loc 1 280 0 is_stmt 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE28:
	.globl	_bg_ReduceGlyph
	.def	_bg_ReduceGlyph;	.scl	2;	.type	32;	.endef
_bg_ReduceGlyph:
LFB29:
	.loc 1 283 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 292 0
	jmp	L84
L87:
	.loc 1 294 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_IsColZero
	testl	%eax, %eax
	je	L100
	.loc 1 296 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 20(%eax)
L84:
	.loc 1 292 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	jg	L87
	jmp	L88
L100:
	.loc 1 295 0
	nop
	.loc 1 299 0
	jmp	L88
L91:
	.loc 1 301 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_IsRowZero
	testl	%eax, %eax
	je	L101
	.loc 1 303 0
	movl	8(%ebp), %eax
	movl	32(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 32(%eax)
	.loc 1 304 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
L88:
	.loc 1 299 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	testl	%eax, %eax
	jg	L91
	jmp	L92
L101:
	.loc 1 302 0
	nop
	.loc 1 307 0
	jmp	L92
L95:
	.loc 1 309 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_IsColZero
	testl	%eax, %eax
	je	L102
	.loc 1 311 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_DeleteFirstCol
	.loc 1 312 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 1 313 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 20(%eax)
L92:
	.loc 1 307 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	jg	L95
	jmp	L96
L102:
	.loc 1 310 0
	nop
	.loc 1 316 0
	jmp	L96
L99:
	.loc 1 318 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_IsRowZero
	testl	%eax, %eax
	je	L103
	.loc 1 320 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_DeleteFirstRow
	.loc 1 321 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
L96:
	.loc 1 316 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	testl	%eax, %eax
	jg	L99
	.loc 1 324 0
	jmp	L98
L103:
	.loc 1 319 0
	nop
L98:
	.loc 1 324 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE29:
	.globl	_bg_Max
	.def	_bg_Max;	.scl	2;	.type	32;	.endef
_bg_Max:
LFB30:
	.loc 1 330 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$48, %esp
	.loc 1 331 0
	movl	$0, -4(%ebp)
	.loc 1 343 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	movl	%eax, -24(%ebp)
	.loc 1 344 0
	movl	8(%ebp), %eax
	movl	32(%eax), %eax
	movl	%eax, -28(%ebp)
	.loc 1 345 0
	movl	8(%ebp), %eax
	movl	28(%eax), %edx
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -32(%ebp)
	.loc 1 346 0
	movl	8(%ebp), %eax
	movl	32(%eax), %edx
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -36(%ebp)
	.loc 1 349 0
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 350 0
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 351 0
	movl	12(%ebp), %eax
	movl	8(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	.loc 1 352 0
	movl	12(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -20(%ebp)
	.loc 1 355 0
	movl	-8(%ebp), %eax
	cmpl	-24(%ebp), %eax
	jle	L105
	.loc 1 357 0
	movl	-24(%ebp), %eax
	movl	%eax, -8(%ebp)
	.loc 1 358 0
	movl	$3, -4(%ebp)
L105:
	.loc 1 361 0
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	-8(%ebp), %eax
	jge	L106
	.loc 1 363 0
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 364 0
	movl	$3, -4(%ebp)
L106:
	.loc 1 368 0
	movl	-12(%ebp), %eax
	cmpl	-32(%ebp), %eax
	jge	L107
	.loc 1 370 0
	movl	$1, -4(%ebp)
	.loc 1 371 0
	movl	-32(%ebp), %eax
	movl	%eax, -12(%ebp)
L107:
	.loc 1 374 0
	movl	-16(%ebp), %eax
	cmpl	-28(%ebp), %eax
	jle	L108
	.loc 1 376 0
	movl	$4, -4(%ebp)
	.loc 1 377 0
	movl	-28(%ebp), %eax
	movl	%eax, -16(%ebp)
L108:
	.loc 1 379 0
	movl	-20(%ebp), %eax
	cmpl	-36(%ebp), %eax
	jge	L109
	.loc 1 381 0
	movl	$2, -4(%ebp)
	.loc 1 382 0
	movl	-36(%ebp), %eax
	movl	%eax, -20(%ebp)
L109:
	.loc 1 386 0
	movl	12(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, 8(%eax)
	.loc 1 387 0
	movl	12(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 12(%eax)
	.loc 1 388 0
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	-12(%ebp), %edx
	subl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 389 0
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	movl	-20(%ebp), %edx
	subl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 391 0
	movl	-4(%ebp), %eax
	.loc 1 392 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE30:
	.section .rdata,"dr"
	.align 4
___func__.3328:
	.ascii "bg_AddTargetBits\0"
	.align 4
___func__.3353:
	.ascii "bg_SetBitmapPixel\0"
	.text
Letext0:
	.file 2 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 3 "/usr/include/machine/_default_types.h"
	.file 4 "/usr/include/sys/lock.h"
	.file 5 "/usr/include/sys/_types.h"
	.file 6 "/usr/include/sys/reent.h"
	.file 7 "/usr/include/stdlib.h"
	.file 8 "/usr/include/sys/_stdint.h"
	.file 9 "bdf_glyph.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x14c0
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_glyph.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.ascii "size_t\0"
	.byte	0x2
	.byte	0xd8
	.long	0x9c
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
	.long	0x109
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
	.long	0x165
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
	.long	0xc9
	.uleb128 0x2
	.ascii "_fpos_t\0"
	.byte	0x5
	.byte	0x72
	.long	0x167
	.uleb128 0x2
	.ascii "_fpos64_t\0"
	.byte	0x5
	.byte	0x78
	.long	0x173
	.uleb128 0x2
	.ascii "_ssize_t\0"
	.byte	0x5
	.byte	0x91
	.long	0xc2
	.uleb128 0x5
	.ascii "wint_t\0"
	.byte	0x2
	.word	0x165
	.long	0x9c
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0xa6
	.long	0x1e6
	.uleb128 0x7
	.ascii "__wch\0"
	.byte	0x5
	.byte	0xa8
	.long	0x1b3
	.uleb128 0x7
	.ascii "__wchb\0"
	.byte	0x5
	.byte	0xa9
	.long	0x1e6
	.byte	0
	.uleb128 0x8
	.long	0x109
	.long	0x1f6
	.uleb128 0x9
	.long	0x1f6
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
	.long	0x22b
	.uleb128 0xb
	.ascii "__count\0"
	.byte	0x5
	.byte	0xa5
	.long	0xc2
	.byte	0
	.uleb128 0xb
	.ascii "__value\0"
	.byte	0x5
	.byte	0xaa
	.long	0x1c2
	.byte	0x4
	.byte	0
	.uleb128 0x2
	.ascii "_mbstate_t\0"
	.byte	0x5
	.byte	0xab
	.long	0x202
	.uleb128 0x2
	.ascii "_flock_t\0"
	.byte	0x5
	.byte	0xaf
	.long	0x156
	.uleb128 0xc
	.byte	0x4
	.long	0x253
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0xd
	.long	0x253
	.uleb128 0x2
	.ascii "__ULong\0"
	.byte	0x6
	.byte	0x16
	.long	0x141
	.uleb128 0xe
	.ascii "_Bigint\0"
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.long	0x2cf
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x31
	.long	0x2cf
	.byte	0
	.uleb128 0xb
	.ascii "_k\0"
	.byte	0x6
	.byte	0x32
	.long	0xc2
	.byte	0x4
	.uleb128 0xb
	.ascii "_maxwds\0"
	.byte	0x6
	.byte	0x32
	.long	0xc2
	.byte	0x8
	.uleb128 0xb
	.ascii "_sign\0"
	.byte	0x6
	.byte	0x32
	.long	0xc2
	.byte	0xc
	.uleb128 0xb
	.ascii "_wds\0"
	.byte	0x6
	.byte	0x32
	.long	0xc2
	.byte	0x10
	.uleb128 0xb
	.ascii "_x\0"
	.byte	0x6
	.byte	0x33
	.long	0x2d5
	.byte	0x14
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x26f
	.uleb128 0x8
	.long	0x260
	.long	0x2e5
	.uleb128 0x9
	.long	0x1f6
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__tm\0"
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.long	0x393
	.uleb128 0xb
	.ascii "__tm_sec\0"
	.byte	0x6
	.byte	0x39
	.long	0xc2
	.byte	0
	.uleb128 0xb
	.ascii "__tm_min\0"
	.byte	0x6
	.byte	0x3a
	.long	0xc2
	.byte	0x4
	.uleb128 0xb
	.ascii "__tm_hour\0"
	.byte	0x6
	.byte	0x3b
	.long	0xc2
	.byte	0x8
	.uleb128 0xb
	.ascii "__tm_mday\0"
	.byte	0x6
	.byte	0x3c
	.long	0xc2
	.byte	0xc
	.uleb128 0xb
	.ascii "__tm_mon\0"
	.byte	0x6
	.byte	0x3d
	.long	0xc2
	.byte	0x10
	.uleb128 0xb
	.ascii "__tm_year\0"
	.byte	0x6
	.byte	0x3e
	.long	0xc2
	.byte	0x14
	.uleb128 0xb
	.ascii "__tm_wday\0"
	.byte	0x6
	.byte	0x3f
	.long	0xc2
	.byte	0x18
	.uleb128 0xb
	.ascii "__tm_yday\0"
	.byte	0x6
	.byte	0x40
	.long	0xc2
	.byte	0x1c
	.uleb128 0xb
	.ascii "__tm_isdst\0"
	.byte	0x6
	.byte	0x41
	.long	0xc2
	.byte	0x20
	.byte	0
	.uleb128 0xf
	.secrel32	LASF0
	.word	0x108
	.byte	0x6
	.byte	0x4a
	.long	0x3e8
	.uleb128 0xb
	.ascii "_fnargs\0"
	.byte	0x6
	.byte	0x4b
	.long	0x3e8
	.byte	0
	.uleb128 0xb
	.ascii "_dso_handle\0"
	.byte	0x6
	.byte	0x4c
	.long	0x3e8
	.byte	0x80
	.uleb128 0x10
	.ascii "_fntypes\0"
	.byte	0x6
	.byte	0x4e
	.long	0x260
	.word	0x100
	.uleb128 0x10
	.ascii "_is_cxa\0"
	.byte	0x6
	.byte	0x51
	.long	0x260
	.word	0x104
	.byte	0
	.uleb128 0x8
	.long	0x165
	.long	0x3f8
	.uleb128 0x9
	.long	0x1f6
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.ascii "_atexit\0"
	.word	0x190
	.byte	0x6
	.byte	0x5d
	.long	0x43e
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x5e
	.long	0x43e
	.byte	0
	.uleb128 0xb
	.ascii "_ind\0"
	.byte	0x6
	.byte	0x5f
	.long	0xc2
	.byte	0x4
	.uleb128 0xb
	.ascii "_fns\0"
	.byte	0x6
	.byte	0x61
	.long	0x444
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF0
	.byte	0x6
	.byte	0x62
	.long	0x393
	.byte	0x88
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x3f8
	.uleb128 0x8
	.long	0x454
	.long	0x454
	.uleb128 0x9
	.long	0x1f6
	.byte	0x1f
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x45a
	.uleb128 0x13
	.uleb128 0xe
	.ascii "__sbuf\0"
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.long	0x487
	.uleb128 0xb
	.ascii "_base\0"
	.byte	0x6
	.byte	0x76
	.long	0x487
	.byte	0
	.uleb128 0xb
	.ascii "_size\0"
	.byte	0x6
	.byte	0x77
	.long	0xc2
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x109
	.uleb128 0x14
	.long	0x1a3
	.long	0x4ab
	.uleb128 0x15
	.long	0x4ab
	.uleb128 0x15
	.long	0x165
	.uleb128 0x15
	.long	0x24d
	.uleb128 0x15
	.long	0x8e
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x4b6
	.uleb128 0xd
	.long	0x4ab
	.uleb128 0x16
	.ascii "_reent\0"
	.word	0x440
	.byte	0x6
	.word	0x239
	.long	0x655
	.uleb128 0x17
	.ascii "_errno\0"
	.byte	0x6
	.word	0x23b
	.long	0xc2
	.byte	0
	.uleb128 0x17
	.ascii "_stdin\0"
	.byte	0x6
	.word	0x240
	.long	0x8da
	.byte	0x4
	.uleb128 0x17
	.ascii "_stdout\0"
	.byte	0x6
	.word	0x240
	.long	0x8da
	.byte	0x8
	.uleb128 0x17
	.ascii "_stderr\0"
	.byte	0x6
	.word	0x240
	.long	0x8da
	.byte	0xc
	.uleb128 0x17
	.ascii "_inc\0"
	.byte	0x6
	.word	0x242
	.long	0xc2
	.byte	0x10
	.uleb128 0x17
	.ascii "_emergency\0"
	.byte	0x6
	.word	0x243
	.long	0xb80
	.byte	0x14
	.uleb128 0x17
	.ascii "_unspecified_locale_info\0"
	.byte	0x6
	.word	0x246
	.long	0xc2
	.byte	0x30
	.uleb128 0x17
	.ascii "_locale\0"
	.byte	0x6
	.word	0x247
	.long	0xb9c
	.byte	0x34
	.uleb128 0x17
	.ascii "__sdidinit\0"
	.byte	0x6
	.word	0x249
	.long	0xc2
	.byte	0x38
	.uleb128 0x17
	.ascii "__cleanup\0"
	.byte	0x6
	.word	0x24b
	.long	0xbad
	.byte	0x3c
	.uleb128 0x17
	.ascii "_result\0"
	.byte	0x6
	.word	0x24e
	.long	0x2cf
	.byte	0x40
	.uleb128 0x17
	.ascii "_result_k\0"
	.byte	0x6
	.word	0x24f
	.long	0xc2
	.byte	0x44
	.uleb128 0x17
	.ascii "_p5s\0"
	.byte	0x6
	.word	0x250
	.long	0x2cf
	.byte	0x48
	.uleb128 0x17
	.ascii "_freelist\0"
	.byte	0x6
	.word	0x251
	.long	0xbb3
	.byte	0x4c
	.uleb128 0x17
	.ascii "_cvtlen\0"
	.byte	0x6
	.word	0x254
	.long	0xc2
	.byte	0x50
	.uleb128 0x17
	.ascii "_cvtbuf\0"
	.byte	0x6
	.word	0x255
	.long	0x24d
	.byte	0x54
	.uleb128 0x17
	.ascii "_new\0"
	.byte	0x6
	.word	0x278
	.long	0xb57
	.byte	0x58
	.uleb128 0x18
	.ascii "_atexit\0"
	.byte	0x6
	.word	0x27c
	.long	0x43e
	.word	0x148
	.uleb128 0x18
	.ascii "_atexit0\0"
	.byte	0x6
	.word	0x27d
	.long	0x3f8
	.word	0x14c
	.uleb128 0x18
	.ascii "_sig_func\0"
	.byte	0x6
	.word	0x281
	.long	0xbc4
	.word	0x2dc
	.uleb128 0x18
	.ascii "__sglue\0"
	.byte	0x6
	.word	0x286
	.long	0x896
	.word	0x2e0
	.uleb128 0x18
	.ascii "__sf\0"
	.byte	0x6
	.word	0x288
	.long	0xbd0
	.word	0x2f0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x48d
	.uleb128 0x14
	.long	0x1a3
	.long	0x679
	.uleb128 0x15
	.long	0x4ab
	.uleb128 0x15
	.long	0x165
	.uleb128 0x15
	.long	0x679
	.uleb128 0x15
	.long	0x8e
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x25b
	.uleb128 0xc
	.byte	0x4
	.long	0x65b
	.uleb128 0x14
	.long	0x183
	.long	0x6a3
	.uleb128 0x15
	.long	0x4ab
	.uleb128 0x15
	.long	0x165
	.uleb128 0x15
	.long	0x183
	.uleb128 0x15
	.long	0xc2
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x685
	.uleb128 0x14
	.long	0xc2
	.long	0x6bd
	.uleb128 0x15
	.long	0x4ab
	.uleb128 0x15
	.long	0x165
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x6a9
	.uleb128 0x8
	.long	0x109
	.long	0x6d3
	.uleb128 0x9
	.long	0x1f6
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.long	0x109
	.long	0x6e3
	.uleb128 0x9
	.long	0x1f6
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__sFILE64\0"
	.byte	0x70
	.byte	0x6
	.byte	0xef
	.long	0x863
	.uleb128 0xb
	.ascii "_p\0"
	.byte	0x6
	.byte	0xf0
	.long	0x487
	.byte	0
	.uleb128 0xb
	.ascii "_r\0"
	.byte	0x6
	.byte	0xf1
	.long	0xc2
	.byte	0x4
	.uleb128 0xb
	.ascii "_w\0"
	.byte	0x6
	.byte	0xf2
	.long	0xc2
	.byte	0x8
	.uleb128 0xb
	.ascii "_flags\0"
	.byte	0x6
	.byte	0xf3
	.long	0x11a
	.byte	0xc
	.uleb128 0xb
	.ascii "_file\0"
	.byte	0x6
	.byte	0xf4
	.long	0x11a
	.byte	0xe
	.uleb128 0xb
	.ascii "_bf\0"
	.byte	0x6
	.byte	0xf5
	.long	0x45b
	.byte	0x10
	.uleb128 0xb
	.ascii "_lbfsize\0"
	.byte	0x6
	.byte	0xf6
	.long	0xc2
	.byte	0x18
	.uleb128 0xb
	.ascii "_data\0"
	.byte	0x6
	.byte	0xf8
	.long	0x4ab
	.byte	0x1c
	.uleb128 0xb
	.ascii "_cookie\0"
	.byte	0x6
	.byte	0xfb
	.long	0x165
	.byte	0x20
	.uleb128 0xb
	.ascii "_read\0"
	.byte	0x6
	.byte	0xfd
	.long	0x655
	.byte	0x24
	.uleb128 0xb
	.ascii "_write\0"
	.byte	0x6
	.byte	0xff
	.long	0x67f
	.byte	0x28
	.uleb128 0x17
	.ascii "_seek\0"
	.byte	0x6
	.word	0x102
	.long	0x6a3
	.byte	0x2c
	.uleb128 0x17
	.ascii "_close\0"
	.byte	0x6
	.word	0x103
	.long	0x6bd
	.byte	0x30
	.uleb128 0x17
	.ascii "_ub\0"
	.byte	0x6
	.word	0x106
	.long	0x45b
	.byte	0x34
	.uleb128 0x17
	.ascii "_up\0"
	.byte	0x6
	.word	0x107
	.long	0x487
	.byte	0x3c
	.uleb128 0x17
	.ascii "_ur\0"
	.byte	0x6
	.word	0x108
	.long	0xc2
	.byte	0x40
	.uleb128 0x17
	.ascii "_ubuf\0"
	.byte	0x6
	.word	0x10b
	.long	0x6c3
	.byte	0x44
	.uleb128 0x17
	.ascii "_nbuf\0"
	.byte	0x6
	.word	0x10c
	.long	0x6d3
	.byte	0x47
	.uleb128 0x17
	.ascii "_lb\0"
	.byte	0x6
	.word	0x10f
	.long	0x45b
	.byte	0x48
	.uleb128 0x17
	.ascii "_blksize\0"
	.byte	0x6
	.word	0x112
	.long	0xc2
	.byte	0x50
	.uleb128 0x17
	.ascii "_flags2\0"
	.byte	0x6
	.word	0x113
	.long	0xc2
	.byte	0x54
	.uleb128 0x17
	.ascii "_offset\0"
	.byte	0x6
	.word	0x115
	.long	0x173
	.byte	0x58
	.uleb128 0x17
	.ascii "_seek64\0"
	.byte	0x6
	.word	0x116
	.long	0x881
	.byte	0x60
	.uleb128 0x17
	.ascii "_lock\0"
	.byte	0x6
	.word	0x119
	.long	0x23d
	.byte	0x64
	.uleb128 0x17
	.ascii "_mbstate\0"
	.byte	0x6
	.word	0x11b
	.long	0x22b
	.byte	0x68
	.byte	0
	.uleb128 0x14
	.long	0x192
	.long	0x881
	.uleb128 0x15
	.long	0x4ab
	.uleb128 0x15
	.long	0x165
	.uleb128 0x15
	.long	0x192
	.uleb128 0x15
	.long	0xc2
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x863
	.uleb128 0x5
	.ascii "__FILE\0"
	.byte	0x6
	.word	0x11d
	.long	0x6e3
	.uleb128 0x19
	.ascii "_glue\0"
	.byte	0xc
	.byte	0x6
	.word	0x123
	.long	0x8d4
	.uleb128 0x17
	.ascii "_next\0"
	.byte	0x6
	.word	0x125
	.long	0x8d4
	.byte	0
	.uleb128 0x17
	.ascii "_niobs\0"
	.byte	0x6
	.word	0x126
	.long	0xc2
	.byte	0x4
	.uleb128 0x17
	.ascii "_iobs\0"
	.byte	0x6
	.word	0x127
	.long	0x8da
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x896
	.uleb128 0xc
	.byte	0x4
	.long	0x887
	.uleb128 0x19
	.ascii "_rand48\0"
	.byte	0xe
	.byte	0x6
	.word	0x13f
	.long	0x91e
	.uleb128 0x17
	.ascii "_seed\0"
	.byte	0x6
	.word	0x140
	.long	0x91e
	.byte	0
	.uleb128 0x17
	.ascii "_mult\0"
	.byte	0x6
	.word	0x141
	.long	0x91e
	.byte	0x6
	.uleb128 0x17
	.ascii "_add\0"
	.byte	0x6
	.word	0x142
	.long	0xac
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.long	0xac
	.long	0x92e
	.uleb128 0x9
	.long	0x1f6
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.word	0x259
	.long	0xadb
	.uleb128 0x17
	.ascii "_unused_rand\0"
	.byte	0x6
	.word	0x25b
	.long	0x9c
	.byte	0
	.uleb128 0x17
	.ascii "_strtok_last\0"
	.byte	0x6
	.word	0x25c
	.long	0x24d
	.byte	0x4
	.uleb128 0x17
	.ascii "_asctime_buf\0"
	.byte	0x6
	.word	0x25d
	.long	0xadb
	.byte	0x8
	.uleb128 0x17
	.ascii "_localtime_buf\0"
	.byte	0x6
	.word	0x25e
	.long	0x2e5
	.byte	0x24
	.uleb128 0x17
	.ascii "_gamma_signgam\0"
	.byte	0x6
	.word	0x25f
	.long	0xc2
	.byte	0x48
	.uleb128 0x17
	.ascii "_rand_next\0"
	.byte	0x6
	.word	0x260
	.long	0x127
	.byte	0x50
	.uleb128 0x17
	.ascii "_r48\0"
	.byte	0x6
	.word	0x261
	.long	0x8e0
	.byte	0x58
	.uleb128 0x17
	.ascii "_mblen_state\0"
	.byte	0x6
	.word	0x262
	.long	0x22b
	.byte	0x68
	.uleb128 0x17
	.ascii "_mbtowc_state\0"
	.byte	0x6
	.word	0x263
	.long	0x22b
	.byte	0x70
	.uleb128 0x17
	.ascii "_wctomb_state\0"
	.byte	0x6
	.word	0x264
	.long	0x22b
	.byte	0x78
	.uleb128 0x17
	.ascii "_l64a_buf\0"
	.byte	0x6
	.word	0x265
	.long	0xaeb
	.byte	0x80
	.uleb128 0x17
	.ascii "_signal_buf\0"
	.byte	0x6
	.word	0x266
	.long	0xafb
	.byte	0x88
	.uleb128 0x17
	.ascii "_getdate_err\0"
	.byte	0x6
	.word	0x267
	.long	0xc2
	.byte	0xa0
	.uleb128 0x17
	.ascii "_mbrlen_state\0"
	.byte	0x6
	.word	0x268
	.long	0x22b
	.byte	0xa4
	.uleb128 0x17
	.ascii "_mbrtowc_state\0"
	.byte	0x6
	.word	0x269
	.long	0x22b
	.byte	0xac
	.uleb128 0x17
	.ascii "_mbsrtowcs_state\0"
	.byte	0x6
	.word	0x26a
	.long	0x22b
	.byte	0xb4
	.uleb128 0x17
	.ascii "_wcrtomb_state\0"
	.byte	0x6
	.word	0x26b
	.long	0x22b
	.byte	0xbc
	.uleb128 0x17
	.ascii "_wcsrtombs_state\0"
	.byte	0x6
	.word	0x26c
	.long	0x22b
	.byte	0xc4
	.uleb128 0x17
	.ascii "_h_errno\0"
	.byte	0x6
	.word	0x26d
	.long	0xc2
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.long	0x253
	.long	0xaeb
	.uleb128 0x9
	.long	0x1f6
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.long	0x253
	.long	0xafb
	.uleb128 0x9
	.long	0x1f6
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.long	0x253
	.long	0xb0b
	.uleb128 0x9
	.long	0x1f6
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.word	0x272
	.long	0xb37
	.uleb128 0x17
	.ascii "_nextf\0"
	.byte	0x6
	.word	0x275
	.long	0xb37
	.byte	0
	.uleb128 0x17
	.ascii "_nmalloc\0"
	.byte	0x6
	.word	0x276
	.long	0xb47
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.long	0x487
	.long	0xb47
	.uleb128 0x9
	.long	0x1f6
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.long	0x9c
	.long	0xb57
	.uleb128 0x9
	.long	0x1f6
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.word	0x257
	.long	0xb80
	.uleb128 0x1c
	.ascii "_reent\0"
	.byte	0x6
	.word	0x26e
	.long	0x92e
	.uleb128 0x1c
	.ascii "_unused\0"
	.byte	0x6
	.word	0x277
	.long	0xb0b
	.byte	0
	.uleb128 0x8
	.long	0x253
	.long	0xb90
	.uleb128 0x9
	.long	0x1f6
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.ascii "__locale_t\0"
	.uleb128 0xc
	.byte	0x4
	.long	0xb90
	.uleb128 0x1e
	.long	0xbad
	.uleb128 0x15
	.long	0x4ab
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xba2
	.uleb128 0xc
	.byte	0x4
	.long	0x2cf
	.uleb128 0x1e
	.long	0xbc4
	.uleb128 0x15
	.long	0xc2
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xbca
	.uleb128 0xc
	.byte	0x4
	.long	0xbb9
	.uleb128 0x8
	.long	0x887
	.long	0xbe0
	.uleb128 0x9
	.long	0x1f6
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.ascii "_impure_ptr\0"
	.byte	0x6
	.word	0x307
	.long	0x4ab
	.uleb128 0x1f
	.ascii "_global_impure_ptr\0"
	.byte	0x6
	.word	0x308
	.long	0x4b1
	.uleb128 0x20
	.ascii "suboptarg\0"
	.byte	0x7
	.byte	0x63
	.long	0x24d
	.uleb128 0x2
	.ascii "uint8_t\0"
	.byte	0x8
	.byte	0x18
	.long	0xf8
	.uleb128 0x2
	.ascii "bf_t\0"
	.byte	0x9
	.byte	0x9
	.long	0xc3b
	.uleb128 0x1d
	.ascii "_bdf_font_struct\0"
	.uleb128 0xe
	.ascii "_bbx_struct\0"
	.byte	0x10
	.byte	0x9
	.byte	0xc
	.long	0xc8a
	.uleb128 0xb
	.ascii "w\0"
	.byte	0x9
	.byte	0xe
	.long	0x167
	.byte	0
	.uleb128 0xb
	.ascii "h\0"
	.byte	0x9
	.byte	0xf
	.long	0x167
	.byte	0x4
	.uleb128 0xb
	.ascii "x\0"
	.byte	0x9
	.byte	0x10
	.long	0x167
	.byte	0x8
	.uleb128 0xb
	.ascii "y\0"
	.byte	0x9
	.byte	0x11
	.long	0x167
	.byte	0xc
	.byte	0
	.uleb128 0x2
	.ascii "bbx_t\0"
	.byte	0x9
	.byte	0x13
	.long	0xc4d
	.uleb128 0xe
	.ascii "_bdf_glyph_struct\0"
	.byte	0x60
	.byte	0x9
	.byte	0x16
	.long	0xe3f
	.uleb128 0xb
	.ascii "bf\0"
	.byte	0x9
	.byte	0x18
	.long	0xe3f
	.byte	0
	.uleb128 0xb
	.ascii "encoding\0"
	.byte	0x9
	.byte	0x1a
	.long	0x167
	.byte	0x4
	.uleb128 0xb
	.ascii "map_to\0"
	.byte	0x9
	.byte	0x1b
	.long	0x167
	.byte	0x8
	.uleb128 0xb
	.ascii "dwidth_x\0"
	.byte	0x9
	.byte	0x1d
	.long	0x167
	.byte	0xc
	.uleb128 0xb
	.ascii "dwidth_y\0"
	.byte	0x9
	.byte	0x1e
	.long	0x167
	.byte	0x10
	.uleb128 0xb
	.ascii "bbx\0"
	.byte	0x9
	.byte	0x20
	.long	0xc8a
	.byte	0x14
	.uleb128 0xb
	.ascii "shift_x\0"
	.byte	0x9
	.byte	0x21
	.long	0x167
	.byte	0x24
	.uleb128 0xb
	.ascii "bitmap_data\0"
	.byte	0x9
	.byte	0x23
	.long	0xe45
	.byte	0x28
	.uleb128 0xb
	.ascii "bitmap_width\0"
	.byte	0x9
	.byte	0x24
	.long	0xc2
	.byte	0x2c
	.uleb128 0xb
	.ascii "bitmap_height\0"
	.byte	0x9
	.byte	0x25
	.long	0xc2
	.byte	0x30
	.uleb128 0xb
	.ascii "target_data\0"
	.byte	0x9
	.byte	0x2a
	.long	0xe45
	.byte	0x34
	.uleb128 0xb
	.ascii "target_max\0"
	.byte	0x9
	.byte	0x2b
	.long	0xc2
	.byte	0x38
	.uleb128 0xb
	.ascii "target_cnt\0"
	.byte	0x9
	.byte	0x2c
	.long	0xc2
	.byte	0x3c
	.uleb128 0xb
	.ascii "target_bit_pos\0"
	.byte	0x9
	.byte	0x2d
	.long	0xc2
	.byte	0x40
	.uleb128 0xb
	.ascii "rle_bits_per_0\0"
	.byte	0x9
	.byte	0x31
	.long	0x9c
	.byte	0x44
	.uleb128 0xb
	.ascii "rle_bits_per_1\0"
	.byte	0x9
	.byte	0x32
	.long	0x9c
	.byte	0x48
	.uleb128 0xb
	.ascii "rle_is_first\0"
	.byte	0x9
	.byte	0x34
	.long	0xc2
	.byte	0x4c
	.uleb128 0xb
	.ascii "rle_bitcnt\0"
	.byte	0x9
	.byte	0x35
	.long	0x9c
	.byte	0x50
	.uleb128 0xb
	.ascii "rle_last_0\0"
	.byte	0x9
	.byte	0x36
	.long	0x9c
	.byte	0x54
	.uleb128 0xb
	.ascii "rle_last_1\0"
	.byte	0x9
	.byte	0x37
	.long	0x9c
	.byte	0x58
	.uleb128 0xb
	.ascii "width_deviation\0"
	.byte	0x9
	.byte	0x39
	.long	0x167
	.byte	0x5c
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xc2f
	.uleb128 0xc
	.byte	0x4
	.long	0xc20
	.uleb128 0x2
	.ascii "bg_t\0"
	.byte	0x9
	.byte	0x3c
	.long	0xc97
	.uleb128 0x21
	.ascii "bg_Max\0"
	.byte	0x1
	.word	0x149
	.long	0xc2
	.long	LFB30
	.long	LFE30-LFB30
	.uleb128 0x1
	.byte	0x9c
	.long	0xf23
	.uleb128 0x22
	.ascii "bg\0"
	.byte	0x1
	.word	0x149
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x22
	.ascii "max\0"
	.byte	0x1
	.word	0x149
	.long	0xf29
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x23
	.ascii "r\0"
	.byte	0x1
	.word	0x14b
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x24
	.secrel32	LASF1
	.byte	0x1
	.word	0x14e
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x24
	.secrel32	LASF2
	.byte	0x1
	.word	0x14e
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x24
	.secrel32	LASF3
	.byte	0x1
	.word	0x14e
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x24
	.secrel32	LASF4
	.byte	0x1
	.word	0x14e
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x23
	.ascii "max_x0\0"
	.byte	0x1
	.word	0x151
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x23
	.ascii "max_x1\0"
	.byte	0x1
	.word	0x151
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x23
	.ascii "max_y0\0"
	.byte	0x1
	.word	0x151
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x23
	.ascii "max_y1\0"
	.byte	0x1
	.word	0x151
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xe4b
	.uleb128 0xc
	.byte	0x4
	.long	0xc8a
	.uleb128 0x25
	.ascii "bg_ReduceGlyph\0"
	.byte	0x1
	.word	0x11a
	.long	LFB29
	.long	LFE29-LFB29
	.uleb128 0x1
	.byte	0x9c
	.long	0xf5f
	.uleb128 0x22
	.ascii "bg\0"
	.byte	0x1
	.word	0x11a
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x25
	.ascii "bg_DeleteFirstRow\0"
	.byte	0x1
	.word	0x110
	.long	LFB28
	.long	LFE28-LFB28
	.uleb128 0x1
	.byte	0x9c
	.long	0xfac
	.uleb128 0x22
	.ascii "bg\0"
	.byte	0x1
	.word	0x110
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "x\0"
	.byte	0x1
	.word	0x112
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x23
	.ascii "y\0"
	.byte	0x1
	.word	0x112
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x25
	.ascii "bg_DeleteFirstCol\0"
	.byte	0x1
	.word	0x106
	.long	LFB27
	.long	LFE27-LFB27
	.uleb128 0x1
	.byte	0x9c
	.long	0xff9
	.uleb128 0x22
	.ascii "bg\0"
	.byte	0x1
	.word	0x106
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x23
	.ascii "x\0"
	.byte	0x1
	.word	0x108
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x23
	.ascii "y\0"
	.byte	0x1
	.word	0x108
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x26
	.ascii "bg_IsRowZero\0"
	.byte	0x1
	.byte	0xfb
	.long	0xc2
	.long	LFB26
	.long	LFE26-LFB26
	.uleb128 0x1
	.byte	0x9c
	.long	0x1041
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0xfb
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "y\0"
	.byte	0x1
	.byte	0xfb
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x28
	.ascii "x\0"
	.byte	0x1
	.byte	0xfd
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x26
	.ascii "bg_IsColZero\0"
	.byte	0x1
	.byte	0xf0
	.long	0xc2
	.long	LFB25
	.long	LFE25-LFB25
	.uleb128 0x1
	.byte	0x9c
	.long	0x1089
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0xf0
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "x\0"
	.byte	0x1
	.byte	0xf0
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x28
	.ascii "y\0"
	.byte	0x1
	.byte	0xf2
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x29
	.ascii "bg_ShowBitmap\0"
	.byte	0x1
	.byte	0xd5
	.long	LFB24
	.long	LFE24-LFB24
	.uleb128 0x1
	.byte	0x9c
	.long	0x10dc
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0xd5
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "bbx\0"
	.byte	0x1
	.byte	0xd5
	.long	0xf29
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x28
	.ascii "x\0"
	.byte	0x1
	.byte	0xd7
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x28
	.ascii "y\0"
	.byte	0x1
	.byte	0xd7
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x26
	.ascii "bg_GetBBXPixel\0"
	.byte	0x1
	.byte	0xb2
	.long	0xc2
	.long	LFB23
	.long	LFE23-LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0x1184
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0xb2
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "x\0"
	.byte	0x1
	.byte	0xb2
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x27
	.ascii "y\0"
	.byte	0x1
	.byte	0xb2
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2a
	.secrel32	LASF1
	.byte	0x1
	.byte	0xb5
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x2a
	.secrel32	LASF2
	.byte	0x1
	.byte	0xb5
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2a
	.secrel32	LASF3
	.byte	0x1
	.byte	0xb5
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x2a
	.secrel32	LASF4
	.byte	0x1
	.byte	0xb5
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x28
	.ascii "bitmap_x\0"
	.byte	0x1
	.byte	0xb8
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x28
	.ascii "bitmap_y\0"
	.byte	0x1
	.byte	0xb8
	.long	0x167
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x2b
	.ascii "bg_GetBitmapPixel\0"
	.byte	0x1
	.byte	0x9f
	.long	0xc2
	.long	LFB22
	.long	LFE22-LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x11d1
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x9f
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "x\0"
	.byte	0x1
	.byte	0x9f
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x27
	.ascii "y\0"
	.byte	0x1
	.byte	0x9f
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x29
	.ascii "bg_SetBitmapPixel\0"
	.byte	0x1
	.byte	0x96
	.long	LFB21
	.long	LFE21-LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0x1239
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x96
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "x\0"
	.byte	0x1
	.byte	0x96
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x27
	.ascii "y\0"
	.byte	0x1
	.byte	0x96
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x27
	.ascii "value\0"
	.byte	0x1
	.byte	0x96
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x2c
	.secrel32	LASF5
	.long	0x1249
	.uleb128 0x5
	.byte	0x3
	.long	___func__.3353
	.byte	0
	.uleb128 0x8
	.long	0x25b
	.long	0x1249
	.uleb128 0x9
	.long	0x1f6
	.byte	0x11
	.byte	0
	.uleb128 0xd
	.long	0x1239
	.uleb128 0x26
	.ascii "bg_SetBitmapSize\0"
	.byte	0x1
	.byte	0x91
	.long	0xc2
	.long	LFB20
	.long	LFE20-LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x129a
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x91
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "w\0"
	.byte	0x1
	.byte	0x91
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x27
	.ascii "h\0"
	.byte	0x1
	.byte	0x91
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x26
	.ascii "bg_SetBitmapSizeInBytes\0"
	.byte	0x1
	.byte	0x86
	.long	0xc2
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x12e5
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x86
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "bytes\0"
	.byte	0x1
	.byte	0x86
	.long	0x8e
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x26
	.ascii "bg_FlushTargetBits\0"
	.byte	0x1
	.byte	0x7d
	.long	0xc2
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x131b
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x7d
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x26
	.ascii "bg_AddTargetBits\0"
	.byte	0x1
	.byte	0x60
	.long	0xc2
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x137a
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x60
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "cnt\0"
	.byte	0x1
	.byte	0x60
	.long	0x9c
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x27
	.ascii "val\0"
	.byte	0x1
	.byte	0x60
	.long	0x9c
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2c
	.secrel32	LASF5
	.long	0x138a
	.uleb128 0x5
	.byte	0x3
	.long	___func__.3328
	.byte	0
	.uleb128 0x8
	.long	0x25b
	.long	0x138a
	.uleb128 0x9
	.long	0x1f6
	.byte	0x10
	.byte	0
	.uleb128 0xd
	.long	0x137a
	.uleb128 0x2d
	.ascii "bg_ClearTargetData\0"
	.byte	0x1
	.byte	0x4f
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x13cd
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x4f
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x28
	.ascii "i\0"
	.byte	0x1
	.byte	0x51
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x26
	.ascii "bg_AddTargetData\0"
	.byte	0x1
	.byte	0x45
	.long	0xc2
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x1410
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x45
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "data\0"
	.byte	0x1
	.byte	0x45
	.long	0xc20
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2e
	.ascii "bg_extend_target_data\0"
	.byte	0x1
	.byte	0x2e
	.long	0xc2
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x1474
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x2e
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x28
	.ascii "extend\0"
	.byte	0x1
	.byte	0x30
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x28
	.ascii "i\0"
	.byte	0x1
	.byte	0x31
	.long	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x28
	.ascii "ptr\0"
	.byte	0x1
	.byte	0x32
	.long	0x165
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x29
	.ascii "bg_Close\0"
	.byte	0x1
	.byte	0x1f
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x149c
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.byte	0x1f
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x2f
	.ascii "bg_Open\0"
	.byte	0x1
	.byte	0xa
	.long	0xf23
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x28
	.ascii "bg\0"
	.byte	0x1
	.byte	0xc
	.long	0xf23
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
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
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x2a
	.uleb128 0x34
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
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x2e
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
LASF1:
	.ascii "glyph_x0\0"
LASF2:
	.ascii "glyph_x1\0"
LASF3:
	.ascii "glyph_y0\0"
LASF4:
	.ascii "glyph_y1\0"
LASF5:
	.ascii "__func__\0"
LASF0:
	.ascii "_on_exit_args\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_realloc;	.scl	2;	.type	32;	.endef
	.def	___assert_func;	.scl	2;	.type	32;	.endef
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef
