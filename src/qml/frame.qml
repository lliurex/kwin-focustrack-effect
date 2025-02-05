/*
    This script is part of the Lliurex Project 
    SPDX-FileCopyrightText: 2024 juanma1980 <juanma1980@gmail.com>
    SPDX-License-Identifier: GPL-3.0
*/
import QtQuick 2.0
import QtQuick.Controls 2.0

ApplicationWindow {
	id: frame
		property bool outputOnly:true
		property int borderWidth: 10
		color:Qt.rgba(0,0,0,0)
		visible: false
		flags:Qt.FrameLessHint|Qt.WindowStaysOnTopHint|Qt.WindowSystemMenuHint| Qt.X11BypassWindowManagerHint | Qt.FramelessWindowHint| Qt.WindowTransparentForInput| Qt.TransparentForMouseEvents|Qt.OnScreenDisplay
		width:200
		height:300
		Rectangle {
			id:rect
			anchors.fill:parent
			color:frame.color
			border.width: frame.borderWidth
			visible:true
		}

		function moveFrame(x,y,w,h){
		   frame.y=y-frame.borderWidth;
		   frame.x=x-frame.borderWidth;
		   frame.width=w+frame.borderWidth*2;
		   frame.height=h+frame.borderWidth*2;
		   console.log("MOVING");


		} // Window
    Component.onCompleted: {
        frame.show();
		console.log("SHOWING FRAME");
    }
}
