#include "SignUpDialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDatabase>
#include <QDir>
#include <QDebug>
#include <QPainter>

SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent) {
    this->resize(400, 380);
    this->setStyleSheet("background-color: #333333;");

    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    balanceLineEdit = new QLineEdit(this);
    signUpButton = new QPushButton("Sign Up", this);


    passwordLineEdit->setGeometry(70,175,270,30);
    usernameLineEdit->setGeometry(70,65,270,30);
    balanceLineEdit->setGeometry(70,285,270,30);
    signUpButton->setGeometry(135,325,130,40);

    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf"); // Adjust with your font path
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 10, QFont::Bold);

    QString lineEditStyle = "QLineEdit { "
                            "border: 2px solid #f4ac24; "
                            "border-radius: 5px; "
                            "padding: 5px; "
                            "background-color: #f8b459; "
                            "color: black; "
                            "}";
    QString buttonStyle = "QPushButton { "
                          "color: white; "
                          "background-color: #f4ac24; "
                          "border-radius: 5px; "
                          "padding: 5px; "
                          "} "
                          "QPushButton:hover { "
                          "background-color: #f8b459; "
                          "} "
                          "QPushButton:pressed { "
                          "background-color: #dc942c; "
                          "}";

    usernameLineEdit->setFont(font);
    passwordLineEdit->setFont(font);
    balanceLineEdit->setFont(font);
    signUpButton->setFont(font);

    usernameLineEdit->setStyleSheet(lineEditStyle);
    passwordLineEdit->setStyleSheet(lineEditStyle);
    balanceLineEdit->setStyleSheet(lineEditStyle);
    signUpButton->setStyleSheet(buttonStyle);

    setWindowTitle("Sign Up");
    setModal(true);

    // Connect the sign-up button click event
    connect(signUpButton, &QPushButton::clicked, this, &SignUpDialog::onSignUpClicked);
}


void SignUpDialog::onSignUpClicked() {
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();
    QString balanceStr = balanceLineEdit->text().trimmed();


    if (!username.isEmpty() && !password.isEmpty() && !balanceStr.isEmpty()) {

        bool ok;
        double balance = balanceStr.toDouble(&ok);

        if (!ok) {
            QMessageBox::warning(this, "Error", "Please enter a valid number for the balance.");
            balanceLineEdit->clear();
            balanceLineEdit->setFocus();
            return;
        }

        QFile file("user_data.txt");
        qDebug() << "Trying to access user_data.txt at:" << QDir::current().absoluteFilePath(file.fileName());

        // Check if the username already exists
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            bool userExists = false;
            QString line;

            while (in.readLineInto(&line)) {
                QStringList parts = line.split(",");
                if (parts.length() > 0 && parts[0] == username) {
                    userExists = true;
                    break;
                }
            }
            file.close();

            if (userExists) {
                QMessageBox::warning(this, "Error", "Username already exists.");

                usernameLineEdit->clear();
                usernameLineEdit->setFocus();
                return;
            }
        } else {
            QMessageBox::warning(this, "Error", "Unable to open file for reading.");
            return;
        }



        if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream out(&file);
            out << username << "," << password << "," << balanceStr << "\n";
            file.close();
            QMessageBox::warning(this, "Sucess", "Account Succesfully created");
            emit userAuthenticated(username,  static_cast<int>(balance));
            accept();

        } else {
            QMessageBox::warning(this, "Error", "Unable to open file for writing.");

        }
    } else {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
    }
}


void SignUpDialog::closeEvent(QCloseEvent *event) {
    emit dialogClosed(); // Emit the signal indicating the dialog was closed
    QDialog::closeEvent(event); // Call the base class implementation
}

void SignUpDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap backgroundImage(":/mainmenu/Resource_Files/signupwindownobox.png");
    if (!backgroundImage.isNull()) {
        QPixmap scaledImg = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        // Calculate the top-left position to center the image in the widget
        QPoint center((this->width() - scaledImg.width()) / 2, (this->height() - scaledImg.height()) / 2);
        painter.drawPixmap(center, scaledImg);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QDialog::paintEvent(event); // Call the base class implementation
}

