//
//
//
// file: game.cpp
// last modified:
// copyright:
// version:
//
// email:
// web:
//



#include <iostream>
#include <cstring>
#include <cstdlib>

//#include <cstdlib>
//#include <cstdio>
//#include <string.h>
//#include <iomanip>
//#include <iterator>
//#include <pthread.h>

//#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <cstdio>

#include "GameUI.h"

#ifdef QT_VERSION
#include "../common/cmdlib.h"
#else
#include "cmdlib.h"
#endif
//#include "threads.h"
#include "sudoku.h"








using namespace std;


int main(int argc, char *argv[])
{

    char		source[1024];
//    char		Extension[1024];
    int			size(0);
    sudoku_t    *header;
    Sudoku game1;

////////////////////////////////////////////////////////////////////

/*
    mx_setcwd (mx::getApplicationPath ());

// fix me
	char cmdline[1024] = "";
	if (argc > 1)
	{
		strcpy (cmdline, argv[1]);
		for (int i = 2; i < argc; i++)
		{
			strcat (cmdline, " ");
			strcat (cmdline, argv[i]);
		}
	}





	//mx::setDisplayMode (0, 0, 0);
	mx::init (argc, argv);
	g_GameUI = new GameUI ();
//	g_GameUI->setMenuBar (g_GameUI->getMenuBar ());
	g_GameUI->setBounds (20, 20, 800, 600);
	g_GameUI->setVisible (true);

//		g_GameUI->Maximize();


	int ret = mx::run ();

	mx::cleanup ();
*/
	char cmdline[1024] = "";
	if (argc > 1)
	{
		strcpy (cmdline, argv[1]);
		for (int i = 2; i < argc; i++)
		{
			strcat (cmdline, " ");
			strcat (cmdline, argv[i]);
		}
	}



    QApplication app(argc, argv);
    printf("this is the console");
    g_GameUI = new GameUI ();
    g_GameUI->resize(800, 600);
    g_GameUI->show();
    return app.exec();


////////////////////////////////////////////////////////////////////


        if (argc == 1)
        Error ((char *)"usage: sudoku textfile");
        cout<<"\n---------------------\n";

        strcpy (source, argv[1]);
        DefaultExtension (source, (char *)".txt");

        size = LoadFile (source, (void **)&header);

        cout<<source<<":"<<size<<endl;

        game1.setSudoku( *header );

        game1.display();

        cout<<"\n---------------------\n";
        sudoku_t    target;

        target = sudoku_t(game1);

        for(int i=0;i<97;i++)
            cout<<target.str[i].str;

        SaveFile (source,&target,sizeof(sudoku_t));

//    system("pause");

//    return ret;
//    return app.exec();

}

