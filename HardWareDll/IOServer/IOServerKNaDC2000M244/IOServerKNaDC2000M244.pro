QT -= gui
QT += network

TEMPLATE = lib
DEFINES += IOSERVERKNADC2000M244_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ioserverknadc2000m244.cpp

HEADERS += \
    ioserverknadc2000m244.h

INCLUDEPATH += \
    ../include

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#Qt Creator默认情况下把所有的编译中间文件都生成到debug和release文件夹里。
#如下这样，编译时生成的临时文件就按不同类型分类放到项目的构建文件夹中了。
UI_DIR  = Obj/Guiwo
MOC_DIR = Obj/Moc
OBJECTS_DIR = Obj/Obj

win32:{
    contains(QT_ARCH, i386):{           #x86
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../../bin/IOServer/win/x86/release
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../../bin/IOServer/win/x86/debug
        }
    }
    else:{
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../../bin/cardReader/win/x64/release
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../../bin/cardReader/win/x64/debug
        }
    }
}

unix:!macx{
    contains(QT_ARCH, i386):{           #x86
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../bin/linux/x86/release
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../bin/linux/x86/debug
#            LIBS += -L$$PWD/../bin/linux/x86/debug/ -lPluginCenter
        }
    }
    else:{                              #x64
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../../bin/IOServer/linux/x64/release
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../../bin/IOServer/linux/x64/debug
        }
    }
}
