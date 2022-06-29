TEMPLATE = subdirs

SUBDIRS += \
    PluginCardReaderDonsee \
    PluginCardReaderMwRfEye \
    PluginIOServerKNaDM244 \
    PluginTest
win32{
}else{
SUBDIRS -= \
    PluginCardReaderDonsee \
    PluginCardReaderMwRfEye
}
