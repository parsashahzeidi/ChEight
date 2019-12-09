# ifndef _CHEIGHT_MEMSTATE
# define _CHEIGHT_MEMSTATE

# include <stdint.h>
# include "hardware.hpp"
# include "constants.hpp"


class ChipEightMemoryExporter{
	// --- Head
protected:
	// We need a uint8_t*, 
	// because we need to reset the memory.
	amem_t mem = nullptr;
	uint16_t stack[25] = {0x0200};
	uint8_t stack_no = 0;
	uint16_t add_register = 0;
	uint8_t cpu_register[16] = {0};
	bool display[64][32] = {0};  // We'll format this later.

	// --- Body
private:
	/**
	 * @brief Removes the memory.
	*/
	void clear_mem(){
		if (mem != nullptr)
			delete[] mem;
		mem = nullptr;
	}

	/**
	 * @brief Changes all the values in the memory to 0
	*/
	void make_mem_zero(){
		for (uint16_t i = 0; i < 4096; i++)
			mem[i] = 0;
	}

	/**
	 * @brief Allocates 4096 bytes of memory.
	*/
	void alloc_mem(){
		clear_mem();
		mem = new mem_t;
	}

	/**
	 * @brief Replaces the array with another array
	*/
	void replace_mem(uint8_t memory[MEM_SIZ]){
		alloc_mem();
		for (uint16_t i = 0; i < 4096; i++)
			mem[i] = memory[i];
	}

	/**
	 * @brief Replaces the stack.
	*/
	void replace_stack(uint16_t input_stack[25]){
		for (uint8_t i = 0; i < 25; i++)
			stack[i] = input_stack[i] & 0x0fff;
	}

	/**
	 * @brief Replaces the 16 CPU registers.
	*/
	void replace_cpu_registers(uint8_t reg[16]){
		for (uint8_t i = 0; i < 16; i++)
			cpu_register[i] = reg[i];
	}

	/**
	 * @brief Replaces the display pixels.
	*/
	void replace_display(bool screen[DISP_X][DISP_Y]){
		for (uint8_t x = 0; x < DISP_X; x++)
			for (uint8_t y = 0; y < DISP_Y; y++)
				display[x][y] = screen[x][y];
	}

	uint8_t* format_display(bool unformatted[DISP_X][DISP_Y]){
		uint8_t* formatted = new uint8_t[DISP_SIZ];
		uint16_t byte_index, bit_index;

		for (uint8_t x = 0; x < DISP_X; x++)
			for (uint8_t y = 0; y < DISP_Y; y++){
				byte_index = (x * DISP_Y) + y;
				bit_index = byte_index & 0x07;  // == (byte_index % 8)
				byte_index = byte_index >> 3;  // == floor(byte_index / 8)

				formatted[DISP_SIZ - byte_index] |= 
					uint8_t(unformatted[x][y]) << bit_index;
			}

		return formatted;
	}

public:
	uint8_t& operator[](uint16_t addr){
		return mem[addr];
	}

	/**
	 * @brief Exports the current state to a uint8_t[].
	*/
	uint8_t* export_state(){
		uint8_t* state = new uint8_t[FILE_STATE_SIZ];
		uint8_t* screen = nullptr;

		uint16_t root_it = 0;
		uint16_t it;

		// --- Memory ---
		// -- Replacing items in state --
		// - Start: 0 -
		// - Until: 4095 -
		// - Length: 4096 -
		// - Fromat: 4 MiB -
		for (it = 0; it < MEM_SIZ; it++){
			state[it] = mem[it];
		}
		root_it += MEM_SIZ;

		// --- Registers ---
		// -- Address register --
		// - Start: 4096 -
		// - Until: 4097 -
		// - Length: 2 -
		// - Fromat: 1 * 2 bytes -
		state[root_it] = add_register;
		state[root_it++] = (add_register >> 8);

		root_it++;

		// -- CPU registers --
		// - Replacing items in state -
		// Start: 4098
		// Until: 4113
		// Length: 16
		// Format: 16 * 1 byte
		for (it = 0; it < REG_SIZ; it++){
			state[root_it + it] = cpu_register[it];
		}
		root_it += REG_SIZ;

		// --- Display ---
		// -- Formatting the display --
		screen = format_display(display);
		
		// -- Replacing items in state --
		// - Start: 4114 -
		// - Until: 4369 -
		// - Length: 256 bytes -
		// - Format: 32 * 64 booleans, Compressed to 256 * 1 byte -
		for (it = 0; it < DISP_SIZ; it++){
			state[root_it + it] = screen[it];
		}
		root_it += DISP_SIZ;
		
		// -- Preventing leaks --
		delete[] screen;

		// --- Stack ---
		// -- Replacing items in state --
		// - Start: 4370 -
		// - Until: 4419 -
		// - Length: 50 -
		// - Format: 25 * 2 bytes -
		for (uint16_t it = 0; it < STK_SIZ; it++){
			state[root_it + (it * 2)] = stack[it];
			state[root_it + (it * 2)] = (stack[it] >> 8);
		}
		
		// --- Stack Iterator ---
		// -- Replacing items in state --
		// - Start: 4420 -
		// - Until: 4420 -
		// - Length: 1 -
		// - Format: 1 byte integer -
		state[4420] = stack_no;

		return state;
	}

	ChipEightMemoryExporter(){
		make_mem_zero();
	}

	ChipEightMemoryExporter(ChipEightHardware hard){
		// Every savable variable,
		// whose contained in ChipEightHardware.
		// All variables are in order of appearance in 
		// this.export_state();.
		replace_mem(hard.memory);
		replace_stack(hard.stack);
		stack_no = hard.stack_no;
		add_register = hard.add_register;
		replace_cpu_registers(hard.cpu_register);
		replace_display(hard.display);
	}

	~ChipEightMemoryExporter(){
		clear_mem();
	}
};

# endif
