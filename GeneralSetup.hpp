# ifndef SETUP_DONE
# define SETUP_DONE

// ---------------- Tool Defines ----------------

// ----- General Display Pixel -----
# ifndef PIXEL_TYPE
	// RRRR RGGG GGBB BBBA
	# define PIXEL_TYPE uint16_t

	# define PIXEL_IS_RGBA 1

	# define PIXEL_R_MASK 0xf800
	# define PIXEL_R_TYPE uint8_t
	# define PIXEL_R_GET( pixel )\
		( PIXEL_R_TYPE ) ( ( pixel & PIXEL_R_MASK ) >> 8)

	# define PIXEL_G_MASK 0x07c0
	# define PIXEL_G_TYPE uint8_t
	# define PIXEL_G_GET( pixel )\
		( PIXEL_G_TYPE ) ( ( pixel & PIXEL_G_MASK ) >> 3)

	# define PIXEL_B_MASK 0x003e
	# define PIXEL_B_TYPE uint8_t
	# define PIXEL_B_GET( pixel )\
		( PIXEL_B_TYPE ) ( ( pixel & PIXEL_B_MASK ) << 2)
# endif

// --- General Display ---
# ifndef DISPLAY_PIXEL_TYPE
	# define DISPLAY_PIXEL_TYPE GeneralDisplayPixel
	# define DISPLAY_CACHE_TYPE DISPLAY_PIXEL_TYPE**

	# define DISPLAY_X_RESOLUTION 1920
	# define DISPLAY_Y_RESOLUTION 1080

	# define DISPLAY_ALLOCATE ( DISPLAY_CACHE_TYPE ) ( new DISPLAY_PIXEL_TYPE[ DISPLAY_X_RESOLUTION * DISPLAY_Y_RESOLUTION ] )
	# define DISPLAY_INDEX( x, y ) [ ( x * DISPLAY_Y_RESOLUTION ) + y ]
# endif

// --- General CPU ---
# ifndef REGISTER_ARRAY_TYPE
	# define REGISTER_ARRAY_ITEM_TYPE uint8_t
	# define REGISTER_ARRAY_TYPE REGISTER_ARRAY_ITEM_TYPE*
	# define REGISTER_ARRAY_SIZE 16
	# define REGISTER_ARRAY_ALLOCATE new REGISTER_ARRAY_ITEM_TYPE[ REGISTER_ARRAY_SIZE ]

	# define ADDRESS_REGISTER_TYPE uint16_t
	# define PROGRAM_COUNTER_TYPE ADDRESS_REGISTER_TYPE*
	# define PROGRAM_COUNTER_STACK_SIZE 25
	# define PROGRAM_COUNTER_ALLOCATE new ADDRESS_REGISTER_TYPE[ PROGRAM_COUNTER_STACK_SIZE ]
# endif

// --- General Memory ---
# ifndef MEMORY_ALLOCATE_SIZE
	# define MEMORY_ALLOCATE_SIZE 4096
	# define MEMORY_ITEM_TYPE uint8_t
	# define MEMORY_POINTER_TYPE MEMORY_ITEM_TYPE*
	# define MEMORY_ITEM_SIZE sizeof( uint8_t )

	# define MEMORY_ALLOCATE new MEMORY_ITEM_TYPE[ MEMORY_ALLOCATE_SIZE ]

	# define MEMINDEX( in ) [ ( in * MEMORY_ITEM_SIZE ) ]
# endif

// --- General OpCode ---
# ifndef OPCODE_SIZE
	# define OPCODE_SIZE 2
	# define OPCODE_CACHE_TYPE uint16_t

	# define OPCODE_MASK0x0fff( in )\
		( in & 0x0fff )

	# define OPCODE_MASK0xf000( in )\
		( ( in & 0xf000 ) >> 12 )

	# define OPCODE_MASK0x00f0( in )\
		( ( in & 0x00f0 ) >> 4 )

	# define OPCODE_MASK0x0f00( in )\
		( ( in & 0x0f00 ) >> 8 )

	# define OPCODE_MASK0x000f( in )\
		( in & 0x000f )

	# define OPCODE_MASK0x0ff0( in )\
		( ( in & 0x0ff0 ) >> 4 )
# endif

// ---------------- Type Defines ----------------


# ifndef DISPLAY_TYPE
	# define DISPLAY_TYPE GeneralDisplay*
# endif


# ifndef CPU_TYPE
	# define CPU_TYPE GeneralCPU*
# endif


# ifndef MEMORY_TYPE
	# define MEMORY_TYPE GeneralMemory*
#endif


# ifndef MOTHERBOARD_TYPE
	# define MOTHERBOARD_TYPE GeneralMotherboard*
# endif


# ifndef COMPUTER_TYPE
	# define COMPUTER_TYPE GeneralComputer*
# endif


# ifndef OPCODE_TYPE
	# define OPCODE_TYPE GeneralOpCode*
# endif


# ifndef OPCODE_LIST_TYPE
	# define OPCODE_LIST_TYPE GeneralOpCodeList*
# endif


# ifndef STATE_TYPE 
	# define STATE_TYPE GeneralState*
# endif


# ifndef INTREPRETER_TYPE 
	# define INTREPRETER_TYPE GeneralIntrepreter*
# endif

# endif