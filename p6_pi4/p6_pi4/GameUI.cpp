/*

===== GameUI.cpp ========================================================

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <mx.h>
//#include <gl.h>
//#include <mxTga.h>

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

#include "GameUI.h"
#include "ui_mainwindow.h"

#ifdef QT_VERSION
#include "../common/cmdlib.h"
#else
#include "cmdlib.h"
#endif

//#include "threads.h"
#include "sudoku.h"






//for window
#define X_RESOLUTION 800
#define Y_RESOLUTION 600

// for sudoku grid
#define X_SIZE 20
#define Y_SIZE 20

#define X_OFFSET X_RESOLUTION/2 - X_SIZE*9/2
#define Y_OFFSET Y_RESOLUTION/3 - Y_SIZE*9/2



GameUI *g_GameUI = 0;
char g_appTitle[] = "Sudoku";




GameUI :: GameUI(QWidget *parent): QMainWindow(parent) //, ui(new Ui::MainWindow)
{
	setWindowTitle(g_appTitle);
    // create menu stuff
	mb = new  QMenuBar(this);
//	mxMenu *menuFile = new mxMenu ();
	QMenu *menuFile = new QMenu(tr("File"), this);
	QMenu *menuOptions = new QMenu(tr("Options"), this);
	QMenu *menuHelp = new QMenu(tr("Help"), this);
//	mxMenu *menuOptions = new mxMenu ();
//	mxMenu *menuView = new mxMenu ();
//	mxMenu *menuHelp = new mxMenu ();

//	mb->addMenu ("File", menuFile);

//	mb->addMenu ("Help", menuHelp);
/*
	mxMenu *menuRecentModels = new mxMenu ();
	menuRecentModels->add ("(empty)", IDC_FILE_RECENTMODELS1);
	menuRecentModels->add ("(empty)", IDC_FILE_RECENTMODELS2);
	menuRecentModels->add ("(empty)", IDC_FILE_RECENTMODELS3);
	menuRecentModels->add ("(empty)", IDC_FILE_RECENTMODELS4);

	mxMenu *menuRecentPakFiles = new mxMenu ();
	menuRecentPakFiles->add ("(empty)", IDC_FILE_RECENTPAKFILES1);
	menuRecentPakFiles->add ("(empty)", IDC_FILE_RECENTPAKFILES2);
	menuRecentPakFiles->add ("(empty)", IDC_FILE_RECENTPAKFILES3);
	menuRecentPakFiles->add ("(empty)", IDC_FILE_RECENTPAKFILES4);
*/

//	menuFile->add ("Load Game...", IDC_FILE_LOADGAME);
//	menuFile->add ("Save Game...", IDC_FILE_SAVEGAME);
//	menuFile->addSeparator ();
//	menuFile->add ("Exit", IDC_FILE_EXIT);
        QAction *openFile = new QAction(tr("Load Game..."), this);
        QAction *saveFile = new QAction(tr("Save Game..."), this);
        QAction *exitAction = new QAction(tr("Exit"), this);

        QAction *checkGame = new QAction(tr("Check Game..."), this);
        QAction *solveGame = new QAction(tr("Solve Game..."), this);

        QAction *helpAbout = new QAction(tr("About..."), this);

        menuFile->addAction(openFile);
        menuFile->addAction(saveFile);
        menuFile->addSeparator ();
        menuFile->addAction(exitAction);

        menuOptions->addAction(checkGame);
        menuOptions->addAction(solveGame);

        menuHelp->addAction(helpAbout);

        connect(openFile, &QAction::triggered, this, &GameUI::event_load_file);
        connect(saveFile, &QAction::triggered, this, &GameUI::event_save_file);
        connect(exitAction, &QAction::triggered, this, &QApplication::quit);

        connect(checkGame, &QAction::triggered, this, &GameUI::event_check_game);
        connect(solveGame, &QAction::triggered, this, &GameUI::event_solve_game);

        //connect(helpAbout, &QAction::triggered, this, &GameUI::event_load_file);

        mb->addMenu(menuFile);
        mb->addMenu(menuOptions);
        mb->addMenu(menuHelp);

        setMenuBar(mb);

    //bt_open = new mxButton (this,  X_RESOLUTION/3 - 30,  400,  60,  36, "Open",IDC_FILE_LOADGAME);
    //bt_save = new mxButton (this,  X_RESOLUTION/2 - 30,  400,  60,  36, "Save",IDC_FILE_SAVEGAME);
    //bt_solve = new mxButton (this,  X_RESOLUTION/3*2 - 30,  400,  60,  36, "Solve",IDC_GAME_SOLVEGAME);
    bt_open = new QPushButton("Open", this);
    bt_open->move(X_RESOLUTION/3 - 30,400);
    bt_open->resize(60,36);
    bt_save = new QPushButton("Save", this);
    bt_save->move(X_RESOLUTION/2 - 30,400);
    bt_save->resize(60,36);
    bt_solve = new QPushButton("Solve", this);
    bt_solve->move(X_RESOLUTION/3*2 - 30,400);
    bt_solve->resize(60,36);
    bt_check = new QPushButton("Check", this);
    bt_check->move(X_RESOLUTION/2 - 30,466);
    bt_check->resize(60,36);


    //connect(bt_open, &QPushButton::clicked, this, &GameUI::event_load_file);
    connect(bt_open, &QPushButton::clicked, this, &GameUI::event_load_file); //old syntex
    connect(bt_save, &QPushButton::clicked, this, &GameUI::event_save_file);
    connect(bt_solve, &QPushButton::clicked, this, &GameUI::event_solve_game);
    connect(bt_check, &QPushButton::clicked, this, &GameUI::event_check_game);

/*
#ifdef WIN32
	menuHelp->add ("Goto Homepage...", IDC_HELP_GOTOHOMEPAGE);
	menuHelp->addSeparator ();
#endif
	menuHelp->add ("About...", IDC_HELP_ABOUT);
*/

//	mb->setChecked( IDC_OPTIONS_WEAPONORIGIN, bUseWeaponOrigin );
//	mb->setChecked( IDC_OPTIONS_LEFTHAND, bUseWeaponLeftHand );

//    SpdLabel = new mxLabel (this, 170, 70, 35, 18, "Speed");

    for(int i = 0,x = X_OFFSET,y = Y_OFFSET;i < 81; i++)
    {
        if(x==9 * X_SIZE+X_OFFSET)
        {
            x=X_OFFSET;
            y+=Y_SIZE;
        }
        {
            SudokuGrid[i] = new QLineEdit(this);
            SudokuGrid[i]->setText("X");
            SudokuGrid[i]->move(x, y);
            SudokuGrid[i]->resize(X_SIZE, Y_SIZE);
        }
       //SudokuGrid[i] = new mxLineEdit (this, x, y, X_SIZE, Y_SIZE, "X",IDC_GAME_NEWINPUT,0);
       x+=X_SIZE;
    }
/*
    for(int i=0;i<81;i++)
    {
        {
                    SudokuGrid[i] = new mxLabel (this, col, row, 10, 10, "X");
        }

    }
*/
//    d_cpl = new ControlPanel (this);
//	d_cpl->setGlWindow (d_GlWindow);
    bt_save->setEnabled(false);
    bt_solve->setEnabled(false);
    bt_check->setEnabled(false);

    for(int j = 0;j<81;j++)
        SudokuGrid[j]->setEnabled(false);

//    SudokuGrid[1]->setLabel("8");

//	setBounds (20, 20, 800, 800);
    resize(X_RESOLUTION, Y_RESOLUTION);
//	setVisible (true);
}



GameUI::~GameUI ()
{
	// grab some params in case that hasn't updates
//	if( d_cpl )
//		g_viewerSettings.editStep = d_cpl->getEditStep();
//	g_viewerSettings.showMaximized = isMaximized();

//	saveRecentFiles ();
//	SaveViewerSettings ();
//	g_studioModel.FreeModel ();
#ifdef WIN32
	DeleteFile ("midump.txt");
#endif
}
/*
void GameUI :: checkboxSet( int id, bool bState )
{
	mb->setChecked( id, bState );
}
*/
void GameUI ::event_load_file(){
        int			size(0);
        sudoku_t    *header;

//    const char *ptr = mxGetOpenFileName (this, 0, "*.txt");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select a file"), QString(), tr("*.txt"));

    if(!filePath.isEmpty())
    {
    QByteArray byteArray = filePath.toUtf8(); //fix me: toLocal8Bit()
    const char *ptr = byteArray.data();
			if(ptr)
            {
                size = LoadFile ((char*)ptr, (void **)&header);

                std::cout<<ptr<<":"<<size<<std::endl;

                current_game.setSudoku( *header );

                free(header);

                current_game.display();

                    bt_save->setEnabled(true);
                    bt_solve->setEnabled(true);
                    bt_check->setEnabled(true);

                        for(int i = 0;i<81;i++)
                            SudokuGrid[i]->setText(current_game.to_string(i));
                            //SudokuGrid[i]->setLabel(current_game.to_string(i));
                        for(int i = 0;i<81;i++)
                            SudokuGrid[i]->setEnabled(true);

                        game_time_start = I_FloatTime ();
            }
    }

}

void GameUI ::event_save_file(){

        char *str;
        QByteArray byteArray;

            for(int i = 0;i<81;i++) //fix me
            {
                byteArray = SudokuGrid[i]->text().toLocal8Bit(); //fix me: toLocal8Bit()
                str = byteArray.data();
//                if(current_game.to_elements(i,str[0]));   //fix me
/*
                mxMessageBox (this,
				"Invalid input will be ignored!\n", "Warning",
				MX_MB_OK | MX_MB_INFORMATION );
*/
                if(current_game.to_elements(i,str[0]))
                {

                    QMessageBox::warning(this, tr("Warning"),tr("Invalid input will be ignored!"));
                    /*

                int ret = QMessageBox::warning(this, tr("My Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel,
                               QMessageBox::Save);
                               */
                /*
				QMessageBox msgBox;
                msgBox.setWindowTitle("Warning!");
                msgBox.setText("Invalid input will be ignored!\n");
                msgBox.exec();
                */
                }
            }

			//char *ptr = (char *) mxGetSaveFileName (this, 0, "*.txt", 0);

    QString filePath = QFileDialog::getOpenFileName(this, tr("Select a file"), QString(), tr("*.txt"));

    if(!filePath.isEmpty())
    {
    byteArray = filePath.toUtf8(); //fix me: toLocal8Bit()
    const char *ptr = byteArray.data();

			if (ptr)
            {
/*
			char filename[256];
			char ext[16];

			strcpy( filename, ptr );
			strcpy( ext, mx_getextension( filename ));
			if( mx_strcasecmp( ext, ".txt" ))
				strcat( filename, ".txt" );
*/
        sudoku_t target = sudoku_t(current_game);

        SaveFile ((char*)ptr,&target,sizeof(sudoku_t));
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"),tr("Invalid file path!"));
            }
    }
}

void GameUI ::event_exit(){

}

void GameUI ::event_newinput(){

}

void GameUI ::event_solve_game(){

}

void GameUI ::event_check_game(){


    if(SudokuGrid[1]->isEnabled())
				game_time_end = I_FloatTime ();

        char *str;
        QByteArray byteArray;

            for(int i = 0;i<81;i++) //fix me
            {
                byteArray = SudokuGrid[i]->text().toLocal8Bit(); //fix me: toLocal8Bit()
                str = byteArray.data();
//                if(current_game.to_elements(i,str[0]));   //fix me
/*
                mxMessageBox (this,
				"Invalid input will be ignored!\n", "Warning",
				MX_MB_OK | MX_MB_INFORMATION );
*/
                if(current_game.to_elements(i,str[0]))
                {

                    QMessageBox::warning(this, tr("Warning"),tr("Invalid input will be ignored!"));
                }
            }
/*
            for(int i = 0;i<81;i++)
            {
                if(current_game.to_elements(i,(SudokuGrid[i]->getLabel())[0]))

                mxMessageBox (this,
				"Invalid input will be ignored!", "Warning",
				MX_MB_OK | MX_MB_WARNING );
            }
*/

				char str_game_msg[256], str_time[32];
//				sprintf (str_time,"%5.0f seconds elapsed.\n%d %d\n", game_time_end-game_time_start,current_game.isFilled(),current_game.isValid());
                sprintf (str_time,"\n%-5.0f seconds elapsed.", game_time_end-game_time_start);

				if( !current_game.isFilled() && !current_game.isValid())

                    sprintf (str_game_msg,"Sudoku hasn't been completed.\nFound error(s) in your answer.");

                if( !current_game.isFilled() && current_game.isValid())

                    sprintf (str_game_msg,"Sudoku hasn't been completed.\nNo error in your answer.");

                if( current_game.isFilled() && !current_game.isValid())
                {
                        for(int j = 0;j<81;j++)
                            SudokuGrid[j]->setEnabled(false);

                    sprintf (str_game_msg,"You Fail.\nFound error(s) in your answer.");
                }

                if( current_game.isFilled() && current_game.isValid())
                {
                        for(int j = 0;j<81;j++)
                            SudokuGrid[j]->setEnabled(false);

                        sprintf (str_game_msg,"You Win!\nNo error in your answer.");
//                      sprintf (str_game_msg + strlen(str_game_msg),"%s", str_time);

                }
                    sprintf (str_game_msg + strlen(str_game_msg),"%s", str_time);

                    //mxMessageBox (this, str_game_msg, "Sudoku", MX_MB_OK | MX_MB_INFORMATION );
                        QMessageBox::information(this, tr("Sudoku"),tr(str_game_msg));

}

/*
void
GameUI::redraw ()
{
	mxEvent event;
	event.event = mxEvent::Size;
	event.width = w2 ();
	event.height = h2 ();
	handleEvent (&event);
}
*/
