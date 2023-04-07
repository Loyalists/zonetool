#pragma once

namespace mapents2spawns
{
	constexpr unsigned int MAX_SPAWNS = 0x1000;

	struct SpawnPoint
	{
		const char* name;
		const char* target;
		const char* script_noteworthy;
		const char* unknown;
		float origin[3];
		float angles[3];
	};

	struct SpawnPointList
	{
		int num_spawns;
		SpawnPoint* spawns;
	};

	SpawnPointList* generate_spawnpoint_list(char* entity_string);
	void dump_spawnpoint_list(const std::string& output, SpawnPointList* list);
	void dump_spawns(const std::string& out, char* entity_string);
}

namespace entitystrings
{
	class ents
	{
	public:

		ents() {};
		ents(const char* string, size_t lenPlusOne) : ents(std::string(string, lenPlusOne - 1)) {}
		ents(std::string buffer) : ents() { this->parse(buffer); };
		ents(const ents& obj) : entities(obj.entities) {};

		std::string build()
		{
			std::string entityString;

			for (auto& entity : this->entities)
			{
				entityString.append("{\n");

				for (auto& property : entity)
				{
					entityString.push_back('"');
					entityString.append(property.first);
					entityString.append("\" \"");
					entityString.append(property.second);
					entityString.append("\"\n");
				}

				entityString.append("}\n");
			}

			return entityString;
		}

	private:
		enum
		{
			PARSE_AWAIT_KEY,
			PARSE_READ_KEY,
			PARSE_AWAIT_VALUE,
			PARSE_READ_VALUE,
		};

		std::vector<std::unordered_map<std::string, std::string>> entities;

		void parse(std::string buffer)
		{
			int parseState = 0;
			std::string key;
			std::string value;
			std::unordered_map<std::string, std::string> entity;

			for (unsigned int i = 0; i < buffer.size(); ++i)
			{
				char character = buffer[i];
				if (character == '{')
				{
					entity.clear();
				}

				switch (character)
				{
				case '{':
				{
					entity.clear();
					break;
				}

				case '}':
				{
					this->entities.push_back(entity);
					entity.clear();
					break;
				}

				case '"':
				{
					if (parseState == PARSE_AWAIT_KEY)
					{
						key.clear();
						parseState = PARSE_READ_KEY;
					}
					else if (parseState == PARSE_READ_KEY)
					{
						parseState = PARSE_AWAIT_VALUE;
					}
					else if (parseState == PARSE_AWAIT_VALUE)
					{
						value.clear();
						parseState = PARSE_READ_VALUE;
					}
					else if (parseState == PARSE_READ_VALUE)
					{
						entity[to_lower_copy(key)] = value;
						parseState = PARSE_AWAIT_KEY;
					}
					else
					{
						throw std::runtime_error("Parsing error!");
					}
					break;
				}

				default:
				{
					if (parseState == PARSE_READ_KEY) key.push_back(character);
					else if (parseState == PARSE_READ_VALUE) value.push_back(character);

					break;
				}
				}
			}
		}
	};
}