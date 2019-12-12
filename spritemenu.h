/*****************************************
 * 桌面精灵的右键弹出菜单
*****************************************/
#ifndef SPRITEMENU_H
#define SPRITEMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QProcess>

class SpriteMenu : public QMenu
{
public:
    SpriteMenu(QWidget *parent = 0);

public:
    QAction *quitAction;    //退出动作， 调用处连接主窗口退出槽

    QMenu *ReloadMenu;      //换装菜单；
    QAction *ReloadMenu_Hat1;
    QAction *ReloadMenu_Hat2;
    QAction *ReloadMenu_Hat3;
    QAction *ReloadMenu_Hat4;
    QAction *ReloadMenu_Cloth1;
    QAction *ReloadMenu_Cloth2;

private:
    QMenu *AppMenu;         //该菜单下的动作用于打开特定App
    QAction *AppMenu_OpenBrowser;      //打开浏览器
    QAction *AppMen_OpenCalc;          //打开计算器


private:
    void init_action();     //初始化所有action

    void open_browser();     //打开谷歌浏览器
};

#endif // SPRITEMENU_H
