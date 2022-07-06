QT += network
TEMPLATE = lib
CONFIG += plugin
TARGET = pluginIOServerKNaDM244
QMAKE_LFLAGS += -Wl,-rpath=./plugins:./

HEADERS += \
    pluginioserverknadm244.h

SOURCES += \
    pluginioserverknadm244.cpp

DISTFILES += \
    pluginmetadata.json

INCLUDEPATH += \
    $$PWD/../drivers/knadc2000m244/include

#Qt Creator默认情况下把所有的编译中间文件都生成到debug和release文件夹里。
#如下这样，编译时生成的临时文件就按不同类型分类放到项目的构建文件夹中了。
UI_DIR  = Obj/Gui
MOC_DIR = Obj/Moc
OBJECTS_DIR = Obj/Obj


win32:{
    contains(QT_ARCH, i386):{            #86
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../bin/win/x86/release/plugins
            LIBS += -L$$PWD/../drivers/knadc2000m244/lib/win/x86/release -lIOServerKNaDC2000M244
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../bin/win/x86/debug/plugins
            LIBS += -L$$PWD/../drivers/knadc2000m244/lib/win/x86/debug -lIOServerKNaDC2000M244
        }
    }
    else:{                              #x64
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../bin/win/x64/release/plugins
            LIBS += -L$$PWD/../drivers/knadc2000m244/lib/win/x64/release -lIOServerKNaDC2000M244
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../bin/win/x64/debug/plugins
            LIBS += -L$$PWD/../drivers/knadc2000m244/lib/win/x64/debug -lIOServerKNaDC2000M244

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
            DESTDIR = $$PWD/../bin/linux/x64/release/plugins
            LIBS += -L$$PWD/../drivers/knadc2000m244/lib/linux/x64/release -lIOServerKNaDC2000M244
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../bin/linux/x64/debug/plugins
            LIBS += -L$$PWD/../drivers/knadc2000m244/lib/linux/x64/debug -lIOServerKNaDC2000M244
        }
    }
}
