#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#include "ui_capturewidget.h"

class CaptureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureWidget(QWidget* parent = nullptr);

signals:
    void sigEnabled(bool);
    void sigRefreshPeriodMsChanged(int);
    void sigSourceTypeChanged(int);  // 0 - camera, 1 - image, 2 - video, 3 - fill white
    void sigCameraNumberChanged(int);
    void sigFile1NameChanged(QString);
    void sigFile2NameChanged(QString);
    void sigVideoFileNameChanged(QString);
    void sigEmptyFrameWidthChanged(int);
    void sigEmptyFrameHeightChanged(int);

public slots:
    void updateWidget(bool value);
    void updateWidgetVideoBar(double frameCur, double frameTotal);

private slots:
    void on_enabledCheckBox_toggled(bool checked);
    // source type
    void on_sourceType_currentChanged(int index);
    // source form camera
    void on_cameraNumberSpinBox_editingFinished();
    // source form images
    void on_file1Button_clicked();
    void on_file2Button_clicked();
    void on_file1Name_editingFinished();
    void on_file2Name_editingFinished();
    void on_refreshPeriodMs_editingFinished();
    // source form video file
    void on_videoFileButton_clicked();
    void on_videoFileName_editingFinished();
    // source empty frame
    void on_frameWidthSpinBox_editingFinished();
    void on_frameHeightSpinBox_editingFinished();

private:
    Ui::CaptureWidget ui;
    QString dir;
};

#endif // CAPTUREWIDGET_H
