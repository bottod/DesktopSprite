#include "spritemenu.h"

SpriteMenu::SpriteMenu(QWidget *parent)
    : QMenu(parent)
{
    init_action();  //初始化子菜单和action
}

//初始化子菜单和action
void SpriteMenu::init_action()
{
    AppMenu = new QMenu("打开程序", this);
    AppMenu_OpenBrowser = new QAction("打开Chrome", this);
    AppMenu->addAction(AppMenu_OpenBrowser);
    connect(AppMenu_OpenBrowser, &QAction::triggered, this, &SpriteMenu::open_browser);
    AppMen_OpenCalc = new QAction("打开计算器", this);
    AppMenu->addAction(AppMen_OpenCalc);
    connect(AppMen_OpenCalc, &QAction::triggered, this, &SpriteMenu::open_browser);


    ReloadMenu = new QMenu("装扮", this);
    ReloadMenu_Hat1 = new QAction("帽子——圣诞", this);
    ReloadMenu_Hat1->setCheckable(true);        ReloadMenu->addAction(ReloadMenu_Hat1);
    connect(ReloadMenu_Hat1, &QAction::triggered, [=](){
        ReloadMenu_Hat2->setChecked(false);
        ReloadMenu_Hat3->setChecked(false);
        ReloadMenu_Hat4->setChecked(false);
    });
    ReloadMenu_Hat2 = new QAction("帽子——樱花", this);
    ReloadMenu_Hat2->setCheckable(true);        ReloadMenu->addAction(ReloadMenu_Hat2);
    connect(ReloadMenu_Hat2, &QAction::triggered, [=](){
        ReloadMenu_Hat1->setChecked(false);
        ReloadMenu_Hat3->setChecked(false);
        ReloadMenu_Hat4->setChecked(false);
    });
    ReloadMenu_Hat3 = new QAction("帽子——水手帽", this);
    ReloadMenu_Hat3->setCheckable(true);        ReloadMenu->addAction(ReloadMenu_Hat3);
    connect(ReloadMenu_Hat3, &QAction::triggered, [=](){
        ReloadMenu_Hat1->setChecked(false);
        ReloadMenu_Hat2->setChecked(false);
        ReloadMenu_Hat4->setChecked(false);
    });
    ReloadMenu_Hat4 = new QAction("帽子——风车", this);
    ReloadMenu_Hat4->setCheckable(true);        ReloadMenu->addAction(ReloadMenu_Hat4);
    connect(ReloadMenu_Hat4, &QAction::triggered, [=](){
        ReloadMenu_Hat1->setChecked(false);
        ReloadMenu_Hat2->setChecked(false);
        ReloadMenu_Hat3->setChecked(false);
    });
    ReloadMenu_Cloth1 = new QAction("衣服——圣诞", this);
    ReloadMenu_Cloth1->setCheckable(true);        ReloadMenu->addAction(ReloadMenu_Cloth1);
    connect(ReloadMenu_Cloth1, &QAction::triggered, [=](){
        ReloadMenu_Cloth2->setChecked(false);
    });
    ReloadMenu_Cloth2 = new QAction("衣服——和服", this);
    ReloadMenu_Cloth2->setCheckable(true);        ReloadMenu->addAction(ReloadMenu_Cloth2);
    connect(ReloadMenu_Cloth2, &QAction::triggered, [=](){
        ReloadMenu_Cloth1->setChecked(false);
    });
    ReloadMenu->addAction(ReloadMenu_Hat1);
    ReloadMenu->addAction(ReloadMenu_Hat2);
    ReloadMenu->addAction(ReloadMenu_Hat3);
    ReloadMenu->addAction(ReloadMenu_Hat4);
    ReloadMenu->addAction(ReloadMenu_Cloth1);
    ReloadMenu->addAction(ReloadMenu_Cloth2);


    quitAction = new QAction("退出程序", this);

    //按顺序加入
    this->addMenu(AppMenu);
    this->addMenu(ReloadMenu);
    this->addAction(quitAction);
}

//打开浏览器
void SpriteMenu::open_browser()
{
    //本地浏览器地址
    QString browser_path = "C:/Program Files (x86)/Google/Chrome/Application/chrome.exe";
    QProcess::startDetached(browser_path, QStringList("http://www.baidu.com"));
}
