#ifndef TYPE_HPP
#define TYPE_HPP

typedef enum ButtonType {
    START_BUTTON,
    EXIT_BUTTON,
    BACK_BUTTON,
    NEXT_BUTTON,
    RESTART_BUTTON,
    PAUSE_BUTTON,
    RESUME_BUTTON,
    FASTFORWARD_BUTTON,
    CHEAT_BUTTON,
} ButtonType;

typedef enum GameState {
    WON,
    LOST,
    ONGOING,
} GameState;

typedef enum BirdType {
    RED,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    BIG,
} BirdType;

typedef enum PigType {
    NORMAL,
    KING,
    SOLDIER,
} PigType;

typedef enum StructureType {
    FRAME_BLOCK,
    FRAME_TRIANGLE,
    TRIANGLE,
    DISC,
    RECTANGLE,
    BLOCK,
    BAR_LONG,
    RECTANGLE_SMALL,
    BAR,
    BLOCK_SMALL,
    BAR_SHORT,
    DISC_SMALL,
} StructureType;

typedef enum EntityType {
    BIRD,
    PIG,
    WOOD,
    STONE,
    GLASS,
} EntityType;

typedef struct Entity {
    union {
        BirdType birdType;
        PigType pigType;
        StructureType structureType;
    };
} Entity;


typedef enum  DamageLevel {
    NONE,
    LIGHT,
    MEDIUM,
    HEAVY,
} DamageLevel ;

#endif //TYPE_HPP
