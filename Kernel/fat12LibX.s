	.code16                       #generate 16-bit code
	.text                         #executable code location
	.globl _start;                #code entry point

	BOOT_LOADER_CODE_AREA_ADDRESS_SEG=	0
	BOOT_LOADER_CODE_AREA_ADDRESS_OFFSET=	0x7c00
	
	BUFFER_SEGMENT=			0x0
	BUFFER_OFFSET=			0x1000	# future Kernel begin address

	BUFFER_FAT12_SEGMENT=		0x0
	BUFFER_FAT12_OFFSET=		0x9000	

.global _LoadFileWithName
/* predefined macros: stack segment                       */
	


	#BOOT_LOADER_ROOT_OFFSET=	0x0200
	#BOOT_LOADER_FAT_OFFSET=		0x0200





/* predefined macros: floppy disk layout                  */
	BOOT_DISK_SECTORS_PER_TRACK=	0x0012
	BOOT_DISK_HEADS_PER_CYLINDER=	0x0002
	BOOT_DISK_BYTES_PER_SECTOR=	0x0200
	BOOT_DISK_SECTORS_PER_CLUSTER=	0x0001


/* predefined macros: file system layout                  */
	FAT12_FAT_POSITION=		1
	FAT12_FAT_SIZE=			9
	FAT12_ROOT_POSITION=		0x13
	FAT12_ROOT_SIZE=		14
	FAT12_ROOT_ENTRIES=		0x00e0
	FAT12_END_OF_FILE=		0x0ff8

	
/* * * * * * * * * * * * * * * * * * * * * * */
	
	FLOPPY_HEADS=			2
	FLOPPY_TRACKS_PER_HEAD=		80
	FLOPPY_SPT=			18	# Sector per track
	FLOPPY_HPC=			80
	FLOPPY_HPC_MUL_SPT=		1440

_start:	
	jmp _boot                #jump to the boot code to start execution


	

     
     .ascii "OSJPBOOT"		# Disc label     
     .word 512    		# Bytes per sector
     .byte 1	                # Sectors per cluster 
     .word 1			# Reserved sectors for boot record
     .byte 2			# Number of copies of the FAT
     .word 224			# Number of entries in root dir
				# (224 * 32 = 7168 = 14 sectors to read)
     .word 2880			# Number of logical sectors
     .byte 0xf0			# Medium descriptor byte
     .word 9			# Sectors per FAT
     .word 18			# Sectors per track (36/cylinder)
     .word 0x02	                # Number of sides/heads
     .long 0                    # Number of hidden sectors
     .long 0			# Number of LBA sectors
     .word 0			# Drive No: 0
     .byte 41			# Drive signature: 41 for floppy
     .long 0			# Volume ID: any number
     .ascii "OS JP      "	# Volume Label: any 11 chars
     .ascii "FAT12   "		# File system









	msgFail: .asciz "\nERROR" #message about erroneous operation
	msgHello: .asciz "Booting..." #message about erroneous operation 
	msg2: .asciz "T2"
	msg3: .asciz "T3" #message about erroneous operation 
	msgDone: .asciz "Done..." #message about erroneous operation
	msgTrue:	.asciz "true"
	msgFalse:	.asciz "false"
	bootDrive : .byte 0x0000
	BOOT_LOADER_STAGE_2_SEGMENT = 0x100
	TOTAL_SECTORS_TO_READ = 0x03

	fileStage2: .ascii  "KERNEL  BIN"
	

      #macro to print null terminated string
      #this macro calls function PrintString
     .macro PrintString str
          leaw \str, %si
          call _PrintString
     .endm
     #function to print null terminated string
     _PrintString:
          lodsb
          orb  %al  , %al
          jz   _PrintStringOut
          movb $0x0e, %ah
          int  $0x10
          jmp  _PrintString
     _PrintStringOut:
     ret

     PrintX:
	push %bp
	mov %sp,	%bp


	mov $0,		%si
	mov 4(%bp),	%bx
	movb $0x0e, %ah
	PrintX_start:
	
	movb (%bx, %si),	%al
	inc %si
        int  $0x10
	cmp $1000, %si
	jne PrintX_start

	mov %bp,	%sp
	pop %bp
     ret

.macro Compare arg1 arg2
	pushf
	cmp \arg1,	\arg2
	je  Compare_true
	PrintString msgFalse
	jmp Compare_end
Compare_true:
	PrintString msgTrue
Compare_end:	
	popf
.endm



    
	/* this macro is used to read a sector into  */
	/* the target memory                         */
	/* It calls the _readSector function with    */
	/* the following parameters                  */
	/* parameter(s): sector Number               */
	/*            address to load                */
	/*            offset of the address          */
	/*            Number of sectors to read      */
	.macro readSector sectorno, address, offset, totalsectors
	pushw \sectorno
	pushw \address
	pushw \offset
	pushw \totalsectors
	call  _readSector
	addw  $0x0008, %sp
	.endm







	/* this function is used to read a sector    */
	/* into the target memory                    */
	/* parameter(s): sector Number               */
	/*            segment address to load        */
	/*            offset of the address          */
	/*            Number of sectors to read      */
	/*					     */
	/* CYL = LBA / (HPC * SPT)		     */
	/* HEAD = (LBA % (HPC * SPT)) / SPT	     */
	/* SECT = (LBA % (HPC * SPT)) % SPT + 1	     */
	/*					     */
	/*					     */

_readSector:
	
	pushw %bp
	movw %sp,	%bp
	
	
	movw 10(%bp),		%ax		# LBA
	movw $FLOPPY_SPT,	%bx	
	xorw %dx,		%dx
	divw %bx
	
	# Sector
	inc %dx
	mov %dl,		%cl	# ready
	

	# Cylinder & Sector
	movw $FLOPPY_HEADS,	%bx	
	xorw %dx,		%dx
	divw %bx

	mov %al,	%ch		# ready
	mov %dl,	%dh		# ready
	movb $0,	%dl		# ready
	


	movb $0x02  , %ah
	movb 4(%bp) , %al

	movw 8(%bp) , %bx
	movw %bx    , %es
	movw 6(%bp) , %bx
	

	#Compare $1, %ch

	
	int  $0x13
	
	
	jc   _failure
	
	cmpb 4(%bp) , %al
	jc   _failure
#Compare $BOOT_LOADER_BUFFER_OFFSET,	%bx
	
	
	movw %bp    , %sp
	popw %bp
	ret

	/* this macro is used to find a file in the  */
	/* FAT formatted drive                       */
	/* it calls readSector macro to perform this */
	/* activity                                  */
	/* parameter(s): root directory position     */
	/*               target address              */
	/*               target offset               */
	/*               root directory size         */
.macro findFile file
	/* read fat table into memory */
	
	readSector $FAT12_ROOT_POSITION, $BUFFER_SEGMENT, $BUFFER_OFFSET, $FAT12_ROOT_SIZE
	
	push $fileStage2
	
	call  _findFile
	addw  $0x0002, %sp
.endm
	
	/* this function is used to find a file in      */
	/* the FAT formatted drive                      */
	/* parameter(s): root directory position        */
	/*               target address                 */
	/*               target offset                  */
	/*               root directory size            */
	/*					        */
	/* return:	%ax = sector where file starts */
_findFile:
	
	pushw %bp
	movw  %sp   , %bp

	movw  $BUFFER_SEGMENT, %ax
	movw  %ax,	%es
	movw  %ax,	%ds
	movw  $BUFFER_OFFSET, %bx
	
	movw  $FAT12_ROOT_ENTRIES, %dx

	

	jmp   _findFileInitValues

_findFileIn:
	movw  $0x0002  , %cx
	movw  4(%bp)   , %si
	movw  %bx    , %di

	repz  cmpsb
	je    _findFileOut
_findFileDecrementCount:
	decw  %dx
	addw  $0x0020, %bx
	#PrintString msg2
_findFileInitValues:
	cmpw  $0x0000, %dx
	jne   _findFileIn
	je    _failure
_findFileOut:
	addw  $0x001a  , %bx
	movw  %es:(%bx), %ax
	movw  %bp, %sp
	popw  %bp
	#PrintString msg3
	ret

/* this macro is used to load a target file  */
/* into the memory                           */
/* It calls findFile and then loads the data */
/* of the respective file into the memory at */
/* address 0x1000:0x0000                     */
/* parameter(s): target file name            */
.macro loadFile file

     /* find sector where the file starts and pass it to %ax */
     findFile \file

     /* backup %ax */
     pushw %ax
	

     /* read fat table into memory */
     readSector $FAT12_FAT_POSITION, $BUFFER_SEGMENT, $BUFFER_FAT12_OFFSET, $FAT12_FAT_SIZE

     /* restore */	
     popw  %ax


     movw  $BUFFER_OFFSET, %bx
_loadCluster:
     pushw %bx
     pushw %ax

 
     clusterToLinearBlockAddress %ax
     readSector %ax, $BUFFER_SEGMENT, %bx, $BOOT_DISK_SECTORS_PER_CLUSTER



     popw  %ax
     xorw %dx, %dx
     movw $0x0003, %bx
     mulw %bx
     movw $0x0002, %bx
     divw %bx


     movw $BUFFER_FAT12_OFFSET, %bx
     addw %ax, %bx
     movw $BUFFER_SEGMENT, %ax
     movw %ax, %es
     movw %es:(%bx), %ax
     orw  %dx, %dx
     jz   _even_cluster
_odd_cluster:
     shrw $0x0004, %ax
     jmp  _done 
_even_cluster:
     and $0x0fff, %ax
_done:
     popw %bx
     addw $BOOT_DISK_BYTES_PER_SECTOR, %bx
     cmpw $FAT12_END_OF_FILE, %ax
     jl  _loadCluster


     /* execute kernel */
     initKernel     
.endm

/* this macro is used to convert the given   */
/* cluster into a sector number              */
/* it calls _clusterToLinearBlockAddress to  */
/* perform this activity                     */
/* parameter(s): cluster number              */
.macro clusterToLinearBlockAddress cluster
     pushw \cluster
     call  _clusterToLinearBlockAddress
     addw  $0x0002, %sp
.endm

/* this function is used to convert the given*/
/* cluster into a sector number              */
/* parameter(s): cluster number              */
_clusterToLinearBlockAddress:
     pushw %bp
     movw  %sp    , %bp
     movw  4(%bp) , %ax
_clusterToLinearBlockAddressIn:
     subw  $0x0002, %ax
     movw  $BOOT_DISK_SECTORS_PER_CLUSTER, %cx
     mulw  %cx
     addw  $FAT12_ROOT_POSITION, %ax
     addw  $FAT12_ROOT_SIZE, %ax
_clusterToLinearBlockAddressOut:
     movw  %bp    , %sp
     popw  %bp
ret


/* parameter(s): target file name            */
/* this macro is used to pass the control of */
/* execution to the loaded file in memory at */
/* address 0x1000:0x0000                     */
/* parameters(s): none                       */
.macro initKernel
     /* initialize the kernel */
     movw  $(BUFFER_SEGMENT), %ax
     movw  $(BUFFER_OFFSET) , %bx
     movw  %ax, %es
     movw  %ax, %ds
PrintString msgHello
PrintString msgHello
PrintString msgHello
jmp _freeze    
 jmp   $(BUFFER_SEGMENT), $(BUFFER_OFFSET)
.endm
 _LoadFileWithName:
	push %bp
	mov %sp, %bp

	call _boot 
	 #PrintString msgDone
	movw  %bp    , %sp
	pop %bp
     ret
_boot:
	PrintString msgHello
	loadFile fileStage2

     PrintString msgDone
_freeze:                      #infinite loop
     jmp _freeze              #
_failure:                     #
     PrintString msgFail     #write error message and then
     jmp _freeze              #jump to the freezing point
     . = _start + 510         #mov to 510th byte from 0 pos
     .byte 0x55               #append first part of the boot signature
     .byte 0xAA               #append last part of the boot signature


