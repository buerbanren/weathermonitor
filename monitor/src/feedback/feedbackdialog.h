#ifndef FEEDBACKDIALOG_H
#define FEEDBACKDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QTextEdit>
#include <QComboBox>

class FeedbackDialog : public QDialog
{
    Q_OBJECT
public:
    FeedbackDialog(QWidget *parent=nullptr);

    // 提交反馈数据到服务器
    void submitFeedback();
private:
    QVBoxLayout *pvlayoutFeedback=nullptr;

    QWidget *pwidgetTop;
    QHBoxLayout *phlayoutTop=nullptr;
    QLabel *plabTitle=nullptr;
    QSpacerItem *phspacerTop=nullptr;
    QPushButton *pbtCloseTop;

    QGridLayout *pgridlayoutFeedbackEdit=nullptr;
    QLabel *plabType=nullptr;
    QComboBox *pcomboxType=nullptr;
    QTextEdit *peditFeedbackContent=nullptr;

    QWidget *pwidgetBottom=nullptr;
    QHBoxLayout *phlayoutBottom=nullptr;
    QSpacerItem *phspacerBottom=nullptr;
    QPushButton *pbtFeedbackSubmit=nullptr;
};

#endif // FEEDBACKDIALOG_H
