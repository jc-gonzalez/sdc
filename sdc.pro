#======================================================================
# SDC - Structured Data Container
#======================================================================
# Project file
# Author: J C Gonzalez - 2015
#======================================================================

TEMPLATE = subdirs
CONFIG  += ordered
SUBDIRS  = \
    json \
    src \
    tests

src.depends = json
tests.depends = src

OTHER_FILES += \
    defaults.pri
