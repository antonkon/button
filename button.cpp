/***************************
 * !!! Я написал комментарии на Русском, НО
 * я понимаю, что коментарии должны быть на Английском. !!!
 *
 *
 *
 *
 *
 *
 *
 ****************************/

#include "button.h"
#include <iostream>
#include <QPen>
#include <QPainter>


Button::Button(QWidget *parent) : QWidget(parent) {
    init("Button");
}

Button::Button(QString text, QWidget *parent) : QWidget(parent) {
    init(text);
}

/*
    Инициализация экземпляра кнопки
*/
void Button::init(QString text) {
    // Установка начального текста кнопки
    this->text = new QLabel(text, this);

    // Создание таймера анмации
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(this->SPEED_ANIMAT);

    // Задание стилий по умолчанию
    setStyleState(ButtonState::Normal, {
        QColor(100, 100, 100),
        QColor(230, 230, 230),
        QColor(0, 0, 0)
    });
    setStyleState(ButtonState::Hover, {
        QColor(20, 220, 20),
        QColor(230, 230, 230),
        QColor(20, 220, 20)
    });
    setStyleState(ButtonState::Pressed, {
        QColor(220, 20, 20),
        QColor(230, 230, 230),
        QColor(220, 20, 20)
    });
    setStyleState(ButtonState::Disabled, {
        QColor(0, 0, 0),
        QColor(230, 230, 230),
        QColor(0, 0, 0)
    });
    // Установка начального состояния
    setState(ButtonState::Normal);
}


/*
    Установка состояния кнопки (объекта)
*/
void Button::setState(ButtonState state) {
    this->state = state;
}

/*
    Установка стиля состояния
*/
void Button::setStyleState(ButtonState state, struct StyleState style_state) {
    switch (state) {
    case Normal:
        this->style_state[0] = style_state;
        break;
    case Hover:
        this->style_state[1] = style_state;
        break;
    case Pressed:
        this->style_state[2] = style_state;
        break;
    case Disabled:
        this->style_state[3] = style_state;
        break;
    }
}

/*
    Установка текста кнопки
*/
void Button::setText(QString text) {
    this->text->setText(text);
}

/*
    Установка размера рамки
*/
void Button::setBorderWidth(int border_width) {
    this->border_width = border_width;
}

/*
    Обработка наведения и нажатия мыши
*/
void Button::mousePressEvent(QMouseEvent * event) {
    this->setState(ButtonState::Pressed);
}
void Button::mouseReleaseEvent(QMouseEvent *event) {
    this->setState(ButtonState::Normal);
    emit clicked();
}
void Button::enterEvent(QEvent *event) {
    this->setState(ButtonState::Hover);
}
void Button::leaveEvent(QEvent *event) {
    this->setState(ButtonState::Normal);
}
// Обработка изменения состояния виджета через setEnabled()
void Button::changeEvent(QEvent *event) {
    if(event->type() == QEvent::EnabledChange) {
        if(!this->isEnabled()) {
            this->timer->stop();
            this->setState(ButtonState::Disabled);
            repaint();
        } else {
            this->timer->start(this->SPEED_ANIMAT);
            this->setState(ButtonState::Normal);
        }
    }
}

/*
    Отрисовка кнопки
*/
void Button::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // Выбор цвета рамки и фона относительно текущего состояния
    painter.setPen(QPen(this->style_state[state].border_color, this->border_width, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(this->style_state[state].background_color, Qt::SolidPattern));

    // Отрисовка кнопки
    if(this->border_width == 0) {
        painter.drawRect(-1, -1, this->width() + 1, this->height() + 1);
    } else {
        painter.drawRect(this->border_width,
                         this->border_width,
                         this->width() - this->border_width - 1,
                         this->height() - this->border_width - 1);
    }

    // Отрисовка анимированной линии если кнопка на отключена
    // (не в состоянии Disabled)
//    std::cout << state << std::endl;
    if(state == ButtonState::Disabled)
        return;
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap));
    // Для состояния Normal
    if(this->animation_button_pos_line >= this->width())
        this->animation_button_pos_line = this->border_width;
    // Для состояния Hover
    if(this->animation_button_pos_line < this->border_width)
        this->animation_button_pos_line = this->width() - this->border_width;

    painter.drawLine(this->animation_button_pos_line, this->border_width+1, this->animation_button_pos_line, this->height() - this->border_width);

    // Вычисление следующего положения линии
    switch (state) {
        case ButtonState::Normal:
            this->animation_button_pos_line += 2;
            break;

        case ButtonState::Hover:
            this->animation_button_pos_line -= 2;
            break;

        case ButtonState::Pressed:
            break;
    }


    this->text->repaint();
}
