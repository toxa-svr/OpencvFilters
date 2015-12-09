#pragma once

#include "ui_dummywidget.h"

class DummyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DummyWidget(QWidget* parent = nullptr);

private:
    Ui::DummyWidget ui;
};
