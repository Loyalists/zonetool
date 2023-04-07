#include "stdafx.hpp"
//#include "H1/Assets/LoadedSound.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void ILoadedSound::dump(LoadedSound* asset, ZoneMemory* mem)
		{
			auto sound = asset;
			auto fp = FileSystem::FileOpen("loaded_sound/"s + asset->name, "wb");

			if (fp)
			{
				char chunkID[] = { 'R', 'I', 'F', 'F' };
				fwrite(chunkID, 4, 1, fp);

				// ChunkSize
				int subchunk1Size = 16;
				int subchunk2Size = sound->sound.info.data_len;
				int chunkSize = 4 + (8 + subchunk1Size) + (8 + subchunk2Size);
				fwrite(&chunkSize, 4, 1, fp);

				// Format
				char format[] = { 'W', 'A', 'V', 'E' };
				fwrite(format, 4, 1, fp);


				// --- FMT SUBCHUNK
				// Subchunk1ID
				char subchunk1ID[] = { 'f', 'm', 't', ' ' };
				fwrite(subchunk1ID, 4, 1, fp);

				// Subchunk1Size
				fwrite(&subchunk1Size, 4, 1, fp);

				// AudioFormat
				short audioFormat = sound->sound.info.format;
				fwrite(&audioFormat, 2, 1, fp);

				// NumChannels
				short numChannels = sound->sound.info.channels;
				fwrite(&numChannels, 2, 1, fp);

				// SampleRate
				int sampleRate = sound->sound.info.rate;
				fwrite(&sampleRate, 4, 1, fp);

				// ByteRate
				int byteRate = sound->sound.info.rate * sound->sound.info.channels * sound->sound.info.bits / 8;
				fwrite(&byteRate, 4, 1, fp);

				// BlockAlign
				short blockAlign = sound->sound.info.block_size;
				fwrite(&blockAlign, 2, 1, fp);

				// BitsPerSample
				short bitsPerSample = sound->sound.info.bits;
				fwrite(&bitsPerSample, 2, 1, fp);


				// --- DATA SUBCHUNK
				// Subchunk2ID
				char subchunk2ID[] = { 'd', 'a', 't', 'a' };
				fwrite(subchunk2ID, 4, 1, fp);

				// Subchunk2Size
				fwrite(&subchunk2Size, 4, 1, fp);

				// Data
				fwrite(sound->sound.data, sound->sound.info.data_len, 1, fp);
			}

			FileSystem::FileClose(fp);
		}
	}
}