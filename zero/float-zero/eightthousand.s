.section .eight
.global _eightstart
_eightstart:
	// Enable VFP ------------------------------------------------------------

	// r1 = Access Control Register
	MRC p15, #0, r1, c1, c0, #2

	// enable full access for p10,11
	ORR r1, r1, #(0xf << 20)

	// ccess Control Register = r1
	MCR p15, #0, r1, c1, c0, #2
	MOV r1, #0

	// flush prefetch buffer because of FMXR below
	MCR p15, #0, r1, c7, c5, #4

	// and CP 10 & 11 were only just enabled
	// Enable VFP itself
	MOV r0,#0x40000000

	// FPEXC = r0
	FMXR FPEXC, r0

	bl _start
