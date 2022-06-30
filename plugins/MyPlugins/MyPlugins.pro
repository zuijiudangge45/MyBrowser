TEMPLATE = subdirs

SUBDIRS += \
    PluginCardReaderDonsee \
    PluginCardReaderMwRfEye \
    PluginIOServerKNaDA2KDDA0A0 \
    PluginIOServerKNaDM244 \
    PluginTest
win32{
}else{
SUBDIRS -= \
    PluginCardReaderDonsee \
    PluginCardReaderMwRfEye
}
