/**
 * ScriptDev2 is an extension for mangos providing enhanced features for
 * area triggers, creatures, game objects, instances, items, and spells beyond
 * the default database scripting in mangos.
 *
 * Copyright (C) 2006-2013  ScriptDev2 <http://www.scriptdev2.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

/**
 * ScriptData
 * SDName:      Spell_Scripts
 * SD%Complete: 100
 * SDComment:   Spell scripts for dummy effects (if script need access/interaction with parts of other AI or instance, add it in related source files).
 * SDCategory:  Spell
 * EndScriptData
 */

/**
 * ContentData
 * Spell 8913:  Sacred Cleansing
 * Spell 19512: Apply Salve
 * spell 21014
 * Spell 21050: Melodious Rapture
 * spell 29528
 * spell 29866
 * spell 34665
 * spell 37136
 * spell 39246
 * spell 44935
 * spell 45109
 * spell 45111
 * EndContentData
 */

#include "precompiled.h"

/**
 * When you make a spell effect:
 * - always check spell id and effect index
 * - always return true when the spell is handled by script
 */

enum
{
    // quest 9452
    SPELL_CAST_FISHING_NET      = 29866,
    GO_RED_SNAPPER              = 181616,
    NPC_ANGRY_MURLOC            = 17102,
    ITEM_RED_SNAPPER            = 23614,
    // SPELL_SUMMON_TEST           = 49214                  // ! Just wrong spell name? It summon correct creature (17102)but does not appear to be used.
};

struct spell_cast_fishing_net : public SpellScript
{
    spell_cast_fishing_net() : SpellScript("spell_cast_fishing_net") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_CAST_FISHING_NET)
        {
            GameObject* pGOTarget = pTarget->ToGameObject();
            if (uiEffIndex == EFFECT_INDEX_0)
            {
                if (pGOTarget->GetRespawnTime() != 0 || pGOTarget->GetEntry() != GO_RED_SNAPPER || pCaster->GetTypeId() != TYPEID_PLAYER)
                {
                    return true;
                }

                if (urand(0, 2))
                {
                    if (Creature* pMurloc = pCaster->SummonCreature(NPC_ANGRY_MURLOC, pCaster->GetPositionX(), pCaster->GetPositionY() + 20.0f, pCaster->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_OOC_DESPAWN, 10000))
                    {
                        pMurloc->AI()->AttackStart(pCaster);
                    }
                }
                else
                {
                    if (Item* pItem = ((Player*)pCaster)->StoreNewItemInInventorySlot(ITEM_RED_SNAPPER, 1))
                    {
                        ((Player*)pCaster)->SendNewItem(pItem, 1, true, false);
                    }
                }

                pGOTarget->SetLootState(GO_JUST_DEACTIVATED);
                return true;
            }
            return true;
        }

        return false;
    }
};

enum
{
    // quest 9629
    SPELL_TAG_MURLOC                    = 30877,
    SPELL_TAG_MURLOC_PROC               = 30875,
    NPC_BLACKSILT_MURLOC                = 17326,
    NPC_TAGGED_MURLOC                   = 17654,

    // quest 9447
    SPELL_HEALING_SALVE                 = 29314,
    SPELL_HEALING_SALVE_DUMMY           = 29319,
    NPC_MAGHAR_GRUNT                    = 16846,

    // quest 10190
    SPELL_RECHARGING_BATTERY            = 34219,
    NPC_DRAINED_PHASE_HUNTER            = 19595,

    // target hulking helboar
    SPELL_ADMINISTER_ANTIDOTE           = 34665,
    NPC_HELBOAR                         = 16880,
    NPC_DREADTUSK                       = 16992,

    // quest 6124/6129
    SPELL_APPLY_SALVE                   = 19512,
    SPELL_SICKLY_AURA                   = 19502,

    NPC_SICKLY_DEER                     = 12298,
    NPC_SICKLY_GAZELLE                  = 12296,

    NPC_CURED_DEER                      = 12299,
    NPC_CURED_GAZELLE                   = 12297,

    // target morbent fel
    SPELL_SACRED_CLEANSING              = 8913,
    NPC_MORBENT                         = 1200,
    NPC_WEAKENED_MORBENT                = 24782,

    // quest 11515
    SPELL_FEL_SIPHON_DUMMY              = 44936,
    NPC_FELBLOOD_INITIATE               = 24918,
    NPC_EMACIATED_FELBLOOD              = 24955,

    // target nestlewood owlkin
    SPELL_INOCULATE_OWLKIN              = 29528,
    NPC_OWLKIN                          = 16518,
    NPC_OWLKIN_INOC                     = 16534,

    // Quest "Disrupt the Greengill Coast" (11541)
    SPELL_ORB_OF_MURLOC_CONTROL         = 45109,
    SPELL_GREENGILL_SLAVE_FREED         = 45110,
    SPELL_ENRAGE                        = 45111,
    NPC_FREED_GREENGILL_SLAVE           = 25085,
    NPC_DARKSPINE_MYRMIDON              = 25060,
    NPC_DARKSPINE_SIREN                 = 25073,

    // quest "The Big Bone Worm" 10930
    SPELL_FUMPING                       = 39246,
    SPELL_SUMMON_HAISHULUD              = 39248,
    NPC_SAND_GNOME                      = 22483,
    NPC_MATURE_BONE_SIFTER              = 22482,

    // quest 9849, item 24501
    SPELL_THROW_GORDAWG_BOULDER         = 32001,
    NPC_MINION_OF_GUROK                 = 18181,

    // npcs that are only interactable while dead
    SPELL_SHROUD_OF_DEATH               = 10848,
    SPELL_SPIRIT_PARTICLES              = 17327,
    NPC_FRANCLORN_FORGEWRIGHT           = 8888,
    NPC_GAERIYAN                        = 9299,

    // quest 11521
    SPELL_EXPOSE_RAZORTHORN_ROOT        = 44935,
    SPELL_SUMMON_RAZORTHORN_ROOT        = 44941,
    NPC_RAZORTHORN_RAVAGER              = 24922,
    GO_RAZORTHORN_DIRT_MOUND            = 187073,

    //  for quest 10584
    SPELL_PROTOVOLTAIC_MAGNETO_COLLECTOR = 37136,
    NPC_ENCASED_ELECTROMENTAL           = 21731,

    // quest 6661
    SPELL_MELODIOUS_RAPTURE             = 21050,
    SPELL_MELODIOUS_RAPTURE_VISUAL      = 21051,
    NPC_DEEPRUN_RAT                     = 13016,
    NPC_ENTHRALLED_DEEPRUN_RAT          = 13017,
};

struct aura_spirit_particles : public AuraScript
{
    aura_spirit_particles() : AuraScript("aura_spirit_particles") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        switch (pAura->GetId())
        {
        case SPELL_SHROUD_OF_DEATH:
        case SPELL_SPIRIT_PARTICLES:
        {
            Creature* pCreature = (Creature*)pAura->GetTarget();

            if (!pCreature || (pCreature->GetEntry() != NPC_FRANCLORN_FORGEWRIGHT && pCreature->GetEntry() != NPC_GAERIYAN))
            {
                return false;
            }

            if (bApply)
            {
                pCreature->m_AuraFlags |= UNIT_AURAFLAG_ALIVE_INVISIBLE;
            }
            else
            {
                pCreature->m_AuraFlags &= ~UNIT_AURAFLAG_ALIVE_INVISIBLE;
            }

            return false;   //TODO why? true
        }
        }

        return false;
    }
};

struct aura_healing_salve : public AuraScript
{
    aura_healing_salve() : AuraScript("aura_healing_salve") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        if (pAura->GetId() != SPELL_HEALING_SALVE || pAura->GetEffIndex() != EFFECT_INDEX_0)
        {
            return true;
        }

        if (bApply)
        {
            if (Unit* pCaster = pAura->GetCaster())
            {
                pCaster->CastSpell(pAura->GetTarget(), SPELL_HEALING_SALVE_DUMMY, true);
            }
        }
        return true;
    }
};

struct aura_healing_salve_dummy : public AuraScript
{
    aura_healing_salve_dummy() : AuraScript("aura_healing_salve_dummy") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        if (pAura->GetId() != SPELL_HEALING_SALVE_DUMMY || pAura->GetEffIndex() != EFFECT_INDEX_0)
        {
            return true;
        }

        if (!bApply)
        {
            Creature* pCreature = (Creature*)pAura->GetTarget();

            pCreature->UpdateEntry(NPC_MAGHAR_GRUNT);

            if (pCreature->getStandState() == UNIT_STAND_STATE_KNEEL)
            {
                pCreature->SetStandState(UNIT_STAND_STATE_STAND);
            }

            pCreature->ForcedDespawn(60 * IN_MILLISECONDS);
        }
        return true;
    }
};

struct aura_recharging_battery : public AuraScript
{
    aura_recharging_battery() : AuraScript("aura_recharging_battery") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        if (pAura->GetId() != SPELL_RECHARGING_BATTERY || pAura->GetEffIndex() != EFFECT_INDEX_0)
            return true;

        if (!bApply)
        {
            if (pAura->GetTarget()->HasAuraState(AURA_STATE_HEALTHLESS_20_PERCENT))
            {
                ((Creature*)pAura->GetTarget())->UpdateEntry(NPC_DRAINED_PHASE_HUNTER);
            }
        }

        return true;
    }
};

struct aura_tag_murloc : public AuraScript
{
    aura_tag_murloc() : AuraScript("aura_tag_murloc") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        if (pAura->GetId() != SPELL_TAG_MURLOC || pAura->GetEffIndex() != EFFECT_INDEX_0)
        {
            return true;
        }

        Creature* pCreature = (Creature*)pAura->GetTarget();

        if (bApply)
        {
            if (pCreature->GetEntry() == NPC_BLACKSILT_MURLOC)
            {
                if (Unit* pCaster = pAura->GetCaster())
                {
                    pCaster->CastSpell(pCreature, SPELL_TAG_MURLOC_PROC, true);
                }
            }
        }
        else
        {
            if (pCreature->GetEntry() == NPC_TAGGED_MURLOC)
            {
                pCreature->ForcedDespawn();
            }
        }

        return true;
    }
};

struct aura_enrage_45111 : public AuraScript
{
    aura_enrage_45111() : AuraScript("aura_enrage_45111") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        if (pAura->GetId() != SPELL_ENRAGE || !bApply || pAura->GetTarget()->GetTypeId() != TYPEID_UNIT)
        {
            return false;
        }

        Creature* pTarget = (Creature*)pAura->GetTarget();

        if (Creature* pCreature = GetClosestCreatureWithEntry(pTarget, NPC_DARKSPINE_MYRMIDON, 25.0f))
        {
            pTarget->AI()->AttackStart(pCreature);
            return true;
        }

        if (Creature* pCreature = GetClosestCreatureWithEntry(pTarget, NPC_DARKSPINE_SIREN, 25.0f))
        {
            pTarget->AI()->AttackStart(pCreature);
            return true;
        }

        return false;
    }
};

struct aura_photovoltaic_magneto_collector : public AuraScript
{
    aura_photovoltaic_magneto_collector() : AuraScript("aura_photovoltaic_magneto_collector") {}

    bool OnDummyApply(const Aura* pAura, bool bApply) override
    {
        if (pAura->GetId() != SPELL_PROTOVOLTAIC_MAGNETO_COLLECTOR || pAura->GetEffIndex() != EFFECT_INDEX_0)
        {
            return true;
        }

        Unit* pTarget = pAura->GetTarget();
        if (bApply && pTarget->GetTypeId() == TYPEID_UNIT)
        {
            ((Creature*)pTarget)->UpdateEntry(NPC_ENCASED_ELECTROMENTAL);
        }
        return true;
    }
};

struct spell_apply_salve : public SpellScript
{
    spell_apply_salve() : SpellScript("spell_apply_salve") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_APPLY_SALVE && uiEffIndex == EFFECT_INDEX_0)
        {
            if (pCaster->GetTypeId() != TYPEID_PLAYER)
            {
                return true;
            }

            Creature *pCreatureTarget = pTarget->ToCreature();
            if (pCreatureTarget->GetEntry() != NPC_SICKLY_DEER && pCreatureTarget->GetEntry() != NPC_SICKLY_GAZELLE)
            {
                return true;
            }

            // Update entry, remove aura, set the kill credit and despawn
            uint32 uiUpdateEntry = pCreatureTarget->GetEntry() == NPC_SICKLY_DEER ? NPC_CURED_DEER : NPC_CURED_GAZELLE;
            pCreatureTarget->RemoveAurasDueToSpell(SPELL_SICKLY_AURA);
            pCreatureTarget->UpdateEntry(uiUpdateEntry);
            ((Player*)pCaster)->KilledMonsterCredit(uiUpdateEntry);
            pCreatureTarget->ForcedDespawn(20000);
        }
        return true;
    }
};

struct spell_sacred_cleansing : public SpellScript
{
    spell_sacred_cleansing() : SpellScript("spell_sacred_cleansing") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_SACRED_CLEANSING && uiEffIndex == EFFECT_INDEX_1)
        {
            if (pTarget->ToCreature() && pTarget->GetEntry() != NPC_MORBENT)
            {
                return true;
            }
            pTarget->ToCreature()->UpdateEntry(NPC_WEAKENED_MORBENT);
        }
        return true;
    }
};

struct spell_melodious_rapture : public SpellScript
{
    spell_melodious_rapture() : SpellScript("spell_melodious_rapture") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_MELODIOUS_RAPTURE && uiEffIndex == EFFECT_INDEX_0)
        {
            Creature *pCreatureTarget = pTarget->ToCreature();
            if (pCaster->GetTypeId() != TYPEID_PLAYER && pCreatureTarget->GetEntry() != NPC_DEEPRUN_RAT)
            {
                return true;
            }

            pCreatureTarget->UpdateEntry(NPC_ENTHRALLED_DEEPRUN_RAT);
            pCreatureTarget->CastSpell(pCreatureTarget, SPELL_MELODIOUS_RAPTURE_VISUAL, false);
            pCreatureTarget->GetMotionMaster()->MoveFollow(pCaster, frand(0.5f, 3.0f), frand(M_PI_F * 0.8f, M_PI_F * 1.2f));

            ((Player*)pCaster)->KilledMonsterCredit(NPC_ENTHRALLED_DEEPRUN_RAT);
        }
        return true;
    }
};

struct spell_administer_antidote : public SpellScript
{
    spell_administer_antidote() : SpellScript("spell_administer_antidote") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_ADMINISTER_ANTIDOTE && uiEffIndex == EFFECT_INDEX_0)
            {
                if (pTarget->GetEntry() != NPC_HELBOAR)
                { return true; }

                // possible needs check for quest state, to not have any effect when quest really complete
                //TODO implement it as a DB condition for CheckCast()

                pTarget->ToCreature()->UpdateEntry(NPC_DREADTUSK);
                return true;
            }
            return true;
    }
};

struct spell_inoculate_owlkin : public SpellScript
{
    spell_inoculate_owlkin() : SpellScript("spell_inoculate_owlkin") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_INOCULATE_OWLKIN && uiEffIndex == EFFECT_INDEX_0)
        {
            if (pTarget->GetEntry() != NPC_OWLKIN)
            { return true; }

            pTarget->ToCreature()->UpdateEntry(NPC_OWLKIN_INOC);
            ((Player*)pCaster)->KilledMonsterCredit(NPC_OWLKIN_INOC);

            // set despawn timer, since we want to remove creature after a short time
            pTarget->ToCreature()->ForcedDespawn(15000);

            return true;
        }
        return true;
    }
};

struct spell_fel_siphon_dummy : public SpellScript
{
    spell_fel_siphon_dummy() : SpellScript("spell_fel_siphon_dummy") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_FEL_SIPHON_DUMMY && uiEffIndex == EFFECT_INDEX_0)
        {
            if (pTarget->GetEntry() != NPC_FELBLOOD_INITIATE)
            { return true; }

            pTarget->ToCreature()->UpdateEntry(NPC_EMACIATED_FELBLOOD);
            return true;
        }
        return true;

    }
};

struct spell_tag_murloc_proc : public SpellScript
{
    spell_tag_murloc_proc() : SpellScript("spell_tag_murloc_proc") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
            if (uiSpellId == SPELL_TAG_MURLOC_PROC && uiEffIndex == EFFECT_INDEX_0)
            {
                if (pTarget->GetEntry() == NPC_BLACKSILT_MURLOC)
                { pTarget->ToCreature()->UpdateEntry(NPC_TAGGED_MURLOC); }
            }
            return true;
    }
};

struct spell_orb_of_murloc_control : public SpellScript
{
    spell_orb_of_murloc_control() : SpellScript("spell_orb_of_murloc_control") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override //SPELL_ORB_OF_MURLOC_CONTROL
    {
        Creature* pCreatureTarget = pTarget->ToCreature();
        pCreatureTarget->CastSpell(pCaster, SPELL_GREENGILL_SLAVE_FREED, true);

        // Freed Greengill Slave
        pCreatureTarget->UpdateEntry(NPC_FREED_GREENGILL_SLAVE);

        pCreatureTarget->CastSpell(pCreatureTarget, SPELL_ENRAGE, true);

        return true;
    }
};

struct spell_fumping : public SpellScript
{
    spell_fumping() : SpellScript("spell_fumping") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        Creature *pCreatureTarget = pTarget->ToCreature();
        if (uiSpellId == SPELL_FUMPING && uiEffIndex == EFFECT_INDEX_2)
        {
            switch (urand(0, 2))
            {
            case 0:
                pCaster->CastSpell(pCreatureTarget, SPELL_SUMMON_HAISHULUD, true);
                break;
            case 1:
                for (int i = 0; i < 2; ++i)
                {
                    if (Creature* pSandGnome = pCaster->SummonCreature(NPC_SAND_GNOME, pCreatureTarget->GetPositionX(), pCreatureTarget->GetPositionY(), pCreatureTarget->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_OOC_DESPAWN, 30000))
                    {
                        pSandGnome->AI()->AttackStart(pCaster);
                    }
                }
                break;
            case 2:
                for (int i = 0; i < 2; ++i)
                {
                    if (Creature* pMatureBoneSifter = pCaster->SummonCreature(NPC_MATURE_BONE_SIFTER, pCreatureTarget->GetPositionX(), pCreatureTarget->GetPositionY(), pCreatureTarget->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_OOC_DESPAWN, 30000))
                    {
                        pMatureBoneSifter->AI()->AttackStart(pCaster);
                    }
                }
                break;
            }
            pCreatureTarget->ForcedDespawn();
        }
        return true;
    }
};

struct spell_throw_gordawg_boulder : public SpellScript
{
    spell_throw_gordawg_boulder() : SpellScript("spell_throw_gordawg_boulder") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        Creature *pCreatureTarget = pTarget->ToCreature();
        if (uiSpellId == SPELL_THROW_GORDAWG_BOULDER && uiEffIndex == EFFECT_INDEX_0)
        {
            for (int i = 0; i < 3; ++i)
            {
                if (irand(i, 2))                        // 2-3 summons
                {
                    pCreatureTarget->SummonCreature(NPC_MINION_OF_GUROK, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 5000);
                }
            }

            if (pCreatureTarget->getVictim())
            {
                pCaster->DealDamage(pCreatureTarget, pCreatureTarget->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                return true;
            }

            // If not in combat, no xp or loot
            pCreatureTarget->SetDeathState(JUST_DIED);
            pCreatureTarget->SetHealth(0);
            return true;
        }
        return true;
    }
};

struct spell_expose_rathorthorn_root : public SpellScript
{
    spell_expose_rathorthorn_root() : SpellScript("spell_expose_rathorthorn_root") {}

    bool EffectDummy(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Object* pTarget, ObjectGuid /*originalCasterGuid*/) override
    {
        if (uiSpellId == SPELL_EXPOSE_RAZORTHORN_ROOT && uiEffIndex == EFFECT_INDEX_0)
        {
            if (pTarget->GetEntry() != NPC_RAZORTHORN_RAVAGER)
            {
                return true;
            }

            if (GameObject* pMound = GetClosestGameObjectWithEntry(pTarget->ToCreature(), GO_RAZORTHORN_DIRT_MOUND, 20.0f))
            {
                if (pMound->GetRespawnTime() != 0)
                {
                    return true;
                }

                pTarget->ToCreature()->CastSpell(pTarget->ToCreature(), SPELL_SUMMON_RAZORTHORN_ROOT, true);
                pMound->SetLootState(GO_JUST_DEACTIVATED);
            }
        }
        return true;
    }
};

void AddSC_spell_scripts()
{
    Script* s;

    s = new spell_cast_fishing_net();
    s->RegisterSelf();
    s = new aura_spirit_particles();
    s->RegisterSelf();
    s = new aura_healing_salve();
    s->RegisterSelf();
    s = new aura_healing_salve_dummy();
    s->RegisterSelf();
    s = new aura_recharging_battery();
    s->RegisterSelf();
    s = new aura_tag_murloc();
    s->RegisterSelf();
    s = new aura_enrage_45111();
    s->RegisterSelf();
    s = new aura_photovoltaic_magneto_collector();
    s->RegisterSelf();
    s = new spell_apply_salve();
    s->RegisterSelf();
    s = new spell_sacred_cleansing();
    s->RegisterSelf();
    s = new spell_melodious_rapture();
    s->RegisterSelf();
    s = new spell_administer_antidote();
    s->RegisterSelf();
    s = new spell_inoculate_owlkin();
    s->RegisterSelf();
    s = new spell_fel_siphon_dummy();
    s->RegisterSelf();
    s = new spell_tag_murloc_proc();
    s->RegisterSelf();
    s = new spell_orb_of_murloc_control();
    s->RegisterSelf();
    s = new spell_fumping();
    s->RegisterSelf();
    s = new spell_throw_gordawg_boulder();
    s->RegisterSelf();
    s = new spell_expose_rathorthorn_root();
    s->RegisterSelf();
}