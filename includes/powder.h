/**
 * Powder Toy - particle simulation (header)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef POWDER_H
#define POWDER_H

#include "air.h"
#include "defines.h"
#include "misc.h"

#define CM_COUNT 11
#define CM_CRACK 10
#define CM_LIFE 9
#define CM_GRAD 8
#define CM_NOTHING 7
#define CM_FANCY 6
#define CM_HEAT 5
#define CM_BLOB 4
#define CM_FIRE 3
#define CM_PERS 2
#define CM_PRESS 1
#define CM_VEL 0

#define BRUSH_REPLACEMODE 0x1
#define BRUSH_SPECIFIC_DELETE 0x2

#include "simulation/ElementNumbers.h"

#define R_TEMP 22
#define MAX_TEMP 9999
#define MIN_TEMP 0
#define O_MAX_TEMP 3500
#define O_MIN_TEMP -273

#define TYPE_PART			0x0000001 //1 Powders
#define TYPE_LIQUID			0x0000002 //2 Liquids
#define TYPE_SOLID			0x0000004 //4 Solids
#define TYPE_GAS			0x0000008 //8 Gases (Includes plasma)
#define TYPE_ENERGY			0x0000010 //16 Energy (Thunder, Light, Neutrons etc.)
#define STATE_FLAGS			0x000001F
#define PROP_CONDUCTS		0x0000020 //32 Conducts electricity
#define PROP_BLACK			0x0000040 //64 Absorbs Photons (not currently implemented or used, a photwl attribute might be better)
#define PROP_NEUTPENETRATE	0x0000080 //128 Penetrated by neutrons
#define PROP_NEUTABSORB		0x0000100 //256 Absorbs neutrons, reflect is default
#define PROP_NEUTPASS		0x0000200 //512 Neutrons pass through, such as with glass
#define PROP_DEADLY			0x0000400 //1024 Is deadly for stickman
#define PROP_HOT_GLOW		0x0000800 //2048 Hot Metal Glow
#define PROP_LIFE			0x0001000 //4096 Is a GoL type
#define PROP_RADIOACTIVE	0x0002000 //8192 Radioactive
#define PROP_LIFE_DEC		0x0004000 //2^14 Life decreases by one every frame if > zero
#define PROP_LIFE_KILL		0x0008000 //2^15 Kill when life value is <= zero
#define PROP_LIFE_KILL_DEC	0x0010000 //2^16 Kill when life value is decremented to <= zero
#define PROP_INDESTRUCTIBLE	0x0020000 //2^17 Makes elements invincible, even to bomb/dest
#define PROP_CLONE			0x0040000 //2^18 Makes elements clone things that touch it
#define PROP_BREAKABLECLONE	0x0080000 //2^19 Makes breakable elements clone things that touch it
#define PROP_POWERED		0x0100000 //2^20 Makes an element turn on/off with PSCN/NSCN
#define PROP_SPARKSETTLE	0x0200000 //2^21 Allow Sparks/Embers to settle
#define PROP_NOAMBHEAT      0x0400000 //2^23 Don't transfer or receive heat from ambient heat.
#define PROP_DRAWONCTYPE	0x0800000 //2^24 Set its ctype to another element if the element is drawn upon it (like what CLNE does)
#define PROP_NOCTYPEDRAW	0x1000000 //2^25 When this element is drawn upon with, do not set ctype (like BCLN for CLNE)

#define FLAG_STAGNANT	0x1
#define FLAG_SKIPMOVE	0x2  // Skip movement for one frame
#define FLAG_WATEREQUAL 0x4  // If a liquid was already checked during equalization
#define FLAG_PHOTDECO	0x8  // compatibility with old saves (decorated photons), only applies to PHOT.
#define FLAG_EXPLODE	0x10 // EXPL explosion
#define FLAG_DISAPPEAR	0x20 // Will disappear on next frame no matter what

class Simulation;
#define UPDATE_FUNC_ARGS Simulation *sim, int i, int x, int y, int surround_space, int nt
#define UPDATE_FUNC_SUBCALL_ARGS sim, i, x, y, surround_space, nt
#define GRAPHICS_FUNC_ARGS Simulation *sim, particle *cpart, int nx, int ny, int *pixel_mode, int* cola, int *colr, int *colg, int *colb, int *firea, int *firer, int *fireg, int *fireb
#define GRAPHICS_FUNC_SUBCALL_ARGS sim, cpart, nx, ny, pixel_mode, cola, colr, colg, colb, firea, firer, fireg, fireb

#include "simulation/Particle.h"

void TRON_init_graphics();

void PPIP_flood_trigger(Simulation* sim, int x, int y, int sparkedBy);

struct part_type
{
	char *name;
	float gravity;
	int falldown;
	int flammable;
	int explosive;
	int meltable;
	int hardness;
	int enabled;
	int weight;
	float heat;
	unsigned char hconduct;
	char *descs;
	unsigned int properties;
	int (*graphics_func) (GRAPHICS_FUNC_ARGS);
};
typedef struct part_type part_type;

struct part_transition
{
	float plv; // transition occurs if pv is lower than this
	int plt;
	float phv; // transition occurs if pv is higher than this
	int pht;
	float tlv; // transition occurs if t is lower than this
	int tlt;
	float thv; // transition occurs if t is higher than this
	int tht;
};
typedef struct part_transition part_transition;

// TODO: falldown, properties, state - should at least one of these be removed?
extern part_type ptypes[PT_NUM];
extern unsigned int platent[PT_NUM];

extern part_transition ptransitions[PT_NUM];

#define CHANNELS ((int)(MAX_TEMP-73)/100+2)
extern const particle emptyparticle;

extern int airMode;

extern particle *parts;
extern particle *cb_parts;

extern unsigned char bmap[YRES/CELL][XRES/CELL];
extern unsigned char emap[YRES/CELL][XRES/CELL];

extern unsigned char cb_bmap[YRES/CELL][XRES/CELL];
extern unsigned char cb_emap[YRES/CELL][XRES/CELL];

extern unsigned pmap[YRES][XRES];
extern unsigned cb_pmap[YRES][XRES];
extern int pmap_count[YRES][XRES];

extern unsigned photons[YRES][XRES];

int get_wavelength_bin(int *wm);

void kill_part(int i);

int interactWavelengths(particle* cpart, int origWl);
int getWavelengths(particle* cpart);

void part_change_type(int i, int x, int y, int t);

void get_gravity_field(int x, int y, float particleGrav, float newtonGrav, float *pGravX, float *pGravY);

int get_brush_flags();

int is_wire(int x, int y);

int is_wire_off(int x, int y);

void set_emap(int x, int y);

int parts_avg(int ci, int ni, int t);

int nearest_part(int ci, int t, int max_d);

void decrease_life(int i);

bool transfer_heat(int i, int t, int surround[8]);

bool particle_transitions(int i, int t);

void rotate_area(int area_x, int area_y, int area_w, int area_h, int invert);

void clear_area(int area_x, int area_y, int area_w, int area_h);

int INST_flood_spark(Simulation *sim, int x, int y);

int flood_water(int x, int y, int i, int originaly, int check);

void orbitalparts_get(int block1, int block2, int resblock1[], int resblock2[]);
void orbitalparts_set(int *block1, int *block2, int resblock1[], int resblock2[]);

void draw_bframe();
void erase_bframe();

#endif
