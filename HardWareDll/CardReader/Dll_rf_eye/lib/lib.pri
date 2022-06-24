INCLUDEPATH += $$PWD

win32{

    INCLUDEPATH += $$PWD/win/include

    contains(QT_ARCH, i386) {
        message("mw_rf_eye:win32:32-bit:-lmwhrf_bj")
        LIBS += -L$$PWD/win/lib/x86 -lmwhrf_bj
    } else {
        message("mw_rf_eye:win32:64-bit:-l")
#        LIBS += -L$$PWD/win/lib/x64 -lavcodec
#        LIBS += -L$$PWD/win/lib/x64/HCNetSDKCom -lAnalyzeData
    }
}

unix:!macx{

#    INCLUDEPATH += $$PWD/win/include

    contains(QT_ARCH, i386) {
        message("mw_rf_eye:linux:32-bit:")
#        LIBS += -L$$PWD/win/lib/x86 -lcomest32
    } else {
        message("mw_rf_eye:linux:64-bit:")
#        LIBS += -L$$PWD/win/lib/x64 -lavcodec
#        LIBS += -L$$PWD/win/lib/x64/HCNetSDKCom -lAnalyzeData
    }
}
