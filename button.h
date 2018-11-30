#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLabel>
#include <QTimer>

enum ButtonState {
    Normal,
    Hover,
    Pressed,
    Disabled
};

struct StyleState {
    QColor  border_color;
    QColor  background_color;
    QColor  text_color;
};

class Button : public QWidget
{
    Q_OBJECT
private:
    int border_width = 2;

    ButtonState state;
    struct StyleState style_state[4];

    QLabel *text = nullptr;
    int animation_button_pos_line = 0;
    QTimer *timer;
    const int SPEED_ANIMAT = 50;

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void changeEvent(QEvent *event);

public:
    explicit Button(QWidget *parent = nullptr);
    explicit Button(QString text, QWidget *parent = nullptr);
    void init(QString text);
    void setText(QString text);
    void setState(ButtonState state);
    void setBorderWidth(int border_width);
    void setStyleState(ButtonState state, struct StyleState style_state);

signals:
    void clicked();

public slots:
};

#endif // BUTTON_H
