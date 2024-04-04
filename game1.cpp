#include "game1.h"
#include "mainwindow.h"
#include <random>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QFontDatabase>






Game1::Game1(int& balance, QWidget *parent) : QWidget(parent), balance(balance), g(std::random_device()()), check(false)
{
    qDebug() << "startGame called";
    this->setGeometry(100, 100, 620, 480);
    this->setWindowTitle("Baccarat Game");

    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    playerCard1 = new QLabel(this);
    playerCard2 = new QLabel(this);
    playerCard3 = new QLabel(this);
    bankerCard1 = new QLabel(this);
    bankerCard2 = new QLabel(this);
    bankerCard3 = new QLabel(this);

    playerCard1->setGeometry(100, 100, 100, 150);
    playerCard2->setGeometry(210, 100, 100, 150);
    playerCard3->setGeometry(155, 200, 100, 150);
    bankerCard1->setGeometry(350, 100, 100, 150);
    bankerCard2->setGeometry(460, 100, 100, 150);
    bankerCard3->setGeometry(405, 200, 100, 150);

    spade_A = new QMovie(":/cards/Resource_Files/Casino_image/Card/A/spade_A.gif");
    heart_A = new QMovie(":/cards/Resource_Files/Casino_image/Card/A/heart_A.gif");
    diamond_A = new QMovie(":/cards/Resource_Files/Casino_image/Card/A/diamond_A.gif");
    club_A = new QMovie(":/cards/Resource_Files/Casino_image/Card/A/club_A.gif");

    spade_2 = new QMovie(":/cards/Resource_Files/Casino_image/Card/2/spade_2.gif");
    heart_2 = new QMovie(":/cards/Resource_Files/Casino_image/Card/2/heart_2.gif");
    diamond_2 = new QMovie(":/cards/Resource_Files/Casino_image/Card/2/diamond_2.gif");
    club_2 = new QMovie(":/cards/Resource_Files/Casino_image/Card/2/club_2.gif");
    spade_3 = new QMovie(":/cards/Resource_Files/Casino_image/Card/3/spade_3.gif");
    heart_3 = new QMovie(":/cards/Resource_Files/Casino_image/Card/3/heart_3.gif");
    diamond_3 = new QMovie(":/cards/Resource_Files/Casino_image/Card/3/diamond_3.gif");
    club_3 = new QMovie(":/cards/Resource_Files/Casino_image/Card/3/club_3.gif");

    spade_4 = new QMovie(":/cards/Resource_Files/Casino_image/Card/4/spade_4.gif");
    heart_4 = new QMovie(":/cards/Resource_Files/Casino_image/Card/4/heart_4.gif");
    diamond_4 = new QMovie(":/cards/Resource_Files/Casino_image/Card/4/diamond_4.gif");
    club_4 = new QMovie(":/cards/Resource_Files/Casino_image/Card/4/club_4.gif");

    spade_5 = new QMovie(":/cards/Resource_Files/Casino_image/Card/5/spade_5.gif");
    heart_5 = new QMovie(":/cards/Resource_Files/Casino_image/Card/5/heart_5.gif");
    diamond_5 = new QMovie(":/cards/Resource_Files/Casino_image/Card/5/diamond_5.gif");
    club_5 = new QMovie(":/cards/Resource_Files/Casino_image/Card/5/club_5.gif");

    spade_6 = new QMovie(":/cards/Resource_Files/Casino_image/Card/6/spade_6.gif");
    heart_6 = new QMovie(":/cards/Resource_Files/Casino_image/Card/6/heart_6.gif");
    diamond_6 = new QMovie(":/cards/Resource_Files/Casino_image/Card/6/diamond_6.gif");
    club_6 = new QMovie(":/cards/Resource_Files/Casino_image/Card/6/club_6.gif");

    spade_7 = new QMovie(":/cards/Resource_Files/Casino_image/Card/7/spade_7.gif");
    heart_7 = new QMovie(":/cards/Resource_Files/Casino_image/Card/7/heart_7.gif");
    diamond_7 = new QMovie(":/cards/Resource_Files/Casino_image/Card/7/diamond_7.gif");
    club_7 = new QMovie(":/cards/Resource_Files/Casino_image/Card/7/club_7.gif");

    spade_8 = new QMovie(":/cards/Resource_Files/Casino_image/Card/8/spade_8.gif");
    heart_8 = new QMovie(":/cards/Resource_Files/Casino_image/Card/8/heart_8.gif");
    diamond_8 = new QMovie(":/cards/Resource_Files/Casino_image/Card/8/diamond_8.gif");
    club_8 = new QMovie(":/cards/Resource_Files/Casino_image/Card/8/club_8.gif");

    spade_9 = new QMovie(":/cards/Resource_Files/Casino_image/Card/9/spade_9.gif");
    heart_9 = new QMovie(":/cards/Resource_Files/Casino_image/Card/9/heart_9.gif");
    diamond_9 = new QMovie(":/cards/Resource_Files/Casino_image/Card/9/diamond_9.gif");
    club_9 = new QMovie(":/cards/Resource_Files/Casino_image/Card/9/club_9.gif");

    spade_10 = new QMovie(":/cards/Resource_Files/Casino_image/Card/10/spade_10.gif");
    heart_10 = new QMovie(":/cards/Resource_Files/Casino_image/Card/10/heart_10.gif");
    diamond_10 = new QMovie(":/cards/Resource_Files/Casino_image/Card/10/diamond_10.gif");
    club_10 = new QMovie(":/cards/Resource_Files/Casino_image/Card/10/club_10.gif");

    spade_J = new QMovie(":/cards/Resource_Files/Casino_image/Card/J/spade_J.gif");
    heart_J = new QMovie(":/cards/Resource_Files/Casino_image/Card/J/heart_J.gif");
    diamond_J = new QMovie(":/cards/Resource_Files/Casino_image/Card/J/diamond_J.gif");
    club_J = new QMovie(":/cards/Resource_Files/Casino_image/Card/J/club_J.gif");

    spade_Q = new QMovie(":/cards/Resource_Files/Casino_image/Card/Q/spade_Q.gif");
    heart_Q = new QMovie(":/cards/Resource_Files/Casino_image/Card/Q/heart_Q.gif");
    diamond_Q = new QMovie(":/cards/Resource_Files/Casino_image/Card/Q/diamond_Q.gif");
    club_Q = new QMovie(":/cards/Resource_Files/Casino_image/Card/Q/club_Q.gif");

    spade_K = new QMovie(":/cards/Resource_Files/Casino_image/Card/K/spade_K.gif");
    heart_K = new QMovie(":/cards/Resource_Files/Casino_image/Card/K/heart_K.gif");
    diamond_K = new QMovie(":/cards/Resource_Files/Casino_image/Card/K/diamond_K.gif");
    club_K = new QMovie(":/cards/Resource_Files/Casino_image/Card/K/club_K.gif");

    std::vector<QMovie*> allCards {spade_A, heart_A, diamond_A, club_A,
        spade_2, heart_2, diamond_2, club_2,
        spade_3, heart_3, diamond_3, club_3,
        spade_4, heart_4, diamond_4, club_4,
        spade_5, heart_5, diamond_5, club_5,
        spade_6, heart_6, diamond_6, club_6,
        spade_7, heart_7, diamond_7, club_7,
        spade_8, heart_8, diamond_8, club_8,
        spade_9, heart_9, diamond_9, club_9,
        spade_10,heart_10, diamond_10, club_10,
        spade_J, heart_J, diamond_J, club_J,
        spade_Q, heart_Q, diamond_Q, club_Q,
        spade_K, heart_K, diamond_K, club_K,};

    check = true;
    if(check){

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(allCards.begin(), allCards.end(), g);

        selectedCards.assign(allCards.begin(), allCards.begin() + 52);}

    playerBetButton = new QPushButton("Player", this);
    bankerBetButton = new QPushButton("Banker", this);
    drawBetButton = new QPushButton("Draw", this);


    // playerBetButton->setStyleSheet("QPushButton { background-color: blue; color: white; }");

    playerBetButton->setStyleSheet("QPushButton {"
                                   "    color: white;"
                                   "    background-color: blue;"
                                   "    border-radius: 5px;"
                                   "    padding: 5px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "    background-color: darkblue;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "    background-color: lightblue;"
                                   "}");
    bankerBetButton->setStyleSheet("QPushButton {"
                                   "    color: white;"
                                   "    background-color: red;"
                                   "    border-radius: 5px;"
                                   "    padding: 5px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "    background-color: darkred;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "    background-color: lightred;"
                                   "}");
    drawBetButton->setStyleSheet("QPushButton {"
                                 "    color: white;"
                                 "    background-color: green;"
                                 "    border-radius: 5px;"
                                 "    padding: 5px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "    background-color: darkgreen;"
                                 "}"
                                 "QPushButton:pressed {"
                                 "    background-color: lightgreen;"
                                 "}");


    connect(playerBetButton, &QPushButton::clicked, this, [this](){ onBetButtonClicked(0); });
    connect(bankerBetButton, &QPushButton::clicked, this, [this](){ onBetButtonClicked(1); });
    connect(drawBetButton, &QPushButton::clicked, this, [this](){ onBetButtonClicked(2); });

    // resultLabel = new QLabel(this);
    // resultLabel->setGeometry(QRect(350, 350, 120, 30));
    // resultLabel->setText("");

    balance_game1 = balance;
    emit balanceChanged(balance_game1);

    playerBetButton->setGeometry(QRect(105, 425, 120, 30));
    bankerBetButton->setGeometry(QRect(405, 425, 120, 30));
    drawBetButton->setGeometry(QRect(255, 425, 120, 30));
    QFont labelFont(fontFamily, 16, QFont::Bold);
    QFont balanceFont(fontFamily, 12, QFont::Bold);

    balanceLabel = new QLabel(this);
    balanceLabel->setFont(balanceFont);
    balanceLabel->setStyleSheet("QLabel { color: white; }");
    balanceLabel->setGeometry(QRect(430, 8, 200, 30));
    balanceLabel->setText("$ " + QString::number(balance_game1));


    QFont buttonFont(fontFamily, 9 , QFont::Bold);
    playerBetButton->setFont(buttonFont);
    bankerBetButton->setFont(buttonFont);
    drawBetButton->setFont(buttonFont);

    bet_amount = 0;

    bet_label = new QLabel(this);
    bet_label->setStyleSheet("QLabel { color: white; }");
    bet_label->setFont(labelFont);
    bet_label->setGeometry(QRect(20, 370, 200, 50));
    bet_label->setText(QString::number(bet_amount));

    chip_1 = new ClickableLabel(this);
    chip_1_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_1.gif");
    chip_1->setMovie(chip_1_gif);
    chip_1->setGeometry(160, 360, 100, 50);
    chip_1_gif->start();
    connect(chip_1, &ClickableLabel::clicked, this, &Game1::chip_1_add);

    chip_5 = new ClickableLabel(this);
    chip_5_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_5.gif");
    chip_5->setMovie(chip_5_gif);
    chip_5->setGeometry(210, 360, 100, 50);
    chip_5_gif->start();
    connect(chip_5, &ClickableLabel::clicked, this, &Game1::chip_5_add);

    chip_10 = new ClickableLabel(this);
    chip_10_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_10_2.gif");
    chip_10->setMovie(chip_10_gif);
    chip_10->setGeometry(260, 360, 100, 50);
    chip_10_gif->start();
    connect(chip_10, &ClickableLabel::clicked, this, &Game1::chip_10_add);


    chip_25 = new ClickableLabel(this);
    chip_25_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_25.gif");
    chip_25->setMovie(chip_25_gif);
    chip_25->setGeometry(310, 360, 100, 50);
    chip_25_gif->start();
    connect(chip_25, &ClickableLabel::clicked, this, &Game1::chip_25_add);

    chip_50 = new ClickableLabel(this);
    chip_50_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_50.gif");
    chip_50->setMovie(chip_50_gif);
    chip_50->setGeometry(360, 360, 100, 50);
    chip_50_gif->start();
    connect(chip_50, &ClickableLabel::clicked, this, &Game1::chip_50_add);

    chip_reject = new ClickableLabel(this);
    chip_reject_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_reject.gif");
    chip_reject->setMovie(chip_reject_gif);
    chip_reject->setGeometry(410, 360, 100, 50);
    chip_reject_gif->start();
    connect(chip_reject, &ClickableLabel::clicked, this, &Game1::chip_reject_add);


    player_label = new QLabel(this);
    player_label->setStyleSheet("QLabel { color: blue; }");
    player_label->setFont(labelFont);
    player_label->setGeometry(QRect(110, 80, 200, 50));

    banker_label = new QLabel(this);
    banker_label->setStyleSheet("QLabel { color: red; }");
    banker_label->setFont(labelFont);
    banker_label->setGeometry(QRect(370, 80, 200, 50));

    popup_banker_label = new QLabel(this);
    popup_banker_label->setGeometry(170, 130, 280, 220);
    popup_banker = new QMovie(":/game1/Resource_Files/Casino_image/banker_popup.png");
    popup_banker_label->setMovie(popup_banker);
    popup_banker->start();
    popup_banker_label->hide();

    popup_player_label = new QLabel(this);
    popup_player_label->setGeometry(170, 130, 280, 220);
    popup_player = new QMovie(":/game1/Resource_Files/Casino_image/player_popup.png");
    popup_player_label->setMovie(popup_player);
    popup_player->start();
    popup_player_label->hide();

    popup_tie_label = new QLabel(this);
    popup_tie_label->setGeometry(170, 130, 280, 220);
    popup_tie = new QMovie(":/game1/Resource_Files/Casino_image/tie_popup.png");
    popup_tie_label->setMovie(popup_tie);
    popup_tie->start();
    popup_tie_label->hide();

    // QPushButton *instructionButton = new QPushButton("Show Instructions", this);
    // instructionButton->setGeometry(QRect(450, 430, 150, 30)); // Adjust the geometry as needed
    // connect(instructionButton, &QPushButton::clicked, this, &Game1::showInstructions);

    instuction_botton = new ClickableLabel(this);
    instuction_botton_gif = new QMovie(":/instructions/Resource_Files/instuction/instuction_botton/bacinstruc.png");
    instuction_botton->setMovie(instuction_botton_gif);
    instuction_botton->setGeometry(40, 8, 105, 34);
    instuction_botton_gif->start();
    connect(instuction_botton, &ClickableLabel::clicked, this, &Game1::showInstructions);

    quitButton = new ClickableLabel(this);
    quitButton_gif = new QMovie(":/quitbutton/Resource_Files/quit_botton/bacexit.png");
    quitButton->setMovie(quitButton_gif);
    quitButton->setGeometry(5, 10, 31, 29);
    quitButton_gif->start();
    connect(quitButton, &ClickableLabel::clicked, this, &Game1::close);
}

void Game1::onBetButtonClicked(int betType) {
    if (bet_amount <= 0 || bet_amount > balance_game1) {
        QMessageBox::warning(this, "Invalid Bet", "Please enter a valid bet amount within your balance.");
        return;
    }

    userBet = betType;
    qDebug() << "Bet button clicked, betType: " << betType << ", amount: " << bet_amount;

    playerBetButton->setEnabled(false);
    bankerBetButton->setEnabled(false);
    drawBetButton->setEnabled(false);

    startGame();
}


int Game1::calculateHandScore(const std::vector<QMovie*>& hand) const {
    int totalScore = 0;

    for (QMovie* card : hand) {
        int cardScore = 0;

        if (card == spade_A || card == heart_A || card == diamond_A || card == club_A) {
            cardScore = 1;
        } else if (card == spade_K || card == heart_K || card == diamond_K || card == club_K ||
                   card == spade_Q || card == heart_Q || card == diamond_Q || card == club_Q ||
                   card == spade_J || card == heart_J || card == diamond_J || card == club_J ||
                   card == spade_10 || card == heart_10 || card == diamond_10 || card == club_10) {
            cardScore = 0;
        } else {        
            const std::vector<QMovie*> cards = {spade_2, heart_2, diamond_2, club_2, spade_3, heart_3, diamond_3, club_3,spade_4, heart_4, diamond_4, club_4,spade_5, heart_5, diamond_5, club_5,spade_6, heart_6, diamond_6, club_6,spade_7, heart_7, diamond_7, club_7,spade_8, heart_8, diamond_8, club_8,spade_9, heart_9, diamond_9, club_9};
            const std::vector<int> values = {2, 2, 2, 2, 3, 3, 3, 3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8, 9, 9, 9, 9};

            for (size_t j = 0; j < cards.size(); ++j) {
                if (card == cards[j]) {
                    cardScore = values[j];
                    break;
                }
            }
        }



        totalScore += cardScore;

    }

    if (totalScore > 9){
        totalScore = totalScore % 10;
    }

    return totalScore;
}


void Game1::setupMovie(QLabel* label, QMovie* movie) {
    if (!label || !movie) {
        qDebug() << "setupMovie called with null label or movie";
        return;
    }

    label->setMovie(movie);
    connect(movie, &QMovie::frameChanged, [movie, label](int frameNumber){
        if (frameNumber == movie->frameCount() - 1) {
            movie->stop();
        }
    });
    movie->start();
}

void Game1::determineWinner() {  
    if (selectedCards.size() < 6) {
        QMessageBox::critical(this, "Error", "Not enough cards to determine the winner.");
        return;
    }

    std::vector<QMovie*> playerHand {selectedCards[0], selectedCards[1]};
    std::vector<QMovie*> bankerHand {selectedCards[2], selectedCards[3]};
    playerScore = calculateHandScore(playerHand);
    bankerScore = calculateHandScore(bankerHand);




    // if (playerScore <= 5) {
    //     playerHand.push_back(selectedCards[4]);
    //     QTimer::singleShot(3000, this, [this](){ setupMovie(playerCard3, selectedCards[4]); });
    //     playerScore = calculateHandScore(playerHand);

    // }

    // if (bankerScore <= 5) {
    //     bankerHand.push_back(selectedCards[5]);
    //     QTimer::singleShot(3000, this, [this](){ setupMovie(bankerCard3, selectedCards[5]); });
    //     bankerScore = calculateHandScore(bankerHand);
    // }


    if (playerScore <= 5) {
        playerHand.push_back(selectedCards[4]);
        QTimer::singleShot(3000, this, [this, playerHand]() mutable {
            setupMovie(playerCard3, selectedCards[4]);
            QTimer::singleShot(3000, this, [this, playerHand]() {
                player_label->show();
                playerScore = calculateHandScore(playerHand);
                updatedPlayerScore = playerScore;
                player_label->setText("Player: " + QString::number(playerScore));
            });
        });

    }else if (playerScore > 5){
        QTimer::singleShot(3000, this, [this, playerHand]() {
            player_label->show();
            playerScore = calculateHandScore(playerHand);
            updatedPlayerScore = playerScore;
            player_label->setText("Player: " + QString::number(playerScore));
        });
    }

    if (bankerScore <= 5) {
        bankerHand.push_back(selectedCards[5]);
        QTimer::singleShot(3000, this, [this, bankerHand]() mutable {
            setupMovie(bankerCard3, selectedCards[5]);
            QTimer::singleShot(3000, this, [this, bankerHand]() {
                banker_label->show();
                bankerScore = calculateHandScore(bankerHand);
                updatedBankerScore = bankerScore;
                banker_label->setText("Banker: " + QString::number(bankerScore));
            });
        });

    } else if (bankerScore > 5){
        QTimer::singleShot(3000, this, [this, bankerHand]() {
            banker_label->show();
            bankerScore = calculateHandScore(bankerHand);
            updatedBankerScore = bankerScore;
            banker_label->setText("Banker: " + QString::number(bankerScore));
        });
    }

    playerScore = calculateHandScore(playerHand);
    bankerScore = calculateHandScore(bankerHand);
    if (playerScore > bankerScore) {
        outcome = 0; // Player wins
    } else if (playerScore < bankerScore) {
        outcome = 1; // Banker wins
    } else {
        outcome = 2; // Tie
    }


    if ((outcome == 0 && userBet == 0) || (outcome == 1 && userBet == 1)) {
        balance_game1 += bet_amount * 2;
        emit balanceChanged(balance_game1);
    } else if (outcome == 2 && userBet == 2) {
        balance_game1 += bet_amount * 8;
        emit balanceChanged(balance_game1);
    } else {
        balance_game1 -= bet_amount;
        emit balanceChanged(balance_game1);
    }



    QString resultMessage;
    switch (outcome) {
    case 0: resultMessage = "Player wins!"; break;
    case 1: resultMessage = "Banker wins!"; break;
    case 2: resultMessage = "Tie!"; break;
    }

    if (bankerHand.size() == 2 && playerHand.size() == 2){
        qDebug() << "else";
        QTimer::singleShot(3500, this, [this, resultMessage]() {
            if(resultMessage == "Player wins!"){
                popup_player_label->show();
                QTimer::singleShot(3000, this, [this]() {popup_player_label->hide();});
            }else if (resultMessage == "Banker wins!"){
                popup_banker_label->show();
                QTimer::singleShot(3000, this, [this]() {popup_banker_label->hide();});
            }else{
                popup_tie_label->show();
                QTimer::singleShot(3000, this, [this]() {popup_tie_label->hide();});
            }
            QTimer::singleShot(3000, this, [this]() {
                playerCard1->clear();
                playerCard2->clear();
                playerCard3->clear();
                bankerCard1->clear();
                bankerCard2->clear();
                bankerCard3->clear();
                player_label->hide();
                banker_label->hide();
                chip_1->setEnabled(true);
                chip_5->setEnabled(true);
                chip_10->setEnabled(true);
                chip_25->setEnabled(true);
                chip_50->setEnabled(true);
                chip_reject->setEnabled(true);
                playerBetButton->setEnabled(true);
                bankerBetButton->setEnabled(true);
                drawBetButton->setEnabled(true);});
            std::shuffle(selectedCards.begin(), selectedCards.end(), g);
            if((outcome == 0 && userBet == 0) || (outcome == 1 && userBet == 1)){
                balanceLabel->setStyleSheet("QLabel { color: green; }");
            }else{
                balanceLabel->setStyleSheet("QLabel { color: red; }");
            }
            balanceLabel->setText("$ " + QString::number(balance_game1));
            QTimer::singleShot(1000, this, [this]() {
                balanceLabel->setStyleSheet("QLabel { color: white; }");

            });
        });
    }    else {
        qDebug() << "playerScore <= 5";
        QTimer::singleShot(6000, this, [this, resultMessage]() {
            if(resultMessage == "Player wins!"){
                popup_player_label->show();
                QTimer::singleShot(3000, this, [this]() {popup_player_label->hide();});
            }else if (resultMessage == "Banker wins!"){
                popup_banker_label->show();
                QTimer::singleShot(3000, this, [this]() {popup_banker_label->hide();});
            }else{
                popup_tie_label->show();
                QTimer::singleShot(3000, this, [this]() {popup_tie_label->hide();});
            }
            QTimer::singleShot(3000, this, [this]() {
                playerCard1->clear();
                playerCard2->clear();
                playerCard3->clear();
                bankerCard1->clear();
                bankerCard2->clear();
                bankerCard3->clear();
                player_label->hide();
                banker_label->hide();
                chip_1->setEnabled(true);
                chip_5->setEnabled(true);
                chip_10->setEnabled(true);
                chip_25->setEnabled(true);
                chip_50->setEnabled(true);
                chip_reject->setEnabled(true);
                playerBetButton->setEnabled(true);
                bankerBetButton->setEnabled(true);
                drawBetButton->setEnabled(true);});
            std::shuffle(selectedCards.begin(), selectedCards.end(), g);

            if((outcome == 0 && userBet == 0) || (outcome == 1 && userBet == 1)){
                balanceLabel->setStyleSheet("QLabel { color: green; }");
            }else{
                balanceLabel->setStyleSheet("QLabel { color: red; }");
            }
            balanceLabel->setText("$ " + QString::number(balance_game1));
            QTimer::singleShot(1000, this, [this]() {
                balanceLabel->setStyleSheet("QLabel { color: white; }");

            });
        });
    }

    qDebug() << "Player Score: " << playerScore << ", Banker Score: " << bankerScore << ", Result: " << resultMessage;


}



void Game1::startGame() {
    qDebug() << "Starting the game";

    chip_1->setEnabled(false);
    chip_5->setEnabled(false);
    chip_10->setEnabled(false);
    chip_25->setEnabled(false);
    chip_50->setEnabled(false);
    chip_reject->setEnabled(false);

    for(auto &card : selectedCards) {
        qDebug() << card->fileName();
    }

    if (selectedCards.size() >= 4) {
        QTimer::singleShot(1000, this, [this](){ setupMovie(playerCard1, selectedCards[0]); });
        QTimer::singleShot(1000, this, [this](){ setupMovie(bankerCard1, selectedCards[2]); });
        QTimer::singleShot(4000, this, [this](){ setupMovie(playerCard2, selectedCards[1]); });
        QTimer::singleShot(4000, this, [this](){ setupMovie(bankerCard2, selectedCards[3]); });

        QTimer::singleShot(4000, this, &Game1::determineWinner);
    } else {
        qDebug() << "Not enough cards in the selectedCards vector!";
    }
}

void Game1::resetGame() {
    for (auto &card : selectedCards) {
        if (card) {
            card->stop();
            card->deleteLater();
        }
    }
    selectedCards.clear();

    if (!check) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(allCards.begin(), allCards.end(), g);
        selectedCards.assign(allCards.begin(), allCards.begin() + 6);
        check = true;
    }

    playerCard1->clear();
    playerCard2->clear();
    playerCard3->clear();
    bankerCard1->clear();
    bankerCard2->clear();
    bankerCard3->clear();


    playerBetButton->setEnabled(true);
    bankerBetButton->setEnabled(true);
    drawBetButton->setEnabled(true);

    qDebug() << "Game reset and ready for a new round";

}

void Game1::updateBalance(int outcome) {

    bool isWin = false;

    if ((userBet == outcome && outcome != 2) || (outcome == 2 && userBet == 2)) {
        isWin = true;
    }

    if (isWin) {
        if (outcome == 2) {
            balance_game1 += bet_amount * 6;
            emit balanceChanged(balance_game1);
        } else {
            balance_game1 += bet_amount * 2;
            emit balanceChanged(balance_game1);
        }
    } else {
        balance_game1 -= bet_amount;
        emit balanceChanged(balance_game1);
    }

    balanceLabel->setText("Balance: $" + QString::number(balance_game1));
}


void Game1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap backgroundImage(":/game1/Resource_Files/Casino_image/table/poker_table_new.jpg");
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QWidget::paintEvent(event);
}

void Game1::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    emit gameClosed(this -> getBalance());
}

void Game1::chip_10_add(){
    qDebug() << "Add 10";
    bet_amount += 10;
    bet_label->setText(QString::number(bet_amount));
}
void Game1::chip_1_add(){
    qDebug() << "Add 1";
    bet_amount += 1;
    bet_label->setText(QString::number(bet_amount));
}
void Game1::chip_5_add(){
    qDebug() << "Add 5";
    bet_amount += 5;
    bet_label->setText(QString::number(bet_amount));
}
void Game1::chip_25_add(){
    qDebug() << "Add 25";
    bet_amount += 25;
    bet_label->setText(QString::number(bet_amount));
}
void Game1::chip_50_add(){
    qDebug() << "Add 50";
    bet_amount += 50;
    bet_label->setText(QString::number(bet_amount));
}
void Game1::chip_reject_add(){
    qDebug() << "chip_reject";
    bet_amount = 0;
    bet_label->setText(QString::number(bet_amount));
}

void Game1::showInstructions() {
    QWidget *instructionWidget = new QWidget;
    QLabel *instructionLabel = new QLabel(instructionWidget);
    QPixmap instructionPixmap(":/instructions/Resource_Files/instuction/Shoe.png");

    instructionWidget->resize(800, 600);

    instructionPixmap = instructionPixmap.scaled(instructionWidget->size(), Qt::KeepAspectRatioByExpanding);

    instructionLabel->setPixmap(instructionPixmap);
    instructionLabel->resize(instructionWidget->size());

    QVBoxLayout *layout = new QVBoxLayout(instructionWidget);
    layout->addWidget(instructionLabel);
    instructionWidget->setLayout(layout);

    instructionWidget->setAttribute(Qt::WA_DeleteOnClose);
    instructionWidget->show();
}


