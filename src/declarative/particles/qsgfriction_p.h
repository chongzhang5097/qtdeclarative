/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Declarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef FRICTIONAFFECTOR_H
#define FRICTIONAFFECTOR_H
#include "qsgparticleaffector_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Declarative)


class QSGFrictionAffector : public QSGParticleAffector
{
    Q_OBJECT
    Q_PROPERTY(qreal factor READ factor WRITE setFactor NOTIFY factorChanged)
public:
    explicit QSGFrictionAffector(QQuickItem *parent = 0);

    qreal factor() const
    {
        return m_factor;
    }
protected:
    virtual bool affectParticle(QSGParticleData *d, qreal dt);
signals:

    void factorChanged(qreal arg);

public slots:

void setFactor(qreal arg)
{
    if (m_factor != arg) {
        m_factor = arg;
        emit factorChanged(arg);
    }
}

private:
qreal m_factor;
};

QT_END_NAMESPACE
QT_END_HEADER
#endif // FRICTIONAFFECTOR_H
