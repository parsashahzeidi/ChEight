# ifndef _CHEIGHT_OPCODE
# define _CHEIGHT_OPCODE
# include "hardware.hpp"


class OpCodeLauncher: public ChipEightHardware{
	protected:
		OpCodeLauncher();
		~OpCodeLauncher();

	private:
		uint32_t rnda, rndb, rndc, rndd, rndt, rnds = 100;
		uint32_t rndcount = 0;
		uint32_t temp = 0;

	public:
		/**
		 * @brief Do nothing
		*/
		void x0000();

		/**
		 * @brief Clear display
		*/
		void x00e0(){
			for (uint8_t posx = 0; posx < 64; posx++)
				for (uint8_t posy = 0; posy < 64; posy++)
					display[posx][posy] = 0;
		}

		/**
		 * @brief Return stack
		*/
		void x00ee(){
			if (stack_no)
				stack_no--;
		}

		/**
		 * @brief Go to nnn
		*/
		void x1___(uint16_t nnn){
			stack[stack_no] = nnn;
		}

		/**
		 * @brief Subrootine call @ nnn
		*/
		void x2___(uint16_t nnn){
			stack_no++;
			stack[stack_no] = nnn;
		}

		/**
		 * @brief If register x is equal to nn, skip next command
		*/
		void x3___(uint8_t x, uint8_t nn){
			if (cpu_register[x] == nn)
				stack[stack_no] += 2;
		}

		/**
		 * @brief If register x isn't equal to nn, skip next command
		*/
		void x4___(uint8_t x, uint8_t nn){
			if (cpu_register[x] != nn)
				stack[stack_no] += 2;
		}

		/**
		 * @brief If register x is equal to register y, skip next command
		*/
		void x5__0(uint8_t x, uint8_t y){
			if (cpu_register[x] == cpu_register[y])
				stack[stack_no] += 2;
		}

		/**
		 * @brief Sets register x to nn
		*/
		void x6___(uint8_t x, uint8_t nn){
			cpu_register[x] = nn;
		}

		/**
		 * @brief Adds nn to register x
		*/
		void x7___(uint8_t x, uint8_t nn){
			cpu_register[x] += nn;
		}


		/**
		 * @brief Sets register x to register y
		*/
		void x8__0(uint8_t x, uint8_t y){
			cpu_register[x] = cpu_register[y];
		}

		/**
		 * @brief Sets register x to reg x | reg y
		*/
		void x8__1(uint8_t x, uint8_t y){
			cpu_register[x] |= cpu_register[y];
		}

		/**
		 * @brief Sets register x to reg x & reg y
		*/
		void x8__2(uint8_t x, uint8_t y){
			cpu_register[x] &= cpu_register[y];
		}
		
		/**
		 * @brief Sets register x to reg x ^ reg y
		*/
		void x8__3(uint8_t x, uint8_t y){
			cpu_register[x] ^= cpu_register[y];
		}

		/**
		 * @brief Adds register y to register x. regf = carry
		*/
		void x8__4(uint8_t x, uint8_t y){
			uint16_t out = cpu_register[x] + cpu_register[y];

			if (out >> 8)
				cpu_register[15] = 1;
			else
				cpu_register[15] = 0;
			
			cpu_register[x] += cpu_register[y];
		}

		/**
		 * @brief Subtracts register y from register x. regf = borrow
		*/
		void x8__5(uint8_t x, uint8_t y){
			int16_t out = cpu_register[x] - cpu_register[y];
			
			if (out < 0)
				cpu_register[15] = 1;
			else
				cpu_register[15] = 0;
			
			cpu_register[x] -= cpu_register[y];
		}

		/**
		 * @brief Shifts register x by 1. regf = reg x.least_significant_bit
		*/
		void x8_06(uint8_t x){
			cpu_register[15] = (cpu_register[x] << 7) >> 7;
			cpu_register[x] >>= 1;
		}
		
		/**
		 * @brief regx = regy - regx. regf = borrow
		*/
		void x8__7(uint8_t x, uint8_t y){
			int16_t out = cpu_register[y] - cpu_register[x];
			
			if (out < 0)
				cpu_register[15] = 1;
			else
				cpu_register[15] = 0;
			
			cpu_register[x] = cpu_register[y] - cpu_register[x];
		}

		/**
		 * @brief Shifts register x by -1. regf = reg x.significant_bit
		*/
		void x8_0e(uint8_t x){
			cpu_register[15] = (cpu_register[x] >> 7) << 7;
			cpu_register[x] <<= 1;
		}

		/**
		 * @brief If register x isn't equal to register y, skip next command
		*/
		void x9__0(uint8_t x, uint8_t y){
			if (cpu_register[x] != cpu_register[y])
				stack[stack_no] += 2;
		}

		/**
		 * @brief Sets the addres register to nnn
		*/
		void xa___(uint16_t nnn){
			add_register = nnn;
		}

		/**
		 * @brief Go to nnn + reg0
		*/
		void xb___(uint16_t nnn){
			stack[stack_no] = nnn + cpu_register[0];
		}

		/**
		 * @brief Sets regx to rand() & nn
		*/
		void xc___(uint8_t x, uint8_t nn){
			// XorWOW algorithm
			rndt = rndd;
			rnds = rnda;

			rndd = rndc;
			rndb = rndb;
			rndd = rnds;

			rndt ^= rndt >> 2;
			rndt ^= rndt << 1;
			rndt ^= rnds ^ (rnds << 4);
			rnda = rndt;

			rndcount += 362437;
			cpu_register[x] = ((rndt + rndcount) << 16) >> 16;
		}

		/**
		 * @brief Draws a sprite with width 8 and height n at (reg x, reg y)
		*/
		void xd___(uint8_t x, uint8_t y, uint8_t n){
			cpu_register[15] = 0;
			uint8_t posx = cpu_register[x];
			uint8_t posy = cpu_register[y];

			for (uint8_t drawy = 0; drawy < n; drawy++){
				for (uint8_t drawx = 0; drawx < 8; drawx++){

					bool current_pixel = 
						(
							memory[add_register + drawy] & 
							(1 << drawx)  // ex. drawx = 4; 1 << drawx == 0x0010 (0000 0000 0001 0000);
						)
						>> drawx;

					display[posx + drawx][posy + drawy] ^= current_pixel;
					if (current_pixel && !display[x + drawx][y + drawy])
						cpu_register[15] = 0;
				}
			}
		}

		/**
		 * @brief If the key in reg x is pressed, skip next command
		*/
		void xe_9e(uint8_t x){
			if (keyboard[cpu_register[x]])
				stack[stack_no] += 2;
		}
		
		/**
		 * @brief If the key in reg x isn't pressed, skip next command
		*/
		void xe_a1(uint8_t x){
			if (!keyboard[cpu_register[x]])
				stack[stack_no] += 2;
		}
		
		/**
		 * @brief Sets reg x to delay timer.
		*/
		void xf_07(uint8_t x){
			cpu_register[x] = delay_timer;
		}

		/**
		 * @brief Waits until a keypress
		*/
		void xf_0a(uint8_t x){
			while (
				!(
					keyboard[0]  || keyboard[1]  || keyboard[2]  ||
					keyboard[3]  || keyboard[4]  || keyboard[5]  ||
					keyboard[6]  || keyboard[7]  || keyboard[8]  ||
					keyboard[9]  || keyboard[10] || keyboard[11] ||
					keyboard[12] || keyboard[13] || keyboard[14] ||
					keyboard[15]
				)
			);
		}

		/**
		 * @brief Sets the delay timer to reg x
		*/
		void xf_15(uint8_t x){
			delay_timer = cpu_register[x];
		}

		/**
		 * @brief Sets the sound timer to reg x
		*/
		void xf_18(uint8_t x){
			sound_timer = cpu_register[x];
		}

		/**
		 * @brief Adds reg x to i. reg f = overflow
		*/
		void xf_1e(uint8_t x){
			temp = add_register + cpu_register[x];
			add_register = temp;

			// Overflow
			cpu_register[15] = bool(temp >> 24);
		}

		/**
		 * @brief Sets i to memory location for font char in reg x
		*/
		void xf_29(uint8_t x){
			add_register = x * 5;
		}

		/**
		 * @brief Splits hundreds, tens and ones of reg x onto i, i + 1, i + 2
		*/
		void xf_33(uint8_t x){
			temp = cpu_register[x];

			// Double Dabble algorithm
			for (uint8_t _ = 0; _ < 8; _++){
				temp <<= 1;

				// Ones
				if (((temp >> 8) & 0xff) > 4)
					temp += 768;  // 3 << 8, add 3 to ones

				// Tens
				if (((temp >> 12) & 0xff) > 4)
					temp += 12288;  // 3 << 12, add 3 to tens

				// Hundreds
				if (((temp >> 16) & 0xff) > 4)
					temp += 196608;  // 3 << 16, add 3 to hundreds
			}

			// Ones
			stack[add_register + 2] = (temp >> 8) & 0xff;
			// Tens
			stack[add_register + 1] = (temp >> 12) & 0xff;
			// Hundreds
			stack[add_register] = (temp >> 16) & 0xff;
		}

		/**
		 * @brief Registery dump from reg 0 to reg x to reg i
		*/
		void xf_55(uint8_t x){
			for (uint8_t item = 0; item < x; item++){
				stack[add_register + item] = cpu_register[item];
			}
		}

		/**
		 * @brief Registery replace from reg 0 to reg x from i
		*/
		void xf_65(uint8_t x){
			for (uint8_t item = 0; item < x; item++){
				cpu_register[item] = stack[add_register + item];
			}
		}
};

# endif
