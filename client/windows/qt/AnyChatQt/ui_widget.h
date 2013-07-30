/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue Feb 1 11:29:28 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *loginBtn;
    QPushButton *initBtn;
    QPushButton *enterRoomBtn;
    QTextEdit *m_ctrlEditLog;
    QLineEdit *IplineEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *PortLineEdit;
    QLabel *label_3;
    QLineEdit *UserLineEdit;
    QLabel *label_4;
    QLineEdit *PwdLineEdit;
    QLabel *label_5;
    QLineEdit *RoomIDlineEdit;
    QCheckBox *VADcheckBox;
    QCheckBox *AECcheckBox;
    QCheckBox *AGCcheckBox;
    QCheckBox *NScheckBox;
    QGroupBox *User0groupBox;
    QGroupBox *User1groupBox;
    QGroupBox *User2groupBox;
    QGroupBox *User3groupBox;
    QPushButton *leaveRoomBtn;
    QPushButton *logoutBtn;
    QPushButton *releaseBtn;
    QPushButton *sendFileBtn;
    QProgressBar *Speak0ProgressBar;
    QProgressBar *Speak1ProgressBar;
    QProgressBar *Speak2ProgressBar;
    QProgressBar *Speak3ProgressBar;
    QLabel *RecordState0;
    QLabel *RecordState3;
    QLabel *RecordState2;
    QLabel *RecordState1;
    QPushButton *TransbufBtn;
    QPushButton *VideopropertyBtn;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *VideocomboBox;
    QComboBox *AudiocomboBox;
    QSlider *OutVolumeChangeSlider;
    QSlider *InVolumeChangeSlider;
    QPushButton *RefreshBtn;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *fileStatuslabel;
    QPushButton *sendMessageBtn;
    QLineEdit *messagelineEdit;
    QPushButton *Videoctrl0Btn;
    QLabel *label_10;
    QPushButton *Audioctrl0Btn;
    QPushButton *Recordctrl0Btn;
    QPushButton *Snapshotctrl0Btn;
    QPushButton *Snapshotctrl1Btn;
    QPushButton *Audioctrl1Btn;
    QPushButton *Videoctrl1Btn;
    QPushButton *Recordctrl1Btn;
    QPushButton *Snapshotctrl2Btn;
    QPushButton *Audioctrl2Btn;
    QPushButton *Videoctrl2Btn;
    QPushButton *Recordctrl2Btn;
    QPushButton *Snapshotctrl3Btn;
    QPushButton *Audioctrl3Btn;
    QPushButton *Videoctrl3Btn;
    QPushButton *Recordctrl3Btn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(770, 638);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setCursor(QCursor(Qt::ArrowCursor));
        loginBtn = new QPushButton(Widget);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setGeometry(QRect(410, 110, 91, 23));
        initBtn = new QPushButton(Widget);
        initBtn->setObjectName(QString::fromUtf8("initBtn"));
        initBtn->setGeometry(QRect(410, 70, 75, 23));
        enterRoomBtn = new QPushButton(Widget);
        enterRoomBtn->setObjectName(QString::fromUtf8("enterRoomBtn"));
        enterRoomBtn->setGeometry(QRect(410, 150, 91, 23));
        m_ctrlEditLog = new QTextEdit(Widget);
        m_ctrlEditLog->setObjectName(QString::fromUtf8("m_ctrlEditLog"));
        m_ctrlEditLog->setGeometry(QRect(20, 70, 381, 211));
        m_ctrlEditLog->viewport()->setProperty("cursor", QVariant(QCursor(Qt::SizeVerCursor)));
        m_ctrlEditLog->setReadOnly(true);
        IplineEdit = new QLineEdit(Widget);
        IplineEdit->setObjectName(QString::fromUtf8("IplineEdit"));
        IplineEdit->setGeometry(QRect(41, 10, 101, 20));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 11, 16, 16));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 11, 41, 16));
        PortLineEdit = new QLineEdit(Widget);
        PortLineEdit->setObjectName(QString::fromUtf8("PortLineEdit"));
        PortLineEdit->setGeometry(QRect(220, 10, 41, 20));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 45, 54, 12));
        UserLineEdit = new QLineEdit(Widget);
        UserLineEdit->setObjectName(QString::fromUtf8("UserLineEdit"));
        UserLineEdit->setGeometry(QRect(70, 42, 71, 20));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 45, 31, 16));
        PwdLineEdit = new QLineEdit(Widget);
        PwdLineEdit->setObjectName(QString::fromUtf8("PwdLineEdit"));
        PwdLineEdit->setGeometry(QRect(210, 42, 71, 20));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(300, 45, 51, 16));
        RoomIDlineEdit = new QLineEdit(Widget);
        RoomIDlineEdit->setObjectName(QString::fromUtf8("RoomIDlineEdit"));
        RoomIDlineEdit->setGeometry(QRect(350, 42, 31, 20));
        VADcheckBox = new QCheckBox(Widget);
        VADcheckBox->setObjectName(QString::fromUtf8("VADcheckBox"));
        VADcheckBox->setGeometry(QRect(420, 260, 111, 16));
        VADcheckBox->setChecked(true);
        AECcheckBox = new QCheckBox(Widget);
        AECcheckBox->setObjectName(QString::fromUtf8("AECcheckBox"));
        AECcheckBox->setGeometry(QRect(540, 260, 111, 16));
        AECcheckBox->setChecked(true);
        AGCcheckBox = new QCheckBox(Widget);
        AGCcheckBox->setObjectName(QString::fromUtf8("AGCcheckBox"));
        AGCcheckBox->setGeometry(QRect(420, 290, 111, 16));
        AGCcheckBox->setChecked(true);
        NScheckBox = new QCheckBox(Widget);
        NScheckBox->setObjectName(QString::fromUtf8("NScheckBox"));
        NScheckBox->setGeometry(QRect(540, 290, 111, 16));
        NScheckBox->setChecked(true);
        User0groupBox = new QGroupBox(Widget);
        User0groupBox->setObjectName(QString::fromUtf8("User0groupBox"));
        User0groupBox->setGeometry(QRect(9, 390, 170, 140));
        User1groupBox = new QGroupBox(Widget);
        User1groupBox->setObjectName(QString::fromUtf8("User1groupBox"));
        User1groupBox->setGeometry(QRect(190, 390, 170, 140));
        User2groupBox = new QGroupBox(Widget);
        User2groupBox->setObjectName(QString::fromUtf8("User2groupBox"));
        User2groupBox->setGeometry(QRect(370, 390, 170, 140));
        User3groupBox = new QGroupBox(Widget);
        User3groupBox->setObjectName(QString::fromUtf8("User3groupBox"));
        User3groupBox->setGeometry(QRect(550, 390, 170, 140));
        leaveRoomBtn = new QPushButton(Widget);
        leaveRoomBtn->setObjectName(QString::fromUtf8("leaveRoomBtn"));
        leaveRoomBtn->setGeometry(QRect(530, 150, 91, 23));
        logoutBtn = new QPushButton(Widget);
        logoutBtn->setObjectName(QString::fromUtf8("logoutBtn"));
        logoutBtn->setGeometry(QRect(530, 110, 91, 23));
        releaseBtn = new QPushButton(Widget);
        releaseBtn->setObjectName(QString::fromUtf8("releaseBtn"));
        releaseBtn->setGeometry(QRect(530, 70, 91, 23));
        sendFileBtn = new QPushButton(Widget);
        sendFileBtn->setObjectName(QString::fromUtf8("sendFileBtn"));
        sendFileBtn->setGeometry(QRect(410, 190, 75, 23));
        Speak0ProgressBar = new QProgressBar(Widget);
        Speak0ProgressBar->setObjectName(QString::fromUtf8("Speak0ProgressBar"));
        Speak0ProgressBar->setGeometry(QRect(10, 530, 171, 23));
        Speak0ProgressBar->setValue(24);
        Speak1ProgressBar = new QProgressBar(Widget);
        Speak1ProgressBar->setObjectName(QString::fromUtf8("Speak1ProgressBar"));
        Speak1ProgressBar->setGeometry(QRect(190, 530, 171, 23));
        Speak1ProgressBar->setValue(24);
        Speak2ProgressBar = new QProgressBar(Widget);
        Speak2ProgressBar->setObjectName(QString::fromUtf8("Speak2ProgressBar"));
        Speak2ProgressBar->setGeometry(QRect(370, 530, 171, 23));
        Speak2ProgressBar->setValue(24);
        Speak3ProgressBar = new QProgressBar(Widget);
        Speak3ProgressBar->setObjectName(QString::fromUtf8("Speak3ProgressBar"));
        Speak3ProgressBar->setGeometry(QRect(550, 530, 171, 23));
        Speak3ProgressBar->setValue(24);
        RecordState0 = new QLabel(Widget);
        RecordState0->setObjectName(QString::fromUtf8("RecordState0"));
        RecordState0->setGeometry(QRect(140, 560, 16, 16));
        RecordState3 = new QLabel(Widget);
        RecordState3->setObjectName(QString::fromUtf8("RecordState3"));
        RecordState3->setGeometry(QRect(680, 560, 16, 16));
        RecordState2 = new QLabel(Widget);
        RecordState2->setObjectName(QString::fromUtf8("RecordState2"));
        RecordState2->setGeometry(QRect(500, 560, 16, 16));
        RecordState1 = new QLabel(Widget);
        RecordState1->setObjectName(QString::fromUtf8("RecordState1"));
        RecordState1->setGeometry(QRect(320, 560, 16, 16));
        TransbufBtn = new QPushButton(Widget);
        TransbufBtn->setObjectName(QString::fromUtf8("TransbufBtn"));
        TransbufBtn->setGeometry(QRect(530, 190, 75, 23));
        VideopropertyBtn = new QPushButton(Widget);
        VideopropertyBtn->setObjectName(QString::fromUtf8("VideopropertyBtn"));
        VideopropertyBtn->setGeometry(QRect(410, 230, 75, 23));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 330, 54, 12));
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 365, 54, 12));
        VideocomboBox = new QComboBox(Widget);
        VideocomboBox->setObjectName(QString::fromUtf8("VideocomboBox"));
        VideocomboBox->setGeometry(QRect(70, 325, 171, 22));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(VideocomboBox->sizePolicy().hasHeightForWidth());
        VideocomboBox->setSizePolicy(sizePolicy1);
        AudiocomboBox = new QComboBox(Widget);
        AudiocomboBox->setObjectName(QString::fromUtf8("AudiocomboBox"));
        AudiocomboBox->setGeometry(QRect(70, 360, 171, 22));
        sizePolicy1.setHeightForWidth(AudiocomboBox->sizePolicy().hasHeightForWidth());
        AudiocomboBox->setSizePolicy(sizePolicy1);
        OutVolumeChangeSlider = new QSlider(Widget);
        OutVolumeChangeSlider->setObjectName(QString::fromUtf8("OutVolumeChangeSlider"));
        OutVolumeChangeSlider->setGeometry(QRect(360, 340, 160, 21));
        OutVolumeChangeSlider->setOrientation(Qt::Horizontal);
        InVolumeChangeSlider = new QSlider(Widget);
        InVolumeChangeSlider->setObjectName(QString::fromUtf8("InVolumeChangeSlider"));
        InVolumeChangeSlider->setGeometry(QRect(580, 340, 160, 21));
        InVolumeChangeSlider->setOrientation(Qt::Horizontal);
        RefreshBtn = new QPushButton(Widget);
        RefreshBtn->setObjectName(QString::fromUtf8("RefreshBtn"));
        RefreshBtn->setGeometry(QRect(260, 340, 51, 23));
        label_8 = new QLabel(Widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(330, 340, 31, 16));
        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(550, 340, 31, 16));
        fileStatuslabel = new QLabel(Widget);
        fileStatuslabel->setObjectName(QString::fromUtf8("fileStatuslabel"));
        fileStatuslabel->setGeometry(QRect(530, 230, 141, 16));
        sendMessageBtn = new QPushButton(Widget);
        sendMessageBtn->setObjectName(QString::fromUtf8("sendMessageBtn"));
        sendMessageBtn->setGeometry(QRect(310, 290, 75, 23));
        messagelineEdit = new QLineEdit(Widget);
        messagelineEdit->setObjectName(QString::fromUtf8("messagelineEdit"));
        messagelineEdit->setGeometry(QRect(20, 290, 281, 20));
        Videoctrl0Btn = new QPushButton(Widget);
        Videoctrl0Btn->setObjectName(QString::fromUtf8("Videoctrl0Btn"));
        Videoctrl0Btn->setGeometry(QRect(10, 580, 23, 23));
        label_10 = new QLabel(Widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 620, 341, 16));
        Audioctrl0Btn = new QPushButton(Widget);
        Audioctrl0Btn->setObjectName(QString::fromUtf8("Audioctrl0Btn"));
        Audioctrl0Btn->setGeometry(QRect(40, 580, 23, 23));
        Recordctrl0Btn = new QPushButton(Widget);
        Recordctrl0Btn->setObjectName(QString::fromUtf8("Recordctrl0Btn"));
        Recordctrl0Btn->setGeometry(QRect(70, 580, 23, 23));
        Snapshotctrl0Btn = new QPushButton(Widget);
        Snapshotctrl0Btn->setObjectName(QString::fromUtf8("Snapshotctrl0Btn"));
        Snapshotctrl0Btn->setGeometry(QRect(100, 580, 23, 23));
        Snapshotctrl1Btn = new QPushButton(Widget);
        Snapshotctrl1Btn->setObjectName(QString::fromUtf8("Snapshotctrl1Btn"));
        Snapshotctrl1Btn->setGeometry(QRect(280, 580, 23, 23));
        Audioctrl1Btn = new QPushButton(Widget);
        Audioctrl1Btn->setObjectName(QString::fromUtf8("Audioctrl1Btn"));
        Audioctrl1Btn->setGeometry(QRect(220, 580, 23, 23));
        Videoctrl1Btn = new QPushButton(Widget);
        Videoctrl1Btn->setObjectName(QString::fromUtf8("Videoctrl1Btn"));
        Videoctrl1Btn->setGeometry(QRect(190, 580, 23, 23));
        Recordctrl1Btn = new QPushButton(Widget);
        Recordctrl1Btn->setObjectName(QString::fromUtf8("Recordctrl1Btn"));
        Recordctrl1Btn->setGeometry(QRect(250, 580, 23, 23));
        Snapshotctrl2Btn = new QPushButton(Widget);
        Snapshotctrl2Btn->setObjectName(QString::fromUtf8("Snapshotctrl2Btn"));
        Snapshotctrl2Btn->setGeometry(QRect(460, 580, 23, 23));
        Audioctrl2Btn = new QPushButton(Widget);
        Audioctrl2Btn->setObjectName(QString::fromUtf8("Audioctrl2Btn"));
        Audioctrl2Btn->setGeometry(QRect(400, 580, 23, 23));
        Videoctrl2Btn = new QPushButton(Widget);
        Videoctrl2Btn->setObjectName(QString::fromUtf8("Videoctrl2Btn"));
        Videoctrl2Btn->setGeometry(QRect(370, 580, 23, 23));
        Recordctrl2Btn = new QPushButton(Widget);
        Recordctrl2Btn->setObjectName(QString::fromUtf8("Recordctrl2Btn"));
        Recordctrl2Btn->setGeometry(QRect(430, 580, 23, 23));
        Snapshotctrl3Btn = new QPushButton(Widget);
        Snapshotctrl3Btn->setObjectName(QString::fromUtf8("Snapshotctrl3Btn"));
        Snapshotctrl3Btn->setGeometry(QRect(640, 580, 23, 23));
        Audioctrl3Btn = new QPushButton(Widget);
        Audioctrl3Btn->setObjectName(QString::fromUtf8("Audioctrl3Btn"));
        Audioctrl3Btn->setGeometry(QRect(580, 580, 23, 23));
        Videoctrl3Btn = new QPushButton(Widget);
        Videoctrl3Btn->setObjectName(QString::fromUtf8("Videoctrl3Btn"));
        Videoctrl3Btn->setGeometry(QRect(550, 580, 23, 23));
        Recordctrl3Btn = new QPushButton(Widget);
        Recordctrl3Btn->setObjectName(QString::fromUtf8("Recordctrl3Btn"));
        Recordctrl3Btn->setGeometry(QRect(610, 580, 23, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        loginBtn->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\347\231\273\345\275\225\357\274\2102\357\274\211", 0, QApplication::UnicodeUTF8));
        initBtn->setText(QApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\357\274\2101\357\274\211", 0, QApplication::UnicodeUTF8));
        enterRoomBtn->setText(QApplication::translate("Widget", "\350\277\233\345\205\245\346\210\277\351\227\264\357\274\2103\357\274\211", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "IP:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "\345\257\206\347\240\201;", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "\346\210\277\351\227\264\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        VADcheckBox->setText(QApplication::translate("Widget", "VAD\357\274\210\351\235\231\351\237\263\346\243\200\346\265\213\357\274\211", 0, QApplication::UnicodeUTF8));
        AECcheckBox->setText(QApplication::translate("Widget", "AEC\357\274\210\345\233\236\351\237\263\346\266\210\351\231\244\357\274\211", 0, QApplication::UnicodeUTF8));
        AGCcheckBox->setText(QApplication::translate("Widget", "AGC\357\274\210\350\207\252\345\212\250\345\242\236\347\233\212\357\274\211", 0, QApplication::UnicodeUTF8));
        NScheckBox->setText(QApplication::translate("Widget", "NS\357\274\210\345\231\252\351\237\263\346\216\247\345\210\266\357\274\211", 0, QApplication::UnicodeUTF8));
        User0groupBox->setTitle(QString());
        User1groupBox->setTitle(QString());
        User2groupBox->setTitle(QString());
        User3groupBox->setTitle(QString());
        leaveRoomBtn->setText(QApplication::translate("Widget", "\347\246\273\345\274\200\346\210\277\351\227\264\357\274\2104\357\274\211", 0, QApplication::UnicodeUTF8));
        logoutBtn->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\346\263\250\351\224\200\357\274\2105\357\274\211", 0, QApplication::UnicodeUTF8));
        releaseBtn->setText(QApplication::translate("Widget", "\351\207\212\346\224\276\350\265\204\346\272\220\357\274\2106\357\274\211", 0, QApplication::UnicodeUTF8));
        sendFileBtn->setText(QApplication::translate("Widget", "\344\274\240\350\276\223\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        RecordState0->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        RecordState3->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        RecordState2->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        RecordState1->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        TransbufBtn->setText(QApplication::translate("Widget", "\344\274\240\347\274\223\345\206\262\345\214\272", 0, QApplication::UnicodeUTF8));
        VideopropertyBtn->setText(QApplication::translate("Widget", "\347\224\273\350\264\250\350\260\203\350\257\225", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "\350\247\206\351\242\221\350\256\276\345\244\207", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Widget", "\351\237\263\351\242\221\350\256\276\345\244\207", 0, QApplication::UnicodeUTF8));
        RefreshBtn->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Widget", "Wave", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Widget", "Mic", 0, QApplication::UnicodeUTF8));
        fileStatuslabel->setText(QString());
        sendMessageBtn->setText(QApplication::translate("Widget", "\345\217\221\351\200\201\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        Videoctrl0Btn->setText(QApplication::translate("Widget", "V", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Widget", "V\357\274\232\346\230\257\350\247\206\351\242\221\346\216\247\345\210\266  A\357\274\232\346\230\257\351\237\263\351\242\221\346\216\247\345\210\266   R\357\274\232\346\230\257\345\275\225\345\203\217\346\216\247\345\210\266  S\357\274\232\345\277\253\347\205\247", 0, QApplication::UnicodeUTF8));
        Audioctrl0Btn->setText(QApplication::translate("Widget", "A", 0, QApplication::UnicodeUTF8));
        Recordctrl0Btn->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        Snapshotctrl0Btn->setText(QApplication::translate("Widget", "S", 0, QApplication::UnicodeUTF8));
        Snapshotctrl1Btn->setText(QApplication::translate("Widget", "S", 0, QApplication::UnicodeUTF8));
        Audioctrl1Btn->setText(QApplication::translate("Widget", "A", 0, QApplication::UnicodeUTF8));
        Videoctrl1Btn->setText(QApplication::translate("Widget", "V", 0, QApplication::UnicodeUTF8));
        Recordctrl1Btn->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        Snapshotctrl2Btn->setText(QApplication::translate("Widget", "S", 0, QApplication::UnicodeUTF8));
        Audioctrl2Btn->setText(QApplication::translate("Widget", "A", 0, QApplication::UnicodeUTF8));
        Videoctrl2Btn->setText(QApplication::translate("Widget", "V", 0, QApplication::UnicodeUTF8));
        Recordctrl2Btn->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
        Snapshotctrl3Btn->setText(QApplication::translate("Widget", "S", 0, QApplication::UnicodeUTF8));
        Audioctrl3Btn->setText(QApplication::translate("Widget", "A", 0, QApplication::UnicodeUTF8));
        Videoctrl3Btn->setText(QApplication::translate("Widget", "V", 0, QApplication::UnicodeUTF8));
        Recordctrl3Btn->setText(QApplication::translate("Widget", "R", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
