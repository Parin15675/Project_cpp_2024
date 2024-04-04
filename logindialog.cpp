#include "logindialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>
#include <QFontDatabase>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    this->resize(350, 350);
    this->setStyleSheet("background-color: #333333;");


    usernameLineEdit = new QLineEdit(this);
    // usernameLineEdit->setPlaceholderText("Username");
    usernameLineEdit->setAlignment(Qt::AlignCenter);

    passwordLineEdit = new QLineEdit(this);
    // passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setAlignment(Qt::AlignCenter);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);

    // QFormLayout *layout = new QFormLayout();
    // layout->addRow(usernameLineEdit);
    // layout->addRow(passwordLineEdit);

    passwordLineEdit->setGeometry(50,220,270,30);
    usernameLineEdit->setGeometry(50,115,270,30);
    loginButton->setGeometry(115,300,130,45);

    // Load the custom font
    int fontId = QFontDatabase::addApplicationFont(":/font/Resource_Files/retro_computer_personal_use.ttf"); // Use the correct path to your font file
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily, 10, QFont::Bold);

    usernameLineEdit->setFont(font);
    passwordLineEdit->setFont(font);
    loginButton->setFont(font);

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

    usernameLineEdit->setStyleSheet(lineEditStyle);
    passwordLineEdit->setStyleSheet(lineEditStyle);
    loginButton->setStyleSheet(buttonStyle);

    // layout->addWidget(loginButton);

    // setLayout(layout);
    setWindowTitle("Login");
    setModal(true);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}


QString LoginDialog::getUsername() const {
    return usernameLineEdit->text();
}

QString LoginDialog::getPassword() const {
    return passwordLineEdit->text();
}

void LoginDialog::onLoginClicked() {
    QString username = getUsername().trimmed();
    QString password = getPassword();

    QFile file("user_data.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Unable to open user data file.");
        return;
    }

    QTextStream in(&file);
    bool loginSuccess = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() >= 3) {
            QString fileUsername = fields.at(0).trimmed();
            QString filePassword = fields.at(1);
            if (username == fileUsername && password == filePassword) {
                userloginbalance = fields.at(2).toInt();
                loginSuccess = true;
                break;
            }
        }
    }
    file.close();

    if (loginSuccess) {
        emit userAuthenticated(username, userloginbalance);
        accept();
    } else {
        QMessageBox::warning(this, "Login failed", "Invalid username or password.");
    }
}



void LoginDialog::closeEvent(QCloseEvent *event) {
    emit dialogClosed(); // Emit the signal indicating the dialog was closed
    QDialog::closeEvent(event); // Call the base class implementation
}

void LoginDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap backgroundImage(":/mainmenu/Resource_Files/loginwindownobox.png");
    if (!backgroundImage.isNull()) {
        QPixmap scaledImg = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPoint center((this->width() - scaledImg.width()) / 2, (this->height() - scaledImg.height()) / 2);
        painter.drawPixmap(center, scaledImg);
    } else {
        qDebug() << "Failed to load the background image.";
    }
    QDialog::paintEvent(event); // Call the base class implementation
}

