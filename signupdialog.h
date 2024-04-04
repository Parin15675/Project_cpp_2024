// SignUpDialog.h

#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QFile>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class SignUpDialog : public QDialog {
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);

private slots:
    void onSignUpClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *balanceLineEdit;
    QPushButton *signUpButton;

protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void userAuthenticated(const QString& username, int balance);

    void dialogClosed();
};

#endif // SIGNUPDIALOG_H
