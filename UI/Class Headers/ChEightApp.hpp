# ifndef _CHEIGHTAPP_HPP
# define _CHEIGHTAPP_HPP 1

# include "../includes.hpp"

# include "ChEightMainFrame.hpp"


class ChEightApp: public wxApp{
private:
    ChEightMainFrame* main_frame = nullptr;
    
public:
    /**
     * @brief Build a window. Returns 1 if succesful.
    */
    bool OnInit();
};

# endif
