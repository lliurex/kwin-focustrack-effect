#include "FocusTrackKCM.h"
#include "ui_FocusTrackKCM.h"
#include "kwineffects_interface.h"
#include "FocusTrackConfig.h"
#include <QDialog>

#if (QT_VERSION_MAJOR >= 6)
FocusTrackKCM::FocusTrackKCM(QObject* parent, const KPluginMetaData& args)
    : KCModule(parent, args)
    , ui(new Ui::Form)
{
    ui->setupUi(widget());
    addConfig(FocusTrackConfig::self(), widget());
#else
FocusTrackKCM::FocusTrackKCM(QWidget* parent, const QVariantList& args)
    : KCModule(parent, args)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    addConfig(FocusTrackConfig::self(), this);
#endif
}

void
FocusTrackKCM::save()
{

    FocusTrackConfig::self()->save();
    KCModule::save();

    const auto dbusName = QStringLiteral("kwin4_effect_focustrack");
    OrgKdeKwinEffectsInterface interface(QStringLiteral("org.kde.KWin"),
                                         QStringLiteral("/Effects"),
                                         QDBusConnection::sessionBus());
    interface.reconfigureEffect(dbusName);

    // It was expected that the Apply button would repaint the whole screen, but it doesn't.
    // Even calling KWin::effects->addRepaintFull(); didn't do the trick.
    // Maybe it is a bug on the KWin side. Need to check and delete these lines later.
    interface.unloadEffect(dbusName);
    interface.loadEffect(dbusName);
}

void FocusTrackKCM::load() {
    KCModule::load();
    FocusTrackConfig::self()->load();
   // ui->InclusionList->addItems(FocusTrackConfig::inclusions());
    //ui->ExclusionList->addItems(FocusTrackConfig::exclusions());
}

void FocusTrackKCM::defaults() {
    KCModule::defaults();
    FocusTrackConfig::self()->setDefaults();
}
