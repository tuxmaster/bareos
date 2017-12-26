/*
	Copyright (C) 2017 Frank Büttner frank@familie-büttner.de

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "MainWindow.h"
#include <QtGui>

#ifndef Q_OS_WIN
#include <signal.h>
void setup_unix_signal_handlers()
{
	struct sigaction term;
	term.sa_handler = MainWindow::termSignalHandler;
	sigemptyset(&term.sa_mask);
	term.sa_flags |= SA_RESTART;
	sigaction(SIGTERM, &term, 0);
}
#endif
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	app.setApplicationName("qt-tray-monitor");

	QTranslator QtTranslation;
	QTranslator AppTranslation;

	QString QtTranslationPath=QLibraryInfo::location(QLibraryInfo::TranslationsPath);
	QString AppTranslationPath=QtTranslationPath;

#ifdef Q_OS_WIN
	AppTranslationPath="./";
#endif

	QtTranslation.load(QLocale(),"qt","_",QtTranslationPath);
	AppTranslation.load(QLocale(),app.applicationName().toLower(),"_",QtTranslationPath);

	if((!AppTranslation.isEmpty()) && (!QtTranslation.isEmpty()))
	{
		app.installTranslator(&QtTranslation);
		app.installTranslator(&AppTranslation);
	}

	MainWindow w;
#ifndef Q_OS_WIN
	setup_unix_signal_handlers();
#endif
	w.show();

	return app.exec();
}
