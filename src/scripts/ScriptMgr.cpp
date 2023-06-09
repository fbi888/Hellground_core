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

#include "precompiled.h"
#include "Database/DatabaseEnv.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "ProgressBar.h"
#include "system/ScriptLoader.h"
#include "system/system.h"

#include "../game/ScriptMgr.h"

#define _FULLVERSION "HellgroundScript"

#ifndef _HELLGROUND_SCRIPT_CONFIG
# define _HELLGROUND_SCRIPT_CONFIG  "hellgroundcore.conf"
#endif // _HELLGROUND_SCRIPT_CONFIG

int num_sc_scripts;
Script *m_scripts[MAX_SCRIPTS];

void FillSpellSummary();

// -------------------
void LoadDatabase()
{
    pSystemMgr.LoadScriptTexts();
    pSystemMgr.LoadScriptWaypoints(); //[TZERO] to implement
}

struct TSpellSummary
{
    uint8 Targets;                                          // set of enum SelectTarget
    uint8 Effects;                                          // set of enum SelectEffect
} extern *SpellSummary;

HELLGROUND_DLL_EXPORT
void FreeScriptLibrary()
{
    // Free Spell Summary
    delete [] SpellSummary;

    // Free resources before library unload
    for(uint16 i =0; i < MAX_SCRIPTS; ++i)
        delete m_scripts[i];

    num_sc_scripts = 0;
}

HELLGROUND_DLL_EXPORT
void InitScriptLibrary()
{
    //Hellground Script startup
    outstring_log(" _   _      _ _ _____                           _ ");
    outstring_log("| | | |    | | |  __ \\                         | |");
    outstring_log("| |_| | ___| | | |  \\/_ __ ___  _   _ _ __   __| |");
    outstring_log("|  _  |/ _ \\ | | | __| '__/ _ \\| | | | '_ \\ / _` |");
    outstring_log("| | | |  __/ | | |_\\ \\ | | (_) | |_| | | | | (_| |");
    outstring_log("\\_| |_/\\___|_|_|\\____/_|  \\___/ \\__,_|_| |_|\\__,_|");
    outstring_log("http://hellground.net based on http://TrinityCore.org");
    outstring_log("Hellground Script initializing %s", _FULLVERSION);

    //Load database (must be called after TScriptConfig.SetSource). In case it failed, no need to even try load.
    LoadDatabase();

    outstring_log("TSCR: Loading C++ scripts");
    BarGoLink bar(1);
    bar.step();
    outstring_log();

    for(uint16 i = 0; i < MAX_SCRIPTS; ++i)
        m_scripts[i] = NULL;

    FillSpellSummary();

    AddScripts();

    outstring_log(">> Loaded %i C++ Scripts.", num_sc_scripts);
}

//*********************************
//*** Functions used globally ***

void DoScriptText(int32 iTextEntry, WorldObject* pSource, Unit* pTarget, bool withoutPrename)
{
    if (!iTextEntry)
        return;

    if (!pSource)
    {
        error_log("TSCR: DoScriptText entry %i, invalid Source pointer.", iTextEntry);
        return;
    }

    if (iTextEntry > 0)
    {
        error_log("TSCR: DoScriptText with source entry %u (TypeId=%u, guid=%u) attempts to process text entry %i, but text entry must be negative.", pSource->GetEntry(), pSource->GetTypeId(), pSource->GetGUIDLow(), iTextEntry);
        return;
    }

    const StringTextData* pData = pSystemMgr.GetTextData(iTextEntry);

    if (!pData)
    {
        error_log("TSCR: DoScriptText with source entry %u (TypeId=%u, guid=%u) could not find text entry %i.", pSource->GetEntry(), pSource->GetTypeId(), pSource->GetGUIDLow(), iTextEntry);
        return;
    }

    debug_log("TSCR: DoScriptText: text entry=%i, Sound=%u, Type=%u, Language=%u, Emote=%u", iTextEntry, pData->uiSoundId, pData->uiType, pData->uiLanguage, pData->uiEmote);

    if (pData->uiSoundId)
    {
        if (GetSoundEntriesStore()->LookupEntry(pData->uiSoundId))
            pSource->SendPlaySound(pData->uiSoundId, false);
        else
            error_log("TSCR: DoScriptText entry %i tried to process invalid sound id %u.", iTextEntry, pData->uiSoundId);
    }

    if (pData->uiEmote)
    {
        if (pSource->GetTypeId() == TYPEID_UNIT || pSource->GetTypeId() == TYPEID_PLAYER)
            ((Unit*)pSource)->HandleEmoteCommand(pData->uiEmote);
        else
            error_log("TSCR: DoScriptText entry %i tried to process emote for invalid TypeId (%u).", iTextEntry, pSource->GetTypeId());
    }

    switch(pData->uiType)
    {
        case CHAT_TYPE_SAY:
            pSource->MonsterSay(iTextEntry, pData->uiLanguage, pTarget ? pTarget->GetGUID() : 0);
            break;
        case CHAT_TYPE_YELL:
            pSource->MonsterYell(iTextEntry, pData->uiLanguage, pTarget ? pTarget->GetGUID() : 0);
            break;
        case CHAT_TYPE_TEXT_EMOTE:
            pSource->MonsterTextEmote(iTextEntry, pTarget ? pTarget->GetGUID() : 0, false, withoutPrename);
            break;
        case CHAT_TYPE_BOSS_EMOTE:
            pSource->MonsterTextEmote(iTextEntry, pTarget ? pTarget->GetGUID() : 0, true, withoutPrename);
            break;
        case CHAT_TYPE_WHISPER:
        {
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                pSource->MonsterWhisper(iTextEntry, pTarget->GetGUID());
            else
                error_log("TSCR: DoScriptText entry %i cannot whisper without target unit (TYPEID_PLAYER).", iTextEntry);

            break;
        }
        case CHAT_TYPE_BOSS_WHISPER:
        {
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                pSource->MonsterWhisper(iTextEntry, pTarget->GetGUID(), true);
            else
                error_log("TSCR: DoScriptText entry %i cannot whisper without target unit (TYPEID_PLAYER).", iTextEntry);

            break;
        }
        case CHAT_TYPE_ZONE_YELL:
            pSource->MonsterYellToZone(iTextEntry, pData->uiLanguage, pTarget ? pTarget->GetGUID() : 0);
            break;
        case CHAT_TYPE_ZONE_BOSS_EMOTE:
            pSource->MonsterTextEmoteToZone(iTextEntry, pTarget ? pTarget->GetGUID() : 0, true, withoutPrename);
            break;
    }

    if (pTarget && pTarget->GetTypeId() == TYPEID_UNIT)
        ((Creature*)pTarget)->AI()->ReceiveScriptText(pSource, iTextEntry);
}

void DoGlobalScriptText(int32 iTextEntry, const char *npcName, Map *map)
{
    if (iTextEntry >= 0)
    {
        error_log("TSCR: DoGlobalScriptText with npc name %s attempts to process text entry %i, but text entry must be negative.", npcName, iTextEntry);
        return;
    }

    const StringTextData* pData = pSystemMgr.GetTextData(iTextEntry);

    if (!pData)
    {
        error_log("TSCR: DoGlobalScriptText with npc name %s could not find text entry %i.", npcName, iTextEntry);
        return;
    }

    bool playSound = pData->uiSoundId && GetSoundEntriesStore()->LookupEntry(pData->uiSoundId);
    uint32 textType = 0;
    switch(pData->uiType)
    {
        case CHAT_TYPE_SAY:
            textType = CHAT_MSG_MONSTER_SAY;
            break;
        case CHAT_TYPE_YELL:
        case CHAT_TYPE_ZONE_YELL:
            textType = CHAT_MSG_MONSTER_YELL;
            break;
        case CHAT_TYPE_TEXT_EMOTE:
            textType = CHAT_MSG_MONSTER_EMOTE;
            break;
        case CHAT_TYPE_BOSS_EMOTE:
            textType = CHAT_MSG_RAID_BOSS_EMOTE;
            break;
        case CHAT_TYPE_WHISPER:
            textType = CHAT_MSG_MONSTER_WHISPER;
            break;
        case CHAT_TYPE_BOSS_WHISPER:
            textType = CHAT_MSG_RAID_BOSS_WHISPER;
            break;
    }

    Map::PlayerList const &players = map->GetPlayers();
    for(Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
    {
        if(Player *player = i->getSource())
        {
            WorldPacket data(SMSG_MESSAGECHAT, 200);
            player->BuildMonsterChat(&data,textType,iTextEntry,LANG_UNIVERSAL,npcName,player->GetGUID());
            player->GetSession()->SendPacket(&data);
            if(playSound)
                (*i).getSource()->SendPlaySound(pData->uiSoundId, true);
        }
    }
}

//*********************************
//*** Functions used internally ***

void Script::RegisterSelf(bool bReportError)
{
    if (uint32 id = GetScriptId(Name.c_str()))
    {
        m_scripts[id] = this;
        ++num_sc_scripts;
    }
    else
    {
        if (bReportError)
            error_log("SD2: Script registering but ScriptName %s is not assigned in database. Script will not be used.", Name.c_str());

        delete this;
    }
}

//********************************
//*** Functions to be Exported ***

HELLGROUND_DLL_EXPORT
bool GossipHello(Player* pPlayer, Creature* pCreature)
{
    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->pGossipHello)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pGossipHello(pPlayer, pCreature);
}

HELLGROUND_DLL_EXPORT
bool GossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    debug_log("SD2: Gossip selection, sender: %u, action: %u", uiSender, uiAction);

    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->pGossipSelect)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pGossipSelect(pPlayer, pCreature, uiSender, uiAction);
}

HELLGROUND_DLL_EXPORT
bool GOGossipSelect(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction)
{
    debug_log("SD2: GO Gossip selection, sender: %u, action: %u", uiSender, uiAction);

    Script* pTempScript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!pTempScript || !pTempScript->pGossipSelectGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pGossipSelectGO(pPlayer, pGo, uiSender, uiAction);
}

HELLGROUND_DLL_EXPORT
bool GossipSelectWithCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* sCode)
{
    debug_log("SD2: Gossip selection with code, sender: %u, action: %u", uiSender, uiAction);

    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->pGossipSelectWithCode)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pGossipSelectWithCode(pPlayer, pCreature, uiSender, uiAction, sCode);
}

HELLGROUND_DLL_EXPORT
bool GOGossipSelectWithCode(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction, const char* sCode)
{
    debug_log("SD2: GO Gossip selection with code, sender: %u, action: %u", uiSender, uiAction);

    Script* pTempScript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!pTempScript || !pTempScript->pGossipSelectGOWithCode)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pGossipSelectGOWithCode(pPlayer, pGo, uiSender, uiAction, sCode);
}

HELLGROUND_DLL_EXPORT
bool QuestAccept(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->pQuestAcceptNPC)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pQuestAcceptNPC(pPlayer, pCreature, pQuest);
}

HELLGROUND_DLL_EXPORT
bool QuestRewarded(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->pQuestRewardedNPC)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pQuestRewardedNPC(pPlayer, pCreature, pQuest);
}

HELLGROUND_DLL_EXPORT
uint32 GetNPCDialogStatus(Player* pPlayer, Creature* pCreature)
{
    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->pDialogStatusNPC)
        return 100;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pDialogStatusNPC(pPlayer, pCreature);
}

HELLGROUND_DLL_EXPORT
uint32 GetGODialogStatus(Player* pPlayer, GameObject* pGo)
{
    Script* pTempScript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!pTempScript || !pTempScript->pDialogStatusGO)
        return 100;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pDialogStatusGO(pPlayer, pGo);
}

HELLGROUND_DLL_EXPORT
bool ItemQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    Script* pTempScript = m_scripts[pItem->GetProto()->ScriptId];

    if (!pTempScript || !pTempScript->pQuestAcceptItem)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pQuestAcceptItem(pPlayer, pItem, pQuest);
}

HELLGROUND_DLL_EXPORT
bool GOUse(Player* pPlayer, GameObject* pGo)
{
    Script* pTempScript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!pTempScript || !pTempScript->pGOUse)
        return false;

    return pTempScript->pGOUse(pPlayer, pGo);
}

HELLGROUND_DLL_EXPORT
bool GOQuestAccept(Player* pPlayer, GameObject* pGo, const Quest* pQuest)
{
    Script* pTempScript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!pTempScript || !pTempScript->pQuestAcceptGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pQuestAcceptGO(pPlayer, pGo, pQuest);
}

HELLGROUND_DLL_EXPORT
bool GOQuestRewarded(Player* pPlayer, GameObject* pGo, Quest const* pQuest)
{
    Script* pTempScript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!pTempScript || !pTempScript->pQuestRewardedGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return pTempScript->pQuestRewardedGO(pPlayer, pGo, pQuest);
}

HELLGROUND_DLL_EXPORT
bool AreaTrigger(Player* pPlayer, AreaTriggerEntry const* atEntry)
{
    Script* pTempScript = m_scripts[GetAreaTriggerScriptId(atEntry->id)];

    if (!pTempScript || !pTempScript->pAreaTrigger)
        return false;

    return pTempScript->pAreaTrigger(pPlayer, atEntry);
}

HELLGROUND_DLL_EXPORT
bool CompletedCinematic(Player* pPlayer, CinematicSequencesEntry const* cinematic)
{
    Script* pTempScript = m_scripts[GetCompletedCinematicScriptId(cinematic->Id)];

    if (!pTempScript || !pTempScript->pCompletedCinematic)
        return false;

    return pTempScript->pCompletedCinematic(pPlayer, cinematic);
}

HELLGROUND_DLL_EXPORT
bool ProcessEvent(uint32 uiEventId, Object* pSource, Object* pTarget, bool bIsStart)
{
    Script* pTempScript = m_scripts[GetEventIdScriptId(uiEventId)];

    if (!pTempScript || !pTempScript->pProcessEventId)
        return false;

    // bIsStart may be false, when event is from taxi node events (arrival=false, departure=true)
    return pTempScript->pProcessEventId(uiEventId, pSource, pTarget, bIsStart);
}

HELLGROUND_DLL_EXPORT
CreatureAI* GetCreatureAI(Creature* pCreature)
{
    Script* pTempScript = m_scripts[pCreature->GetScriptId()];

    if (!pTempScript || !pTempScript->GetAI)
        return NULL;

    CreatureAI* ai = pTempScript->GetAI(pCreature);
    ai->m_AIName = pCreature->GetScriptName();
    return ai;
}

HELLGROUND_DLL_EXPORT
bool ItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    Script* pTempScript = m_scripts[pItem->GetProto()->ScriptId];

    if (!pTempScript || !pTempScript->pItemUse)
        return false;

    return pTempScript->pItemUse(pPlayer, pItem, targets);
}

HELLGROUND_DLL_EXPORT
bool AuraDummy(Aura const* pAura, bool bApply)
{
    Script* pTempScript = m_scripts[((Creature*)pAura->GetTarget())->GetScriptId()];

    if (!pTempScript || !pTempScript->pEffectAuraDummy)
        return false;

    return pTempScript->pEffectAuraDummy(pAura, bApply);
}

HELLGROUND_DLL_EXPORT
bool ReceiveEmote( Player *player, Creature *_Creature, uint32 emote )
{
    Script *tmpscript = m_scripts[_Creature->GetScriptId()];
    if (!tmpscript || !tmpscript->pReceiveEmote) return false;

    return tmpscript->pReceiveEmote(player, _Creature, emote);
}

HELLGROUND_DLL_EXPORT
InstanceData* CreateInstanceData(Map* pMap)
{
    if (!pMap->IsDungeon())
        return NULL;
    Script* pTempScript = m_scripts[((InstanceMap*)pMap)->GetScriptId()];

    if (!pTempScript || !pTempScript->GetInstanceData)
        return NULL;

    return pTempScript->GetInstanceData(pMap);
}

HELLGROUND_DLL_EXPORT
bool SpellSetTargetMap(Unit* pCaster, std::list<Unit*> &unitList, SpellCastTargets const& targets, SpellEntry const *pSpell, uint32 effectIndex)
{
    Script* pTempScript = m_scripts[GetSpellIdScriptId(pSpell->Id)];

    if (!pTempScript || !pTempScript->pSpellTargetMap)
        return false;

    return pTempScript->pSpellTargetMap(pCaster, unitList, targets, pSpell, effectIndex);
}

HELLGROUND_DLL_EXPORT
bool SpellHandleEffect(Unit *pCaster, Unit* pUnit, Item* pItem, GameObject* pGameObject, SpellEntry const *pSpell, uint32 effectIndex)
{
    Script* pTempScript = m_scripts[GetSpellIdScriptId(pSpell->Id)];

    if (!pTempScript || !pTempScript->pSpellHandleEffect)
        return false;

    return pTempScript->pSpellHandleEffect(pCaster, pUnit, pItem, pGameObject, pSpell, effectIndex);
}
