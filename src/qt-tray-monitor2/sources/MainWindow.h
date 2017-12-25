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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

class TrayIcon;
class QSocketNotifier;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
		Q_OBJECT

	public:
		explicit		MainWindow(QWidget *parent = Q_NULLPTR);
		bool			event(QEvent *e) Q_DECL_FINAL Q_DECL_OVERRIDE;
	public Q_SLOTS:
#ifndef Q_OS_WIN
		void			handleSigTerm();
#endif
#ifndef Q_OS_WIN
		static void		termSignalHandler(int);
#endif
	protected:
		virtual void	changeEvent(QEvent *e) Q_DECL_FINAL Q_DECL_OVERRIDE;
		virtual void	closeEvent(QCloseEvent *event) Q_DECL_FINAL Q_DECL_OVERRIDE;

	private Q_SLOTS:
		void			show_me();
		void			close_me();

	private:
		TrayIcon		*m_trayIcon;
		bool			m_must_close;
#ifndef Q_OS_WIN
		static int		m_sigtermFd[2];
		QSocketNotifier	*m_sn_term;
#endif
};

#endif // MAINWINDOW_H
