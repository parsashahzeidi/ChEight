# ifndef SETUP_DONE
# define SETUP_DONE

// ---------------- Tool Defines ----------------

// ----- Chip Eight Display Pixel -----
# ifndef PIXEL_TYPE
	// 0000 000A
	# define PIXEL_TYPE bool

	# define PIXEL_IS_MONO 1

	# define PIXEL_V_MASK 0x01
	# define PIXEL_V_TYPE uint8_t
	# define PIXEL_V_GET( pixel )\
		( PIXEL_V_TYPE ) ( pixel & PIXEL_V_MASK )

# endif

// --- Chip Eight Display ---
# ifndef DISPLAY_PIXEL_TYPE
	# define DISPLAY_PIXEL_TYPE GeneralDisplayPixel
	# define DISPLAY_CACHE_TYPE DISPLAY_PIXEL_TYPE*

	# define DISPLAY_X_RESOLUTION 64
	# define DISPLAY_Y_RESOLUTION 32

	# define DISPLAY_ALLOCATE ( DISPLAY_CACHE_TYPE ) ( new DISPLAY_PIXEL_TYPE[ DISPLAY_X_RESOLUTION * DISPLAY_Y_RESOLUTION ] )
	# define DISPLAY_INDEX( x, y ) [ ( x * DISPLAY_Y_RESOLUTION ) + y ]
# endif

// --- Chip Eight CPU ---
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

// --- Chip Eight Memory ---
# ifndef MEMORY_ALLOCATE_SIZE
	# define MEMORY_ALLOCATE_SIZE 4096
	# define MEMORY_ITEM_TYPE uint8_t
	# define MEMORY_POINTER_TYPE MEMORY_ITEM_TYPE*
	# define MEMORY_ITEM_SIZE sizeof( uint8_t )

	# define MEMORY_ALLOCATE new MEMORY_ITEM_TYPE[ MEMORY_ALLOCATE_SIZE ]

	# define MEMINDEX( in ) [ ( in * MEMORY_ITEM_SIZE ) ]
# endif

// --- Chip Eight OpCode ---
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