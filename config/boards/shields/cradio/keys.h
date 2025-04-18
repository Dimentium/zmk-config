// Aliases

#define KEY_Q 0
#define KEY_W 1
#define KEY_E 2
#define KEY_R 3
#define KEY_T 4

#define KEY_Y 5
#define KEY_U 6
#define KEY_I 7
#define KEY_O 8
#define KEY_P 9

#define KEY_A 10
#define KEY_S 11
#define KEY_D 12
#define KEY_F 13
#define KEY_G 14

#define KEY_H 15
#define KEY_J 16
#define KEY_K 17
#define KEY_L 18
#define KEY_QUOTE 19

#define KEY_Z 20
#define KEY_X 21
#define KEY_C 22
#define KEY_V 23
#define KEY_B 24

#define KEY_N 25
#define KEY_M 26
#define KEY_COMMA 27
#define KEY_DOT   28
#define KEY_FSLH  29

#define THUMB_LL 30
#define THUMB_LR 31
#define THUMB_RL 32
#define THUMB_RR 33

#define LEFT_HALF   0  1  2  3  4 10 11 12 13 14 20 21 22 23 24 
#define RIGHT_HALF  5  6  7  8  9 15 16 17 18 19 25 26 27 28 29
#define THUMBS     30 31 32 33

#define COMBO(NAME, BINDINGS, KEYPOS, LAYERS) \
  combo_##NAME { \
    timeout-ms = <65>; \
    bindings = <BINDINGS>; \
    key-positions = <KEYPOS>; \
    layers = <LAYERS>; \
};

#define MOD_MACRO(name, mod)                            \
name: name## {                                    \
    compatible = "zmk,behavior-macro";              \
    #binding-cells = <0>;                           \
    wait-ms = <0>;                                  \
    bindings                                            \
        = <&macro_press &kp mod>                        \
        , <&macro_pause_for_release>                    \
        , <&macro_release &kp mod>;                     \
 };

// EOF