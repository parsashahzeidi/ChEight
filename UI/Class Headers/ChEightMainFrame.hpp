# ifndef _CHEIGHTMAINFRAME_HPP
# define _CHEIGHTMAINFRAME_HPP 1

# include "../includes.hpp"

# define DEFINE_EVENT(event_name) void event_name(wxCommandEvent& event)


class ChEightMainFrame: public wxFrame{
private:
    // ---  MenuBar  ---
    // -- Events --
    // - menu_file -
    enum {
        ID_F_READ_STATE = 256,
        ID_F_SAVE_STATE = 257,
        ID_F_MAKE_EMPTY_STATE = 258,

        ID_F_PAUSE_PLAY_STATE = 259,

        ID_F_PREFERENCES = 260
    };

    // - menu_view -
    enum {
        ID_V_KEYPAD = 261,
        ID_V_DISPLAY = 262,

        ID_V_OPCODE_HISTORY = 263,
        ID_V_OPCODE_LIST = 264
    };
    
    // - menu_cheats -
    enum {
        ID_C_PROCESSOR_SPEED = 265,

        ID_C_MAKE_SNAPSHOT = 266,
        ID_C_REMOVE_LAST_SNAPSHOT = 267,
        ID_C_RESTORE_LAST_SNAPSHOT = 268
    };

    // -- Definitions --
    wxMenuBar* menu_bar = nullptr;
    wxMenu* menu_file = nullptr;
    wxMenu* menu_view = nullptr;
    wxMenu* menu_cheats = nullptr;

    // --- Purpose-Related ---
    // -- Defnitions --
    ChipEightIntrepreter intrepreter;

public:
    // System events:
    /**
     * @brief Event that closes the current window.
    */
    DEFINE_EVENT(on_exit);

    // Menu bar events
    /**
     * @brief Load a memory state.
    */
    DEFINE_EVENT(on_f_read_state);

    /**
     * @brief Save a memory state.
    */
    DEFINE_EVENT(on_f_save_state);

    /**
     * @brief Clears the state.
    */
    DEFINE_EVENT(on_f_make_empty_state);

    /**
     * @brief Plays / Resumes the state.
    */
    DEFINE_EVENT(on_f_pause_play_state);

    /**
     * @brief Settings window.
    */
    DEFINE_EVENT(on_f_preferences);

    ChEightMainFrame();
    ~ChEightMainFrame();

    wxDECLARE_EVENT_TABLE();
};

# endif
