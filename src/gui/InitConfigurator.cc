
#include "gui/InitConfigurator.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QString>
#include <QSettings>
#include <QWidget>
#include "gui/Settings.h"

#include <string>

void InitConfigurator::initUpdateCheckBox(const BlockSignals<QCheckBox *>& checkBox, const Settings::SettingsEntryBool& entry)
{
  checkBox->setChecked(entry.value());
}

void InitConfigurator::initIntSpinBox(const BlockSignals<QSpinBox *>& spinBox, const Settings::SettingsEntryInt& entry)
{
  spinBox->setMinimum(entry.minimum());
  spinBox->setMaximum(entry.maximum());
}

void InitConfigurator::updateIntSpinBox(const BlockSignals<QSpinBox *>& spinBox, const Settings::SettingsEntryInt& entry)
{
  spinBox->setValue(entry.value());
}

void InitConfigurator::initUpdateDoubleSpinBox(QDoubleSpinBox *spinBox, const Settings::SettingsEntryDouble& entry)
{
  spinBox->blockSignals(true);
  spinBox->setSingleStep(entry.step());
  spinBox->setMinimum(entry.minimum());
  spinBox->setMaximum(entry.maximum());
  spinBox->setValue(entry.value());
  spinBox->blockSignals(false);
}

void InitConfigurator::initComboBox(QComboBox *comboBox, const Settings::SettingsEntryEnum& entry)
{
  comboBox->clear();
  for (const auto& item : entry.items()) {
    comboBox->addItem(QString::fromStdString(item.description), QString::fromStdString(item.value));
  }
  updateComboBox(comboBox, entry);
}

void InitConfigurator::updateComboBox(const BlockSignals<QComboBox *>& comboBox, const Settings::SettingsEntryEnum& entry)
{
  comboBox->setCurrentIndex(entry.index());
}

void InitConfigurator::updateComboBox(const BlockSignals<QComboBox *>& comboBox, const std::string& value)
{
  int index = comboBox->findData(QString::fromStdString(value));
  if (index >= 0) {
    comboBox->setCurrentIndex(index);
  } else {
    comboBox->setCurrentIndex(0);
  }
}

void InitConfigurator::initButtonGroup(const BlockSignals<QButtonGroup *>& buttonGroup, const Settings::SettingsEntryEnum& entry)
{
  for (const auto button : buttonGroup->buttons()) {
    const auto settingsValue = button->property(Settings::PROPERTY_NAME).toString().toStdString();
    if (settingsValue == entry.value()) {
      button->setChecked(true);
    }
  }
}

void InitConfigurator::applyButtonGroup(const BlockSignals<QButtonGroup *>& buttonGroup, Settings::SettingsEntryEnum& entry)
{
  const auto button = buttonGroup->checkedButton();
  if (button) {
      const auto settingsValue = button->property(Settings::PROPERTY_NAME).toString().toStdString();
      entry.setValue(settingsValue);
  }
}
