# ifndef _CHEIGHT_EMULATOR
# define _CHEIGHT_EMULATOR

# include "opcodes.hpp"
# include "essentials.hpp"
# include "filestate.hpp"
# include "constants.hpp"
# include <thread>
# include <chrono>


class ChipEightIntrepreter: public OpCodeLauncher{
	// --- Head
private:
	std::thread sys_cycle;  // Each motherboard timecycle
	std::thread sys;  // Main thread

	uint16_t current_opcode;

	uint8_t  x_000;
	uint8_t  x000_;
	uint8_t  x00_0;
	uint8_t  x00__;
	uint8_t  x0_00;
	uint16_t x0___;

public:
	bool pause = false;

	uint64_t cpu_speed = 0;

	// --- Body
private:
	/**
	 * @brief Gets an opcode from a stack.
	*/
	uint16_t get_opcode(){
		uint16_t out = 
			(memory[stack[stack_no]] << 8) |
			memory[stack[stack_no]++];

		stack[stack_no]++;
		return out;
	}

public:
	/**
	 * @brief Interpretting command.
	*/
	void iterate(){
		current_opcode = get_opcode();

		// Masks
		x_000 = mask0xf000(current_opcode);
		x000_ = mask0x000f(current_opcode);
		x00_0 = mask0x00f0(current_opcode);
		x00__ = mask0x00ff(current_opcode);
		x0_00 = mask0x0f00(current_opcode);
		x0___ = mask0x0fff(current_opcode);

		// Detecting opcodes

		// 3 Opcodes
		if (x_000 == 0){
			if (current_opcode == 0x0000)
				x0000();
			// Clear Display
			if (current_opcode == 0x00e0)
				x00e0();
			// Return from a stack
			else if (current_opcode == 0x00ee)
				stack_no--;
			// RCA1802
			else
				warn_component("RCA1802 codes cannot be launched.", "Intrepreter");
		}

		// Goto
		else if (x_000 == 1)
			x1___(x0___);

		// Make a stack
		else if (x_000 == 2)
			x2___(x0___);

		// Conditional
		else if (x_000 == 3)
			x3___(x0_00, x00__);

		// Conditional
		else if (x_000 == 4)
			x4___(x0_00, x00__);

		// Conditional
		else if ((x_000 == 5) && (x000_ == 0))
			x5__0(x0_00, x00_0);

		// Const change
		else if (x_000 == 6)
			x6___(x0_00, x00__);

		// Const change
		else if (x_000 == 7)
			x7___(x0_00, x00__);

		// 9 Opcodes
		else if (x_000 == 8){
			// Assign
			if ((x000_ == 0))
				x8__0(x0_00, x00_0);

			// BitOp
			else if (x000_ == 1)
				x8__1(x0_00, x00_0);

			// BitOp
			else if (x000_ == 2)
				x8__2(x0_00, x00_0);

			// BitOp
			else if (x000_ == 3)
				x8__3(x0_00, x00_0);

			// Math
			else if (x000_ == 4)
				x8__4(x0_00, x00_0);

			// Math
			else if (x000_ == 5)
				x8__5(x0_00, x00_0);

			// BitOp
			else if (x000_ == 6)
				x8_06(x0_00);  // reg y isn't usable.

			// Math
			else if (x000_ == 7)
				x8__7(x0_00, x00_0);

			// BitOp
			else if (x000_ == 14 && x00_0 == 0)
				x8_0e(x0_00);
		}

		// Conditional
		else if ((x_000 == 9) && (x000_ == 0))
			x9__0(x0_00, x00_0);
		
		// Const change
		else if (x_000 == 10)
			xa___(x0___);

		// Const change
		else if (x_000 == 11)
			xb___(x0___);

		// Random operation
		else if (x_000 == 12)
			xc___(x0_00, x00__);

		// Display sprite
		else if (x_000 == 13)
			xd___(x0_00, x00_0, x000_);

		// 2 Opcodes
		else if (x_000 == 14){
			// Conditional
			if (x00__ == 0x9e)
				xe_9e(x0_00);

			// Conditional
			else if (x00__ == 0xa1)
				xe_a1(x0_00);
		}

		// 9 Opcodes
		else if (x_000 == 15){
			// Assign
			if (x00__ == 7)
				xf_07(x0_00);
			
			// Assign
			else if (x00__ == 0x0a)
				xf_0a(x0_00);
			
			// Assign
			else if (x00__ == 0x15)
				xf_15(x0_00);
			
			// Assign
			else if (x00__ == 0x18)
				xf_18(x0_00);
			
			// Math
			else if (x00__ == 0x1e)
				xf_1e(x0_00);
			
			// Sprite
			else if (x00__ == 0x29)
				xf_29(x0_00);
			
			// Math
			else if (x00__ == 0x33)
				xf_33(x0_00);

			// Dump
			else if (x00__ == 0x55)
				xf_55(x0_00);
			
			// Dump
			else if (x00__ == 0x65)
				xf_65(x0_00);
		}
		
	}

	/**
	 * @brief Main loop.\
	 *  is usable in general, but my workflow limits me to iterate();.
	*/
	void intrepret(){
		// Initialize timers (Delay, sound).
		init();

		while(1){
			// Wait while pause is true. TODO: This is a busy wait.
			while (pause);

			iterate();

			// Waiting for CPU delay
			sys_cycle.join();
		}
	}

	ChipEightIntrepreter(char mem[MEM_SIZ], uint16_t pc = 0x0200){
		for (uint16_t i = 0; i < MEM_SIZ; i++)
			memory[i] = mem[i];
		stack[0] = pc;
	}

	~ChipEightIntrepreter();
};

# endif
