#pragma once

#include <sdk.hpp>

enum NPCMoveType
{
	NPCMoveType_None,
	NPCMoveType_Walk,
	NPCMoveType_Jog,
	NPCMoveType_Sprint
};

struct INPC : public IExtensible, public IEntity
{
	/// Get player instance of NPC.
	virtual IPlayer* getPlayer() = 0;

	/// Spawn NPC.
	virtual void spawn() = 0;

	/// Move NPC to a specified location.
	virtual bool move(Vector3 position, NPCMoveType moveType) = 0;

	/// Stop NPC from moving.
	virtual void stopMove() = 0;

	/// Set NPC skin
	virtual void setSkin(int model) = 0;
};

struct NPCEventHandler
{
	virtual void onNPCFinishMove(INPC& npc) {};
	virtual void onNPCCreate(INPC& npc) {};
	virtual void onNPCDestroy(INPC& npc) {};
};

static const UID NPCComponent_UID = UID(0x3D0E59E87F4E90BC);
struct INPCComponent : public IPool<INPC>, public INetworkComponent
{
	PROVIDE_UID(NPCComponent_UID)

	/// Get the npc event dispatcher
	virtual IEventDispatcher<NPCEventHandler>& getEventDispatcher() = 0;

	/// Create a controllable NPC
	virtual INPC* create(StringView name) = 0;

	/// Destroy an NPC. We need this because it's more than just an entity removal from a pool
	virtual void destroy(INPC& npc) = 0;
};