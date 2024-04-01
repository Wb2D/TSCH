QT += core gui sql
QT += winextras
QT += networkauth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBWorker\dbworker.cpp \
    ErrorTracker\errortracker.cpp \
    HammingCodeEngine\DataWorker\Converter\converter.cpp \
    HammingCodeEngine\DataWorker\NumberGenerator\numberGenerator.cpp \
    HammingCodeEngine\DataWorker\BitSequence\bitSequence.cpp \
    HammingCodeEngine\DataWorker\BitSequence\BitSequenceShell\bitSequenceShell.cpp \
    HammingCodeEngine\DataWorker\BigInteger\BigInteger.cpp \
    HammingCodeEngine\DataWorker\BigInteger\BigIntegerShell\bigIntegerShell.cpp \
    HammingCodeEngine\Encoder\HammingCode\Encoder74\Encoder74.cpp \
    HammingCodeEngine\Encoder\HammingCode\Encoder84\encoder84.cpp \
    HammingCodeEngine\Encoder\HammingCode\Encoder1511\encoder1511.cpp \
    HammingCodeEngine\Encoder\HammingCode\Encoder1611\encoder1611.cpp \
    HammingCodeEngine\Encoder\HammingCode\EncoderDecimal1511\encoderDecimal1511.cpp \
    HammingCodeEngine\Decoder\HammingCode\Decoder74\decoder74.cpp \
    HammingCodeEngine\Decoder\HammingCode\Decoder84\decoder84.cpp \
    HammingCodeEngine\Decoder\HammingCode\Decoder1511\decoder1511.cpp \
    HammingCodeEngine\Decoder\HammingCode\Decoder1611\decoder1611.cpp \
    HammingCodeEngine\Decoder\HammingCode\DecoderDecimal1511\decoderDecimal1511.cpp \
    Src\frame.cpp \
    Src\global.cpp \
    Src\notificationform.cpp \
    Src\dialogmail.cpp \
    main.cpp \
    Src\mainwindow.cpp \
    Src\studyform.cpp \
    Src\testform.cpp \

HEADERS += \
    DBWorker\dbworker.h \
    ErrorTracker\errortracker.h \
    HammingCodeEngine\DataWorker\Converter\converter.h \
    HammingCodeEngine\DataWorker\NumberGenerator\numberGenerator.h \
    HammingCodeEngine\DataWorker\BitSequence\bitSequence.h \
    HammingCodeEngine\DataWorker\BitSequence\BitSequenceShell/bitSequenceShell.h \
    HammingCodeEngine\DataWorker\BigInteger\BigInteger.h \
    HammingCodeEngine\DataWorker\BigInteger\BigIntegerShell/bigIntegerShell.h \
    HammingCodeEngine\Encoder\HammingCode\Encoder74\Encoder74.h \
    HammingCodeEngine\Encoder\HammingCode\Encoder84\encoder84.h \
    HammingCodeEngine\Encoder\HammingCode\Encoder1511\encoder1511.h \
    HammingCodeEngine\Encoder\HammingCode\Encoder1611\encoder1611.h \
    HammingCodeEngine\Encoder\HammingCode\EncoderDecimal1511\encoderDecimal1511.h \
    HammingCodeEngine\Decoder\HammingCode\Decoder74\decoder74.h \
    HammingCodeEngine\Decoder\HammingCode\Decoder84/decoder84.h \
    HammingCodeEngine\Decoder\HammingCode\Decoder1511/decoder1511.h \
    HammingCodeEngine\Decoder\HammingCode\Decoder1611/decoder1611.h \
    HammingCodeEngine\Decoder\HammingCode\DecoderDecimal1511\decoderDecimal1511.h \
    Include\clickableLabel.h \
    Include\global.h \
    Include\notificationform.h \
    Include\frame.h \
    Include\mainwindow.h \
    Include\studyform.h \
    Include\dialogmail.h \
    Include\testform.h \

FORMS += \
    Ui\notificationform.ui \
    Ui\dialogmail.ui \
    Ui\mainwindow.ui \
    Ui\studyform.ui \
    Ui\testform.ui \

# Default rules for deployment.
qnx: target.path = \tmp\$${TARGET}\bin
else: unix:!android: target.path = \opt\$${TARGET}\bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources\resource.qrc \

DISTFILES += \
    Scripts\sendMail.exe \
    config.json \
