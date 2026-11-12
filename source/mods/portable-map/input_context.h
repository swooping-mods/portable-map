/* The native map itself sets UIBlocked/MenuBlocked. Check the same explicit
 * other-screen gates as Map Control Framework before admitting its toggle. */
static int portable_input_context(PTR walker){
 int ok=1;PTR pause=call(m.pause_menu,walker,0,&ok);
 if(!ok||!malive(pause))return 0;
 int blocked=boolean(m.pause_blocks,pause,&ok),modal=boolean(m.pause_modal,pause,&ok);
 if(!ok||blocked||modal)return 0;
 for(unsigned i=0;i<6;i++){
  void *a[]={m.screen_types[i]};PTR screen=call(m.component,walker,a,&ok);
  if(!ok)return 0;
  if(screen){
   void *live_args[]={screen};PTR live=call(m.alive,0,live_args,&ok);
   if(!ok||!live||!unbox(live))return 0;
   if(*(unsigned char*)unbox(live)&&boolean(m.screen_open[i],screen,&ok))return 0;
   if(!ok)return 0;
  }
 }
 return 1;
}
