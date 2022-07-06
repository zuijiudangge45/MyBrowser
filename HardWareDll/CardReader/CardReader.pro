TEMPLATE = subdirs
SUBDIRS += \
    CardReaderDonsee \
    Dll_rf_eye \
    ReaderDonsee \
    ReaderMWRFEYE

win32{
    SUBDIRS -= \
        CardReaderDonsee \
        Dll_rf_eye \
}
