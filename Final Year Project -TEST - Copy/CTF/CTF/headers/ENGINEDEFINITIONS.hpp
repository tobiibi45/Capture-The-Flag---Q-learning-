#pragma once

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define WINDOW_TITLE "Capture The Flag"

/*SPLASH SCREEN FEATURES*/
#define SPLASH_STATE_SHOW_TIME 3.0
#define LOGO_FILEPATH "..//..//assets//images//kStudio.fw.png"
#define SPLASH_SCENE_BACKGROUND_FILEPATH "..//..//assets//images//splashBG.fw.png"

/*MAIN MENU SCREEN FEATURES*/
#define MAIN_MENU_BACKGROUND_FILEPATH "..//..//assets//images//mmBackG.jpg"
#define MAIN_MENU_NEWGAME_FILEPATH "..//..//assets//images//newgame.fw.png"
#define MAIN_MENU_SETTINGS_FILEPATH "..//..//assets//images//settings.fw.png"
#define MAIN_MENU_EXIT_FILEPATH "..//..//assets//images//exit.fw.png"
#define MAIN_MENU_CHARACTERS_FILEPATH "..//..//assets//images//menuCHs.fw.png"

/*SETTINGS SCREEN FEATURES*/
#define SETTINGS_BACKGROUND_FILEPATH "..//..//assets//images//pausebackG.fw.png"
#define SETTINGS_EXIT_FILEPATH "..//..//assets//images//exitstt.fw.png"
#define SETTINGS_MUSIC_VOLUME_FILEPATH "..//..//assets//images//mVolume.fw.png"
#define SETTINGS_EFFECTS_VOLUME_FILEPATH "..//..//assets//images//sVolume.fw.png"
#define SETTINGS_ADD_FILEPATH "..//..//assets//images//add1.fw.png"
#define SETTINGS_SUBTRACT_FILEPATH "..//..//assets//images//subtract2.fw.png"

/*PAUSE SCREEN FEATURES*/
#define PAUSE_BACKGROUND_FILEPATH "..//..//assets//images//pausebackG.fw.png"
#define PAUSE_BUTTON_FILEPATH "..//..//assets//images//pause.fw.png"
#define PAUSE_SETTINGS_FILEPATH "..//..//assets//images//settings.fw.png"
#define PAUSE_EXIT_FILEPATH "..//..//assets//images//exit.fw.png"
#define PAUSE_RESUME_FILEPATH "..//..//assets//images//resume.fw.png"

/*GAME OVER SCREEN FEATURES*/
#define WINNER_MESSAGE_FILEPATH "..//..//assets//images//winner.fw.png"
#define LOSER_MESSAGE_FILEPATH "..//..//assets//images//lose.fw.png"
#define RETRY_MESSAGE_FILEPATH "..//..//assets//images//retry.fw.png"
#define DRAW_MESSAGE_FILEPATH "..//..//assets//images//draw.fw.png"
#define EXIT_FILEPATH "..//..//assets//images//exit.fw.png"

/*GAME SCREEN FEATURES*/
#define GAME_BACKGROUND_FILEPATH "..//..//assets//images//map.fw.png"
#define PLAYER1_FILEPATH "..//..//assets//images//girledit.fw.png"
#define PLAYER2_FILEPATH "..//..//assets//images//boyedit.fw.png"
#define ENEMY_FILEPATH "..//..//assets//images//doctor1.fw.png"
#define FLAGS_CAPTURED_PLAYER "..//..//assets//images//flagCap.fw.png"
#define FLAGS_CAPTURED_ENEMY "..//..//assets//images//flagCapE.fw.png"

/*MUSIC FILES*/
#define MUSIC_GAMEPLAY "..//..//assets//audio//gameplay.wav"
#define MUSCI_MENU "..//..//assets//audio//menu.wav"
#define MUSIC_EFFECT_BULLET "..//..//assets//audio//bullet.wav"
#define MUSIC_EFFECT_DEATH "..//..//assets//audio//death.wav"
#define MUSIC_EFFECT_TIMER "..//..//assets//audio//countdown1m.wav"

/*GAME OBJECTS */
#define LEFT_BOTTOM_BUSH "..//..//assets//images//wall_BL.fw.png"
#define RIGHT_BOTTOM_BUSH "..//..//assets//images//wall_BR.fw.png"
#define LEFT_TOP_BUSH "..//..//assets//images//wall_TL.fw.png"
#define RIGHT_TOP_BUSH "..//..//assets//images//wall_TR.fw.png"
#define MIDDLE_BUSH_VERTICAL "..//..//assets//images//wall.fw.png"
#define MIDDLE_BUSH_HORIZONTAL "..//..//assets//images//wall_rotated.fw.png"
#define FLAT_LEFT_BUSH "..//..//assets//images//wall_flat_L.fw.png"
#define FLAT_RIGHT_BUSH "..//..//assets//images//wall_flat_R.fw.png"
#define PEDESTAL_RED "..//..//assets//images//pedRed.fw.png"
#define PEDESTAL_BLUE "..//..//assets//images//pedBlue.fw.png"
#define RED_FLAG "..//..//assets//images//rFlag.fw.png"
#define BLUE_FLAG "..//..//assets//images//bFlag.fw.png"
#define RED_BULLET "..//..//assets//images//rbullet.fw.png"
#define BLUE_BULLET "..//..//assets//images//bbullet.fw.png"
#define HEALTHBAR "..//..//assets//images//healthbar.fw.png"
#define HEALTHBAR_BACKG "..//..//assets//images//healthbar_backg.fw.png"
#define MAX_HEALTH 100.f
#define MAX_BULLET 10
#define SHOOTING_DELAY 1
#define RESPAWN_DELAY 10
#define WORLD_X_BUFFER 390.f
#define WORLD_Y_BUFFER 15.f
#define CELL_SIZE 20.f
#define WORLD_SIZE 128
#define WALLS_BUFFER 1.25f
#define WALLS_BUFFER2 1.15f

static const float SCALE = 30.f;

static const short BIT_WALLS = 2;
static const short BIT_PLAYER = 4;
static const short BIT_ENEMY = 8;
static const short BIT_BULLET = 16;
static const short BIT_BORDER = 32;
static const short BIT_RED_PED = 64;
static const short BIT_BLUE_PED = 128;
static const short BIT_RED_FLAG = 256;
static const short BIT_BLUE_FLAG = 512;
static const short BIT_ENEMY_RADER = 1024;
static const short BIT_ENEMY_BULLET = 2048;
static const short BIT_PLAYER_BASE_AREA = 4096;
static const short BIT_ENEMY_BASE_AREA = 8196;
static const short BIT_ENEMY_OBJECT_FINDER = 16392;

static const float BULLET_SPPED = 100.f;

#define STATE_PLAYING 98
#define STATE_WON 97
#define STATE_LOSE 96
#define STATE_DRAW 95

#define GAME_OVER_SHOW_TIME 5.0
#define GAME_TIME 180
#define SCORE_FONT "..//..//assets//fonts//font.ttf"

#define ENEMY_HEALTH_RANGE 20

//////////////////////////////Q-LEARNER////////////////////////////




struct bodyUserData {
	int type;
};