#ifndef GAME3_H
#define GAME3_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QLineEdit>
#include <Qstring>
#include "ClickableLabel.h"


class Game3 : public QWidget
{
    Q_OBJECT
    // UserAccount *userAccount;

public:
    explicit Game3(int& balance, QWidget *parent = nullptr);
    ~Game3();
    // Game3(UserAccount *account, QWidget *parent = nullptr);

    int getBalance() { return balance_game3; }

    void showAllButtons();
    void hideAllButtons();

private:
    int& balance;

    void paintEvent(QPaintEvent *event);
    void setupMovie(QLabel* label, QMovie* movie);
    void setupMovie2(QLabel* label, QMovie* movie);
    void shoot_Top_Left();
    void shoot_Top_Right();
    void shoot_Down_Left();
    void shoot_Down_Right();
    void determineWinner(int userChoice);
    void hideButtonTopLeft();
    void Goal_still();
    void gameOver();
    void resetGameState();
    void updateBalanceDisplay();
    void InvalidBet();
    void chooseGoalkeeper(int input);
    void chooseGoalkeeperEasy();
    void chooseGoalkeeperHard();
    void setHardMode();
    void setGoalkeeperModeButtonsEnabled(bool enabled);
    void goal_goal_goal();
    void startMovie(QLabel* label, const QString& moviePath);


    QMovie *football_down_left;
    QMovie *football_top_left;
    QMovie *football_down_right;
    QMovie *football_still;
    QMovie *football_top_right;

    QMovie *goalkeeper_top_right;
    QMovie *goalkeeper_bottom_right;
    QMovie *goalkeeper_top_left;
    QMovie *goalkeeper_bottom_left;
    QMovie *goalkeeper_still;

    QMovie *goalkeeper_top_left_hard;
    QMovie *goalkeeper_top_right_hard;
    QMovie *goalkeeper_bottom_right_hard;
    QMovie *goalkeeper_bottom_left_hard;
    QMovie *goalkeeper_still_hard;

    QMovie *goalkeeper_top_left_hard_win;
    QMovie *goalkeeper_top_right_hard_win;
    QMovie *goalkeeper_bottom_right_hard_win;
    QMovie *goalkeeper_bottom_left_hard_win;

    QMovie *goalkeeper_top_left_win;
    QMovie *goalkeeper_top_right_win;
    QMovie *goalkeeper_bottom_right_win;
    QMovie *goalkeeper_bottom_left_win;

    QMovie *goal_goal;

    ClickableLabel *buttonShootTopLeft;
    ClickableLabel *buttonShootTopRight;
    ClickableLabel *buttonShootLeft;
    ClickableLabel *buttonShootRight;


    QMovie *target_1;

    QLabel *football_label;
    QLabel *goalkeeper_label;
    QLabel *betLabel;
    QLabel *goal_goal_Label;

    double bet_Label_easy;
    int bet_Label_hard;

    std::vector<int> goal_direction;
    int winningDirection;
    int win_round;
    int remain_round;
    QString resultMassage;

    bool check;

    QLineEdit *betAmountLineEdit;
    QLabel *remainsLabel;
    QLabel *win_round_Label;
    QLabel *balanceLabel;

    int balance_game3;
    bool goalkeeper_check;

    QPushButton *goalkeeper_hard_button;
    QPushButton *goalkeeper_easy_button;

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

    int bet_amount;

    QLabel *bet_label;
    bool check_invalid;
    void setupMovie_win(QLabel* label, QMovie* movie);
    bool check_game;

    double bet_select;

    bool check_balance;
    bool check_win;

    ClickableLabel *goal_easy_button_label;
    QMovie *goal_easy_button;

    ClickableLabel *goal_hard_button_label;
    QMovie *goal_hard_button;

    QMovie *popup_win;
    QMovie *popup_lose;

    QLabel *popup_win_label;
    QLabel *popup_lose_label;
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




};

#endif // GAME3_H

