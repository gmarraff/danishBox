#include "gamecontroller.h"
#include <QMessageBox>
#include "danishbox.h"
#include "kiddobox.h"
#include "sewingbox.h"
#include "admin.h"
#include "kiddo.h"
#include "admin.h"
#include "grandma.h"
#include "boxview.h"
#include "item.h"
#include "danish.h"
#include "quisquilia.h"
#include "sewingtool.h"

User* GameController::loggedUser = 0;
GameController::GameController(Box* box, QObject *parent) : QObject(parent), managedBox(box)
{

}
QString GameController::sadIconPath(){
    return "icons/reactions/sad.ico";
}
QString GameController::typeHelper(Box::Type tp){
    switch(tp){
    case(Box::Amoeba):
        return "vuota";
    case(Box::Danish):
        return "di danesi";
    case(Box::Sewing):
        return "di attrezzi da cucito";
    case(Box::Quisquilia):
        return "di giocattoli";
    default:
		return "non valida";
    }
    return "indefinita";
}

void GameController::react(){
    Box* openedBox = open(new Box(*managedBox));
    bool reaction =  ((dynamic_cast<::Admin*>(loggedUser)) ||
                      openedBox->type() == Box::Amoeba ||
                      (dynamic_cast<::Kiddo*>(loggedUser) && (dynamic_cast<::DanishBox*>(openedBox) || dynamic_cast<::KiddoBox*>(openedBox))) ||
                      (dynamic_cast<::Grandma*>(loggedUser) && (dynamic_cast<::DanishBox*>(openedBox) || dynamic_cast<::SewingBox*>(openedBox)))
    );
    if(reaction){
        BoxView *bv = new BoxView(openedBox, loggedUser, this);
        bv->show();
    }else
        sadReact(openedBox->type());
}
void GameController::sadReact(Box::Type tp) const{
    QMessageBox sadReact;
    sadReact.setIconPixmap(GameController::sadIconPath());
    sadReact.setWindowTitle("Oh no!");
    sadReact.setText("Hai aperto una scatola " + GameController::typeHelper(tp) + "!");
    sadReact.exec();
}
Box* GameController::open(Box* box){
	box->setOpened();
	box->recoveItems();
	if(box->empty()) return box;
    if(dynamic_cast<::Danish*>(box->itemAt(0))) return new DanishBox(box);
    if(dynamic_cast<::SewingTool*>(box->itemAt(0))) return new SewingBox(box);
    if(dynamic_cast<::Quisquilia*>(box->itemAt(0))) return new KiddoBox(box);
	return box;
}
