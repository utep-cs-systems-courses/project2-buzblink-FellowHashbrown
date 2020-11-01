	.arch msp430g2553
	.p2align 1,0

	.text

jt:
	.word default
	.word case1
	.word case2
	.word case3
	.word case4

	.global state_advance

state_advance:
	mov.b #5, r13
	mov.b &switch_state_changed, r12
	cmp.b r12, r13
	jnc default
	add r12, r12
	mov jt(r12), r0
	jmp jt[s]

default:
case1:
	call #toggle_red
	jmp end
case2:
	call #toggle_green
	jmp end
case3:
	call #toggle_red_green
	jmp end
case4:
	call #toggle_off
	jmp end
end:
	ret
