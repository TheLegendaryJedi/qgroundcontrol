///*=====================================================================
//
//QGroundControl Open Source Ground Control Station
//
//(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
//
//This file is part of the QGROUNDCONTROL project
//
//    QGROUNDCONTROL is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QGROUNDCONTROL is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
//
//======================================================================*/

/**
 * @file
 *   @brief Definition of the class Pixhawk3DWidget.
 *
 *   @author Lionel Heng <hengli@student.ethz.ch>
 *
 */

#ifndef PIXHAWK3DWIDGET_H
#define PIXHAWK3DWIDGET_H

#include <osgText/Text>
#include <osgEarth/MapNode>

#include "Q3DWidget.h"

class UASInterface;

/**
 * @brief A 3D View widget which displays vehicle-centric information.
 **/
class Pixhawk3DWidget : public Q3DWidget
{
    Q_OBJECT

public:
    explicit Pixhawk3DWidget(QWidget* parent = 0);
    ~Pixhawk3DWidget();

    void buildLayout(void);

    double getTime(void) const;

public slots:
    void setActiveUAS(UASInterface* uas);

private slots:
    void showGrid(int state);
    void showTrail(int state);
    void showWaypoints(int state);
    void recenter(void);
    void toggleFollowCamera(int state);

protected:
    virtual void display(void);
    virtual void mousePressEvent(QMouseEvent* event);

    UASInterface* uas;

private:
    osg::ref_ptr<osg::Geode> createGrid(void);
    osg::ref_ptr<osg::Geode> createTrail(void);
    osg::ref_ptr<osgEarth::MapNode> createMap(void);
    osg::ref_ptr<osg::Node> createTarget(void);
    osg::ref_ptr<osg::Group> createWaypoints(void);

    void setupHUD(void);

    void updateHUD(float robotX, float robotY, float robotZ,
                   float robotRoll, float robotPitch, float robotYaw);
    void updateTrail(float robotX, float robotY, float robotZ);
    void updateTarget(void);
    void updateWaypoints(void);

    void markTarget(void);

    bool displayGrid;
    bool displayTrail;
    bool displayTarget;
    bool displayWaypoints;

    bool followCamera;

    osg::ref_ptr<osg::Vec3Array> trailVertices;
    QVarLengthArray<osg::Vec3, 10000> trail;

    osg::ref_ptr<osg::Geometry> hudBackgroundGeometry;
    osg::ref_ptr<osgText::Text> statusText;
    osg::ref_ptr<osg::Geode> gridNode;
    osg::ref_ptr<osg::Geode> trailNode;
    osg::ref_ptr<osg::Geometry> trailGeometry;
    osg::ref_ptr<osg::DrawArrays> trailDrawArrays;
    osg::ref_ptr<osgEarth::MapNode> mapNode;
    osg::ref_ptr<osg::Geode> targetNode;
    osg::ref_ptr<osg::PositionAttitudeTransform> targetPosition;
    osg::ref_ptr<osg::Group> waypointsNode;

    QPushButton* targetButton;

    float lastRobotX, lastRobotY, lastRobotZ;
};

#endif // PIXHAWK3DWIDGET_H
