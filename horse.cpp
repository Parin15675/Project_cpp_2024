#include "horse.h"
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <QVBoxLayout>
#include <QThread>
#include <QDebug>
#include <QPainter>
#include <QMovie>
#include <QFile>
#include <iostream>

Horse::Horse(int topSpeed, const QString& imagePath, const QString& hatPath)
    : position(0), speed(0), topSpeed(topSpeed), finished(false), haveHat(true), hatimagePath(hatPath),imagePath(imagePath), label(nullptr), movie(nullptr) {
}

Horse::~Horse() {
    delete label;
    delete movie;
}

void Horse::UpdatePosition() {
    position += speed;
}

void Horse::UpdateTopSpeed(){
    topSpeed = rand() % 20 + 2;
}

void Horse::UpdateSpeed() {
    speed = rand() % topSpeed + 2;
}

int Horse::GetPosition() const {
    return position;
}

void Horse::SetPosition(int x) {
    position = x;
}

int Horse::GetTopSpeed(){
    return topSpeed;
}

QString Horse::GetImagePath() const {
    return imagePath;
}

QString Horse::GetHatImagePath() const{
    return hatimagePath;
}

void Horse::RemoveHat(){
    haveHat = false;
}


void Horse::SetLabel() {
    QLabel* horseLabel = new QLabel();

    movie = new QMovie(imagePath);
    movie->setScaledSize(QSize(170, 120));
    horseLabel->setMovie(movie);
    movie->start();

    label = horseLabel;
}



QLabel* Horse::GetLabel() const {
    return label;
}

bool Horse::GetFinished(){
    return finished;
}

void Horse::SetFinished(){
    finished = true;
}
