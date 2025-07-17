/*
    This script is part of the Lliurex Project 
    SPDX-FileCopyrightText: 2024 juanma1980 <juanma1980@gmail.com>
    SPDX-License-Identifier: GPL-3.0
*/
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
	id: frame
		property bool outputOnly:true
		property int borderWidth: 10
		property double frameOpacity: 0
		color:Qt.rgba(0,0,0,0)
    	property color borderColor: Qt.rgba(200,1,0,1)
    	property color frameColor: Qt.rgba(100,120,0,frameOpacity)
		width:200
		height:300
		visible:false
		flags:Qt.FrameLessHint|Qt.WindowStaysOnTopHint|Qt.WindowSystemMenuHint| Qt.X11BypassWindowManagerHint | Qt.FramelessWindowHint| Qt.WindowTransparentForInput| Qt.TransparentForMouseEvents|Qt.OnScreenDisplay
		Rectangle {
			id:rect
			anchors.fill:parent
			border.color:frame.borderColor
			border.width: frame.borderWidth
			visible:true
			color:frame.frameColor
		}

		function moveFrame(x,y,w,h){
		   frame.y=y-frame.borderWidth;
		   frame.x=x-frame.borderWidth;
		   frame.width=w+frame.borderWidth*2;
		   frame.height=h+frame.borderWidth*2;
		   console.log("PARMS");
		   console.log(frame.borderColor);
		   console.log(frame.frameOpacity);
		   console.log(frame.frameColor);
		   console.log("MOVING");



		} // Window
    Component.onCompleted: {
        frame.show();

    }

    function updateConfig(){
		console.log("**** UPDATE ****")
    }

}
