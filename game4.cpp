#include "game4.h"
#include <QPainter>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <QPushButton>
#include "ClickableLabel.h"
#include <QFontDatabase>
#include <QVBoxLayout>


Game4::Game4(int& balance, QWidget *parent) :  QWidget(parent), balance(balance), multiplier(1.0), gameActive(false) {
    this->setWindowTitle("Game 4 - Crash");
    this->resize(1000, 600);
    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    balance_game4 = balance;
    bet_amount = 0;

    plane_label = new QLabel(this);
    multiplier_label = new QLabel(this);
    bomb_label = new QLabel(this);
    betButton = new QPushButton("Start", this);
    cashoutButton = new QPushButton("Cash Out", this);

    plane = new QMovie(":/game4/Resource_Files/Crash/plane_100.gif");
    plane_label->setGeometry(180, 410,100,100);
    plane_label->setMovie(plane);
    plane->start();

    bomb = new QMovie(":/game4/Resource_Files/Crash/bomb_2.gif");
    bomb_label->setGeometry(150, 50,151,100);
    bomb_label->setMovie(bomb);

    cashOutLabel = new QLabel(this);
    cashOutLabel->hide();
    cashOutLabel->setStyleSheet("QLabel { color: green; }");
    QFont labelFont(fontFamily, 16, QFont::Bold);
    cashOutLabel->setFont(labelFont);
    betButton->setFont(labelFont);
    betButton->setStyleSheet("QPushButton {"
                             "    color: white;"
                             "    background-color: orange;"
                             "    border-radius: 5px;"
                             "    padding: 5px;"
                             "}"
                             "QPushButton:hover {"
                             "    background-color: darkorange;"
                             "}"
                             "QPushButton:pressed {"
                             "    background-color: lightorange;"
                             "}");

    QFont labelFont_cash(fontFamily, 9, QFont::Bold);
    cashoutButton->setFont(labelFont_cash);
    cashoutButton->setStyleSheet("QPushButton {"
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

    QFont labelFont_cash_out(fontFamily, 40 , QFont::Bold);
    cashOutLabel->setGeometry(QRect(640, 200, 500, 500));
    cashOutLabel->setFont(labelFont_cash_out);

    QFont balance_labelFont(fontFamily, 12, QFont::Bold);
    balance_label = new QLabel(this);
    balance_label->setStyleSheet("QLabel { color: black; }");
    balance_label->setFont(balance_labelFont);
    balance_label->setGeometry(QRect(810, 3, 200, 50));
    balance_label->setText("$ " + QString::number(balance));

    bet_label = new QLabel(this);
    bet_label->setStyleSheet("QLabel { color: black; }");
    bet_label->setFont(labelFont);
    bet_label->setGeometry(QRect(18, 450, 200, 50));
    bet_label->setText(QString::number(bet_amount));

    multiplier_label->setGeometry(770, 510, 200, 100);

    QFont labelFont_n(fontFamily, 40, QFont::Bold);
    multiplier_label->setFont(labelFont_n);
    updateMultiplierDisplay();

    betButton->setGeometry(60, 545, 100, 50);
    cashoutButton->setGeometry(170, 545, 100, 50);
    cashoutButton->setEnabled(false);

    connect(betButton, &QPushButton::clicked, this, &Game4::startGame);
    connect(cashoutButton, &QPushButton::clicked, this, &Game4::cashOut);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game4::updateGame);

    chip_1 = new ClickableLabel(this);
    chip_1_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_1.gif");
    chip_1->setMovie(chip_1_gif);
    chip_1->setGeometry(300, 545, 100, 50);
    chip_1_gif->start();
    connect(chip_1, &ClickableLabel::clicked, this, &Game4::chip_1_add);

    chip_5 = new ClickableLabel(this);
    chip_5_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_5.gif");
    chip_5->setMovie(chip_5_gif);
    chip_5->setGeometry(350, 545, 100, 50);
    chip_5_gif->start();
    connect(chip_5, &ClickableLabel::clicked, this, &Game4::chip_5_add);

    chip_10 = new ClickableLabel(this);
    chip_10_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_10_2.gif");
    chip_10->setMovie(chip_10_gif);
    chip_10->setGeometry(400, 545, 100, 50);
    chip_10_gif->start();
    connect(chip_10, &ClickableLabel::clicked, this, &Game4::chip_10_add);

    chip_25 = new ClickableLabel(this);
    chip_25_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_25.gif");
    chip_25->setMovie(chip_25_gif);
    chip_25->setGeometry(450, 545, 100, 50);
    chip_25_gif->start();
    connect(chip_25, &ClickableLabel::clicked, this, &Game4::chip_25_add);

    chip_50 = new ClickableLabel(this);
    chip_50_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_50.gif");
    chip_50->setMovie(chip_50_gif);
    chip_50->setGeometry(500, 545, 100, 50);
    chip_50_gif->start();
    connect(chip_50, &ClickableLabel::clicked, this, &Game4::chip_50_add);

    chip_reject = new ClickableLabel(this);
    chip_reject_gif = new QMovie(":/chips/Resource_Files/Casino_image/table/chip_reject.gif");
    chip_reject->setMovie(chip_reject_gif);
    chip_reject->setGeometry(550, 545, 100, 50);
    chip_reject_gif->start();
    connect(chip_reject, &ClickableLabel::clicked, this, &Game4::chip_reject_add);

    instuction_botton = new ClickableLabel(this);
    instuction_botton_gif = new QMovie(":/instructions/Resource_Files/instuction/instuction_botton/crashinstruc.png");
    instuction_botton->setMovie(instuction_botton_gif);
    instuction_botton->setGeometry(48, 5, 114, 38);
    instuction_botton_gif->start();
    connect(instuction_botton, &ClickableLabel::clicked, this, &Game4::showInstructions);

    quitButton = new ClickableLabel(this);
    quitButton_gif = new QMovie(":/quitbutton/Resource_Files/quit_botton/crashexit.png");
    quitButton->setMovie(quitButton_gif);
    quitButton->setGeometry(5, 5, 41, 38);
    quitButton_gif->start();
    connect(quitButton, &ClickableLabel::clicked, this, &Game4::close);

}

void Game4::startGame() {
    if (bet_amount > 0 && bet_amount <= balance_game4){
        if (gameActive) return;

        chip_1->setEnabled(false);
        chip_5->setEnabled(false);
        chip_10->setEnabled(false);
        chip_25->setEnabled(false);
        chip_50->setEnabled(false);
        chip_reject->setEnabled(false);

        multiplier = 1.0;
        gameActive = true;
        betButton->setEnabled(false);
        cashoutButton->setEnabled(true);
        plane->jumpToFrame(0); // Reset the plane animation if needed
        gameTimer->start(100); // Update every 0.1 seconds


        balance_game4 = balance_game4 - bet_amount;
        balance_label->setStyleSheet("QLabel { color: red; }");
        balance_label->setText("$ " + QString::number(balance_game4));
        QTimer::singleShot(1000, this, [this]() {balance_label->setStyleSheet("QLabel { color: black; }");});
    }
    else{
        qDebug() << "Invalid Bet";
    }
}

void Game4::cashOut() {
    if (!gameActive) return;
    multiplier_new = multiplier / 10.0;
    double payout = bet_amount * multiplier_new;
    balance_game4 += payout;

    QString message = QString("+ $%2").arg(payout, 0, 'f', 2);
    qDebug() << message;
    balance_label->setStyleSheet("QLabel { color: green; }");
    balance_label->setText("$ " + QString::number(balance_game4));
    QTimer::singleShot(1000, this, [this]() {balance_label->setStyleSheet("QLabel { color: black; }");});
    cashOutLabel->setText(message);
    cashOutLabel->show();
    cashoutButton->setEnabled(false);

}
void Game4::updateGame() {
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> dist;
    multiplier += dist(rng);

    // Set the initial position of the plane
    const int startX = 180;
    const int startY = 410;
    const double speed = 3.5;

    int currentX = startX + static_cast<int>(multiplier * speed);
    int currentY = startY - static_cast<int>(multiplier * speed);

    // Ensure that the plane stays within the window bounds
    currentX = std::min(currentX, this->width() - plane_label->width());
    currentY = std::max(currentY, 0);

    plane_label->move(currentX, currentY);

    updateMultiplierDisplay();

    if (QRandomGenerator::global()->bounded(100) < 2.1) { // Crash condition
        gameTimer->stop();
        qDebug() << "Game crashed at multiplier:" << multiplier;

        // Stop the plane movie and hide the label
        plane->stop();
        plane_label->hide();
        plane_label->update(); // Force the label to update its appearance

        // Position the bomb label at the crash site and show the bomb animation
        bomb_label->move(plane_label->pos()); // Position bomb at last plane position
        bomb_label->setMovie(bomb);
        bomb_label->show();
        bomb->start();
        bomb_label->update(); // Force the label to update its appearance

        // Update the UI immediately
        QCoreApplication::processEvents();

        cashoutButton->setEnabled(false);
        QTimer::singleShot(3000, this, &Game4::resetGame);

    }
}

void Game4::updateMultiplierDisplay() {
    multiplier_new = multiplier / 10.0;
    multiplier_label->setText(QString("%1x").arg(multiplier_new, 0, 'f', 2));

}


void Game4::resetGame() {

    qDebug() << "reset game";
    gameActive = false;
    betButton->setEnabled(true);
    cashoutButton->setEnabled(false);

    bomb->stop();
    bomb_label->hide();

    cashOutLabel->hide();
    multiplier_label->setText(QString("0 x"));

    plane_label->move(180, 410);
    plane->start();
    plane_label->show();

    balance_label->setText("$ " + QString::number(balance_game4));
    bet_amount = 0;
    bet_label->setText(QString::number(bet_amount));

    chip_1->setEnabled(true);
    chip_5->setEnabled(true);
    chip_10->setEnabled(true);
    chip_25->setEnabled(true);
    chip_50->setEnabled(true);
    chip_reject->setEnabled(true);
}

Game4::~Game4() {
    delete plane;
    delete gameTimer;
}

void Game4::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPixmap backgroundImage(":/game4/Resource_Files/Crash/bg_2.jpeg");
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QWidget::paintEvent(event);
}

void Game4::chip_10_add(){
    qDebug() << "Add 10";
    if(balance > 0 || bet_amount <= balance){
        bet_amount += 10;
        bet_label->setText(QString::number(bet_amount));}
}
void Game4::chip_1_add(){
    qDebug() << "Add 1";
    if(balance > 0 || bet_amount <= balance){
        bet_amount += 1;
        bet_label->setText(QString::number(bet_amount));}
}
void Game4::chip_5_add(){
    qDebug() << "Add 5";
    if(balance > 0 || bet_amount <= balance){
        bet_amount += 5;
        bet_label->setText(QString::number(bet_amount));}
}
void Game4::chip_25_add(){
    qDebug() << "Add 25";
    if(balance > 0 || bet_amount <= balance_game4){
        bet_amount += 25;
        bet_label->setText(QString::number(bet_amount));}
}
void Game4::chip_50_add(){
    qDebug() << "Add 50";
    if(balance > 0 || bet_amount <= balance){
        bet_amount += 50;
        bet_label->setText(QString::number(bet_amount));}
}
void Game4::chip_reject_add(){
    qDebug() << "chip_reject";
    bet_amount = 0;
    bet_label->setText(QString::number(bet_amount));
}

void Game4::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    gameTimer->stop();
    qDebug() << "Game crashed at multiplier:" << multiplier;

    // Stop the plane movie and hide the label
    plane->stop();
    plane_label->hide();
    plane_label->update();

    // Position the bomb label at the crash site and show the bomb animation
    bomb_label->move(plane_label->pos()); // Position bomb at last plane position
    bomb_label->setMovie(bomb);
    bomb_label->show();
    bomb->start();
    bomb_label->update(); // Force the label to update its appearance

    // Update the UI immediately
    QCoreApplication::processEvents();

    cashoutButton->setEnabled(false);
    // Delay resetGame call by 5 seconds (5000 milliseconds)
    QTimer::singleShot(3000, this, &Game4::resetGame);

    // Assuming balance has changed to newBalance
    emit gameClosed(this -> getBalance());
}

void Game4::showInstructions() {
    QWidget *instructionWidget = new QWidget;
    QLabel *instructionLabel = new QLabel(instructionWidget);
    QPixmap instructionPixmap(":/instructions/Resource_Files/instuction/instuction_crash.png");

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
