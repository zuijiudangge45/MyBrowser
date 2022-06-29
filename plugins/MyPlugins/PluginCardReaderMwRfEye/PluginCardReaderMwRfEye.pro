TEMPLATE = lib
CONFIG += plugin
TARGET = pluginCardReaderMwRfEye

HEADERS += \
    plugincardreadermwrfeye.h

SOURCES += \
    plugincardreadermwrfeye.cpp

DISTFILES += \
    pluginmetadata.json

INCLUDEPATH += \
    $$PWD/../drivers/cardReader/mw_rfeye/win/x86/include

#Qt Creator默认情况下把所有的编译中间文件都生成到debug和release文件夹里。
#如下这样，编译时生成的临时文件就按不同类型分类放到项目的构建文件夹中了。
UI_DIR  = Obj/Gui
MOC_DIR = Obj/Moc
OBJECTS_DIR = Obj/Obj


win32:{
    contains(QT_ARCH, i386):{            #86
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../bin/win/x86/release/plugins
            LIBS += -L$$PWD/../drivers/cardReader/mw_rfeye/win/x86/lib/release/ -lDll_rf_eye
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../bin/win/x86/debug/plugins
            LIBS += -L$$PWD/../drivers/cardReader/mw_rfeye/win/x86/lib/debug -lDll_rf_eye

        }
    }
    else:{                              #x64
        CONFIG(release, debug|release):{
            DESTDIR = $$PWD/../bin/win/x64/release/plugins
            LIBS += -L$$PWD/../drivers/cardReader_mwRfEye/lib/win/x64/release/ -lDll_rf_eye
        }
        else:CONFIG(debug, debug|release):{
            DESTDIR = $$PWD/../bin/win/x64/debug/plugins
            LIBS += -L$$PWD/../drivers/cardReader_mwRfEye/lib/win/x64/debug/ -lDll_rf_eye

        }
    }
}
