#ifndef HORSERACING_H
#define HORSERACING_H

#include <vector>
#include "horse.h"
#include <QObject>

class HorseRacing : public QObject{
    Q_OBJECT
public:
    explicit HorseRacing(QObject *parent = nullptr);
    virtual ~HorseRacing();

    void SimulateRace();
    void UpdateNewSpeed();
    void RunRace();
    bool isRaceOver();

    int getNumHorse();
    int getFinishLine();
    std::vector<Horse> getHorses();

    Horse FindFastestHorse();
    void CalculateWinningOdds();
    void CalculateBettingOdds();
    std::pair<double, double> CalculateOdds(double winPercentage);
    std::vector<std::pair<double, double>> getBettingOdds();
    QString HorseInfo(int index);

    std::vector<Horse> horses;
    void paintEvent(QPaintEvent *event);



private:
    static const int NUM_HORSES;
    static const int FinishLinePosition;
    bool raceOver;

    static std::vector<int> finishPlace;
    static std::vector<double> WinningOdds;
    static std::vector<std::pair<double, double>> BettingOdds;


signals:
    void raceFinished(int winningHorseIndex);

};

#endif // HORSE_RACING_H
