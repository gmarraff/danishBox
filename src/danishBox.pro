        #-------------------------------------------------
    #
    # Project created by QtCreator 2017-08-17T10:23:45
    #
    #-------------------------------------------------

    QT       += core gui

    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

    TARGET = danishBox
    TEMPLATE = app

    # The following define makes your compiler emit warnings if you use
    # any feature of Qt which as been marked as deprecated (the exact warnings
    # depend on your compiler). Please consult the documentation of the
    # deprecated API in order to know how to port your code away from it.
    DEFINES += QT_DEPRECATED_WARNINGS

    # You can also make your code fail to compile if you use deprecated APIs.
    # In order to do so, uncomment the following line.
    # You can also select to disable deprecated APIs only up to a certain version of Qt.
    # DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050501    # disables all the APIs deprecated before Qt 5.5.1

     CONFIG += C++11

    SOURCES += jsonmanager.cpp \
	item.cpp \
	danish.cpp \
	quisquilia.cpp \
	sewingtool.cpp \
	box.cpp \
	danishbox.cpp \
	sewingbox.cpp \
	kiddobox.cpp \
	user.cpp \
    	kiddo.cpp \
    	grandma.cpp \
    	admin.cpp \
	main.cpp\
        welcomeform.cpp \
        loginform.cpp \
        signupform.cpp \
        clickablelabel.cpp \
	menuview.cpp \
        authui.cpp \
        adminui.cpp \
	adminzone.cpp \
	adminzonecontroller.cpp \
	gamecontroller.cpp \
	boxgame.cpp \
	boxview.cpp \
        newboxview.cpp \
	throwboxesview.cpp \
	newquisquiliaview.cpp \
	newsewingview.cpp \
	newitemview.cpp

    HEADERS  += jsonmanager.h \
	danish.h \
	quisquilia.h \
	sewingtool.h \
	box.h \
	danishbox.h \
	sewingbox.h \
	kiddobox.h \
	user.h \
	kiddo.h \
	grandma.h \
	admin.h \
	item.h \
	welcomeform.h \
        loginform.h \
        signupform.h \
        clickablelabel.h \
	menuview.h \
        authui.h \
        adminui.h \
        adminzone.h \
	adminzonecontroller.h \
	gamecontroller.h \
	boxgame.h \
	boxview.h \
        newboxview.h \
	throwboxesview.h \
	newquisquiliaview.h \
	newsewingview.h \
	newitemview.h
