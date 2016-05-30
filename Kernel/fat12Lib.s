.code16gcc
.global _PrintString
.global _LoadFileWithName
.global _ListFiles


	BUFFER_SEGMENT=			0x0
	BUFFER_OFFSET=			0x5000	# future Kernel begin address
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

	BUFFER_FAT12_SEGMENT=		0x0
	BUFFER_FAT12_OFFSET=		0xe000	

/* * * * * * * * * * * * * * * * * * * * * * */
	
	FLOPPY_HEADS=			2
	FLOPPY_TRACKS_PER_HEAD=		80
	FLOPPY_SPT=			18	# Sector per track
	FLOPPY_HPC=			80
	FLOPPY_HPC_MUL_SPT=		1440

	msgFail: .asciz "\nERROR" #message about erroneous operation
	msgHello: .asciz "Booting..." #message about erroneous operation 
	msg2: .asciz "T2"
	msg3: .asciz "T3" #message about erroneous operation 
	msgDone: .asciz "Done..." #message about erroneous operation
	msgTrue:	.asciz "true"
	msgFalse:	.asciz "false"
fileStage2: .ascii  "SAMPLE  TXT"
 
     #function to print null terminated string
     _PrintString:
	push %bp
	mov %sp, %bp
	/*mov 6(%bp),	%si
	_PrintStringNext:
	*/
	mov $9, %ax
	push %ax
	call _Test
	add $2, %sp
	/*
	lodsb
	orb  %al  , %al
	jz   _PrintStringOut
	movb $0x0e, %ah
	int  $0x10
	jmp  _PrintStringNext
        _PrintStringOut:*/
	pop %bp
	
     ret

 _Test:
	push %bp
	mov %sp, %bp

	pop %bp
	ret






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
	
	
	movw 12(%bp),		%ax		# LBA 	 +2
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
	movb 6(%bp) , %al	# +2

	movw 10(%bp) , %bx	# +2
	movw %bx    , %es
	movw 8(%bp) , %bx	# +2
	

	#Compare $1, %ch

	
	int  $0x13
	
	
	jc   _failure
	
	cmpb 6(%bp) , %al	# +2
	jc   _failure
#Compare $BOOT_LOADER_BUFFER_OFFSET,	%bx
	
	movw  %bp    , %sp
	pop %bp
	ret

	/* this macro is used to find a file in the  */
	/* FAT formatted drive                       */
	/* it calls readSector macro to perform this */
	/* activity                                  */
	/* parameter(s): root directory position     */
	/*               target address              */
	/*               target offset               */
	/*               root directory size         */

	
	/* this function is used to find a file in      */
	/* the FAT formatted drive                      */
	/* parameter(s): root directory position        */
	/*               target address                 */
	/*               target offset                  */
	/*               root directory size            */
	/*					        */
	/* return:	%ax = sector where file starts */
_findFile:
	
	push %bp
	mov  %sp   , %bp

	/* read fat table into memory */
	pushw $FAT12_ROOT_POSITION
	pushw $BUFFER_SEGMENT
	pushw $BUFFER_OFFSET
	pushw $FAT12_ROOT_SIZE
	call  _readSector
	addw  $0x0008, %sp
		
	
	
	

	movw  $BUFFER_SEGMENT, %ax
	movw  %ax,	%es
	movw  %ax,	%ds
	movw  $BUFFER_OFFSET, %bx
	
	movw  $FAT12_ROOT_ENTRIES, %dx

	

	jmp   _findFileInitValues

_findFileIn:
	movw  $0x0002  , %cx
	movw  $fileStage2   , %si	# +2
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
	movw  %bp    , %sp
	popw  %bp
	#PrintString msg3
	ret

/* this macro is used to load a target file  */
/* into the memory                           */
/* It calls findFile and then loads the data */
/* of the respective file into the memory at */
/* address 0x1000:0x0000                     */
/* parameter(s): target file name            */
     _loadFile:
	push %bp
	mov %sp, %bp
     /* find sector where the file starts and pass it to %ax */
     call _findFile
	
     /* backup %ax */
     pushw %ax
	
	pushw $FAT12_FAT_POSITION
	pushw $BUFFER_FAT12_SEGMENT
	pushw $BUFFER_FAT12_OFFSET
	pushw $FAT12_FAT_SIZE
     /* read fat table into memory */
    	 call _readSector
	addw  $0x0008, %sp

     /* restore */	
     popw  %ax


     movw  $BUFFER_OFFSET, %bx
_loadCluster:
     pushw %bx
     pushw %ax

	pushw %ax
    	call _clusterToLinearBlockAddress
	addw  $0x0002, %sp

	pushw %ax
	pushw  $BUFFER_SEGMENT
	pushw %bx
	pushw  $BOOT_DISK_SECTORS_PER_CLUSTER
       	call _readSector
	addw  $0x0008, %sp
	



     popw  %ax
     xorw %dx, %dx
     movw $0x0003, %bx
     mulw %bx
     movw $0x0002, %bx
     divw %bx


     movw $BUFFER_FAT12_OFFSET, %bx
     addw %ax, %bx
     movw $BUFFER_FAT12_SEGMENT, %ax
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
	movw  %bp    , %sp
	pop %bp
     /* execute kernel */
     //initKernel     
//.endm
ret

/* this macro is used to convert the given   */
/* cluster into a sector number              */
/* it calls _clusterToLinearBlockAddress to  */
/* perform this activity                     */
/* parameter(s): cluster number              */


/* this function is used to convert the given*/
/* cluster into a sector number              */
/* parameter(s): cluster number              */
_clusterToLinearBlockAddress:
     pushw %bp
     movw  %sp    , %bp
     movw  6(%bp) , %ax		# +2
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
/*.macro initKernel
     /* initialize the kernel 
     movw  $(BUFFER_SEGMENT), %ax
     movw  $(BUFFER_OFFSET) , %bx
     movw  %ax, %es
     movw  %ax, %ds
     PrintString msgDone
     PrintString msgDone
     PrintString msgDone
     ljmp   $(BUFFER_SEGMENT), $(BUFFER_OFFSET)
.endm*/

 _LoadFileWithName:
	push %bp
	mov %sp, %bp
	mov 6(%bp),	%bx
	mov $fileStage2,	%dx
	mov $0,	%si
	_LoadFileWithNameCopyNextLetter:
	
	movb (%bx, %si), %cl
	movb %cl, fileStage2(%si)
	
	inc %si
	cmp $12,	%si
	jne _LoadFileWithNameCopyNextLetter
	


	#_PrintStringNext:
	#movw $0xc000, (BUFFER_OFFSET)
	#movw $0x0,    (BUFFER_SEGMENT)
	call _loadFile 
	 #PrintString msgDone
	mov $BUFFER_OFFSET, %ax
	movw  %bp    , %sp
	pop %bp
	
     ret


_freeze:                      #infinite loop
     jmp _freeze              #
_failure:                     #
     #PrintString msgFail     #write error message and then
     jmp _freeze              #jump to the freezing point





_ListFiles:
	
	push %bp
	mov  %sp   , %bp
	
	/* read fat table into memory */
	pushw $FAT12_ROOT_POSITION
	pushw $BUFFER_SEGMENT
	pushw $BUFFER_OFFSET
	pushw $FAT12_ROOT_SIZE
	call  _readSector
	addw  $0x0008, %sp
		
	
	mov $BUFFER_OFFSET, %ax
	
	mov %bp, %sp
	pop %bp
	ret

















