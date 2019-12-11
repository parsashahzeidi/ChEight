# ifndef _CHEIGHT_CPU
# define _CHEIGHT_CPU

# include <stdint.h>
# include <time.h>
# include <chrono>
# include <thread>
# include "constants.hpp"
# include "essentials.hpp"


class ChipEightHardware{
// --- Head ---
public:
	uint8_t memory[MEM_SIZ] = {0};
	uint16_t stack[STK_ARR_SIZ] = {0x0200};
	uint8_t stack_no = 0;

	uint16_t add_register = 0;
	uint8_t cpu_register[REG_SIZ] = {0};

	bool display[DISP_X][DISP_Y] = {0};

	bool keyboard[16] = {0};

	uint64_t delay_timer = 0;
	uint64_t sound_timer = 0;

	std::thread timer;
	std::thread key_detect;

// --- Body ---
private:
	/**
	 * @brief Writes font data to memory
	*/
	void font_write(){
		static uint8_t font_data[80] = {
			0xf0, 0x90, 0x90, 0x90, 0xf0,  // 0
			0x20, 0x20, 0x20, 0x20, 0x20,  // 1
			0xf0, 0x90, 0x20, 0x40, 0xf0,  // 2
			0xf0, 0x10, 0xf0, 0x10, 0xf0,  // 3
			0xa0, 0xa0, 0xa0, 0xf0, 0x20,  // 4
			0xf0, 0x80, 0xf0, 0x10, 0xf0,  // 5
			0xf0, 0x80, 0xf0, 0x90, 0xf0,  // 6
			0xf0, 0x10, 0x10, 0x10, 0x10,  // 7
			0xf0, 0x90, 0xf0, 0x90, 0xf0,  // 8
			0xf0, 0x90, 0xf0, 0x10, 0xf0,  // 9
			0xf0, 0x90, 0xf0, 0x90, 0x90,  // a
			0x80, 0x80, 0xf0, 0x90, 0xf0,  // b
			0xf0, 0x80, 0x80, 0x80, 0xf0,  // c
			0x10, 0x10, 0xf0, 0x90, 0xf0,  // d
			0xf0, 0x80, 0xf0, 0x80, 0xf0,  // e
			0xf0, 0x80, 0xe0, 0x80, 0x80   // f
		};

		for (uint8_t i = 0; i < 80; i++){
			memory[i] = font_data[i];
		}
	}

	/**
	 * @brief Decreases the timers at 62.5hz. \
		 This timer runs independendently bc of some opcodes
	*/
	void timer_loop(){
		while (true){
			// Wait till next tick
			std::this_thread::sleep_for(
				std::chrono::milliseconds(16)
			);

			if (delay_timer)
				delay_timer--;
			
			if (sound_timer)
				sound_timer--;
		}
	}

	/**
	 * @brief Helps make a thread of a non-static function (timer_loop).
	*/
	static void chip_eight_initialiser(ChipEightHardware* hard){
		hard->timer_loop();
	}

public:
	/**
	 * @brief Initialises the class timers & fonts.
	*/
	void init(){
		timer = std::thread(chip_eight_initialiser, this);
		font_write();
	}

protected: // Singleton
	ChipEightHardware();
	~ChipEightHardware();

};

# endif
