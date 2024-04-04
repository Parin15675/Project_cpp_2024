#include "horseracing.h"
#include "horse.h"
#include "HorseRacingWidget.h"
#include <cstdlib>
#include <ctime>
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <QVBoxLayout>
#include <QThread>
#include <QDebug>
#include <QPixmap>
#include <QPainter>



const int HorseRacing::NUM_HORSES = 5;
const int HorseRacing::FinishLinePosition = 800;
const std::vector<QString> imagePaths = {":/horsegame/Resource_Files/horse/purplehorse.gif",":/horsegame/Resource_Files/horse/redhorse.gif",":/horsegame/Resource_Files/horse/yellohorse.gif",":/horsegame/Resource_Files/horse/bluehorse.gif",":/horsegame/Resource_Files/horse/greenhorse.gif"};
const std::vector<QString> hatimagePaths = {"C:/Users/Dell/Code/C++/ProjectC++/hat.jpg","C:/Users/Dell/Code/C++/ProjectC++/hat.jpg","C:/Users/Dell/Code/C++/ProjectC++/hat.jpg","C:/Users/Dell/Code/C++/ProjectC++/hat.jpg","C:/Users/Dell/Code/C++/ProjectC++/hat.jpg"};

std::vector<int> HorseRacing::finishPlace;
std::vector<double> HorseRacing::WinningOdds;
std::vector<std::pair<double, double>> HorseRacing::BettingOdds;


HorseRacing::HorseRacing(QObject *parent) : QObject(parent)  {
    raceOver = false;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < NUM_HORSES; ++i) {
        QString imagePath = QString(imagePaths[i]).arg(i+1); // Provide the correct path to the horse image
        QString hatimagePath = QString(hatimagePaths[i]).arg(i+1);
        horses.push_back(Horse(rand() % 15 + 5, imagePath, hatimagePath)); // Create horse with image path
    }

}

HorseRacing::~HorseRacing() {
}


void HorseRacing::SimulateRace() {
    for (int i = 0; i < NUM_HORSES; ++i) {
        if (horses[i].GetFinished()){
            continue;
        }
        else{
            horses[i].UpdatePosition();
        }
    }
}

void HorseRacing::UpdateNewSpeed() {
    for (int i = 0; i < NUM_HORSES; ++i) {
        int chance = rand() % 11 + 1;
        // Generate a new random speed for each horse
        if(chance == 10){
            horses[i].UpdateTopSpeed();
        }
        horses[i].UpdateSpeed();
    }
}

void HorseRacing::RunRace() {
    // Create an instance of the HorseRacingWidget
    HorseRacingWidget* raceWidget = new HorseRacingWidget();
    raceWidget->setWindowTitle("Horse Race");

    QVBoxLayout* horseracelayout = new QVBoxLayout(raceWidget);
    raceWidget->setLayout(horseracelayout);
    raceWidget->resize(1000, 589);

    // Create QLabel objects for each horse and add them to the HorseRacingWidget's layout
    for (int i = 0; i < NUM_HORSES; ++i) {
        horses[i].SetLabel();
        horseracelayout->addWidget(horses[i].GetLabel());
    }

    // Show the HorseRacingWidget
    raceWidget->show();


    // Start the race animation loop
    while (!raceOver) {
        SimulateRace();
        UpdateNewSpeed();

        // Update position of each horse label
        for (int i = 0; i < NUM_HORSES; ++i) {
            if (horses[i].GetPosition() >= FinishLinePosition){
                horses[i].SetFinished();
                finishPlace.push_back(i);

            }
            horses[i].GetLabel()->move(horses[i].GetPosition(), i * 100); // Adjust vertical positioning as needed
        }

        // Check if every horse has crossed the finish line
        raceOver = true;
        for (int i = 0; i < NUM_HORSES; ++i) {
            if (horses[i].GetPosition() < FinishLinePosition) {
                raceOver = false;
                break;
            }
        }

        // Add a short delay for the animation
        QCoreApplication::processEvents();
        QThread::msleep(100);
    }

    if (raceOver) {
        emit raceFinished(finishPlace.front());
        raceWidget->close();
    }
}


bool HorseRacing::isRaceOver() {
    if (raceOver){
        return true;
    }
    else{
        return false;
    }
}

int HorseRacing::getNumHorse(){
    return NUM_HORSES;
}
int HorseRacing::getFinishLine(){
    return FinishLinePosition;
}

std::vector<Horse> HorseRacing::getHorses(){
    return horses;
}

Horse HorseRacing::FindFastestHorse() {
    Horse fastestHorse = horses[0];
    int maxSpeed = fastestHorse.GetTopSpeed();

    for (int i = 0; i < NUM_HORSES; ++i) {
        if (horses[i].GetTopSpeed() > maxSpeed) {
            maxSpeed = horses[i].GetTopSpeed();
            fastestHorse = horses[i];
        }
    }

    return fastestHorse;
}



void HorseRacing::CalculateWinningOdds() {
    double totalTopSpeed = 0;

    // Calculate total top speed
    for (int i = 0; i < NUM_HORSES; ++i) {
        totalTopSpeed += horses[i].GetTopSpeed();
    }
    for (int i = 0; i < NUM_HORSES; ++i) {
        double odd;
        odd = ((horses[i].GetTopSpeed())/totalTopSpeed) * 100.00;
        qDebug() << "Winning odds for horse" << i << ":" << odd;
        WinningOdds.push_back(odd);
    }
}

std::vector<std::pair<double, double>> HorseRacing::getBettingOdds(){
    return BettingOdds;
}


void HorseRacing::CalculateBettingOdds() {
    for (int i = 0; i < NUM_HORSES; ++i) {
        std::pair<double, double> betodd = CalculateOdds(WinningOdds[i]);
        qDebug() << "Betting odds for horse" << i << ":" << betodd.first << "/" << betodd.second;
        BettingOdds.push_back(betodd);
    }
}

std::pair<double, double> HorseRacing::CalculateOdds(double winPercentage) {
    double numerator = (100 / winPercentage) - 1;
    double denominator = 1.00;

    return std::make_pair(numerator, denominator);
}

QString HorseRacing::HorseInfo(int index) {
    if (index < 0 || index >= BettingOdds.size()) {
        return "Invalid index";
    }

    std::pair<double, double> odds = BettingOdds[index];

    QString info = "Top Speed: " + QString::number(horses[index].GetTopSpeed()) + "\n" + "Odds: " + QString::number(odds.first, 'f', 1) + "/" + QString::number(odds.second, 'f', 1);

    return info;
}


