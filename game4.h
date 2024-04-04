#ifndef GAME4_H
#define GAME4_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QTimer>
#include <QRandomGenerator>
#include "ClickableLabel.h"

class Game4 : public QWidget {
    Q_OBJECT

public:
    explicit Game4(int& balance, QWidget *parent = nullptr);
    ~Game4();
    // Game3(UserAccount *account, QWidget *parent = nullptr);

    int getBalance() { return balance_game4; }



private slots:
    void startGame();
    void cashOut();
    void updateGame();
    void showInstructions();

private:
    QLabel *plane_label;
    QLabel *bomb_label;
    QLabel *multiplier_label;
    QLabel *balance_label;
    QLabel *bet_label;

    int balance_game4;

    QPushButton *betButton;
    QPushButton *cashoutButton;
    QMovie *plane;
    QMovie *bomb;


    QPixmap *planePixmap;
    QTimer *gameTimer;
    QLabel *cashOutLabel;

    double multiplier;
    bool gameActive;
    int balance;


    void updateMultiplierDisplay();
    void resetGame();

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

    double multiplier_new;

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

#endif // GAME4_H
