add_subdirectory(kcm)

set(effect_SRCS
    FocusTrackEffect.h
    FocusTrackEffect.cpp
    FocusTrackShader.h
    FocusTrackShader.cpp
    plugin.cpp
)

find_package(Qt5  REQUIRED COMPONENTS Quick)
kconfig_add_kcfg_files(effect_SRCS FocusTrackConfig.kcfgc)
kcoreaddons_add_plugin(kwin4_effect_focustrack SOURCES ${effect_SRCS} INSTALL_NAMESPACE "kwin/effects/plugins/")

target_link_libraries(kwin4_effect_focustrack
    Qt${QT_MAJOR_VERSION}::DBus
    KF${QT_MAJOR_VERSION}::ConfigGui
    Qt${QT_MAJOR_VERSION}::Quick
)
if(${QT_MAJOR_VERSION} EQUAL 6)
    target_link_libraries(kwin4_effect_focustrack
            KWin::kwin
            Qt${QT_MAJOR_VERSION}::CorePrivate
    )
else()
    target_link_libraries(kwin4_effect_focustrack
            KWinEffects::kwineffects
            KWinEffects::kwinglutils
    )
endif()
install(DIRECTORY shaders DESTINATION ${KDE_INSTALL_DATADIR}/kwin)
set(KWIN_EFFECTS_INSTALL_DIR "/usr/share/kwin/effects")  
install(DIRECTORY qml DESTINATION ${KWIN_EFFECTS_INSTALL_DIR}/kwin4_effect_focustrack)
