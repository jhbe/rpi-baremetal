MEMORY 
{ 
	ram : ORIGIN = 0x8000, LENGTH = 0x18000 
} 

SECTIONS 
{ 
	.text : { *(.text*) } > ram
	.bss : { *(.bss*) } > ram
	_end = .;
} 
