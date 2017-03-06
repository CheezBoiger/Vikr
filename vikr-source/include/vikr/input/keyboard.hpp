//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_KEYBOARD_HPP
#define __VIKR_KEYBOARD_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/input/window.hpp>
#include <unordered_map>


// VIKR Key Codes... They are glfw keycodes

/*! @} */

/*! @name Boolean values
*  @{ */
/*! @brief One.
*
*  One.  Seriously.  You don't _need_ to use this symbol in your code.  It's
*  just semantic sugar for the number 1.  You can use `1` or `true` or `_True`
*  or `GL_TRUE` or whatever you want.
*/
#define VIKR_TRUE                   1
/*! @brief Zero.
*
*  Zero.  Seriously.  You don't _need_ to use this symbol in your code.  It's
*  just just semantic sugar for the number 0.  You can use `0` or `false` or
*  `_False` or `GL_FALSE` or whatever you want.
*/
#define VIKR_FALSE                  0
/*! @} */

/*! @name Key and button actions
*  @{ */
/*! @brief The key or mouse button was released.
*
*  The key or mouse button was released.
*
*  @ingroup input
*/
#define VIKR_RELEASE                0
/*! @brief The key or mouse button was pressed.
*
*  The key or mouse button was pressed.
*
*  @ingroup input
*/
#define VIKR_PRESS                  1
/*! @brief The key was held down until it repeated.
*
*  The key was held down until it repeated.
*
*  @ingroup input
*/
#define VIKR_REPEAT                 2


/* The unknown key */
#define VIKR_KEY_UNKNOWN            -1

/* Printable keys */
#define VIKR_KEY_SPACE              32
#define VIKR_KEY_APOSTROPHE         39  /* ' */
#define VIKR_KEY_COMMA              44  /* , */
#define VIKR_KEY_MINUS              45  /* - */
#define VIKR_KEY_PERIOD             46  /* . */
#define VIKR_KEY_SLASH              47  /* / */
#define VIKR_KEY_0                  48
#define VIKR_KEY_1                  49
#define VIKR_KEY_2                  50
#define VIKR_KEY_3                  51
#define VIKR_KEY_4                  52
#define VIKR_KEY_5                  53
#define VIKR_KEY_6                  54
#define VIKR_KEY_7                  55
#define VIKR_KEY_8                  56
#define VIKR_KEY_9                  57
#define VIKR_KEY_SEMICOLON          59  /* ; */
#define VIKR_KEY_EQUAL              61  /* = */
#define VIKR_KEY_A                  65
#define VIKR_KEY_B                  66
#define VIKR_KEY_C                  67
#define VIKR_KEY_D                  68
#define VIKR_KEY_E                  69
#define VIKR_KEY_F                  70
#define VIKR_KEY_G                  71
#define VIKR_KEY_H                  72
#define VIKR_KEY_I                  73
#define VIKR_KEY_J                  74
#define VIKR_KEY_K                  75
#define VIKR_KEY_L                  76
#define VIKR_KEY_M                  77
#define VIKR_KEY_N                  78
#define VIKR_KEY_O                  79
#define VIKR_KEY_P                  80
#define VIKR_KEY_Q                  81
#define VIKR_KEY_R                  82
#define VIKR_KEY_S                  83
#define VIKR_KEY_T                  84
#define VIKR_KEY_U                  85
#define VIKR_KEY_V                  86
#define VIKR_KEY_W                  87
#define VIKR_KEY_X                  88
#define VIKR_KEY_Y                  89
#define VIKR_KEY_Z                  90
#define VIKR_KEY_LEFT_BRACKET       91  /* [ */
#define VIKR_KEY_BACKSLASH          92  /* \ */
#define VIKR_KEY_RIGHT_BRACKET      93  /* ] */
#define VIKR_KEY_GRAVE_ACCENT       96  /* ` */
#define VIKR_KEY_WORLD_1            161 /* non-US #1 */
#define VIKR_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define VIKR_KEY_ESCAPE             256
#define VIKR_KEY_ENTER              257
#define VIKR_KEY_TAB                258
#define VIKR_KEY_BACKSPACE          259
#define VIKR_KEY_INSERT             260
#define VIKR_KEY_DELETE             261
#define VIKR_KEY_RIGHT              262
#define VIKR_KEY_LEFT               263
#define VIKR_KEY_DOWN               264
#define VIKR_KEY_UP                 265
#define VIKR_KEY_PAGE_UP            266
#define VIKR_KEY_PAGE_DOWN          267
#define VIKR_KEY_HOME               268
#define VIKR_KEY_END                269
#define VIKR_KEY_CAPS_LOCK          280
#define VIKR_KEY_SCROLL_LOCK        281
#define VIKR_KEY_NUM_LOCK           282
#define VIKR_KEY_PRINT_SCREEN       283
#define VIKR_KEY_PAUSE              284
#define VIKR_KEY_F1                 290
#define VIKR_KEY_F2                 291
#define VIKR_KEY_F3                 292
#define VIKR_KEY_F4                 293
#define VIKR_KEY_F5                 294
#define VIKR_KEY_F6                 295
#define VIKR_KEY_F7                 296
#define VIKR_KEY_F8                 297
#define VIKR_KEY_F9                 298
#define VIKR_KEY_F10                299
#define VIKR_KEY_F11                300
#define VIKR_KEY_F12                301
#define VIKR_KEY_F13                302
#define VIKR_KEY_F14                303
#define VIKR_KEY_F15                304
#define VIKR_KEY_F16                305
#define VIKR_KEY_F17                306
#define VIKR_KEY_F18                307
#define VIKR_KEY_F19                308
#define VIKR_KEY_F20                309
#define VIKR_KEY_F21                310
#define VIKR_KEY_F22                311
#define VIKR_KEY_F23                312
#define VIKR_KEY_F24                313
#define VIKR_KEY_F25                314
#define VIKR_KEY_KP_0               320
#define VIKR_KEY_KP_1               321
#define VIKR_KEY_KP_2               322
#define VIKR_KEY_KP_3               323
#define VIKR_KEY_KP_4               324
#define VIKR_KEY_KP_5               325
#define VIKR_KEY_KP_6               326
#define VIKR_KEY_KP_7               327
#define VIKR_KEY_KP_8               328
#define VIKR_KEY_KP_9               329
#define VIKR_KEY_KP_DECIMAL         330
#define VIKR_KEY_KP_DIVIDE          331
#define VIKR_KEY_KP_MULTIPLY        332
#define VIKR_KEY_KP_SUBTRACT        333
#define VIKR_KEY_KP_ADD             334
#define VIKR_KEY_KP_ENTER           335
#define VIKR_KEY_KP_EQUAL           336
#define VIKR_KEY_LEFT_SHIFT         340
#define VIKR_KEY_LEFT_CONTROL       341
#define VIKR_KEY_LEFT_ALT           342
#define VIKR_KEY_LEFT_SUPER         343
#define VIKR_KEY_RIGHT_SHIFT        344
#define VIKR_KEY_RIGHT_CONTROL      345
#define VIKR_KEY_RIGHT_ALT          346
#define VIKR_KEY_RIGHT_SUPER        347
#define VIKR_KEY_MENU               348

#define VIKR_KEY_LAST               VIKR_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
*
*  See [key input](@ref input_key) for how these are used.
*
*  @ingroup input
*  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
*/
#define VIKR_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
*/
#define VIKR_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
*/
#define VIKR_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
*/
#define VIKR_MOD_SUPER           0x0008

#define VIKR_MOUSE_BUTTON_1         0
#define VIKR_MOUSE_BUTTON_2         1
#define VIKR_MOUSE_BUTTON_3         2
#define VIKR_MOUSE_BUTTON_4         3
#define VIKR_MOUSE_BUTTON_5         4
#define VIKR_MOUSE_BUTTON_6         5
#define VIKR_MOUSE_BUTTON_7         6
#define VIKR_MOUSE_BUTTON_8         7
#define VIKR_MOUSE_BUTTON_LAST      VIKR_MOUSE_BUTTON_8
#define VIKR_MOUSE_BUTTON_LEFT      VIKR_MOUSE_BUTTON_1
#define VIKR_MOUSE_BUTTON_RIGHT     VIKR_MOUSE_BUTTON_2
#define VIKR_MOUSE_BUTTON_MIDDLE    VIKR_MOUSE_BUTTON_3

#define VIKR_JOYSTICK_1             0
#define VIKR_JOYSTICK_2             1
#define VIKR_JOYSTICK_3             2
#define VIKR_JOYSTICK_4             3
#define VIKR_JOYSTICK_5             4
#define VIKR_JOYSTICK_6             5
#define VIKR_JOYSTICK_7             6
#define VIKR_JOYSTICK_8             7
#define VIKR_JOYSTICK_9             8
#define VIKR_JOYSTICK_10            9
#define VIKR_JOYSTICK_11            10
#define VIKR_JOYSTICK_12            11
#define VIKR_JOYSTICK_13            12
#define VIKR_JOYSTICK_14            13
#define VIKR_JOYSTICK_15            14
#define VIKR_JOYSTICK_16            15
#define VIKR_JOYSTICK_LAST          VIKR_JOYSTICK_16




namespace vikr {



typedef void(*KeyboardCallback)(VikrWindow*, int, int, int, int);

/**
  Keyboard handle.
*/
class Keyboard {
public:

  /**
    Key enums
  */
  enum Key {
    KEY_UNKNOWN = VIKR_KEY_UNKNOWN,
    KEY_SPACE = VIKR_KEY_SPACE,
    KEY_APOSTROPHE = VIKR_KEY_APOSTROPHE,
    KEY_COMMA = VIKR_KEY_COMMA,
    KEY_MINUS = VIKR_KEY_MINUS,
    KEY_PERIOD = VIKR_KEY_PERIOD,
    KEY_SLASH = VIKR_KEY_SLASH,
    KEY_0 = VIKR_KEY_0,
    KEY_1 = VIKR_KEY_1,
    KEY_2 = VIKR_KEY_2,
    KEY_3 = VIKR_KEY_3,
    KEY_4 = VIKR_KEY_4,
    KEY_5 = VIKR_KEY_5,
    KEY_6 = VIKR_KEY_6,
    KEY_7 = VIKR_KEY_7,
    KEY_8 = VIKR_KEY_8,
    KEY_9 = VIKR_KEY_9,
    KEY_SEMICOLON = VIKR_KEY_SEMICOLON,
    KEY_EQUAL = VIKR_KEY_EQUAL,
    KEY_A = VIKR_KEY_A,
    KEY_B = VIKR_KEY_B,
    KEY_C = VIKR_KEY_C,
    KEY_D = VIKR_KEY_D,
    KEY_E = VIKR_KEY_E,
    KEY_F = VIKR_KEY_F,
    KEY_G = VIKR_KEY_G,
    KEY_H = VIKR_KEY_H,
    KEY_I = VIKR_KEY_I,
    KEY_J = VIKR_KEY_J,
    KEY_K = VIKR_KEY_K,
    KEY_L = VIKR_KEY_L,
    KEY_M = VIKR_KEY_M,
    KEY_N = VIKR_KEY_N,
    KEY_O = VIKR_KEY_O,
    KEY_P = VIKR_KEY_P,
    KEY_Q = VIKR_KEY_Q,
    KEY_R = VIKR_KEY_R,
    KEY_S = VIKR_KEY_S,
    KEY_T = VIKR_KEY_T,
    KEY_U = VIKR_KEY_U,
    KEY_V = VIKR_KEY_V,
    KEY_W = VIKR_KEY_W,
    KEY_X = VIKR_KEY_X,
    KEY_Y = VIKR_KEY_Y,
    KEY_Z = VIKR_KEY_Z,
    KEY_LEFT_BRACKET = VIKR_KEY_LEFT_BRACKET,
    KEY_BACKSLASH = VIKR_KEY_BACKSLASH,
    KEY_RIGHT_BRACKET = VIKR_KEY_RIGHT_BRACKET,
    KEY_GRAVE_ACCENT = VIKR_KEY_GRAVE_ACCENT,
    KEY_WORLD_1 = VIKR_KEY_WORLD_1,
    KEY_WORLD_2 = VIKR_KEY_WORLD_2,
    
    KEY_ESCAPE = VIKR_KEY_ESCAPE,
    KEY_ENTER = VIKR_KEY_ENTER,
    KEY_TAB = VIKR_KEY_TAB,
    KEY_BACKSPACE = VIKR_KEY_BACKSPACE,
    KEY_INSERT = VIKR_KEY_INSERT,
    KEY_DELETE = VIKR_KEY_DELETE,
    KEY_RIGHT = VIKR_KEY_RIGHT,
    KEY_LEFT = VIKR_KEY_LEFT,
    KEY_DOWN = VIKR_KEY_DOWN,
    KEY_UP = VIKR_KEY_UP,
    KEY_PAGE_UP = VIKR_KEY_PAGE_UP,
    KEY_PAGE_DOWN = VIKR_KEY_PAGE_DOWN,
    KEY_HOME = VIKR_KEY_HOME,
    KEY_END = VIKR_KEY_END,
    KEY_CAPS_LOCK = VIKR_KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK = VIKR_KEY_SCROLL_LOCK,
    KEY_NUM_LOCK = VIKR_KEY_NUM_LOCK,
    KEY_PRINT_SCREEN = VIKR_KEY_PRINT_SCREEN,
    KEY_PAUSE = VIKR_KEY_PAUSE,
    KEY_F1 = VIKR_KEY_F1,
    KEY_F2 = VIKR_KEY_F2,
    KEY_F3 = VIKR_KEY_F3,
    KEY_F4 = VIKR_KEY_F4,
    KEY_F5 = VIKR_KEY_F5,
    KEY_F6 = VIKR_KEY_F6,
    KEY_F7 = VIKR_KEY_F7,
    KEY_F8 = VIKR_KEY_F8,
    KEY_F9 = VIKR_KEY_F9,
    KEY_F10 = VIKR_KEY_F10,
    KEY_F11 = VIKR_KEY_F11,
    KEY_F12 = VIKR_KEY_F12,
    KEY_F13 = VIKR_KEY_F13,
    KEY_F14 = VIKR_KEY_F14,
    KEY_F15 = VIKR_KEY_F15,
    KEY_F16 = VIKR_KEY_F16,
    KEY_F17 = VIKR_KEY_F17,
    KEY_F18 = VIKR_KEY_F18,
    KEY_F19 = VIKR_KEY_F19,
    KEY_F20 = VIKR_KEY_F20,
    KEY_F21 = VIKR_KEY_F21,
    KEY_F22 = VIKR_KEY_F22,
    KEY_F23 = VIKR_KEY_F23,
    KEY_F24 = VIKR_KEY_F24,
    KEY_F25 = VIKR_KEY_F25,
    KEY_KP_0 = VIKR_KEY_KP_0,
    KEY_KP_1 = VIKR_KEY_KP_1,
    KEY_KP_2 = VIKR_KEY_KP_2,
    KEY_KP_3 = VIKR_KEY_KP_3,
    KEY_KP_4 = VIKR_KEY_KP_4,
    KEY_KP_5 = VIKR_KEY_KP_5,
    KEY_KP_6 = VIKR_KEY_KP_6,
    KEY_KP_7 = VIKR_KEY_KP_7,
    KEY_KP_8 = VIKR_KEY_KP_8,
    KEY_KP_9 = VIKR_KEY_KP_9,
    KEY_KP_DECIMAL = VIKR_KEY_KP_DECIMAL,
    KEY_KP_DIVIDE = VIKR_KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY = VIKR_KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT = VIKR_KEY_KP_SUBTRACT,
    KEY_KP_ADD = VIKR_KEY_KP_ADD,
    KEY_KP_ENTER = VIKR_KEY_KP_ENTER,
    KEY_KP_EQUAL = VIKR_KEY_KP_EQUAL,
    KEY_LEFT_SHIFT = VIKR_KEY_LEFT_SHIFT,
    KEY_LEFT_CNTRL = VIKR_KEY_LEFT_CONTROL,
    KEY_LEFT_CONTROL = VIKR_KEY_LEFT_CONTROL,
    KEY_LEFT_ALT = VIKR_KEY_LEFT_ALT,
    KEY_LEFT_SUPER = VIKR_KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT = VIKR_KEY_RIGHT_SHIFT,
    KEY_RIGHT_CNTRL = VIKR_KEY_RIGHT_CONTROL,
    KEY_RIGHT_CONTROL = VIKR_KEY_RIGHT_CONTROL,
    KEY_RIGHT_ALT = VIKR_KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER = VIKR_KEY_RIGHT_SUPER,
    KEY_MENU = VIKR_KEY_MENU,
    KEY_LAST = VIKR_KEY_MENU,
  };

  enum Mode {
    KEY_RELEASED = -1,
    KEY_RELEASE = VIKR_RELEASE,
    KEY_PRESS = VIKR_PRESS,
    KEY_REPEAT = VIKR_REPEAT,
  };

  static vbool IsPressed(Key key) { return key_map[key] == KEY_PRESS; }
  static vbool IsRepeating(Key key) { return key_map[key] == KEY_REPEAT; }
  static vbool IsReleasing(Key key) { return key_map[key] = KEY_RELEASE; }
  static vbool IsReleased(Key key) { return key_map[key] = KEY_RELEASED; }

  static vint32 RegisterKeyboardCallback(KeyboardCallback callback);
  static vint32 UnRegisterKeyboardCallback();
  
  static KeyboardCallback GetKeyboardCallback() { return callback; }
  static vbool SetEnable(vbool enable);

  static vvoid DefaultKeyCallback(VikrWindow *window, vint32 key, 
    vint32 scancode, vint32 action, vint32 mode);

  static std::unordered_map<Key, Mode> key_map;

private:

  static vbool enable;
  static KeyboardCallback callback;
};
}
#endif // __VIKR_KEYBOARD_HPP