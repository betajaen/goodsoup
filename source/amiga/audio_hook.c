#include <proto/exec.h>
#include "amiga/sdi/sdi_hook.h"

struct AHIAudioCtrl;

extern void gs_ahi_player_cb();
extern void gs_ahi_sound_cb(struct AHISoundMessage*);

HOOKPROTO(gs_ahi_player_fn, void, struct AHIAudioCtrl *actrl, APTR ignored) {
gs_ahi_player_cb();
}

MakeHook(gs_ahi_player_fn_hook, gs_ahi_player_fn);

HOOKPROTO(gs_ahi_sound_fn, void, struct AHIAudioCtrl *actrl, struct AHISoundMessage* msg) {
	gs_ahi_sound_cb(msg);
}

MakeHook(gs_ahi_sound_fn_hook, gs_ahi_sound_fn);