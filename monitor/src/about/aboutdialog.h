#ifndef ABOUTFRAME_H
#define ABOUTFRAME_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = nullptr);


private:
    QVBoxLayout *pvlayoutAbout=nullptr;

    QWidget *pwidgetTop;
    QHBoxLayout *phlayoutTop=nullptr;
    QLabel *plabTitle=nullptr;
    QSpacerItem *phspacerTop=nullptr;
    QPushButton *pbtCloseTop;

    QLabel *labelDescrib=nullptr;

    QWidget *pwidgetBottom=nullptr;
    QHBoxLayout *phlayoutBottom=nullptr;
    QSpacerItem *phspacerBottom=nullptr;
    QPushButton *pbtCloseBottom=nullptr;
};

#endif // ABOUTFRAME_H
