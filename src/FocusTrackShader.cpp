//
// Created by matin on 20/07/22.
// Adaptded by juanma1980 27/04/24
//

#include <QFile>
#include <QWidget>

#if QT_VERSION_MAJOR >= 6
    #include <opengl/glutils.h>
#else
    #include <kwinglutils.h>
#endif
#include "FocusTrackShader.h"
#include "FocusTrackEffect.h"
#include "FocusTrackConfig.h"

FocusTrackShader::FocusTrackShader():
        m_manager(KWin::ShaderManager::instance()),
        m_widget(new QWidget)
{
    const QString fragmentshader = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kwin/shaders/FocusFrame.frag"));
    qCritical() << fragmentshader;
    QFile file(fragmentshader);
    if (!file.open(QFile::ReadOnly))
        qCritical() << "FocuTrack: no shader found at kwin/shaders/FocusFrame.frag - Exiting...";

    const QByteArray frag = file.readAll();
    auto shader = m_manager->generateShaderFromFile(KWin::ShaderTrait::MapTexture, QStringLiteral(""), fragmentshader);
    m_shader = std::move(shader);
    file.close();
    if (!m_shader->isValid())
        qCritical() << "FocusTrack: no valid shaders found! FocusTrack will not work.";

    m_shader_focusTrackFilter = m_shader->uniformLocation("borderWidth");
    qInfo() << "FocusTrack: shaders loaded. "<< m_shader->uniformLocation("borderWidth");
}

bool FocusTrackShader::IsValid() const {
    return m_shader && m_shader->isValid();
}

const std::unique_ptr<KWin::GLShader>&
FocusTrackShader::Bind() const {
	//auto filter=static_cast<int>(FocusTrackConfig::FocusTrackConfig());
	//auto correction=static_cast<bool>(FocusTrackConfig::applyFocusTrack());
	//auto borderColor=static_cast<int>(FocusTrackConfig::borderColor());
	auto borderWidth=static_cast<bool>(FocusTrackConfig::borderWidth());
	//auto focusTrackFilter=static_cast<bool>(FocusTrackConfig::focusTrackFilter());
    m_manager->pushShader(m_shader.get());
    m_shader->setUniform("focusTrackFilter",1);
    //m_shader->setUniform("applyFocusTrack",applyFocustrack);
    return m_shader;
}

void FocusTrackShader::Unbind() const {
    m_manager->popShader();
}
