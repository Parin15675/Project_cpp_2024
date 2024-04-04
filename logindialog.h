#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

    int userloginbalance;

private slots:
    void onLoginClicked();

protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void userAuthenticated(const QString& username, int balance);

    void dialogClosed();
};

#endif // LOGINDIALOG_H
