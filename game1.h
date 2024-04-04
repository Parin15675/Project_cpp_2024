#ifndef GAME1_H
#define GAME1_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QLineEdit>
#include <random>
#include "ClickableLabel.h"


class Game1 : public QWidget
{
    Q_OBJECT
    // UserAccount *userAccount;

public:
    explicit Game1(int& balance, QWidget *parent = nullptr);
    // Game1(/*UserAccount *account,*/ QWidget *parent = nullptr);
    int getBalance() { return balance_game1; }



private slots:
    void onBetButtonClicked(int betType);
    void startGame();
    void updateBalance(int outcome);
    void showInstructions();

private:
    int& balance;

    std::mt19937 g;
    int userBet;
    QLabel *playerCard1;
    QLabel *playerCard2;
    QLabel *playerCard3;
    QLabel *bankerCard1;
    QLabel *bankerCard2;
    QLabel *bankerCard3;
    QPushButton *playerBetButton;
    QPushButton *bankerBetButton;
    QPushButton *drawBetButton;

    std::vector<QMovie*> allCards;

    QMovie *spade_A;
    QMovie *club_A;
    QMovie *diamond_A;
    QMovie *heart_A;

    QMovie *spade_2;
    QMovie *club_2;
    QMovie *diamond_2;
    QMovie *heart_2;

    QMovie *spade_3;
    QMovie *club_3;
    QMovie *diamond_3;
    QMovie *heart_3;

    QMovie *spade_4;
    QMovie *club_4;
    QMovie *diamond_4;
    QMovie *heart_4;

    QMovie *spade_5;
    QMovie *club_5;
    QMovie *diamond_5;
    QMovie *heart_5;

    QMovie *spade_6;
    QMovie *club_6;
    QMovie *diamond_6;
    QMovie *heart_6;

    QMovie *spade_7;
    QMovie *club_7;
    QMovie *diamond_7;
    QMovie *heart_7;

    QMovie *spade_8;
    QMovie *club_8;
    QMovie *diamond_8;
    QMovie *heart_8;

    QMovie *spade_9;
    QMovie *club_9;
    QMovie *diamond_9;
    QMovie *heart_9;

    QMovie *spade_10;
    QMovie *club_10;
    QMovie *diamond_10;
    QMovie *heart_10;

    QMovie *spade_K;
    QMovie *club_K;
    QMovie *diamond_K;
    QMovie *heart_K;

    QMovie *spade_J;
    QMovie *club_J;
    QMovie *diamond_J;
    QMovie *heart_J;

    QMovie *spade_Q;
    QMovie *club_Q;
    QMovie *diamond_Q;
    QMovie *heart_Q;

    void initializeCardMovies();
    void setupMovie(QLabel* label, QMovie* movie);

    void checkAllMoviesFinished();

    std::vector<QMovie*> selectedCards;
    std::vector<int> cardValue;
    void determineWinner();
    int calculateHandScore(const std::vector<QMovie*>& hand) const;
    QLabel *resultLabel;
    void resetGame();
    void populateAllCards();
    void clearCardLabel(QLabel* cardLabel);
    bool askPlayAgain();

    bool check;

    QLineEdit *betAmountLineEdit;
    QLabel *balanceLabel;
    QLabel *payoutRateLabel;
    int balance_game1;
    void paintEvent(QPaintEvent *event) override;

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
    QLabel *player_label;
    QLabel *banker_label;
    int playerScore;
    int bankerScore;
    int updatedPlayerScore;
    int updatedBankerScore;
    int outcome;

    QMovie *popup_banker;
    QMovie *popup_player;
    QMovie *popup_tie;


    QLabel *popup_banker_label;
    QLabel *popup_player_label;
    QLabel *popup_tie_label;

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

#endif // GAME1_H
