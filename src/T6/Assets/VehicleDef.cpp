// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace T6
	{
#define VEHICLE_DUMP_FIELD(__field__) \
	data[#__field__] = asset->__field__

#define VEHICLE_DUMP_ASSET(__field__) \
	if (asset->__field__) \
	{ \
		data[#__field__] = asset->__field__->name; \
	} \
	else \
	{ \
		data[#__field__] = ""; \
	}

#define VEHICLE_DUMP_FIELD_ARR(__field__, __size__) \
	for (auto idx##__field__ = 0; idx##__field__ < __size__; idx##__field__++) \
	{ \
		data[#__field__][idx##__field__] = asset->__field__[idx##__field__]; \
	}

#define VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(__field__) \
	data["turretViewLimits"][#__field__] = asset->turretViewLimits.__field__

#define VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(__field__, __index__) \
	data["passengerViewLimits"][__index__][#__field__] = asset->passengerViewLimits[__index__].__field__

#define VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(__field__) \
	data[#__field__] = asset->nitrousVehParams.__field__

#define VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(__field__, __size__) \
	for (auto idx##__field__ = 0; idx##__field__ < __size__; idx##__field__++) \
	{ \
		data[#__field__][idx##__field__] = asset->nitrousVehParams.__field__[idx##__field__]; \
	}

#define VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(__field__) \
	data[#__field__] = asset->engine.__field__

		Json IVehicleDef::dump_vehicle_parameters(VehicleDef* asset)
		{
			Json data;
			if (asset->nitrousVehParams.m_name)
			{
				data["m_name"] = asset->nitrousVehParams.m_name;
			}
			else
			{
				data["m_name"] = "";
			}
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_speed_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_accel_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_reverse_scale);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_steer_angle_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_steer_angle_speed_scale);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_steer_speed);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_wheel_radius);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_susp_spring_k);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_susp_damp_k);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_susp_adj);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_susp_hard_limit);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_susp_min_height);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_fric_fwd);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_fric_side);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_fric_brake);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_fric_hand_brake);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_body_mass);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_roll_stability);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_pitch_stability);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_pitch_roll_resistance);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_yaw_resistance);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_upright_strength);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tilt_fakey);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_peel_out_max_speed);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_damp_coast);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_damp_brake);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_damp_hand);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_auto_hand_brake_min_speed);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_traction_type);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(m_bbox_min, 3);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(m_bbox_max, 3);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(m_mass_center_offset, 3);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(m_buoyancybox_min, 3);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(m_buoyancybox_max, 3);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_water_speed_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_water_accel_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_water_turn_accel);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_water_turn_speed_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_water_ebrake_power);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD_ARR(m_boat_motor_offset, 3);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_boat_speed_rise);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_boat_speed_tilt);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_boat_side_fric_scale);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_boat_forward_fric_scale);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_boat_vertical_fric_scale);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_jump_force);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_tire_fric_side_max);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_drive_on_walls);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_linear_drag_scale);
			VEHICLE_DUMP_VEHICLE_PARAMETER_FIELD(m_angular_drag_scale);
			return data;

		}

		Json IVehicleDef::dump_vehicle_engine(VehicleDef* asset)
		{
			
			Json data;
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(idleRpms);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(maxRpms);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(maxTorque);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(brakingCoeff);
			for (int i = 0; i < 4; i++)
			{
				data["loadFadeParams"][i] = asset->engine.loadFadeParams[i];
			}
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(loadScale);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(loadSmoothing);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(throttleLag);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(pitchScale);
			for (int i = 0; i < 5; i++)
			{
				if (asset->engine.onload[i].name)
				{
					data["onload"][i]["name"] = asset->engine.onload[i].name;
				}
				else
				{
					data["onload"][i]["name"] = "";
				}
				data["onload"][i]["alias"] = asset->engine.onload[i].alias;
				for (int j = 0; j < 5; j++)
				{
					data["onload"][i]["params"][j] = asset->engine.onload[i].params[j];
				}
			}
			for (int i = 0; i < 5; i++)
			{
				if (asset->engine.offload[i].name)
				{
					data["offload"][i]["name"] = asset->engine.offload[i].name;
				}
				else
				{
					data["offload"][i]["name"] = "";
				}
				data["offload"][i]["alias"] = asset->engine.offload[i].alias;
				for (int j = 0; j < 5; j++)
				{
					data["offload"][i]["params"][j] = asset->engine.offload[i].params[j];
				}
			}
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(numGears);
			VEHICLE_DUMP_VEHICLE_ENGINE_FIELD(loopLastGear);
			for (int i = 0; i < 10; i++)
			{
				data["gears"][i]["minRPM"] = asset->engine.gears[i].minRPM;
				data["gears"][i]["maxRPM"] = asset->engine.gears[i].maxRPM;
				data["gears"][i]["ratio"] = asset->engine.gears[i].ratio;
			}
			return data;
		}

		cspField_t* get_cspfield_for_offset(int offset)
		{
			cspField_t* vehicleDefFields = reinterpret_cast<cspField_t*>(0x101EBA8);
			for (int i = 0; i < 556; i++)
			{
				if (vehicleDefFields[i].iOffset == offset)
				{
					return &vehicleDefFields[i];
				}
			}
			return nullptr;
		}

		void IVehicleDef::dump(VehicleDef* asset)
		{
			Json data;
			//std::string vehicleDefString = "VEHICLEFILE";
			//
			//for (int i = 0; i < sizeof(VehicleDef); i += 4)
			//{
			//	cspField_t* field = get_cspfield_for_offset(i);
			//	if (field == nullptr)
			//	{
			//		continue;
			//	}
			//	
			//	switch (field->iFieldType)
			//	{
			//	case 0x12:
			//		int* typeValue = reinterpret_cast<int*>(reinterpret_cast<char*>(asset) + i);
			//		const char** s_vehicleClassNames = reinterpret_cast<const char**>(0x101E45C);
			//		vehicleDefString += "\\"s + std::string(field->szName) + "\\"s + std::string(s_vehicleClassNames[*typeValue]);
			//		break;
				//case 0x13:
				//	v6 = 0;
				//	while (I_stricmp(pValue, (&s_vehicleCameraModes)[v6]))
				//	{
				//		if (++v6 >= 8)
				//			goto LABEL_14;
				//	}
				//	pStruct->cameraMode = v6;
				//LABEL_14:
				//	if (v6 != 8)
				//		goto LABEL_30;
				//	Com_Error(ERR_DROP, "\x15Unknown vehicle camera mode [%s]\n");
				//	result = 1;
				//	break;
				//case 0x14:
				//	v7 = TRACTION_TYPE_FRONT;
				//	while (I_stricmp(pValue, (&s_tractionTypeNames)[v7]))
				//	{
				//		if (++v7 >= NUM_TRACTION_TYPES)
				//			goto LABEL_21;
				//	}
				//	pStruct->nitrousVehParams.m_traction_type = v7;
				//LABEL_21:
				//	if (v7 != NUM_TRACTION_TYPES)
				//		goto LABEL_30;
				//	Com_Error(ERR_DROP, "\x15Unknown traction type [%s]\n");
				//	result = 1;
				//	break;
				//case 0x15:
				//	*(float*)((char*)&pStruct->name + fieldOffset) = atof(pValue) * 17.6;
				//	result = 1;
				//	break;
				//case 0x16:
				//	*(float*)((char*)&pStruct->name + fieldOffset) = atof(pValue) * 0.001;
				//	result = 1;
				//	break;
				//case 0x17:
				//	if (I_stricmp(pValue, "axis"))
				//	{
				//		if (I_stricmp(pValue, "allies"))
				//		{
				//			Com_Error(ERR_DROP, "unknown team '%s', should be axis or allies\n");
				//			goto LABEL_30;
				//		}
				//		pStruct->eTeam = 1;
				//		result = 1;
				//	}
				//	else
				//	{
				//		pStruct->eTeam = 2;
				//		result = 1;
				//	}
				//	break;
				//case 0x1A:
				//LABEL_30:
				//	result = 1;
				//	break;
				//default:
				//	result = 0;
				//	break;
			//	}

			//}
			data["name"] = asset->name;
			data["type"] = asset->type;
			VEHICLE_DUMP_FIELD(remoteControl);
			VEHICLE_DUMP_FIELD(bulletDamage);
			VEHICLE_DUMP_FIELD(armorPiercingDamage);
			VEHICLE_DUMP_FIELD(grenadeDamage);
			VEHICLE_DUMP_FIELD(projectileDamage);
			VEHICLE_DUMP_FIELD(projectileSplashDamage);
			VEHICLE_DUMP_FIELD(heavyExplosiveDamage);
			VEHICLE_DUMP_FIELD(cameraMode);
			VEHICLE_DUMP_FIELD(autoRecenterOnAccel);
			VEHICLE_DUMP_FIELD(thirdPersonDriver);
			VEHICLE_DUMP_FIELD(thirdPersonUseVehicleRoll);
			VEHICLE_DUMP_FIELD(thirdPersonCameraPitchVehicleRelative);
			VEHICLE_DUMP_FIELD(thirdPersonCameraHeightWorldRelative);
			VEHICLE_DUMP_FIELD(thirdPersonCameraRange);
			VEHICLE_DUMP_FIELD(thirdPersonCameraMinPitchClamp);
			VEHICLE_DUMP_FIELD(thirdPersonCameraMaxPitchClamp);
			VEHICLE_DUMP_FIELD_ARR(thirdPersonCameraHeight, 2);
			VEHICLE_DUMP_FIELD_ARR(thirdPersonCameraPitch, 2);
			VEHICLE_DUMP_FIELD(cameraAlwaysAutoCenter);
			VEHICLE_DUMP_FIELD(cameraAutoCenterLerpRate);
			VEHICLE_DUMP_FIELD(cameraAutoCenterMaxLerpRate);
			VEHICLE_DUMP_FIELD(thirdPersonCameraSpringDistance);
			VEHICLE_DUMP_FIELD(thirdPersonCameraSpringTime);
			VEHICLE_DUMP_FIELD(thirdPersonCameraHandbrakeTurnRateInc);
			VEHICLE_DUMP_FIELD(cameraFOV);
			VEHICLE_DUMP_FIELD(cameraRollFraction);
			VEHICLE_DUMP_FIELD_ARR(tagPlayerOffset, 3);
			VEHICLE_DUMP_FIELD(killcamCollision);
			VEHICLE_DUMP_FIELD(killcamDist);
			VEHICLE_DUMP_FIELD(killcamZDist);
			VEHICLE_DUMP_FIELD(killcamMinDist);
			VEHICLE_DUMP_FIELD(killcamZTargetOffset);
			VEHICLE_DUMP_FIELD(killcamFOV);
			VEHICLE_DUMP_FIELD(killcamNearBlur);
			VEHICLE_DUMP_FIELD(killcamNearBlurStart);
			VEHICLE_DUMP_FIELD(killcamNearBlurEnd);
			VEHICLE_DUMP_FIELD(killcamFarBlur);
			VEHICLE_DUMP_FIELD(killcamFarBlurStart);
			VEHICLE_DUMP_FIELD(killcamFarBlurEnd);
			VEHICLE_DUMP_FIELD(isDrivable);
			VEHICLE_DUMP_FIELD(numberOfSeats);
			VEHICLE_DUMP_FIELD(numberOfGunners);
			VEHICLE_DUMP_FIELD_ARR(seatSwitchOrder, 11);
			VEHICLE_DUMP_FIELD(driverControlledGunPos);
			VEHICLE_DUMP_FIELD_ARR(entryPointRadius, 5);
			VEHICLE_DUMP_FIELD(texScrollScale);
			VEHICLE_DUMP_FIELD(wheelRotRate);
			VEHICLE_DUMP_FIELD(extraWheelRotScale);
			VEHICLE_DUMP_FIELD(wheelChildTakesSteerYaw);
			VEHICLE_DUMP_FIELD(maxSpeed);
			VEHICLE_DUMP_FIELD(maxSpeedVertical);
			VEHICLE_DUMP_FIELD(accel);
			VEHICLE_DUMP_FIELD(accelVertical);
			VEHICLE_DUMP_FIELD(rotRate);
			VEHICLE_DUMP_FIELD(rotAccel);
			VEHICLE_DUMP_FIELD(maxBodyPitch);
			VEHICLE_DUMP_FIELD(maxBodyRoll);
			VEHICLE_DUMP_FIELD(collisionDamage);
			VEHICLE_DUMP_FIELD(collisionSpeed);
			VEHICLE_DUMP_FIELD(suspensionTravel);
			VEHICLE_DUMP_FIELD(heliCollisionScalar);
			VEHICLE_DUMP_FIELD(viewPitchOffset);
			VEHICLE_DUMP_FIELD(viewInfluence);
			VEHICLE_DUMP_FIELD_ARR(tiltFromAcceleration, 2);
			VEHICLE_DUMP_FIELD_ARR(tiltFromDeceleration, 2);
			VEHICLE_DUMP_FIELD_ARR(tiltFromVelocity, 2);
			VEHICLE_DUMP_FIELD_ARR(tiltSpeed, 2);
			VEHICLE_DUMP_FIELD(turretWeapon);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(horizSpanLeft);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(horizSpanRight);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(vertSpanUp);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(vertSpanDown);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(horizResistLeft);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(horizResistRight);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(vertResistUp);
			VEHICLE_DUMP_TURRETVIEWLIMITS_FIELD(vertResistDown);
			VEHICLE_DUMP_FIELD(turretRotRate);
			VEHICLE_DUMP_FIELD(turretClampPlayerView);
			VEHICLE_DUMP_FIELD(turretLockTurretToPlayerView);
			VEHICLE_DUMP_FIELD_ARR(gunnerWeapon, 4);
			VEHICLE_DUMP_FIELD_ARR(gunnerWeaponIndex, 4);
			VEHICLE_DUMP_FIELD(gunnerRotRate);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					data["gunnerRestAngles"][i][j] = asset->gunnerRestAngles[i][j];
				}
			}
			for (int i = 0; i < 6; i++)
			{
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(horizSpanLeft, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(horizSpanRight, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(vertSpanUp, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(vertSpanDown, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(horizResistLeft, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(horizResistRight, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(vertResistUp, i);
				VEHICLE_DUMP_PASSENGERVIEWLIMITS_FIELD(vertResistDown, i);
			}
			VEHICLE_DUMP_FIELD_ARR(sndNames, 2);
			VEHICLE_DUMP_FIELD_ARR(sndIndices, 2);
			VEHICLE_DUMP_FIELD_ARR(sndMaterialNames, 3);
			VEHICLE_DUMP_FIELD(skidSpeedMin);
			VEHICLE_DUMP_FIELD(skidSpeedMax);
			VEHICLE_DUMP_FIELD(futzName);
			VEHICLE_DUMP_FIELD(futzBlend);
			VEHICLE_DUMP_FIELD(animType);
			VEHICLE_DUMP_FIELD(animSet);
			VEHICLE_DUMP_FIELD(scriptedAnimationEntry);
			VEHICLE_DUMP_FIELD_ARR(mantleAngles, 4);
			VEHICLE_DUMP_FIELD_ARR(extraWheelTags, 4);
			VEHICLE_DUMP_FIELD(driverHideTag);
			for (int i = 0; i < 4; i++)
			{
				if (asset->attachmentModels && asset->attachmentModels[i] && asset->attachmentModels[i]->name)
				{
					data["attachmentModels"][i] = asset->attachmentModels[i]->name;
				}
				else
				{
					data["attachmentModels"][i] = "";
				}
			}
			VEHICLE_DUMP_FIELD_ARR(attachmentTags, 4);
			for (int i = 0; i < 4; i++)
			{
				if (asset->deathAttachmentModels && asset->deathAttachmentModels[i] && asset->deathAttachmentModels[i]->name)
				{
					data["deathAttachmentModels"][i] = asset->deathAttachmentModels[i]->name;
				}
				else
				{
					data["deathAttachmentModels"][i] = "";
				}
			}
			VEHICLE_DUMP_FIELD_ARR(deathAttachmentTags, 4);
			VEHICLE_DUMP_FIELD_ARR(tracerOffset, 2);
			VEHICLE_DUMP_ASSET(model);
			VEHICLE_DUMP_ASSET(viewModel);
			VEHICLE_DUMP_ASSET(deathModel);
			VEHICLE_DUMP_ASSET(enemyModel);
			VEHICLE_DUMP_FIELD(modelSwapDelay);
			VEHICLE_DUMP_ASSET(exhaustFx);
			VEHICLE_DUMP_FIELD(oneExhaust);
			for (int i = 0; i < 32; i++)
			{
				if (asset->treadFx && asset->treadFx[i] && asset->treadFx[i]->name)
				{
					data["treadFx"][i] = asset->treadFx[i]->name;
				}
				else
				{
					data["treadFx"][i] = "";
				}
			}
			VEHICLE_DUMP_ASSET(deathFx);
			VEHICLE_DUMP_FIELD(deathFxTag);
			VEHICLE_DUMP_FIELD(deathFxSound);
			for (int i = 0; i < 4; i++)
			{
				if (asset->lightFx && asset->lightFx[i] && asset->lightFx[i]->name)
				{
					data["lightFx"][i] = asset->lightFx[i]->name;
				}
				else
				{
					data["lightFx"][i] = "";
				}
			}
			VEHICLE_DUMP_FIELD_ARR(lightFxTag, 4);
			VEHICLE_DUMP_ASSET(friendlyLightFx);
			VEHICLE_DUMP_FIELD(friendlyLightFxTag);
			VEHICLE_DUMP_ASSET(enemyLightFx);
			VEHICLE_DUMP_FIELD(enemyLightFxTag);
			VEHICLE_DUMP_FIELD(radiusDamageMin);
			VEHICLE_DUMP_FIELD(radiusDamageMax);
			VEHICLE_DUMP_FIELD(radiusDamageRadius);
			VEHICLE_DUMP_FIELD(shootShock);
			VEHICLE_DUMP_FIELD(shootRumble);
			VEHICLE_DUMP_FIELD(deathQuakeScale);
			VEHICLE_DUMP_FIELD(deathQuakeDuration);
			VEHICLE_DUMP_FIELD(deathQuakeRadius);
			VEHICLE_DUMP_FIELD(rumbleType);
			VEHICLE_DUMP_FIELD(rumbleScale);
			VEHICLE_DUMP_FIELD(rumbleDuration);
			VEHICLE_DUMP_FIELD(rumbleRadius);
			VEHICLE_DUMP_FIELD(rumbleBaseTime);
			VEHICLE_DUMP_FIELD(rumbleAdditionalTime);
			VEHICLE_DUMP_FIELD(healthDefault);
			VEHICLE_DUMP_FIELD(healthMin);
			VEHICLE_DUMP_FIELD(healthMax);
			VEHICLE_DUMP_FIELD(eTeam);
			VEHICLE_DUMP_FIELD(boostAccelMultiplier);
			VEHICLE_DUMP_FIELD(boostDuration);
			VEHICLE_DUMP_FIELD(boostSpeedIncrease);
			VEHICLE_DUMP_FIELD(addToCompass);
			VEHICLE_DUMP_FIELD(addToCompassEnemy);
			VEHICLE_DUMP_FIELD(compassIcon);
			VEHICLE_DUMP_ASSET(compassIconMaterial);
			VEHICLE_DUMP_FIELD(gasButtonName);
			VEHICLE_DUMP_FIELD(gasButton);
			VEHICLE_DUMP_FIELD(reverseBrakeButtonName);
			VEHICLE_DUMP_FIELD(reverseBrakeButton);
			VEHICLE_DUMP_FIELD(handBrakeButtonName);
			VEHICLE_DUMP_FIELD(handBrakeButton);
			VEHICLE_DUMP_FIELD(attackButtonName);
			VEHICLE_DUMP_FIELD(attackButton);
			VEHICLE_DUMP_FIELD(attackSecondaryButtonName);
			VEHICLE_DUMP_FIELD(attackSecondaryButton);
			VEHICLE_DUMP_FIELD(boostButtonName);
			VEHICLE_DUMP_FIELD(boostButton);
			VEHICLE_DUMP_FIELD(moveUpButtonName);
			VEHICLE_DUMP_FIELD(moveUpButton);
			VEHICLE_DUMP_FIELD(moveDownButtonName);
			VEHICLE_DUMP_FIELD(moveDownButton);
			VEHICLE_DUMP_FIELD(switchSeatButtonName);
			VEHICLE_DUMP_FIELD(switchSeatButton);
			//VEHICLE_DUMP_FIELD(steerGraphName);
			//VEHICLE_DUMP_FIELD(steerGraph);
			//VEHICLE_DUMP_FIELD(accelGraphName);
			//VEHICLE_DUMP_FIELD(accelGraph);
			VEHICLE_DUMP_FIELD(isNitrous);
			VEHICLE_DUMP_FIELD(isFourWheelSteering);
			VEHICLE_DUMP_FIELD(useCollmap);
			VEHICLE_DUMP_FIELD(radius);
			VEHICLE_DUMP_FIELD(minHeight);
			VEHICLE_DUMP_FIELD(maxHeight);
			VEHICLE_DUMP_FIELD(max_fric_tilt_angle);
			VEHICLE_DUMP_FIELD(max_fric_tilt);
			VEHICLE_DUMP_FIELD(noDirectionalDamage);
			VEHICLE_DUMP_FIELD(fakeBodyStabilizer);
			VEHICLE_DUMP_FIELD(vehHelicopterBoundsRadius);
			VEHICLE_DUMP_FIELD(vehHelicopterDecelerationFwd);
			VEHICLE_DUMP_FIELD(vehHelicopterDecelerationSide);
			VEHICLE_DUMP_FIELD(vehHelicopterDecelerationUp);
			VEHICLE_DUMP_FIELD(vehHelicopterTiltFromControllerAxes);
			VEHICLE_DUMP_FIELD(vehHelicopterTiltFromFwdAndYaw);
			VEHICLE_DUMP_FIELD(vehHelicopterTiltFromFwdAndYaw_VelAtMaxTilt);
			VEHICLE_DUMP_FIELD(vehHelicopterTiltMomentum);
			VEHICLE_DUMP_FIELD(vehHelicopterQuadRotor);
			VEHICLE_DUMP_FIELD(vehHelicopterAccelTwardsView);
			VEHICLE_DUMP_FIELD(maxRotorArmMovementAngle);
			VEHICLE_DUMP_FIELD(maxRotorArmRotationAngle);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainHeight);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainMaxHeight);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainHeightLimit);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainHeightAccel);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainHeightMinimum);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainHeightMaximum);
			VEHICLE_DUMP_FIELD(vehHelicopterMaintainCeilingMinimum);
			VEHICLE_DUMP_FIELD(joltVehicle);
			VEHICLE_DUMP_FIELD(joltVehicleDriver);
			VEHICLE_DUMP_FIELD(joltMaxTime);
			VEHICLE_DUMP_FIELD(joltTime);
			VEHICLE_DUMP_FIELD(joltWaves);
			VEHICLE_DUMP_FIELD(joltIntensity);
			data["nitrousVehParams"] = dump_vehicle_parameters(asset);
			VEHICLE_DUMP_FIELD_ARR(driveBySoundRadius, 2);
			int i = offsetof(VehicleDef, steerGraphName);
			for (int i = 0; i < 40; i++)
			{
				if (asset->driveBySounds[i].name)
				{
					data["driveBySounds"][i]["name"] = asset->driveBySounds[i].name;
				}
				else
				{
					data["driveBySounds"][i]["name"] = "";
				}
				data["driveBySounds"][i]["alias"] = asset->driveBySounds[i].alias;
				data["driveBySounds"][i]["apex"] = asset->driveBySounds[i].apex;
			}
			VEHICLE_DUMP_FIELD(doFootSteps);
			VEHICLE_DUMP_FIELD(isSentient);
			data["engine"] = dump_vehicle_engine(asset);
			for (int i = 0; i < 2; i++)
			{
				data["antenna"][i]["springK"] = asset->antenna[i].springK;
				data["antenna"][i]["damp"] = asset->antenna[i].damp;
				data["antenna"][i]["length"] = asset->antenna[i].length;
				data["antenna"][i]["gravity"] = asset->antenna[i].gravity;
			}
			VEHICLE_DUMP_FIELD(csvInclude);
			VEHICLE_DUMP_FIELD(customFloat0);
			VEHICLE_DUMP_FIELD(customFloat1);
			VEHICLE_DUMP_FIELD(customFloat2);
			VEHICLE_DUMP_FIELD(customBool0);
			VEHICLE_DUMP_FIELD(customBool1);
			VEHICLE_DUMP_FIELD(customBool2);
			std::string json = data.dump(4);
			auto file = FileSystem::FileOpen("vehicles\\"s + asset->name, "wb");
			fwrite(json.data(), json.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}
