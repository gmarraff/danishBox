#ifndef NEWSEWINGVIEW_H
#define NEWSEWINGVIEW_H
#include "authui.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class NewSewingView : public authUI
{
    Q_OBJECT
private:
    QLineEdit *codeLine, *nameLine, *utilityLine;
    QPushButton *insertButton;
    QLabel *resultLabel;
protected:
    bool authorized() const override;
    void authorizedUI() override;
    void notAuthorizedUI() override;
public:
    explicit NewSewingView(User* usr, QWidget *parent = 0);

signals:

public slots:
    void insertSewingTool();
};

#endif // NEWSEWINGVIEW_H
