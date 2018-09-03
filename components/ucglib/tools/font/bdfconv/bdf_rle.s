	.file	"bdf_rle.c"
	.text
Ltext0:
	.def	_bg_err;	.scl	3;	.type	32;	.endef
_bg_err:
LFB12:
	.file 1 "bdf_rle.c"
	.loc 1 271 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 272 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_puts
	.loc 1 273 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.def	_bg_init_rle;	.scl	3;	.type	32;	.endef
_bg_init_rle:
LFB13:
	.loc 1 276 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 277 0
	movl	8(%ebp), %eax
	movl	$0, 80(%eax)
	.loc 1 278 0
	movl	8(%ebp), %eax
	movl	$1, 76(%eax)
	.loc 1 279 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 68(%eax)
	.loc 1 280 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 72(%eax)
	.loc 1 281 0
	movl	8(%ebp), %eax
	movl	$0, 84(%eax)
	.loc 1 282 0
	movl	8(%ebp), %eax
	movl	$1, 88(%eax)
	.loc 1 283 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_ClearTargetData
	.loc 1 284 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.section .rdata,"dr"
LC0:
	.ascii "error in bg_01_rle 1 0\0"
LC1:
	.ascii "error in bg_01_rle 1 a\0"
LC2:
	.ascii "error in bg_01_rle 1 b\0"
	.text
	.def	_bg_01_rle;	.scl	3;	.type	32;	.endef
_bg_01_rle:
LFB14:
	.loc 1 287 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 288 0
	movl	8(%ebp), %eax
	movl	76(%eax), %eax
	testl	%eax, %eax
	jne	L4
	.loc 1 288 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	84(%eax), %eax
	cmpl	12(%ebp), %eax
	jne	L4
	.loc 1 288 0 discriminator 2
	movl	8(%ebp), %eax
	movl	88(%eax), %eax
	cmpl	16(%ebp), %eax
	jne	L4
	.loc 1 290 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	80(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 80(%eax)
	.loc 1 291 0
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L7
	.loc 1 292 0
	movl	$LC0, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L6
L4:
	.loc 1 296 0
	movl	8(%ebp), %eax
	movl	76(%eax), %eax
	testl	%eax, %eax
	jne	L8
	.loc 1 298 0
	movl	$0, 8(%esp)
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L9
	.loc 1 299 0
	movl	$LC0, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L6
L9:
	.loc 1 300 0
	movl	8(%ebp), %eax
	movl	80(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 80(%eax)
L8:
	.loc 1 302 0
	movl	8(%ebp), %eax
	movl	68(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L10
	.loc 1 303 0
	movl	$LC1, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L6
L10:
	.loc 1 304 0
	movl	8(%ebp), %eax
	movl	72(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L11
	.loc 1 305 0
	movl	$LC2, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L6
L11:
	.loc 1 316 0
	movl	8(%ebp), %eax
	movl	$0, 76(%eax)
	.loc 1 317 0
	movl	8(%ebp), %eax
	movl	80(%eax), %edx
	movl	8(%ebp), %eax
	movl	68(%eax), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 80(%eax)
	.loc 1 318 0
	movl	8(%ebp), %eax
	movl	80(%eax), %edx
	movl	8(%ebp), %eax
	movl	72(%eax), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 80(%eax)
	.loc 1 319 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 84(%eax)
	.loc 1 320 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 88(%eax)
L7:
	.loc 1 322 0
	movl	$1, %eax
L6:
	.loc 1 323 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.def	_bg_prepare_01_rle;	.scl	3;	.type	32;	.endef
_bg_prepare_01_rle:
LFB15:
	.loc 1 335 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 337 0
	jmp	L13
L16:
	.loc 1 339 0
	movl	8(%ebp), %eax
	movl	68(%eax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_01_rle
	testl	%eax, %eax
	jne	L14
	.loc 1 340 0
	movl	$0, %eax
	jmp	L15
L14:
	.loc 1 341 0
	movl	8(%ebp), %eax
	movl	68(%eax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	subl	%edx, %eax
	addl	$1, %eax
	movl	%eax, 12(%ebp)
L13:
	.loc 1 337 0
	movl	8(%ebp), %eax
	movl	68(%eax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	cmpl	12(%ebp), %eax
	jbe	L16
	.loc 1 343 0
	jmp	L17
L19:
	.loc 1 345 0
	movl	8(%ebp), %eax
	movl	72(%eax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_01_rle
	testl	%eax, %eax
	jne	L18
	.loc 1 346 0
	movl	$0, %eax
	jmp	L15
L18:
	.loc 1 347 0
	movl	$0, 12(%ebp)
	.loc 1 348 0
	movl	8(%ebp), %eax
	movl	72(%eax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	subl	%edx, %eax
	addl	$1, %eax
	movl	%eax, 16(%ebp)
L17:
	.loc 1 343 0
	movl	8(%ebp), %eax
	movl	72(%eax), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	subl	$1, %eax
	cmpl	16(%ebp), %eax
	jbe	L19
	.loc 1 350 0
	cmpl	$0, 12(%ebp)
	jne	L20
	.loc 1 350 0 is_stmt 0 discriminator 1
	cmpl	$0, 16(%ebp)
	je	L21
L20:
	.loc 1 351 0 is_stmt 1
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_01_rle
	testl	%eax, %eax
	jne	L21
	.loc 1 352 0
	movl	$0, %eax
	jmp	L15
L21:
	.loc 1 353 0
	movl	$1, %eax
L15:
	.loc 1 354 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE15:
	.section .rdata,"dr"
LC3:
	.ascii "error in bg_rle_compress\0"
LC4:
	.ascii "bd_is_one == 0\0"
LC5:
	.ascii "bdf_rle.c\0"
	.text
	.globl	_bg_rle_compress
	.def	_bg_rle_compress;	.scl	2;	.type	32;	.endef
_bg_rle_compress:
LFB16:
	.loc 1 358 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	.loc 1 369 0
	cmpl	$0, 12(%ebp)
	jne	L23
	.loc 1 370 0
	movl	8(%ebp), %eax
	addl	$20, %eax
	movl	%eax, 12(%ebp)
L23:
	.loc 1 372 0
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_init_rle
	.loc 1 377 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetData
	testl	%eax, %eax
	jns	L24
	.loc 1 378 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L24:
	.loc 1 380 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetData
	testl	%eax, %eax
	jns	L26
	.loc 1 381 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L26:
	.loc 1 382 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1164(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L27
	.loc 1 383 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L27:
	.loc 1 384 0
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1168(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L28
	.loc 1 385 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L28:
	.loc 1 386 0
	movl	12(%ebp), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1156(%eax), %eax
	subl	$1, %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1156(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L29
	.loc 1 387 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L29:
	.loc 1 388 0
	movl	12(%ebp), %eax
	movl	12(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1160(%eax), %eax
	subl	$1, %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1160(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L30
	.loc 1 389 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L30:
	.loc 1 391 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1104(%eax), %eax
	testl	%eax, %eax
	jne	L31
	.loc 1 393 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1172(%eax), %eax
	subl	$1, %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1172(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L32
	.loc 1 394 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L31:
	.loc 1 396 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1104(%eax), %eax
	cmpl	$2, %eax
	jne	L33
	.loc 1 398 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1172(%eax), %eax
	subl	$1, %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1172(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L32
	.loc 1 399 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L33:
	.loc 1 403 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1172(%eax), %eax
	subl	$1, %eax
	movl	$1, %ebx
	movl	%eax, %ecx
	sall	%cl, %ebx
	movl	%ebx, %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	1172(%eax), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L32
	.loc 1 404 0
	movl	$LC3, (%esp)
	call	_bg_err
	movl	$0, %eax
	jmp	L25
L32:
	.loc 1 407 0
	movl	$0, -24(%ebp)
	.loc 1 408 0
	movl	$0, -28(%ebp)
	.loc 1 409 0
	movl	$0, -32(%ebp)
	.loc 1 410 0
	movl	$0, -36(%ebp)
	.loc 1 414 0
	movl	12(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	addl	%edx, %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	L34
L42:
	.loc 1 416 0
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -12(%ebp)
	jmp	L35
L41:
	.loc 1 418 0
	movl	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_GetBBXPixel
	testl	%eax, %eax
	jne	L36
	.loc 1 420 0
	cmpl	$0, -24(%ebp)
	je	L37
	.loc 1 422 0
	movl	-36(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, _bd_list.3265(,%eax,4)
	.loc 1 423 0
	movl	$0, -24(%ebp)
	.loc 1 424 0
	addl	$1, -36(%ebp)
	.loc 1 425 0
	movl	$0, -28(%ebp)
L37:
	.loc 1 427 0
	addl	$1, -28(%ebp)
	jmp	L38
L36:
	.loc 1 431 0
	cmpl	$0, -24(%ebp)
	jne	L39
	.loc 1 433 0
	movl	-36(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, _bd_list.3265(,%eax,4)
	.loc 1 434 0
	movl	$1, -24(%ebp)
	.loc 1 435 0
	addl	$1, -36(%ebp)
	.loc 1 436 0
	movl	$0, -28(%ebp)
L39:
	.loc 1 438 0
	addl	$1, -28(%ebp)
L38:
	.loc 1 441 0
	movl	-32(%ebp), %eax
	cmpl	-28(%ebp), %eax
	jge	L40
	.loc 1 442 0
	movl	-28(%ebp), %eax
	movl	%eax, -32(%ebp)
L40:
	.loc 1 416 0 discriminator 2
	addl	$1, -12(%ebp)
L35:
	.loc 1 416 0 is_stmt 0 discriminator 1
	movl	12(%ebp), %eax
	movl	8(%eax), %edx
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	addl	%edx, %eax
	cmpl	-12(%ebp), %eax
	jg	L41
	.loc 1 414 0 is_stmt 1 discriminator 2
	subl	$1, -16(%ebp)
L34:
	.loc 1 414 0 is_stmt 0 discriminator 1
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	-16(%ebp), %eax
	jle	L42
	.loc 1 447 0 is_stmt 1
	movl	-36(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, _bd_list.3265(,%eax,4)
	.loc 1 448 0
	addl	$1, -36(%ebp)
	.loc 1 450 0
	movl	-36(%ebp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	L43
	.loc 1 452 0
	cmpl	$0, -24(%ebp)
	je	L44
	.loc 1 452 0 is_stmt 0 discriminator 1
	movl	$LC4, 12(%esp)
	movl	$___func__.3272, 8(%esp)
	movl	$452, 4(%esp)
	movl	$LC5, (%esp)
	call	___assert_func
L44:
	.loc 1 453 0 is_stmt 1
	movl	-36(%ebp), %eax
	movl	$0, _bd_list.3265(,%eax,4)
	.loc 1 454 0
	addl	$1, -36(%ebp)
L43:
	.loc 1 464 0
	movl	$0, -20(%ebp)
	jmp	L45
L47:
	.loc 1 469 0
	movl	-20(%ebp), %eax
	addl	$1, %eax
	movl	_bd_list.3265(,%eax,4), %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	_bd_list.3265(,%eax,4), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_prepare_01_rle
	testl	%eax, %eax
	jne	L46
	.loc 1 470 0
	movl	$0, %eax
	jmp	L25
L46:
	.loc 1 464 0 discriminator 2
	addl	$2, -20(%ebp)
L45:
	.loc 1 464 0 is_stmt 0 discriminator 1
	movl	-20(%ebp), %eax
	cmpl	-36(%ebp), %eax
	jl	L47
	.loc 1 477 0 is_stmt 1
	movl	$0, 8(%esp)
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_AddTargetBits
	testl	%eax, %eax
	jne	L48
	.loc 1 478 0
	movl	$0, %eax
	jmp	L25
L48:
	.loc 1 480 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_FlushTargetBits
	testl	%eax, %eax
	jne	L49
	.loc 1 481 0
	movl	$0, %eax
	jmp	L25
L49:
	.loc 1 484 0
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	60(%eax), %eax
	movb	%al, (%edx)
	.loc 1 499 0
	movl	$1, %eax
L25:
	.loc 1 500 0
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE16:
	.section .rdata,"dr"
	.align 4
LC6:
	.ascii "RLE Compress: Encoding %ld bits %u/%u\0"
	.text
	.globl	_bf_RLECompressAllGlyphsWithFieldSize
	.def	_bf_RLECompressAllGlyphsWithFieldSize;	.scl	2;	.type	32;	.endef
_bf_RLECompressAllGlyphsWithFieldSize:
LFB17:
	.loc 1 503 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$72, %esp
	.loc 1 506 0
	movl	$0, -16(%ebp)
	.loc 1 509 0
	movl	$0, -12(%ebp)
	jmp	L51
L53:
	.loc 1 511 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 512 0
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L52
	.loc 1 514 0
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_copy_bbx_and_update_shift
	.loc 1 570 0
	movl	16(%ebp), %edx
	movl	12(%ebp), %eax
	movl	20(%ebp), %ecx
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	leal	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	_bg_rle_compress
	.loc 1 571 0
	movl	-20(%ebp), %eax
	movl	60(%eax), %eax
	leal	0(,%eax,8), %edx
	movl	-20(%ebp), %eax
	movl	64(%eax), %eax
	addl	%edx, %eax
	addl	%eax, -16(%ebp)
	.loc 1 572 0
	cmpl	$0, 20(%ebp)
	je	L52
	.loc 1 574 0
	movl	-20(%ebp), %eax
	movl	60(%eax), %eax
	leal	0(,%eax,8), %edx
	movl	-20(%ebp), %eax
	movl	64(%eax), %eax
	leal	(%edx,%eax), %ecx
	movl	-20(%ebp), %eax
	movl	80(%eax), %edx
	movl	-20(%ebp), %eax
	movl	4(%eax), %eax
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC6, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
L52:
	.loc 1 509 0 discriminator 2
	addl	$1, -12(%ebp)
L51:
	.loc 1 509 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L53
	.loc 1 579 0 is_stmt 1
	movl	-16(%ebp), %eax
	.loc 1 580 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.globl	_bf_RLE_get_glyph_data
	.def	_bf_RLE_get_glyph_data;	.scl	2;	.type	32;	.endef
_bf_RLE_get_glyph_data:
LFB18:
	.loc 1 584 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	12(%ebp), %eax
	movb	%al, -20(%ebp)
	.loc 1 585 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 586 0
	addl	$21, -4(%ebp)
L60:
	.loc 1 589 0
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	L62
	.loc 1 591 0
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-20(%ebp), %al
	jne	L58
	.loc 1 593 0
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$21, %eax
	jmp	L59
L58:
	.loc 1 595 0
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	addl	%eax, -4(%ebp)
	.loc 1 589 0
	jmp	L60
L62:
	.loc 1 590 0
	nop
	.loc 1 597 0
	movl	$0, %eax
L59:
	.loc 1 598 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.section .rdata,"dr"
	.align 4
LC7:
	.ascii "RLE Compress: best zero bits %d, one bits %d, total bit size %lu\0"
	.align 4
LC8:
	.ascii "RLE Compress: Font code generation, selected glyphs=%d, total glyphs=%d\0"
	.align 4
LC9:
	.ascii "RLE Compress: Error, glyph too large, encoding=\0"
	.align 4
LC10:
	.ascii "RLE Compress: 'A' pos = %u, 'a' pos = %u\0"
LC11:
	.ascii "RLE Compress: Font size %d\0"
	.text
	.globl	_bf_RLECompressAllGlyphs
	.def	_bf_RLECompressAllGlyphs;	.scl	2;	.type	32;	.endef
_bf_RLECompressAllGlyphs:
LFB19:
	.loc 1 602 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$116, %esp
	.cfi_offset 3, -12
	.loc 1 607 0
	movl	$0, -28(%ebp)
	movl	$0, -32(%ebp)
	.loc 1 608 0
	movl	$0, -60(%ebp)
	.loc 1 609 0
	movl	$-1, -36(%ebp)
	.loc 1 623 0
	movl	$0, -40(%ebp)
	.loc 1 624 0
	movl	$65, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_GetIndexByEncoding
	movl	%eax, -64(%ebp)
	.loc 1 625 0
	cmpl	$0, -64(%ebp)
	js	L64
	.loc 1 627 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-64(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-64(%ebp), %ecx
	sall	$2, %ecx
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	32(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -40(%ebp)
L64:
	.loc 1 630 0
	movl	$0, -44(%ebp)
	.loc 1 631 0
	movl	$49, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_GetIndexByEncoding
	movl	%eax, -68(%ebp)
	.loc 1 632 0
	cmpl	$0, -68(%ebp)
	js	L65
	.loc 1 634 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-68(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-68(%ebp), %ecx
	sall	$2, %ecx
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	32(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -44(%ebp)
L65:
	.loc 1 637 0
	movl	$0, -48(%ebp)
	.loc 1 638 0
	movl	$103, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_GetIndexByEncoding
	movl	%eax, -72(%ebp)
	.loc 1 639 0
	cmpl	$0, -72(%ebp)
	js	L66
	.loc 1 641 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-72(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	32(%eax), %eax
	movl	%eax, -48(%ebp)
L66:
	.loc 1 645 0
	movl	$0, -52(%ebp)
	.loc 1 646 0
	movl	$40, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_GetIndexByEncoding
	movl	%eax, -76(%ebp)
	.loc 1 647 0
	cmpl	$0, -76(%ebp)
	js	L67
	.loc 1 649 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-76(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-76(%ebp), %ecx
	sall	$2, %ecx
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	32(%eax), %eax
	addl	%edx, %eax
	movl	%eax, -52(%ebp)
	.loc 1 650 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-76(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	32(%eax), %eax
	movl	%eax, -56(%ebp)
	jmp	L68
L67:
	.loc 1 654 0
	movl	-40(%ebp), %eax
	movl	%eax, -52(%ebp)
	.loc 1 655 0
	cmpl	$0, -52(%ebp)
	jne	L69
	.loc 1 656 0
	movl	-44(%ebp), %eax
	movl	%eax, -52(%ebp)
L69:
	.loc 1 658 0
	movl	-48(%ebp), %eax
	movl	%eax, -56(%ebp)
L68:
	.loc 1 662 0
	movl	$2, -20(%ebp)
	jmp	L70
L74:
	.loc 1 664 0
	movl	$2, -24(%ebp)
	jmp	L71
L73:
	.loc 1 666 0
	movl	$0, 12(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLECompressAllGlyphsWithFieldSize
	movl	%eax, -60(%ebp)
	.loc 1 667 0
	movl	-36(%ebp), %eax
	cmpl	-60(%ebp), %eax
	jbe	L72
	.loc 1 669 0
	movl	-60(%ebp), %eax
	movl	%eax, -36(%ebp)
	.loc 1 670 0
	movl	-20(%ebp), %eax
	movl	%eax, -28(%ebp)
	.loc 1 671 0
	movl	-24(%ebp), %eax
	movl	%eax, -32(%ebp)
L72:
	.loc 1 664 0 discriminator 2
	addl	$1, -24(%ebp)
L71:
	.loc 1 664 0 is_stmt 0 discriminator 1
	cmpl	$6, -24(%ebp)
	jle	L73
	.loc 1 662 0 is_stmt 1 discriminator 2
	addl	$1, -20(%ebp)
L70:
	.loc 1 662 0 is_stmt 0 discriminator 1
	cmpl	$6, -20(%ebp)
	jle	L74
	.loc 1 676 0 is_stmt 1
	movl	-36(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$LC7, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 677 0
	movl	$0, 12(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLECompressAllGlyphsWithFieldSize
	.loc 1 680 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_ClearTargetData
	.loc 1 693 0
	movl	8(%ebp), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	1100(%eax), %eax
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC8, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 696 0
	movl	8(%ebp), %eax
	movl	1100(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 697 0
	movl	8(%ebp), %eax
	movl	1104(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 698 0
	movl	-28(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 699 0
	movl	-32(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 702 0
	movl	8(%ebp), %eax
	movl	1164(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 703 0
	movl	8(%ebp), %eax
	movl	1168(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 704 0
	movl	8(%ebp), %eax
	movl	1156(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 705 0
	movl	8(%ebp), %eax
	movl	1160(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 706 0
	movl	8(%ebp), %eax
	movl	1172(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 709 0
	movl	8(%ebp), %eax
	movl	1108(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 710 0
	movl	8(%ebp), %eax
	movl	1112(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 711 0
	movl	8(%ebp), %eax
	movl	1116(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 712 0
	movl	8(%ebp), %eax
	movl	1120(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 715 0
	cmpl	$0, -40(%ebp)
	jle	L75
	.loc 1 716 0
	movl	-40(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	jmp	L76
L75:
	.loc 1 718 0
	movl	-44(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
L76:
	.loc 1 719 0
	movl	-48(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 722 0
	movl	-52(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 723 0
	movl	-56(%ebp), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 726 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 727 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 730 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 731 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 733 0
	movl	$0, -12(%ebp)
	jmp	L77
L82:
	.loc 1 735 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -80(%ebp)
	.loc 1 736 0
	movl	-80(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	js	L78
	.loc 1 738 0
	movl	-80(%ebp), %eax
	movl	52(%eax), %eax
	testl	%eax, %eax
	je	L78
	.loc 1 741 0
	movl	-80(%ebp), %eax
	movl	60(%eax), %eax
	cmpl	$254, %eax
	jle	L79
	.loc 1 743 0
	movl	-80(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC9, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Error
	.loc 1 744 0
	movl	$1, (%esp)
	call	_exit
L79:
	.loc 1 747 0
	movl	$0, -16(%ebp)
	jmp	L80
L81:
	.loc 1 749 0 discriminator 3
	movl	-80(%ebp), %eax
	movl	52(%eax), %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 747 0 discriminator 3
	addl	$1, -16(%ebp)
L80:
	.loc 1 747 0 is_stmt 0 discriminator 1
	movl	-80(%ebp), %eax
	movl	60(%eax), %eax
	cmpl	-16(%ebp), %eax
	jg	L81
L78:
	.loc 1 733 0 is_stmt 1 discriminator 2
	addl	$1, -12(%ebp)
L77:
	.loc 1 733 0 is_stmt 0 discriminator 1
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	L82
	.loc 1 755 0 is_stmt 1
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 756 0
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_AddTargetData
	.loc 1 758 0
	movl	$65, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLE_get_glyph_data
	movl	%eax, -84(%ebp)
	.loc 1 759 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	addl	$17, %eax
	movl	-84(%ebp), %edx
	shrl	$8, %edx
	movb	%dl, (%eax)
	.loc 1 760 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	addl	$18, %eax
	movl	-84(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 762 0
	movl	$97, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLE_get_glyph_data
	movl	%eax, -84(%ebp)
	.loc 1 763 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	addl	$19, %eax
	movl	-84(%ebp), %edx
	shrl	$8, %edx
	movb	%dl, (%eax)
	.loc 1 764 0
	movl	8(%ebp), %eax
	movl	1176(%eax), %eax
	addl	$20, %eax
	movl	-84(%ebp), %edx
	movb	%dl, (%eax)
	.loc 1 766 0
	movl	$97, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLE_get_glyph_data
	movl	%eax, %ebx
	movl	$65, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_RLE_get_glyph_data
	movl	%ebx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$LC10, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 768 0
	movl	8(%ebp), %eax
	movl	1184(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$LC11, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bf_Log
	.loc 1 770 0
	nop
	addl	$116, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
.lcomm _bd_list.3265,8192,32
	.section .rdata,"dr"
	.align 4
___func__.3272:
	.ascii "bg_rle_compress\0"
	.text
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
	.long	0x1627
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.4.0 -mtune=generic -march=i686 -g\0"
	.byte	0xc
	.ascii "bdf_rle.c\0"
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
	.long	0x10e8
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
	.long	0x10f4
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
	.long	0x1105
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
	.long	0x10d6
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
	.long	0x10d0
	.uleb128 0xc
	.ascii "bf\0"
	.byte	0xa
	.byte	0x18
	.long	0x10d0
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
	.long	0x10d6
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
	.long	0x10d6
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
	.uleb128 0x12
	.secrel32	LASF7
	.byte	0xa
	.byte	0x31
	.long	0xe7
	.byte	0x44
	.uleb128 0x12
	.secrel32	LASF8
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
	.long	0x10ee
	.uleb128 0xe
	.byte	0x4
	.long	0x10dc
	.uleb128 0x9
	.long	0x13f
	.long	0x1105
	.uleb128 0x22
	.long	0x201
	.word	0x3ff
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xc1c
	.uleb128 0x23
	.ascii "bf_RLECompressAllGlyphs\0"
	.byte	0x1
	.word	0x259
	.long	LFB19
	.long	LFE19-LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x12c8
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.word	0x259
	.long	0x10d0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x25
	.ascii "i\0"
	.byte	0x1
	.word	0x25b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "j\0"
	.byte	0x1
	.word	0x25b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "bg\0"
	.byte	0x1
	.word	0x25c
	.long	0x10ee
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x25
	.ascii "rle_0\0"
	.byte	0x1
	.word	0x25e
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x25
	.ascii "rle_1\0"
	.byte	0x1
	.word	0x25e
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x25
	.ascii "best_rle_0\0"
	.byte	0x1
	.word	0x25f
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x25
	.ascii "best_rle_1\0"
	.byte	0x1
	.word	0x25f
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x26
	.secrel32	LASF9
	.byte	0x1
	.word	0x260
	.long	0x14c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x25
	.ascii "min_total_bits\0"
	.byte	0x1
	.word	0x261
	.long	0x14c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x25
	.ascii "idx_cap_a\0"
	.byte	0x1
	.word	0x263
	.long	0xe0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x25
	.ascii "idx_cap_a_ascent\0"
	.byte	0x1
	.word	0x264
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x25
	.ascii "idx_1\0"
	.byte	0x1
	.word	0x265
	.long	0xe0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x25
	.ascii "idx_1_ascent\0"
	.byte	0x1
	.word	0x266
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x25
	.ascii "idx_g\0"
	.byte	0x1
	.word	0x267
	.long	0xe0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x25
	.ascii "idx_g_descent\0"
	.byte	0x1
	.word	0x268
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x25
	.ascii "idx_para\0"
	.byte	0x1
	.word	0x269
	.long	0xe0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x25
	.ascii "idx_para_ascent\0"
	.byte	0x1
	.word	0x26a
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x25
	.ascii "idx_para_descent\0"
	.byte	0x1
	.word	0x26b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x25
	.ascii "pos\0"
	.byte	0x1
	.word	0x26d
	.long	0xe7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.byte	0
	.uleb128 0x27
	.ascii "bf_RLE_get_glyph_data\0"
	.byte	0x1
	.word	0x247
	.long	0xe7
	.long	LFB18
	.long	LFE18-LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x1322
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.word	0x247
	.long	0x10d0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x28
	.secrel32	LASF1
	.byte	0x1
	.word	0x247
	.long	0xc0d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x25
	.ascii "font\0"
	.byte	0x1
	.word	0x249
	.long	0x10d6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x29
	.ascii "bf_RLECompressAllGlyphsWithFieldSize\0"
	.byte	0x1
	.word	0x1f6
	.long	0x14c
	.long	LFB17
	.long	LFE17-LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x13dc
	.uleb128 0x24
	.ascii "bf\0"
	.byte	0x1
	.word	0x1f6
	.long	0x10d0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "rle_0\0"
	.byte	0x1
	.word	0x1f6
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x24
	.ascii "rle_1\0"
	.byte	0x1
	.word	0x1f6
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x28
	.secrel32	LASF10
	.byte	0x1
	.word	0x1f6
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x25
	.ascii "i\0"
	.byte	0x1
	.word	0x1f8
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "bg\0"
	.byte	0x1
	.word	0x1f9
	.long	0x10ee
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x26
	.secrel32	LASF9
	.byte	0x1
	.word	0x1fa
	.long	0x14c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "local_bbx\0"
	.byte	0x1
	.word	0x1fb
	.long	0xf56
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.uleb128 0x29
	.ascii "bg_rle_compress\0"
	.byte	0x1
	.word	0x165
	.long	0xe0
	.long	LFB16
	.long	LFE16-LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0x14f6
	.uleb128 0x24
	.ascii "bg\0"
	.byte	0x1
	.word	0x165
	.long	0x10ee
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "bbx\0"
	.byte	0x1
	.word	0x165
	.long	0x14f6
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x28
	.secrel32	LASF7
	.byte	0x1
	.word	0x165
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x28
	.secrel32	LASF8
	.byte	0x1
	.word	0x165
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x28
	.secrel32	LASF10
	.byte	0x1
	.word	0x165
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x25
	.ascii "x\0"
	.byte	0x1
	.word	0x167
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x25
	.ascii "y\0"
	.byte	0x1
	.word	0x168
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x25
	.ascii "i\0"
	.byte	0x1
	.word	0x169
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x25
	.ascii "bd_is_one\0"
	.byte	0x1
	.word	0x16a
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x25
	.ascii "bd_curr_len\0"
	.byte	0x1
	.word	0x16b
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x25
	.ascii "bd_max_len\0"
	.byte	0x1
	.word	0x16c
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x25
	.ascii "bd_chg_cnt\0"
	.byte	0x1
	.word	0x16d
	.long	0xe0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x25
	.ascii "bd_list\0"
	.byte	0x1
	.word	0x16f
	.long	0x14fc
	.uleb128 0x5
	.byte	0x3
	.long	_bd_list.3265
	.uleb128 0x2a
	.ascii "__func__\0"
	.long	0x151d
	.uleb128 0x5
	.byte	0x3
	.long	___func__.3272
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.long	0xf56
	.uleb128 0x9
	.long	0xe0
	.long	0x150d
	.uleb128 0x22
	.long	0x201
	.word	0x7ff
	.byte	0
	.uleb128 0x9
	.long	0x147
	.long	0x151d
	.uleb128 0xa
	.long	0x201
	.byte	0xf
	.byte	0
	.uleb128 0x4
	.long	0x150d
	.uleb128 0x2b
	.ascii "bg_prepare_01_rle\0"
	.byte	0x1
	.word	0x14e
	.long	0xe0
	.long	LFB15
	.long	LFE15-LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x1573
	.uleb128 0x24
	.ascii "bg\0"
	.byte	0x1
	.word	0x14e
	.long	0x10ee
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "a\0"
	.byte	0x1
	.word	0x14e
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x24
	.ascii "b\0"
	.byte	0x1
	.word	0x14e
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x2b
	.ascii "bg_01_rle\0"
	.byte	0x1
	.word	0x11e
	.long	0xe0
	.long	LFB14
	.long	LFE14-LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x15bc
	.uleb128 0x24
	.ascii "bg\0"
	.byte	0x1
	.word	0x11e
	.long	0x10ee
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x24
	.ascii "a\0"
	.byte	0x1
	.word	0x11e
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x24
	.ascii "b\0"
	.byte	0x1
	.word	0x11e
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x2c
	.ascii "bg_init_rle\0"
	.byte	0x1
	.word	0x113
	.long	LFB13
	.long	LFE13-LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x1607
	.uleb128 0x24
	.ascii "bg\0"
	.byte	0x1
	.word	0x113
	.long	0x10ee
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x28
	.secrel32	LASF7
	.byte	0x1
	.word	0x113
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x28
	.secrel32	LASF8
	.byte	0x1
	.word	0x113
	.long	0xe7
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x2d
	.ascii "bg_err\0"
	.byte	0x1
	.word	0x10e
	.long	LFB12
	.long	LFE12-LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x24
	.ascii "s\0"
	.byte	0x1
	.word	0x10e
	.long	0x677
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
	.uleb128 0x28
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
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
LASF5:
	.ascii "target_max\0"
LASF7:
	.ascii "rle_bits_per_0\0"
LASF8:
	.ascii "rle_bits_per_1\0"
LASF2:
	.ascii "dwidth_x\0"
LASF3:
	.ascii "dwidth_y\0"
LASF9:
	.ascii "total_bits\0"
LASF6:
	.ascii "target_cnt\0"
LASF10:
	.ascii "is_output\0"
LASF0:
	.ascii "_on_exit_args\0"
LASF1:
	.ascii "encoding\0"
LASF4:
	.ascii "target_data\0"
	.ident	"GCC: (GNU) 6.4.0"
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_bg_ClearTargetData;	.scl	2;	.type	32;	.endef
	.def	_bg_AddTargetBits;	.scl	2;	.type	32;	.endef
	.def	_bg_AddTargetData;	.scl	2;	.type	32;	.endef
	.def	_bg_GetBBXPixel;	.scl	2;	.type	32;	.endef
	.def	___assert_func;	.scl	2;	.type	32;	.endef
	.def	_bg_FlushTargetBits;	.scl	2;	.type	32;	.endef
	.def	_bf_copy_bbx_and_update_shift;	.scl	2;	.type	32;	.endef
	.def	_bf_Log;	.scl	2;	.type	32;	.endef
	.def	_bf_GetIndexByEncoding;	.scl	2;	.type	32;	.endef
	.def	_bf_ClearTargetData;	.scl	2;	.type	32;	.endef
	.def	_bf_AddTargetData;	.scl	2;	.type	32;	.endef
	.def	_bf_Error;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
