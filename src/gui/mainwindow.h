/****************************************************************
 *  Vidalia is distributed under the following license:
 *
 *  Copyright (C) 2006,  Matt Edman, Justin Hipple
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

/** 
 * \file mainwindow.h
 * \version $Id$
 */

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>

#include <control/torcontrol.h>

#include "tray/trayicon.h"
#include "about/aboutdialog.h"
#include "log/messagelog.h"
#include "bwgraph/bwgraph.h"
#include "config/configdialog.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /** Default constructor */
  MainWindow();
  /** Default destructor */
  ~MainWindow();


public slots:
  /** Overrides the default show() slot to display the default menubar */
  void show();


private slots:
  /** Called when the user selects "Start" from the menu. */
  void start();
  /** Called when the Tor process has successfully started. */
  void started();
  /** Called when the user selects "Stop" form the menu. */
  void stop();
  /** Called when the Tor process has exited, either expectedly or not. */
  void stopped(int errorCode, QProcess::ExitStatus exitStatus);
  /** Called when the control socket has connected to Tor. */
  void connected();
  /** Called when the user selects "About" from the menu. */
  void showAbout();
  /** Called when the user selects "Message Log" from the menu. */
  void showMessageLog();
  /** Called when the user selects "Bandwidth Graph" from the menu. */
  void showBandwidthGraph();
  /** Called when the user selects "Configuration" from the menu. */
  void showConfig();
  /** Called when the user exits Vidalia. */
  void close();


private:
  /** Sets the application's window or dock (Mac) icon. */
  void setApplicationIcon(QString res);
  /** Create the tray popup menu and it's submenus */
  void createMenus();
  /** Create the actions on the tray menu or menubar */
  void createActions();
  /** Creates a default menubar on Mac */
  void createMenuBar();
  /** Removes the default menubar on Mac */
  void removeMenuBar();
  /* Used to determine if the Tor process exiting was intentional or not */
  bool _isIntentionalExit;
 
  /** A MessageLog object which handles logging Tor messages */
  MessageLog* _messageLog;
  /** A BandwidthGraph object which handles monitoring Tor bandwidth usage */
  BandwidthGraph* _bandwidthGraph;
  /** A TorControl object that handles communication with Tor */
  TorControl* _torControl; 
  /** Instance of a tray icon that will appear in the system tray */
  TrayIcon* _trayIcon; 
  
  /** Define the popup menus for the system tray icon */
  QMenu* _trayMenu;
  /** Defines the actions for the tray menu */
  QAction* _startAct;
  QAction* _stopAct;
  QAction* _configAct;
  QAction* _aboutAct;
  QAction* _exitAct;
  QAction* _bandwidthAct;
  QAction* _messageAct;

/* GUI elements unique on Mac so we can use the system menubar */
#if defined(Q_WS_MAC)
  QMenuBar* _menuBar;
  QMenu* _fileMenu;
  QMenu* _torMenu;
  QMenu* _viewMenu;
  QMenu* _helpMenu;
#endif
};

#endif

