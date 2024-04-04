#ifndef HORSEBETWINDOW_H
#define HORSEBETWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "horseracing.h"
#include "horse.h"
#include "ClickableLabel.h"
#include <QLineEdit>

class HorseBetWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HorseBetWindow(int& balance, HorseRacing* horseRacing, QWidget *parent = nullptr);

    int getBalance() { return balance_game2; }

    QString HorseInfo();
    void betOnHorse1();
    void betOnHorse2();
    void betOnHorse3();
    void betOnHorse4();
    void betOnHorse5();

    void onRaceFinished(int winningHorseIndex);

    void startRace();

private:
    QVBoxLayout *mainLayout;
    HorseRacing* m_horseRacing;
    QLabel *balanceLabel;
    QLabel *bet_label;
    QLabel *asd;
    QLabel *add;
    QLabel *balanceLabel_fake;
    int userHorseNum;
    double userBetRate;


    int balance_game2;

    int betAmount;
    QLineEdit *betAmountInput;

    int bet_amount;
    QMovie *chip_1_gif;
    QMovie *chip_5_gif;
    QMovie *chip_10_gif;
    QMovie *chip_25_gif;
    QMovie *chip_50_gif;
    QMovie *chip_reject_gif;

    ClickableLabel *chip_1;
    ClickableLabel *chip_5;
    ClickableLabel *chip_10;
    ClickableLabel *chip_25;
    ClickableLabel *chip_50;
    ClickableLabel *chip_reject;

    void chip_1_add();
    void chip_5_add();
    void chip_10_add();
    void chip_25_add();
    void chip_50_add();
    void chip_reject_add();

    QMovie *popup_win;
    QMovie *popup_lose;

    QLabel *popup_win_label;
    QLabel *popup_lose_label;

    QMovie *purhorsewin;
    QMovie *redhorsewin;
    QMovie *yellowhorsewin;
    QMovie *bluehorsewin;
    QMovie *greenhorsewin;

    QMovie *purhorselose;
    QMovie *redhorselose;
    QMovie *yellowhorselose;
    QMovie *bluehorselose;
    QMovie *greenhorselose;

    std::vector<QMovie*> allhorsewin;
    std::vector<QMovie*> allhorselose;

    void showInstructions();

    ClickableLabel *instuction_botton;
    ClickableLabel *quitButton;
    QMovie *instuction_botton_gif;
    QMovie *quitButton_gif;


signals:
    void balanceChanged(int newBalance);

    void gameClosed(int newBalance);

protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};



#endif // HORSEBETWINDOW_H
