#include "FocusTrackEffect.h"

KWIN_EFFECT_FACTORY_SUPPORTED_ENABLED(  FocusTrackEffect,
                                        "metadata.json",
                                        return FocusTrackEffect::supported();,
                                        return FocusTrackEffect::enabledByDefault();)

#include "plugin.moc"
