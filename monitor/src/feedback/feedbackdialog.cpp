#include "feedbackdialog.h"
#include "../common/comdefine.h"
#include <QListView>

FeedbackDialog::FeedbackDialog(QWidget *parent):
    QDialog(parent)
{
    this->setFixedSize(460,200);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->hide();
    this->setObjectName("aboutDialog");
    this->setStyleSheet(Common::readFileContent(":/qss/resource/qss/feedbackdialog.css").data());

    // 主布局，垂直布局
    pvlayoutFeedback=new QVBoxLayout(this);
    pvlayoutFeedback->setContentsMargins(0,0,0,0);
    pvlayoutFeedback->setSpacing(0);
    this->setLayout(pvlayoutFeedback);

    // 标题栏布局，水平布局
    pwidgetTop=new QWidget(this);
    pwidgetTop->setFixedHeight(32);

    phlayoutTop=new QHBoxLayout(pwidgetTop);
    phlayoutTop->setContentsMargins(10,0,10,0);
    phlayoutTop->setAlignment(Qt::AlignVCenter);

    plabTitle=new QLabel(this);
    plabTitle->setObjectName("btaboutTitle");
    plabTitle->setFixedSize(64,32);
    plabTitle->setText("反馈");
    plabTitle->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    phlayoutTop->addWidget(plabTitle);

    phspacerTop=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    phlayoutTop->addItem(phspacerTop);

    pbtCloseTop=new QPushButton(this);
    pbtCloseTop->setObjectName("btCloseTop");
    pbtCloseTop->setFixedSize(24,24);
    connect(pbtCloseTop,&QPushButton::clicked, this, &FeedbackDialog::close);
    phlayoutTop->addWidget(pbtCloseTop);

    pwidgetTop->setLayout(phlayoutTop);
    pvlayoutFeedback->addWidget(pwidgetTop);


    // 反馈操作区
    pgridlayoutFeedbackEdit=new QGridLayout(this);
    pgridlayoutFeedbackEdit->setContentsMargins(24,16,24,16);
    pgridlayoutFeedbackEdit->setVerticalSpacing(16);

    plabType=new QLabel(this);
    plabType->setObjectName("labFeedback");
    plabType->setTextFormat(Qt::RichText);
    plabType->setText("类  别");
    plabType->setFixedSize(64,24);
    plabType->setAlignment(Qt::AlignmentFlag::AlignVCenter | Qt::AlignLeft);
    pgridlayoutFeedbackEdit->addWidget(plabType,0,0);

    pcomboxType=new QComboBox(this);
    pcomboxType->setView(new  QListView());
    pcomboxType->setObjectName("comboxType");
    pcomboxType->setFixedSize(96,24);
    pcomboxType->addItems({"天气简要","今日详情","24小时预报","7天预报","降水雷达预报","其他"});
    pgridlayoutFeedbackEdit->addWidget(pcomboxType,0,1);

    peditFeedbackContent=new QTextEdit(this);
    peditFeedbackContent->setObjectName("editFeedback");
    peditFeedbackContent->setPlaceholderText("详细内容");
    peditFeedbackContent->setTextColor(QColor(255,255,255));
    pgridlayoutFeedbackEdit->addWidget(peditFeedbackContent,1,0,3,4);

    pvlayoutFeedback->addLayout(pgridlayoutFeedbackEdit);

    // 底部布局
    pwidgetBottom=new QWidget(this);
    pwidgetBottom->setFixedHeight(34);

    phlayoutBottom=new QHBoxLayout(this);
    phlayoutBottom->setContentsMargins(10,0,64,10);

    phspacerBottom=new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    phlayoutBottom->addItem(phspacerBottom);

    pbtFeedbackSubmit=new QPushButton(this);
    pbtFeedbackSubmit->setObjectName("btCloseBottom");
    pbtFeedbackSubmit->setFixedSize(64,24);
    pbtFeedbackSubmit->setText("提交");
    connect(pbtFeedbackSubmit,&QPushButton::clicked, this, &FeedbackDialog::submitFeedback);
    phlayoutBottom->addWidget(pbtFeedbackSubmit);

    pwidgetBottom->setLayout(phlayoutBottom);
    pvlayoutFeedback->addWidget(pwidgetBottom);
}

void FeedbackDialog::submitFeedback()
{
    if(peditFeedbackContent->toPlainText().size()==0)
    {
        return;
    }
    else{
        peditFeedbackContent->clear();
    }
}
