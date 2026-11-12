/* A rooted screen is an outstanding restoration obligation. Keep the exact
 * receiver through failed calls, scene replacement and cleanup retries. */
static int opened_here, map_returning;
static int map_observe(PTR screen,int *open){
 int ok=1;void *a[]={screen};
 PTR live=screen?call(m.alive,0,a,&ok):0;
 if(!ok||(screen&&(!live||!unbox(live))))return 0;
 if(!screen||!*(unsigned char*)unbox(live)){*open=0;return 1;}
 PTR value=call(m.mapping.map_open,screen,0,&ok);
 if(!ok||!value||!unbox(value))return 0;
 *open=*(unsigned char*)unbox(value)!=0;return 1;
}
static void map_release(void){ddrop(&m.map);opened_here=map_returning=0;}
static int feature_end(void){
 fw_clear();if(!opened_here){map_release();return 1;}map_returning=1;
 PTR screen=dget(m.map);int open=0;
 if(!screen||!map_observe(screen,&open))return 0;
 if(open){int ok=1;call(m.mapping.map_close,screen,0,&ok);if(!ok)return 0;
  if(!map_observe(screen,&open)||open)return 0;
 }
 map_release();return 1;
}
static void feature_tick(PTR walker,PTR world,int input){
 (void)world;(void)input;int ok=1,open=0;PTR screen=map();
 /* Never transfer ownership to a replacement map, even if its state matches. */
 if(opened_here&&(map_returning||screen!=dget(m.map))){if(!feature_end())return;}
 m.active_tool=fw_equipped(walker);
 if(!m.active_tool){feature_end();return;}
 int blocked=boolean(m.blocked,walker,&ok);
 if(!ok||!screen||!map_observe(screen,&open)){fw_clear();return;}
 if(opened_here&&!open)map_release();
 if(m.pressed[0x7b]&&(!blocked||open)){
  if(open){
   if(opened_here){if(!feature_end())m.status="Map close pending";}
   else {call(m.mapping.map_close,screen,0,&ok);m.status=ok?"":"Map unavailable";}
  }else{
   /* Capture before Open: an exception may still have changed native state. */
   m.map=dhold(screen);if(!m.map){m.status="Map unavailable";return;}
   opened_here=1;call(m.mapping.map_begin,screen,0,&ok);
   if(!ok||!map_observe(screen,&open)||!open){m.status="Map unavailable";feature_end();}
   else m.status="";
  }
 }
 if(map_returning){fw_clear();return;}
 char key[64]="F12",text[96];moon_input_label("portable-map.toggle","!Ctrl+!Shift+!Alt+F12",key,sizeof(key));cat(cat(text,key),": Open / close map");fw_hints->publish(MOD_ID,walker,text);
}
