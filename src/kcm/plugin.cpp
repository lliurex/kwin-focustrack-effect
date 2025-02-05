#include "FocusTrackKCM.h"

// KF5
#include <KPluginFactory>

#if (QT_VERSION_MAJOR >= 248)
K_PLUGIN_CLASS(FocusTrackKCM)
#else
K_PLUGIN_FACTORY_WITH_JSON(FocusTrackConfigFactory,
                           "metadata.json",
                           registerPlugin<FocusTrackKCM>();)
#endif

#include "plugin.moc"
