# ifndef _GENERALINTREPRETER_HPP
# define _GENERALINTREPRETER_HPP 1

# include <stdint.h>
# include "GeneralSetup.hpp"

// General Display Pixel
class GeneralDisplayPixel{
	// --- Head
public:
	PIXEL_TYPE value;

	// --- Body
public:
# ifdef PIXEL_IS_RGBA
	/**
	 * @brief Gets the red colour
	*/
	PIXEL_R_TYPE get_r(){ return PIXEL_R_GET( value ); }
	/**
	 * @brief Gets the green colour
	*/
	PIXEL_G_TYPE get_g(){ return PIXEL_G_GET( value ); }
	/**
	 * @brief Gets the blue colour
	*/
	PIXEL_B_TYPE get_b(){ return PIXEL_B_GET( value ); }

# elif defined( PIXEL_IS_MONO )
	/**
	 * @brief Gets the value
	*/
	PIXEL_V_TYPE get_v(){ return PIXEL_V_GET( value ); }

# endif

	GeneralDisplayPixel& operator=( PIXEL_TYPE in ){
		value = in;
		return *this;
	}

	bool operator==( PIXEL_TYPE in ){
		return value == in;
	}

	bool operator!=( PIXEL_TYPE in ){
		return value != in;
	}

	PIXEL_TYPE& operator^=( PIXEL_TYPE in ){
		return value ^= in;  // Dependency for ChipEight
	}

	// --- CTOR ~ DTOR
public:
	GeneralDisplayPixel( PIXEL_TYPE val ): value( val ) { }
	GeneralDisplayPixel(): value( 0 ) { }
	~GeneralDisplayPixel(){ }
};


// General Display
class GeneralDisplay{
	// --- Head
public:
	DISPLAY_CACHE_TYPE display_cache = nullptr;

	// --- Body
public:
	DISPLAY_PIXEL_TYPE& operator[]( uint64_t in ){
		return display_cache[ in ];
	};

	/**
	 * @brief Prints an ASCII display to stdout
	*/
	virtual void print_to_stdout() = 0;
	/**
	 * @brief Clears a previously printed ASCII display (At stdout)
	*/
	virtual void clear_print() = 0;

	/**
	 * @brief Sets the value of a specific pixel 
	*/
	void set_pixel( uint64_t x, uint64_t y, PIXEL_TYPE val ){
		display_cache DISPLAY_INDEX( x, y ) = val;
	}

	/**
	 * @brief Renews the class
	*/
	void clear_state(){
		delete[] display_cache;
		display_cache = DISPLAY_ALLOCATE;
	}

	// --- CTOR ~ DTOR
public:
	GeneralDisplay(){ display_cache = DISPLAY_ALLOCATE; }
	~GeneralDisplay(){ delete[] display_cache; }
};


// General CPU
class GeneralCPU{
	// --- Head
public:
	REGISTER_ARRAY_TYPE registers = nullptr;
	ADDRESS_REGISTER_TYPE add_register = 0x0200;

	PROGRAM_COUNTER_TYPE pc = nullptr;

	// --- Body
public:
	/**
	 * @brief Renews the registers
	*/
	void reset_registers(){
		for ( uint64_t it = 0; it < REGISTER_ARRAY_SIZE; it++ )
			registers[it] = 0;
	}

	/**
	 * @brief Renews the stack
	*/
	void reset_stack(){
		for ( uint64_t it = 0; it < PROGRAM_COUNTER_STACK_SIZE; it++ )
			pc[it] = 0;
	}

public:
	/**
	 * @brief Renews the class
	*/
	void clear_state(){
		delete[] pc, registers;

		registers = REGISTER_ARRAY_ALLOCATE;
		reset_registers();

		pc = PROGRAM_COUNTER_ALLOCATE;
		reset_stack();
	}

	// --- CTOR ~ DTOR
protected:
	GeneralCPU(){
		registers = REGISTER_ARRAY_ALLOCATE;
		reset_registers();

		pc = PROGRAM_COUNTER_ALLOCATE;
		reset_stack();
	}
	~GeneralCPU(){ delete[] pc, registers; }
};


// General Memory
class GeneralMemory{
	// --- Head
public:
	MEMORY_POINTER_TYPE memory_ptr = nullptr;

	// --- Body
public:
	MEMORY_ITEM_TYPE& operator[]( uint64_t in ){
		return memory_ptr MEMINDEX( in );
	}

	/**
	 * @brief Renews the class
	*/
	void clear_state(){
		delete[] memory_ptr;
		memory_ptr = MEMORY_ALLOCATE;
	}

	// --- CTOR ~ DTOR
protected:
	GeneralMemory(){ memory_ptr = MEMORY_ALLOCATE; }
	~GeneralMemory(){ delete[] memory_ptr; }
};


// General Motherboard
class GeneralMotherboard{
	// --- Head
public:
	MEMORY_TYPE memory = nullptr;
	CPU_TYPE cpu = nullptr;

	// --- Body
public:
	/**
	 * @brief Renews the class
	*/
	void clear_state(){
		memory->clear_state();
		cpu->clear_state();
	}
	
	// --- CTOR ~ DTOR
protected:
	GeneralMotherboard( MEMORY_TYPE mem, CPU_TYPE _cpu ){
		memory = mem;
		cpu = _cpu;
	}
	~GeneralMotherboard(){ }
};


// General Computer
class GeneralComputer{
	// --- Head
public:
	MOTHERBOARD_TYPE motherboard = nullptr;
	DISPLAY_TYPE display = nullptr;

	// --- Body
public:
	/**
	 * @brief Renews the class
	*/
	void clear_state(){
		motherboard->clear_state();
		display->clear_state();
	}

	// --- CTOR ~ DTOR
protected:
	GeneralComputer( DISPLAY_TYPE disp, MOTHERBOARD_TYPE mboard ){
		display = disp;
		motherboard = mboard;
	}
	~GeneralComputer(){ }
};


// General OpCode
class GeneralOpCode{
	// --- Head
public:
	OPCODE_CACHE_TYPE opcode_cache = 0;

	// --- Body
public:
	/**
	 * @brief Checks if an opcode has the same pattern as this one
	*/
	virtual bool is_this_type( OPCODE_CACHE_TYPE ) = 0;
	/**
	 * @brief Launches the opcode
	*/
	virtual bool run( INTREPRETER_TYPE ) = 0;

	// --- CTOR ~ DTOR
protected:
	GeneralOpCode(){ }
	GeneralOpCode( OPCODE_CACHE_TYPE in ){ opcode_cache = in; }
	~GeneralOpCode(){ }
};


// General OpCode List
class GeneralOpCodeList{
	// --- Head
public:
	OPCODE_TYPE* arr;
	uint64_t arrlen;

	// --- Body
public:
	OPCODE_TYPE& operator[]( uint64_t in ){
		return arr[in];
	}

	/**
	 * @brief Finds a specific opcode
	*/
	OPCODE_TYPE find_opcode( OPCODE_CACHE_TYPE in ){
		for (uint64_t it = 0; it < arrlen; it++)
			if ( arr[it]->is_this_type( in ) )
				return arr[it];
		
		return arr[0];
	}

	// --- CTOR ~ DTOR
public:
	GeneralOpCodeList(){ }
	~GeneralOpCodeList(){ }
};


// General State
class GeneralState{
	// --- Head
public:
	DISPLAY_CACHE_TYPE display = nullptr;
	REGISTER_ARRAY_TYPE registers = nullptr;
	ADDRESS_REGISTER_TYPE add_register = 0x0200;
	PROGRAM_COUNTER_TYPE stack = nullptr;

	// --- Body
public:
	/**
	 * @brief sets the display state
	*/
	void set_display(DISPLAY_CACHE_TYPE disp){
		for ( uint64_t it = 0; it < DISPLAY_X_RESOLUTION * DISPLAY_Y_RESOLUTION; it++ )
				display[ it ] = disp[ it ];
	}
	/**
	 * @brief sets the cpu registers
	*/
	void set_cpu_registers( REGISTER_ARRAY_TYPE regs ){
		for ( uint64_t it = 0; it < REGISTER_ARRAY_SIZE; it++ )
			registers[ it ] = regs[ it ];
	}
	/**
	 * @brief sets the address register
	*/
	void set_add_register( ADDRESS_REGISTER_TYPE add_reg ){ add_register = add_reg; }
	/**
	 * @brief Sets the stack value
	*/
	void set_stack( PROGRAM_COUNTER_TYPE pc ){
		for ( uint64_t it = 0; it < PROGRAM_COUNTER_STACK_SIZE; it++ )
			stack[ it ] = pc[ it ];
	}

	// --- CTOR ~ DTOR
public:
	GeneralState(){
		display = DISPLAY_ALLOCATE;
		registers = REGISTER_ARRAY_ALLOCATE;
		stack = PROGRAM_COUNTER_ALLOCATE;
	}
	~GeneralState(){ delete[] display, registers, stack; }
};


// General Intrepreter
class GeneralIntrepreter{
	// --- Head
public:
	OPCODE_LIST_TYPE opcode_list = nullptr;
	COMPUTER_TYPE computer = nullptr;

	bool paused = false;

	// --- Body
public:
	/**
	 * @brief Iterates thru a system cycle
	*/
	virtual void iterate() = 0;
	/**
	 * @brief Runs a series of system cycles
	*/
	virtual void intrepret() = 0;
	
	/**
	 * @brief Renews the class
	*/
	void clear_state(){
		computer->clear_state();
	}

	STATE_TYPE get_state(){
		STATE_TYPE state;

		state->set_display( computer->display->display_cache );

		state->set_cpu_registers( computer->motherboard->cpu->registers );
		state->set_add_register( computer->motherboard->cpu->add_register );

		state->set_stack( computer->motherboard->cpu->pc );

		return state;
	}

	/**
	 * @brief Pauses the emu
	*/
	void pause(){ paused = true;}
	/**
	 * @brief Gets out of the pause state
	*/
	void resume(){ paused = false; }
	/**
	 * @brief Returns pause state
	*/
	bool is_paused(){ return paused; }

	// --- CTOR ~ DTOR
protected:
	GeneralIntrepreter( COMPUTER_TYPE comp ){ computer = comp; }
	GeneralIntrepreter(){ }
	~GeneralIntrepreter(){ }
};

# endif