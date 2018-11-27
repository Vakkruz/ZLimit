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
			//slog("Freed entity #%i", i);
		}
		free(entity_manager.entityList);
	}
	memset(&entity_manager, 0, sizeof(EntityManager));
	slog("entity system closed");

}

Entity *new_entity(char name)
{
	int i;
	for (i = 0; i < entity_manager.maxEntities; i++)
	{
		if (entity_manager.entityList[i].used == 0)
		{
			memset(&entity_manager.entityList[i], 0, sizeof(Entity));
			entity_manager.entityList[i].id = entity_manager.autoincrement++;
			entity_manager.entityList[i].used = 1;
			
			vector2d_set(entity_manager.entityList[i].scale, 1, 1);
			if (name == "bot") {
				entity_manager.entityList[i].type = BOT;
				entity_manager.entityList[i].modelname = "cube";
			}
			if (name == "player") {
				entity_manager.entityList[i].type = PLAYER;
				entity_manager.entityList[i].modelname = "EGX";
			}
			
			//slog("Entity created: Number #%i", i);
			return &entity_manager.entityList[i];
			
		}
	}
	return NULL;
}


void free_entity(Entity *self)
{
	Model model;
	int i;
	if (!self)return;

	if (self->free)self->free(self);
	memset(self, 0, sizeof(Entity));
}

void draw_entity(Entity *self, Uint32 bufframe, VkCommandBuffer combuff) {

	Model *model;
	model = gf3d_model_load(self->modelname);

	gf3d_model_draw(model,bufframe,combuff);

}

void draw_all_ents(Uint32 bufframe, VkCommandBuffer combuff) {
	int i;
	for (i = 0; i < entity_manager.maxEntities; i++) {
		draw_entity(entity_manager.entityList[i], bufframe, combuff);
	}
}