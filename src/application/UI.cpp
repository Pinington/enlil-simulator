#include "application/UI.h"

UI::UI(QWidget *parent) {
    QHBoxLayout* topLayout = new QHBoxLayout(this);

    QPushButton* redButton = new QPushButton("Red");
    QPushButton* blueButton = new QPushButton("Blue");
    
    this->setFixedHeight(40);

    QPalette p = QPalette();
    p.setColor(QPalette::Window, QColor(12, 100, 255, 255));

    this->setAutoFillBackground(true);
    this->setPalette(p);

    topLayout->addWidget(redButton);
    topLayout->addWidget(blueButton);
    topLayout->addStretch();
}