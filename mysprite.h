#ifndef MYSPRITE_H
#define MYSPRITE_H

#include <QDialog>
#include <QPoint>
#include <QLabel>
#include <QMenu>
#include <QPixmap>
#include <QImage>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QAction>
#include <QPainter>
#include <QTime>
#include <QTimer>

#include <spritemenu.h>

class MySprite : public QDialog
{
    Q_OBJECT

public:
    MySprite(QWidget *parent = 0);
    ~MySprite();

private:
    bool m_DragEnable;      //是否按下
    QPoint m_RelativePos;   //相对位置

    int blinkFrame = 0;     //眨眼过程中的第几帧（单次眨眼）
    int  struggleFrame = 0; //挣扎过程中的第几帧

    //主窗口布局
    QHBoxLayout* mainLayout;
    QLabel* m_SpriteShowLabel;      //显示精灵的控件
    QImage m_SpriteShowImage;       //显示精灵的图片（总体图），该图片在上面的控件显示
    QImage *m_SpriteNowBaseImage = nullptr;    //当前基底
    QImage *m_SpriteNowHatImage = nullptr;     //当前帽子
    QImage *m_SpriteNowClothesImage = nullptr; //当前衣服

    //各种类的动作分别载入到对应的列表
    QImage m_SpriteNormalImageList[10];     //普通状态下
    QImage m_SpriteBlinkImageList[2];       //眨眼动作
    QImage m_SpriteClothesImageList[8];      //衣服图片
    QImage m_SpriteHatImageList[8];         //帽子图片
    QImage m_SpriteStruggleImageList[3];    //拖拽时挣扎图片

    //右键菜单
    SpriteMenu *pSpriteMenu;


    //眨眼事件定时器
    QTimer *m_AutoBlinkTimer;//隔一段时间自动眨眼
    QTimer *m_OnceBlinkTimer;//单次眨眼
    QTimer *m_StruggleTimer; //拖动挣扎的定时器（按下时）


private:
    bool CheckDragRegion(const QPoint &g_pos);                  //鼠标是否进入图像区域
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *event);    //右键弹出菜单

private:
    //主窗口初始化
    void mainWindowInit();
    //创建菜单
    void createMenu();
    //载入各种类动作图片
    void loadImageList();
    //初始化要用到的定时器
    void timerInit();

    //混合png图片 结果存在m_SpriteShowImage
    void mixImage(QImage* baseImage, QImage* hatImage, QImage* clothesImage);
    //显示精灵在桌面上
    void showSprite();

    int getNewBlinkTime();//获取眨眼随机数 3——6秒一次

private:
    void slot_AutoBlinkAction();     //自动眨眼事件
    void slot_OnceBlinkAction();     //单次眨眼(指眨眼的过程)
    void slot_struggleAction();      //拖动时的挣扎事件

};

#endif // MYSPRITE_H
