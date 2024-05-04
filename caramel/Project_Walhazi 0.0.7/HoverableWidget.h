#ifndef HOVERABLEWIDGET_H
#define HOVERABLEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QDate>
class HoverableWidget : public QWidget {
    Q_OBJECT

signals:
    void entered();
    void left();

protected:
    void enterEvent(QEvent *event) override {
        Q_UNUSED(event);
        emit entered();
    }

    void leaveEvent(QEvent *event) override {
        Q_UNUSED(event);
        emit left();
    }
};

#endif // HOVERABLEWIDGET_H
