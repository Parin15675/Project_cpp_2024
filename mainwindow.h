#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "game1.h"
#include "horsebetwindow.h"
#include "game3.h"
#include "game4.h"
#include <QMovie>
// #include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int& getBalance() {return userbalance;}

    void setUsername(const QString& username);
    void setBalance(int newBalance);

private slots:
    void openGame1();
    void openGame3();
    void openGame4();

    void runHorseRacingGame();

    void updateBalance(int newBalance);
    void updateBalanceForHorseBet(int newBalance);

    void setUser(const QString& username, int balance);
    void onAddBalanceClicked();
    void showInstructions();


private:
    Ui::MainWindow *ui;
    QPushButton *game1Button;
    QPushButton *game2Button;
    QPushButton *game3Button;
    QPushButton *game4Button;
    QPushButton *quitButton;
    Game1 *game1Window = nullptr;
    Game3 *game3Window = nullptr;
    Game4 *game4Window = nullptr;
    QLabel *balanceLabel;
    QLabel *usernameLabel;

    QString userName; // Store the logged-in username
    int userbalance;

    void initUI();
    void loadUserData();

    void updateUserDataFile(const QString& username, int newBalance);


    QMovie *penelto_botton;
    QMovie *baccarat_button;
    QMovie *horse_racing_botton;
    QMovie *crash_botton;
    QMovie *exit_botton;
    QMovie *add_botton;
    QMovie *team_botton;

    ClickableLabel *penelto_botton_label;
    ClickableLabel *baccarat_button_label;
    ClickableLabel *horse_racing_botton_label;
    ClickableLabel *crash_botton_label;
    ClickableLabel *exit_botton_label;
    ClickableLabel *add_botton_label;
    ClickableLabel *team_botton_label;

    // QMediaPlayer *backgroundMusicPlayer;
    // QMediaPlayer *player;
    // QMediaPlaylist *playlist;

protected:
    void paintEvent(QPaintEvent *event) override;


};
#endif // MAINWINDOW_H

