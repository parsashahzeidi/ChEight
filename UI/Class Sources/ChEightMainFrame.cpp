# ifndef _CHEIGHTMAINFRAME_CPP
# define _CHEIGHTMAINFRAME_CPP 1

# include "../Class Headers/ChEightMainFrame.hpp"


wxBEGIN_EVENT_TABLE(ChEightMainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, ChEightMainFrame::on_exit)
wxEND_EVENT_TABLE()


DEFINE_EVENT(ChEightMainFrame::on_exit){
    event.Skip(1);
    Close(1);
}


DEFINE_EVENT(ChEightMainFrame::on_f_read_state){
    event.Skip();
}


DEFINE_EVENT(ChEightMainFrame::on_f_save_state){
    event.Skip();
}


DEFINE_EVENT(ChEightMainFrame::on_f_make_empty_state){
    event.Skip();
}


DEFINE_EVENT(ChEightMainFrame::on_f_pause_play_state){
    event.Skip();

    if (intrepreter.pause)
        menu_file->SetLabel(4, "Resume Gameplay\tSpace");
    else
        menu_file->SetLabel(4, "Pause Gameplay\tSpace");
    
    intrepreter.pause = !intrepreter.pause;
}


DEFINE_EVENT(ChEightMainFrame::on_f_preferences){
    event.Skip();
}


ChEightMainFrame::ChEightMainFrame(): 
    wxFrame(nullptr, wxID_ANY, "ChEight - Idle.") {
    // --- Menu Bar ---
    // -- Head --
    menu_bar = new wxMenuBar;
    menu_file = new wxMenu;
    menu_view = new wxMenu;
    menu_cheats = new wxMenu;

    // -- Body --
    // - menu_file -
    menu_file->Append(ID_F_READ_STATE, "Load Memory\tCtrl-O");
    menu_file->Append(ID_F_SAVE_STATE, "Save Memory\tCtrl-S");
    menu_file->Append(ID_F_MAKE_EMPTY_STATE, "Clear Memory\tShift-Del");
    menu_file->AppendSeparator();
    menu_file->Append(ID_F_PAUSE_PLAY_STATE, "Pause Gameplay\tSpace");
    menu_file->AppendSeparator();
    menu_file->Append(ID_F_PREFERENCES, "Preferences\tCtrl-Shift-Esc");
    menu_file->AppendSeparator();
    menu_file->Append(wxID_EXIT, "Exit\tCtrl-Q");
    // Appending to the menu bar
    menu_bar->Append(menu_file, "&File");

    // - menu_view -
    menu_view->Append(ID_V_KEYPAD, "View the Keypad");
    menu_view->Append(ID_V_DISPLAY, "View the Chip-8 Display");
    menu_view->AppendSeparator();
    menu_view->Append(ID_V_OPCODE_HISTORY, "View the OpCode History");
    menu_view->Append(ID_V_OPCODE_LIST, "View the OpCode Wiki\tCtrl-K");
    // Appending to the menu bar
    menu_bar->Append(menu_view, "&View");

    // - menu_cheats -
    menu_cheats->Append(ID_C_PROCESSOR_SPEED, "Change the Processing Speed\tShift-S");
    menu_cheats->AppendSeparator();
    menu_cheats->Append(ID_C_MAKE_SNAPSHOT, "Make a Snapshot\tShift-M");
    menu_cheats->Append(ID_C_REMOVE_LAST_SNAPSHOT, "Remove last Snapshot\tShift-M");
    menu_cheats->Append(ID_C_RESTORE_LAST_SNAPSHOT, "Restore last Snapshot\tShift-M");
    // Appending to the menu bar
    menu_bar->Append(menu_cheats, "&Cheats");

    // -- Feet --
    SetMenuBar(menu_bar);
    CreateStatusBar();
    SetStatusText("Idle");
}


ChEightMainFrame::~ChEightMainFrame(){
    
}

# endif
