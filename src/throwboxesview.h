#ifndef THROWBOXESVIEW_H
#define THROWBOXESVIEW_H
#include "authui.h"
#include <QListWidget>
#include <QPushButton>


class ThrowBoxesView : public authUI
{
    Q_OBJECT
private:
    QListWidget *boxesList;
    QPushButton *throwButton;
public:
    ThrowBoxesView(User* usr, QWidget *parent = 0);
protected:
    bool authorized() const override;
    void authorizedUI() override;
    void closeEvent(QCloseEvent *event) override;
public slots:
    void enableThrowButton();
    void throwBox();
};

#endif // THROWBOXESVIEW_H
