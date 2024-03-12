#include <gui.hpp>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QKeyEvent>

class SpeedTestWindow : public QWidget{
    protected:
        void keyPressEvent(QKeyEvent *event) override {
            qDebug() << "Key pressed: " << event->text();
            QWidget::keyPressEvent(event);
        }
};

int QtGuiModule::start_gui(){
    QApplication a(this->argc, this->argv);
    a.setStyleSheet("QPushButton {border: 1px solid #ffffff;} * {text-align: center; color: white;}");

    SpeedTestWindow window;
    window.setFixedSize(300, 300);
    window.setStyleSheet("background-color:#020122;");

    QStackedWidget mainWidget;

    QWidget menuScreen;
    QVBoxLayout menuLayout;
    
    QLabel Title("Speed Typist");
    Title.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    QFont font = Title.font();
    font.setPointSize(24);
    Title.setFont(font);

    QLabel HighScore("High Score : " + QString::fromStdString(logic_interface.load_highscore()));
    HighScore.setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    QPushButton startButton("Start");
    QPushButton quitButton("Quit");

    menuLayout.addWidget(&Title);
    menuLayout.addWidget(&HighScore);
    menuLayout.addWidget(&startButton);
    menuLayout.addWidget(&quitButton);
    menuScreen.setLayout(&menuLayout);
    mainWidget.addWidget(&menuScreen);

    QWidget speedTypistScreen;
    QVBoxLayout speedTypistLayout;
    QHBoxLayout currentStatsLayout;
    QPushButton backtoMenuButton("Go to menu screen");

    QLabel wordPerMinute("10 WPM");
    wordPerMinute.setMaximumHeight(30);
    wordPerMinute.setAlignment(Qt::AlignHCenter);
    QLabel countDown("60 s");
    countDown.setMaximumHeight(30);
    countDown.setAlignment(Qt::AlignHCenter);
    QLabel characterPerMinute("20 CPM");
    characterPerMinute.setMaximumHeight(30);
    characterPerMinute.setAlignment(Qt::AlignHCenter);

    QLabel currentTarget("<font color='yellow'>Hell</font>o World!");
    currentTarget.setAlignment(Qt::AlignCenter);
    currentTarget.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont currentTargetFont = currentTarget.font();
    currentTargetFont.setPointSize(currentTarget.width() / currentTarget.text().length());
    currentTarget.setFont(currentTargetFont);

    backtoMenuButton.setFocusPolicy(Qt::NoFocus);
    speedTypistLayout.addWidget(&backtoMenuButton);

    currentStatsLayout.addWidget(&wordPerMinute);
    currentStatsLayout.addWidget(&countDown);
    currentStatsLayout.addWidget(&characterPerMinute);
    speedTypistLayout.addLayout(&currentStatsLayout);
    speedTypistLayout.addWidget(&currentTarget);

    speedTypistScreen.setLayout(&speedTypistLayout);

    mainWidget.addWidget(&speedTypistScreen);

    QObject::connect(&quitButton, &QPushButton::clicked, [&](){
        QApplication::quit();
    });

    QObject::connect(&startButton, &QPushButton::clicked, [&](){
        mainWidget.setCurrentIndex(1);
    });
    QObject::connect(&backtoMenuButton, &QPushButton::clicked, [&](){
        mainWidget.setCurrentIndex(0);
    });

    QVBoxLayout mainLayout;
    mainLayout.addWidget(&mainWidget);
    window.setLayout(&mainLayout);

    window.show();
    return a.exec();
}

void QtGuiModule::stop_gui(){
    std::cout<<"stopping gui"<<std::endl;
}

void QtGuiModule::switch_to_menu_screen(){
    std::cout<<"Switch to main menu" << std::endl;
}

void QtGuiModule::switch_to_test_screen(){
    std::cout<<"Switch to test screen" << std::endl;
}

std::unique_ptr<GuiModule> GuiModuleFactory::createModule(GuiModuleType type, int argc, char* argv[], GuiLogicStruct logic_interface)
{
    return std::unique_ptr<GuiModule>(new QtGuiModule(argc, argv, logic_interface));
}
