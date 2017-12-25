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
#include "TrayIcon.h"

TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(parent)
{
	create_menu();
	setIcon(QIcon(":/os_bar/ok.png"));
	setToolTip(parent->windowTitle());
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason )), this, SLOT(double_click(QSystemTrayIcon::ActivationReason )));
}
void TrayIcon::create_menu()
{
	QWidget *parent=dynamic_cast<QWidget*>(this);
	QMenu *menu = new QMenu(parent);

	QAction *closeAction = new QAction(tr("Exit"),parent);
	connect(closeAction, &QAction::triggered, this, &TrayIcon::CloseApp);
	menu->addAction(closeAction);

	this->setContextMenu(menu);
}
void TrayIcon::double_click(QSystemTrayIcon::ActivationReason click)
{
	if (click == QSystemTrayIcon::DoubleClick)
		Q_EMIT OpenApp();
}
