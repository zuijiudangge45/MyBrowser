TEMPLATE = subdirs

SUBDIRS += HardWareTest
SUBDIRS += IOServer

win32:{
    contains(QT_ARCH, i386):{           #(win32-x86)
        SUBDIRS += CardReader
    }
}
