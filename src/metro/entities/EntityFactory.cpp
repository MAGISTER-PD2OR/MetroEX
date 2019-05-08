#include "EntityFactory.h"
#include "metro/Config.h"
#include "metro/MetroConfigDatabase.h"
#include "metro/MetroReflection.h"
#include "Entity.h"

#include "log.h"


namespace {
const char* clsids[] = {
    "AI_VISION_HELPER_ENTITY",
    "AMEBA",
    "AMMO",
    "ANIM_OBJECT",
    "ANIMSCRIPT",
    "ANOMALY",
    "AQUA_FEMALE",
    "AQUA_MALE_BIG",
    "AQUA_MALE_SMALL",
    "ARAHIND",
    "ARM_DEVICES",
    "BIG_MOTHER",
    "BINOCULARS",
    "BIOMASS_LARGE",
    "BLIND",
    "BOAT",
    "BREAKABLE_ADVANCED",
    "BREAKABLE_ICE",
    "BROADENED_LIAN",
    "BUSH",
    "BUSH_ZONE",
    "CAM_TRACK",
    "CANNIBAL",
    "CATFISH",
    "CHARGER",
    "CLAYMORE_ZONE",
    "CLOCK",
    "COMPASS",
    "COSTUME_UPGRADE",
    "DARK",
    "DARKCHILD",
    "DEER",
    "DEVICE",
    "DEVICE_UPGRADE",
    "DEVICE_UPGRADE_LAMP",
    "DOG",
    "DREZINA_HAND",
    "DREZINA_MOTO",
    "DUMMY_NPC",
    "EFFECT",
    "EFFECTM",
    "FILTER",
    "FLEXIBLE_ENTITY",
    "FLOWER",
    "FLYING_CREATURE",
    "FORCE_FIELD",
    "G_LEVEL",
    "G_PERSIS",
    "GASMASK",
    "GATEWAY",
    "GRIZLY",
    "HANDS_FOR_DREZINA",
    "HARPY",
    "HEAD_SHOT",
    "headquarter",
    "HEAP",
    "HEAP_ZONE",
    "HELSING_ARROW",
    "HELSING_ARROW_BREAKABLE",
    "HUD_MNGR",
    "HUD_OBJECT",
    "HUMAN",
    "HUMANIMAL",
    "KID",
    "KULEMET",
    "LADDER",
    "LIAN",
    "LIBRARIAN",
    "LIGHTER",
    "LIGHTER_VISUAL",
    "LURKER",
    "MAP_PAD_UPGRADE",
    "MECH_ENTITY",
    "MEDKIT",
    "MEDKIT_HEAP",
    "MEDKIT_SPECIAL",
    "METAL_DETECTOR_UPGRADE",
    "MODIFIER",
    "MONSTER",
    "MOTION_SENSOR_UPGRADE",
    "MOUNT_GUN",
    "NIGHTVISION",
    "NOSACH",
    "NOSALIS",
    "NOSALIS_FEMALE",
    "NPC",
    "NPC_FX",
    "O_AIPOINT",
    "O_ANIM_ENTITY",
    "O_BASEZONE",
    "O_BRKBL",
    "O_COVER_LINK",
    "O_DUMMY",
    "O_ENTITY",
    "O_EXPLOSION",
    "O_HELPERTEXT",
    "O_HELPERTEXT_COUNTER",
    "o_hlamp",
    "O_INTEREST",
    "O_PHYSICS",
    "O_SCALING_ENTITY",
    "O_WATERZONE",
    "OBJECT",
    "PARTICLES",
    "PATROL_POINT",
    "PLAYER",
    "PLAYER_MAP",
    "PLAYER_TIMER",
    "PLAYER_TIMER_2033",
    "PLAYER_TIMER_UPGRADE",
    "PLAYERS_BODY",
    "PLAYERS_HANDS",
    "PLAYERS_KNIFE",
    "PROXY",
    "PULSOMETER_UPGRADE",
    "RABBIT",
    "RAGDOLL",
    "RAIL_ENTITY",
    "RAT",
    "s_actor",
    "SCRIPTED_ENTITY",
    "SHIELD",
    "siege_bomb",
    "SIMPLE",
    "SIMPLE_MONSTER",
    "SIMPLE_NPC",
    "SNAKE",
    "SOFT_ENTITY",
    "SOFT_ENTITY_INST",
    "STATICPROP",
    "STATICPROP_BREAKABLE",
    "STATICPROP_MOVABLE",
    "STATION_STAND",
    "STRETCHY_HAND",
    "STRETCHY_HANDLEFT",
    "STRETCHY_MAN",
    "TAPE",
    "TORCH",
    "TORCHLIGHT",
    "TORCHLIGHT_UPGRADABLE",
    "TREADMILL_TILE",
    "TURRET",
    "UPGRADE_TAGS",
    "VEHICLE",
    "VIRTUAL_CAMERA",
    "VIRTUAL_HAND",
    "VIRTUAL_MONITOR",
    "VISOR",
    "VISUALSCRIPT",
    "VISUALSCRIPT_REF",
    "VR_ENTITY",
    "WALLMARK",
    "WATCHMAN",
    "WAVES_EMITTER",
    "WB_WEAPON_HOLDER",
    "WEAPON",
    "WEAPON_2012",
    "WEAPON_ABZAC",
    "WEAPON_AK_74",
    "WEAPON_AK74",
    "WEAPON_AK74_TEST",
    "WEAPON_AKSU",
    "WEAPON_ASHOT",
    "WEAPON_ASHOT_2B",
    "WEAPON_BIGUN",
    "WEAPON_C4_DYNAMITE",
    "WEAPON_CLAYMORE",
    "WEAPON_DAGGER",
    "WEAPON_DECOY",
    "WEAPON_DSHK",
    "WEAPON_DUPLET",
    "WEAPON_DUPLET_2B",
    "WEAPON_DUPLET_3B",
    "WEAPON_DUPLET_4B",
    "WEAPON_DYNAMITE",
    "WEAPON_FAKE",
    "WEAPON_FLAME",
    "WEAPON_FLAME_DYNAMITE",
    "WEAPON_FLAME_GRENADE",
    "WEAPON_FLAMETHROWER",
    "WEAPON_FLARE",
    "WEAPON_GATLING",
    "WEAPON_HELLBREATH",
    "WEAPON_HELLBREATH_SHOCK",
    "WEAPON_HELSING",
    "WEAPON_HOLDER",
    "WEAPON_ITEM",
    "WEAPON_ITEM_AMMO",
    "WEAPON_ITEM_LAMP",
    "WEAPON_ITEM_LAMP_BACKLIGHT",
    "WEAPON_ITEM_LASER",
    "WEAPON_ITEM_MAGAZINE",
    "WEAPON_ITEM_NOOBEGUN",
    "WEAPON_ITEM_NOOBETUBE",
    "WEAPON_ITEM_OPTIC",
    "WEAPON_ITEM_PRESET",
    "WEAPON_ITEM_SILENCER",
    "WEAPON_ITEM_SPEEDLOADER",
    "WEAPON_ITEM_VR",
    "WEAPON_ITEM_VR_ATTACH",
    "WEAPON_KNIVES",
    "WEAPON_LAUNCHER",
    "WEAPON_LAUNCHER_TIME",
    "WEAPON_MACHETA",
    "WEAPON_MAG",
    "WEAPON_MEDVED",
    "WEAPON_NOOB_LAUNCHER",
    "WEAPON_NOOB_SHOTGUN",
    "WEAPON_PADONAG",
    "WEAPON_PREVED",
    "WEAPON_REVOLVER",
    "WEAPON_RPK",
    "WEAPON_SAIGA",
    "WEAPON_SHOTGUN",
    "WEAPON_STICKY_DYNAMITE",
    "WEAPON_TIHAR",
    "WEAPON_TUMAK",
    "WEAPON_UBLUDOK",
    "WEAPON_UBOYNICHEG",
    "WEAPON_VENTIL",
    "WEAPON_VSV",
    "WEAPON_VYHLOP",
    "WEB",
    "WEB_ZONE",
    "WICK_VISUAL",
    "WOMAN",
    "WOMAN_COMBAT",
    "WOMAN_STRIP",
};

const char* staticDataKeys[] = {
    "_G.config.entity.ai_point",
    "_G.config.entity.ai_vision_helper_entity",
    "_G.config.entity.ammo_044_ap",
    "_G.config.entity.ammo_044_fmj",
    "_G.config.entity.ammo_12x70mm",
    "_G.config.entity.ammo_12x70mm_fire",
    "_G.config.entity.ammo_12x70mm_flamethrower",
    "_G.config.entity.ammo_12x70mm_flamethrower_unlim",
    "_G.config.entity.ammo_12x70mm_macheta",
    "_G.config.entity.ammo_12x70mm_macheta_alt",
    "_G.config.entity.ammo_12x70mm_macheta_alt_free",
    "_G.config.entity.ammo_12x70mm_macheta_fast",
    "_G.config.entity.ammo_15mm",
    "_G.config.entity.ammo_15mm_sabot",
    "_G.config.entity.ammo_545x39_fmj",
    "_G.config.entity.ammo_762x39_fmj",
    "_G.config.entity.ammo_762x39_mg",
    "_G.config.entity.ammo_762x39_mg_light",
    "_G.config.entity.ammo_762x39_mg_nopierce",
    "_G.config.entity.ammo_flamethrower_alt",
    "_G.config.entity.ammo_handgun_oculus",
    "_G.config.entity.ammo_makeshift_oculus",
    "_G.config.entity.ammo_money",
    "_G.config.entity.ammo_rifle_oculus",
    "_G.config.entity.ammo_shell_ak74",
    "_G.config.entity.ammo_shell_ashot",
    "_G.config.entity.ammo_shell_base",
    "_G.config.entity.ammo_shell_revolver",
    "_G.config.entity.ammo_shell_ubludok",
    "_G.config.entity.ammo_shell_uboynicheg",
    "_G.config.entity.ammo_shell_ventil",
    "_G.config.entity.ammo_shotgun_alt_oculus",
    "_G.config.entity.ammo_shotgun_e_mag_oculus",
    "_G.config.entity.ammo_shotgun_oculus",
    "_G.config.entity.ammo_shotgun_sf4ag_oculus",
    "_G.config.entity.ammo_sniper_oculus",
    "_G.config.entity.anim_entity",
    "_G.config.entity.aqua_female",
    "_G.config.entity.aqua_male_small",
    "_G.config.entity.arahind",
    "_G.config.entity.arm_devices",
    "_G.config.entity.armor",
    "_G.config.entity.battery",
    "_G.config.entity.binoculars",
    "_G.config.entity.blind",
    "_G.config.entity.boat",
    "_G.config.entity.bulletproof",
    "_G.config.entity.cannibal",
    "_G.config.entity.catfish",
    "_G.config.entity.charger",
    "_G.config.entity.charger_visual",
    "_G.config.entity.chemical_tier",
    "_G.config.entity.clock",
    "_G.config.entity.color",
    "_G.config.entity.compass",
    "_G.config.entity.craft_chemical",
    "_G.config.entity.craft_consumable",
    "_G.config.entity.craft_metal",
    "_G.config.entity.darkchild",
    "_G.config.entity.deer",
    "_G.config.entity.design",
    "_G.config.entity.device_upgrade_base",
    "_G.config.entity.diversionary_tier",
    "_G.config.entity.dog",
    "_G.config.entity.drezina_hand",
    "_G.config.entity.drezina_moto",
    "_G.config.entity.dummy",
    "_G.config.entity.effect",
    "_G.config.entity.effectm",
    "_G.config.entity.empty_armor",
    "_G.config.entity.empty_bracer",
    "_G.config.entity.empty_clock",
    "_G.config.entity.empty_helmet",
    "_G.config.entity.empty_torchlight",
    "_G.config.entity.empty_unloading",
    "_G.config.entity.empty_unloading_spartain",
    "_G.config.entity.entity",
    "_G.config.entity.explosion",
    "_G.config.entity.filter",
    "_G.config.entity.flexible_entity",
    "_G.config.entity.flying_creature",
    "_G.config.entity.force_field",
    "_G.config.entity.gasmask",
    "_G.config.entity.geiger_test",
    "_G.config.entity.grizly",
    "_G.config.entity.hands_for_drezina",
    "_G.config.entity.hanging_lamp",
    "_G.config.entity.harpy",
    "_G.config.entity.heavy_armor",
    "_G.config.entity.hud_object",
    "_G.config.entity.humanimal",
    "_G.config.entity.interest",
    "_G.config.entity.kid",
    "_G.config.entity.kulemet",
    "_G.config.entity.kulemet_bashnya",
    "_G.config.entity.kulemet_bashnya_nopierce",
    "_G.config.entity.ladder",
    "_G.config.entity.light_armor",
    "_G.config.entity.lighter",
    "_G.config.entity.lighter_visual",
    "_G.config.entity.luminosity",
    "_G.config.entity.lurker",
    "_G.config.entity.map_visual",
    "_G.config.entity.medkit",
    "_G.config.entity.metal_detector",
    "_G.config.entity.middle_worm",
    "_G.config.entity.modifier",
    "_G.config.entity.motion_detector",
    "_G.config.entity.nightvision",
    "_G.config.entity.nosalis",
    "_G.config.entity.npc_enemy_fx",
    "_G.config.entity.npc_friend_fx",
    "_G.config.entity.patrol_point",
    "_G.config.entity.pendulum",
    "_G.config.entity.player",
    "_G.config.entity.player_map",
    "_G.config.entity.players_hands",
    "_G.config.entity.power",
    "_G.config.entity.proxy",
    "_G.config.entity.pulsometer_test",
    "_G.config.entity.rabbit",
    "_G.config.entity.radio",
    "_G.config.entity.rail_entity",
    "_G.config.entity.rat",
    "_G.config.entity.reflected_light",
    "_G.config.entity.restrictor",
    "_G.config.entity.scaling_entity",
    "_G.config.entity.scripted_entity",
    "_G.config.entity.simple_anomaly",
    "_G.config.entity.small_worm",
    "_G.config.entity.soft_entity",
    "_G.config.entity.spartain_tier",
    "_G.config.entity.speed",
    "_G.config.entity.static",
    "_G.config.entity.static_breakable",
    "_G.config.entity.static_movable",
    "_G.config.entity.station",
    "_G.config.entity.tape",
    "_G.config.entity.text_helper",
    "_G.config.entity.timer",
    "_G.config.entity.torchlight_upgradable",
    "_G.config.entity.treadmill_tile",
    "_G.config.entity.upgrade_ammunition",
    "_G.config.entity.upgrade_battery",
    "_G.config.entity.upgrade_extended_equip",
    "_G.config.entity.upgrade_extended_fastdrop",
    "_G.config.entity.upgrade_filter",
    "_G.config.entity.upgrade_glass",
    "_G.config.entity.upgrade_googles",
    "_G.config.entity.upgrade_helm",
    "_G.config.entity.upgrade_lamp",
    "_G.config.entity.upgrade_power",
    "_G.config.entity.vehicle",
    "_G.config.entity.visor0",
    "_G.config.entity.visor1",
    "_G.config.entity.visor2",
    "_G.config.entity.visor3",
    "_G.config.entity.vr_attach_base",
    "_G.config.entity.vr_upgrade_base",
    "_G.config.entity.vs",
    "_G.config.entity.wallmark",
    "_G.config.entity.watchman",
    "_G.config.entity.waterzone",
    "_G.config.entity.waves_emitter",
    "_G.config.entity.wb_weapon_holder",
    "_G.config.entity.weapon_ammo_base",
    "_G.config.entity.weapon_item_inh",
    "_G.config.entity.weapon_item_lamp",
    "_G.config.entity.weapon_item_lamp_backlight",
    "_G.config.entity.weapon_laser_base",
    "_G.config.entity.weapon_magazine_ak_small_loot",
    "_G.config.entity.weapon_magazine_helsing_ext_altammo_loot",
    "_G.config.entity.weapon_magazine_helsing_ext_loot",
    "_G.config.entity.weapon_magazine_helsing_small_altammo_loot",
    "_G.config.entity.weapon_magazine_helsing_small_loot",
    "_G.config.entity.weapon_magazine_ng",
    "_G.config.entity.weapon_magazine_revolver_small_loot",
    "_G.config.entity.weapon_magazine_tihar_small_altammo_loot",
    "_G.config.entity.weapon_magazine_tihar_small_loot",
    "_G.config.entity.weapon_magazine_ubludok_small_loot",
    "_G.config.entity.weapon_magazine_ubo_small_loot",
    "_G.config.entity.weapon_magazine_ubo_std_loot",
    "_G.config.entity.weapon_magazine_ventil_loot",
    "_G.config.entity.weapon_preset_base",
    "_G.config.entity.weapon_scope_base",
    "_G.config.entity.weapon_silencer_base",
    "_G.config.entity.weapon_speedloader_base",
    "_G.config.entity.web",
    "_G.config.entity.wick_visual",
    "_G.config.entity.woman",
    "_G.config.entity.woman_combat",
    "_G.config.entity.woman_strip",
    "_G.config.entity.worm",
    "_G.config.entity.wpn_ak_74_ng",
    "_G.config.entity.wpn_anomaly",
    "_G.config.entity.wpn_aqua_sputum",
    "_G.config.entity.wpn_arrow",
    "_G.config.entity.wpn_arrow_breakable",
    "_G.config.entity.wpn_ashot_ng",
    "_G.config.entity.wpn_cannibal_grenage",
    "_G.config.entity.wpn_dagger",
    "_G.config.entity.wpn_decoy",
    "_G.config.entity.wpn_dynamite",
    "_G.config.entity.wpn_dynamite_npc",
    "_G.config.entity.wpn_dynamite_paint",
    "_G.config.entity.wpn_dynamite_small",
    "_G.config.entity.wpn_flame_good",
    "_G.config.entity.wpn_flame_grenage",
    "_G.config.entity.wpn_flame_grenage_npc",
    "_G.config.entity.wpn_flamethrower_grenage",
    "_G.config.entity.wpn_flamethrower_ng",
    "_G.config.entity.wpn_flare",
    "_G.config.entity.wpn_gatling_ng",
    "_G.config.entity.wpn_helsing_ng",
    "_G.config.entity.wpn_humanimal_stuff",
    "_G.config.entity.wpn_macheta",
    "_G.config.entity.wpn_revolver_ng",
    "_G.config.entity.wpn_spider_sputum",
    "_G.config.entity.wpn_tihar_ng",
    "_G.config.entity.wpn_ubludok_ng",
    "_G.config.entity.wpn_uboynicheg_ng",
    "_G.config.entity.wpn_ventil_ng",
    "_G.config.entity.wpn_vyhlop_ng",
    "_G.config.entity.wpn_water_worm_sputum",
};

MyDict<uint32_t, const char*> CreateClassMap() {
    MyDict<uint32_t, const char*> result;
    for (auto el : clsids)
        result[Hash_CalculateCRC32(el)] = el;
    return result;
}

MyDict<uint32_t, const char*> CreateStaticDataMap() {
    MyDict<uint32_t, const char*> result;
    for (auto el : staticDataKeys)
        result[Hash_CalculateCRC32(el)] = el;
    return result;
}

uobject* Create(uint32_t clsid) {
    switch (clsid) {
    // case 0xcea8466e: // PLAYER_TIMER_UPGRADE
    //    return new player_timer_hud_item_object;
    // case 0x0cbbe8a6: // o_hlamp
    //    return new lamp;
    case 0x46985674: // EFFECT
        return new uobject_effect;
    case 0x2301c4ef: // STATICPROP
        return new uobject_static;
    case 0x0f10b43b: // O_ENTITY
        return new centity;
    case 0x54571bfa: // VISUALSCRIPT
        return new uobject_vs;
    default:
        return new UnknownObject;
    }
}

MyDict<uint64_t, std::unique_ptr<uobject_static_params>> paramCache;

uobject_static_params* CreateStaticParam(uint32_t clsid) {
    switch (clsid) {
        // case 0xcea8466e: // PLAYER_TIMER_UPGRADE
        //   return new player_timer_hud_item_object_static_params;
        // case 0x0cbbe8a6: // o_hlamp
        //    return new lamp;
    case 0x46985674: // EFFECT
        return new uobject_static_params;
    case 0x2301c4ef: // STATICPROP
        return new uobject_static_params;
    case 0x0f10b43b: // O_ENTITY
        return new centity_static_params;
    case 0x54571bfa: // VISUALSCRIPT
        return new uobject_static_params;
    default:
        return new unknown_static_params;
    }
}
}

namespace EntityFactory {

    uobject* Create(const InitData& data) {
        static auto classMap = CreateClassMap();
        static auto staticMap = CreateStaticDataMap();
        CharString  cls = classMap[data.clsid];
        CharString  staticData = staticMap[data.static_data_key];
        uobject*    entity = ::Create(data.clsid);
        entity->initData = data;
        entity->cls = cls;
        entity->static_data = staticData;
        return entity;
    }

    uobject_static_params* GetStaticParams(const InitData& init, MemStream& config) {
        const uint64_t key = (scast<uint64_t>(init.clsid) << 32) | init.static_data_key;
        auto it = paramCache.find(key);
        if (it != paramCache.end()) {
            return it->second.get();
        }

        auto param = CreateStaticParam(init.clsid);
        paramCache[key].reset(param);

        char cfgName[256];
        sprintf(cfgName, "content\\scripts\\static_data\\%08x_%08x_%08x.bin", init.clsid, init.clsid, init.static_data_key);
        const auto* cfgInfo = MetroConfigsDatabase::Get().FindFile(cfgName);
        const auto* cfgInfo2 = MetroConfigsDatabase::Get().FindFile(Hash_CalculateCRC32(cfgName));
        assert(cfgInfo2);
        if (!cfgInfo) {
            LogPrint(LogLevel::Warning, "Unknown static data: ", cfgName);
        }

        config.SetCursor(cfgInfo2->offset);
        MemStream stream = config.Substream(cfgInfo2->length);
        MetroReflectionReader r(stream);

        uint16_t version;
        METRO_READ_MEMBER(r, version);
        r.SetUserData(version);
        param->Serialize(r);

        assert(r.GetStream().Ended());

        return param;
    }
}