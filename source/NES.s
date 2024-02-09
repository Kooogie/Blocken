;
; File generated by cc65 v 2.19 - Git ce3bcad
;
	.fopt		compiler,"cc65 v 2.19 - Git ce3bcad"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.export		_MEM_POINTER
	.export		_MEM_POINTER2
	.export		_main
	.export		_draw_level_meta
	.export		_center_screen
	.export		_fetch_palettes
	.export		_get_controller_input
	.export		_wait_for_vertical
	.export		_clear_memory
	.export		_show_loop1
	.export		_show_loop2

.segment	"BSS"

_MEM_POINTER:
	.res	1,$00
_MEM_POINTER2:
	.res	1,$00

; ---------------------------------------------------------------
; void __near__ main (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

.segment	"CODE"

	lda     #$00
	sta     $0000
	tax
	sta     $00FF
	jsr     _clear_memory
	jsr     _fetch_palettes
	jsr     _draw_level_meta
	jsr     _center_screen
	lda     #$1E
	sta     $2001
	ldx     #$00
	lda     #$80
	sta     $2000
L0002:	jsr     _wait_for_vertical
	jsr     _show_loop1
	jsr     _show_loop2
	jsr     _center_screen
	ldx     #$00
	lda     $0000
	inc     $0000
	jmp     L0002

.endproc

; ---------------------------------------------------------------
; void __near__ draw_level_meta (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_draw_level_meta: near

.segment	"CODE"

	lda     #$00
	sta     $0000
	sta     $0001
	sta     $0002
	sta     $0003
	sta     $0004
	sta     $0005
	sta     $0040
L0017:	lda     $0005
	cmp     #$04
	bcc     L001D
	rts
L001D:	lda     $0004
	cmp     #$10
	bne     L0006
	lda     #$00
	sta     $0001
	lda     $0002
	clc
	adc     #$40
	sta     $0002
	lda     #$00
	sta     $0004
L0006:	ldy     $0040
	lda     $E000,y
	sta     _MEM_POINTER
	lda     #$00
	sta     $0000
	lda     $0040
	and     #$0F
	asl     a
	sta     $0001
	lda     #$00
	sta     $0042
L0018:	lda     $0042
	cmp     #$04
	bcs     L001C
	lda     $0000
	clc
	adc     $0001
	bcc     L0016
	clc
L0016:	adc     $0002
	clc
	adc     $0042
	sta     $0003
	lda     _MEM_POINTER
	beq     L0019
	asl     a
	asl     a
	clc
	adc     $0042
	sta     $0050
	ldy     $0050
	lda     $FD00,y
	sta     _MEM_POINTER2
	lda     $0005
	clc
	adc     #$20
	sta     $2006
	lda     $0003
	sta     $2006
	lda     _MEM_POINTER2
	sta     $2007
L0019:	lda     $0042
	cmp     #$01
	bne     L001A
	lda     #$1E
	sta     $0000
L001A:	lda     $0003
	cmp     #$FF
	bne     L001B
	inc     $0005
L001B:	inc     $0042
	jmp     L0018
L001C:	inc     $0004
	inc     $0040
	jmp     L0017

.endproc

; ---------------------------------------------------------------
; void __near__ center_screen (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_center_screen: near

.segment	"CODE"

	lda     #$20
	sta     $2006
	lda     #$00
	sta     $2006
	sta     $2007
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ fetch_palettes (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_fetch_palettes: near

.segment	"CODE"

	lda     #$00
	sta     $0040
L000B:	lda     $0040
	cmp     #$20
	beq     L000C
	lda     #$3F
	sta     $2006
	lda     $0040
	sta     $2006
	lda     #$00
	sta     $2007
	inc     $0040
	jmp     L000B
L000C:	lda     #$00
	sta     $0040
L000D:	lda     $0040
	cmp     #$20
	beq     L0007
	ldy     $0040
	lda     $FC00,y
	sta     _MEM_POINTER
	lda     #$3F
	sta     $2006
	lda     $0040
	sta     $2006
	lda     _MEM_POINTER
	sta     $2007
	inc     $0040
	jmp     L000D
L0007:	rts

.endproc

; ---------------------------------------------------------------
; void __near__ get_controller_input (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_get_controller_input: near

.segment	"CODE"

	lda     #$01
	sta     $4016
	lda     #$00
	sta     $4016
	sta     $0000
L0006:	lda     $0000
	cmp     #$08
	beq     L0007
	lda     $4016
	and     #$01
	sta     $0030
	lda     $0031
	asl     a
	sta     $0031
	lda     $0030
	ora     $0031
	sta     $0031
	inc     $0000
	jmp     L0006
L0007:	lda     $0031
	sta     $0032
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ wait_for_vertical (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_wait_for_vertical: near

.segment	"CODE"

	lda     $2002
	sta     $0022
	cmp     #$80
	bcc     L0007
	lda     $00FF
	cmp     #$01
	beq     L0008
	rts
L0008:	lda     $0000
	lsr     a
	lsr     a
	lsr     a
	lsr     a
	and     #$0F
	sta     $000D
	lda     $0000
	and     #$0F
	sta     $000C
	lda     #$20
	sta     $2006
	lda     #$82
	sta     $2006
	lda     $000D
	ora     #$F0
	sta     $2007
	lda     #$20
	sta     $2006
	lda     #$83
	sta     $2006
	lda     $000C
	ora     #$F0
	sta     $2007
	lda     $0004
	lsr     a
	lsr     a
	lsr     a
	lsr     a
	and     #$0F
	sta     $000D
	lda     $0004
	and     #$0F
	sta     $000C
	lda     #$20
	sta     $2006
	lda     #$80
	sta     $2006
	lda     $000D
	ora     #$F0
	sta     $2007
	lda     #$20
	sta     $2006
	lda     #$81
	sta     $2006
	lda     $000C
	ora     #$F0
	sta     $2007
	lda     #$00
	sta     $0000
	sta     $0004
	rts
L0007:	lda     $00FF
	cmp     #$01
	bne     L0006
	inc     $0000
	lda     $0000
	cmp     #$FF
	bne     L0006
	inc     $0004
L0006:	jmp     _wait_for_vertical

.endproc

; ---------------------------------------------------------------
; void __near__ clear_memory (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_clear_memory: near

.segment	"CODE"

	rts

.endproc

; ---------------------------------------------------------------
; void __near__ show_loop1 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_show_loop1: near

.segment	"CODE"

	lda     $0000
	lsr     a
	lsr     a
	lsr     a
	lsr     a
	and     #$0F
	sta     $000D
	lda     $0000
	and     #$0F
	sta     $000C
	lda     #$28
	sta     $2006
	lda     #$A0
	sta     $2006
	lda     $000D
	clc
	adc     #$F0
	sta     $2007
	lda     #$28
	sta     $2006
	lda     #$A1
	sta     $2006
	lda     $000C
	clc
	adc     #$F0
	sta     $2007
	rts

.endproc

; ---------------------------------------------------------------
; void __near__ show_loop2 (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_show_loop2: near

.segment	"CODE"

	lda     $0001
	lsr     a
	lsr     a
	lsr     a
	lsr     a
	and     #$0F
	sta     $000D
	lda     $0001
	and     #$0F
	sta     $000C
	lda     #$20
	sta     $2006
	lda     #$C0
	sta     $2006
	lda     $000D
	clc
	adc     #$F0
	sta     $2007
	lda     #$20
	sta     $2006
	lda     #$C1
	sta     $2006
	lda     $000C
	clc
	adc     #$F0
	sta     $2007
	rts

.endproc

