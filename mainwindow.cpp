#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "signupdialog.h"
#include "ClickableLabel.h"
#include <QThread>
#include <qmessagebox.h>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QPainter>
#include <QFontDatabase>
#include <QInputDialog>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf"); // Use the correct path to your font file
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    this->setWindowTitle("PPM888");
    this->resize(600, 800);

    QMessageBox msgBox;
    msgBox.setWindowTitle("PPM888");
    msgBox.setText("WELCOME        TO        PPM888");
    msgBox.setFont(QFont(fontFamily, 12, QFont::Bold));
    msgBox.setStyleSheet("color: white; background-color: #44008a;");
    QPushButton *signUpButton = msgBox.addButton("Sign Up", QMessageBox::AcceptRole);
    signUpButton->setFont(QFont(fontFamily, 12, QFont::Bold));
    signUpButton->setStyleSheet("QPushButton {"
                                "    color: white;"
                                "    background-color: #28A745;"
                                "    border-radius: 5px;"
                                "    padding: 5px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #218838;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: #1C7430;"
                                "}");
    QPushButton *loginButton = msgBox.addButton("Log In", QMessageBox::RejectRole);
    loginButton->setFont(QFont(fontFamily, 12, QFont::Bold));
    loginButton->setStyleSheet("QPushButton {"
                               "    color: white;"
                               "    background-color: #0078D7;"
                               "    border-radius: 5px;"
                               "    padding: 5px;"
                               "}"
                               "QPushButton:hover {"
                               "    background-color: #005EA6;"
                               "}"
                               "QPushButton:pressed {"
                               "    background-color: #003A70;"
                               "}");
    int ret = msgBox.exec();


    if (ret == QMessageBox::Cancel){
        QMessageBox::information(nullptr, "Dialog Closed", "The message dialog was closed.");
        QTimer::singleShot(0, this, [this]() {
            this->close();
            QApplication::exit(0);
        });
        return;
    }

    if (msgBox.clickedButton() == signUpButton) {
        SignUpDialog signUpDialog;
        connect(&signUpDialog, &SignUpDialog::dialogClosed, this, [this]() {
            QMessageBox::information(nullptr, "Dialog Closed", "The signup dialog was closed.");
            QTimer::singleShot(0, this, [this]() {
                this->close();
                QApplication::exit(0);
            });
        });
        connect(&signUpDialog, &SignUpDialog::userAuthenticated, this, &MainWindow::setUser);
        if (signUpDialog.exec() == QDialog::Rejected) {
            QCoreApplication::quit();
            return;
        }
    }

    if (msgBox.clickedButton() == loginButton) {
        LoginDialog loginDialog;
        connect(&loginDialog, &LoginDialog::dialogClosed, this, [this]() {
            QMessageBox::information(nullptr, "Dialog Closed", "The login dialog was closed.");
            QTimer::singleShot(0, this, [this]() {
                this->close();
                QApplication::exit(0);
            });
        });
        connect(&loginDialog, &LoginDialog::userAuthenticated, this, &MainWindow::setUser);
        if (loginDialog.exec() == QDialog::Rejected) {
            QCoreApplication::quit();
            return;
        }
    }


}



MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initUI() {
    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf"); // Use the correct path to your font file
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    QFont balanceFont(fontFamily, 12, QFont::Bold);
    balanceLabel = new QLabel(this);
    balanceLabel->setStyleSheet("QLabel { color: white; }");
    balanceLabel->setFont(balanceFont);
    balanceLabel->setGeometry(QRect(450, 50, 200, 30));
    balanceLabel->setText(QString("$ %1").arg(userbalance));

    QFont usernameFont(fontFamily, 12, QFont::Bold);
    usernameLabel = new QLabel(this);
    usernameLabel->setStyleSheet("QLabel { color: white; }");
    usernameLabel->setFont(usernameFont);
    usernameLabel->setGeometry(QRect(450, 10, 200, 30));
    usernameLabel->setText(QString("%1").arg(userName));

    baccarat_button_label = new ClickableLabel(this);
    baccarat_button = new QMovie(":/mainmenu/Resource_Files/botton_game/baccarat_button.gif");
    baccarat_button_label->setGeometry(150, 210, 300, 120);
    baccarat_button_label->setMovie(baccarat_button);
    baccarat_button->start();

    connect(baccarat_button_label, &ClickableLabel::clicked, this, &MainWindow::openGame1);

    horse_racing_botton_label = new ClickableLabel(this);
    horse_racing_botton = new QMovie(":/mainmenu/Resource_Files/botton_game/horse_racing_button.gif");
    horse_racing_botton_label->setGeometry(150, 340, 300, 120);
    horse_racing_botton_label->setMovie(horse_racing_botton);
    horse_racing_botton->start();

    connect(horse_racing_botton_label, &ClickableLabel::clicked, this, &MainWindow::runHorseRacingGame);

    penelto_botton_label = new ClickableLabel(this);
    penelto_botton = new QMovie(":/mainmenu/Resource_Files/botton_game/penalto_button.gif");
    penelto_botton_label->setGeometry(150, 470, 300, 120);
    penelto_botton_label->setMovie(penelto_botton);
    penelto_botton->start();

    connect(penelto_botton_label, &ClickableLabel::clicked, this, &MainWindow::openGame3);


    crash_botton_label = new ClickableLabel(this);
    crash_botton = new QMovie(":/mainmenu/Resource_Files/botton_game/crash_button.gif");
    crash_botton_label->setGeometry(150, 600, 300, 120);
    crash_botton_label->setMovie(crash_botton);
    crash_botton->start();

    connect(crash_botton_label, &ClickableLabel::clicked, this, &MainWindow::openGame4);

    exit_botton_label = new ClickableLabel(this);
    exit_botton = new QMovie(":/mainmenu/Resource_Files/botton_exit.png");
    exit_botton_label->setGeometry(10, 15, 41, 38);
    exit_botton_label->setMovie(exit_botton);
    exit_botton->start();
    connect(exit_botton_label, &ClickableLabel::clicked, this, &MainWindow::close);

    add_botton_label = new ClickableLabel(this);
    add_botton = new QMovie(":/mainmenu/Resource_Files/botton_add.png");
    add_botton_label->setGeometry(400, 47, 41, 38);
    add_botton_label->setMovie(add_botton);
    add_botton->start();
    connect(add_botton_label, &ClickableLabel::clicked, this, &MainWindow::onAddBalanceClicked);

    // player = new QMediaPlayer(this);
    // playlist = new QMediaPlaylist(player);

    // playlist->addMedia(QUrl::fromLocalFile("C:/path/to/your/music.mp3")); // replace with your path to music file
    // playlist->setPlaybackMode(QMediaPlaylist::Loop); // loop the playlist

    // player->setPlaylist(playlist);
    // player->setVolume(50); // volume level from 0 to 100
    // player->play();

    team_botton_label = new ClickableLabel(this);
    team_botton = new QMovie(":/mainmenu/Resource_Files/botton_team_member.png");
    team_botton_label->setGeometry(50, 15, 41, 38);
    team_botton_label->setMovie(team_botton);
    team_botton->start();
    connect(team_botton_label, &ClickableLabel::clicked, this, &MainWindow::showInstructions);


}

void MainWindow::setUsername(const QString& username) {
    userName = username;
}

void MainWindow::setBalance(const int balance) {
    userbalance = balance;
}


void MainWindow::setUser(const QString& username, int balance) {
    setUsername(username);
    setBalance(balance);
    loadUserData();
    initUI();
}

void MainWindow::loadUserData() {
    // Assuming user data is stored in a format like: username,password,balance
    QFile file("user_data.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() >= 3 && fields[0] == userName) {
                userbalance = fields[2].toInt(); // Update balance based on file
                break;
            }
        }
        file.close();
    }
}



void MainWindow::openGame1() {
    game1Window = new Game1(userbalance);
    connect(game1Window, &Game1::gameClosed, this, &MainWindow::updateBalance);
    game1Window->show();

}

void MainWindow::runHorseRacingGame()
{
    HorseRacing* horseRace = nullptr;
    horseRace = new HorseRacing();
    HorseBetWindow* horsebetWindow = new HorseBetWindow(userbalance, horseRace);
    connect(horsebetWindow, &HorseBetWindow::gameClosed, this, &MainWindow::updateBalanceForHorseBet);
    horsebetWindow->show();
}


void MainWindow::openGame3() {
    game3Window = new Game3(userbalance);
    connect(game3Window, &Game3::gameClosed, this, &MainWindow::updateBalance);
    game3Window->show();
}

void MainWindow::openGame4() {
    game4Window = new Game4(userbalance);
    connect(game4Window, &Game4::gameClosed, this, &MainWindow::updateBalance);
    game4Window->show();
}

void MainWindow::updateBalanceForHorseBet(int newBalance) {
    userbalance = newBalance;
    balanceLabel->setText(QString("$ %1").arg(userbalance));
    updateUserDataFile(userName, userbalance);

}

void MainWindow::updateBalance(int newBalance) {
    userbalance = newBalance;
    balanceLabel->setText(QString("$ %1").arg(userbalance));
    updateUserDataFile(userName, userbalance);

}

void MainWindow::updateUserDataFile(const QString& username, int newBalance) {
    // Temporary container for storing user data lines
    QStringList userDataLines;
    QFile file("user_data.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');
            if (fields.size() >= 3) {
                // If the current line is for our user, update the balance
                if (fields[0].trimmed() == username) {
                    fields[2] = QString::number(newBalance); // Update balance
                    line = fields.join(',');
                }
            }
            userDataLines.append(line);
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Unable to open file for reading.");
        return;
    }

    // Write updated data back to the file
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        foreach (const QString &line, userDataLines) {
            out << line << "\n";
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Unable to open file for writing.");
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPixmap backgroundImage(":/mainmenu/Resource_Files/mainmenu_bg_2.png");
    if (!backgroundImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), backgroundImage);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QWidget::paintEvent(event);
}

void MainWindow::onAddBalanceClicked() {
    bool ok;
    double amount = QInputDialog::getDouble(this, tr("Add Balance"),
                                            tr("Amount:"), 0, 0, 10000, 2, &ok);
    if (ok && amount > 0) {
        userbalance += amount;
        balanceLabel->setText(QString("$ %1").arg(userbalance));
        updateUserDataFile(userName, userbalance);
        QMessageBox::information(this, "Balance Updated", QString("Your balance has been updated by %1.").arg(amount));
    }
}


void MainWindow::showInstructions() {
    qDebug() << "it works";


    QWidget *instructionWidget = new QWidget;
    QLabel *instructionLabel = new QLabel(instructionWidget);
    QPixmap instructionPixmap(":/mainmenu/Resource_Files/TEAM_MEMBER.png");

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

