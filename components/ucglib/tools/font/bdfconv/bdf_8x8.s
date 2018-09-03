	.file	"bdf_8x8.c"
	.text
Ltext0:
	.globl	_bg_8x8_convert
	.def	_bg_8x8_convert;	.scl	2;	.type	32;	.endef
_bg_8x8_convert:
LFB12:
	.file 1 "bdf_8x8.c"
	.loc 1 21 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 26 0
	cmpl	$0, 12(%ebp)
	jne	L2
	.loc 1 27 0
	movl	8(%ebp), %eax
	addl	$20, %eax
	movl	%eax, 12(%ebp)
L2:
	.loc 1 29 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_ClearTargetData
	.loc 1 31 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$8, %eax
	je	L3
	.loc 1 32 0
	movl	$0, %eax
	jmp	L4
L3:
	.loc 1 33 0
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	$8, %eax
	je	L5
	.loc 1 34 0
	movl	$0, %eax
	jmp	L4
L5:
	.loc 1 54 0
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -12(%ebp)
	jmp	L6
L11:
	.loc 1 56 0
	movl	$0, -20(%ebp)
	.loc 1 57 0
	movl	12(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	addl	%edx, %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	L7
L9:
	.loc 1 59 0
	sarl	-20(%ebp)
	.loc 1 60 0
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBBXPixel
	testl	%eax, %eax
	je	L8
	.loc 1 62 0
	orl	$128, -20(%ebp)
L8:
	.loc 1 57 0 discriminator 2
	subl	$1, -16(%ebp)
L7:
	.loc 1 57 0 is_stmt 0 discriminator 1
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	-16(%ebp), %eax
	jle	L9
	.loc 1 65 0 is_stmt 1
	movl	-20(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetData
	testl	%eax, %eax
	jns	L10
	.loc 1 66 0
	movl	$0, %eax
	jmp	L4
L10:
	.loc 1 54 0 discriminator 2
	addl	$1, -12(%ebp)
L6:
	.loc 1 54 0 is_stmt 0 discriminator 1
	movl	12(%ebp), %eax
	movl	8(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	cmpl	-12(%ebp), %eax
	jg	L11
	.loc 1 69 0 is_stmt 1
	movl	$1, %eax
L4:
	.loc 1 70 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "Generate8x8Font: Error, glyph width is not 8, width=%d, encoding=%d\0"
	.align 4
LC1:
	.ascii "Generate8x8Font: Error, glyph height is not 8, height=%d, encoding=%d\0"
	.align 4
LC2:
	.ascii "Generate8x8Font: Error, 8x8 conversion, encoding=%d\0"
	.align 4
LC3:
	.ascii "Generate8x8Font: Error, glyph size is not 8, size=%d, encoding=%d\0"
LC4:
	.ascii "Generate8x8Font: Font size %d\0"
	.text
	.globl	_bf_Generate8x8Font
	.def	_bf_Generate8x8Font;	.scl	2;	.type	32;	.endef
_bf_Generate8x8Font:
LFB13:
	.loc 1 74 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$72, %esp
	.loc 1 83 0
	movl	$0, -12(%ebp)
	jmp	L13
L17:
	.loc 1 85 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	.loc 1 86 0
	movl	-36(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L14
	.loc 1 88 0
	movl	-36(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-52(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_copy_bbx_and_update_shift
	.loc 1 90 0
	movl	-52(%ebp), %eax
	cmpl	$8, %eax
	je	L15
	.loc 1 92 0
	movl	-36(%ebp), %eax
	movl	4(%eax), %edx
	movl	-52(%ebp), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	jmp	L14
L15:
	.loc 1 96 0
	movl	-48(%ebp), %eax
	cmpl	$8, %eax
	je	L16
	.loc 1 98 0
	movl	-36(%ebp), %eax
	movl	4(%eax), %edx
	movl	-48(%ebp), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	jmp	L14
L16:
	.loc 1 102 0
	leal	-52(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_8x8_convert
	testl	%eax, %eax
	jne	L14
	.loc 1 104 0
	movl	-36(%ebp), %eax
	movl	4(%eax), %edx
	movl	-36(%ebp), %eax
	movl	60(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC2, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
L14:
	.loc 1 83 0 discriminator 2
	addl	$1, -12(%ebp)
L13:
	.loc 1 83 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L17
	.loc 1 113 0 is_stmt 1
	movl	$-1, -24(%ebp)
	.loc 1 114 0
	movl	$-1, -28(%ebp)
	.loc 1 116 0
	movl	$0, -16(%ebp)
	jmp	L18
L24:
	.loc 1 118 0
	movl	$0, -12(%ebp)
	jmp	L19
L23:
	.loc 1 120 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	.loc 1 121 0
	movl	-36(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-16(%ebp), %eax
	jne	L20
	.loc 1 123 0
	movl	-36(%ebp), %eax
	movl	52(%eax), %eax
	testl	%eax, %eax
	je	L20
	.loc 1 126 0
	movl	-36(%ebp), %eax
	movl	60(%eax), %eax
	cmpl	$8, %eax
	je	L21
	.loc 1 128 0
	movl	-36(%ebp), %eax
	movl	4(%eax), %edx
	movl	-36(%ebp), %eax
	movl	60(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC3, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	jmp	L20
L21:
	.loc 1 132 0
	cmpl	$0, -24(%ebp)
	jns	L22
	.loc 1 133 0
	movl	-16(%ebp), %eax
	movl	%eax, -24(%ebp)
L22:
	.loc 1 134 0
	movl	-16(%ebp), %eax
	movl	%eax, -28(%ebp)
L20:
	.loc 1 118 0 discriminator 2
	addl	$1, -12(%ebp)
L19:
	.loc 1 118 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L23
	.loc 1 116 0 is_stmt 1 discriminator 2
	addl	$1, -16(%ebp)
L18:
	.loc 1 116 0 is_stmt 0 discriminator 1
	cmpl	$255, -16(%ebp)
	jle	L24
	.loc 1 143 0 is_stmt 1
	movl	-24(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 144 0
	movl	-28(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 147 0
	movl	-24(%ebp), %eax
	movl	%eax, -16(%ebp)
	jmp	L25
L34:
	.loc 1 149 0
	movl	$0, -32(%ebp)
	.loc 1 150 0
	movl	$0, -12(%ebp)
	jmp	L26
L30:
	.loc 1 152 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -36(%ebp)
	.loc 1 153 0
	movl	-36(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-16(%ebp), %eax
	jne	L27
	.loc 1 155 0
	movl	-36(%ebp), %eax
	movl	52(%eax), %eax
	testl	%eax, %eax
	je	L27
	.loc 1 158 0
	movl	-36(%ebp), %eax
	movl	60(%eax), %eax
	cmpl	$8, %eax
	jne	L27
	.loc 1 160 0
	movl	$0, -20(%ebp)
	jmp	L28
L29:
	.loc 1 162 0 discriminator 3
	movl	-36(%ebp), %eax
	movl	52(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 160 0 discriminator 3
	addl	$1, -20(%ebp)
L28:
	.loc 1 160 0 is_stmt 0 discriminator 1
	movl	-36(%ebp), %eax
	movl	60(%eax), %eax
	cmpl	-20(%ebp), %eax
	jg	L29
	.loc 1 164 0 is_stmt 1
	movl	$1, -32(%ebp)
L27:
	.loc 1 150 0 discriminator 2
	addl	$1, -12(%ebp)
L26:
	.loc 1 150 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L30
	.loc 1 169 0 is_stmt 1
	cmpl	$0, -32(%ebp)
	jne	L31
	.loc 1 171 0
	movl	$0, -20(%ebp)
	jmp	L32
L33:
	.loc 1 173 0 discriminator 3
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 171 0 discriminator 3
	addl	$1, -20(%ebp)
L32:
	.loc 1 171 0 is_stmt 0 discriminator 1
	cmpl	$7, -20(%ebp)
	jle	L33
L31:
	.loc 1 147 0 is_stmt 1 discriminator 2
	addl	$1, -16(%ebp)
L25:
	.loc 1 147 0 is_stmt 0 discriminator 1
	movl	-16(%ebp), %eax
	cmpl	-28(%ebp), %eax
	jle	L34
	.loc 1 179 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC4, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 180 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
Letext0:
	.file 2 "/usr/include/machine/_default_types.h"
	.file 3 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 4 "/usr/include/sys/lock.h"
	.file 5 "/usr/include/sys/_types.h"
	.file 6 "/usr/include/sys/reent.h"
	.file 7 "/usr/include/sys/_stdint.h"
	.file 8 "/usr/include/stdio.h"
	.file 9 "/usr/include/stdlib.h"
	.file 10 "bdf_glyph.h"
	.file 11 "bdf_font.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x1239
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_8x8.c\0"
	.ascii "/home/jp/esp/Ka-Radio32/components/ucglib/tools/font/bdfconv\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0x3
	.ascii "__uint8_t\0"
	.byte	0x2
	.byte	0x2b
	.long	0xac
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.uleb128 0x3
	.ascii "size_t\0"
	.byte	0x3
	.byte	0xd8
	.long	0xe7
	.uleb128 0x2
	.byte	0xc
	.byte	0x4
	.ascii "long double\0"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0x4
	.long	0x13f
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "long unsigned int\0"
	.uleb128 0x3
	.ascii "_LOCK_T\0"
	.byte	0x4
	.byte	0xc
	.long	0x170
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii "long int\0"
	.uleb128 0x3
	.ascii "_off64_t\0"
	.byte	0x5
	.byte	0x5e
	.long	0xf7
	.uleb128 0x3
	.ascii "_fpos_t\0"
	.byte	0x5
	.byte	0x72
	.long	0x172
	.uleb128 0x3
	.ascii "_fpos64_t\0"
	.byte	0x5
	.byte	0x78
	.long	0x17e
	.uleb128 0x3
	.ascii "_ssize_t\0"
	.byte	0x5
	.byte	0x91
	.long	0xe0
	.uleb128 0x6
	.ascii "wint_t\0"
	.byte	0x3
	.word	0x165
	.long	0xe7
	.uleb128 0x7
	.byte	0x4
	.byte	0x5
	.byte	0xa6
	.long	0x1f1
	.uleb128 0x8
	.ascii "__wch\0"
	.byte	0x5
	.byte	0xa8
	.long	0x1be
	.uleb128 0x8
	.ascii "__wchb\0"
	.byte	0x5
	.byte	0xa9
	.long	0x1f1
	.byte	0
	.uleb128 0x9
	.long	0xac
	.long	0x201
	.uleb128 0xa
	.long	0x201
	.byte	0x3
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.ascii "sizetype\0"
	.uleb128 0xb
	.byte	0x8
	.byte	0x5
	.byte	0xa3
	.long	0x236
	.uleb128 0xc
	.ascii "__count\0"
	.byte	0x5
	.byte	0xa5
	.long	0xe0
	.byte	0
	.uleb128 0xc
	.ascii "__value\0"
	.byte	0x5
	.byte	0xaa
	.long	0x1cd
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.ascii "_mbstate_t\0"
	.byte	0x5
	.byte	0xab
	.long	0x20d
	.uleb128 0x3
	.ascii "_flock_t\0"
	.byte	0x5
	.byte	0xaf
	.long	0x161
	.uleb128 0x3
	.ascii "__ULong\0"
	.byte	0x6
	.byte	0x16
	.long	0x14c
	.uleb128 0xd
	.ascii "_Bigint\0"
	.byte	0x18
	.byte	0x6
	.byte	0x2f
	.long	0x2c7
	.uleb128 0xc
	.ascii "_next\0"
	.byte	0x6
	.byte	0x31
	.long	0x2c7
	.byte	0
	.uleb128 0xc
	.ascii "_k\0"
	.byte	0x6
	.byte	0x32
	.long	0xe0
	.byte	0x4
	.uleb128 0xc
	.ascii "_maxwds\0"
	.byte	0x6
	.byte	0x32
	.long	0xe0
	.byte	0x8
	.uleb128 0xc
	.ascii "_sign\0"
	.byte	0x6
	.byte	0x32
	.long	0xe0
	.byte	0xc
	.uleb128 0xc
	.ascii "_wds\0"
	.byte	0x6
	.byte	0x32
	.long	0xe0
	.byte	0x10
	.uleb128 0xc
	.ascii "_x\0"
	.byte	0x6
	.byte	0x33
	.long	0x2cd
	.byte	0x14
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x267
	.uleb128 0x9
	.long	0x258
	.long	0x2dd
	.uleb128 0xa
	.long	0x201
	.byte	0
	.byte	0
	.uleb128 0xd
	.ascii "__tm\0"
	.byte	0x24
	.byte	0x6
	.byte	0x37
	.long	0x38b
	.uleb128 0xc
	.ascii "__tm_sec\0"
	.byte	0x6
	.byte	0x39
	.long	0xe0
	.byte	0
	.uleb128 0xc
	.ascii "__tm_min\0"
	.byte	0x6
	.byte	0x3a
	.long	0xe0
	.byte	0x4
	.uleb128 0xc
	.ascii "__tm_hour\0"
	.byte	0x6
	.byte	0x3b
	.long	0xe0
	.byte	0x8
	.uleb128 0xc
	.ascii "__tm_mday\0"
	.byte	0x6
	.byte	0x3c
	.long	0xe0
	.byte	0xc
	.uleb128 0xc
	.ascii "__tm_mon\0"
	.byte	0x6
	.byte	0x3d
	.long	0xe0
	.byte	0x10
	.uleb128 0xc
	.ascii "__tm_year\0"
	.byte	0x6
	.byte	0x3e
	.long	0xe0
	.byte	0x14
	.uleb128 0xc
	.ascii "__tm_wday\0"
	.byte	0x6
	.byte	0x3f
	.long	0xe0
	.byte	0x18
	.uleb128 0xc
	.ascii "__tm_yday\0"
	.byte	0x6
	.byte	0x40
	.long	0xe0
	.byte	0x1c
	.uleb128 0xc
	.ascii "__tm_isdst\0"
	.byte	0x6
	.byte	0x41
	.long	0xe0
	.byte	0x20
	.byte	0
	.uleb128 0xf
	.secrel32	LASF0
	.word	0x108
	.byte	0x6
	.byte	0x4a
	.long	0x3e0
	.uleb128 0xc
	.ascii "_fnargs\0"
	.byte	0x6
	.byte	0x4b
	.long	0x3e0
	.byte	0
	.uleb128 0xc
	.ascii "_dso_handle\0"
	.byte	0x6
	.byte	0x4c
	.long	0x3e0
	.byte	0x80
	.uleb128 0x10
	.ascii "_fntypes\0"
	.byte	0x6
	.byte	0x4e
	.long	0x258
	.word	0x100
	.uleb128 0x10
	.ascii "_is_cxa\0"
	.byte	0x6
	.byte	0x51
	.long	0x258
	.word	0x104
	.byte	0
	.uleb128 0x9
	.long	0x170
	.long	0x3f0
	.uleb128 0xa
	.long	0x201
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.ascii "_atexit\0"
	.word	0x190
	.byte	0x6
	.byte	0x5d
	.long	0x436
	.uleb128 0xc
	.ascii "_next\0"
	.byte	0x6
	.byte	0x5e
	.long	0x436
	.byte	0
	.uleb128 0xc
	.ascii "_ind\0"
	.byte	0x6
	.byte	0x5f
	.long	0xe0
	.byte	0x4
	.uleb128 0xc
	.ascii "_fns\0"
	.byte	0x6
	.byte	0x61
	.long	0x43c
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF0
	.byte	0x6
	.byte	0x62
	.long	0x38b
	.byte	0x88
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x3f0
	.uleb128 0x9
	.long	0x44c
	.long	0x44c
	.uleb128 0xa
	.long	0x201
	.byte	0x1f
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x452
	.uleb128 0x13
	.uleb128 0xd
	.ascii "__sbuf\0"
	.byte	0x8
	.byte	0x6
	.byte	0x75
	.long	0x47f
	.uleb128 0xc
	.ascii "_base\0"
	.byte	0x6
	.byte	0x76
	.long	0x47f
	.byte	0
	.uleb128 0xc
	.ascii "_size\0"
	.byte	0x6
	.byte	0x77
	.long	0xe0
	.byte	0x4
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xac
	.uleb128 0x14
	.long	0x1ae
	.long	0x4a3
	.uleb128 0x15
	.long	0x4a3
	.uleb128 0x15
	.long	0x170
	.uleb128 0x15
	.long	0x64d
	.uleb128 0x15
	.long	0x122
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x4ae
	.uleb128 0x4
	.long	0x4a3
	.uleb128 0x16
	.ascii "_reent\0"
	.word	0x440
	.byte	0x6
	.word	0x239
	.long	0x64d
	.uleb128 0x17
	.ascii "_errno\0"
	.byte	0x6
	.word	0x23b
	.long	0xe0
	.byte	0
	.uleb128 0x17
	.ascii "_stdin\0"
	.byte	0x6
	.word	0x240
	.long	0x8d8
	.byte	0x4
	.uleb128 0x17
	.ascii "_stdout\0"
	.byte	0x6
	.word	0x240
	.long	0x8d8
	.byte	0x8
	.uleb128 0x17
	.ascii "_stderr\0"
	.byte	0x6
	.word	0x240
	.long	0x8d8
	.byte	0xc
	.uleb128 0x17
	.ascii "_inc\0"
	.byte	0x6
	.word	0x242
	.long	0xe0
	.byte	0x10
	.uleb128 0x17
	.ascii "_emergency\0"
	.byte	0x6
	.word	0x243
	.long	0xb7e
	.byte	0x14
	.uleb128 0x17
	.ascii "_unspecified_locale_info\0"
	.byte	0x6
	.word	0x246
	.long	0xe0
	.byte	0x30
	.uleb128 0x17
	.ascii "_locale\0"
	.byte	0x6
	.word	0x247
	.long	0xb9a
	.byte	0x34
	.uleb128 0x17
	.ascii "__sdidinit\0"
	.byte	0x6
	.word	0x249
	.long	0xe0
	.byte	0x38
	.uleb128 0x17
	.ascii "__cleanup\0"
	.byte	0x6
	.word	0x24b
	.long	0xbab
	.byte	0x3c
	.uleb128 0x17
	.ascii "_result\0"
	.byte	0x6
	.word	0x24e
	.long	0x2c7
	.byte	0x40
	.uleb128 0x17
	.ascii "_result_k\0"
	.byte	0x6
	.word	0x24f
	.long	0xe0
	.byte	0x44
	.uleb128 0x17
	.ascii "_p5s\0"
	.byte	0x6
	.word	0x250
	.long	0x2c7
	.byte	0x48
	.uleb128 0x17
	.ascii "_freelist\0"
	.byte	0x6
	.word	0x251
	.long	0xbb1
	.byte	0x4c
	.uleb128 0x17
	.ascii "_cvtlen\0"
	.byte	0x6
	.word	0x254
	.long	0xe0
	.byte	0x50
	.uleb128 0x17
	.ascii "_cvtbuf\0"
	.byte	0x6
	.word	0x255
	.long	0x64d
	.byte	0x54
	.uleb128 0x17
	.ascii "_new\0"
	.byte	0x6
	.word	0x278
	.long	0xb55
	.byte	0x58
	.uleb128 0x18
	.ascii "_atexit\0"
	.byte	0x6
	.word	0x27c
	.long	0x436
	.word	0x148
	.uleb128 0x18
	.ascii "_atexit0\0"
	.byte	0x6
	.word	0x27d
	.long	0x3f0
	.word	0x14c
	.uleb128 0x18
	.ascii "_sig_func\0"
	.byte	0x6
	.word	0x281
	.long	0xbc2
	.word	0x2dc
	.uleb128 0x18
	.ascii "__sglue\0"
	.byte	0x6
	.word	0x286
	.long	0x894
	.word	0x2e0
	.uleb128 0x18
	.ascii "__sf\0"
	.byte	0x6
	.word	0x288
	.long	0xbce
	.word	0x2f0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x13f
	.uleb128 0xe
	.byte	0x4
	.long	0x485
	.uleb128 0x14
	.long	0x1ae
	.long	0x677
	.uleb128 0x15
	.long	0x4a3
	.uleb128 0x15
	.long	0x170
	.uleb128 0x15
	.long	0x677
	.uleb128 0x15
	.long	0x122
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x147
	.uleb128 0xe
	.byte	0x4
	.long	0x659
	.uleb128 0x14
	.long	0x18e
	.long	0x6a1
	.uleb128 0x15
	.long	0x4a3
	.uleb128 0x15
	.long	0x170
	.uleb128 0x15
	.long	0x18e
	.uleb128 0x15
	.long	0xe0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x683
	.uleb128 0x14
	.long	0xe0
	.long	0x6bb
	.uleb128 0x15
	.long	0x4a3
	.uleb128 0x15
	.long	0x170
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x6a7
	.uleb128 0x9
	.long	0xac
	.long	0x6d1
	.uleb128 0xa
	.long	0x201
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.long	0xac
	.long	0x6e1
	.uleb128 0xa
	.long	0x201
	.byte	0
	.byte	0
	.uleb128 0xd
	.ascii "__sFILE64\0"
	.byte	0x70
	.byte	0x6
	.byte	0xef
	.long	0x861
	.uleb128 0xc
	.ascii "_p\0"
	.byte	0x6
	.byte	0xf0
	.long	0x47f
	.byte	0
	.uleb128 0xc
	.ascii "_r\0"
	.byte	0x6
	.byte	0xf1
	.long	0xe0
	.byte	0x4
	.uleb128 0xc
	.ascii "_w\0"
	.byte	0x6
	.byte	0xf2
	.long	0xe0
	.byte	0x8
	.uleb128 0xc
	.ascii "_flags\0"
	.byte	0x6
	.byte	0xf3
	.long	0xbd
	.byte	0xc
	.uleb128 0xc
	.ascii "_file\0"
	.byte	0x6
	.byte	0xf4
	.long	0xbd
	.byte	0xe
	.uleb128 0xc
	.ascii "_bf\0"
	.byte	0x6
	.byte	0xf5
	.long	0x453
	.byte	0x10
	.uleb128 0xc
	.ascii "_lbfsize\0"
	.byte	0x6
	.byte	0xf6
	.long	0xe0
	.byte	0x18
	.uleb128 0xc
	.ascii "_data\0"
	.byte	0x6
	.byte	0xf8
	.long	0x4a3
	.byte	0x1c
	.uleb128 0xc
	.ascii "_cookie\0"
	.byte	0x6
	.byte	0xfb
	.long	0x170
	.byte	0x20
	.uleb128 0xc
	.ascii "_read\0"
	.byte	0x6
	.byte	0xfd
	.long	0x653
	.byte	0x24
	.uleb128 0xc
	.ascii "_write\0"
	.byte	0x6
	.byte	0xff
	.long	0x67d
	.byte	0x28
	.uleb128 0x17
	.ascii "_seek\0"
	.byte	0x6
	.word	0x102
	.long	0x6a1
	.byte	0x2c
	.uleb128 0x17
	.ascii "_close\0"
	.byte	0x6
	.word	0x103
	.long	0x6bb
	.byte	0x30
	.uleb128 0x17
	.ascii "_ub\0"
	.byte	0x6
	.word	0x106
	.long	0x453
	.byte	0x34
	.uleb128 0x17
	.ascii "_up\0"
	.byte	0x6
	.word	0x107
	.long	0x47f
	.byte	0x3c
	.uleb128 0x17
	.ascii "_ur\0"
	.byte	0x6
	.word	0x108
	.long	0xe0
	.byte	0x40
	.uleb128 0x17
	.ascii "_ubuf\0"
	.byte	0x6
	.word	0x10b
	.long	0x6c1
	.byte	0x44
	.uleb128 0x17
	.ascii "_nbuf\0"
	.byte	0x6
	.word	0x10c
	.long	0x6d1
	.byte	0x47
	.uleb128 0x17
	.ascii "_lb\0"
	.byte	0x6
	.word	0x10f
	.long	0x453
	.byte	0x48
	.uleb128 0x17
	.ascii "_blksize\0"
	.byte	0x6
	.word	0x112
	.long	0xe0
	.byte	0x50
	.uleb128 0x17
	.ascii "_flags2\0"
	.byte	0x6
	.word	0x113
	.long	0xe0
	.byte	0x54
	.uleb128 0x17
	.ascii "_offset\0"
	.byte	0x6
	.word	0x115
	.long	0x17e
	.byte	0x58
	.uleb128 0x17
	.ascii "_seek64\0"
	.byte	0x6
	.word	0x116
	.long	0x87f
	.byte	0x60
	.uleb128 0x17
	.ascii "_lock\0"
	.byte	0x6
	.word	0x119
	.long	0x248
	.byte	0x64
	.uleb128 0x17
	.ascii "_mbstate\0"
	.byte	0x6
	.word	0x11b
	.long	0x236
	.byte	0x68
	.byte	0
	.uleb128 0x14
	.long	0x19d
	.long	0x87f
	.uleb128 0x15
	.long	0x4a3
	.uleb128 0x15
	.long	0x170
	.uleb128 0x15
	.long	0x19d
	.uleb128 0x15
	.long	0xe0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x861
	.uleb128 0x6
	.ascii "__FILE\0"
	.byte	0x6
	.word	0x11d
	.long	0x6e1
	.uleb128 0x19
	.ascii "_glue\0"
	.byte	0xc
	.byte	0x6
	.word	0x123
	.long	0x8d2
	.uleb128 0x17
	.ascii "_next\0"
	.byte	0x6
	.word	0x125
	.long	0x8d2
	.byte	0
	.uleb128 0x17
	.ascii "_niobs\0"
	.byte	0x6
	.word	0x126
	.long	0xe0
	.byte	0x4
	.uleb128 0x17
	.ascii "_iobs\0"
	.byte	0x6
	.word	0x127
	.long	0x8d8
	.byte	0x8
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x894
	.uleb128 0xe
	.byte	0x4
	.long	0x885
	.uleb128 0x19
	.ascii "_rand48\0"
	.byte	0xe
	.byte	0x6
	.word	0x13f
	.long	0x91c
	.uleb128 0x17
	.ascii "_seed\0"
	.byte	0x6
	.word	0x140
	.long	0x91c
	.byte	0
	.uleb128 0x17
	.ascii "_mult\0"
	.byte	0x6
	.word	0x141
	.long	0x91c
	.byte	0x6
	.uleb128 0x17
	.ascii "_add\0"
	.byte	0x6
	.word	0x142
	.long	0xca
	.byte	0xc
	.byte	0
	.uleb128 0x9
	.long	0xca
	.long	0x92c
	.uleb128 0xa
	.long	0x201
	.byte	0x2
	.byte	0
	.uleb128 0x1a
	.byte	0xd0
	.byte	0x6
	.word	0x259
	.long	0xad9
	.uleb128 0x17
	.ascii "_unused_rand\0"
	.byte	0x6
	.word	0x25b
	.long	0xe7
	.byte	0
	.uleb128 0x17
	.ascii "_strtok_last\0"
	.byte	0x6
	.word	0x25c
	.long	0x64d
	.byte	0x4
	.uleb128 0x17
	.ascii "_asctime_buf\0"
	.byte	0x6
	.word	0x25d
	.long	0xad9
	.byte	0x8
	.uleb128 0x17
	.ascii "_localtime_buf\0"
	.byte	0x6
	.word	0x25e
	.long	0x2dd
	.byte	0x24
	.uleb128 0x17
	.ascii "_gamma_signgam\0"
	.byte	0x6
	.word	0x25f
	.long	0xe0
	.byte	0x48
	.uleb128 0x17
	.ascii "_rand_next\0"
	.byte	0x6
	.word	0x260
	.long	0x108
	.byte	0x50
	.uleb128 0x17
	.ascii "_r48\0"
	.byte	0x6
	.word	0x261
	.long	0x8de
	.byte	0x58
	.uleb128 0x17
	.ascii "_mblen_state\0"
	.byte	0x6
	.word	0x262
	.long	0x236
	.byte	0x68
	.uleb128 0x17
	.ascii "_mbtowc_state\0"
	.byte	0x6
	.word	0x263
	.long	0x236
	.byte	0x70
	.uleb128 0x17
	.ascii "_wctomb_state\0"
	.byte	0x6
	.word	0x264
	.long	0x236
	.byte	0x78
	.uleb128 0x17
	.ascii "_l64a_buf\0"
	.byte	0x6
	.word	0x265
	.long	0xae9
	.byte	0x80
	.uleb128 0x17
	.ascii "_signal_buf\0"
	.byte	0x6
	.word	0x266
	.long	0xaf9
	.byte	0x88
	.uleb128 0x17
	.ascii "_getdate_err\0"
	.byte	0x6
	.word	0x267
	.long	0xe0
	.byte	0xa0
	.uleb128 0x17
	.ascii "_mbrlen_state\0"
	.byte	0x6
	.word	0x268
	.long	0x236
	.byte	0xa4
	.uleb128 0x17
	.ascii "_mbrtowc_state\0"
	.byte	0x6
	.word	0x269
	.long	0x236
	.byte	0xac
	.uleb128 0x17
	.ascii "_mbsrtowcs_state\0"
	.byte	0x6
	.word	0x26a
	.long	0x236
	.byte	0xb4
	.uleb128 0x17
	.ascii "_wcrtomb_state\0"
	.byte	0x6
	.word	0x26b
	.long	0x236
	.byte	0xbc
	.uleb128 0x17
	.ascii "_wcsrtombs_state\0"
	.byte	0x6
	.word	0x26c
	.long	0x236
	.byte	0xc4
	.uleb128 0x17
	.ascii "_h_errno\0"
	.byte	0x6
	.word	0x26d
	.long	0xe0
	.byte	0xcc
	.byte	0
	.uleb128 0x9
	.long	0x13f
	.long	0xae9
	.uleb128 0xa
	.long	0x201
	.byte	0x19
	.byte	0
	.uleb128 0x9
	.long	0x13f
	.long	0xaf9
	.uleb128 0xa
	.long	0x201
	.byte	0x7
	.byte	0
	.uleb128 0x9
	.long	0x13f
	.long	0xb09
	.uleb128 0xa
	.long	0x201
	.byte	0x17
	.byte	0
	.uleb128 0x1a
	.byte	0xf0
	.byte	0x6
	.word	0x272
	.long	0xb35
	.uleb128 0x17
	.ascii "_nextf\0"
	.byte	0x6
	.word	0x275
	.long	0xb35
	.byte	0
	.uleb128 0x17
	.ascii "_nmalloc\0"
	.byte	0x6
	.word	0x276
	.long	0xb45
	.byte	0x78
	.byte	0
	.uleb128 0x9
	.long	0x47f
	.long	0xb45
	.uleb128 0xa
	.long	0x201
	.byte	0x1d
	.byte	0
	.uleb128 0x9
	.long	0xe7
	.long	0xb55
	.uleb128 0xa
	.long	0x201
	.byte	0x1d
	.byte	0
	.uleb128 0x1b
	.byte	0xf0
	.byte	0x6
	.word	0x257
	.long	0xb7e
	.uleb128 0x1c
	.ascii "_reent\0"
	.byte	0x6
	.word	0x26e
	.long	0x92c
	.uleb128 0x1c
	.ascii "_unused\0"
	.byte	0x6
	.word	0x277
	.long	0xb09
	.byte	0
	.uleb128 0x9
	.long	0x13f
	.long	0xb8e
	.uleb128 0xa
	.long	0x201
	.byte	0x18
	.byte	0
	.uleb128 0x1d
	.ascii "__locale_t\0"
	.uleb128 0xe
	.byte	0x4
	.long	0xb8e
	.uleb128 0x1e
	.long	0xbab
	.uleb128 0x15
	.long	0x4a3
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xba0
	.uleb128 0xe
	.byte	0x4
	.long	0x2c7
	.uleb128 0x1e
	.long	0xbc2
	.uleb128 0x15
	.long	0xe0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xbc8
	.uleb128 0xe
	.byte	0x4
	.long	0xbb7
	.uleb128 0x9
	.long	0x885
	.long	0xbde
	.uleb128 0xa
	.long	0x201
	.byte	0x2
	.byte	0
	.uleb128 0x1f
	.ascii "_impure_ptr\0"
	.byte	0x6
	.word	0x307
	.long	0x4a3
	.uleb128 0x1f
	.ascii "_global_impure_ptr\0"
	.byte	0x6
	.word	0x308
	.long	0x4a9
	.uleb128 0x3
	.ascii "uint8_t\0"
	.byte	0x7
	.byte	0x18
	.long	0x9b
	.uleb128 0x3
	.ascii "FILE\0"
	.byte	0x8
	.byte	0x42
	.long	0x885
	.uleb128 0x20
	.ascii "suboptarg\0"
	.byte	0x9
	.byte	0x63
	.long	0x64d
	.uleb128 0x3
	.ascii "bf_t\0"
	.byte	0xa
	.byte	0x9
	.long	0xc45
	.uleb128 0x11
	.ascii "_bdf_font_struct\0"
	.word	0x4a4
	.byte	0xb
	.byte	0x10
	.long	0xf19
	.uleb128 0xc
	.ascii "is_verbose\0"
	.byte	0xb
	.byte	0x12
	.long	0xe0
	.byte	0
	.uleb128 0xc
	.ascii "glyph_list\0"
	.byte	0xb
	.byte	0x14
	.long	0x10fe
	.byte	0x4
	.uleb128 0xc
	.ascii "glyph_cnt\0"
	.byte	0xb
	.byte	0x15
	.long	0xe0
	.byte	0x8
	.uleb128 0xc
	.ascii "glyph_max\0"
	.byte	0xb
	.byte	0x16
	.long	0xe0
	.byte	0xc
	.uleb128 0xc
	.ascii "line_buf\0"
	.byte	0xb
	.byte	0x19
	.long	0x110a
	.byte	0x10
	.uleb128 0x10
	.ascii "line_pos\0"
	.byte	0xb
	.byte	0x1a
	.long	0xe0
	.word	0x410
	.uleb128 0x10
	.ascii "is_bitmap_parsing\0"
	.byte	0xb
	.byte	0x1b
	.long	0xe0
	.word	0x414
	.uleb128 0x21
	.secrel32	LASF1
	.byte	0xb
	.byte	0x1d
	.long	0x172
	.word	0x418
	.uleb128 0x21
	.secrel32	LASF2
	.byte	0xb
	.byte	0x1f
	.long	0x172
	.word	0x41c
	.uleb128 0x21
	.secrel32	LASF3
	.byte	0xb
	.byte	0x20
	.long	0x172
	.word	0x420
	.uleb128 0x10
	.ascii "bbx_w\0"
	.byte	0xb
	.byte	0x22
	.long	0x172
	.word	0x424
	.uleb128 0x10
	.ascii "bbx_h\0"
	.byte	0xb
	.byte	0x23
	.long	0x172
	.word	0x428
	.uleb128 0x10
	.ascii "bbx_x\0"
	.byte	0xb
	.byte	0x24
	.long	0x172
	.word	0x42c
	.uleb128 0x10
	.ascii "bbx_y\0"
	.byte	0xb
	.byte	0x25
	.long	0x172
	.word	0x430
	.uleb128 0x10
	.ascii "bitmap_x\0"
	.byte	0xb
	.byte	0x27
	.long	0xe0
	.word	0x434
	.uleb128 0x10
	.ascii "bitmap_y\0"
	.byte	0xb
	.byte	0x28
	.long	0xe0
	.word	0x438
	.uleb128 0x10
	.ascii "glyph_pos\0"
	.byte	0xb
	.byte	0x29
	.long	0xe0
	.word	0x43c
	.uleb128 0x10
	.ascii "fp\0"
	.byte	0xb
	.byte	0x2a
	.long	0x111b
	.word	0x440
	.uleb128 0x10
	.ascii "str_font\0"
	.byte	0xb
	.byte	0x2c
	.long	0x64d
	.word	0x444
	.uleb128 0x10
	.ascii "str_copyright\0"
	.byte	0xb
	.byte	0x2d
	.long	0x64d
	.word	0x448
	.uleb128 0x10
	.ascii "selected_glyphs\0"
	.byte	0xb
	.byte	0x2f
	.long	0x172
	.word	0x44c
	.uleb128 0x10
	.ascii "bbx_mode\0"
	.byte	0xb
	.byte	0x31
	.long	0xe0
	.word	0x450
	.uleb128 0x10
	.ascii "max\0"
	.byte	0xb
	.byte	0x33
	.long	0xf56
	.word	0x454
	.uleb128 0x10
	.ascii "enc_w\0"
	.byte	0xb
	.byte	0x36
	.long	0x172
	.word	0x464
	.uleb128 0x10
	.ascii "enc_h\0"
	.byte	0xb
	.byte	0x37
	.long	0x172
	.word	0x468
	.uleb128 0x10
	.ascii "enc_x\0"
	.byte	0xb
	.byte	0x38
	.long	0x172
	.word	0x46c
	.uleb128 0x10
	.ascii "enc_y\0"
	.byte	0xb
	.byte	0x39
	.long	0x172
	.word	0x470
	.uleb128 0x10
	.ascii "dx_min\0"
	.byte	0xb
	.byte	0x3c
	.long	0x172
	.word	0x474
	.uleb128 0x10
	.ascii "dx_max\0"
	.byte	0xb
	.byte	0x3d
	.long	0x172
	.word	0x478
	.uleb128 0x10
	.ascii "x_min\0"
	.byte	0xb
	.byte	0x40
	.long	0x172
	.word	0x47c
	.uleb128 0x10
	.ascii "x_max\0"
	.byte	0xb
	.byte	0x41
	.long	0x172
	.word	0x480
	.uleb128 0x10
	.ascii "bbx_x_max_bit_size\0"
	.byte	0xb
	.byte	0x44
	.long	0xe0
	.word	0x484
	.uleb128 0x10
	.ascii "bbx_y_max_bit_size\0"
	.byte	0xb
	.byte	0x45
	.long	0xe0
	.word	0x488
	.uleb128 0x10
	.ascii "bbx_w_max_bit_size\0"
	.byte	0xb
	.byte	0x46
	.long	0xe0
	.word	0x48c
	.uleb128 0x10
	.ascii "bbx_h_max_bit_size\0"
	.byte	0xb
	.byte	0x47
	.long	0xe0
	.word	0x490
	.uleb128 0x10
	.ascii "dx_max_bit_size\0"
	.byte	0xb
	.byte	0x48
	.long	0xe0
	.word	0x494
	.uleb128 0x21
	.secrel32	LASF4
	.byte	0xb
	.byte	0x4b
	.long	0x10ec
	.word	0x498
	.uleb128 0x21
	.secrel32	LASF5
	.byte	0xb
	.byte	0x4c
	.long	0xe0
	.word	0x49c
	.uleb128 0x21
	.secrel32	LASF6
	.byte	0xb
	.byte	0x4d
	.long	0xe0
	.word	0x4a0
	.byte	0
	.uleb128 0xd
	.ascii "_bbx_struct\0"
	.byte	0x10
	.byte	0xa
	.byte	0xc
	.long	0xf56
	.uleb128 0xc
	.ascii "w\0"
	.byte	0xa
	.byte	0xe
	.long	0x172
	.byte	0
	.uleb128 0xc
	.ascii "h\0"
	.byte	0xa
	.byte	0xf
	.long	0x172
	.byte	0x4
	.uleb128 0xc
	.ascii "x\0"
	.byte	0xa
	.byte	0x10
	.long	0x172
	.byte	0x8
	.uleb128 0xc
	.ascii "y\0"
	.byte	0xa
	.byte	0x11
	.long	0x172
	.byte	0xc
	.byte	0
	.uleb128 0x3
	.ascii "bbx_t\0"
	.byte	0xa
	.byte	0x13
	.long	0xf19
	.uleb128 0xd
	.ascii "_bdf_glyph_struct\0"
	.byte	0x60
	.byte	0xa
	.byte	0x16
	.long	0x10e6
	.uleb128 0xc
	.ascii "bf\0"
	.byte	0xa
	.byte	0x18
	.long	0x10e6
	.byte	0
	.uleb128 0x12
	.secrel32	LASF1
	.byte	0xa
	.byte	0x1a
	.long	0x172
	.byte	0x4
	.uleb128 0xc
	.ascii "map_to\0"
	.byte	0xa
	.byte	0x1b
	.long	0x172
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF2
	.byte	0xa
	.byte	0x1d
	.long	0x172
	.byte	0xc
	.uleb128 0x12
	.secrel32	LASF3
	.byte	0xa
	.byte	0x1e
	.long	0x172
	.byte	0x10
	.uleb128 0xc
	.ascii "bbx\0"
	.byte	0xa
	.byte	0x20
	.long	0xf56
	.byte	0x14
	.uleb128 0xc
	.ascii "shift_x\0"
	.byte	0xa
	.byte	0x21
	.long	0x172
	.byte	0x24
	.uleb128 0xc
	.ascii "bitmap_data\0"
	.byte	0xa
	.byte	0x23
	.long	0x10ec
	.byte	0x28
	.uleb128 0xc
	.ascii "bitmap_width\0"
	.byte	0xa
	.byte	0x24
	.long	0xe0
	.byte	0x2c
	.uleb128 0xc
	.ascii "bitmap_height\0"
	.byte	0xa
	.byte	0x25
	.long	0xe0
	.byte	0x30
	.uleb128 0x12
	.secrel32	LASF4
	.byte	0xa
	.byte	0x2a
	.long	0x10ec
	.byte	0x34
	.uleb128 0x12
	.secrel32	LASF5
	.byte	0xa
	.byte	0x2b
	.long	0xe0
	.byte	0x38
	.uleb128 0x12
	.secrel32	LASF6
	.byte	0xa
	.byte	0x2c
	.long	0xe0
	.byte	0x3c
	.uleb128 0xc
	.ascii "target_bit_pos\0"
	.byte	0xa
	.byte	0x2d
	.long	0xe0
	.byte	0x40
	.uleb128 0xc
	.ascii "rle_bits_per_0\0"
	.byte	0xa
	.byte	0x31
	.long	0xe7
	.byte	0x44
	.uleb128 0xc
	.ascii "rle_bits_per_1\0"
	.byte	0xa
	.byte	0x32
	.long	0xe7
	.byte	0x48
	.uleb128 0xc
	.ascii "rle_is_first\0"
	.byte	0xa
	.byte	0x34
	.long	0xe0
	.byte	0x4c
	.uleb128 0xc
	.ascii "rle_bitcnt\0"
	.byte	0xa
	.byte	0x35
	.long	0xe7
	.byte	0x50
	.uleb128 0xc
	.ascii "rle_last_0\0"
	.byte	0xa
	.byte	0x36
	.long	0xe7
	.byte	0x54
	.uleb128 0xc
	.ascii "rle_last_1\0"
	.byte	0xa
	.byte	0x37
	.long	0xe7
	.byte	0x58
	.uleb128 0xc
	.ascii "width_deviation\0"
	.byte	0xa
	.byte	0x39
	.long	0x172
	.byte	0x5c
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc39
	.uleb128 0xe
	.byte	0x4
	.long	0xc0d
	.uleb128 0x3
	.ascii "bg_t\0"
	.byte	0xa
	.byte	0x3c
	.long	0xf63
	.uleb128 0xe
	.byte	0x4
	.long	0x1104
	.uleb128 0xe
	.byte	0x4
	.long	0x10f2
	.uleb128 0x9
	.long	0x13f
	.long	0x111b
	.uleb128 0x22
	.long	0x201
	.word	0x3ff
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc1c
	.uleb128 0x23
	.ascii "bf_Generate8x8Font\0"
	.byte	0x1
	.byte	0x49
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x11d2
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.byte	0x49
	.long	0x10e6
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "i\0"
	.byte	0x1
	.byte	0x4b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "j\0"
	.byte	0x1
	.byte	0x4b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "k\0"
	.byte	0x1
	.byte	0x4b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x25
	.ascii "bg\0"
	.byte	0x1
	.byte	0x4c
	.long	0x1104
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x25
	.ascii "first\0"
	.byte	0x1
	.byte	0x4d
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x25
	.ascii "last\0"
	.byte	0x1
	.byte	0x4d
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x25
	.ascii "local_bbx\0"
	.byte	0x1
	.byte	0x4e
	.long	0xf56
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x25
	.ascii "is_glyph_written\0"
	.byte	0x1
	.byte	0x4f
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x26
	.ascii "bg_8x8_convert\0"
	.byte	0x1
	.byte	0x14
	.long	0xe0
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0x1236
	.uleb128 0x24
	.ascii "bg\0"
	.byte	0x1
	.byte	0x14
	.long	0x1104
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "bbx\0"
	.byte	0x1
	.byte	0x14
	.long	0x1236
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x25
	.ascii "x\0"
	.byte	0x1
	.byte	0x16
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "y\0"
	.byte	0x1
	.byte	0x17
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "d\0"
	.byte	0x1
	.byte	0x18
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xf56
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
	.uleb128 0x24
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
	.def	_bg_ClearTargetData;	.scl	2;	.type	32;	.endef
	.def	_bg_GetBBXPixel;	.scl	2;	.type	32;	.endef
	.def	_bg_AddTargetData;	.scl	2;	.type	32;	.endef
	.def	_bf_copy_bbx_and_update_shift;	.scl	2;	.type	32;	.endef
	.def	_bf_Log;	.scl	2;	.type	32;	.endef
	.def	_bf_AddTargetData;	.scl	2;	.type	32;	.endef
