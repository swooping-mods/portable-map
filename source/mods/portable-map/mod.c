#define MOD_INPUT_ACTIONS {{"portable-map.toggle","!Ctrl+!Shift+!Alt+F12",0x7b}}
#define FEATURE 15
#define MOD_ID "portable-map"
#define HUD_Y 420
#define FW_NAME "Portable Map"
#define FW_DESC "Open the native map from anywhere on foot."
#define FW_PRICE 200
#define FW_TEMPLATE 0
#include "runtime.h"
static int opened_here;
static void feature_end(void){fw_clear();PTR o=dget(m.map);if(opened_here&&malive(o)&&mapopen(o)){int ok=1;call(m.mapping.map_close,o,0,&ok);}opened_here=0;}
static void feature_tick(PTR walker,PTR world,int input){
 (void)world;(void)input;int ok=1;PTR screen=map();int open=mapopen(screen),blocked=boolean(m.blocked,walker,&ok);
 m.active_tool=fw_equipped(walker);
 if(!m.active_tool){if(opened_here)feature_end();else fw_clear();return;}
 if(m.pressed[0x7b]&&screen&&(!blocked||open)){
  call(open?m.mapping.map_close:m.mapping.map_begin,screen,0,&ok);if(ok){opened_here=!open;ddrop(&m.map);m.map=dhold(screen);}m.status=ok?"":"Map unavailable";
 }
 if(opened_here&&!open&&!mapopen(screen))opened_here=0;
 char key[64]="F12",text[96];moon_input_label("portable-map.toggle","!Ctrl+!Shift+!Alt+F12",key,sizeof(key));cat(cat(text,key),": Open / close map");fw_hints->publish(MOD_ID,walker,text);
}
