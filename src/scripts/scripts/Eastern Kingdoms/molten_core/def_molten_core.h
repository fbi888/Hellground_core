/* 
 * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * Copyright (C) 2008-2015 Hellground <http://hellground.net/>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef SC_DEF_MOLTEN_CORE_H
#define SC_DEF_MOLTEN_CORE_H

#define DATA_LUCIFRON_EVENT                 0
#define DATA_MAGMADAR_EVENT                 1
#define DATA_GEHENNAS_EVENT                 2
#define DATA_GARR_EVENT                     3
#define DATA_SHAZZRAH_EVENT                 4
#define DATA_BARON_GEDDON_EVENT             5
#define DATA_GOLEMAGG_THE_INCINERATOR_EVENT 6
#define DATA_SULFURON_HARBRINGER_EVENT      7
#define DATA_MAJORDOMO_EXECUTUS_EVENT       8
#define DATA_RAGNAROS_EVENT                 9
#define DATA_GOLEMAGG_DEATH                 10
#define DATA_SULFURON                       11
#define DATA_FLAMEWAKERPRIEST               12
#define DATA_GOLEMAGG                       13
#define DATA_RUNES                          14
#define DATA_SUMMON_RAGNAROS                15

#endif

enum RuneFlags
{
    RUNE_ZETH_FLAG      = 1,
    RUNE_MAZJ_FLAG      = 2,
    RUNE_THERI_FLAG     = 4,
    RUNE_BLAZ_FLAG      = 8,
    RUNE_KRESS_FLAG     = 16,
    RUNE_MOHN_FLAG      = 32,
    RUNE_KORO_FLAG      = 64,
    RUNES_COMPLETE      = RUNE_ZETH_FLAG | RUNE_MAZJ_FLAG | RUNE_THERI_FLAG | RUNE_BLAZ_FLAG | RUNE_KRESS_FLAG | RUNE_MOHN_FLAG | RUNE_KORO_FLAG
};
