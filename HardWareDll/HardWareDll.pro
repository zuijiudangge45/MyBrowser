TEMPLATE = subdirs

SUBDIRS += HardWareTest
SUBDIRS += CardReader
SUBDIRS += IOServer

win32{

}else{
SUBDIRS -= CardReader
}
