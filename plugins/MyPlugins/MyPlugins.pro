TEMPLATE = subdirs

SUBDIRS += \
    PluginIOServerKNaDA2KDDA0A0 \
    PluginIOServerKNaDM244 \
    PluginTest
win32:{
    contains(QT_ARCH, i386):{           #(win32-x86)
        SUBDIRS += \
            PluginCardReaderDonsee \
            PluginCardReaderMwRfEye
    }
}
