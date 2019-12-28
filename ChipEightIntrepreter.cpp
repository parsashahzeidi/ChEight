# ifndef _CHIPEIGHTINTREPRETER_CPP
# define _CHIPEIGHTINTREPRETER_CPP

# include <stdint.h>
# include <iostream>

# include "ChipEightSetup.hpp"
# include "GeneralIntrepreter.hpp"

// Chip Eight Display Pixel
class ChipEightDisplayPixel: public GeneralDisplayPixel{
	// --- Body
	// --- No Virtual function found.

	// --- CTOR ~ DTOR
public:
	ChipEightDisplayPixel( bool val ): value( val ) { }
	ChipEightDisplayPixel(): value( 0 ) { }
	~ChipEightDisplayPixel(){ }
};


// Chip Eight Display
class ChipEightDisplay: GeneralDisplay{
	// --- Body
public:
	/**
	 * @brief Prints an ASCII display to stdout
	*/
	void print_to_stdout(){
		for ( uint64_t x = 0; x < DISPLAY_X_RESOLUTION; x++ ){
			for ( uint64_t y = 0; y < DISPLAY_Y_RESOLUTION; y++ ){
				// Black Pixel
				if (display_cache DISPLAY_INDEX( x, y ) == ( 0 ) )
					std::cout << "  ";
				else 
					std::cout << "\178\178";
			}
		}
	}

	/**
	 * @brief Clears a previously printed ASCII display (At stdout)
	*/
	void clear_print(){
		// Clearing the lines one by one using ANSI Escape Codes 
		for ( uint64_t y = 0; y < DISPLAY_Y_RESOLUTION; y++ )
			std::cout << "\033[2K\033[1A";
	}

	// --- CTOR ~ DTOR
public:
	ChipEightDisplay(){ display_cache = DISPLAY_ALLOCATE; }
	~ChipEightDisplay(){ delete[] display_cache; }
};


// Chip Eight CPU
class ChipEightCPU: GeneralCPU{
	// --- Body
	// --- No virtual functions found.

	// --- CTOR ~ DTOR
public:
	ChipEightCPU(){
		registers = REGISTER_ARRAY_ALLOCATE;
		reset_registers();

		pc = PROGRAM_COUNTER_ALLOCATE;
		reset_stack();
	}
	~ChipEightCPU(){ delete[] pc, registers; }
};


// Chip Eight Memory
class ChipEightMemory: GeneralMemory{
	// --- Body
	// --- No virtual functions found.

	// --- CTOR ~ DTOR
public:
	ChipEightMemory(){ memory_ptr = MEMORY_ALLOCATE; }
	~ChipEightMemory(){ delete[] memory_ptr; }
};


// Chip Eight Motherboard
class ChipEightMotherboard: GeneralMotherboard{
	// --- Body
	// --- No virtual functions found.
	
	// --- CTOR ~ DTOR
protected:
	ChipEightMotherboard( MEMORY_TYPE mem, CPU_TYPE _cpu ){
		memory = mem;
		cpu = _cpu;
	}
	~ChipEightMotherboard(){ }
};


// Chip Eight Computer
class ChipEightComputer: GeneralComputer{
	// --- Body
	// --- No virtual functions found.

	// --- CTOR ~ DTOR
protected:
	ChipEightComputer( DISPLAY_TYPE disp, MOTHERBOARD_TYPE mboard ){
		display = disp;
		motherboard = mboard;
	}
	~ChipEightComputer(){ }
};


// Chip Eight OpCode
class ChipEightOpCode: GeneralOpCode{
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
	ChipEightOpCode(){ }
	ChipEightOpCode( OPCODE_CACHE_TYPE in ){ opcode_cache = in; }
	~ChipEightOpCode(){ }
};


// Chip Eight OpCode List
class ChipEightOpCodeList: GeneralOpCodeList{
	// --- Body
	// --- No virtual functions found.

	// --- CTOR ~ DTOR
protected:
	ChipEightOpCodeList(){ }
	~ChipEightOpCodeList(){ }
};


// Chip Eight State
class ChipEightState{
	// --- Body
	// --- No virtual functions found.

	// --- CTOR ~ DTOR
public:
	ChipEightState(){
		display = DISPLAY_ALLOCATE;
		registers = REGISTER_ARRAY_ALLOCATE;
		stack = PROGRAM_COUNTER_ALLOCATE;
	}
	~ChipEightState(){ delete[] display, registers, stack; }
};


// Chip Eight Intrepreter
class ChipEightIntrepreter: GeneralIntrepreter{
	// --- Body
public:
	/**
	 * @brief Iterates thru a system cycle
	*/
	virtual void iterate(){
		if (paused)
			return;

		opcode_list->find_opcode(motherboard->get_opcode())->run(this);
	}
	/**
	 * @brief Runs a series of system cycles
	*/
	virtual void intrepret() = 0;  // TODO: <

	// --- CTOR ~ DTOR
protected:
	ChipEightIntrepreter( COMPUTER_TYPE comp ){ computer = comp; }
	~ChipEightIntrepreter(){ }
};


# endif
