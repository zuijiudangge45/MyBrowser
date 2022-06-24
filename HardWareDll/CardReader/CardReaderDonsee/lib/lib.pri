INCLUDEPATH += $$PWD

win32{

    INCLUDEPATH += $$PWD/win/include

    contains(QT_ARCH, i386) {
        message("donsee:win32:32-bit:-lcomest32")
        LIBS += -L$$PWD/win/lib/x86 -lcomest32
    } else {
        message("donsee:win32:64-bit:")
#        LIBS += -L$$PWD/win/lib/x64 -lavcodec
#        LIBS += -L$$PWD/win/lib/x64/HCNetSDKCom -lAnalyzeData
    }
}

unix:!macx{

#    INCLUDEPATH += $$PWD/win/include

    contains(QT_ARCH, i386) {
        message("donsee:linux:32-bit:")
#        LIBS += -L$$PWD/win/lib/x86 -lcomest32
    } else {
        message("donsee:linux:64-bit:")
#        LIBS += -L$$PWD/win/lib/x64 -lavcodec
#        LIBS += -L$$PWD/win/lib/x64/HCNetSDKCom -lAnalyzeData
    }
}
