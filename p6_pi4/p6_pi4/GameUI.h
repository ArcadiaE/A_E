//=============================================================================
//
// Purpose: sudoku GUI
//
// $NoKeywords: $
//=============================================================================


#ifndef __GAMEUI_H__
#define __GAMEUI_H__


//#ifndef INCLUDED_MXWINDOW
//#include <mx/mxWindow.h>
//#endif

//
// GameUI.h
//

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

/*
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
*/

#define IDC_FILE_LOADGAME			1001
#define IDC_FILE_SAVEGAME			1002

#define IDC_FILE_EXIT			    1017

#define IDC_GAME_SOLVEGAME		    1101
#define IDC_GAME_NEWINPUT		    1102

#define IDC_HELP_GOTOHOMEPAGE		1301
#define IDC_HELP_ABOUT			    1302


class GameUI : public QMainWindow
{
    //Q_OBJECT

public:
	// CREATORS

    GameUI (QWidget *parent = nullptr);
	~GameUI ();

	// MANIPULATORS
//	virtual int handleEvent (mxEvent *event);
//	void checkboxSet( int id, bool bState );
//	void redraw ();

	// ACCESSORS
//	mxMenuBar *getMenuBar () const { return mb; }
//	GlWindow *getGlWindow () const { return d_GlWindow; }
//	PAKViewer *getPAKViewer () const { return d_PAKViewer; }

private:
    QMenuBar *mb;
    QLineEdit *SudokuGrid[81];

    QPushButton *bt_open;
    QPushButton *bt_save;
    QPushButton *bt_solve;
    QPushButton *bt_check;

//  fix me
//    Ui::MainWindow *ui;
    void event_load_file();
    void event_save_file();
    void event_exit();
    void event_newinput();
    void event_solve_game();
    void event_check_game();

    double game_time_start;
    double game_time_end;

};

extern GameUI *g_GameUI;
extern char g_appTitle[];

#endif  //__GAMEUI_H__
