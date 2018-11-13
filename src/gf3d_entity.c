#include "gf3d_entity.h"
#include "simple_logger.h"


typedef struct{
	Uint32 maxEntities;
	Entity *entityList;
	Uint64 autoincrement;
}EntityManager;

static EntityManager entity_manager = { 0 };

void entity_sys_start(Uint32 MaxEntities) {
	if (!MaxEntities)
	{
		slog("cannot initialize entity system for zero entities");
		return;
	}
	memset(&entity_manager, 0, sizeof(EntityManager));

	entity_manager.entityList = (Entity*)malloc(sizeof(Entity)*MaxEntities);
	if (!entity_manager.entityList)
	{
		slog("failed to allocate entity list");
		entity_sys_end();
		return;
	}
	memset(entity_manager.entityList, 0, sizeof(Entity)*MaxEntities);
	entity_manager.maxEntities = MaxEntities;
	atexit(entity_sys_end);
	slog("entity system initialized");
}

void entity_sys_end() {

	int i;
	if (entity_manager.entityList != NULL)
	{
		for (i = 0; i < entity_manager.maxEntities; i++)
		{
			free_entity(&entity_manager.entityList[i]);
		}
		free(entity_manager.entityList);
	}
	memset(&entity_manager, 0, sizeof(EntityManager));
	slog("entity system closed");

}

Entity *new_entity()
{
	int i;
	for (i = 0; i < entity_manager.maxEntities; i++)
	{
		if (entity_manager.entityList[i].used == 0)
		{

			memset(&entity_manager.entityList[i], 0, sizeof(Entity));
			entity_manager.entityList[i].id = entity_manager.autoincrement++;
			entity_manager.entityList[i].used = 1;
			

			return &entity_manager.entityList[i];
		}
	}
	return NULL;
}


void free_entity(Entity *self)
{
	int i;
	if (!self)return;
	if (self->free)self->free(self);
	memset(self, 0, sizeof(Entity));
}

void draw_entity(Entity *self) {

}