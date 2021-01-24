#include "room.h"

Room::Room(QObject *parent, QGraphicsScene *scene, std::list<Proyectile *> *p, std::string name_) : QObject(parent), scene(scene), v_limit(720), h_limit(1280) {

    cleared = false;
    item = nullptr;
    spring = nullptr;
    boss_door = nullptr;

    bg = nullptr;

    if(name_ == "f1-safe"){
        walls.push_back(new Wall(this, 1280 - 300, 720 - 300, 300, 300));
        walls.push_back(new Wall(this, 1280-400, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-500, 720-100, 100, 100));

        left_door = nullptr;
        right_door = new Door(this, this, 1280-160, 720-300-40, 20, 40);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f1-safe.png");
        setPos(0,0);

        itemX = 0;
        itemY = 0;

        boss = nullptr;

        type = "safe";
        name = "safe";
    }
    else if(name_ == "f1-1"){
        walls.push_back(new Wall(this, 0, 720 - 300, 100, 300));
        walls.push_back(new Wall(this, 100, 720-200, 100, 200));
        walls.push_back(new Wall(this, 200, 720-100, 100, 100));
        walls.push_back(new Wall(this, 1280 - 100, 720 - 300, 100, 300));
        walls.push_back(new Wall(this, 250, 720 - 400, 300, 40));
        walls.push_back(new Wall(this, 700, 720 - 300, 300, 40));
        walls.push_back(new Wall(this, 650, 720 - 550, 300, 40));

        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 850, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 400, 420, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 850, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 850, 570, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 40, 720-300-40, 20, 40);
        right_door = new Door(this, this, 1280-60, 720-300-40, 20, 40);
        up_door = nullptr;
        down_door = new Door(this, this, 1280/2 - 10, 720-40, 20, 40);

        bg = new QPixmap(":/Assets/Sprites/f1-1.png");
        setPos(0,0);

        spring = new Spring(nullptr, 1135, 5, 100, 40, 0.025f, 0.25f);

        itemX = 840 - 24;
        itemY = 720 - 550 - 32;

        boss = nullptr;

        type = "normal";
        name = "1";
    }
    else if(name_ == "f1-2"){
        walls.push_back(new Wall(this, 0, 720 - 300, 200, 40));
        walls.push_back(new Wall(this, 300, 720 - 200, 200, 40));
        walls.push_back(new Wall(this, 500, 720-60, 500, 60));
        walls.push_back(new Wall(this, 1280-200, 720 - 200, 200, 40));
        walls.push_back(new Wall(this, 800, 720 - 350, 200, 40));
        walls.push_back(new Wall(this, 500, 720 - 450, 200, 40));
        walls.push_back(new Wall(this, 200, 720 - 550, 200, 40));
        walls.push_back(new Wall(this, 500, 720 - 650, 200, 40));

        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 780, 80, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 290, 560, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 200, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 40, 720-300-40, 20, 40);
        right_door = nullptr;
        up_door = new Door(this, this, 590, 720-650-40, 20, 40);
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f1-2.png");
        setPos(0,0);

        itemX = 300 - 32;
        itemY = 720 - 550 - 32;

        boss = nullptr;

        type = "normal";
        name = "2";
    }
    else if(name_ == "f1-item"){
        walls.push_back(new Wall(this, 1280 - 200, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 720-100, 100, 100));
        walls.push_back(new Wall(this, 0, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 200, 720-200, 100, 200));
        walls.push_back(new Wall(this, 300, 720-100, 100, 100));

        walls.push_back(new Wall(this, 300, 720 - 400, 680, 50));
        walls.push_back(new Wall(this, 400, 720 - 460, 480, 60));
        walls.push_back(new Wall(this, 1280/2 -30, 720 - 500, 60, 40));

        left_door = nullptr;
        right_door = nullptr;
        up_door = nullptr;
        down_door = new Door(this, this, 1280/2 -10, 720-40, 20, 40);

        bg = new QPixmap(":/Assets/Sprites/f1-item.png");
        setPos(0,0);

        itemX = 1280/2 - 16;
        itemY = 720 - 500 - 32;

        boss = nullptr;

        type = "treasure";
        name = "item";
    }
    else if(name_ == "f1-3"){

        walls.push_back(new Wall(this, 1280 - 300, 720 - 150, 300, 150));
        walls.push_back(new Wall(this, 0, 720 - 150, 300, 150));
        walls.push_back(new Wall(this, 200, 720 - 300, 300, 40));

        walls.push_back(new Wall(this, 1280 - 500, 720 - 300, 300, 40));

        walls.push_back(new Wall(this, 500, 720 - 450, 280, 40));
        walls.push_back(new Wall(this, 500, 720 - 120, 280, 40));

                enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 140, 170, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
                enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280-140, 170, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
                enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280/2, 140, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = nullptr;
        right_door = nullptr;
        up_door = new Door(this, this, 1280/2 -10, 720-450-40, 20, 40);
        down_door = new Door(this, this, 1280/2 -10, 720-40, 20, 40);

        bg = new QPixmap(":/Assets/Sprites/f1-3.png");
        setPos(0,0);

        itemX = 1280/2 - 16;
        itemY = 720 - 120 - 32;

        boss = nullptr;

        type = "normal";
        name = "3";
    }
    else if(name_ == "f1-4"){

        walls.push_back(new Wall(this, 1280 - 200, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 720-100, 100, 100));
        walls.push_back(new Wall(this, 1280 - 200, 0, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 0, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 0, 100, 100));
        walls.push_back(new Wall(this, 400, 720-650, 180, 40));
        walls.push_back(new Wall(this, 580, 0, 40, 110));
        walls.push_back(new Wall(this, 200, 720-550, 150, 20));
        walls.push_back(new Wall(this, 50, 720-450, 150, 20));
        walls.push_back(new Wall(this, 200, 720-350, 150, 20));
        walls.push_back(new Wall(this, 50, 720-250, 150, 20));
        walls.push_back(new Wall(this, 200, 720-150, 150, 20));
        walls.push_back(new Wall(this, 50, 720-50, 150, 50));
        walls.push_back(new Wall(this, 200, 720-25, 150, 25));

        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280-250, 220, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280-350, 120, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280-450, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = nullptr;
        right_door = new Door(this, this, 1280 - 100 - 20, 720-300-80, 40, 80);
        up_door = new Door(this, this, 500, 720-650-40, 20, 40);
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f1-4.png");
        setPos(0,0);

        itemX = 125 - 16;
        itemY = 720 - 50 - 32;

        boss = nullptr;

        type = "normal";
        name = "4";
    }
    else if(name_ == "lamprey"){

        walls.push_back(new Wall(this, 50, 720-100, 150, 20));
        walls.push_back(new Wall(this, 300, 720-100, 150, 20));
        walls.push_back(new Wall(this, 550, 720-100, 150, 20));
        walls.push_back(new Wall(this, 800, 720-100, 150, 20));

        walls.push_back(new Wall(this, 0, 720-250, 50, 20));
        walls.push_back(new Wall(this, 150, 720-250, 150, 20));
        walls.push_back(new Wall(this, 400, 720-250, 150, 20));
        walls.push_back(new Wall(this, 650, 720-250, 150, 20));

        walls.push_back(new Wall(this, 50, 720-400, 150, 20));
        walls.push_back(new Wall(this, 300, 720-400, 150, 20));
        walls.push_back(new Wall(this, 550, 720-400, 150, 20));

        walls.push_back(new Wall(this, 0, 720-550, 50, 20));
        walls.push_back(new Wall(this, 150, 720-550, 150, 20));
        walls.push_back(new Wall(this, 400, 720-550, 150, 20));

        left_door = new Door(this, this, 0, 720-40, 20, 40);
        right_door = nullptr;
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f1-boss.png");
        setPos(0,0);

        boss_door = new Door(this, nullptr, "boss", 1280/2, 610, 1280 - 150 - 20, 720-80, 40, 80, ":/Assets/Sprites/f1-boss-door.png");

        boss = new Boss(this, scene, "lamprey", p, 1280-150, 720/2, 0, 0, 50, 300, 200, 0, 1e-5, 0.1, 0);

        itemX =  475 - 16;
        itemY = 720 - 550 -32;

        type = "boss";
        name = "boss";
    }

    else if(name_ == "f2-safe"){
        walls.push_back(new Wall(this, 400, 720 - 600, 480, 40));

        walls.push_back(new Wall(this, 0, 720-200, 300, 200));
        walls.push_back(new Wall(this, 300, 720-100, 100, 100));

        walls.push_back(new Wall(this, 1280-300, 720-200, 300, 200));
        walls.push_back(new Wall(this, 1280-400, 720-100, 100, 100));

        left_door = nullptr;
        right_door = nullptr;
        up_door = nullptr;
        down_door = new Door(this, this, 1280/2 - 10, 720-40, 20, 40);

        bg = new QPixmap(":/Assets/Sprites/f2-safe.png");
        setPos(0,0);

        itemX = 0;
        itemY = 0;

        boss = nullptr;

        type = "safe";
        name = "safe";
    }
    else if(name_ == "f2-1"){
        walls.push_back(new Wall(this, 0, 720-200, 300, 200));
        walls.push_back(new Wall(this, 300, 720-100, 100, 100));
        walls.push_back(new Wall(this, 1280-300, 720-200, 300, 200));
        walls.push_back(new Wall(this, 1280-400, 720-100, 100, 100));

        walls.push_back(new Wall(this, 1280/2 - 75, 720-550, 150, 20));

        walls.push_back(new Wall(this, 250, 720-340, 100, 20));
        walls.push_back(new Wall(this, 450, 720-440, 100, 20));
        walls.push_back(new Wall(this, 1280-350, 720-340, 100, 20));
        walls.push_back(new Wall(this, 1280-550, 720-440, 100, 20));

        walls.push_back(new Wall(this, 390, 720-310, 20, 10));
        walls.push_back(new Wall(this, 1280-410, 720-310, 20, 10));

        enemies.push_back(new Enemy(this, this->scene, "x", "jump", p, 4, 1280/2, 20, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "orbit", "jump", p, 4, 400, 320, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "orbit", "jump", p, 4, 1280-400, 320, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 40, 720-200-40, 20, 40);
        right_door = new Door(this, this, 1280-60, 720-200-40, 20, 40);
        up_door = new Door(this, this, 1280/2 -10, 720-550-40, 20, 40);
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f2-1.png");
        setPos(0,0);

        itemX = 1280/2 - 16;
        itemY = 720 - 32;

        boss = nullptr;

        type = "normal";
        name = "1";
    }
    else if(name_ == "f2-2"){
        walls.push_back(new Wall(this, 0, 720-150, 200, 150));
        walls.push_back(new Wall(this, 200, 720-75, 75, 75));
        walls.push_back(new Wall(this, 1280-200, 720-150, 200, 150));
        walls.push_back(new Wall(this, 1280-275, 720-75, 75, 75));

        walls.push_back(new Wall(this, 1280/2, 720-100, 50, 20));
        walls.push_back(new Wall(this, 1280/2, 720-20, 50, 20));
        walls.push_back(new Wall(this, 1280/2 + 10, 720-80, 30, 60));

        walls.push_back(new Wall(this, 400, 720-100, 50, 20));
        walls.push_back(new Wall(this, 400, 720-20, 50, 20));
        walls.push_back(new Wall(this, 400 + 10, 720-80, 30, 60));

        walls.push_back(new Wall(this, 850, 720-100, 50, 20));
        walls.push_back(new Wall(this, 850, 720-20, 50, 20));
        walls.push_back(new Wall(this, 850 + 10, 720-80, 30, 60));

        enemies.push_back(new Enemy(this, this->scene, "orbit", "jump", p, 4, 1280/2 + 25, 110, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "orbit", "jump", p, 4, 425, 110, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "orbit", "jump", p, 4, 1280-405, 110, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 40, 720-150-40, 20, 40);
        right_door = new Door(this, this, 1280-60, 720-150-40, 20, 40);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f2-2.png");
        setPos(0,0);

        itemX = 1280/2+25-16;
        itemY = 720 -100-32;

        boss = nullptr;

        type = "normal";
        name = "2";
    }
    else if(name_ == "f2-item"){
        walls.push_back(new Wall(this, 1280-300, 720-300, 300, 300));
        walls.push_back(new Wall(this, 1280-400, 720-350, 100, 350));
        walls.push_back(new Wall(this, 1280-550, 720-400, 150, 400));

        walls.push_back(new Wall(this, 1280-495, 720-420, 40, 20));
        walls.push_back(new Wall(this, 0, 0, 730, 720));

        left_door = nullptr;
        right_door = new Door(this, this, 1180, 720-300-40, 20, 40);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f2-item.png");
        setPos(0,0);

        itemX = 1280 - 483-24;
        itemY = 720 - 420 - 32;

        boss = nullptr;

        type = "treasure";
        name = "item";
    }
    else if(name_ == "f2-3"){
        walls.push_back(new Wall(this, 0, 720-150, 200, 150));
        walls.push_back(new Wall(this, 200, 720-75, 75, 75));
        walls.push_back(new Wall(this, 1280-200, 720-150, 200, 150));
        walls.push_back(new Wall(this, 1280-275, 720-75, 75, 75));

        walls.push_back(new Wall(this, 300, 720-250, 150, 30));
        walls.push_back(new Wall(this, 1280-450, 720-250, 150, 30));
        walls.push_back(new Wall(this, 570, 720-250, 150, 30));

        walls.push_back(new Wall(this, 450, 720-400, 150, 30));
        walls.push_back(new Wall(this, 1280 - 600, 720-400, 150, 30));

        enemies.push_back(new Enemy(this, this->scene, "x", "jump", p, 4, 450+75, 410, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "jump", p, 4, 1280-600 + 75, 410, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "orbit", "left_right", p, 4, 450, 260, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "orbit", "left_right", p, 4, 1280-300, 260, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 40, 720-150-40, 20, 40);
        right_door = new Door(this, this, 1280-60, 720-150-40, 20, 40);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f2-3.png");
        setPos(0,0);

        itemX = 1280/2 - 16;
        itemY = 720 - 32;

        boss = nullptr;

        type = "normal";
        name = "3";
    }
    else if(name_ == "f2-4"){
        walls.push_back(new Wall(this, 0, 720-150, 200, 150));
        walls.push_back(new Wall(this, 200, 720-75, 75, 75));
        walls.push_back(new Wall(this, 1280-200, 720-150, 200, 150));

        walls.push_back(new Wall(this, 1280-275, 720-75, 75, 75));
        walls.push_back(new Wall(this, 1280-350, 720-250, 100, 30));
        walls.push_back(new Wall(this, 1280-400, 720-280, 100, 30));
        walls.push_back(new Wall(this, 1280-450, 720-310, 100, 30));
        walls.push_back(new Wall(this, 1280-500, 720-340, 100, 30));
        walls.push_back(new Wall(this, 1280-550, 720-370, 100, 30));
        walls.push_back(new Wall(this, 1280-600, 720-400, 100, 30));
        walls.push_back(new Wall(this, 1280-650, 720-430, 100, 30));
        walls.push_back(new Wall(this, 1280-700, 720-460, 100, 30));
        walls.push_back(new Wall(this, 1280-950, 720-490, 300, 30));
        walls.push_back(new Wall(this, 1280-850, 720-580, 50, 20));

        walls.push_back(new Wall(this, 1280-970, 0, 20, 260));
        walls.push_back(new Wall(this, 1280-800 + 320, 0, 20, 160));
        walls.push_back(new Wall(this, 1280-800, 720-600, 320, 40));

        enemies.push_back(new Enemy(this, this->scene, "x", "left_right_jump", p, 4, 800, 20, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "cross", "jump", p, 4, 1200, 160, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "cross", "left_right", p, 4, 1280-650, 590, 0, 0, 10, 15, 2, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 60, 720-150-40, 20, 40);
        right_door = nullptr;
        up_door = new Door(this, this, 1280/2 - 20, 720-600-80, 40, 80);
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f2-4.png");
        setPos(0,0);

        itemX = 1280/2 - 16;
        itemY = 720 - 32;

        boss = nullptr;

        type = "normal";
        name = "4";
    }
    else if(name_ == "priest"){

        walls.push_back(new Wall(this, 580, 720-150, 120, 40));
        walls.push_back(new Wall(this, 1280/2 - 15, 720-110, 30, 60));
        walls.push_back(new Wall(this, 1280/2 - 30 - 10, 720-110, 20, 40));
        walls.push_back(new Wall(this, 1280/2 + 30 - 10, 720-110, 20, 40));

        walls.push_back(new Wall(this, 1280/2 - 25, 720 - 250, 50, 50));

        walls.push_back(new Wall(this, 200, 720-100, 100, 20));
        walls.push_back(new Wall(this, 1280-300, 720-100, 100, 20));

        walls.push_back(new Wall(this, 50, 720-200, 100, 20));
        walls.push_back(new Wall(this, 1280-150, 720-200, 100, 20));
        walls.push_back(new Wall(this, 1280-450, 720-200, 100, 20));
        walls.push_back(new Wall(this, 350, 720-200, 100, 20));

        walls.push_back(new Wall(this, 200, 720-300, 100, 20));
        walls.push_back(new Wall(this, 1280-300, 720-300, 100, 20));

        walls.push_back(new Wall(this, 280, 720-320, 20, 20));
        walls.push_back(new Wall(this, 1280-300, 720-320, 20, 20));

        walls.push_back(new Wall(this, 1280-450, 720-450, 100, 20));
        walls.push_back(new Wall(this, 350, 720-450, 100, 20));

        walls.push_back(new Wall(this, 500, 720-600, 100, 20));
        walls.push_back(new Wall(this, 680, 720-600, 100, 20));

        left_door = nullptr;
        right_door = nullptr;
        up_door = nullptr;
        down_door = new Door(this, this, 1280/2 - 10, 720-40, 20, 40);

        boss_door = new Door(this, nullptr, "boss", 150, 0, 150 - 20, 720-80, 40, 80, ":/Assets/Sprites/f2-boss-door.png");

        boss = new Boss(this, scene, "priest", p, 1280/2, 250, 0, 0, 25, 100, 200, 5, 1e-5, 0.1, 0);

        bg = new QPixmap(":/Assets/Sprites/f2-boss.png");
        setPos(0,0);

        itemX =  1280/2 - 16;
        itemY = 720 - 150 -32;

        type = "boss";
        name = "boss";
    }

    else if(name_ == "f3-item"){
        walls.push_back(new Wall(this, 1280-500, 720-300, 500, 300));
        walls.push_back(new Wall(this, 1280-550, 720-200, 50, 200));
        walls.push_back(new Wall(this, 1280-600, 720-100, 50, 100));
        walls.push_back(new Wall(this, 1280-700, 720-400, 100, 40));
        walls.push_back(new Wall(this, 1280-900, 720-500, 100, 40));
        walls.push_back(new Wall(this, 0, 720-600, 300, 40));

        left_door = nullptr;
        right_door = new Door(this, this, 1180, 720-300-40, 20, 40);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f3-item.png");
        setPos(0,0);

        itemX = 150 - 16;
        itemY = 720 - 600 - 32;

        boss = nullptr;

        type = "treasure";
        name = "item";
    }
    else if(name_ == "f3-1"){

        walls.push_back(new Wall(this, 0, 720 - 300, 150, 300));

        walls.push_back(new Wall(this, 250, 720 - 250, 300, 40));
        walls.push_back(new Wall(this, 1280 - 450, 720 - 250, 300, 40));
        walls.push_back(new Wall(this, 550, 720 - 380, 280, 40));
        walls.push_back(new Wall(this, 550, 720 - 120, 280, 40));

                enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 130, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
                enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 300, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
                enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 690, 400, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 150/2 -10, 720-300-40, 20, 40);
        right_door = new Door(this, this, 1280-280, 720-40, 20, 40);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f3-2.png");
        setPos(0,0);

        spring = new Spring(nullptr, 180, 5, 100, 40, 0.025f, 0.25f);

        itemX = 1280/2 - 16;
        itemY = 720 - 120 - 32;

        boss = nullptr;

        type = "normal";
        name = "1";
    }
    else if(name_ == "f3-safe"){
        walls.push_back(new Wall(this, 1280 - 300, 720 - 300, 300, 100));
        walls.push_back(new Wall(this, 1280-400, 720-200, 400, 100));
        walls.push_back(new Wall(this, 1280-500, 720-100, 500, 100));
        walls.push_back(new Wall(this, 400, 720 - 290, 150, 40));
        walls.push_back(new Wall(this, 400, 720 - 250, 350, 40));
        walls.push_back(new Wall(this, 100, 720 - 400, 250, 40));
        walls.push_back(new Wall(this, 420, 720 - 500, 80, 40));
        walls.push_back(new Wall(this, 550, 720 - 600, 500, 40));

        left_door = nullptr;
        right_door = new Door(this, this, 1280 - 100 - 10, 720-300-40, 20, 40);
        up_door = new Door(this, this, 900, 720-600-40, 20, 40);
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f3-safe.png");
        setPos(0,0);

        spring = new Spring(nullptr, 20, 5, 100, 40, 0.025f, 0.25f);

        itemX = 0;
        itemY = 0;

        boss = nullptr;

        type = "safe";
        name = "safe";
    }
    else if(name_ == "f3-2"){

        walls.push_back(new Wall(this, 0, 720 - 600, 300, 40));

        walls.push_back(new Wall(this, 250, 720 - 450, 400, 40));
        walls.push_back(new Wall(this, 150, 720 - 200, 50, 20));
        walls.push_back(new Wall(this, 150, 720 - 100, 50, 20));

        walls.push_back(new Wall(this, 0, 720 - 300, 150, 300));

        walls.push_back(new Wall(this, 800, 720-450, 50, 450));
        walls.push_back(new Wall(this, 850, 720-350, 50, 350));
        walls.push_back(new Wall(this, 900, 720-250, 50, 250));
        walls.push_back(new Wall(this, 950, 720-150, 50, 150));
        walls.push_back(new Wall(this, 1000, 720-50, 50, 50));

        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 480, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 825, 470, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 150/2 -10, 720-300-40, 20, 40);
        right_door = new Door(this, this, 1280-120, 720-40, 20, 40);
        up_door = new Door(this, this, 150 -10, 720-600-40, 20, 40);
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f3-1.png");
        setPos(0,0);

        spring = new Spring(nullptr, 760, 5, 100, 40, 0.025f, 0.25f);

        itemX = 450 - 16;
        itemY = 720 - 450 - 32;

        boss = nullptr;

        type = "normal";
        name = "2";
    }
    else if(name_ == "f3-3"){

        walls.push_back(new Wall(this, 0, 720 - 200, 300, 200));
        walls.push_back(new Wall(this, 300, 720 - 200, 50, 20));
        walls.push_back(new Wall(this, 300, 720 - 100, 50, 20));

        walls.push_back(new Wall(this, 800, 720 - 200, 300, 200));
        walls.push_back(new Wall(this, 1100, 720 - 100, 50, 100));

        walls.push_back(new Wall(this, 350, 720 - 350, 200, 40));
        walls.push_back(new Wall(this, 650, 720 - 450, 100, 40));
        walls.push_back(new Wall(this, 850, 720 - 550, 100, 40));
        walls.push_back(new Wall(this, 1050, 720 - 650, 150, 40));

        left_door = nullptr;
        right_door = nullptr;
        up_door = new Door(this, this, 1200, 720-650-40, 20, 40);
        down_door = nullptr;

        enemies.push_back(new Enemy(this, this->scene, "cross", "left_right_jump", p, 4, 150-10, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "double", "", p, 4, 1065, 650+20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 550, 20, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        bg = new QPixmap(":/Assets/Sprites/f3-3.png");
        setPos(0,0);

        spring = new Spring(nullptr, 1280-40, 5, 100, 40, 0.025f, 0.25f);

        itemX = 450 - 16;
        itemY = 720 - 350 - 32;

        boss = nullptr;

        type = "normal";
        name = "3";
    }
    else if(name_ == "f3-4"){
        walls.push_back(new Wall(this, 1280 - 200, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-500, 720-100, 200, 100));
        walls.push_back(new Wall(this, 1280-600, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280 - 800, 720 - 300, 200, 300));
        walls.push_back(new Wall(this, 1280-900, 720-200, 100, 200));
        walls.push_back(new Wall(this, 1280-1000, 720-100, 100, 100));

        walls.push_back(new Wall(this, 1280 - 200, 0, 200, 300));
        walls.push_back(new Wall(this, 1280-300, 0, 100, 200));
        walls.push_back(new Wall(this, 1280-400, 0, 100, 100));

        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280-700, 320, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));
        enemies.push_back(new Enemy(this, this->scene, "x", "", p, 4, 1280-400, 120, 0, 0, 10, 15, 5, 1e-5, 0.1, 0));

        left_door = new Door(this, this, 50, 720-40, 20, 40);
        right_door = new Door(this, this, 1280 - 100 - 20, 720-300-80, 40, 80);
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f3-4.png");
        setPos(0,0);

        itemX = 1280-700 - 16;
        itemY = 720 - 300 - 32;

        boss = nullptr;

        type = "normal";
        name = "4";
    }
    else if(name_ == "expelled"){
        walls.push_back(new Wall(this, 0, 720 - 100, 1280, 100));

        walls.push_back(new Wall(this, 150, 720 - 250, 150, 10));
        walls.push_back(new Wall(this, 1280-300, 720 -250, 150, 10));
        walls.push_back(new Wall(this, 1280-150-400, 720 - 400, 150, 10));
        walls.push_back(new Wall(this, 400, 720 - 400, 150, 10));

        left_door = new Door(this, this, 0, 720-140, 20, 40);
        right_door = nullptr;
        up_door = nullptr;
        down_door = nullptr;

        bg = new QPixmap(":/Assets/Sprites/f3-boss.png");
        setPos(0,0);

        boss_door = new Door(this, nullptr, "final_boss", 0, 0, 1280 - 150 - 20, 720-100-80, 40, 80, ":/Assets/Sprites/f3-boss-door.png");

        boss = new Boss(this, scene, "expelled", p, 1200, 220, 0, 0, 20, 60, 120, 5, 1e-5, 0.1, 0);

        itemX =  250;
        itemY = 720 - 16;

        type = "final_boss";
        name = "boss";
    }

    else{
        itemX =  0;
        itemY = 0;

        left_door = nullptr;
        right_door = nullptr;
        up_door = nullptr;
        down_door = nullptr;

        type = "normal";
        name = "0";
        boss = nullptr;
    }
}
Room::~Room() {

    walls.clear();
    enemies.clear();

    if(left_door != nullptr)
        delete left_door;
    if(right_door != nullptr)
        delete right_door;
    if(up_door != nullptr)
        delete up_door;
    if(down_door != nullptr)
        delete down_door;
    if(boss_door != nullptr)
        delete boss_door;
    if(item != nullptr)
        delete item;
    if(item != nullptr)
        delete boss;
    if(bg != nullptr)
        delete bg;
    if(spring != nullptr)
        delete spring;
}

void Room::load_room() {

    if(bg != nullptr)
        scene->addItem(this);

    if(spring != nullptr)
        scene->addItem(spring);

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->addItem(*k);
        (*k)->setPos((*k)->getPosx(), (*k)->getPosy());
    }

    if(type == "normal")
        for(auto k = enemies.begin(); k!=enemies.end(); k++){
            scene->addItem(*k);
            (*k)->setPos((*k)->getX(), (*k)->getY());
            (*k)->init();
        }

    if(type == "boss" || type == "final_boss"){
        if(boss != nullptr){
            scene->addItem(boss);
            boss->setPos(boss->getX(), boss->getY());
            boss->init();
        }
        if(cleared)
            scene->addItem(boss_door);
    }

    if(left_door != nullptr) {
        scene->addItem(left_door);
        left_door->setPos(left_door->getPosx(), left_door->getPosy());
    }
    if(right_door != nullptr) {
        scene->addItem(right_door);
        right_door->setPos(right_door->getPosx(), right_door->getPosy());
    }
    if(up_door != nullptr) {
        scene->addItem(up_door);
        up_door->setPos(up_door->getPosx(), up_door->getPosy());
    }
    if(down_door != nullptr) {
        scene->addItem(down_door);
        down_door->setPos(down_door->getPosx(), down_door->getPosy());
    }

    if(item != nullptr){
        scene->addItem(item);
        item->setPos(itemX, itemY);
        //item->getName()->raise();
        //item->getName()->setHidden(false);
    }
}
void Room::deload_room() {

    if(bg != nullptr)
        scene->removeItem(this);

    if(spring != nullptr)
        scene->removeItem(spring);

    for(auto k = walls.begin(); k!=walls.end(); k++){
        scene->removeItem(*k);
    }

    if(type == "normal")
        for(auto k = enemies.begin(); k!=enemies.end(); k++){
            scene->removeItem(*k);
            (*k)->stop();
        }

    if(type == "boss" || type == "final_boss"){
        if(boss != nullptr){
            scene->removeItem(boss);
            boss->stop();
        }
        if(cleared)
            scene->removeItem(boss_door);
    }

    if(left_door != nullptr)
        scene->removeItem(left_door);
    if(right_door != nullptr)
        scene->removeItem(right_door);
    if(up_door != nullptr)
        scene->removeItem(up_door);
    if(down_door != nullptr)
        scene->removeItem(down_door);

    if(item != nullptr){
        scene->removeItem(item);
        //item->getName()->setHidden(true);
    }
}

std::list<Enemy *> Room::getEnemies() const {
    return enemies;
}

QRectF Room::boundingRect() const {
    return QRectF(0, 0, 1280, 720);
}
void Room::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    painter->drawPixmap(0, 0, *bg, 0, 0, 1280, 720);
}

void Room::clear_room() {
    cleared = true;

    if(type == "normal")
        enemies.clear();

    else  if(type == "boss" || type == "final_boss") {
        delete boss;
        boss = nullptr;

        scene->addItem(boss_door);
    }
}
bool Room::isClear() const {
    return cleared;
}

std::string Room::getType() const {
    return type;
}
Boss *Room::getBoss() const {
    return boss;
}

int Room::getItemX() const {
    return itemX;
}
int Room::getItemY() const {
    return itemY;
}
Spring *Room::getSpring() const {
    return spring;
}
std::string Room::getName() const {
    return name;
}

void Room::remove_item() {
    scene->removeItem(item);
    delete item;
    item = nullptr;
}

void Room::spawn_heart() {
    item = new Item(nullptr, "Heart", 1, 0.2, 1, 1, 1, 1, 1, 1 ,1, 1, 1, "single", ":/Assets/Sprites/Items/heart.png");
    item->setPos(itemX, itemY);
    scene->addItem(item);
    item->updateLabel(itemX, itemY);
    scene->addWidget(item->getName_label());
    item->getName_label()->setVisible(true);
}
void Room::spawn_item(Item *i) {

    if(i != nullptr) {
        item = i;
        item->setPos(itemX, itemY);
        scene->addItem(item);
        item->updateLabel(itemX, itemY);
        scene->addWidget(item->getName_label());
        item->getName_label()->setVisible(true);
    }
}
