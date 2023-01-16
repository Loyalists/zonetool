#include "stdafx.hpp"
#include "H1/Assets/Sound.hpp"

#define STREAMED_TO_LOADED_IW3

namespace ZoneTool
{
	namespace IW3
	{
		H1::SoundDspBus channel_to_dspbus_index[33]
		{
			H1::SND_DSPBUS_PHYSICS,		//SND_CHANNEL_PHYSICS,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_AUTO,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_AUTO2,
			H1::SND_DSPBUS_ANIMALS,		//SND_CHANNEL_AUTODOG,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_BULLETIMPACT,
			H1::SND_DSPBUS_WHIZBYS,		//SND_CHANNEL_BULLETWHIZBY,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_ELEMENT,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_AUTO2D,
			H1::SND_DSPBUS_VEHICLES,	//SND_CHANNEL_VEHICLE,
			H1::SND_DSPBUS_VEHICLES,	//SND_CHANNEL_VEHICLELIMITED,
			H1::SND_DSPBUS_INTERFACE,	//SND_CHANNEL_MENU,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_BODY,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_BODY2D,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_RELOAD,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_RELOAD2D,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_ITEM,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_EFFECTS1,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_EFFECTS2,
			H1::SND_DSPBUS_WEAPONS,		//SND_CHANNEL_WEAPON,
			H1::SND_DSPBUS_WEAPONS,		//SND_CHANNEL_WEAPON2D,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_NONSHOCK,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_VOICE,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_LOCAL,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_LOCAL2,
			H1::SND_DSPBUS_AMBIENCE,	//SND_CHANNEL_AMBIENT,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_HURT,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_PLAYER1,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_PLAYER2,
			H1::SND_DSPBUS_MUSIC,		//SND_CHANNEL_MUSIC,
			H1::SND_DSPBUS_MUSIC,		//SND_CHANNEL_MUSICNOPAUSE,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_MISSION,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_ANNOUNCER,
			H1::SND_DSPBUS_DEFAULT,		//SND_CHANNEL_SHELLSHOCK,
		};

		H1::SoundVolMod channel_to_volmod_index[33]
		{
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_PHYSICS,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_AUTO,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_AUTO2,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_AUTODOG,
			H1::SND_VOLMOD_IMPACT_CRITICAL,		//SND_CHANNEL_BULLETIMPACT,
			H1::SND_VOLMOD_BULLET_WHIZBY,		//SND_CHANNEL_BULLETWHIZBY,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_ELEMENT,
			H1::SND_VOLMOD_FRONTEND_SFX,		//SND_CHANNEL_AUTO2D,
			H1::SND_VOLMOD_VEHICLE_NPC,			//SND_CHANNEL_VEHICLE,
			H1::SND_VOLMOD_VEHICLE_NPC_SPECIAL,	//SND_CHANNEL_VEHICLELIMITED,
			H1::SND_VOLMOD_HUD,					//SND_CHANNEL_MENU,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_BODY,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_BODY2D,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_RELOAD,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_RELOAD2D,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_ITEM,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_EFFECTS1,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_EFFECTS2,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_WEAPON,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_WEAPON2D,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_NONSHOCK,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_VOICE,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_LOCAL,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_LOCAL2,
			H1::SND_VOLMOD_AMB_QUAD,			//SND_CHANNEL_AMBIENT,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_HURT,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_PLAYER1,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_PLAYER2,
			H1::SND_VOLMOD_MUSIC,				//SND_CHANNEL_MUSIC,
			H1::SND_VOLMOD_MUSIC,				//SND_CHANNEL_MUSICNOPAUSE,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_MISSION,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_ANNOUNCER,
			H1::SND_VOLMOD_DEFAULT,				//SND_CHANNEL_SHELLSHOCK,
		};

		void GenerateH1SoundAlias(snd_alias_t* alias, H1::snd_alias_t* h1_alias, ZoneMemory* mem)
		{
			h1_alias->aliasName = alias->aliasName;
			h1_alias->subtitle = alias->subtitle;
			h1_alias->secondaryAliasName = alias->secondaryAliasName;
			h1_alias->chainAliasName = alias->chainAliasName;

			// todo
			h1_alias->soundFile;
			h1_alias->soundFile = mem->Alloc<H1::SoundFile>();

			h1_alias->soundFile->exists = alias->soundFile->exists;
			h1_alias->soundFile->type = static_cast<H1::snd_alias_type_t>(alias->soundFile->type);

			switch (h1_alias->soundFile->type)
			{
			case H1::snd_alias_type_t::SAT_LOADED:
				h1_alias->soundFile->u.loadSnd = mem->Alloc<H1::LoadedSound>();
				h1_alias->soundFile->u.loadSnd->name = alias->soundFile->sound.loadSnd->name;
				// no need to convert rest
				break;
			case H1::snd_alias_type_t::SAT_STREAMED:
#ifdef STREAMED_TO_LOADED_IW3
				h1_alias->soundFile->type = H1::snd_alias_type_t::SAT_LOADED;
				const std::string s_dir = alias->soundFile->sound.streamSnd.dir;
				const std::string s_name = alias->soundFile->sound.streamSnd.name;
				const auto path = std::filesystem::path(s_dir + "/" + s_name);

				std::string noext_path = s_dir + "/" + path.stem().string();

				h1_alias->soundFile->u.loadSnd = mem->Alloc<H1::LoadedSound>();
				h1_alias->soundFile->u.loadSnd->name = mem->StrDup(noext_path);
#else
				h1_alias->soundFile->u.streamSnd.filename.isLocalized = false;
				h1_alias->soundFile->u.streamSnd.filename.isStreamed = false;
				h1_alias->soundFile->u.streamSnd.filename.fileIndex = 0;

				h1_alias->soundFile->u.streamSnd.filename.info.raw.name = alias->soundFile->sound.streamSnd.name;
				h1_alias->soundFile->u.streamSnd.filename.info.raw.dir = alias->soundFile->sound.streamSnd.dir;

				h1_alias->soundFile->u.streamSnd.totalMsec = 0;
#endif
				break;
			}

			h1_alias->mixerGroup = nullptr;

			h1_alias->poly = 1;
			h1_alias->polyGlobal = 174;
			h1_alias->polyEntityType = 0;
			h1_alias->polyGlobalType = 0;

			h1_alias->dspBusIndex = 0; // default;
			h1_alias->priority = 1;

			h1_alias->__pad0;

			h1_alias->volMin = alias->volMin;
			h1_alias->volMax = alias->volMax;
			h1_alias->volModIndex = 0; // default

			h1_alias->pitchMin = alias->pitchMin;
			h1_alias->pitchMax = alias->pitchMax;

			h1_alias->distMin = alias->distMin;
			h1_alias->distMax = alias->distMax;

			h1_alias->velocityMin = 0.0f;

			h1_alias->masterPriority = 50;
			h1_alias->masterPercentage = 0.0f;

			h1_alias->slavePercentage = alias->slavePercentage;

			h1_alias->playbackPercentage = 100;
			h1_alias->probability = alias->probability;

			h1_alias->sndContext = nullptr;

			h1_alias->sequence = alias->sequence;
			h1_alias->lfePercentage = alias->lfePercentage;
			h1_alias->centerPercentage = alias->centerPercentage;
			h1_alias->startDelay = alias->startDelay;

			auto* default_sndcurve = mem->Alloc<H1::SndCurve>();
			default_sndcurve->name = "$default";

			H1::SndCurve* sndcurve = nullptr;
			if (alias->volumeFalloffCurve && alias->volumeFalloffCurve->filename != ""s)
			{
				sndcurve = mem->Alloc<H1::SndCurve>();
				sndcurve->filename = alias->volumeFalloffCurve->filename;
				sndcurve->isDefault = 0;
				sndcurve->knotCount = alias->volumeFalloffCurve->knotCount;
				memcpy(sndcurve->knots, alias->volumeFalloffCurve->knots, sizeof(float[16][2]));
			}
			else
			{
				sndcurve = default_sndcurve;
			}

			h1_alias->sndCurve = sndcurve;
			h1_alias->lpfCurve = default_sndcurve;
			h1_alias->reverbSendCurve = default_sndcurve;

			h1_alias->speakerMap = nullptr;
			if (alias->speakerMap)
			{
				h1_alias->speakerMap = mem->Alloc<H1::SpeakerMap>();
				h1_alias->speakerMap->isDefault = alias->speakerMap->isDefault;
				h1_alias->speakerMap->name = alias->speakerMap->name;
				h1_alias->speakerMap->unknown = 0;

				for (char x = 0; x < 2; x++)
				{
					for (char y = 0; y < 2; y++)
					{
						h1_alias->speakerMap->channelMaps[x][y].speakerCount = alias->speakerMap->channelMaps[x][y].entryCount;
						for (char i = 0; i < 6; i++)
						{
							h1_alias->speakerMap->channelMaps[x][y].speakers[i].speaker = alias->speakerMap->channelMaps[x][y].speakers[i].speaker;
							h1_alias->speakerMap->channelMaps[x][y].speakers[i].numLevels = alias->speakerMap->channelMaps[x][y].speakers[i].numLevels;
							h1_alias->speakerMap->channelMaps[x][y].speakers[i].levels[0] = alias->speakerMap->channelMaps[x][y].speakers[i].levels[0];
							h1_alias->speakerMap->channelMaps[x][y].speakers[i].levels[1] = alias->speakerMap->channelMaps[x][y].speakers[i].levels[1];
						}
					}
				}
			}

			h1_alias->envelopMin = alias->envelopMin;
			h1_alias->envelopMax = alias->envelopMax;

			h1_alias->reverbWetMixOverride = 0.0f;
			h1_alias->reverbMultiplier = 1.0f;
			h1_alias->smartPanDistance2d = 0.0f;
			h1_alias->smartPanDistance3d = 0.0f;
			h1_alias->smartPanAttenuation3d = 1.0f;

			h1_alias->envelopPercentage = alias->envelopPercentage;

			h1_alias->stereo3dAngle = 0;
			h1_alias->stereo3dStart = 0.0f;
			h1_alias->stereo3dEnd = 0.0f;

			h1_alias->allowDoppler = 0;
			h1_alias->dopplerPreset = nullptr;

			h1_alias->u1 = 4; // always 4?
			h1_alias->u2 = 0.5011872053146362f; // unk

			// convert flags
			H1::SoundAliasFlags h1_flags{ 0 };
			IW3::SoundAliasFlags iw3_flags{ 0 };

			h1_flags.intValue = 0;
			iw3_flags.intValue = alias->flags;

			// h1 struct may be wrong?
			h1_flags.packed.looping = iw3_flags.looping;
			h1_flags.packed.isMaster = iw3_flags.isMaster;
			h1_flags.packed.isSlave = iw3_flags.isSlave;
			h1_flags.packed.fullDryLevel = iw3_flags.fullDryLevel;
			h1_flags.packed.noWetLevel = iw3_flags.noWetLevel;
			h1_flags.packed.is3d = iw3_flags.unknown1;
			h1_flags.packed.unk1 = 6; // ? 4 = world sound, 6 = ambient
			h1_flags.packed.type = h1_alias->soundFile->type; //iw3_flags.type;
			h1_flags.packed.unk2 = 0;

			h1_alias->flags = h1_flags.intValue;

			h1_alias->volModIndex = channel_to_volmod_index[iw3_flags.channel];
			h1_alias->dspBusIndex = channel_to_dspbus_index[iw3_flags.channel];
		}

		H1::snd_alias_list_t* GenerateH1Sound(snd_alias_list_t* asset, ZoneMemory* mem)
		{
			auto* h1_asset = mem->Alloc<H1::snd_alias_list_t>();
			h1_asset->aliasName = asset->aliasName;
			
			h1_asset->count = asset->count;
			h1_asset->head = mem->Alloc<H1::snd_alias_t>(h1_asset->count);
			for (unsigned char i = 0; i < h1_asset->count; i++)
			{
				GenerateH1SoundAlias(&asset->head[i], &h1_asset->head[i], mem);
			}

			h1_asset->contextList = nullptr;
			h1_asset->contextListCount = 0;

			return h1_asset;
		}

		void ISound::dump(snd_alias_list_t* asset, ZoneMemory* mem)
		{
			// generate h1 asset
			auto* h1_asset = GenerateH1Sound(asset, mem);

			// dump lightdef
			H1::ISound::dump(h1_asset);
		}
	}
}