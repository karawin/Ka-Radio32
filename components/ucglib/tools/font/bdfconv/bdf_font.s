	.file	"bdf_font.c"
	.text
Ltext0:
	.globl	_bf_Error
	.def	_bf_Error;	.scl	2;	.type	32;	.endef
_bf_Error:
LFB12:
	.file 1 "bdf_font.c"
	.loc 1 8 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 10 0
	leal	16(%ebp), %eax
	movl	%eax, -12(%ebp)
	.loc 1 11 0
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_vprintf
	.loc 1 12 0
	movl	$10, (%esp)
	call	_putchar
	.loc 1 14 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_bf_Log
	.def	_bf_Log;	.scl	2;	.type	32;	.endef
_bf_Log:
LFB13:
	.loc 1 17 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 19 0
	leal	16(%ebp), %eax
	movl	%eax, -12(%ebp)
	.loc 1 20 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	L4
	.loc 1 22 0
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_vprintf
	.loc 1 23 0
	movl	$10, (%esp)
	call	_putchar
L4:
	.loc 1 26 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.globl	_bf_Open
	.def	_bf_Open;	.scl	2;	.type	32;	.endef
_bf_Open:
LFB14:
	.loc 1 32 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 34 0
	movl	$1188, (%esp)
	call	_malloc
	movl	%eax, -12(%ebp)
	.loc 1 35 0
	cmpl	$0, -12(%ebp)
	je	L6
	.loc 1 37 0
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 38 0
	movl	-12(%ebp), %eax
	movl	$0, 4(%eax)
	.loc 1 39 0
	movl	-12(%ebp), %eax
	movl	$0, 8(%eax)
	.loc 1 40 0
	movl	-12(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 41 0
	movl	-12(%ebp), %eax
	movl	$0, 1092(%eax)
	.loc 1 42 0
	movl	-12(%ebp), %eax
	movl	$0, 1096(%eax)
	.loc 1 43 0
	movl	-12(%ebp), %eax
	movl	$0, 1176(%eax)
	.loc 1 44 0
	movl	-12(%ebp), %eax
	movl	$0, 1180(%eax)
	.loc 1 45 0
	movl	-12(%ebp), %eax
	movl	$0, 1184(%eax)
	.loc 1 46 0
	movl	-12(%ebp), %eax
	movl	$0, 1100(%eax)
	.loc 1 48 0
	movl	-12(%ebp), %eax
	movl	$0, 1124(%eax)
	.loc 1 49 0
	movl	-12(%ebp), %eax
	movl	$0, 1128(%eax)
	.loc 1 50 0
	movl	-12(%ebp), %eax
	movl	$0, 1132(%eax)
	.loc 1 51 0
	movl	-12(%ebp), %eax
	movl	$0, 1136(%eax)
	.loc 1 53 0
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 1104(%eax)
	.loc 1 55 0
	movl	-12(%ebp), %eax
	jmp	L7
L6:
	.loc 1 57 0
	movl	$0, %eax
L7:
	.loc 1 58 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.globl	_bf_Clear
	.def	_bf_Clear;	.scl	2;	.type	32;	.endef
_bf_Clear:
LFB15:
	.loc 1 61 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 63 0
	movl	$0, -12(%ebp)
	jmp	L9
L10:
	.loc 1 65 0 discriminator 3
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	_free
	.loc 1 63 0 discriminator 3
	addl	$1, -12(%ebp)
L9:
	.loc 1 63 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L10
	.loc 1 67 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	$0, 8(%eax)
	.loc 1 69 0
	movl	8(%ebp), %eax
	movl	1092(%eax), %eax
	testl	%eax, %eax
	je	L11
	.loc 1 70 0
	movl	8(%ebp), %eax
	movl	1092(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L11:
	.loc 1 71 0
	movl	8(%ebp), %eax
	movl	$0, 1092(%eax)
	.loc 1 72 0
	movl	8(%ebp), %eax
	movl	1096(%eax), %eax
	testl	%eax, %eax
	je	L12
	.loc 1 73 0
	movl	8(%ebp), %eax
	movl	1096(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L12:
	.loc 1 74 0
	movl	8(%ebp), %eax
	movl	$0, 1096(%eax)
	.loc 1 75 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.globl	_bf_Close
	.def	_bf_Close;	.scl	2;	.type	32;	.endef
_bf_Close:
LFB16:
	.loc 1 78 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 79 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Clear
	.loc 1 80 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	L14
	.loc 1 81 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L14:
	.loc 1 82 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	testl	%eax, %eax
	je	L15
	.loc 1 83 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, (%esp)
	call	_free
L15:
	.loc 1 84 0
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	.loc 1 85 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	.loc 1 86 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_free
	.loc 1 87 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.def	_bf_extend;	.scl	3;	.type	32;	.endef
_bf_extend:
LFB17:
	.loc 1 90 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 91 0
	movl	$16, -16(%ebp)
	.loc 1 93 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	jne	L17
	.loc 1 95 0
	movl	-16(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, -12(%ebp)
	.loc 1 96 0
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	jmp	L18
L17:
	.loc 1 100 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_realloc
	movl	%eax, -12(%ebp)
L18:
	.loc 1 102 0
	cmpl	$0, -12(%ebp)
	jne	L19
	.loc 1 103 0
	movl	$0, %eax
	jmp	L20
L19:
	.loc 1 104 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	-16(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 1 105 0
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, 4(%eax)
	.loc 1 106 0
	movl	$1, %eax
L20:
	.loc 1 107 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.globl	_bf_AddGlyph
	.def	_bf_AddGlyph;	.scl	2;	.type	32;	.endef
_bf_AddGlyph:
LFB18:
	.loc 1 111 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	.loc 1 112 0
	jmp	L22
L24:
	.loc 1 113 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_extend
	testl	%eax, %eax
	jne	L22
	.loc 1 114 0
	movl	$-1, %eax
	jmp	L23
L22:
	.loc 1 112 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	%eax, %edx
	jle	L24
	.loc 1 115 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	sall	$2, %eax
	leal	(%edx,%eax), %ebx
	call	_bg_Open
	movl	%eax, (%ebx)
	.loc 1 116 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	L25
	.loc 1 117 0
	movl	$-1, %eax
	jmp	L23
L25:
	.loc 1 118 0
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 119 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 8(%eax)
	.loc 1 120 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	subl	$1, %eax
L23:
	.loc 1 121 0
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.def	_bf_extend_target_data;	.scl	3;	.type	32;	.endef
_bf_extend_target_data:
LFB19:
	.loc 1 125 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 126 0
	movl	$16, -20(%ebp)
	.loc 1 129 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	testl	%eax, %eax
	jne	L27
	.loc 1 131 0
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, -16(%ebp)
	.loc 1 132 0
	movl	8(%ebp), %eax
	movl	$0, 1180(%eax)
	jmp	L28
L27:
	.loc 1 136 0
	movl	8(%ebp), %eax
	movl	1180(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_realloc
	movl	%eax, -16(%ebp)
L28:
	.loc 1 138 0
	cmpl	$0, -16(%ebp)
	jne	L29
	.loc 1 139 0
	movl	$0, %eax
	jmp	L30
L29:
	.loc 1 140 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 1176(%eax)
	.loc 1 141 0
	movl	8(%ebp), %eax
	movl	1180(%eax), %eax
	movl	%eax, -12(%ebp)
	jmp	L31
L32:
	.loc 1 142 0 discriminator 3
	movl	8(%ebp), %eax
	movl	1176(%eax), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 141 0 discriminator 3
	addl	$1, -12(%ebp)
L31:
	.loc 1 141 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	1180(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	cmpl	-12(%ebp), %eax
	jg	L32
	.loc 1 143 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	1180(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1180(%eax)
	.loc 1 144 0
	movl	$1, %eax
L30:
	.loc 1 145 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.globl	_bf_AddTargetData
	.def	_bf_AddTargetData;	.scl	2;	.type	32;	.endef
_bf_AddTargetData:
LFB20:
	.loc 1 148 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	movb	%al, -12(%ebp)
	.loc 1 149 0
	jmp	L34
L36:
	.loc 1 150 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_extend_target_data
	testl	%eax, %eax
	jne	L34
	.loc 1 151 0
	movl	$-1, %eax
	jmp	L35
L34:
	.loc 1 149 0
	movl	8(%ebp), %eax
	movl	1180(%eax), %edx
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	cmpl	%eax, %edx
	jle	L36
	.loc 1 152 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %edx
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	addl	%eax, %edx
	movzbl	-12(%ebp), %eax
	movb	%al, (%edx)
	.loc 1 153 0
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1184(%eax)
	.loc 1 154 0
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	subl	$1, %eax
L35:
	.loc 1 155 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.globl	_bf_ClearTargetData
	.def	_bf_ClearTargetData;	.scl	2;	.type	32;	.endef
_bf_ClearTargetData:
LFB21:
	.loc 1 158 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 160 0
	movl	$0, -4(%ebp)
	jmp	L38
L39:
	.loc 1 161 0 discriminator 3
	movl	8(%ebp), %eax
	movl	1176(%eax), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	.loc 1 160 0 discriminator 3
	addl	$1, -4(%ebp)
L38:
	.loc 1 160 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	1180(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	L39
	.loc 1 162 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	$0, 1184(%eax)
	.loc 1 163 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.globl	_bf_CalculateSelectedNumberOfGlyphs
	.def	_bf_CalculateSelectedNumberOfGlyphs;	.scl	2;	.type	32;	.endef
_bf_CalculateSelectedNumberOfGlyphs:
LFB22:
	.loc 1 166 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 169 0
	movl	8(%ebp), %eax
	movl	$0, 1100(%eax)
	.loc 1 172 0
	movl	$0, -4(%ebp)
	jmp	L41
L43:
	.loc 1 174 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-4(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 175 0
	movl	-8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L42
	.loc 1 177 0
	movl	8(%ebp), %eax
	movl	1100(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1100(%eax)
L42:
	.loc 1 172 0 discriminator 2
	addl	$1, -4(%ebp)
L41:
	.loc 1 172 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	L43
	.loc 1 180 0 is_stmt 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.section .rdata,"dr"
LC0:
	.ascii "Reduce: Start\0"
LC1:
	.ascii "Reduce: End\0"
	.text
	.globl	_bf_ReduceAllGlyph
	.def	_bf_ReduceAllGlyph;	.scl	2;	.type	32;	.endef
_bf_ReduceAllGlyph:
LFB23:
	.loc 1 184 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 189 0
	movl	$LC0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 191 0
	movl	$0, -12(%ebp)
	jmp	L45
L47:
	.loc 1 193 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 194 0
	movl	-16(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L46
	.loc 1 196 0
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_ReduceGlyph
	.loc 1 198 0
	movl	-16(%ebp), %eax
	movl	44(%eax), %edx
	movl	-16(%ebp), %eax
	movl	20(%eax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -20(%ebp)
	.loc 1 199 0
	movl	-16(%ebp), %eax
	movl	48(%eax), %edx
	movl	-16(%ebp), %eax
	movl	24(%eax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -24(%ebp)
L46:
	.loc 1 191 0 discriminator 2
	addl	$1, -12(%ebp)
L45:
	.loc 1 191 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L47
	.loc 1 206 0 is_stmt 1
	movl	$LC1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 208 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE23:
	.globl	_bf_ShowAllGlyphs
	.def	_bf_ShowAllGlyphs;	.scl	2;	.type	32;	.endef
_bf_ShowAllGlyphs:
LFB24:
	.loc 1 211 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 214 0
	movl	$0, -12(%ebp)
	jmp	L49
L51:
	.loc 1 216 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 217 0
	movl	-16(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L50
	.loc 1 219 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_ShowBitmap
L50:
	.loc 1 214 0 discriminator 2
	addl	$1, -12(%ebp)
L49:
	.loc 1 214 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L51
	.loc 1 222 0 is_stmt 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
	.globl	_bf_GetIndexByEncoding
	.def	_bf_GetIndexByEncoding;	.scl	2;	.type	32;	.endef
_bf_GetIndexByEncoding:
LFB25:
	.loc 1 225 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 228 0
	movl	$0, -4(%ebp)
	jmp	L53
L56:
	.loc 1 230 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-4(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
	.loc 1 231 0
	movl	-8(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	12(%ebp), %eax
	jne	L54
	.loc 1 232 0
	movl	-4(%ebp), %eax
	jmp	L55
L54:
	.loc 1 228 0 discriminator 2
	addl	$1, -4(%ebp)
L53:
	.loc 1 228 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-4(%ebp), %eax
	jg	L56
	.loc 1 234 0 is_stmt 1
	movl	$-1, %eax
L55:
	.loc 1 235 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE25:
	.section .rdata,"dr"
	.align 4
LC2:
	.ascii "CalculateMaxBBX: x=%ld, y=%ld, w=%ld, h=%ld\0"
	.align 4
LC3:
	.ascii "CalculateMaxBBX: Encodings x=%ld, y=%ld, w=%ld, h=%ld\0"
	.text
	.globl	_bf_CalculateMaxBBX
	.def	_bf_CalculateMaxBBX;	.scl	2;	.type	32;	.endef
_bf_CalculateMaxBBX:
LFB26:
	.loc 1 238 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	.loc 1 240 0
	movl	$1, -16(%ebp)
	.loc 1 245 0
	movl	$0, -12(%ebp)
	jmp	L58
L66:
	.loc 1 247 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 248 0
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L59
	.loc 1 250 0
	cmpl	$0, -16(%ebp)
	je	L60
	.loc 1 252 0
	movl	8(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	20(%edx), %ecx
	movl	%ecx, 1108(%eax)
	movl	24(%edx), %ecx
	movl	%ecx, 1112(%eax)
	movl	28(%edx), %ecx
	movl	%ecx, 1116(%eax)
	movl	32(%edx), %edx
	movl	%edx, 1120(%eax)
	.loc 1 253 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1132(%eax)
	.loc 1 254 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1136(%eax)
	.loc 1 255 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1124(%eax)
	.loc 1 256 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1128(%eax)
	.loc 1 257 0
	movl	$0, -16(%ebp)
	jmp	L59
L60:
	.loc 1 261 0
	movl	8(%ebp), %eax
	addl	$1108, %eax
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_Max
	movl	%eax, -24(%ebp)
	.loc 1 262 0
	movl	-24(%ebp), %eax
	cmpl	$2, %eax
	je	L61
	cmpl	$2, %eax
	jg	L62
	cmpl	$1, %eax
	je	L63
	jmp	L59
L62:
	cmpl	$3, %eax
	je	L64
	cmpl	$4, %eax
	je	L65
	jmp	L59
L63:
	.loc 1 265 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1124(%eax)
	.loc 1 266 0
	jmp	L59
L61:
	.loc 1 268 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1128(%eax)
	.loc 1 269 0
	jmp	L59
L64:
	.loc 1 271 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1132(%eax)
	.loc 1 272 0
	jmp	L59
L65:
	.loc 1 274 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1136(%eax)
	.loc 1 275 0
	nop
L59:
	.loc 1 245 0 discriminator 2
	addl	$1, -12(%ebp)
L58:
	.loc 1 245 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L66
	.loc 1 281 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	cmpl	$3, %eax
	jne	L67
	.loc 1 283 0
	movl	8(%ebp), %eax
	movl	1108(%eax), %eax
	addl	$7, %eax
	andl	$-8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1108(%eax)
	.loc 1 284 0
	movl	8(%ebp), %eax
	movl	1112(%eax), %eax
	addl	$7, %eax
	andl	$-8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 1112(%eax)
L67:
	.loc 1 288 0
	movl	8(%ebp), %eax
	movl	1112(%eax), %ebx
	movl	8(%ebp), %eax
	movl	1108(%eax), %ecx
	movl	8(%ebp), %eax
	movl	1120(%eax), %edx
	movl	8(%ebp), %eax
	movl	1116(%eax), %eax
	movl	%ebx, 20(%esp)
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC2, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 289 0
	movl	8(%ebp), %eax
	movl	1128(%eax), %ebx
	movl	8(%ebp), %eax
	movl	1124(%eax), %ecx
	movl	8(%ebp), %eax
	movl	1136(%eax), %edx
	movl	8(%ebp), %eax
	movl	1132(%eax), %eax
	movl	%ebx, 20(%esp)
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC3, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 290 0
	nop
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.section .rdata,"dr"
	.align 4
LC4:
	.ascii "bf_CalculateMinMaxDWidth: dx_min=%ld, dx_max=%ld\0"
	.align 4
LC5:
	.ascii "bf_CalculateMinMaxDWidth: x_min=%ld, x_max=%ld\0"
	.align 4
LC6:
	.ascii "bf_CalculateMinMaxDWidth: Monospaced font.\0"
	.text
	.globl	_bf_CalculateMinMaxDWidth
	.def	_bf_CalculateMinMaxDWidth;	.scl	2;	.type	32;	.endef
_bf_CalculateMinMaxDWidth:
LFB27:
	.loc 1 293 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 297 0
	movl	8(%ebp), %eax
	movl	$32767, 1140(%eax)
	.loc 1 298 0
	movl	8(%ebp), %eax
	movl	$-32767, 1144(%eax)
	.loc 1 300 0
	movl	8(%ebp), %eax
	movl	$32767, 1148(%eax)
	.loc 1 301 0
	movl	8(%ebp), %eax
	movl	$-32767, 1152(%eax)
	.loc 1 303 0
	movl	$0, -12(%ebp)
	jmp	L69
L74:
	.loc 1 305 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 306 0
	movl	-16(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L70
	.loc 1 308 0
	movl	8(%ebp), %eax
	movl	1140(%eax), %edx
	movl	-16(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jle	L71
	.loc 1 309 0
	movl	-16(%ebp), %eax
	movl	12(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1140(%eax)
L71:
	.loc 1 310 0
	movl	8(%ebp), %eax
	movl	1144(%eax), %edx
	movl	-16(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jge	L72
	.loc 1 311 0
	movl	-16(%ebp), %eax
	movl	12(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1144(%eax)
L72:
	.loc 1 313 0
	movl	8(%ebp), %eax
	movl	1148(%eax), %edx
	movl	-16(%ebp), %eax
	movl	28(%eax), %eax
	cmpl	%eax, %edx
	jle	L73
	.loc 1 314 0
	movl	-16(%ebp), %eax
	movl	28(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1148(%eax)
L73:
	.loc 1 315 0
	movl	8(%ebp), %eax
	movl	1152(%eax), %edx
	movl	-16(%ebp), %eax
	movl	28(%eax), %eax
	cmpl	%eax, %edx
	jge	L70
	.loc 1 316 0
	movl	-16(%ebp), %eax
	movl	28(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 1152(%eax)
L70:
	.loc 1 303 0 discriminator 2
	addl	$1, -12(%ebp)
L69:
	.loc 1 303 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L74
	.loc 1 320 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	1144(%eax), %edx
	movl	8(%ebp), %eax
	movl	1140(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC4, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 321 0
	movl	8(%ebp), %eax
	movl	1152(%eax), %edx
	movl	8(%ebp), %eax
	movl	1148(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC5, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 322 0
	movl	8(%ebp), %eax
	movl	1140(%eax), %edx
	movl	8(%ebp), %eax
	movl	1144(%eax), %eax
	cmpl	%eax, %edx
	jne	L76
	.loc 1 322 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	1148(%eax), %eax
	testl	%eax, %eax
	js	L76
	.loc 1 324 0 is_stmt 1
	movl	$LC6, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
L76:
	.loc 1 327 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE27:
	.globl	_get_unsigned_bit_size
	.def	_get_unsigned_bit_size;	.scl	2;	.type	32;	.endef
_get_unsigned_bit_size:
LFB28:
	.loc 1 330 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 331 0
	movl	$0, -4(%ebp)
	.loc 1 332 0
	jmp	L78
L79:
	.loc 1 334 0
	movl	8(%ebp), %eax
	shrl	%eax
	movl	%eax, 8(%ebp)
	.loc 1 335 0
	addl	$1, -4(%ebp)
L78:
	.loc 1 332 0
	cmpl	$0, 8(%ebp)
	jne	L79
	.loc 1 337 0
	movl	-4(%ebp), %eax
	.loc 1 338 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE28:
	.globl	_get_signed_bit_size
	.def	_get_signed_bit_size;	.scl	2;	.type	32;	.endef
_get_signed_bit_size:
LFB29:
	.loc 1 341 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	.loc 1 342 0
	cmpl	$0, 8(%ebp)
	jns	L82
	.loc 1 343 0
	movl	8(%ebp), %eax
	notl	%eax
	movl	%eax, (%esp)
	call	_get_unsigned_bit_size
	addl	$1, %eax
	jmp	L83
L82:
	.loc 1 344 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_unsigned_bit_size
	addl	$1, %eax
L83:
	.loc 1 345 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE29:
	.globl	_bf_copy_bbx_and_update_shift
	.def	_bf_copy_bbx_and_update_shift;	.scl	2;	.type	32;	.endef
_bf_copy_bbx_and_update_shift:
LFB30:
	.loc 1 348 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 350 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	testl	%eax, %eax
	jne	L85
	.loc 1 352 0
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	20(%edx), %ecx
	movl	%ecx, (%eax)
	movl	24(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	28(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	32(%edx), %edx
	movl	%edx, 12(%eax)
	jmp	L86
L85:
	.loc 1 354 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	cmpl	$2, %eax
	jne	L87
	.loc 1 356 0
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	1108(%edx), %ecx
	movl	%ecx, (%eax)
	movl	1112(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	1116(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	1120(%edx), %edx
	movl	%edx, 12(%eax)
	.loc 1 357 0
	movl	12(%ebp), %eax
	movl	$0, 8(%eax)
	.loc 1 358 0
	movl	16(%ebp), %eax
	movl	28(%eax), %eax
	testl	%eax, %eax
	jns	L88
	.loc 1 359 0
	movl	16(%ebp), %eax
	movl	28(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, 36(%eax)
L88:
	.loc 1 360 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jge	L86
	.loc 1 361 0
	movl	16(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	jmp	L86
L87:
	.loc 1 363 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	cmpl	$3, %eax
	jne	L90
	.loc 1 365 0
	movl	8(%ebp), %eax
	movl	1108(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 366 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jge	L91
	.loc 1 367 0
	movl	16(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
L91:
	.loc 1 368 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	addl	$7, %eax
	andl	$-8, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 369 0
	movl	8(%ebp), %eax
	movl	1112(%eax), %eax
	addl	$7, %eax
	andl	$-8, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 370 0
	movl	8(%ebp), %eax
	movl	1116(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, 8(%eax)
	.loc 1 371 0
	movl	8(%ebp), %eax
	movl	1120(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 1 372 0
	movl	12(%ebp), %eax
	movl	$0, 8(%eax)
	.loc 1 373 0
	movl	16(%ebp), %eax
	movl	28(%eax), %eax
	testl	%eax, %eax
	jns	L86
	.loc 1 374 0
	movl	16(%ebp), %eax
	movl	28(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, 36(%eax)
	jmp	L86
L90:
	.loc 1 379 0
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	1108(%edx), %ecx
	movl	%ecx, (%eax)
	movl	1112(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	1116(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	1120(%edx), %edx
	movl	%edx, 12(%eax)
	.loc 1 380 0
	movl	16(%ebp), %eax
	movl	20(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 381 0
	movl	16(%ebp), %eax
	movl	28(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, 8(%eax)
	.loc 1 382 0
	movl	12(%ebp), %eax
	movl	$0, 8(%eax)
	.loc 1 383 0
	movl	16(%ebp), %eax
	movl	28(%eax), %eax
	testl	%eax, %eax
	jns	L93
	.loc 1 386 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	28(%eax), %eax
	subl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 387 0
	movl	16(%ebp), %eax
	movl	28(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, 36(%eax)
	jmp	L94
L93:
	.loc 1 392 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	28(%eax), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
L94:
	.loc 1 395 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jge	L86
	.loc 1 396 0
	movl	16(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
L86:
	.loc 1 399 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	20(%eax), %eax
	subl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%edx, 92(%eax)
	.loc 1 400 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE30:
	.section .rdata,"dr"
	.align 4
LC7:
	.ascii "bf_CalculateMaxBitFieldSize: bbx.x=%d, bbx.y=%d, bbx.w=%d, bbx.h=%d, dwidth=%d\0"
	.text
	.globl	_bf_CalculateMaxBitFieldSize
	.def	_bf_CalculateMaxBitFieldSize;	.scl	2;	.type	32;	.endef
_bf_CalculateMaxBitFieldSize:
LFB31:
	.loc 1 403 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$64, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	.loc 1 408 0
	movl	8(%ebp), %eax
	movl	$0, 1156(%eax)
	.loc 1 409 0
	movl	8(%ebp), %eax
	movl	$0, 1160(%eax)
	.loc 1 410 0
	movl	8(%ebp), %eax
	movl	$0, 1164(%eax)
	.loc 1 411 0
	movl	8(%ebp), %eax
	movl	$0, 1168(%eax)
	.loc 1 412 0
	movl	8(%ebp), %eax
	movl	$0, 1172(%eax)
	.loc 1 413 0
	movl	$0, -12(%ebp)
	jmp	L96
L105:
	.loc 1 415 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 416 0
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L97
	.loc 1 419 0
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_copy_bbx_and_update_shift
	.loc 1 471 0
	movl	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_unsigned_bit_size
	movl	%eax, -16(%ebp)
	.loc 1 472 0
	movl	8(%ebp), %eax
	movl	1164(%eax), %eax
	cmpl	-16(%ebp), %eax
	jge	L98
	.loc 1 473 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 1164(%eax)
L98:
	.loc 1 475 0
	movl	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_unsigned_bit_size
	movl	%eax, -16(%ebp)
	.loc 1 476 0
	movl	8(%ebp), %eax
	movl	1168(%eax), %eax
	cmpl	-16(%ebp), %eax
	jge	L99
	.loc 1 477 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 1168(%eax)
L99:
	.loc 1 480 0
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_signed_bit_size
	movl	%eax, -16(%ebp)
	.loc 1 481 0
	movl	8(%ebp), %eax
	movl	1156(%eax), %eax
	cmpl	-16(%ebp), %eax
	jge	L100
	.loc 1 482 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 1156(%eax)
L100:
	.loc 1 485 0
	movl	-24(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_signed_bit_size
	movl	%eax, -16(%ebp)
	.loc 1 486 0
	movl	8(%ebp), %eax
	movl	1160(%eax), %eax
	cmpl	-16(%ebp), %eax
	jge	L101
	.loc 1 487 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 1160(%eax)
L101:
	.loc 1 489 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	testl	%eax, %eax
	jne	L102
	.loc 1 491 0
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
	call	_get_signed_bit_size
	movl	%eax, -16(%ebp)
	jmp	L103
L102:
	.loc 1 493 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	cmpl	$2, %eax
	jne	L104
	.loc 1 495 0
	movl	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_signed_bit_size
	movl	%eax, -16(%ebp)
	jmp	L103
L104:
	.loc 1 499 0
	movl	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_signed_bit_size
	movl	%eax, -16(%ebp)
L103:
	.loc 1 501 0
	movl	8(%ebp), %eax
	movl	1172(%eax), %eax
	cmpl	-16(%ebp), %eax
	jge	L97
	.loc 1 502 0
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, 1172(%eax)
L97:
	.loc 1 413 0 discriminator 2
	addl	$1, -12(%ebp)
L96:
	.loc 1 413 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L105
	.loc 1 506 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	1172(%eax), %esi
	movl	8(%ebp), %eax
	movl	1168(%eax), %ebx
	movl	8(%ebp), %eax
	movl	1164(%eax), %ecx
	movl	8(%ebp), %eax
	movl	1160(%eax), %edx
	movl	8(%ebp), %eax
	movl	1156(%eax), %eax
	movl	%esi, 24(%esp)
	movl	%ebx, 20(%esp)
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC7, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 509 0
	nop
	addl	$64, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE31:
	.section .rdata,"dr"
	.align 4
LC8:
	.ascii "Monospace Statistics: Max width extention %ld, average width extention %ld.%ld\0"
	.text
	.globl	_bf_ShowMonospaceStatistics
	.def	_bf_ShowMonospaceStatistics;	.scl	2;	.type	32;	.endef
_bf_ShowMonospaceStatistics:
LFB32:
	.loc 1 512 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$68, %esp
	.cfi_offset 3, -12
	.loc 1 515 0
	movl	$0, -16(%ebp)
	.loc 1 516 0
	movl	$0, -20(%ebp)
	.loc 1 517 0
	movl	$0, -24(%ebp)
	.loc 1 518 0
	movl	$0, -12(%ebp)
	jmp	L107
L110:
	.loc 1 520 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -28(%ebp)
	.loc 1 521 0
	movl	-28(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L108
	.loc 1 523 0
	movl	-28(%ebp), %eax
	movl	92(%eax), %eax
	cmpl	-20(%ebp), %eax
	jle	L109
	.loc 1 524 0
	movl	-28(%ebp), %eax
	movl	92(%eax), %eax
	movl	%eax, -20(%ebp)
L109:
	.loc 1 525 0
	movl	-28(%ebp), %eax
	movl	92(%eax), %eax
	addl	%eax, -24(%ebp)
	.loc 1 526 0
	addl	$1, -16(%ebp)
L108:
	.loc 1 518 0 discriminator 2
	addl	$1, -12(%ebp)
L107:
	.loc 1 518 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L110
	.loc 1 529 0 is_stmt 1
	cmpl	$0, -16(%ebp)
	jne	L111
	.loc 1 530 0
	addl	$1, -16(%ebp)
L111:
	.loc 1 531 0
	movl	-24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	cltd
	idivl	-16(%ebp)
	movl	%eax, %ebx
	movl	$1717986919, %edx
	movl	%ebx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ebx, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	subl	%eax, %ebx
	movl	%ebx, %ecx
	movl	-24(%ebp), %eax
	cltd
	idivl	-16(%ebp)
	movl	%ecx, 16(%esp)
	movl	%eax, 12(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC8, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 551 0
	nop
	addl	$68, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE32:
	.section .rdata,"dr"
LC9:
	.ascii "/*\12\0"
LC10:
	.ascii "  Fontname: %s\12\0"
LC11:
	.ascii "  Copyright: %s\12\0"
LC12:
	.ascii "  Glyphs: %d/%d\12\0"
LC13:
	.ascii "  BBX Build Mode: %d\12\0"
LC14:
	.ascii "*/\12\0"
LC15:
	.ascii "#include \"ucg.h\"\12\0"
	.align 4
LC16:
	.ascii "const ucg_fntpgm_uint8_t %s[%d] UCG_FONT_SECTION(\"%s\") = {\12\0"
LC17:
	.ascii "  \0"
LC18:
	.ascii "%d\0"
LC19:
	.ascii "\12%s\0"
LC20:
	.ascii "};\12\0"
	.text
	.globl	_bf_WriteUCGCByFP
	.def	_bf_WriteUCGCByFP;	.scl	2;	.type	32;	.endef
_bf_WriteUCGCByFP:
LFB33:
	.loc 1 555 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 1 557 0
	movl	$16, -16(%ebp)
	.loc 1 559 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC9, (%esp)
	call	_fwrite
	.loc 1 560 0
	movl	8(%ebp), %eax
	movl	1092(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC10, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 561 0
	movl	8(%ebp), %eax
	movl	1096(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC11, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 562 0
	movl	8(%ebp), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	1100(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC12, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 563 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC13, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 564 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC14, (%esp)
	call	_fwrite
	.loc 1 565 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$17, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC15, (%esp)
	call	_fwrite
	.loc 1 566 0
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC16, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 567 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$2, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC17, (%esp)
	call	_fwrite
	.loc 1 569 0
	movl	$0, -12(%ebp)
	jmp	L113
L116:
	.loc 1 571 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 8(%esp)
	movl	$LC18, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 572 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	cmpl	%eax, %edx
	je	L114
	.loc 1 573 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$44, (%esp)
	call	_fputc
L114:
	.loc 1 574 0
	movl	-12(%ebp), %eax
	addl	$1, %eax
	cltd
	idivl	-16(%ebp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	L115
	.loc 1 575 0
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC19, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
L115:
	.loc 1 569 0 discriminator 2
	addl	$1, -12(%ebp)
L113:
	.loc 1 569 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L116
	.loc 1 578 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC20, (%esp)
	call	_fwrite
	.loc 1 579 0
	movl	$1, %eax
	.loc 1 580 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE33:
	.section .rdata,"dr"
LC21:
	.ascii "#include \"u8g2.h\"\12\0"
	.align 4
LC22:
	.ascii "const uint8_t %s[%d] U8G2_FONT_SECTION(\"%s\") = {\12\0"
	.text
	.globl	_bf_WriteU8G2CByFP
	.def	_bf_WriteU8G2CByFP;	.scl	2;	.type	32;	.endef
_bf_WriteU8G2CByFP:
LFB34:
	.loc 1 583 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 1 585 0
	movl	$16, -16(%ebp)
	.loc 1 587 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC9, (%esp)
	call	_fwrite
	.loc 1 588 0
	movl	8(%ebp), %eax
	movl	1092(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC10, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 589 0
	movl	8(%ebp), %eax
	movl	1096(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC11, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 590 0
	movl	8(%ebp), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	1100(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC12, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 591 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC13, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 592 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC14, (%esp)
	call	_fwrite
	.loc 1 593 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$18, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC21, (%esp)
	call	_fwrite
	.loc 1 594 0
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC22, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 595 0
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$2, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC17, (%esp)
	call	_fwrite
	.loc 1 597 0
	movl	$0, -12(%ebp)
	jmp	L119
L122:
	.loc 1 599 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 8(%esp)
	movl	$LC18, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	.loc 1 600 0
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	cmpl	%eax, %edx
	je	L120
	.loc 1 601 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$44, (%esp)
	call	_fputc
L120:
	.loc 1 602 0
	movl	-12(%ebp), %eax
	addl	$1, %eax
	cltd
	idivl	-16(%ebp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	L121
	.loc 1 603 0
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC19, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fprintf
L121:
	.loc 1 597 0 discriminator 2
	addl	$1, -12(%ebp)
L119:
	.loc 1 597 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L122
	.loc 1 606 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC20, (%esp)
	call	_fwrite
	.loc 1 607 0
	movl	$1, %eax
	.loc 1 608 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE34:
	.section .rdata,"dr"
LC23:
	.ascii "wb\0"
	.align 4
LC24:
	.ascii "bf_WriteUCGCByFilename: Open error '%s'\0"
	.align 4
LC25:
	.ascii "bf_WriteUCGCByFilename: Write file '%s'\0"
	.text
	.globl	_bf_WriteUCGCByFilename
	.def	_bf_WriteUCGCByFilename;	.scl	2;	.type	32;	.endef
_bf_WriteUCGCByFilename:
LFB35:
	.loc 1 611 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 613 0
	movl	$LC23, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fopen
	movl	%eax, -12(%ebp)
	.loc 1 614 0
	cmpl	$0, -12(%ebp)
	jne	L125
	.loc 1 616 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC24, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 617 0
	movl	$0, %eax
	jmp	L126
L125:
	.loc 1 620 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_WriteUCGCByFP
	.loc 1 621 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC25, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 623 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fclose
	.loc 1 624 0
	movl	$1, %eax
L126:
	.loc 1 625 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE35:
	.section .rdata,"dr"
	.align 4
LC26:
	.ascii "bf_WriteU8G2CByFilename: Open error '%s'\0"
	.align 4
LC27:
	.ascii "bf_WriteU8G2CByFilename: Write file '%s'\0"
	.text
	.globl	_bf_WriteU8G2CByFilename
	.def	_bf_WriteU8G2CByFilename;	.scl	2;	.type	32;	.endef
_bf_WriteU8G2CByFilename:
LFB36:
	.loc 1 628 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 630 0
	movl	$LC23, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fopen
	movl	%eax, -12(%ebp)
	.loc 1 631 0
	cmpl	$0, -12(%ebp)
	jne	L128
	.loc 1 633 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC26, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 634 0
	movl	$0, %eax
	jmp	L129
L128:
	.loc 1 637 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_WriteU8G2CByFP
	.loc 1 638 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC27, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 640 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_fclose
	.loc 1 641 0
	movl	$1, %eax
L129:
	.loc 1 642 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE36:
	.globl	_bf_OpenFromFile
	.def	_bf_OpenFromFile;	.scl	2;	.type	32;	.endef
_bf_OpenFromFile:
LFB37:
	.loc 1 647 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 650 0
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Open
	movl	%eax, -12(%ebp)
	.loc 1 651 0
	cmpl	$0, -12(%ebp)
	je	L131
	.loc 1 654 0
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_ParseFile
	testl	%eax, %eax
	je	L132
	.loc 1 656 0
	movl	20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Map
	.loc 1 657 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_CalculateSelectedNumberOfGlyphs
	.loc 1 659 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_ReduceAllGlyph
	.loc 1 660 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_CalculateMaxBBX
	.loc 1 662 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_CalculateMinMaxDWidth
	.loc 1 664 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_CalculateMaxBitFieldSize
	.loc 1 667 0
	cmpl	$0, 24(%ebp)
	je	L133
	.loc 1 667 0 is_stmt 0 discriminator 1
	cmpl	$1, 24(%ebp)
	jne	L134
L133:
	.loc 1 669 0 is_stmt 1
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLECompressAllGlyphs
	jmp	L135
L134:
	.loc 1 673 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Generate8x8Font
L135:
	.loc 1 676 0
	movl	-12(%ebp), %eax
	movl	1104(%eax), %eax
	testl	%eax, %eax
	je	L136
	.loc 1 677 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_ShowMonospaceStatistics
L136:
	.loc 1 679 0
	movl	-12(%ebp), %eax
	jmp	L137
L132:
	.loc 1 681 0
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Close
L131:
	.loc 1 683 0
	movl	$0, %eax
L137:
	.loc 1 684 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE37:
Letext0:
	.file 2 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 3 "/usr/include/machine/_default_types.h"
	.file 4 "/usr/include/sys/lock.h"
	.file 5 "/usr/include/sys/_types.h"
	.file 6 "/usr/include/sys/reent.h"
	.file 7 "/usr/include/stdlib.h"
	.file 8 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stdarg.h"
	.file 9 "/usr/include/sys/_stdint.h"
	.file 10 "/usr/include/stdio.h"
	.file 11 "bdf_glyph.h"
	.file 12 "bdf_font.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x1a85
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_font.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.ascii "size_t\0"
	.byte	0x2
	.byte	0xd8
	.long	0x9b
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
	.long	0x108
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
	.long	0x164
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
	.long	0xc8
	.uleb128 0x2
	.ascii "_fpos_t\0"
	.byte	0x5
	.byte	0x72
	.long	0x166
	.uleb128 0x2
	.ascii "_fpos64_t\0"
	.byte	0x5
	.byte	0x78
	.long	0x172
	.uleb128 0x2
	.ascii "_ssize_t\0"
	.byte	0x5
	.byte	0x91
	.long	0xc1
	.uleb128 0x5
	.ascii "wint_t\0"
	.byte	0x2
	.word	0x165
	.long	0x9b
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.byte	0xa6
	.long	0x1e5
	.uleb128 0x7
	.ascii "__wch\0"
	.byte	0x5
	.byte	0xa8
	.long	0x1b2
	.uleb128 0x7
	.ascii "__wchb\0"
	.byte	0x5
	.byte	0xa9
	.long	0x1e5
	.byte	0
	.uleb128 0x8
	.long	0x108
	.long	0x1f5
	.uleb128 0x9
	.long	0x1f5
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
	.long	0x22a
	.uleb128 0xb
	.ascii "__count\0"
	.byte	0x5
	.byte	0xa5
	.long	0xc1
	.byte	0
	.uleb128 0xb
	.ascii "__value\0"
	.byte	0x5
	.byte	0xaa
	.long	0x1c1
	.byte	0x4
	.byte	0
	.uleb128 0x2
	.ascii "_mbstate_t\0"
	.byte	0x5
	.byte	0xab
	.long	0x201
	.uleb128 0x2
	.ascii "_flock_t\0"
	.byte	0x5
	.byte	0xaf
	.long	0x155
	.uleb128 0xc
	.byte	0x4
	.long	0x252
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0xd
	.long	0x252
	.uleb128 0x2
	.ascii "__ULong\0"
	.byte	0x6
	.byte	0x16
	.long	0x140
	.uleb128 0xe
	.ascii "_Bigint\0"
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.long	0x2ce
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x31
	.long	0x2ce
	.byte	0
	.uleb128 0xb
	.ascii "_k\0"
	.byte	0x6
	.byte	0x32
	.long	0xc1
	.byte	0x4
	.uleb128 0xb
	.ascii "_maxwds\0"
	.byte	0x6
	.byte	0x32
	.long	0xc1
	.byte	0x8
	.uleb128 0xb
	.ascii "_sign\0"
	.byte	0x6
	.byte	0x32
	.long	0xc1
	.byte	0xc
	.uleb128 0xb
	.ascii "_wds\0"
	.byte	0x6
	.byte	0x32
	.long	0xc1
	.byte	0x10
	.uleb128 0xb
	.ascii "_x\0"
	.byte	0x6
	.byte	0x33
	.long	0x2d4
	.byte	0x14
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x26e
	.uleb128 0x8
	.long	0x25f
	.long	0x2e4
	.uleb128 0x9
	.long	0x1f5
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__tm\0"
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.long	0x392
	.uleb128 0xb
	.ascii "__tm_sec\0"
	.byte	0x6
	.byte	0x39
	.long	0xc1
	.byte	0
	.uleb128 0xb
	.ascii "__tm_min\0"
	.byte	0x6
	.byte	0x3a
	.long	0xc1
	.byte	0x4
	.uleb128 0xb
	.ascii "__tm_hour\0"
	.byte	0x6
	.byte	0x3b
	.long	0xc1
	.byte	0x8
	.uleb128 0xb
	.ascii "__tm_mday\0"
	.byte	0x6
	.byte	0x3c
	.long	0xc1
	.byte	0xc
	.uleb128 0xb
	.ascii "__tm_mon\0"
	.byte	0x6
	.byte	0x3d
	.long	0xc1
	.byte	0x10
	.uleb128 0xb
	.ascii "__tm_year\0"
	.byte	0x6
	.byte	0x3e
	.long	0xc1
	.byte	0x14
	.uleb128 0xb
	.ascii "__tm_wday\0"
	.byte	0x6
	.byte	0x3f
	.long	0xc1
	.byte	0x18
	.uleb128 0xb
	.ascii "__tm_yday\0"
	.byte	0x6
	.byte	0x40
	.long	0xc1
	.byte	0x1c
	.uleb128 0xb
	.ascii "__tm_isdst\0"
	.byte	0x6
	.byte	0x41
	.long	0xc1
	.byte	0x20
	.byte	0
	.uleb128 0xf
	.secrel32	LASF0
	.word	0x108
	.byte	0x6
	.byte	0x4a
	.long	0x3e7
	.uleb128 0xb
	.ascii "_fnargs\0"
	.byte	0x6
	.byte	0x4b
	.long	0x3e7
	.byte	0
	.uleb128 0xb
	.ascii "_dso_handle\0"
	.byte	0x6
	.byte	0x4c
	.long	0x3e7
	.byte	0x80
	.uleb128 0x10
	.ascii "_fntypes\0"
	.byte	0x6
	.byte	0x4e
	.long	0x25f
	.word	0x100
	.uleb128 0x10
	.ascii "_is_cxa\0"
	.byte	0x6
	.byte	0x51
	.long	0x25f
	.word	0x104
	.byte	0
	.uleb128 0x8
	.long	0x164
	.long	0x3f7
	.uleb128 0x9
	.long	0x1f5
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.ascii "_atexit\0"
	.word	0x190
	.byte	0x6
	.byte	0x5d
	.long	0x43d
	.uleb128 0xb
	.ascii "_next\0"
	.byte	0x6
	.byte	0x5e
	.long	0x43d
	.byte	0
	.uleb128 0xb
	.ascii "_ind\0"
	.byte	0x6
	.byte	0x5f
	.long	0xc1
	.byte	0x4
	.uleb128 0xb
	.ascii "_fns\0"
	.byte	0x6
	.byte	0x61
	.long	0x443
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF0
	.byte	0x6
	.byte	0x62
	.long	0x392
	.byte	0x88
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x3f7
	.uleb128 0x8
	.long	0x453
	.long	0x453
	.uleb128 0x9
	.long	0x1f5
	.byte	0x1f
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x459
	.uleb128 0x13
	.uleb128 0xe
	.ascii "__sbuf\0"
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.long	0x486
	.uleb128 0xb
	.ascii "_base\0"
	.byte	0x6
	.byte	0x76
	.long	0x486
	.byte	0
	.uleb128 0xb
	.ascii "_size\0"
	.byte	0x6
	.byte	0x77
	.long	0xc1
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x108
	.uleb128 0x14
	.long	0x1a2
	.long	0x4aa
	.uleb128 0x15
	.long	0x4aa
	.uleb128 0x15
	.long	0x164
	.uleb128 0x15
	.long	0x24c
	.uleb128 0x15
	.long	0x8d
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x4b5
	.uleb128 0xd
	.long	0x4aa
	.uleb128 0x16
	.ascii "_reent\0"
	.word	0x440
	.byte	0x6
	.word	0x239
	.long	0x654
	.uleb128 0x17
	.ascii "_errno\0"
	.byte	0x6
	.word	0x23b
	.long	0xc1
	.byte	0
	.uleb128 0x17
	.ascii "_stdin\0"
	.byte	0x6
	.word	0x240
	.long	0x8d9
	.byte	0x4
	.uleb128 0x17
	.ascii "_stdout\0"
	.byte	0x6
	.word	0x240
	.long	0x8d9
	.byte	0x8
	.uleb128 0x17
	.ascii "_stderr\0"
	.byte	0x6
	.word	0x240
	.long	0x8d9
	.byte	0xc
	.uleb128 0x17
	.ascii "_inc\0"
	.byte	0x6
	.word	0x242
	.long	0xc1
	.byte	0x10
	.uleb128 0x17
	.ascii "_emergency\0"
	.byte	0x6
	.word	0x243
	.long	0xb7f
	.byte	0x14
	.uleb128 0x17
	.ascii "_unspecified_locale_info\0"
	.byte	0x6
	.word	0x246
	.long	0xc1
	.byte	0x30
	.uleb128 0x17
	.ascii "_locale\0"
	.byte	0x6
	.word	0x247
	.long	0xb9b
	.byte	0x34
	.uleb128 0x17
	.ascii "__sdidinit\0"
	.byte	0x6
	.word	0x249
	.long	0xc1
	.byte	0x38
	.uleb128 0x17
	.ascii "__cleanup\0"
	.byte	0x6
	.word	0x24b
	.long	0xbac
	.byte	0x3c
	.uleb128 0x17
	.ascii "_result\0"
	.byte	0x6
	.word	0x24e
	.long	0x2ce
	.byte	0x40
	.uleb128 0x17
	.ascii "_result_k\0"
	.byte	0x6
	.word	0x24f
	.long	0xc1
	.byte	0x44
	.uleb128 0x17
	.ascii "_p5s\0"
	.byte	0x6
	.word	0x250
	.long	0x2ce
	.byte	0x48
	.uleb128 0x17
	.ascii "_freelist\0"
	.byte	0x6
	.word	0x251
	.long	0xbb2
	.byte	0x4c
	.uleb128 0x17
	.ascii "_cvtlen\0"
	.byte	0x6
	.word	0x254
	.long	0xc1
	.byte	0x50
	.uleb128 0x17
	.ascii "_cvtbuf\0"
	.byte	0x6
	.word	0x255
	.long	0x24c
	.byte	0x54
	.uleb128 0x17
	.ascii "_new\0"
	.byte	0x6
	.word	0x278
	.long	0xb56
	.byte	0x58
	.uleb128 0x18
	.ascii "_atexit\0"
	.byte	0x6
	.word	0x27c
	.long	0x43d
	.word	0x148
	.uleb128 0x18
	.ascii "_atexit0\0"
	.byte	0x6
	.word	0x27d
	.long	0x3f7
	.word	0x14c
	.uleb128 0x18
	.ascii "_sig_func\0"
	.byte	0x6
	.word	0x281
	.long	0xbc3
	.word	0x2dc
	.uleb128 0x18
	.ascii "__sglue\0"
	.byte	0x6
	.word	0x286
	.long	0x895
	.word	0x2e0
	.uleb128 0x18
	.ascii "__sf\0"
	.byte	0x6
	.word	0x288
	.long	0xbcf
	.word	0x2f0
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x48c
	.uleb128 0x14
	.long	0x1a2
	.long	0x678
	.uleb128 0x15
	.long	0x4aa
	.uleb128 0x15
	.long	0x164
	.uleb128 0x15
	.long	0x678
	.uleb128 0x15
	.long	0x8d
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x25a
	.uleb128 0xc
	.byte	0x4
	.long	0x65a
	.uleb128 0x14
	.long	0x182
	.long	0x6a2
	.uleb128 0x15
	.long	0x4aa
	.uleb128 0x15
	.long	0x164
	.uleb128 0x15
	.long	0x182
	.uleb128 0x15
	.long	0xc1
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x684
	.uleb128 0x14
	.long	0xc1
	.long	0x6bc
	.uleb128 0x15
	.long	0x4aa
	.uleb128 0x15
	.long	0x164
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x6a8
	.uleb128 0x8
	.long	0x108
	.long	0x6d2
	.uleb128 0x9
	.long	0x1f5
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.long	0x108
	.long	0x6e2
	.uleb128 0x9
	.long	0x1f5
	.byte	0
	.byte	0
	.uleb128 0xe
	.ascii "__sFILE64\0"
	.byte	0x70
	.byte	0x6
	.byte	0xef
	.long	0x862
	.uleb128 0xb
	.ascii "_p\0"
	.byte	0x6
	.byte	0xf0
	.long	0x486
	.byte	0
	.uleb128 0xb
	.ascii "_r\0"
	.byte	0x6
	.byte	0xf1
	.long	0xc1
	.byte	0x4
	.uleb128 0xb
	.ascii "_w\0"
	.byte	0x6
	.byte	0xf2
	.long	0xc1
	.byte	0x8
	.uleb128 0xb
	.ascii "_flags\0"
	.byte	0x6
	.byte	0xf3
	.long	0x119
	.byte	0xc
	.uleb128 0xb
	.ascii "_file\0"
	.byte	0x6
	.byte	0xf4
	.long	0x119
	.byte	0xe
	.uleb128 0xb
	.ascii "_bf\0"
	.byte	0x6
	.byte	0xf5
	.long	0x45a
	.byte	0x10
	.uleb128 0xb
	.ascii "_lbfsize\0"
	.byte	0x6
	.byte	0xf6
	.long	0xc1
	.byte	0x18
	.uleb128 0xb
	.ascii "_data\0"
	.byte	0x6
	.byte	0xf8
	.long	0x4aa
	.byte	0x1c
	.uleb128 0xb
	.ascii "_cookie\0"
	.byte	0x6
	.byte	0xfb
	.long	0x164
	.byte	0x20
	.uleb128 0xb
	.ascii "_read\0"
	.byte	0x6
	.byte	0xfd
	.long	0x654
	.byte	0x24
	.uleb128 0xb
	.ascii "_write\0"
	.byte	0x6
	.byte	0xff
	.long	0x67e
	.byte	0x28
	.uleb128 0x17
	.ascii "_seek\0"
	.byte	0x6
	.word	0x102
	.long	0x6a2
	.byte	0x2c
	.uleb128 0x17
	.ascii "_close\0"
	.byte	0x6
	.word	0x103
	.long	0x6bc
	.byte	0x30
	.uleb128 0x17
	.ascii "_ub\0"
	.byte	0x6
	.word	0x106
	.long	0x45a
	.byte	0x34
	.uleb128 0x17
	.ascii "_up\0"
	.byte	0x6
	.word	0x107
	.long	0x486
	.byte	0x3c
	.uleb128 0x17
	.ascii "_ur\0"
	.byte	0x6
	.word	0x108
	.long	0xc1
	.byte	0x40
	.uleb128 0x17
	.ascii "_ubuf\0"
	.byte	0x6
	.word	0x10b
	.long	0x6c2
	.byte	0x44
	.uleb128 0x17
	.ascii "_nbuf\0"
	.byte	0x6
	.word	0x10c
	.long	0x6d2
	.byte	0x47
	.uleb128 0x17
	.ascii "_lb\0"
	.byte	0x6
	.word	0x10f
	.long	0x45a
	.byte	0x48
	.uleb128 0x17
	.ascii "_blksize\0"
	.byte	0x6
	.word	0x112
	.long	0xc1
	.byte	0x50
	.uleb128 0x17
	.ascii "_flags2\0"
	.byte	0x6
	.word	0x113
	.long	0xc1
	.byte	0x54
	.uleb128 0x17
	.ascii "_offset\0"
	.byte	0x6
	.word	0x115
	.long	0x172
	.byte	0x58
	.uleb128 0x17
	.ascii "_seek64\0"
	.byte	0x6
	.word	0x116
	.long	0x880
	.byte	0x60
	.uleb128 0x17
	.ascii "_lock\0"
	.byte	0x6
	.word	0x119
	.long	0x23c
	.byte	0x64
	.uleb128 0x17
	.ascii "_mbstate\0"
	.byte	0x6
	.word	0x11b
	.long	0x22a
	.byte	0x68
	.byte	0
	.uleb128 0x14
	.long	0x191
	.long	0x880
	.uleb128 0x15
	.long	0x4aa
	.uleb128 0x15
	.long	0x164
	.uleb128 0x15
	.long	0x191
	.uleb128 0x15
	.long	0xc1
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x862
	.uleb128 0x5
	.ascii "__FILE\0"
	.byte	0x6
	.word	0x11d
	.long	0x6e2
	.uleb128 0x19
	.ascii "_glue\0"
	.byte	0xc
	.byte	0x6
	.word	0x123
	.long	0x8d3
	.uleb128 0x17
	.ascii "_next\0"
	.byte	0x6
	.word	0x125
	.long	0x8d3
	.byte	0
	.uleb128 0x17
	.ascii "_niobs\0"
	.byte	0x6
	.word	0x126
	.long	0xc1
	.byte	0x4
	.uleb128 0x17
	.ascii "_iobs\0"
	.byte	0x6
	.word	0x127
	.long	0x8d9
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0x895
	.uleb128 0xc
	.byte	0x4
	.long	0x886
	.uleb128 0x19
	.ascii "_rand48\0"
	.byte	0xe
	.byte	0x6
	.word	0x13f
	.long	0x91d
	.uleb128 0x17
	.ascii "_seed\0"
	.byte	0x6
	.word	0x140
	.long	0x91d
	.byte	0
	.uleb128 0x17
	.ascii "_mult\0"
	.byte	0x6
	.word	0x141
	.long	0x91d
	.byte	0x6
	.uleb128 0x17
	.ascii "_add\0"
	.byte	0x6
	.word	0x142
	.long	0xab
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.long	0xab
	.long	0x92d
	.uleb128 0x9
	.long	0x1f5
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.word	0x259
	.long	0xada
	.uleb128 0x17
	.ascii "_unused_rand\0"
	.byte	0x6
	.word	0x25b
	.long	0x9b
	.byte	0
	.uleb128 0x17
	.ascii "_strtok_last\0"
	.byte	0x6
	.word	0x25c
	.long	0x24c
	.byte	0x4
	.uleb128 0x17
	.ascii "_asctime_buf\0"
	.byte	0x6
	.word	0x25d
	.long	0xada
	.byte	0x8
	.uleb128 0x17
	.ascii "_localtime_buf\0"
	.byte	0x6
	.word	0x25e
	.long	0x2e4
	.byte	0x24
	.uleb128 0x17
	.ascii "_gamma_signgam\0"
	.byte	0x6
	.word	0x25f
	.long	0xc1
	.byte	0x48
	.uleb128 0x17
	.ascii "_rand_next\0"
	.byte	0x6
	.word	0x260
	.long	0x126
	.byte	0x50
	.uleb128 0x17
	.ascii "_r48\0"
	.byte	0x6
	.word	0x261
	.long	0x8df
	.byte	0x58
	.uleb128 0x17
	.ascii "_mblen_state\0"
	.byte	0x6
	.word	0x262
	.long	0x22a
	.byte	0x68
	.uleb128 0x17
	.ascii "_mbtowc_state\0"
	.byte	0x6
	.word	0x263
	.long	0x22a
	.byte	0x70
	.uleb128 0x17
	.ascii "_wctomb_state\0"
	.byte	0x6
	.word	0x264
	.long	0x22a
	.byte	0x78
	.uleb128 0x17
	.ascii "_l64a_buf\0"
	.byte	0x6
	.word	0x265
	.long	0xaea
	.byte	0x80
	.uleb128 0x17
	.ascii "_signal_buf\0"
	.byte	0x6
	.word	0x266
	.long	0xafa
	.byte	0x88
	.uleb128 0x17
	.ascii "_getdate_err\0"
	.byte	0x6
	.word	0x267
	.long	0xc1
	.byte	0xa0
	.uleb128 0x17
	.ascii "_mbrlen_state\0"
	.byte	0x6
	.word	0x268
	.long	0x22a
	.byte	0xa4
	.uleb128 0x17
	.ascii "_mbrtowc_state\0"
	.byte	0x6
	.word	0x269
	.long	0x22a
	.byte	0xac
	.uleb128 0x17
	.ascii "_mbsrtowcs_state\0"
	.byte	0x6
	.word	0x26a
	.long	0x22a
	.byte	0xb4
	.uleb128 0x17
	.ascii "_wcrtomb_state\0"
	.byte	0x6
	.word	0x26b
	.long	0x22a
	.byte	0xbc
	.uleb128 0x17
	.ascii "_wcsrtombs_state\0"
	.byte	0x6
	.word	0x26c
	.long	0x22a
	.byte	0xc4
	.uleb128 0x17
	.ascii "_h_errno\0"
	.byte	0x6
	.word	0x26d
	.long	0xc1
	.byte	0xcc
	.byte	0
	.uleb128 0x8
	.long	0x252
	.long	0xaea
	.uleb128 0x9
	.long	0x1f5
	.byte	0x19
	.byte	0
	.uleb128 0x8
	.long	0x252
	.long	0xafa
	.uleb128 0x9
	.long	0x1f5
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.long	0x252
	.long	0xb0a
	.uleb128 0x9
	.long	0x1f5
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.word	0x272
	.long	0xb36
	.uleb128 0x17
	.ascii "_nextf\0"
	.byte	0x6
	.word	0x275
	.long	0xb36
	.byte	0
	.uleb128 0x17
	.ascii "_nmalloc\0"
	.byte	0x6
	.word	0x276
	.long	0xb46
	.byte	0x78
	.byte	0
	.uleb128 0x8
	.long	0x486
	.long	0xb46
	.uleb128 0x9
	.long	0x1f5
	.byte	0x1d
	.byte	0
	.uleb128 0x8
	.long	0x9b
	.long	0xb56
	.uleb128 0x9
	.long	0x1f5
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.word	0x257
	.long	0xb7f
	.uleb128 0x1c
	.ascii "_reent\0"
	.byte	0x6
	.word	0x26e
	.long	0x92d
	.uleb128 0x1c
	.ascii "_unused\0"
	.byte	0x6
	.word	0x277
	.long	0xb0a
	.byte	0
	.uleb128 0x8
	.long	0x252
	.long	0xb8f
	.uleb128 0x9
	.long	0x1f5
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.ascii "__locale_t\0"
	.uleb128 0xc
	.byte	0x4
	.long	0xb8f
	.uleb128 0x1e
	.long	0xbac
	.uleb128 0x15
	.long	0x4aa
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xba1
	.uleb128 0xc
	.byte	0x4
	.long	0x2ce
	.uleb128 0x1e
	.long	0xbc3
	.uleb128 0x15
	.long	0xc1
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xbc9
	.uleb128 0xc
	.byte	0x4
	.long	0xbb8
	.uleb128 0x8
	.long	0x886
	.long	0xbdf
	.uleb128 0x9
	.long	0x1f5
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.ascii "_impure_ptr\0"
	.byte	0x6
	.word	0x307
	.long	0x4aa
	.uleb128 0x1f
	.ascii "_global_impure_ptr\0"
	.byte	0x6
	.word	0x308
	.long	0x4b0
	.uleb128 0x20
	.ascii "suboptarg\0"
	.byte	0x7
	.byte	0x63
	.long	0x24c
	.uleb128 0x2
	.ascii "__gnuc_va_list\0"
	.byte	0x8
	.byte	0x28
	.long	0xc35
	.uleb128 0x21
	.byte	0x4
	.ascii "__builtin_va_list\0"
	.long	0x252
	.uleb128 0x2
	.ascii "va_list\0"
	.byte	0x8
	.byte	0x63
	.long	0xc1f
	.uleb128 0x2
	.ascii "uint8_t\0"
	.byte	0x9
	.byte	0x18
	.long	0xf7
	.uleb128 0x2
	.ascii "FILE\0"
	.byte	0xa
	.byte	0x42
	.long	0x886
	.uleb128 0x2
	.ascii "bf_t\0"
	.byte	0xb
	.byte	0x9
	.long	0xc83
	.uleb128 0x11
	.ascii "_bdf_font_struct\0"
	.word	0x4a4
	.byte	0xc
	.byte	0x10
	.long	0xf4b
	.uleb128 0x12
	.secrel32	LASF1
	.byte	0xc
	.byte	0x12
	.long	0xc1
	.byte	0
	.uleb128 0xb
	.ascii "glyph_list\0"
	.byte	0xc
	.byte	0x14
	.long	0x1130
	.byte	0x4
	.uleb128 0xb
	.ascii "glyph_cnt\0"
	.byte	0xc
	.byte	0x15
	.long	0xc1
	.byte	0x8
	.uleb128 0xb
	.ascii "glyph_max\0"
	.byte	0xc
	.byte	0x16
	.long	0xc1
	.byte	0xc
	.uleb128 0xb
	.ascii "line_buf\0"
	.byte	0xc
	.byte	0x19
	.long	0x113c
	.byte	0x10
	.uleb128 0x10
	.ascii "line_pos\0"
	.byte	0xc
	.byte	0x1a
	.long	0xc1
	.word	0x410
	.uleb128 0x10
	.ascii "is_bitmap_parsing\0"
	.byte	0xc
	.byte	0x1b
	.long	0xc1
	.word	0x414
	.uleb128 0x22
	.secrel32	LASF2
	.byte	0xc
	.byte	0x1d
	.long	0x166
	.word	0x418
	.uleb128 0x22
	.secrel32	LASF3
	.byte	0xc
	.byte	0x1f
	.long	0x166
	.word	0x41c
	.uleb128 0x22
	.secrel32	LASF4
	.byte	0xc
	.byte	0x20
	.long	0x166
	.word	0x420
	.uleb128 0x10
	.ascii "bbx_w\0"
	.byte	0xc
	.byte	0x22
	.long	0x166
	.word	0x424
	.uleb128 0x10
	.ascii "bbx_h\0"
	.byte	0xc
	.byte	0x23
	.long	0x166
	.word	0x428
	.uleb128 0x10
	.ascii "bbx_x\0"
	.byte	0xc
	.byte	0x24
	.long	0x166
	.word	0x42c
	.uleb128 0x10
	.ascii "bbx_y\0"
	.byte	0xc
	.byte	0x25
	.long	0x166
	.word	0x430
	.uleb128 0x10
	.ascii "bitmap_x\0"
	.byte	0xc
	.byte	0x27
	.long	0xc1
	.word	0x434
	.uleb128 0x10
	.ascii "bitmap_y\0"
	.byte	0xc
	.byte	0x28
	.long	0xc1
	.word	0x438
	.uleb128 0x10
	.ascii "glyph_pos\0"
	.byte	0xc
	.byte	0x29
	.long	0xc1
	.word	0x43c
	.uleb128 0x10
	.ascii "fp\0"
	.byte	0xc
	.byte	0x2a
	.long	0x114d
	.word	0x440
	.uleb128 0x10
	.ascii "str_font\0"
	.byte	0xc
	.byte	0x2c
	.long	0x24c
	.word	0x444
	.uleb128 0x10
	.ascii "str_copyright\0"
	.byte	0xc
	.byte	0x2d
	.long	0x24c
	.word	0x448
	.uleb128 0x10
	.ascii "selected_glyphs\0"
	.byte	0xc
	.byte	0x2f
	.long	0x166
	.word	0x44c
	.uleb128 0x22
	.secrel32	LASF5
	.byte	0xc
	.byte	0x31
	.long	0xc1
	.word	0x450
	.uleb128 0x10
	.ascii "max\0"
	.byte	0xc
	.byte	0x33
	.long	0xf88
	.word	0x454
	.uleb128 0x10
	.ascii "enc_w\0"
	.byte	0xc
	.byte	0x36
	.long	0x166
	.word	0x464
	.uleb128 0x10
	.ascii "enc_h\0"
	.byte	0xc
	.byte	0x37
	.long	0x166
	.word	0x468
	.uleb128 0x10
	.ascii "enc_x\0"
	.byte	0xc
	.byte	0x38
	.long	0x166
	.word	0x46c
	.uleb128 0x10
	.ascii "enc_y\0"
	.byte	0xc
	.byte	0x39
	.long	0x166
	.word	0x470
	.uleb128 0x10
	.ascii "dx_min\0"
	.byte	0xc
	.byte	0x3c
	.long	0x166
	.word	0x474
	.uleb128 0x10
	.ascii "dx_max\0"
	.byte	0xc
	.byte	0x3d
	.long	0x166
	.word	0x478
	.uleb128 0x10
	.ascii "x_min\0"
	.byte	0xc
	.byte	0x40
	.long	0x166
	.word	0x47c
	.uleb128 0x10
	.ascii "x_max\0"
	.byte	0xc
	.byte	0x41
	.long	0x166
	.word	0x480
	.uleb128 0x10
	.ascii "bbx_x_max_bit_size\0"
	.byte	0xc
	.byte	0x44
	.long	0xc1
	.word	0x484
	.uleb128 0x10
	.ascii "bbx_y_max_bit_size\0"
	.byte	0xc
	.byte	0x45
	.long	0xc1
	.word	0x488
	.uleb128 0x10
	.ascii "bbx_w_max_bit_size\0"
	.byte	0xc
	.byte	0x46
	.long	0xc1
	.word	0x48c
	.uleb128 0x10
	.ascii "bbx_h_max_bit_size\0"
	.byte	0xc
	.byte	0x47
	.long	0xc1
	.word	0x490
	.uleb128 0x10
	.ascii "dx_max_bit_size\0"
	.byte	0xc
	.byte	0x48
	.long	0xc1
	.word	0x494
	.uleb128 0x22
	.secrel32	LASF6
	.byte	0xc
	.byte	0x4b
	.long	0x111e
	.word	0x498
	.uleb128 0x22
	.secrel32	LASF7
	.byte	0xc
	.byte	0x4c
	.long	0xc1
	.word	0x49c
	.uleb128 0x22
	.secrel32	LASF8
	.byte	0xc
	.byte	0x4d
	.long	0xc1
	.word	0x4a0
	.byte	0
	.uleb128 0xe
	.ascii "_bbx_struct\0"
	.byte	0x10
	.byte	0xb
	.byte	0xc
	.long	0xf88
	.uleb128 0xb
	.ascii "w\0"
	.byte	0xb
	.byte	0xe
	.long	0x166
	.byte	0
	.uleb128 0xb
	.ascii "h\0"
	.byte	0xb
	.byte	0xf
	.long	0x166
	.byte	0x4
	.uleb128 0xb
	.ascii "x\0"
	.byte	0xb
	.byte	0x10
	.long	0x166
	.byte	0x8
	.uleb128 0xb
	.ascii "y\0"
	.byte	0xb
	.byte	0x11
	.long	0x166
	.byte	0xc
	.byte	0
	.uleb128 0x2
	.ascii "bbx_t\0"
	.byte	0xb
	.byte	0x13
	.long	0xf4b
	.uleb128 0xe
	.ascii "_bdf_glyph_struct\0"
	.byte	0x60
	.byte	0xb
	.byte	0x16
	.long	0x1118
	.uleb128 0xb
	.ascii "bf\0"
	.byte	0xb
	.byte	0x18
	.long	0x1118
	.byte	0
	.uleb128 0x12
	.secrel32	LASF2
	.byte	0xb
	.byte	0x1a
	.long	0x166
	.byte	0x4
	.uleb128 0xb
	.ascii "map_to\0"
	.byte	0xb
	.byte	0x1b
	.long	0x166
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF3
	.byte	0xb
	.byte	0x1d
	.long	0x166
	.byte	0xc
	.uleb128 0x12
	.secrel32	LASF4
	.byte	0xb
	.byte	0x1e
	.long	0x166
	.byte	0x10
	.uleb128 0xb
	.ascii "bbx\0"
	.byte	0xb
	.byte	0x20
	.long	0xf88
	.byte	0x14
	.uleb128 0xb
	.ascii "shift_x\0"
	.byte	0xb
	.byte	0x21
	.long	0x166
	.byte	0x24
	.uleb128 0xb
	.ascii "bitmap_data\0"
	.byte	0xb
	.byte	0x23
	.long	0x111e
	.byte	0x28
	.uleb128 0xb
	.ascii "bitmap_width\0"
	.byte	0xb
	.byte	0x24
	.long	0xc1
	.byte	0x2c
	.uleb128 0xb
	.ascii "bitmap_height\0"
	.byte	0xb
	.byte	0x25
	.long	0xc1
	.byte	0x30
	.uleb128 0x12
	.secrel32	LASF6
	.byte	0xb
	.byte	0x2a
	.long	0x111e
	.byte	0x34
	.uleb128 0x12
	.secrel32	LASF7
	.byte	0xb
	.byte	0x2b
	.long	0xc1
	.byte	0x38
	.uleb128 0x12
	.secrel32	LASF8
	.byte	0xb
	.byte	0x2c
	.long	0xc1
	.byte	0x3c
	.uleb128 0xb
	.ascii "target_bit_pos\0"
	.byte	0xb
	.byte	0x2d
	.long	0xc1
	.byte	0x40
	.uleb128 0xb
	.ascii "rle_bits_per_0\0"
	.byte	0xb
	.byte	0x31
	.long	0x9b
	.byte	0x44
	.uleb128 0xb
	.ascii "rle_bits_per_1\0"
	.byte	0xb
	.byte	0x32
	.long	0x9b
	.byte	0x48
	.uleb128 0xb
	.ascii "rle_is_first\0"
	.byte	0xb
	.byte	0x34
	.long	0xc1
	.byte	0x4c
	.uleb128 0xb
	.ascii "rle_bitcnt\0"
	.byte	0xb
	.byte	0x35
	.long	0x9b
	.byte	0x50
	.uleb128 0xb
	.ascii "rle_last_0\0"
	.byte	0xb
	.byte	0x36
	.long	0x9b
	.byte	0x54
	.uleb128 0xb
	.ascii "rle_last_1\0"
	.byte	0xb
	.byte	0x37
	.long	0x9b
	.byte	0x58
	.uleb128 0xb
	.ascii "width_deviation\0"
	.byte	0xb
	.byte	0x39
	.long	0x166
	.byte	0x5c
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xc77
	.uleb128 0xc
	.byte	0x4
	.long	0xc5c
	.uleb128 0x2
	.ascii "bg_t\0"
	.byte	0xb
	.byte	0x3c
	.long	0xf95
	.uleb128 0xc
	.byte	0x4
	.long	0x1136
	.uleb128 0xc
	.byte	0x4
	.long	0x1124
	.uleb128 0x8
	.long	0x252
	.long	0x114d
	.uleb128 0x23
	.long	0x1f5
	.word	0x3ff
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xc6b
	.uleb128 0x24
	.ascii "bf_OpenFromFile\0"
	.byte	0x1
	.word	0x286
	.long	0x1118
	.long	LFB37
	.long	LFE37-LFB37
	.uleb128 0x1
	.byte	0x9c
	.long	0x11e8
	.uleb128 0x25
	.ascii "bdf_filename\0"
	.byte	0x1
	.word	0x286
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x26
	.secrel32	LASF1
	.byte	0x1
	.word	0x286
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x26
	.secrel32	LASF5
	.byte	0x1
	.word	0x286
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x25
	.ascii "map_str\0"
	.byte	0x1
	.word	0x286
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x25
	.ascii "font_format\0"
	.byte	0x1
	.word	0x286
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x27
	.ascii "bf\0"
	.byte	0x1
	.word	0x288
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x24
	.ascii "bf_WriteU8G2CByFilename\0"
	.byte	0x1
	.word	0x273
	.long	0xc1
	.long	LFB36
	.long	LFE36-LFB36
	.uleb128 0x1
	.byte	0x9c
	.long	0x1260
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x273
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x26
	.secrel32	LASF9
	.byte	0x1
	.word	0x273
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x26
	.secrel32	LASF10
	.byte	0x1
	.word	0x273
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x26
	.secrel32	LASF11
	.byte	0x1
	.word	0x273
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x27
	.ascii "fp\0"
	.byte	0x1
	.word	0x275
	.long	0x114d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x24
	.ascii "bf_WriteUCGCByFilename\0"
	.byte	0x1
	.word	0x262
	.long	0xc1
	.long	LFB35
	.long	LFE35-LFB35
	.uleb128 0x1
	.byte	0x9c
	.long	0x12d7
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x262
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x26
	.secrel32	LASF9
	.byte	0x1
	.word	0x262
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x26
	.secrel32	LASF10
	.byte	0x1
	.word	0x262
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x26
	.secrel32	LASF11
	.byte	0x1
	.word	0x262
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x27
	.ascii "fp\0"
	.byte	0x1
	.word	0x264
	.long	0x114d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x24
	.ascii "bf_WriteU8G2CByFP\0"
	.byte	0x1
	.word	0x246
	.long	0xc1
	.long	LFB34
	.long	LFE34-LFB34
	.uleb128 0x1
	.byte	0x9c
	.long	0x135a
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x246
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "out_fp\0"
	.byte	0x1
	.word	0x246
	.long	0x114d
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x26
	.secrel32	LASF10
	.byte	0x1
	.word	0x246
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x26
	.secrel32	LASF11
	.byte	0x1
	.word	0x246
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x27
	.ascii "i\0"
	.byte	0x1
	.word	0x248
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x28
	.secrel32	LASF12
	.byte	0x1
	.word	0x249
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x24
	.ascii "bf_WriteUCGCByFP\0"
	.byte	0x1
	.word	0x22a
	.long	0xc1
	.long	LFB33
	.long	LFE33-LFB33
	.uleb128 0x1
	.byte	0x9c
	.long	0x13dc
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x22a
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "out_fp\0"
	.byte	0x1
	.word	0x22a
	.long	0x114d
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x26
	.secrel32	LASF10
	.byte	0x1
	.word	0x22a
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x26
	.secrel32	LASF11
	.byte	0x1
	.word	0x22a
	.long	0x678
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x27
	.ascii "i\0"
	.byte	0x1
	.word	0x22c
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x28
	.secrel32	LASF12
	.byte	0x1
	.word	0x22d
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x29
	.ascii "bf_ShowMonospaceStatistics\0"
	.byte	0x1
	.word	0x1ff
	.long	LFB32
	.long	LFE32-LFB32
	.uleb128 0x1
	.byte	0x9c
	.long	0x1460
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x1ff
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "i\0"
	.byte	0x1
	.word	0x201
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.word	0x202
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x27
	.ascii "cnt\0"
	.byte	0x1
	.word	0x203
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x27
	.ascii "max\0"
	.byte	0x1
	.word	0x204
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x27
	.ascii "sum\0"
	.byte	0x1
	.word	0x205
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x29
	.ascii "bf_CalculateMaxBitFieldSize\0"
	.byte	0x1
	.word	0x192
	.long	LFB31
	.long	LFE31-LFB31
	.uleb128 0x1
	.byte	0x9c
	.long	0x14db
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x192
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "i\0"
	.byte	0x1
	.word	0x194
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.word	0x195
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x27
	.ascii "bs\0"
	.byte	0x1
	.word	0x196
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x27
	.ascii "local_bbx\0"
	.byte	0x1
	.word	0x197
	.long	0xf88
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.uleb128 0x2a
	.ascii "bf_copy_bbx_and_update_shift\0"
	.byte	0x1
	.word	0x15b
	.long	LFB30
	.long	LFE30-LFB30
	.uleb128 0x1
	.byte	0x9c
	.long	0x153d
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x15b
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "target_bbx\0"
	.byte	0x1
	.word	0x15b
	.long	0x153d
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x25
	.ascii "bg\0"
	.byte	0x1
	.word	0x15b
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0xc
	.byte	0x4
	.long	0xf88
	.uleb128 0x24
	.ascii "get_signed_bit_size\0"
	.byte	0x1
	.word	0x154
	.long	0xc1
	.long	LFB29
	.long	LFE29-LFB29
	.uleb128 0x1
	.byte	0x9c
	.long	0x157b
	.uleb128 0x25
	.ascii "v\0"
	.byte	0x1
	.word	0x154
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x2b
	.ascii "get_unsigned_bit_size\0"
	.byte	0x1
	.word	0x149
	.long	0xc1
	.long	LFB28
	.long	LFE28-LFB28
	.uleb128 0x1
	.byte	0x9c
	.long	0x15c2
	.uleb128 0x25
	.ascii "v\0"
	.byte	0x1
	.word	0x149
	.long	0x140
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "i\0"
	.byte	0x1
	.word	0x14b
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x29
	.ascii "bf_CalculateMinMaxDWidth\0"
	.byte	0x1
	.word	0x124
	.long	LFB27
	.long	LFE27-LFB27
	.uleb128 0x1
	.byte	0x9c
	.long	0x1617
	.uleb128 0x25
	.ascii "bf\0"
	.byte	0x1
	.word	0x124
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x27
	.ascii "i\0"
	.byte	0x1
	.word	0x126
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x27
	.ascii "bg\0"
	.byte	0x1
	.word	0x127
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x2c
	.ascii "bf_CalculateMaxBBX\0"
	.byte	0x1
	.byte	0xed
	.long	LFB26
	.long	LFE26-LFB26
	.uleb128 0x1
	.byte	0x9c
	.long	0x1687
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0xed
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0xef
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "is_first\0"
	.byte	0x1
	.byte	0xf0
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x2e
	.ascii "enc_idx\0"
	.byte	0x1
	.byte	0xf1
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x2e
	.ascii "bg\0"
	.byte	0x1
	.byte	0xf2
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x2f
	.ascii "bf_GetIndexByEncoding\0"
	.byte	0x1
	.byte	0xe0
	.long	0xc1
	.long	LFB25
	.long	LFE25-LFB25
	.uleb128 0x1
	.byte	0x9c
	.long	0x16e7
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0xe0
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x30
	.secrel32	LASF2
	.byte	0x1
	.byte	0xe0
	.long	0x166
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0xe2
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x2e
	.ascii "bg\0"
	.byte	0x1
	.byte	0xe3
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x2c
	.ascii "bf_ShowAllGlyphs\0"
	.byte	0x1
	.byte	0xd2
	.long	LFB24
	.long	LFE24-LFB24
	.uleb128 0x1
	.byte	0x9c
	.long	0x173e
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0xd2
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.ascii "bbx\0"
	.byte	0x1
	.byte	0xd2
	.long	0x153d
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0xd4
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "bg\0"
	.byte	0x1
	.byte	0xd5
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x2c
	.ascii "bf_ReduceAllGlyph\0"
	.byte	0x1
	.byte	0xb7
	.long	LFB23
	.long	LFE23-LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0x17a8
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0xb7
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0xb9
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "bg\0"
	.byte	0x1
	.byte	0xba
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x2e
	.ascii "red_x\0"
	.byte	0x1
	.byte	0xbb
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x2e
	.ascii "red_y\0"
	.byte	0x1
	.byte	0xbb
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x31
	.ascii "bf_CalculateSelectedNumberOfGlyphs\0"
	.byte	0x1
	.byte	0xa5
	.long	LFB22
	.long	LFE22-LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x1803
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0xa5
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0xa7
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x2e
	.ascii "bg\0"
	.byte	0x1
	.byte	0xa8
	.long	0x1136
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x31
	.ascii "bf_ClearTargetData\0"
	.byte	0x1
	.byte	0x9d
	.long	LFB21
	.long	LFE21-LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0x1841
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x9d
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0x9f
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x32
	.ascii "bf_AddTargetData\0"
	.byte	0x1
	.byte	0x93
	.long	0xc1
	.long	LFB20
	.long	LFE20-LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x1884
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x93
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.ascii "data\0"
	.byte	0x1
	.byte	0x93
	.long	0xc5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x33
	.ascii "bf_extend_target_data\0"
	.byte	0x1
	.byte	0x7c
	.long	0xc1
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x18e8
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x7c
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "extend\0"
	.byte	0x1
	.byte	0x7e
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0x7f
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2e
	.ascii "ptr\0"
	.byte	0x1
	.byte	0x80
	.long	0x164
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x32
	.ascii "bf_AddGlyph\0"
	.byte	0x1
	.byte	0x6e
	.long	0xc1
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x1917
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x6e
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x33
	.ascii "bf_extend\0"
	.byte	0x1
	.byte	0x59
	.long	0xc1
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x1963
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x59
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "extend\0"
	.byte	0x1
	.byte	0x5b
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x2e
	.ascii "ptr\0"
	.byte	0x1
	.byte	0x5c
	.long	0x164
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2c
	.ascii "bf_Close\0"
	.byte	0x1
	.byte	0x4d
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x198b
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x4d
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x2c
	.ascii "bf_Clear\0"
	.byte	0x1
	.byte	0x3c
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x19bf
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x3c
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2e
	.ascii "i\0"
	.byte	0x1
	.byte	0x3e
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x32
	.ascii "bf_Open\0"
	.byte	0x1
	.byte	0x1f
	.long	0x1118
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a06
	.uleb128 0x30
	.secrel32	LASF1
	.byte	0x1
	.byte	0x1f
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x30
	.secrel32	LASF5
	.byte	0x1
	.byte	0x1f
	.long	0xc1
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x2e
	.ascii "bf\0"
	.byte	0x1
	.byte	0x21
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2c
	.ascii "bf_Log\0"
	.byte	0x1
	.byte	0x10
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a48
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x10
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.ascii "fmt\0"
	.byte	0x1
	.byte	0x10
	.long	0x24c
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x34
	.uleb128 0x2e
	.ascii "va\0"
	.byte	0x1
	.byte	0x12
	.long	0xc4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x35
	.ascii "bf_Error\0"
	.byte	0x1
	.byte	0x7
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2d
	.ascii "bf\0"
	.byte	0x1
	.byte	0x7
	.long	0x1118
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2d
	.ascii "fmt\0"
	.byte	0x1
	.byte	0x7
	.long	0x24c
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x34
	.uleb128 0x2e
	.ascii "va\0"
	.byte	0x1
	.byte	0x9
	.long	0xc4d
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x2116
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
	.uleb128 0x30
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x34
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x35
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
LASF7:
	.ascii "target_max\0"
LASF12:
	.ascii "bytes_per_line\0"
LASF3:
	.ascii "dwidth_x\0"
LASF4:
	.ascii "dwidth_y\0"
LASF8:
	.ascii "target_cnt\0"
LASF10:
	.ascii "fontname\0"
LASF5:
	.ascii "bbx_mode\0"
LASF0:
	.ascii "_on_exit_args\0"
LASF2:
	.ascii "encoding\0"
LASF9:
	.ascii "filename\0"
LASF11:
	.ascii "indent\0"
LASF1:
	.ascii "is_verbose\0"
LASF6:
	.ascii "target_data\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_vprintf;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_realloc;	.scl	2;	.type	32;	.endef
	.def	_bg_Open;	.scl	2;	.type	32;	.endef
	.def	_bg_ReduceGlyph;	.scl	2;	.type	32;	.endef
	.def	_bg_ShowBitmap;	.scl	2;	.type	32;	.endef
	.def	_bg_Max;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_fputc;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_bf_ParseFile;	.scl	2;	.type	32;	.endef
	.def	_bf_Map;	.scl	2;	.type	32;	.endef
	.def	_bf_RLECompressAllGlyphs;	.scl	2;	.type	32;	.endef
	.def	_bf_Generate8x8Font;	.scl	2;	.type	32;	.endef
