#ifndef PLUGINMANAGE_H
#define PLUGINMANAGE_H

#include <QFrame>
#include <QLabel>
#include <QLibrary>
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QSpacerItem>

class PluginManage : public QFrame
{
    Q_OBJECT
public:
    explicit PluginManage(QWidget *parent = nullptr);

    // 界面布局
    void initUILayout(QWidget *parent);

    // 载入插件dll
    void loadPluginDLL();



signals:

private:
    // 界面布局
    QVBoxLayout *p_vlayout=nullptr;
        QHBoxLayout *p_hlayoutTop=nullptr;
        QFrame *p_frameTop=nullptr;
            QLabel *p_labPluginTitle=nullptr;
            QSpacerItem *p_hSpacerTop=nullptr;
            QPushButton *p_btClose=nullptr;

        QGridLayout *p_gridLayoutPlugin=nullptr;
            QPushButton *p_btPluginAdd=nullptr;
            QPushButton *p_btPluginAdd2=nullptr;
            QSpacerItem *p_hSpacer=nullptr;
            QSpacerItem *p_vSpacer=nullptr;


    QWidget *testWidget=nullptr;

    /*
     * 描述：界面事件继承，实现拖动
     *
     * */

protected:

    virtual bool event(QEvent *event);


private:
    QPoint posCursor;
    bool pressed=false;


};

#endif // PLUGINMANAGE_H
