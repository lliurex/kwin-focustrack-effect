/*
 *   Adapted by juanma1980 Copyright © 2024
 *   Original work:
 *
 *   Copyright © 2015 Robert Metsäranta <therealestrob@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; see the file COPYING.  if not, write to
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *   Boston, MA 02110-1301, USA.
 */

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusPendingReply>
#include <QtDBus/QDBusMetaType>
#include <KX11Extras>
#include <QJsonDocument>
#include <KSharedConfig>
#include <KConfigGroup>

#if QT_VERSION_MAJOR >= 6
	#include <opengl/glutils.h>
	#include <effect/effecthandler.h>
	#include <core/output.h>
	#include <core/renderviewport.h>
#else
	#include <kwinglutils.h>
#endif
#include "FocusTrackEffect.h"
#include "FocusTrackConfig.h"
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QString>
#include <QColor>

FocusTrackEffect::FocusTrackEffect()
	: KWin::OffscreenEffect()
	{
		reconfigure(ReconfigureAll);
		if (auto connection = QDBusConnection::sessionBus();
			!connection.isConnected()) {
			qWarning("FocusTrack: Cannot connect to the D-Bus session bus.\n");
		} else {
			QDBusConnection bus = QDBusConnection::sessionBus();

			QDBusInterface *interface = new QDBusInterface(
									"net.lliurex.accessibility",		 // service name
									"/net/lliurex/accessibility",		   // object path
									"net.lliurex.accessibility",	   // interface name
									bus,
									this); 
			QDBusPendingCall pendingCall = interface->asyncCall("trackFocus");
	   		bool connectionState = bus.connect(
	   										"net.lliurex.accessibility",		 // service name
											"/net/lliurex/accessibility",		   // object path
											"net.lliurex.accessibility",	   // interface name
											"focusChanged",				// signal name
											this, SLOT(handleDBusSignal(QString))
											);
			qInfo() << "FocusTrackEffect: Connected to focusChanged: " <<connectionState;
		}
		if(m_shaderManager.IsValid()) {
        	//for (const auto& win: KWin::effects->stackingOrder())
            //	windowAdded(win);
        	connect(KWin::effects, &KWin::EffectsHandler::windowAdded, this, &FocusTrackEffect::windowAdded);
            connect(KWin::effects, &KWin::EffectsHandler::windowDeleted, this, &FocusTrackEffect::windowRemoved);
#if QT_VERSION_MAJOR < 6
			qInfo() << "FocusTrackEffect: Connecting events...";
			connect(KWin::effects, &KWin::EffectsHandler::windowFinishUserMovedResized, this, &FocusTrackEffect::getCurrentFocusCoordsAsync);
			connect(KWin::effects, &KWin::EffectsHandler::windowMaximizedStateChanged, this, &FocusTrackEffect::getCurrentFocusCoordsAsync);
			connect(KWin::effects, &KWin::EffectsHandler::windowHidden, this, &FocusTrackEffect::getCurrentFocusCoordsAsync);
			//connect(KWin::effects, &KWin::EffectsHandler::windowAdded, this, &FocusTrackEffect::getCurrentFocusCoordsAsync);

#endif
		}
		this->loadFrameQml();
		this->getCurrentFocusCoordsAsync();
	}

KConfigGroup FocusTrackEffect::readConfig()
{
		KSharedConfigPtr config=KSharedConfig::openConfig("kwinrc");
		KConfigGroup group(config,"Effect-ًFocusTrack");
		const auto gL=group.keyList();
		return(group);
}

bool FocusTrackEffect::loadFrameQml()
{
	engine = new QQmlApplicationEngine();
	connect(engine, &QQmlApplicationEngine::objectCreated,
			this, [this](QObject *obj, const QUrl &objUrl) {
		if (!obj && objUrl == QUrl(QStringLiteral("/usr/share/kwin/effects/kwin4_effect_focustrack/qml/frame.qml"))) {
			qFatal("Error loading QML file.");
		} else {
			qDebug() << "QML file loaded successfully.";
		}
	}, Qt::QueuedConnection);
	engine->load(QUrl(QStringLiteral("/usr/share/kwin/effects/kwin4_effect_focustrack/qml/frame.qml"))); 
	// Check if the root object is valid and create a window from it
	if (!engine->rootObjects().isEmpty()) {
		window = qobject_cast<QQuickWindow *>(engine->rootObjects().first());
		if (window) {
			int borderWidth=1;
			
			qDebug() << "Window created successfully.";
			QColor color=QColor(25,0,255,0.1);
			KConfigGroup group=this->readConfig();
			QString width=group.readEntry("borderWidth","5");
			QString opacity=group.readEntry("Opacity","0");
			QColor borderColor=group.readEntry("borderColor",color);
			QColor frameColor=group.readEntry("frameColor",borderColor);
			float alpha=opacity.toFloat();
			if (alpha>0)
				alpha=alpha-0.01;
			if (alpha>99)
				alpha=99;

			frameColor.setAlphaF(alpha/100);
			borderColor.setAlphaF(0.9);
			window->setProperty("borderWidth",width);
			window->setProperty("frameOpacity",opacity);
			window->setProperty("borderColor",borderColor.name(borderColor.HexArgb));
			window->setProperty("frameColor",frameColor.name(frameColor.HexArgb));
			qInfo() << "FocusTrack: Config width:" << width;
			qInfo() << "FocusTrack: Config opacity:" << opacity;
			qInfo() << "FocusTrack: Config fColor:" << frameColor.name(frameColor.HexArgb);
			qInfo() << "FocusTrack: Config bColor:" << borderColor.name(borderColor.HexArgb);
			window->show();

		} else {
			qDebug() << "Failed to create window.";
		}
	} else {
		qDebug() << "No root objects found.";
	}
	return(engine->rootObjects().isEmpty());
}

FocusTrackEffect::~FocusTrackEffect(){// = default;
	m_shaderManager.Unbind();
	window->deleteLater();
	}

void FocusTrackEffect::getCurrentFocusCoordsAsync()
{
	QDBusInterface *interface = new QDBusInterface(
									"net.lliurex.accessibility",		 // service name
									"/net/lliurex/accessibility",		   // object path
									"net.lliurex.accessibility",	   // interface name
									QDBusConnection::sessionBus(),
									this); 
	qInfo() << "FocusTrackEffect: Interface focusChanged";
	// Call the method asynchronously
	qDBusRegisterMetaType<QMap<QString, int16_t>>();

	QDBusPendingCall pendingCall = interface->asyncCall("getCurrentFocusCoords");
	// Handle the response
	QDBusPendingCallWatcher *callWatcher = new QDBusPendingCallWatcher(pendingCall, this);
	connect(callWatcher, &QDBusPendingCallWatcher::finished, this, &FocusTrackEffect::handleDBusCurrentCoordsAsync);
}

void FocusTrackEffect::handleDBusCurrentCoordsAsync(QDBusPendingCallWatcher *call)
{ 
	QDBusPendingReply<QMap<QString,int16_t>> reply = *call;

	if (reply.isError()) {
		qDebug() << "Error:" << reply.error().message();
	} else {
		// Process the reply
		QMap result = reply.value();
		qInfo() << "FocusTrack: Current coords:" << result;
	}
}

void FocusTrackEffect::handleDBusSignal(const QString &coords)
{
	QByteArray strCoords=coords.toUtf8();
	strCoords.replace("\'","\\'");
	this->moveFrame(strCoords);
}

void FocusTrackEffect::moveFrame(const QByteArray &coords)
{
	qInfo() << "FocusTrackEffect: Focus coords: " << coords;
	QJsonParseError error;
	QJsonDocument jcoords = QJsonDocument::fromJson(coords,&error);
	if (jcoords.isEmpty())
	{
		qInfo()<< "Failed parse JSON: "<<error.errorString();
	}
	QJsonObject objCoords = jcoords.object();
	int coordX=objCoords["x"].toInt();
	int coordY=objCoords["y"].toInt();
	int coordW=objCoords["w"].toInt();
	int coordH=objCoords["h"].toInt();
	qInfo()<<"Moving frame";
 	QMetaObject::invokeMethod(window, "moveFrame",
								  Q_ARG(QVariant,coordX),
								  Q_ARG(QVariant,coordY),
								  Q_ARG(QVariant,coordW),
								  Q_ARG(QVariant,coordH));
	qInfo()<<"Moving end";
}

void FocusTrackEffect::windowAdded(KWin::EffectWindow *w)
{
    qInfo() << "added: " << w->windowRole() << w->windowType() << w->windowClass();
    const QSet<QString> hardExceptions {};// "plasmashell"}; //, "kscreenlocker_greet", "ksmserver", "krunner" };
    const auto name = w->windowClass().split(QChar::Space).first();
    if (hardExceptions.contains(name))
        return;
  /*  if (const auto& [w2, r] = m_managed.insert({w, false}); r) {
#if QT_VERSION_MAJOR >= 6
        connect(w, &KWin::EffectWindow::windowFrameGeometryChanged, this, &FocusTrackEffect::windowResized);
#endif
        redirect(w);
        setShader(w, m_shaderManager.GetShader().get());
        checkTiled();
    }*/
	this->getCurrentFocusCoordsAsync();
}
void FocusTrackEffect::windowRemoved(KWin::EffectWindow *w)
{
	m_managed.erase(w);
	checkTiled();
}

void FocusTrackEffect::reconfigure(const ReconfigureFlags flags)
{
	Q_UNUSED(flags)
	FocusTrackConfig::self()->read();
}

void FocusTrackEffect::prePaintWindow(KWin::EffectWindow *w, KWin::WindowPrePaintData &data, std::chrono::milliseconds time)
{
	if (!hasEffect(w))
	{
		Effect::prePaintWindow(w, data, time);
		return;
	}

	const auto size = 1;

#if QT_VERSION_MAJOR >= 6
	const auto geo = w->frameGeometry() * w->screen()->scale();
	data.setTranslucent();
#else
	const auto geo = w->frameGeometry() * KWin::effects->renderTargetScale();
	data.setTranslucent();
#endif
	QRegion reg {};
	reg += QRect(geo.x(), geo.y(), size, size);
	reg += QRect(geo.x()+geo.width()-size, geo.y(), size, size);
	reg += QRect(geo.x(), geo.y()+geo.height()-size, size, size);
	reg += QRect(geo.x()+geo.width()-size, geo.y()+geo.height()-size, size, size);
	data.opaque -= reg;
	data.paint += reg;

	OffscreenEffect::prePaintWindow(w, data, time);
}

bool FocusTrackEffect::supported()
{
	qInfo()<<"focusTrack supported: "<<KWin::effects->isOpenGLCompositing();
	return KWin::effects->isOpenGLCompositing();
}

#if QT_VERSION_MAJOR >= 6
void FocusTrackEffect::drawWindow(const KWin::RenderTarget &renderTarget, const KWin::RenderViewport &viewport,
									KWin::EffectWindow *w, int mask, const QRegion &region,
									KWin::WindowPaintData &data) {
#else
void FocusTrackEffect::drawWindow(KWin::EffectWindow *w, int mask, const QRegion &region,
									KWin::WindowPaintData &data) {
#endif
	if (!hasEffect(w))
	{
		unredirect(w);
#if QT_VERSION_MAJOR >= 6
		OffscreenEffect::drawWindow(renderTarget, viewport, w, mask, region, data);
#else
		OffscreenEffect::drawWindow(w, mask, region, data);
#endif
		return;
	}

	redirect(w);
	setShader(w, m_shaderManager.GetShader().get());
	m_shaderManager.Bind();
	glActiveTexture(GL_TEXTURE0);

#if QT_VERSION_MAJOR >= 6
	OffscreenEffect::drawWindow(renderTarget, viewport, w, mask, region, data);
#else
	OffscreenEffect::drawWindow(w, mask, region, data);
#endif
	m_shaderManager.Unbind();
}

bool FocusTrackEffect::hasEffect(const KWin::EffectWindow *w) const {
	const auto name = w->windowClass().split(QChar::Space).first();
	return m_shaderManager.IsValid()
		   && m_managed.contains(w);
		   //&& (w->isNormalWindow() || w->isDialog());
}

QString FocusTrackEffect::get_window_titles() const {
	QStringList response;
	for (const auto& [win, tiled]: m_managed) {
		const auto name = win->windowClass().split(QChar::Space).first();
		if (!response.contains(name))
			response.push_back(name);
	}
	return response.join("\n");
}

template<bool vertical>
bool FocusTrackEffect::checkTiled(double window_start, const double& screen_end, double gap) {
	if (window_start == screen_end) {
		return true;	// Found the last chain of tiles
	} else if (window_start > screen_end) {
		return false;
	}

	const bool firstGap = (gap == -1);

	bool r = false;
	for (auto& [w, tiled]: m_managed) {

		if (firstGap) {
			gap = std::get<vertical>(std::make_pair(w->x(), w->y())) - window_start;
			if(gap > 40)		// There is no way that a window is tiled and has such a big gap.
				continue;
			window_start += gap;
		}

		if (std::get<vertical>(std::make_pair(w->x(), w->y())) == window_start) {
			if (std::get<vertical>(std::make_pair(w->width(), w->height())) + gap > 0) {
				if (checkTiled<vertical>(window_start + std::get<vertical>(std::make_pair(w->width(), w->height())) + gap, screen_end, gap)) {
					tiled = true;   // Mark every tile as you go back to the first.
					r = true;
				}
			}
		}

		if(firstGap) {
			window_start -= gap;	// Revert changes.
		}
	}
	return r;
}

void FocusTrackEffect::checkTiled() {
	for (auto& [w, tiled]: m_managed) {	 // Delete tile memory.
		tiled = false;
	}

	for (const auto& screen: KWin::effects->screens()) {		// Per every screen
		const auto& geometry = screen->geometry();
		checkTiled<false>(geometry.x(), geometry.x() + geometry.width()); // Check horizontally
		checkTiled<true>(geometry.y(), geometry.y() + geometry.height()); // Check vertically
	}
	

}

