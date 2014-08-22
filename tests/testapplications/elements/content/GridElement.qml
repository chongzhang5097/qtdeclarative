/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

Item {
    id: gridelementtest
    anchors.fill: parent
    property string testtext: ""

    Grid {
        id: gridelement
        height: 120; width: 120; spacing: 5; columns: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        Rectangle { id: gr; color: "green"; height: 50; width: 50; border.color: "gray"; border.width: 3; opacity: .9; radius: 5; clip: true }
        Rectangle { id: re; color: "red"; height: 50; width: 50; border.color: "gray"; border.width: 3; opacity: .9; radius: 5; clip: true }
        Rectangle {
            id: bl
            color: "blue"; height: 50; width: 50; border.color: "gray"; border.width: 3; radius: 5; clip: true
            opacity: 0; visible: opacity != 0
        }
        Rectangle { id: bk; color: "black"; height: 50; width: 50; border.color: "gray"; border.width: 3; opacity: .9; radius: 5; clip: true }

        move: Transition { NumberAnimation { properties: "x,y"; duration: 1000; easing.type: Easing.OutBounce } }
        add: Transition { NumberAnimation { properties: "x,y"; duration: 1000; easing.type: Easing.OutBounce } }

    }

    SystemTestHelp { id: helpbubble; visible: statenum != 0
        anchors { top: parent.top; horizontalCenter: parent.horizontalCenter; topMargin: 50 }
    }
    BugPanel { id: bugpanel }

    states: [
        State { name: "start"; when: statenum == 1
            PropertyChanges { target: gridelementtest
                testtext: "This is a Grid element. At present it should be showing three rectangles - green, red and black, two "+
                "in the top row.\n"+
                "Next, let's add a rectangle to the Grid - it should drop in from the top and the black rectangle should move to give it space" }
        },
        State { name: "added"; when: statenum == 2
            PropertyChanges { target: bl; opacity: .9 }
            PropertyChanges { target: gridelementtest
                testtext: "The Grid should now be showing four rectangles - green, red, blue and black.\n"+
                "Next, lets alter the Grid to form a single column" }
        },
        State { name: "singlecolumn"; when: statenum == 3
            PropertyChanges { target: bl; opacity: .9 }
            PropertyChanges { target: gridelement; columns: 1 }
            PropertyChanges { target: gridelementtest
                testtext: "The Grid should now be showing four rectangles - green, red, blue and black.\n"+
                "Advance to restart the test." }
        }
    ]

}
