#pragma once

#include <kcmodule.h>

namespace Ui {
    class Form;
}

class FocusTrackKCM final: public KCModule
{
    Q_OBJECT
public:
#if (QT_VERSION_MAJOR >= 6)
    explicit FocusTrackKCM(QObject* parent, const KPluginMetaData& args);
#else
    explicit FocusTrackKCM(QWidget* parent = nullptr, const QVariantList& args = QVariantList());
#endif

public Q_SLOTS:
    void defaults() override;
    void load() override;
    void save() override;
//    void update_windows() const;

private:
    std::shared_ptr<Ui::Form> ui;

#if (QT_VERSION_MAJOR >= 6)
    const QPalette& palette() { return widget()->palette(); };
#endif
};
