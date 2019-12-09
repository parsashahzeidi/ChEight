# undef wxNO_THREADS
# undef wxUSE_THREADS
# define wxUSE_THREADS 1

# include <wx/wxprec.h>
# include <wx/wx.h>

# include "../essentials.hpp"

# include "Class Sources/ChEightApp.cpp"
# include "Class Sources/ChEightMainFrame.cpp"

wxIMPLEMENT_APP(ChEightApp);
