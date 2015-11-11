#include <QFileDialog>
#include "capturewidget.h"



CaptureWidget::CaptureWidget(QWidget* parent) :
    QWidget(parent), dir(QCoreApplication::applicationDirPath())
{
    ui.setupUi(this);
}

void CaptureWidget::updateWidget(bool value) {
    ui.enabledCheckBox->setChecked(value);
    ui.sourceType->setEnabled(!value);
}

void CaptureWidget::updateWidgetVideoBar(double frameCur, double frameTotal) {
    ui.videoProgress->setMaximum(frameTotal);
    ui.videoProgress->setValue(frameCur);
    ui.labelFrames->setText("Current frame:  " + QString::number(frameCur) +
                                 " of " + QString::number(frameTotal));
}



void CaptureWidget::on_enabledCheckBox_toggled(bool checked)
{
    ui.sourceType->setEnabled(!checked);
    emit sigEnabled(checked);
}


//------------------

void CaptureWidget::on_refreshPeriodMs_editingFinished()
{
    emit sigRefreshPeriodMsChanged(ui.refreshPeriodMs->value());
}

void CaptureWidget::on_sourceType_currentChanged(int index)
{
    emit sigSourceTypeChanged(index); // 0 - camera, 1 - image, 2 - video, 3 - fill white
}

void CaptureWidget::on_cameraNumberSpinBox_editingFinished()
{
    emit sigCameraNumberChanged(ui.cameraNumberSpinBox->value());
}

void CaptureWidget::on_file1Button_clicked()
{
    QString imageFilename = QFileDialog::getOpenFileName(nullptr,
                                            "Open first image file",
                                            dir,
                                            "All files (*.*)");
    dir = imageFilename;
    if (imageFilename.isEmpty()) {
        return;
    }

    ui.file1Name->setText(imageFilename);
    emit sigFile1NameChanged(imageFilename);
}

void CaptureWidget::on_file2Button_clicked()
{
    QString imageFilename = QFileDialog::getOpenFileName(nullptr,
                                            "Open second image file",
                                            dir,
                                            "All files (*.*)");
    dir = imageFilename;
    if (imageFilename.isEmpty()) {
        return;
    }

    ui.file2Name->setText(imageFilename);
    emit sigFile2NameChanged(imageFilename);
}


void CaptureWidget::on_file1Name_editingFinished()
{
    emit sigFile1NameChanged(ui.file1Name->text());
}

void CaptureWidget::on_file2Name_editingFinished()
{
    emit sigFile2NameChanged(ui.file2Name->text());
}

void CaptureWidget::on_videoFileButton_clicked()
{
    QString videoFilename = QFileDialog::getOpenFileName(nullptr,
                                            "Open video file",
                                            QCoreApplication::applicationDirPath(),
                                            "All files (*.*)");
    if (videoFilename.isEmpty()) {
        return;
    }

    ui.videoFileName->setText(videoFilename);
    emit sigVideoFileNameChanged(videoFilename);
}

void CaptureWidget::on_videoFileName_editingFinished()
{
    emit sigVideoFileNameChanged(ui.videoFileName->text());
}

void CaptureWidget::on_frameWidthSpinBox_editingFinished()
{
    emit sigEmptyFrameWidthChanged(ui.frameWidthSpinBox->value());
}

void CaptureWidget::on_frameHeightSpinBox_editingFinished()
{
    emit sigEmptyFrameHeightChanged(ui.frameHeightSpinBox->value());
}
