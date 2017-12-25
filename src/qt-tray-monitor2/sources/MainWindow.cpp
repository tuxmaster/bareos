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
#include "TrayIcon.h"

#ifndef Q_OS_WIN
#include <sys/socket.h>
#include <unistd.h>
#endif

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
	m_must_close=false;
	setupUi(this);
#ifndef Q_OS_WIN
	::socketpair(AF_UNIX, SOCK_STREAM,0,m_sigtermFd);
	m_sn_term = new QSocketNotifier(m_sigtermFd[1], QSocketNotifier::Read, this);
	connect(m_sn_term, SIGNAL(activated(int)), this, SLOT(handleSigTerm()));
#endif
	tabs->setVisible(false);
	m_trayIcon = new TrayIcon(this);
	connect(m_trayIcon, &TrayIcon::CloseApp, this, &MainWindow::close_me);
	connect(m_trayIcon, &TrayIcon::OpenApp, this, &MainWindow::show_me);

	m_trayIcon->show();
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}

void MainWindow::show_me()
{
	show();
	raise();
}

void MainWindow::close_me()
{
	m_must_close=true;
	QMainWindow::close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (isHidden() || m_must_close)
		event->accept();
	else
	{
		hide();
		event->ignore();
	}
}

bool MainWindow::event(QEvent *e)
{
	if (e->type() == QEvent::WindowStateChange )
	{
		if (isMinimized())
		{
			hide();
			return true;
		}
		else
			return QMainWindow::event(e);
	}
	return QMainWindow::event(e);
}
#ifndef Q_OS_WIN
void MainWindow::termSignalHandler(int)
{
	char a=1;
	::write(m_sigtermFd[0], &a ,sizeof(a));
}

void MainWindow::handleSigTerm()
{
	m_sn_term->setEnabled(false);
	char tmp;
	::read(m_sigtermFd[1], &tmp, sizeof(tmp));
	close_me();
}
int MainWindow::m_sigtermFd[2]={0};
#endif
