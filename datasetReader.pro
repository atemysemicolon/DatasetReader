TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


#OpenCV stuff
LIBS += `pkg-config opencv --libs`

#OpenMP stuff
QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

#Enabling c++ '11 standard
QMAKE_CXXFLAGS += -std=c++11

#Enabling TBB
QMAKE_CXXFLAGS += -ltbb

#Enable Boost stuff
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_thread -lboost_system

SOURCES += \
    main.cpp
