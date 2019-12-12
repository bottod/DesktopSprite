#include "mysprite.h"
#include "QDebug"

MySprite::MySprite(QWidget *parent)
    : QDialog(parent)
{
    m_DragEnable = false;           //默认没按下
    m_RelativePos = QPoint(0, 0);   //相对位置初始化

    mainWindowInit();               //窗口初始化
    createMenu();                   //创建右键菜单
    loadImageList();                //载入需要的图片
    timerInit();                    //定时器初始化


    //精灵初始动作
    m_SpriteNowBaseImage = &(m_SpriteNormalImageList[0]);
    showSprite();
}




//主窗口的一些必要设置 以及 布局
void MySprite::mainWindowInit()
{
    //设置窗口属性
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //设置默认菜单显示
    setContextMenuPolicy(Qt::DefaultContextMenu);


    //窗口布局
    mainLayout = new QHBoxLayout(this);
    m_SpriteShowLabel = new QLabel(this);
    mainLayout->addWidget(m_SpriteShowLabel);
}

//创建右键菜单对象
void MySprite::createMenu()
{
    pSpriteMenu = new SpriteMenu(this);

    //装扮
    connect(pSpriteMenu->ReloadMenu_Hat1, &QAction::triggered, this, [=](){
        if(pSpriteMenu->ReloadMenu_Hat1->isChecked())
            m_SpriteNowHatImage = &(m_SpriteHatImageList[0]);
        else
            m_SpriteNowHatImage = nullptr;
        showSprite();
    });
    connect(pSpriteMenu->ReloadMenu_Hat2, &QAction::triggered, this, [=](){
        if(pSpriteMenu->ReloadMenu_Hat2->isChecked())
            m_SpriteNowHatImage = &(m_SpriteHatImageList[2]);
        else
            m_SpriteNowHatImage = nullptr;
        showSprite();
    });
    connect(pSpriteMenu->ReloadMenu_Hat3, &QAction::triggered, this, [=](){
        if(pSpriteMenu->ReloadMenu_Hat3->isChecked())
            m_SpriteNowHatImage = &(m_SpriteHatImageList[4]);
        else
            m_SpriteNowHatImage = nullptr;
        showSprite();
    });
    connect(pSpriteMenu->ReloadMenu_Hat4, &QAction::triggered, this, [=](){
        if(pSpriteMenu->ReloadMenu_Hat4->isChecked())
            m_SpriteNowHatImage = &(m_SpriteHatImageList[6]);
        else
            m_SpriteNowHatImage = nullptr;
        showSprite();
    });
    connect(pSpriteMenu->ReloadMenu_Cloth1, &QAction::triggered, this, [=](){
        if(pSpriteMenu->ReloadMenu_Cloth1->isChecked())
            m_SpriteNowClothesImage = &(m_SpriteClothesImageList[0]);
        else
            m_SpriteNowClothesImage = nullptr;
        showSprite();
    });
    connect(pSpriteMenu->ReloadMenu_Cloth2, &QAction::triggered, this, [=](){
        if(pSpriteMenu->ReloadMenu_Cloth2->isChecked())
            m_SpriteNowClothesImage = &(m_SpriteClothesImageList[4]);
        else
            m_SpriteNowClothesImage = nullptr;
        showSprite();
    });

    //退出
    connect(pSpriteMenu->quitAction, &QAction::triggered, this, [=](){exit(0);});
}

//导入各种类图片 帽子和衣服顺序有要求，同一套要顺序放置 先静止时后拖动时
void MySprite::loadImageList()
{
    m_SpriteNormalImageList[0].load(":/normal/res/surface0000.png");
    m_SpriteNormalImageList[1].load(":/normal/res/surface0001.png");
    m_SpriteNormalImageList[2].load(":/normal/res/surface0002.png");
    m_SpriteNormalImageList[3].load(":/normal/res/surface0003.png");
    m_SpriteNormalImageList[4].load(":/normal/res/surface0004.png");
    m_SpriteNormalImageList[5].load(":/normal/res/surface0005.png");
    m_SpriteNormalImageList[6].load(":/normal/res/surface0006.png");
    m_SpriteNormalImageList[7].load(":/normal/res/surface0007.png");
    m_SpriteNormalImageList[8].load(":/normal/res/surface0008.png");
    m_SpriteNormalImageList[9].load(":/normal/res/surface0009.png");
    m_SpriteStruggleImageList[0].load(":/drag/res/surface0091.png");
    m_SpriteStruggleImageList[1].load(":/drag/res/surface0092.png");
    m_SpriteStruggleImageList[2].load(":/drag/res/surface0093.png");
    m_SpriteBlinkImageList[0].load(":/blink/res/surface1003.png");
    m_SpriteBlinkImageList[1].load(":/blink/res/surface1004.png");
    m_SpriteHatImageList[0].load(":/hat/res/surface3000.png");
    m_SpriteHatImageList[1].load(":/hat/res/surface3001.png");
    m_SpriteHatImageList[2].load(":/hat/res/surface3002.png");
    m_SpriteHatImageList[3].load(":/hat/res/surface3003.png");
    m_SpriteHatImageList[4].load(":/hat/res/surface3004.png");
    m_SpriteHatImageList[5].load(":/hat/res/surface3005.png");
    m_SpriteHatImageList[6].load(":/hat/res/surface3006.png");
    m_SpriteHatImageList[7].load(":/hat/res/surface3007.png");
    m_SpriteClothesImageList[0].load(":/clothes/res/surface3100.png");
    m_SpriteClothesImageList[1].load(":/clothes/res/surface3101.png");
    m_SpriteClothesImageList[2].load(":/clothes/res/surface3102.png");
    m_SpriteClothesImageList[3].load(":/clothes/res/surface3103.png");
    m_SpriteClothesImageList[4].load(":/clothes/res/surface3200.png");
    m_SpriteClothesImageList[5].load(":/clothes/res/surface3201.png");
    m_SpriteClothesImageList[6].load(":/clothes/res/surface3202.png");
    m_SpriteClothesImageList[7].load(":/clothes/res/surface3203.png");
}

//混合图片，不同的衣服和帽子混合显示 结果存在m_SpriteShowImage
void MySprite::mixImage(QImage* baseImage, QImage* hatImage, QImage* clothesImage)
{
    m_SpriteShowImage = *baseImage;
    QPainter imagepainter(&m_SpriteShowImage);  //新建画板
    imagepainter.setCompositionMode(QPainter::CompositionMode_SourceOver);   //设置重叠效果
    if(clothesImage != nullptr)
        imagepainter.drawImage(0,0, *clothesImage);
    if(hatImage != nullptr)
        imagepainter.drawImage(0,0, *hatImage);
    imagepainter.end();
}

//显示精灵在桌面上
void MySprite::showSprite()
{
    mixImage(m_SpriteNowBaseImage, m_SpriteNowHatImage, m_SpriteNowClothesImage);
    m_SpriteShowLabel->setPixmap(QPixmap::fromImage(m_SpriteShowImage));
}

//初始化要用到的定时器
void MySprite::timerInit()
{
    //眨眼事件的定时器 3-6秒一次眨眼
    m_AutoBlinkTimer = new QTimer(this);
    connect(m_AutoBlinkTimer, &QTimer::timeout, this, &MySprite::slot_AutoBlinkAction);
    m_OnceBlinkTimer = new QTimer(this);
    connect(m_OnceBlinkTimer, &QTimer::timeout, this, &MySprite::slot_OnceBlinkAction);
    m_StruggleTimer = new QTimer(this);
    connect(m_StruggleTimer, &QTimer::timeout, this, &MySprite::slot_struggleAction);

    m_AutoBlinkTimer->start(3000);//自动眨眼开启
}

//产生随机数3-6之间用于每次眨眼的间隔
int MySprite::getNewBlinkTime()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int blink_time =qrand()%3 + 3;

    return blink_time;
}

MySprite::~MySprite()
{

}



/************************** slot *********************************/
//每3-6秒眨眼一次
void MySprite::slot_AutoBlinkAction()
{
    m_AutoBlinkTimer->stop();

    m_OnceBlinkTimer->start(100);//眨眼，一次在0.4秒

    int newBlinkTime = getNewBlinkTime();
    m_AutoBlinkTimer->start(1000 * newBlinkTime);
}

//单次眨眼(指眨眼的过程)
void MySprite::slot_OnceBlinkAction()
{
    switch (blinkFrame)
    {
        case 0://半开眼
            m_SpriteNowBaseImage = &(m_SpriteBlinkImageList[0]);
            break;
        case 1://闭眼
            m_SpriteNowBaseImage = &(m_SpriteBlinkImageList[1]);
            break;
        case 2://半开眼
            m_SpriteNowBaseImage = &(m_SpriteBlinkImageList[0]);
            break;
        default://开眼
            m_SpriteNowBaseImage = &(m_SpriteNormalImageList[0]);
            blinkFrame = 0;
            m_OnceBlinkTimer->stop();
            break;
    }
    blinkFrame++;
    showSprite();
}

//按下时拖动时（挣扎的过程）
void MySprite::slot_struggleAction()
{
    switch (struggleFrame)
    {
        case 0:
            m_SpriteNowBaseImage = &(m_SpriteStruggleImageList[0]);
            break;
        case 1:
            m_SpriteNowBaseImage = &(m_SpriteStruggleImageList[1]);
            break;
        case 2:
            m_SpriteNowBaseImage = &(m_SpriteStruggleImageList[2]);
            break;
        default:
            m_SpriteNowBaseImage = &(m_SpriteStruggleImageList[0]);
            struggleFrame = 0;
            break;
    }
    struggleFrame++;
    showSprite();
}





/********************** virtual void 事件 ************************/
//判断鼠标是否点在人物上
bool MySprite::CheckDragRegion(const QPoint &g_pos)
{
    QPoint pt = g_pos; //输入全局鼠标点
    QRect rcWnd = geometry();//获取全局程序位置
    //qDebug() << "pos: " << pt << "geometry: " << rcWnd;


    //转换鼠标点到屏幕左上角开始的相对位置
    pt.setX(pt.x() - rcWnd.left());
    pt.setY(pt.y() - rcWnd.top());

    int nW = rcWnd.width();
    int nH = rcWnd.height();

    //在左上角判断一个原窗口大小的rect
    QRect rcDrag(0, 0, nW, nH);
    if(rcDrag.contains(pt))
    {
        return true;
    }

    return false;
}

void MySprite::mousePressEvent(QMouseEvent *e)
{
    //左键单击
    if(CheckDragRegion(e->globalPos()) && e->button() == Qt::LeftButton)
    {
        //如果点在人物上
        m_DragEnable = true; //已按下，可拖动
        m_RelativePos= pos() - e->globalPos();

        m_AutoBlinkTimer->stop();       //拖动时不眨眼，该挣扎

        //挣扎原始状态
        m_SpriteNowBaseImage = &(m_SpriteStruggleImageList[0]);
        if(m_SpriteNowHatImage != nullptr)
            m_SpriteNowHatImage = m_SpriteNowHatImage + 1;
        if(m_SpriteNowClothesImage != nullptr)
            m_SpriteNowClothesImage = m_SpriteNowClothesImage + 1;
        showSprite();//显示挣扎初始状态

        m_StruggleTimer->start(100);    //精灵挣扎状态切换
    }
}

void MySprite::mouseMoveEvent(QMouseEvent* e)
{
    if(m_DragEnable)
    {
        move(e->globalPos()+ m_RelativePos);
    }
}

void MySprite::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    if(m_DragEnable)
    {
        m_DragEnable = false;

        m_StruggleTimer->stop();//关闭挣扎

        //恢复原始状态
        m_SpriteNowBaseImage = &(m_SpriteNormalImageList[0]);
        if(m_SpriteNowHatImage != nullptr)
            m_SpriteNowHatImage = m_SpriteNowHatImage - 1;
        if(m_SpriteNowClothesImage != nullptr)
            m_SpriteNowClothesImage = m_SpriteNowClothesImage - 1;
        showSprite();//重新显示

        int newBlinkTime = getNewBlinkTime();
        m_AutoBlinkTimer->start(1000 * newBlinkTime);//重新开启自动眨眼
    }
}

//右键菜单事件
void MySprite::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event)

    //在鼠标右键点击的地方显示菜单
    pSpriteMenu->exec(QCursor::pos());
}

