#include <proto/exec.h>
#include "amiga/SDI/SDI_hook.h"

struct AHIAudioCtrl;
struct AHISoundMessage;

extern void gs_ahi_sound_cb(struct AHIAudioCtrl *actrl, struct AHISoundMessage*);

HOOKPROTO(gs_ahi_sound_fn, void, struct AHIAudioCtrl *actrl, struct AHISoundMessage* msg) {
	gs_ahi_sound_cb(actrl, msg);
}

MakeHook(gs_ahi_sound_fn_hook, gs_ahi_sound_fn);
