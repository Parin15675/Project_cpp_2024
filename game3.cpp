#include "game3.h"
#include "mainwindow.h"
#include "ClickableLabel.h"
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QMovie>
#include <QTimer>
#include <QApplication>
#include <QFont>
#include <QIcon>
#include <QSize>
#include <random>
#include <QFontDatabase>


Game3::Game3(int& balance, QWidget *parent) :  QWidget(parent), balance(balance) {
    this->setWindowTitle("Game 3");
    this->resize(600, 600);

    football_label = new QLabel(this);
    goalkeeper_label = new QLabel(this);
    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    football_down_left = new QMovie(":/football/Resource_Files/football/football/football_down_left_new.gif");
    football_top_left = new QMovie(":/football/Resource_Files/football/football/football_top_left_new.gif");
    football_down_right = new QMovie(":/football/Resource_Files/football/football/football_down_right_new.gif");
    football_still = new QMovie(":/football/Resource_Files/football/football_still_new.gif");
    football_top_right = new QMovie(":/football/Resource_Files/football/football/football_top_right_new.gif");

    goalkeeper_top_right = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_right_new.gif");
    goalkeeper_bottom_right = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_right_new.gif");
    goalkeeper_top_left = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_left_new.gif");
    goalkeeper_bottom_left = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_left_new.gif");
    goalkeeper_still = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_still.gif");

    goalkeeper_top_left_hard = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_left_hard_new.gif");
    goalkeeper_top_right_hard = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_right_hard_new.gif");
    goalkeeper_bottom_right_hard = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_right_hard_new.gif");
    goalkeeper_bottom_left_hard = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_left_hard_new.gif");
    goalkeeper_still_hard = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_still_hard.gif");

    goalkeeper_top_left_hard_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_left_hard_win_new.gif");
    goalkeeper_top_right_hard_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_right_hard_win_new.gif");
    goalkeeper_bottom_right_hard_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_right_hard_win_new.gif");
    goalkeeper_bottom_left_hard_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_left_hard_win_new.gif");

    goalkeeper_top_left_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_left_win_new.gif");
    goalkeeper_top_right_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_right_win_new.gif");
    goalkeeper_bottom_right_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_right_win_new.gif");
    goalkeeper_bottom_left_win = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_left_win_new.gif");

    setupMovie(football_label,football_still);
    setupMovie(goalkeeper_label,goalkeeper_still);

    buttonShootTopLeft = new ClickableLabel(this);
    buttonShootTopRight = new ClickableLabel(this);
    buttonShootLeft = new ClickableLabel(this);
    buttonShootRight = new ClickableLabel(this);

    buttonShootTopLeft->setGeometry(160, 180, 100, 100);
    buttonShootTopRight->setGeometry(410, 180, 100, 100);
    buttonShootLeft->setGeometry(160, 280, 100, 100);
    buttonShootRight->setGeometry(410, 280, 100, 100);

    target_1 = new QMovie(":/game3/Resource_Files/football/target_2.gif");

    buttonShootTopLeft->setMovie(target_1);
    buttonShootTopRight->setMovie(target_1);
    buttonShootLeft->setMovie(target_1);
    buttonShootRight->setMovie(target_1);
    target_1->start();

    connect(buttonShootTopLeft, &ClickableLabel::clicked, this, &Game3::shoot_Top_Left);
    connect(buttonShootTopRight,  &ClickableLabel::clicked, this, &Game3::shoot_Top_Right);
    connect(buttonShootLeft,  &ClickableLabel::clicked, this, &Game3::shoot_Down_Left);
    connect(buttonShootRight,  &ClickableLabel::clicked, this, &Game3::shoot_Down_Right);

    std::vector<int> num = {1,2,3,4};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(num.begin(), num.end(), g);

    std::vector<int> goal_direction;

    goal_direction.assign(num.begin(), num.begin() + 4);
    remain_round = 5;
    win_round = 0;

    QFont balanceLabelFont(fontFamily, 12, QFont::Bold);
    balanceLabel = new QLabel(this);
    balanceLabel->setFont(balanceLabelFont);
    balanceLabel->setStyleSheet("QLabel { color: black; }");
    balanceLabel->setGeometry(QRect(420, 8, 200, 30));
    balanceLabel->setText("$ " + QString::number(balance_game3));
    bet_Label_easy = 0.5;
    bet_Label_hard = 2;

    QFont remainsLabelFont(fontFamily, 8, QFont::Bold);
    remainsLabel = new QLabel(this);
    remainsLabel->setFont(remainsLabelFont);
    remainsLabel->setStyleSheet("QLabel { color: black; }");
    remainsLabel->setGeometry(QRect(0, 350, 200, 30));
    remainsLabel->setText("Remain round: " + QString::number(remain_round));

    win_round_Label = new QLabel(this);
    win_round_Label->setFont(remainsLabelFont);
    win_round_Label->setStyleSheet("QLabel { color: black; }");
    win_round_Label->setGeometry(QRect(470, 350, 200, 30));
    win_round_Label->setText("Win round: " + QString::number(win_round));
    check_balance = true;
    balance_game3 = balance;
    balanceLabel->setText("$ " + QString::number(balance_game3));
    check_balance = false;

    chip_1 = new ClickableLabel(this);
    chip_1_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_1.gif");
    chip_1->setMovie(chip_1_gif);
    chip_1->setGeometry(300, 70, 100, 50);
    chip_1_gif->start();
    connect(chip_1, &ClickableLabel::clicked, this, &Game3::chip_1_add);

    chip_5 = new ClickableLabel(this);
    chip_5_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_5.gif");
    chip_5->setMovie(chip_5_gif);
    chip_5->setGeometry(350, 70, 100, 50);
    chip_5_gif->start();
    connect(chip_5, &ClickableLabel::clicked, this, &Game3::chip_5_add);

    chip_10 = new ClickableLabel(this);
    chip_10_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_10_2.gif");
    chip_10->setMovie(chip_10_gif);
    chip_10->setGeometry(400, 70, 100, 50);
    chip_10_gif->start();
    connect(chip_10, &ClickableLabel::clicked, this, &Game3::chip_10_add);

    chip_25 = new ClickableLabel(this);
    chip_25_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_25.gif");
    chip_25->setMovie(chip_25_gif);
    chip_25->setGeometry(450, 70, 100, 50);
    chip_25_gif->start();
    connect(chip_25, &ClickableLabel::clicked, this, &Game3::chip_25_add);

    chip_50 = new ClickableLabel(this);
    chip_50_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_50.gif");
    chip_50->setMovie(chip_50_gif);
    chip_50->setGeometry(500, 70, 100, 50);
    chip_50_gif->start();
    connect(chip_50, &ClickableLabel::clicked, this, &Game3::chip_50_add);

    chip_reject = new ClickableLabel(this);
    chip_reject_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_reject.gif");
    chip_reject->setMovie(chip_reject_gif);
    chip_reject->setGeometry(550, 70, 100, 50);
    chip_reject_gif->start();
    connect(chip_reject, &ClickableLabel::clicked, this, &Game3::chip_reject_add);

    bet_Label_easy = 0.5;
    bet_amount = 0;
    bet_select = bet_Label_easy;

    QFont bet_labelFont(fontFamily, 12, QFont::Bold);
    bet_label = new QLabel(this);
    bet_label->setStyleSheet("QLabel { color: black; }");
    bet_label->setFont(bet_labelFont);
    bet_label->setGeometry(QRect(35, 70, 200, 50));
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));

    goal_easy_button_label = new ClickableLabel(this);
    goal_easy_button = new QMovie(":/game3/Resource_Files/football/Goalkeeper/goal_easy_button.png");
    goal_easy_button_label->setGeometry(80, 450, 190, 135);
    goal_easy_button_label->setMovie(goal_easy_button);
    goal_easy_button->start();
    connect(goal_easy_button_label, &ClickableLabel::clicked, this, &Game3::chooseGoalkeeperEasy);

    goal_hard_button_label = new ClickableLabel(this);
    goal_hard_button = new QMovie(":/game3/Resource_Files/football/Goalkeeper/goal_hard_button.png");
    goal_hard_button_label->setGeometry(335, 450, 190, 135);
    goal_hard_button_label->setMovie(goal_hard_button);
    goal_hard_button->start();
    connect(goal_hard_button_label, &ClickableLabel::clicked, this, &Game3::chooseGoalkeeperHard);

    popup_win_label = new QLabel(this);
    popup_win_label->setGeometry(150, 230, 310, 100);
    popup_win = new QMovie(":/game3/Resource_Files/football/peswinpop.png");
    popup_win_label->setMovie(popup_win);
    popup_win->start();
    popup_win_label->hide();

    popup_lose_label = new QLabel(this);
    popup_lose_label->setGeometry(150, 230, 310, 100);
    popup_lose = new QMovie(":/game3/Resource_Files/football/peslosepop.png");
    popup_lose_label->setMovie(popup_lose);
    popup_lose->start();
    popup_lose_label->hide();

    instuction_botton = new ClickableLabel(this);
    instuction_botton_gif = new QMovie(":/instructions/Resource_Files/instuction/instuction_botton/pesinst.png");
    instuction_botton->setMovie(instuction_botton_gif);
    instuction_botton->setGeometry(48, 5, 114, 38);
    instuction_botton_gif->start();
    connect(instuction_botton, &ClickableLabel::clicked, this, &Game3::showInstructions);

    quitButton = new ClickableLabel(this);
    quitButton_gif = new QMovie(":/quitbutton/Resource_Files/quit_botton/pesexit.png");
    quitButton->setMovie(quitButton_gif);
    quitButton->setGeometry(5, 5, 41, 38);
    quitButton_gif->start();
    connect(quitButton, &ClickableLabel::clicked, this, &Game3::close);


    check_invalid = true;
    check_game = true;
}

Game3::~Game3() {}



void Game3::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap backgroundImage(":/game3/Resource_Files/football/pitch_new_2.jpg");
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QWidget::paintEvent(event);
}

void Game3::InvalidBet(){
    if (bet_amount <= 0 || bet_amount > balance_game3) {
        qDebug() << "invalid 101";
        QMessageBox::warning(this, "Invalid Bet", "Your bet is invalid or exceeds your balance.");
        check_invalid = false;
        resetGameState();
        return;
    }else{
        check_invalid = true;
    }
}

void Game3::setupMovie(QLabel* label, QMovie* movie) {
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

void Game3::setupMovie_win(QLabel* label, QMovie* movie) {

    qDebug() << "movie win";
    if (!label || !movie) {
        qDebug() << "setupMovie called with null label or movie";
        return;
    }

    label->setMovie(movie);
    connect(movie, &QMovie::frameChanged, [movie, label](int frameNumber){
    });
    movie->start();
}


void Game3::chooseGoalkeeper(int input){
    if(input == 1){
        qDebug() << "goal easy";
        goalkeeper_check = true;
        goalkeeper_top_right = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_right_new.gif");
        goalkeeper_bottom_right = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_right_new.gif");
        goalkeeper_top_left = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_left_new.gif");
        goalkeeper_bottom_left = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_left_new.gif");
        goalkeeper_still = new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_still.gif");
        bet_select = bet_Label_easy;
        bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
    }else{
        qDebug() << "goal hard";
        goalkeeper_top_left= new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_left_hard_new.gif");
        goalkeeper_top_right= new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_top_right_hard_new.gif");
        goalkeeper_bottom_right= new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_right_hard_new.gif");
        goalkeeper_bottom_left= new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_bottom_left_hard_new.gif");
        goalkeeper_still= new QMovie(":/goalkeeper/Resource_Files/football/Goalkeeper/goalkeeper_still_hard.gif");
        goalkeeper_check = false;
        bet_select = bet_Label_hard;
        bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));


    }
}

void Game3::setGoalkeeperModeButtonsEnabled(bool enabled) {
    if(enabled){
        goal_easy_button_label->show();
        goal_hard_button_label->show();
    }else{
        goal_easy_button_label->hide();
        goal_hard_button_label->hide();
    }
}

void Game3::chooseGoalkeeperEasy() {
    chooseGoalkeeper(1);
    setupMovie(goalkeeper_label,goalkeeper_still);
}

void Game3::chooseGoalkeeperHard() {
    chooseGoalkeeper(2);
    setupMovie(goalkeeper_label,goalkeeper_still_hard);
}

void Game3::setHardMode() {
    check = false;
    qDebug() << "Game mode set to hard";
}

void Game3::updateBalanceDisplay() {
    if(win_round == 3){
        balanceLabel->setStyleSheet("QLabel { color: green; }");
    }else{
        balanceLabel->setStyleSheet("QLabel { color: red; }");
    }
    balanceLabel->setText("$ " + QString::number(balance_game3));
    QTimer::singleShot(1000, this, [this]() {balanceLabel->setStyleSheet("QLabel { color: black; }");});
}

void Game3::resetGameState(){
    QTimer::singleShot(1000, this, [this]() {setGoalkeeperModeButtonsEnabled(true); qDebug() << "reset botton";});
    check_game = true;
    popup_win_label->hide();
    popup_lose_label->hide();
    win_round_Label->setStyleSheet("QLabel { color: black; }");
    remainsLabel->setStyleSheet("QLabel { color: black; }");
    win_round = 0;
    remain_round = 5;
    remainsLabel->setText("Remain round: " + QString::number(remain_round));
    win_round_Label->setText("Win round: " + QString::number(win_round));
    setupMovie(football_label,football_still);
    setupMovie(goalkeeper_label,goalkeeper_still);
    chip_1->setEnabled(true);
    chip_5->setEnabled(true);
    chip_10->setEnabled(true);
    chip_25->setEnabled(true);
    chip_50->setEnabled(true);
    chip_reject->setEnabled(true);
}

void Game3::gameOver() {
    QString resultMessage;
    if (bet_amount <= 0 || bet_amount > balance_game3) {
        QMessageBox::warning(this, "Invalid Bet", "Your bet is invalid or exceeds your balance.");
        resetGameState();
        return;
    }


    if (win_round >= 3) {
        if(goalkeeper_check){
            balance_game3 = bet_amount*0.5 + balance_game3;
        }
        else{
            balance_game3 = bet_amount*2 + balance_game3;
        }
        QTimer::singleShot(2000, this, [this]() {updateBalanceDisplay();});

        resultMessage = "Congratulations! You've won the game!";
        check_game = false;
    } else {
        balance_game3 = balance_game3 - bet_amount;
        QTimer::singleShot(2000, this, [this]() {updateBalanceDisplay();});
        resultMessage = "Game Over. Try again!";
        check_game = false;
    }


    QTimer::singleShot(2000, this, [this, resultMessage]() {
        // QMessageBox::StandardButton reply = QMessageBox::question(this, "Game Result", resultMessage + "\nDo you want to close the game?",
        //                                                           QMessageBox::Yes | QMessageBox::No);

        // if (reply == QMessageBox::Yes) {

        //     this->close();
        // }else{
        //     check_game = true;
        //     resetGameState();} // Reset the game state whether the user decides to close the game or not

        if (resultMessage == "Congratulations! You've won the game!"){
            popup_win_label->show();
            QTimer::singleShot(2000, this, [this]() {resetGameState();});
        }else{
            popup_lose_label->show();
            QTimer::singleShot(2000, this, [this]() {resetGameState();});
        }

    });
}

void Game3::startMovie(QLabel* label, const QString& moviePath) {
    if (!label) {
        qDebug() << "startMovie called with null label";
        return;
    }

    QMovie* movie = new QMovie(moviePath);

    if (!movie->isValid()) {
        qDebug() << "Movie failed to load. Path:" << moviePath;
        delete movie;
        return;
    }

    label->setMovie(movie);


    connect(movie, &QMovie::frameChanged, [label](int frameNumber) {
        if (frameNumber == 0) {
            label->setMovie(label->movie());
        }
    });


    connect(movie, &QMovie::finished, [movie]() {
        delete movie;
    });

    movie->start();
}


void Game3::determineWinner(int userChoice) {
    if (bet_amount <= 0 || bet_amount > balance_game3) {
        qDebug() << "start game invalid";

        QMessageBox::warning(this, "Invalid Bet", "Your bet is invalid or exceeds your balance.");
        resetGameState();
        return;
    }

    hideAllButtons();
    chip_1->setEnabled(false);
    chip_5->setEnabled(false);
    chip_10->setEnabled(false);
    chip_25->setEnabled(false);
    chip_50->setEnabled(false);
    chip_reject->setEnabled(false);

    if (remain_round <= 0){
        qDebug() << "Game over";
        gameOver();

    }
    else{
        int rand_num;
        int rand_num_2;
        int winningDirection;
        std::random_device rd;
        std::mt19937 gen(rd());

        if (goalkeeper_check) {
            qDebug() << "mode easy";
            int rand_num = (userChoice == 3 || userChoice == 4) ? 2 : userChoice;
            std::uniform_int_distribution<> dis(rand_num, rand_num + 2);
            winningDirection = dis(gen);
        } else {
            qDebug() << "mode hard";
            int rand_num = (userChoice == 4) ? 3 : userChoice;
            std::uniform_int_distribution<> dis(rand_num, rand_num + 1);
            winningDirection = dis(gen);
        }

        if(winningDirection == 1){
            if (goalkeeper_check){
                if(userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_bottom_left);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_bottom_left_win);
                }
            }
            else{
                if(userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_bottom_left_hard);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_bottom_left_hard_win);
                }
            }
        }
        else if(winningDirection == 2){
            if (goalkeeper_check){
                if (userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_bottom_right);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_bottom_right_win);
                }
            }
            else{
                if (userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_bottom_right_hard);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_bottom_right_hard_win);
                }
            }
        }
        else if(winningDirection == 3){
            if (goalkeeper_check){
                if(userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_top_left);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_top_left_win);
                }
            }
            else{
                if(userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_top_left_hard);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_top_left_hard_win);
                }
            }
        }
        else {
            if (goalkeeper_check){
                if(userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_top_right);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_top_right_win);
                }
            }
            else{
                if(userChoice == winningDirection){
                    setupMovie(goalkeeper_label, goalkeeper_top_right_hard);}
                else{
                    setupMovie(goalkeeper_label, goalkeeper_top_right_hard_win);
                }
            }
        }


        if (userChoice == winningDirection) {
            qDebug() << "User loses!:" << winningDirection;
            qDebug() << "Winning round: " << win_round;
        } else {
            qDebug() << "User wins with choice:" << userChoice;
            win_round += 1; // Increment win count on win

            if(win_round == 3){
                QTimer::singleShot(2000, this, [this]() {
                    win_round_Label->setStyleSheet("QLabel { color: orange; }");
                    win_round_Label->setText("Win round: " + QString::number(win_round));

                });}else{
                QTimer::singleShot(2000, this, [this]() {
                    win_round_Label->setText("Win round: " + QString::number(win_round));
                });
            }
        }

        remain_round -= 1;
        remainsLabel->setText("Remain round: " + QString::number(remain_round));
        if (remain_round <= 0 || win_round == 3) {
            if(remain_round == 0){
                remainsLabel->setStyleSheet("QLabel { color: red; }");
                gameOver();
            }
            else{
                gameOver();
            }
        } else {
            showAllButtons();
        }
        showAllButtons();
    }

}





void Game3::shoot_Down_Left() {
    InvalidBet();
    if(check_invalid && check_game){
        setGoalkeeperModeButtonsEnabled(false);
        if (remain_round > 0){
            setupMovie(football_label, football_down_left);
            determineWinner(1);
        }else{
            qDebug() << "Game over";
            setupMovie(football_label,football_still);
            setupMovie(goalkeeper_label,goalkeeper_still);
        }
        Goal_still();
    }
}
void Game3::shoot_Down_Right() {
    InvalidBet();
    if (check_invalid && check_game){
        setGoalkeeperModeButtonsEnabled(false);
        if(remain_round > 0) {
            setupMovie(football_label, football_down_right);
            determineWinner(2);
        }else{
            qDebug() << "Game over";
            setupMovie(football_label,football_still);
            setupMovie(goalkeeper_label,goalkeeper_still);
        }
        Goal_still();
    }
}

void Game3::shoot_Top_Left() {
    InvalidBet();
    if(check_invalid && check_game){
        setGoalkeeperModeButtonsEnabled(false);
        if(remain_round > 0){
            setupMovie(football_label, football_top_left);
            determineWinner(3);
        }else{
            qDebug() << "Game over";
            setupMovie(football_label,football_still);
            setupMovie(goalkeeper_label,goalkeeper_still);
        }
        Goal_still();
    }
}

void Game3::shoot_Top_Right() {
    InvalidBet();
    if(check_invalid && check_game){
        setGoalkeeperModeButtonsEnabled(false);
        if(remain_round > 0){
            setupMovie(football_label, football_top_right);
            determineWinner(4);
        }else{
            qDebug() << "Game over";
            setupMovie(football_label,football_still);
            setupMovie(goalkeeper_label,goalkeeper_still);
        }
        Goal_still();
    }
}

void Game3::showAllButtons() {
    buttonShootTopLeft->show();
    buttonShootTopRight->show();
    buttonShootLeft->show();
    buttonShootRight->show();
}

void Game3::hideAllButtons(){
    buttonShootTopLeft->hide();
    buttonShootTopRight->hide();
    buttonShootLeft->hide();
    buttonShootRight->hide();
}

void Game3::Goal_still(){
    qDebug() << "Hiding all buttons";
    hideAllButtons();
    QTimer::singleShot(2000, this, [this](){
        qDebug() << "Resetting football movie";
        setupMovie(football_label, football_still);
    });
    QTimer::singleShot(2000, this, [this](){
        qDebug() << "Resetting goalkeeper movie, check is" << check;
        if(check){
            setupMovie(goalkeeper_label, goalkeeper_still);
        }else{
            setupMovie(goalkeeper_label, goalkeeper_still_hard);
        }
    });
    QTimer::singleShot(2000, this, [this](){
        qDebug() << "Showing all buttons";
        showAllButtons();
    });
}




void Game3::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    emit gameClosed(this -> getBalance());
}

void Game3::chip_10_add(){
    qDebug() << "Add 10";
    bet_amount += 10;
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
}
void Game3::chip_1_add(){
    qDebug() << "Add 1";
    bet_amount += 1;
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
}
void Game3::chip_5_add(){
    qDebug() << "Add 5";
    bet_amount += 5;
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
}
void Game3::chip_25_add(){
    qDebug() << "Add 25";
    bet_amount += 25;
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
}
void Game3::chip_50_add(){
    qDebug() << "Add 50";
    bet_amount += 50;
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
}
void Game3::chip_reject_add(){
    qDebug() << "chip_reject";
    bet_amount = 0;
    bet_label->setText(QString::number(bet_amount) + " x " + QString::number(bet_select));
}

void Game3::showInstructions() {
    QWidget *instructionWidget = new QWidget;
    QLabel *instructionLabel = new QLabel(instructionWidget);
    QPixmap instructionPixmap(":/instructions/Resource_Files/instuction/instuction_penelto.png");
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

