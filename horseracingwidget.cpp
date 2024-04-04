// HorseRacingWidget.cpp
#include "HorseRacingWidget.h"
#include <QPainter>

HorseRacingWidget::HorseRacingWidget(QWidget *parent) : QWidget(parent) {
}

void HorseRacingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap backgroundImage(":/horsegame/Resource_Files/horse/horsestadium.png");
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QWidget::paintEvent(event);
}
