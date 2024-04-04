// In horse.h
#ifndef HORSE_H
#define HORSE_H

#include <QLabel>
#include <QString>
#include <QMovie>

class Horse {
public:
    Horse(int topSpeed, const QString& imagePath, const QString& hatimagePath);
    ~Horse();

    void UpdatePosition();
    void UpdateSpeed();
    void UpdateTopSpeed();

    int GetPosition() const;
    void SetPosition(int x);

    int GetTopSpeed();

    QString GetImagePath() const;
    QString GetHatImagePath() const;
    void RemoveHat();

    void SetLabel();
    QLabel* GetLabel() const;

    bool GetFinished();
    void SetFinished();

private:
    bool haveHat;
    int position;
    int speed;
    int topSpeed;
    bool finished;
    QString imagePath;
    QString hatimagePath;
    QLabel* label;
    QMovie* movie;
};

#endif // HORSE_H
