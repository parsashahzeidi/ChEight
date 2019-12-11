# ifndef _CHEIGHT_CONSTANTS
# define _CHEIGHT_CONSTANTS

# include <stdint.h>

// File State --------------------------------------------------------------
// -- Memory sizes --
// ChEight's Memory size
# define MEM_SIZ 4096

// -- Registers
// ChEight's Address register's size
# define ADD_REG_SIZ 2
// ChEight's CPU Register array size
# define REG_SIZ 16

// -- Display
// ChEight's Display size's X axis
# define DISP_X 64
// ChEight's Display size's y axis
# define DISP_Y 32
// ChEight's Display size
# define DISP_SIZ ((DISP_Y * DISP_X) >> 3)
// (n >> 3) == (n / 8)

// -- Stack
// ChEight's Stack size
# define STK_ARR_SIZ 25
// ChEight's stack size in bits
# define STK_SIZ (STK_ARR_SIZ << 1)
// (n << 1) == (n * 2)
// ChEight's Stack Iterator size
# define STK_IT_SIZ 1

// ChEight's Save state size
# define FILE_STATE_SIZ (MEM_SIZ + ADD_REG_SIZ + REG_SIZ + DISP_SIZ + STK_SIZ + STK_IT_SIZ)

// -- Types --
// ChEight's Memory type
# define mem_t uint8_t[MEM_SIZ]

// ChEight's Abstract Memory type
# define _AMEM_T uint8_t*
typedef _AMEM_T amem_t;


// Emulator ----------------------------------------------------------------
// -- Masking tools --
// After BitAND-ing 2 values,
// The value is shifted so that the least significant bit
// is on the right side of the byte.
# define mask0x000f(value) \
	(value & 0x000f)
# define mask0x00f0(value) \
	((value & 0x00f0) >> 4)
# define mask0x00ff(value) \
	(value & 0x00ff)
# define mask0x0f00(value) \
	((value & 0x0f00) >> 8)
# define mask0x0fff(value) \
	(value & 0x0fff)
# define mask0xf000(value) \
	((value & 0xf000) >> 12)

# endif
