/* dpboxt: Terminal for DPBox
   Copyright (C) 1995-96 by Mark Wahl
   For license details see documentation
   Main procedure (main.c)
   created: Mark Wahl DL4YBG 95/01/14
   updated: Mark Wahl DL4YBG 96/01/20
*/
#define DPBOXT_DATE "96/01/20"
#define DPBOXT_VERSION "V0.2b"
#include "tnt.h"

int act_channel;
int act_mode;
int act_state;
int is_root;
char tnt_dir[80];

char signon[] =
"DPBOXT "DPBOXT_VERSION" DPBox Terminal\015"
"LINUX-Version, Created: "DPBOXT_DATE"\015"
"Copyright (C) 1995-96 by Mark Wahl, DL4YBG\015"
"For license details see documentation.\015"
"To start DPBox give command ':box <ENTER>'.\015"
"To get help: <ALT> H or <Esc> H\015\015";

int 
main(argc,argv)
int argc;
char *argv[];
{
  char ch;
  fd_set fdmask;
  struct timeval timevalue;
  int served;
  int max_fd;
  int count;
  int unlock;

  umask(0); /* don't filter file-permissions */

  is_root = (geteuid() == 0);
  
  if (read_init_file(argc,argv,&unlock))
    exit(1);
  if (term_init())
    exit(1);
  
  signal(SIGHUP, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);

  init_file();
  init_screen();  
  init_keyboard();
  init_help();
  init_conv();
  init_iface();
  init_mb();
  init_blist();

  mb_display_buf(signon,strlen(signon));
    
  act_state = S_NORMAL;
  
  while (act_state) {
    iface_trying();
    FD_ZERO(&fdmask);
    FD_SET(0,&fdmask);
    max_fd = 1;
    iface_fdset(&max_fd,&fdmask);
    timevalue.tv_usec = 0;
    timevalue.tv_sec = RESY_TIME;
    count = select(max_fd,&fdmask,
                  (struct fd_set *) 0,(struct fd_set *) 0,&timevalue);
    if (count == -1) {
      continue;
    }
    served = 0;
    if (FD_ISSET(0,&fdmask)) {
      if (read(0,&ch,1) == 1) {
        keyboard_server(&act_state,&ch);
      }
      served = 1;
    }
    if (!iface_receive(&fdmask)) {
      served = 1;
    }
  }

  exit_blist();
  exit_mb();
  exit_iface();
  exit_file();
  exit_help();
  exit_keyboard();
  exit_screen();

  exit(0);
}
