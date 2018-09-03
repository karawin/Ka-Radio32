	.file	"bdf_map.c"
	.text
Ltext0:
.lcomm _range_from,4,4
.lcomm _range_to,4,4
.lcomm _is_exclude,4,4
.lcomm _map_to,4,4
	.def	_skip_space;	.scl	3;	.type	32;	.endef
_skip_space:
LFB12:
	.file 1 "bdf_map.c"
	.loc 1 33 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
L5:
	.loc 1 36 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	L6
	.loc 1 38 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$32, %al
	jg	L7
	.loc 1 40 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 36 0
	jmp	L5
L6:
	.loc 1 37 0
	nop
	jmp	L3
L7:
	.loc 1 39 0
	nop
L3:
	.loc 1 42 0
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.def	_get_dec;	.scl	3;	.type	32;	.endef
_get_dec:
LFB13:
	.loc 1 45 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 46 0
	movl	$0, -4(%ebp)
L10:
	.loc 1 49 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$47, %al
	jle	L9
	.loc 1 49 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$57, %al
	jg	L9
	.loc 1 51 0 is_stmt 1
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -4(%ebp)
	.loc 1 52 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$48, %eax
	addl	%eax, -4(%ebp)
	.loc 1 53 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 49 0
	jmp	L10
L9:
	.loc 1 60 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 61 0
	movl	-4(%ebp), %eax
	.loc 1 62 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.def	_get_hex;	.scl	3;	.type	32;	.endef
_get_hex:
LFB14:
	.loc 1 65 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 66 0
	movl	$0, -4(%ebp)
L17:
	.loc 1 69 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$47, %al
	jle	L13
	.loc 1 69 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$57, %al
	jg	L13
	.loc 1 71 0 is_stmt 1
	sall	$4, -4(%ebp)
	.loc 1 72 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$48, %eax
	addl	%eax, -4(%ebp)
	.loc 1 73 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	jmp	L14
L13:
	.loc 1 75 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$96, %al
	jle	L15
	.loc 1 75 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$102, %al
	jg	L15
	.loc 1 77 0 is_stmt 1
	sall	$4, -4(%ebp)
	.loc 1 78 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$87, %eax
	addl	%eax, -4(%ebp)
	.loc 1 79 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	jmp	L14
L15:
	.loc 1 81 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$64, %al
	jle	L16
	.loc 1 81 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$70, %al
	jg	L16
	.loc 1 83 0 is_stmt 1
	sall	$4, -4(%ebp)
	.loc 1 84 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$55, %eax
	addl	%eax, -4(%ebp)
	.loc 1 85 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
L14:
	.loc 1 69 0
	jmp	L17
L16:
	.loc 1 92 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 93 0
	movl	-4(%ebp), %eax
	.loc 1 94 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.def	_get_num;	.scl	3;	.type	32;	.endef
_get_num:
LFB15:
	.loc 1 97 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	.loc 1 98 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$36, %al
	je	L20
	.loc 1 99 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_dec
	jmp	L21
L20:
	.loc 1 100 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 101 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 102 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_hex
L21:
	.loc 1 103 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.def	_get_mul;	.scl	3;	.type	32;	.endef
_get_mul:
LFB16:
	.loc 1 106 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 108 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_num
	movl	%eax, -4(%ebp)
	.loc 1 109 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$42, %al
	jne	L23
	.loc 1 111 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 112 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 113 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_num
	movl	%eax, %edx
	movl	-4(%ebp), %eax
	imull	%edx, %eax
	movl	%eax, -4(%ebp)
L23:
	.loc 1 115 0
	movl	-4(%ebp), %eax
	.loc 1 116 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.def	_get_add;	.scl	3;	.type	32;	.endef
_get_add:
LFB17:
	.loc 1 119 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	.loc 1 121 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_mul
	movl	%eax, -4(%ebp)
	.loc 1 122 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$43, %al
	jne	L26
	.loc 1 124 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 125 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 126 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_mul
	addl	%eax, -4(%ebp)
L26:
	.loc 1 128 0
	movl	-4(%ebp), %eax
	.loc 1 129 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.def	_get_range;	.scl	3;	.type	32;	.endef
_get_range:
LFB18:
	.loc 1 132 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	.loc 1 133 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_add
	movl	%eax, _range_from
	.loc 1 134 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$45, %al
	je	L29
	.loc 1 136 0
	movl	_range_from, %eax
	movl	%eax, _range_to
	.loc 1 144 0
	jmp	L31
L29:
	.loc 1 140 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 141 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 142 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_add
	movl	%eax, _range_to
L31:
	.loc 1 144 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.def	_map_cmd;	.scl	3;	.type	32;	.endef
_map_cmd:
LFB19:
	.loc 1 147 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	.loc 1 148 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$42, %al
	jne	L33
	.loc 1 150 0
	movl	$32, _range_from
	.loc 1 151 0
	movl	$255, _range_to
	.loc 1 152 0
	movl	$32, _map_to
	.loc 1 153 0
	movl	$0, _is_exclude
	.loc 1 155 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 156 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 180 0
	jmp	L36
L33:
	.loc 1 158 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$126, %al
	jne	L35
	.loc 1 160 0
	movl	$1, _is_exclude
	.loc 1 161 0
	movl	$0, _map_to
	.loc 1 163 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 164 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 165 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_range
	.loc 1 180 0
	jmp	L36
L35:
	.loc 1 170 0
	movl	$0, _is_exclude
	.loc 1 171 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_range
	.loc 1 172 0
	movl	_range_from, %eax
	movl	%eax, _map_to
	.loc 1 173 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$62, %al
	jne	L36
	.loc 1 175 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 176 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 177 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_get_add
	movl	%eax, _map_to
L36:
	.loc 1 180 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "Map: exclude=%d from=%ld to=%ld map=%ld\0"
	.text
	.globl	_bf_map_cmd
	.def	_bf_map_cmd;	.scl	2;	.type	32;	.endef
_bf_map_cmd:
LFB20:
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
	.loc 1 186 0
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_map_cmd
	.loc 1 188 0
	movl	_map_to, %ebx
	movl	_range_to, %ecx
	movl	_range_from, %edx
	movl	_is_exclude, %eax
	movl	%ebx, 20(%esp)
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 190 0
	movl	$0, -12(%ebp)
	jmp	L38
L41:
	.loc 1 192 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 193 0
	movl	-16(%ebp), %eax
	movl	4(%eax), %edx
	movl	_range_from, %eax
	cmpl	%eax, %edx
	jl	L39
	.loc 1 193 0 is_stmt 0 discriminator 1
	movl	-16(%ebp), %eax
	movl	4(%eax), %edx
	movl	_range_to, %eax
	cmpl	%eax, %edx
	jg	L39
	.loc 1 195 0 is_stmt 1
	movl	_is_exclude, %eax
	testl	%eax, %eax
	je	L40
	.loc 1 197 0
	movl	-16(%ebp), %eax
	movl	$-1, 8(%eax)
	jmp	L39
L40:
	.loc 1 201 0
	movl	-16(%ebp), %eax
	movl	4(%eax), %edx
	movl	_range_from, %eax
	subl	%eax, %edx
	movl	_map_to, %eax
	addl	%eax, %edx
	movl	-16(%ebp), %eax
	movl	%edx, 8(%eax)
L39:
	.loc 1 190 0 discriminator 2
	addl	$1, -12(%ebp)
L38:
	.loc 1 190 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L41
	.loc 1 206 0 is_stmt 1
	nop
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.globl	_bf_map_list
	.def	_bf_map_list;	.scl	2;	.type	32;	.endef
_bf_map_list:
LFB21:
	.loc 1 209 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 214 0
	movl	$0, -12(%ebp)
	jmp	L43
L44:
	.loc 1 216 0 discriminator 3
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 217 0 discriminator 3
	movl	-16(%ebp), %eax
	movl	$-1, 8(%eax)
	.loc 1 214 0 discriminator 3
	addl	$1, -12(%ebp)
L43:
	.loc 1 214 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L44
	.loc 1 221 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
L47:
	.loc 1 224 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_map_cmd
	.loc 1 225 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movzbl	(%eax), %eax
	cmpb	$44, %al
	jne	L49
	.loc 1 227 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 228 0
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	_skip_space
	.loc 1 224 0
	jmp	L47
L49:
	.loc 1 226 0
	nop
	.loc 1 230 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.section .rdata,"dr"
LC1:
	.ascii "Map: map_cmd_list='%s'\0"
	.text
	.globl	_bf_Map
	.def	_bf_Map;	.scl	2;	.type	32;	.endef
_bf_Map:
LFB22:
	.loc 1 233 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 234 0
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 235 0
	leal	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_map_list
	.loc 1 238 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
Letext0:
	.file 2 "/usr/include/machine/_default_types.h"
	.file 3 "/usr/lib/gcc/i686-pc-msys/6.4.0/include/stddef.h"
	.file 4 "/usr/include/sys/lock.h"
	.file 5 "/usr/include/sys/_types.h"
	.file 6 "/usr/include/sys/reent.h"
	.file 7 "/usr/include/sys/_stdint.h"
	.file 8 "/usr/include/stdio.h"
	.file 9 "bdf_glyph.h"
	.file 10 "bdf_font.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x13be
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_map.c\0"
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
	.uleb128 0x3
	.ascii "bf_t\0"
	.byte	0x9
	.byte	0x9
	.long	0xc34
	.uleb128 0x11
	.ascii "_bdf_font_struct\0"
	.word	0x4a4
	.byte	0xa
	.byte	0x10
	.long	0xf08
	.uleb128 0xc
	.ascii "is_verbose\0"
	.byte	0xa
	.byte	0x12
	.long	0xe0
	.byte	0
	.uleb128 0xc
	.ascii "glyph_list\0"
	.byte	0xa
	.byte	0x14
	.long	0x10ed
	.byte	0x4
	.uleb128 0xc
	.ascii "glyph_cnt\0"
	.byte	0xa
	.byte	0x15
	.long	0xe0
	.byte	0x8
	.uleb128 0xc
	.ascii "glyph_max\0"
	.byte	0xa
	.byte	0x16
	.long	0xe0
	.byte	0xc
	.uleb128 0xc
	.ascii "line_buf\0"
	.byte	0xa
	.byte	0x19
	.long	0x10f9
	.byte	0x10
	.uleb128 0x10
	.ascii "line_pos\0"
	.byte	0xa
	.byte	0x1a
	.long	0xe0
	.word	0x410
	.uleb128 0x10
	.ascii "is_bitmap_parsing\0"
	.byte	0xa
	.byte	0x1b
	.long	0xe0
	.word	0x414
	.uleb128 0x20
	.secrel32	LASF1
	.byte	0xa
	.byte	0x1d
	.long	0x172
	.word	0x418
	.uleb128 0x20
	.secrel32	LASF2
	.byte	0xa
	.byte	0x1f
	.long	0x172
	.word	0x41c
	.uleb128 0x20
	.secrel32	LASF3
	.byte	0xa
	.byte	0x20
	.long	0x172
	.word	0x420
	.uleb128 0x10
	.ascii "bbx_w\0"
	.byte	0xa
	.byte	0x22
	.long	0x172
	.word	0x424
	.uleb128 0x10
	.ascii "bbx_h\0"
	.byte	0xa
	.byte	0x23
	.long	0x172
	.word	0x428
	.uleb128 0x10
	.ascii "bbx_x\0"
	.byte	0xa
	.byte	0x24
	.long	0x172
	.word	0x42c
	.uleb128 0x10
	.ascii "bbx_y\0"
	.byte	0xa
	.byte	0x25
	.long	0x172
	.word	0x430
	.uleb128 0x10
	.ascii "bitmap_x\0"
	.byte	0xa
	.byte	0x27
	.long	0xe0
	.word	0x434
	.uleb128 0x10
	.ascii "bitmap_y\0"
	.byte	0xa
	.byte	0x28
	.long	0xe0
	.word	0x438
	.uleb128 0x10
	.ascii "glyph_pos\0"
	.byte	0xa
	.byte	0x29
	.long	0xe0
	.word	0x43c
	.uleb128 0x10
	.ascii "fp\0"
	.byte	0xa
	.byte	0x2a
	.long	0x110a
	.word	0x440
	.uleb128 0x10
	.ascii "str_font\0"
	.byte	0xa
	.byte	0x2c
	.long	0x64d
	.word	0x444
	.uleb128 0x10
	.ascii "str_copyright\0"
	.byte	0xa
	.byte	0x2d
	.long	0x64d
	.word	0x448
	.uleb128 0x10
	.ascii "selected_glyphs\0"
	.byte	0xa
	.byte	0x2f
	.long	0x172
	.word	0x44c
	.uleb128 0x10
	.ascii "bbx_mode\0"
	.byte	0xa
	.byte	0x31
	.long	0xe0
	.word	0x450
	.uleb128 0x10
	.ascii "max\0"
	.byte	0xa
	.byte	0x33
	.long	0xf45
	.word	0x454
	.uleb128 0x10
	.ascii "enc_w\0"
	.byte	0xa
	.byte	0x36
	.long	0x172
	.word	0x464
	.uleb128 0x10
	.ascii "enc_h\0"
	.byte	0xa
	.byte	0x37
	.long	0x172
	.word	0x468
	.uleb128 0x10
	.ascii "enc_x\0"
	.byte	0xa
	.byte	0x38
	.long	0x172
	.word	0x46c
	.uleb128 0x10
	.ascii "enc_y\0"
	.byte	0xa
	.byte	0x39
	.long	0x172
	.word	0x470
	.uleb128 0x10
	.ascii "dx_min\0"
	.byte	0xa
	.byte	0x3c
	.long	0x172
	.word	0x474
	.uleb128 0x10
	.ascii "dx_max\0"
	.byte	0xa
	.byte	0x3d
	.long	0x172
	.word	0x478
	.uleb128 0x10
	.ascii "x_min\0"
	.byte	0xa
	.byte	0x40
	.long	0x172
	.word	0x47c
	.uleb128 0x10
	.ascii "x_max\0"
	.byte	0xa
	.byte	0x41
	.long	0x172
	.word	0x480
	.uleb128 0x10
	.ascii "bbx_x_max_bit_size\0"
	.byte	0xa
	.byte	0x44
	.long	0xe0
	.word	0x484
	.uleb128 0x10
	.ascii "bbx_y_max_bit_size\0"
	.byte	0xa
	.byte	0x45
	.long	0xe0
	.word	0x488
	.uleb128 0x10
	.ascii "bbx_w_max_bit_size\0"
	.byte	0xa
	.byte	0x46
	.long	0xe0
	.word	0x48c
	.uleb128 0x10
	.ascii "bbx_h_max_bit_size\0"
	.byte	0xa
	.byte	0x47
	.long	0xe0
	.word	0x490
	.uleb128 0x10
	.ascii "dx_max_bit_size\0"
	.byte	0xa
	.byte	0x48
	.long	0xe0
	.word	0x494
	.uleb128 0x20
	.secrel32	LASF4
	.byte	0xa
	.byte	0x4b
	.long	0x10db
	.word	0x498
	.uleb128 0x20
	.secrel32	LASF5
	.byte	0xa
	.byte	0x4c
	.long	0xe0
	.word	0x49c
	.uleb128 0x20
	.secrel32	LASF6
	.byte	0xa
	.byte	0x4d
	.long	0xe0
	.word	0x4a0
	.byte	0
	.uleb128 0xd
	.ascii "_bbx_struct\0"
	.byte	0x10
	.byte	0x9
	.byte	0xc
	.long	0xf45
	.uleb128 0xc
	.ascii "w\0"
	.byte	0x9
	.byte	0xe
	.long	0x172
	.byte	0
	.uleb128 0xc
	.ascii "h\0"
	.byte	0x9
	.byte	0xf
	.long	0x172
	.byte	0x4
	.uleb128 0xc
	.ascii "x\0"
	.byte	0x9
	.byte	0x10
	.long	0x172
	.byte	0x8
	.uleb128 0xc
	.ascii "y\0"
	.byte	0x9
	.byte	0x11
	.long	0x172
	.byte	0xc
	.byte	0
	.uleb128 0x3
	.ascii "bbx_t\0"
	.byte	0x9
	.byte	0x13
	.long	0xf08
	.uleb128 0xd
	.ascii "_bdf_glyph_struct\0"
	.byte	0x60
	.byte	0x9
	.byte	0x16
	.long	0x10d5
	.uleb128 0xc
	.ascii "bf\0"
	.byte	0x9
	.byte	0x18
	.long	0x10d5
	.byte	0
	.uleb128 0x12
	.secrel32	LASF1
	.byte	0x9
	.byte	0x1a
	.long	0x172
	.byte	0x4
	.uleb128 0xc
	.ascii "map_to\0"
	.byte	0x9
	.byte	0x1b
	.long	0x172
	.byte	0x8
	.uleb128 0x12
	.secrel32	LASF2
	.byte	0x9
	.byte	0x1d
	.long	0x172
	.byte	0xc
	.uleb128 0x12
	.secrel32	LASF3
	.byte	0x9
	.byte	0x1e
	.long	0x172
	.byte	0x10
	.uleb128 0xc
	.ascii "bbx\0"
	.byte	0x9
	.byte	0x20
	.long	0xf45
	.byte	0x14
	.uleb128 0xc
	.ascii "shift_x\0"
	.byte	0x9
	.byte	0x21
	.long	0x172
	.byte	0x24
	.uleb128 0xc
	.ascii "bitmap_data\0"
	.byte	0x9
	.byte	0x23
	.long	0x10db
	.byte	0x28
	.uleb128 0xc
	.ascii "bitmap_width\0"
	.byte	0x9
	.byte	0x24
	.long	0xe0
	.byte	0x2c
	.uleb128 0xc
	.ascii "bitmap_height\0"
	.byte	0x9
	.byte	0x25
	.long	0xe0
	.byte	0x30
	.uleb128 0x12
	.secrel32	LASF4
	.byte	0x9
	.byte	0x2a
	.long	0x10db
	.byte	0x34
	.uleb128 0x12
	.secrel32	LASF5
	.byte	0x9
	.byte	0x2b
	.long	0xe0
	.byte	0x38
	.uleb128 0x12
	.secrel32	LASF6
	.byte	0x9
	.byte	0x2c
	.long	0xe0
	.byte	0x3c
	.uleb128 0xc
	.ascii "target_bit_pos\0"
	.byte	0x9
	.byte	0x2d
	.long	0xe0
	.byte	0x40
	.uleb128 0xc
	.ascii "rle_bits_per_0\0"
	.byte	0x9
	.byte	0x31
	.long	0xe7
	.byte	0x44
	.uleb128 0xc
	.ascii "rle_bits_per_1\0"
	.byte	0x9
	.byte	0x32
	.long	0xe7
	.byte	0x48
	.uleb128 0xc
	.ascii "rle_is_first\0"
	.byte	0x9
	.byte	0x34
	.long	0xe0
	.byte	0x4c
	.uleb128 0xc
	.ascii "rle_bitcnt\0"
	.byte	0x9
	.byte	0x35
	.long	0xe7
	.byte	0x50
	.uleb128 0xc
	.ascii "rle_last_0\0"
	.byte	0x9
	.byte	0x36
	.long	0xe7
	.byte	0x54
	.uleb128 0xc
	.ascii "rle_last_1\0"
	.byte	0x9
	.byte	0x37
	.long	0xe7
	.byte	0x58
	.uleb128 0xc
	.ascii "width_deviation\0"
	.byte	0x9
	.byte	0x39
	.long	0x172
	.byte	0x5c
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc28
	.uleb128 0xe
	.byte	0x4
	.long	0xc0d
	.uleb128 0x3
	.ascii "bg_t\0"
	.byte	0x9
	.byte	0x3c
	.long	0xf52
	.uleb128 0xe
	.byte	0x4
	.long	0x10f3
	.uleb128 0xe
	.byte	0x4
	.long	0x10e1
	.uleb128 0x9
	.long	0x13f
	.long	0x110a
	.uleb128 0x21
	.long	0x201
	.word	0x3ff
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc1c
	.uleb128 0x22
	.ascii "range_from\0"
	.byte	0x1
	.byte	0x1b
	.long	0x172
	.uleb128 0x5
	.byte	0x3
	.long	_range_from
	.uleb128 0x22
	.ascii "range_to\0"
	.byte	0x1
	.byte	0x1c
	.long	0x172
	.uleb128 0x5
	.byte	0x3
	.long	_range_to
	.uleb128 0x22
	.ascii "is_exclude\0"
	.byte	0x1
	.byte	0x1d
	.long	0xe0
	.uleb128 0x5
	.byte	0x3
	.long	_is_exclude
	.uleb128 0x22
	.ascii "map_to\0"
	.byte	0x1
	.byte	0x1e
	.long	0x172
	.uleb128 0x5
	.byte	0x3
	.long	_map_to
	.uleb128 0x23
	.ascii "bf_Map\0"
	.byte	0x1
	.byte	0xe8
	.long	LFB22
	.long	LFE22-LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x11a7
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.byte	0xe8
	.long	0x10d5
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "map_cmd_list\0"
	.byte	0x1
	.byte	0xe8
	.long	0x677
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x23
	.ascii "bf_map_list\0"
	.byte	0x1
	.byte	0xd0
	.long	LFB21
	.long	LFE21-LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0x11f7
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.byte	0xd0
	.long	0x10d5
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0xd0
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x22
	.ascii "i\0"
	.byte	0x1
	.byte	0xd2
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x22
	.ascii "bg\0"
	.byte	0x1
	.byte	0xd3
	.long	0x10f3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0x677
	.uleb128 0x23
	.ascii "bf_map_cmd\0"
	.byte	0x1
	.byte	0xb6
	.long	LFB20
	.long	LFE20-LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x124c
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.byte	0xb6
	.long	0x10d5
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0xb6
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x22
	.ascii "i\0"
	.byte	0x1
	.byte	0xb8
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x22
	.ascii "bg\0"
	.byte	0x1
	.byte	0xb9
	.long	0x10f3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x25
	.ascii "map_cmd\0"
	.byte	0x1
	.byte	0x92
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x1272
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x92
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x25
	.ascii "get_range\0"
	.byte	0x1
	.byte	0x83
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x129a
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x83
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x26
	.ascii "get_add\0"
	.byte	0x1
	.byte	0x76
	.long	0x172
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x12d0
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x76
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x22
	.ascii "v\0"
	.byte	0x1
	.byte	0x78
	.long	0x172
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x26
	.ascii "get_mul\0"
	.byte	0x1
	.byte	0x69
	.long	0x172
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x1306
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x69
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x22
	.ascii "v\0"
	.byte	0x1
	.byte	0x6b
	.long	0x172
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x26
	.ascii "get_num\0"
	.byte	0x1
	.byte	0x60
	.long	0x172
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x1330
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x60
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x26
	.ascii "get_hex\0"
	.byte	0x1
	.byte	0x40
	.long	0x172
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x1366
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x40
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x22
	.ascii "v\0"
	.byte	0x1
	.byte	0x42
	.long	0x172
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x26
	.ascii "get_dec\0"
	.byte	0x1
	.byte	0x2c
	.long	0x172
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x139c
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x2c
	.long	0x11f7
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x22
	.ascii "v\0"
	.byte	0x1
	.byte	0x2e
	.long	0x172
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x27
	.ascii "skip_space\0"
	.byte	0x1
	.byte	0x20
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.byte	0x20
	.long	0x11f7
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
	.uleb128 0x21
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x26
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
LASF5:
	.ascii "target_max\0"
LASF2:
	.ascii "dwidth_x\0"
LASF3:
	.ascii "dwidth_y\0"
LASF6:
	.ascii "target_cnt\0"
LASF0:
	.ascii "_on_exit_args\0"
LASF1:
	.ascii "encoding\0"
LASF4:
	.ascii "target_data\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_bf_Log;	.scl	2;	.type	32;	.endef
