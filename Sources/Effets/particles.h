typedef enum{BALLISTIC, PLASMA, EXPLOSIVE} weaponType;

typedef struct{
    int speed;
    int damage;
    weaponType type;
    GameObject *parent;
} projectile;

typedef struct{
    int speed;
    int damage;
    weaponType type;
    GameObject *parent;
} hit;