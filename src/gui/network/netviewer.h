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
 * \file netviewer.h
 * \version $Id: netviewer.h 699 2006-04-15 03:12:22Z hipplej $
 */

#ifndef _NETVIEWER_H
#define _NETVIEWER_H

#include <QMainWindow>
#include <QStringList>
#include <QEvent>
#include <QTimer>
#include <control/torcontrol.h>
#include <util/geoip/geoipresolver.h>

#include "zimageview.h"
#include "ui_netviewer.h"


class NetViewer : public QMainWindow
{
  Q_OBJECT

public:
  /** Default constructor */
  NetViewer(QWidget* parent = 0);

public slots:
  /** Overloaded QWidget.show() **/
  void show();
  /** Loads a list of routers that Tor knows about. */
  void loadRouterList();
  /** Loads a list of current circuits and streams. */
  void loadConnections();

protected:
  /** Called to deliver a NEWDESC event from Tor. */
  void customEvent(QEvent *event);

private slots:
  /** Called when the user selects the "Help" action on the toolbar. */
  void help();
  /** Called when the user selects the "New Nym" action on the toolbar. */
  void newNym();
  /** Called when the user selects a map action on the toolbar */
  /** Called when the user selects a circuit on the circuit list */
  void circuitSelected(Circuit circuit);
  /** Called when an IP has been resolved to geographic information. */
  void resolved(int id, QList<GeoIp> geoips);
  
private:
  /** Loads a list of router descriptors from the list of IDs. */
  void loadDescriptors(QStringList ids);

  /** TorControl object used to talk to Tor. */
  TorControl* _torControl;
  /** Timer that fires once an hour to update the router list. */
  QTimer* _timer;
  /** ZImageView that displays the map **/
  ZImageView* _map;
  /** GeoIpResolver used to geolocate routers by IP address. */
  GeoIpResolver _geoip;

  /** Qt Designer generated object **/
  Ui::NetViewer ui;
};

#endif

