// betwindow.cpp
#include "horsebetwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QTimer>
#include <QFontDatabase>


HorseBetWindow::HorseBetWindow(int& balance, HorseRacing* horseRacing, QWidget *parent) : QWidget(parent), m_horseRacing(horseRacing), balance_game2(balance)
{

    purhorsewin = new QMovie (":/horsepopup/Resource_Files/horse/popup_win/purhorsewin.png");
    redhorsewin = new QMovie (":/horsepopup/Resource_Files/horse/popup_win/redhorsewin.png");
    yellowhorsewin = new QMovie (":/horsepopup/Resource_Files/horse/popup_win/yellowhorsewin.png");
    bluehorsewin = new QMovie (":/horsepopup/Resource_Files/horse/popup_win/bluehorsewin.png");
    greenhorsewin = new QMovie (":/horsepopup/Resource_Files/horse/popup_win/greenhorsewin.png");

    purhorselose = new QMovie (":/horsepopup/Resource_Files/horse/popup_lose/purhorselose.png");
    redhorselose = new QMovie (":/horsepopup/Resource_Files/horse/popup_lose/redhorselose.png");
    yellowhorselose = new QMovie (":/horsepopup/Resource_Files/horse/popup_lose/yellowhorselose.png");
    bluehorselose = new QMovie (":/horsepopup/Resource_Files/horse/popup_lose/bluehorselose.png");
    greenhorselose = new QMovie (":/horsepopup/Resource_Files/horse/popup_lose/greenhorselose.png");

    std::vector<QMovie*> allhorsewin {purhorsewin,redhorsewin,yellowhorsewin,bluehorsewin,greenhorsewin};
    std::vector<QMovie*> allhorselose {purhorselose,redhorselose,yellowhorselose,bluehorselose,greenhorselose};

    mainLayout = new QVBoxLayout(this);
    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf"); // Use the correct path to your font file
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QHBoxLayout *horseLayout = new QHBoxLayout;
    QFont labelFont(fontFamily, 10, QFont::Bold);
    const std::vector<Horse>& horses = m_horseRacing->getHorses();
    m_horseRacing->CalculateWinningOdds();
    m_horseRacing->CalculateBettingOdds();

    for (int i = 0; i < horses.size(); ++i) {
        QPixmap horseImage(horses[i].GetImagePath());
        QLabel *horseLabel = new QLabel;
        horseLabel->setPixmap(horseImage.scaled(200, 300));

        // Create a label for horse information
        QLabel *infoLabel = new QLabel(m_horseRacing->HorseInfo(i));
        infoLabel->setAlignment(Qt::AlignCenter);

        horseLabel->setFont(labelFont);
        infoLabel->setFont(labelFont);

        QVBoxLayout *horseInfoLayout = new QVBoxLayout;
        horseInfoLayout->addWidget(horseLabel);
        horseInfoLayout->addWidget(infoLabel);
        horseLayout->addLayout(horseInfoLayout);


    }

    QHBoxLayout *bettingChoiceLayout = new QHBoxLayout;
    for (size_t i = 0; i < horses.size(); ++i) {
        QString HorseNameNumber = "Horse " + QString::number(i+1);
        QLabel *HorseBetLabel = new QLabel(HorseNameNumber);
        QPushButton* bettingButton = new QPushButton(" ", this);
        bettingButton->setFont(labelFont);
        bettingButton->setStyleSheet("QPushButton {"
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
        bettingButton->setFixedSize(60,20);
        QFont HorseBetLabelFont(fontFamily, 8, QFont::Bold);
        HorseBetLabel->setFont(HorseBetLabelFont);
        if (i == 0) {
            connect(bettingButton, &QPushButton::clicked, this, &HorseBetWindow::betOnHorse1);
        } else if (i == 1) {
            connect(bettingButton, &QPushButton::clicked, this, &HorseBetWindow::betOnHorse2);
        } else if (i == 2) {
            connect(bettingButton, &QPushButton::clicked, this, &HorseBetWindow::betOnHorse3);
        } else if (i == 3) {
            connect(bettingButton, &QPushButton::clicked, this, &HorseBetWindow::betOnHorse4);
        } else if (i == 4) {
            connect(bettingButton, &QPushButton::clicked, this, &HorseBetWindow::betOnHorse5);
        }


        bettingChoiceLayout->addWidget(HorseBetLabel, 0, Qt::AlignCenter);
        bettingChoiceLayout->addWidget(bettingButton, 0, Qt::AlignCenter);
        mainLayout->addLayout(bettingChoiceLayout, 0);
    }
    QFont bet_label_labelFont(fontFamily, 13, QFont::Bold);
    bet_amount = 0;
    bet_label = new QLabel(this);
    bet_label->setStyleSheet("QLabel { color: black; }"); // Set the text color to green
    bet_label->setFont(bet_label_labelFont);
    bet_label->setGeometry(QRect(25, 500, 200, 50)); // Set this to wherever you want the label to appear
    bet_label->setText(QString::number(bet_amount));

    mainLayout->addLayout(horseLayout);

    QString balanceText = QString(" ");
    balanceLabel_fake = new QLabel(this);
    balanceLabel_fake->setAlignment(Qt::AlignLeft);
    balanceLabel_fake->setFont(labelFont);
    // balanceLabel->setGeometry(QRect(800, 500, 200, 50));
    mainLayout->addWidget(balanceLabel_fake);

    QFont balance_labelFont(fontFamily, 15, QFont::Bold);
    balanceLabel = new QLabel(this);
    balanceLabel->setStyleSheet("QLabel { color: black; }");
    balanceLabel->setFont(balance_labelFont);
    balanceLabel->setGeometry(QRect(830, 500, 200, 50));
    balanceLabel->setText("$ " + QString::number(balance_game2));





    asd = new QLabel(this);
    add = new QLabel(this);

    QHBoxLayout *balanceAndBetLayout = new QHBoxLayout;
    balanceAndBetLayout->addWidget(asd);
    balanceAndBetLayout->addWidget(add);
    mainLayout->addLayout(balanceAndBetLayout);

    connect(m_horseRacing, &HorseRacing::raceFinished, this, &HorseBetWindow::onRaceFinished);

    setWindowTitle("Bet Window");
    resize(1000, 600);
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);



    chip_1 = new ClickableLabel(this);
    chip_1_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_1.gif");
    chip_1->setMovie(chip_1_gif);
    chip_1->setGeometry(340, 500, 100, 50);
    chip_1_gif->start();
    connect(chip_1, &ClickableLabel::clicked, this, &HorseBetWindow::chip_1_add);

    chip_5 = new ClickableLabel(this);
    chip_5_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_5.gif");
    chip_5->setMovie(chip_5_gif);
    chip_5->setGeometry(390, 500, 100, 50);
    chip_5_gif->start();
    connect(chip_5, &ClickableLabel::clicked, this, &HorseBetWindow::chip_5_add);

    chip_10 = new ClickableLabel(this);
    chip_10_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_10_2.gif");
    chip_10->setMovie(chip_10_gif);
    chip_10->setGeometry(440, 500, 100, 50);
    chip_10_gif->start();
    connect(chip_10, &ClickableLabel::clicked, this, &HorseBetWindow::chip_10_add);

    chip_25 = new ClickableLabel(this);
    chip_25_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_25.gif");
    chip_25->setMovie(chip_25_gif);
    chip_25->setGeometry(490, 500, 100, 50);
    chip_25_gif->start();
    connect(chip_25, &ClickableLabel::clicked, this, &HorseBetWindow::chip_25_add);

    chip_50 = new ClickableLabel(this);
    chip_50_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_50.gif");
    chip_50->setMovie(chip_50_gif);
    chip_50->setGeometry(540, 500, 100, 50);
    chip_50_gif->start();
    connect(chip_50, &ClickableLabel::clicked, this, &HorseBetWindow::chip_50_add);

    chip_reject = new ClickableLabel(this);
    chip_reject_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_reject.gif");
    chip_reject->setMovie(chip_reject_gif);
    chip_reject->setGeometry(590, 500, 100, 50);
    chip_reject_gif->start();
    connect(chip_reject, &ClickableLabel::clicked, this, &HorseBetWindow::chip_reject_add);

    popup_win_label = new QLabel(this);
    popup_win_label->setGeometry(235, 130, 580, 333);
    // popup_win_label->setMovie(allhorsewin[1]);
    // allhorsewin[1]->start();
    // popup_win_label->show();

    popup_lose_label = new QLabel(this);
    popup_lose_label->setGeometry(235, 130, 580, 333);

    instuction_botton = new ClickableLabel(this);
    instuction_botton_gif = new QMovie(":/instructions/Resource_Files/instuction/instuction_botton/horseinstruc.png");
    instuction_botton->setMovie(instuction_botton_gif);
    instuction_botton->setGeometry(910, 565, 93, 34);
    instuction_botton_gif->start();
    connect(instuction_botton, &ClickableLabel::clicked, this, &HorseBetWindow::showInstructions);

    quitButton = new ClickableLabel(this);
    quitButton_gif = new QMovie(":/quitbutton/Resource_Files/quit_botton/horseexit.png");
    quitButton->setMovie(quitButton_gif);
    quitButton->setGeometry(1010, 565, 35, 34);
    quitButton_gif->start();
    connect(quitButton, &ClickableLabel::clicked, this, &HorseBetWindow::close);

}


void HorseBetWindow::betOnHorse1(){
    if (bet_amount <= 0 || bet_amount > balance_game2) {
        QMessageBox::warning(this, "Invalid bet", "Please enter a valid bet amount that does not exceed your balance.");
        return;
    }
    userHorseNum = 0;
    userBetRate = m_horseRacing->getBettingOdds()[userHorseNum].first;
    balance_game2 -= bet_amount;
    m_horseRacing->RunRace();
}
void HorseBetWindow::betOnHorse2(){
    if (bet_amount <= 0 || bet_amount > balance_game2) {
        QMessageBox::warning(this, "Invalid bet", "Please enter a valid bet amount that does not exceed your balance.");
        return;
    }

    userHorseNum = 1;
    userBetRate = m_horseRacing->getBettingOdds()[userHorseNum].first;
    balance_game2 -= bet_amount;
    m_horseRacing->RunRace();
}
void HorseBetWindow::betOnHorse3(){
    if (bet_amount <= 0 || bet_amount > balance_game2) {
        QMessageBox::warning(this, "Invalid bet", "Please enter a valid bet amount that does not exceed your balance.");
        return;
    }

    userHorseNum = 2;
    userBetRate = m_horseRacing->getBettingOdds()[userHorseNum].first;
    balance_game2 -= bet_amount;
    m_horseRacing->RunRace();
}
void HorseBetWindow::betOnHorse4() {
    if (bet_amount <= 0 || bet_amount > balance_game2) {
        QMessageBox::warning(this, "Invalid bet", "Please enter a valid bet amount that does not exceed your balance.");
        return;
    }

    userHorseNum = 3;
    userBetRate = m_horseRacing->getBettingOdds()[userHorseNum].first;
    balance_game2 -= bet_amount;
    m_horseRacing->RunRace();
}
void HorseBetWindow::betOnHorse5() {
    if (bet_amount <= 0 || bet_amount > balance_game2) {
        QMessageBox::warning(this, "Invalid bet", "Please enter a valid bet amount that does not exceed your balance.");
        return;
    }

    userHorseNum = 4;
    userBetRate = m_horseRacing->getBettingOdds()[userHorseNum].first;
    m_horseRacing->RunRace();
    balance_game2 -= bet_amount;
}

void HorseBetWindow::startRace() {
    // Remove the hat from the userHorse
    m_horseRacing->RunRace();
}



void HorseBetWindow::onRaceFinished(int winningHorseIndex) {
    qDebug() << userHorseNum;

    if (winningHorseIndex == userHorseNum) {
        // User's horse won
        int winnings = bet_amount * userBetRate;
        balance_game2 += winnings;
        // QMessageBox::information(this, "Race Finished", QString("You won! New balance: %1").arg(balance_game2));
        if(userHorseNum == 0){
            popup_win = new QMovie(":/horsepopup/Resource_Files/horse/popup_win/purhorsewin.png");
            popup_win_label->setMovie(popup_win);
            popup_win->start();
            popup_win_label->show();
        }else if (userHorseNum == 1){
            popup_win = new QMovie(":/horsepopup/Resource_Files/horse/popup_win/redhorsewin.png");
            popup_win_label->setMovie(popup_win);
            popup_win->start();
            popup_win_label->show();
        }else if (userHorseNum == 2){
            popup_win = new QMovie(":/horsepopup/Resource_Files/horse/popup_win/yellowhorsewin.png");
            popup_win_label->setMovie(popup_win);
            popup_win->start();
            popup_win_label->show();
        }else if (userHorseNum == 3){
            popup_win = new QMovie(":/horsepopup/Resource_Files/horse/popup_win/bluehorsewin.png");
            popup_win_label->setMovie(popup_win);
            popup_win->start();
            popup_win_label->show();
        }else {
            popup_win = new QMovie(":/horsepopup/Resource_Files/horse/popup_win/greenhorsewin.png");
            popup_win_label->setMovie(popup_win);
            popup_win->start();
            popup_win_label->show();
        }


    } else {
        // User's horse lost
        // QMessageBox::information(this, "Race Finished", QString("You lost. New balance: %1").arg(balance_game2));

        if(userHorseNum == 0){
            popup_lose = new QMovie(":/horsepopup/Resource_Files/horse/popup_lose/purhorselose.png");
            popup_lose_label->setMovie(popup_lose);
            popup_lose->start();
            popup_lose_label->show();
        }else if (userHorseNum == 1){
            popup_lose = new QMovie(":/horsepopup/Resource_Files/horse/popup_lose/redhorselose.png");
            popup_lose_label->setMovie(popup_lose);
            popup_lose->start();
            popup_lose_label->show();
        }else if (userHorseNum == 2){
            popup_lose = new QMovie(":/horsepopup/Resource_Files/horse/popup_lose/yellowhorselose.png");
            popup_lose_label->setMovie(popup_lose);
            popup_lose->start();
            popup_lose_label->show();
        }else if (userHorseNum == 3){
            popup_lose = new QMovie(":/horsepopup/Resource_Files/horse/popup_lose/bluehorselose.png");
            popup_lose_label->setMovie(popup_lose);
            popup_lose->start();
            popup_lose_label->show();
        }else {
            popup_lose = new QMovie(":/horsepopup/Resource_Files/horse/popup_lose/greenhorselose.png");
            popup_lose_label->setMovie(popup_lose);
            popup_lose->start();
            popup_lose_label->show();
        }


    }

    balanceLabel->setText("$ " + QString::number(balance_game2));

    QTimer::singleShot(5000, this, [this]() {close();});

}


void HorseBetWindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event); // Let the base class handle the event
    // Assuming balance has changed to newBalance
    emit gameClosed(this -> getBalance());
}

void HorseBetWindow::chip_10_add(){
    qDebug() << "Add 10";
    bet_amount += 10;
    bet_label->setText(QString::number(bet_amount));
}
void HorseBetWindow::chip_1_add(){
    qDebug() << "Add 1";
    bet_amount += 1;
    bet_label->setText(QString::number(bet_amount));
}
void HorseBetWindow::chip_5_add(){
    qDebug() << "Add 5";
    bet_amount += 5;
    bet_label->setText(QString::number(bet_amount));
}
void HorseBetWindow::chip_25_add(){
    qDebug() << "Add 25";
    bet_amount += 25;
    bet_label->setText(QString::number(bet_amount));
}
void HorseBetWindow::chip_50_add(){
    qDebug() << "Add 50";
    bet_amount += 50;
    bet_label->setText(QString::number(bet_amount));
}
void HorseBetWindow::chip_reject_add(){
    qDebug() << "chip_reject";
    bet_amount = 0;
    bet_label->setText(QString::number(bet_amount));
}

void HorseBetWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPixmap backgroundImage(":/horsegame/Resource_Files/horse/horsebg.png");
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QWidget::paintEvent(event);
}

void HorseBetWindow::showInstructions() {
    QWidget *instructionWidget = new QWidget;
    QLabel *instructionLabel = new QLabel(instructionWidget);
    QPixmap instructionPixmap(":/instructions/Resource_Files/instuction/instuction_horse.png");
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

