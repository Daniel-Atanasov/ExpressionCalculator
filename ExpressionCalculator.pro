TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L"$$(PATH_LIB)"
INCLUDEPATH += $$(PATH_INCLUDE)
win32:LIBS += -luser32 -lComctl32 -lGdi32 -lSciLexer -lScintilla

# Ascii mode
DEFINES -= UNICODE
DEFINES -= _UNICODE

SOURCES += main.cpp \
    init.cpp \
    tokenizer.cpp

HEADERS += \
    init.h \
    tokenizer.h
