# ifndef _CHEIGHTAPP_CPP
# define _CHEIGHTAPP_CPP

# include "../Class Headers/ChEightApp.hpp"


bool ChEightApp::OnInit(){
    main_frame = new ChEightMainFrame;
    main_frame->Show(1);
    return 1;
}

# endif