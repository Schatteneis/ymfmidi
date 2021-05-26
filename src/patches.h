#ifndef __PATCHES_H
#define __PATCHES_H

#include <map>
#include <string>

// one carrier/modulator pair in a patch, out of a possible two
struct PatchVoice
{
	uint8_t op_mode[2] = {0};  // regs 0x20+
	uint8_t op_ksr[2]   = {0}; // regs 0x40+ (upper bits)
	uint8_t op_level[2] = {0}; // regs 0x40+ (lower bits)
	uint8_t op_ad[2] = {0};    // regs 0x60+
	uint8_t op_sr[2] = {0};    // regs 0x80+
	uint8_t conn = 0;          // regs 0xC0+
	uint8_t op_wave[2] = {0};  // regs 0xE0+
	
	int8_t tune = 0; // MIDI note offset
	double finetune = 0.0;
};

typedef std::map<uint16_t, struct OPLPatch> OPLPatchSet;

struct OPLPatch
{
	std::string name;
	bool fourOp = false; // true 4op
	bool dualTwoOp = false; // only valid if fourOp = false
	uint8_t fixedNote = 0;
	int8_t velocity = 0; // MIDI velocity offset
	
	PatchVoice voice[2];
	
	// default names
	static const char* names[256];
	
	static bool load(const char *path, OPLPatchSet& patches, int offset = 0);
	static bool load(FILE *file, OPLPatchSet& patches, int offset = 0);

private:
	// individual format loaders
	static bool loadWOPL(FILE *file, OPLPatchSet& patches, int offset = 0);
	static bool loadOP2(FILE *file, OPLPatchSet& patches, int offset = 0);
	static bool loadAIL(FILE *file, OPLPatchSet& patches, int offset = 0);
	static bool loadTMB(FILE *file, OPLPatchSet& patches, int offset = 0);
};

#endif // __PATCHES_H
