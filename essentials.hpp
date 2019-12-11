# ifndef _CHEIGHT_ESSENTIAL
# define _CHEIGHT_ESSENTIAL

# include <iostream>
# include <string.h>
# include <thread>

std::string last_msg;


/**
 * @brief Error without a crash notifier
*/
void warning(std::string msg){
	if ((msg != last_msg) || (msg != "")){
		std::cerr << "\033[1;38;2;238;206;27m"  // Yellw fg
			<< msg << "\033[0m\n";
		
		last_msg = msg;
	}
}


/**
 * @brief Crash notifier
*/
void error(std::string msg, uint64_t code){
	if ((msg != last_msg) || (msg != "")){
		std::cerr << "\033[1;38;2;223;52m"  // Red fg
			<< msg << "\033[0m\n";

		last_msg = msg;
	}
}


/**
 * @brief Non-Error message notifier
*/
void log(std::string msg){
	if ((msg != last_msg) || (msg != "")){
		std::cout << msg << '\n';

		last_msg = msg;
	}
}


/**
 * @brief Error without a crash notifier for a specific component
*/
void warn_component(std::string msg, std::string component){
	warning(
		component + 
		": Warning: " + 
		msg + 
		".\n"
	);
}


/**
 * @brief Crash notifier for a specific component
*/
void err_component(std::string msg, std::string component, uint64_t code){
	error( 
		component + 
		": Error: " + 
		msg + 
		".\n",
		code
	);
}


/**
 * @brief Non-Error message notifier for a specific component
*/
void log_component(std::string msg, std::string component){
	log(
		component + 
		": " + 
		msg
	);
}

# endif
