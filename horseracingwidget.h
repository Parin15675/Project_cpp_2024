// HorseRacingWidget.h
#ifndef HORSERACINGWIDGET_H
#define HORSERACINGWIDGET_H

#include <QWidget>

class HorseRacingWidget : public QWidget {
    Q_OBJECT
public:
    HorseRacingWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // HORSERACINGWIDGET_H
