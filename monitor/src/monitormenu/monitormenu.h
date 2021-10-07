#ifndef MONITORMENU_H
#define MONITORMENU_H

#include <QEvent>
#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QButtonGroup>

// 菜单UI控件结构体
struct StructMenu{
    QPushButton *button=nullptr;    // 菜单按键
    QLabel *label=nullptr;  // 菜单文本描述
};

class MonitorMenu : public QFrame
{
    Q_OBJECT
public:
    explicit MonitorMenu(QWidget *parent = nullptr);

private:
    void initUILayout();

signals:
    void menuChanged(std::string name);

protected:

private:
    QGridLayout *pgridlayoutMainMenu=nullptr;
        QPushButton *pbtUpload=nullptr; // 上拉窗口按键
        QPushButton *pbtExit=nullptr;   // 退出
        QLabel *plabExit=nullptr;
        QPushButton *pbtPlugin=nullptr; // 插件
        QLabel *plabPlugin=nullptr;
        QPushButton *pbtFeedback=nullptr;    //反馈
        QLabel *plabFeedback=nullptr;
        QPushButton *pbtAbout=nullptr;  // 关于
        QLabel *plabAbout=nullptr;
        QPushButton *pbtDownload=nullptr;   // 下拉窗口按键

   std::map<std::string,StructMenu> mapMenuControl;
   QButtonGroup *btgroupMenu=nullptr;


};

#endif // MONITORMENU_H
